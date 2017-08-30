#pragma once
/*
@author zhp
@date 2014-2-18 13:49
@purpose function objects of console
*/
#include "Net/server.h"
#include "Protocol/P_BaseStruct.h"
#include "FuncObjs/FuncObjInter.h"
#include "GLuaS.h"
#include "Protocol/P_NormalMsg.h"
#include <Net/Bufcall_Socket.h>
#include "CfgStruct.h"
#include <Communicate/CG_Defines.h>
#include <Funcobjs/FuncObjCoor.h>
#include <Net/IoTimer.h>

class FuncObj_NormalS;
class SessionOperS : public BufCall_SocketExcept{
public:
	SessionOperS( FuncObj_NormalS& func_obj_normal );

	//interfaces
public:
	//ƣ��
	void SetMatchAddict();
	//��������״̬
	void SetRunState( const char* str_run_state );
	//���ýű������Ϣ
	void SetScriptOutputInfo( const std::string& output_info );
	//��ʼ�ű�
	void StartRunScript();
	//echo message
	void EchoMsg( const char* msg );
	//���
	void BanAccount();
	//����
	void ExchangeGameAc();
	//���ý�ɫ��
	void SetRoleName( const std::string& role_name );
	//���ý�ɫ�ȼ�
	void SetRoleLvl( int role_lvl );
	//������������֤��
	void SetFreeLieShouCnt( int fatigue_data );
	//���õ�������
	void SetSingleExp( int single_exp );
	//����˫������
	void SetDoubleExp( int double_exp );
	//�������ڵ�ͼ�򷿼�
	void SetCurMapRoomName( const std::string& map_room_name );
	//���õ�ǰ���
	void SetCurGold( int cur_gold );
	//���ý�ɫ�б���Ϣ
	void SetRoleListInfo( const Json::Value& json_array );
	//�Զ�������ѡ���ɫ
	void AutoCreateOrSelectRole();
	//��Ϸ��½�ɹ�
	void GameLoginSucceed();
	//��ɫ������
	void RoleRestricted();
	//������ɫʧ��
	void OnCreateRoleFailed();
	//����ƣ��ֵ
	void SetFatigueData( pt_qword fatigue_data );
	//��ɫˢ��
	void SetRolesUseOut();
	//���ʱ��
	void SetBanAcTime( const std::string& time );
	//���߲�����
	void NoReLoginAtDisconnect();
	void SetRunInfo(int cnt, bool script_running, const DateTimeLocal& last_recv_msg_time);

	//test
public:
	//������Ʒ��Ϣ
	void SetItemsInfo( const Json::Value& items_array );
	//�����ҵĳ����б���Ϣ
	void SetMyOfferList( const Json::Value& sold_players );
	//���������ŵĳ�����
	void SetOtherOfferItems( const Json::Value& sold_players );

private:
	FuncObj_NormalS&				func_obj_normal_;
	int								active_cnt_ = 0;

	BC_REG_CLS_DECLARE(SessionOperS);
};
//////////////////////////////////////////////////////////////////////////
class CoorTrans_CS : public CoorTransTrack{
public:
	CoorTrans_CS( FuncObj_NormalS& func_obj_normal, const TrackIterPtrT& track_iter );
	P_CoorTypeT GetCoorType() const;

private:
	FuncObj_NormalS&		nor_;
};
//////////////////////////////////////////////////////////////////////////
class FuncObj_NormalS : public Session{
	friend class SessionOperS;
	friend class CoorTrans_CS;

	//type definitions
public:
	struct stGameInfo{
		CString					running_state_;				//����״̬
		CString					role_name_;					//��ɫ��
		std::string				role_name_a_;
		int						role_lvl_;
		CString					map_room_name_;
		int						cur_gold_;
		boost::optional<int>	begin_gold_;
		CString					job_name_;
		int						free_lie_shou_cnt_;
		int						single_exp_;
		int						double_exp_;
		unsigned __int64		fatigue_data_;

		stGameInfo();
	};
	typedef Iterator<FuncObj_NormalS*> Iterator;
	typedef std::shared_ptr<Iterator> IteratorPtr;

public:
	FuncObj_NormalS( Server& server );
	~FuncObj_NormalS();

	//interfaces
public:
	//�õ�FuncObj_IInter
	FuncObj_IInter& GetFuncObjInter();
	//�õ�glua
	GLuaS& GetGLua();
	LuaScriptS& GetLuaScript();
	//get json echo
	JsonEcho& GetJsonEcho();
	//�õ�session operate
	SessionOperS& GetSessionOper();
	//�õ�coordinate
	CoorTrans_CS& GetCoorTrans();
	//��Ϸ��Ϣ
	stGameInfo& GetGameInfo();
	//game acount type
	void SetGameAcType( enGameAcType game_ac_type );
	enGameAcType GetGameAcType() const;
	//game service index
	void SetServiceIdx( int service_idx );
	int GetServiceIdx() const;
	//get ac
	const std::string& GetGameAc() const;
	const std::string& GetGameService() const;
	bool IsActiveTimeout(DateTimeLocal& time_now) const;
	void SetActiveTimeoutHandle();

public:
	void OnDisconnect(IoConnectBase* connect) override;

public:
	bool SetAccountInfo( const P_Modify_Account& account_info );
	//��ӽ�ֹ��
	void AddProhibitItem( stSpecificCfg::enProhibitReason reason, LPCTSTR str_run_state );
	//�����Ҽ�����
	void SetRightBtHit( bool is_right_hit );
	//���ó���Ѱ·
	void SetOpenVillagePath( bool is_open_village_path );
	void SetYouHuan(bool you_hua);

	//������Ϣ
protected:
	bool OnCallLuaFuncResult( P_Exec_CallLuaFuncResult& func_res );
	//Զ�̵���lua
	void CallRemoteLua( const char* lua_func_name, const char* lua_func_param );
	//��Ϸ������Ϣ
	bool OnGameProccessInfo( const P_Exec_GameProccessInfo& game_proccess_info );

protected:
	bool OnUserMsg( P_MsgNT msg_num, void* param, size_t param_size ) override;
	bool OnConnected(IoConnectBase* connect) override;
	void DoSomeConnected();

	//func objs
private:
	FuncObj_IInter			func_obj_inter_;
	GLuaS					glua_;
	JsonEcho				json_echo_;
	SessionOperS			session_oper_;
	CoorTrans_CS			coor_trans_;
	LuaScriptS				lua_script_;

public:
	std::string				account_;
	std::string				password_;
	std::string				service_name_;
	stGameInfo				game_info_;
	enGameAcType			game_ac_type_;
	int						service_idx_;
	CString					str_final_run_state_;
	DWORD					game_process_id_;
	IoTimerPtr				timer_login_succeed_;
	bool					no_relogin_at_disconnect_;
	bool					is_you_hua_;
	DateTimeLocal			last_active_time_;
	IoTimerPtr				timer_active_handle_;
};
