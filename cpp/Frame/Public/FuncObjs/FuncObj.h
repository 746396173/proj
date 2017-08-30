#pragma once
/*
@author zhp
@date 2013-12-20
@purpose function object�����ܶ���(���Ǻ�������)
*/
#include <boost/smart_ptr.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/lock_guard.hpp>
#include <map>
#include <vector>
#include "Protocol/P_Defines.h"
#include "Net/AllocHandler.h"
#include <queue>
#include "Common/MakeSecret.h"
#include "../DependSelfLib.h"
#include <Net/IoTimer.h>


class FuncObj;
struct P_Main
{
	pt_dword			msg_len;		//������Ϣ����
	pt_dword			obj_cnt;		//�������
	pt_dword			msg_count_;		//��Ϣ����
	P_FuncObjOper		obj_oper;

	P_Main();
	P_ObjId* GetObjsId();
	void* GetParam();
	pt_dword ParamSize();
	pt_dword GetTotalLength();
	//�õ�����msg_len֮��ĵ�ַ
	void* GetFollowMsgAddr();

	//encode
	bool Encode( FuncObj& func_obj, P_FuncObjOper oper, const void* param, pt_dword param_size, 
		pt_dword max_size );
	//decode
	bool Decode( FuncObj& func_obj );

	//����decode��������ڴ�
	static pt_dword CalcNeedMemory( FuncObj& func_obj, P_FuncObjOper oper, 
		const void* param, pt_dword param_size );
};

class FuncObj{
	friend P_Main;

public:
	FuncObj( FuncObj* parent, P_ObjId id );
	virtual ~FuncObj();
	template<typename T>
	T* CastTo(){
#ifdef _DEBUG
		return dynamic_cast<T*>(this);
#else
		return static_cast<T*>(this);
#endif
	}
	template<typename T>
	T& CastAs(){
		return *CastTo<T>();
	}

	//for send
public:
	//�ڲ�Э��
	virtual bool Inner( P_MsgNT msg_num, const void* param, size_t param_size );
	//�û���Ϣ
	virtual bool UserMsg( P_MsgNT msg_num, const void* param, size_t param_size );

	//for recv
protected:
	//�ڲ�Э��
	virtual bool OnInner( P_MsgNT msg_num, void* param, size_t param_size ){ return false; }
	//�û���Ϣ
	virtual bool OnUserMsg( P_MsgNT msg_num, void* param, size_t param_size ){ return false; }

public:
	FuncObj* GetParent();
	//find subobj
	virtual FuncObj* FindSubObj( P_ObjId id );
	//get identity
	P_ObjId GetId();
	//�õ�����func obj
	FuncObj* GetMosttop();
	//inner add
	virtual bool InnerAdd( FuncObj& func_obj );
	virtual bool ObjValid() const;
	virtual bool DoDecode( P_FuncObjOper oper, void* param, pt_dword param_size );

protected:
	//operate encode
	virtual bool OperEncode( P_FuncObjOper oper, const void* param, pt_dword param_size, FuncObj* msg_owner );
	//������׷�ӳ���
	virtual int GetAdditionalParamSize() const;
	virtual void EncodeAddtionalParam( void* additional_param ) const;

public:
	FuncObj*				parent_;

protected:
	P_ObjId					id_;
};

class FuncObjs : public FuncObj{
public:
	FuncObjs( FuncObj* parent, P_ObjId id );
	~FuncObjs();

	FuncObj* FindSubObj( P_ObjId id );
	bool InnerDelete( FuncObj* subobj );
	bool InnerAdd( FuncObj& func_obj );

private:
	typedef std::vector<FuncObj*> ContT;
	ContT::iterator FindSubObjIt( P_ObjId id );

public:
	ContT				objs_;
};

class FuncObj_Buffer : public FuncObjs{
public:
	FuncObj_Buffer( FuncObj* parent, P_ObjId id );
	virtual ~FuncObj_Buffer();

protected:
	typedef std::pair<bool, P_Main*> P_Main_UseT;

protected:
	bool OperEncode( P_FuncObjOper oper, const void* param, pt_dword param_size, FuncObj* msg_owner );
	struct RecvHelper{
		RecvHelper();
		void SetMsgPtr( P_Main* msg );
		static P_Main* MakePMain( decltype(P_Main::msg_len) msg_len );

		decltype(P_Main::msg_len)			msg_len_;			//������Ϣ����
		boost::shared_ptr<P_Main>			msg_;
	};

protected:
	std::queue<P_Main_UseT>		buffers_send_;
	std::queue<RecvHelper>		buffers_recv_;
};

//send or recv implementation
class FuncObjTop : public FuncObj_Buffer, public boost::enable_shared_from_this<FuncObjTop>{
	class DelaySend{
	public:
		virtual void DoSendOne();
	};
	class SendImpl : public DelaySend{
	public:
		SendImpl( FuncObjTop& obj );
		void DoSendOne();

	private:
		FuncObjTop&		obj_;
	};

public:
	FuncObjTop();
	boost::asio::ip::tcp::socket& socket();

public:
	virtual void DoDisconnect() = 0;
	bool ObjValid() const override;

protected:
	void AsyncReadFullPackage();
	void HandleReadBody(const boost::system::error_code& error,
		size_t bytes_transferred);
	void handle_write(const boost::system::error_code& error);
	bool OperEncode( P_FuncObjOper oper, const void* param, pt_dword param_size, FuncObj* msg_owner );
	//����һ����
	virtual void SendOnePackage( P_Main_UseT& package );
	//decodeһ����
	virtual bool DecodeOnePackage( P_Main& p_main, int bytes_transferred );

private:
	//read header
	void HandleReadHeader( const boost::system::error_code& error );
	void DoSomeReadError_( const boost::system::error_code* error );
	void BeginSendAnyPacket();

protected:
	//send mutex type
	typedef boost::mutex SendMutexT;
	typedef boost::lock_guard<SendMutexT> LockGuard;
	SendMutexT							send_mutex_;
	handler_allocator					allocator_;
	boost::asio::ip::tcp::socket		socket_;
	pt_dword					send_count_;
	pt_dword					recv_count_;
	SendImpl					real_send_;
	DelaySend					delay_send_;
	DelaySend*					send_one_;
};

//����
class FuncObjTop_Secret : public FuncObjTop{
public:
	//�õ�compo
	CryptoStrCompose& GetCompoSend();
	CryptoStrCompose& GetCompoRecv();

protected:
	void SendOnePackage( P_Main_UseT& package );
	bool DecodeOnePackage( P_Main& p_main, int bytes_transferred );
	bool HandleSecrectKeyImpl( const char* sercret_key, size_t sercret_key_size );

protected:
	void HandShake_Send();
	bool OnInner( P_MsgNT msg_num, void* param, size_t param_size );
	virtual void OccurSomeError_();
	bool OnSortSecretKey( pt_csz key_a, pt_dword key_size_a, pt_csz key_b, pt_dword key_size_b );

private:
	virtual bool DoConnectDone() = 0;
	virtual bool SortSecretKey( pt_csz recv_key, pt_dword key_size ) = 0;

protected:
	Secret_RC4			secret_rc4_send_;
	Secret_RC4			secret_rc4_recv_;
	CryptoStrCompose						compo_send_;
	CryptoStrCompose						compo_recv_;
	IoTimerPtr			timer_check_valid_;

protected:
	std::string			self_key_info_;
};

//ת�����������Ŀǰ�������ã���Щ������δ�����������δ���
class FuncObj_Dispatcher : public FuncObj{
public:
	FuncObj_Dispatcher( FuncObj* parent, FuncObj* recv, FuncObj* send );

public:
	bool OnInner( P_MsgNT msg_num, void* param, size_t param_size );
	bool OnUserMsg( P_MsgNT msg_num, void* param, size_t param_size );

	//for send
public:
	//lookup
	bool Inner( P_MsgNT msg_num, const void* param, size_t param_size );
	//another
	bool UserMsg( P_MsgNT msg_num, const void* param, size_t param_size );

private:
	FuncObj*					recv_;				//������
	FuncObj*					send_;				//������
};

//game
class FuncObj_Game : public FuncObj{
public:
	FuncObj_Game( FuncObj* parent );
};

//glua
class GLua : public FuncObj{
protected:
	GLua( FuncObj* parent );
};