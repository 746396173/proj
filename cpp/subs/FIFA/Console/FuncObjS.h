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
#include <Net/BufCallCoorTrans.h>
#include "../Game/Facility/GTypes.h"
#include "CfgStruct.h"
#include <Communicate/CG_Defines.h>
#include <Net/JsonCall.h>

class FuncObj_NormalS;
class SessionOperS : public BufCall_SocketExcept{
public:
	SessionOperS( FuncObj_NormalS& func_obj_normal );

	//interfaces
public:
	//ƣ��
	void SetMatchAddict();
	//����EP
	void SetEP( double ep );
	//��������
	void SetMatchCnt( int match_cnt );
	//��������״̬
	void SetRunState( const char* str_run_state );
	//���ý�����
	void SetTrainerName( const char* str_trainer_name );
	//���ý����ȼ�
	void SetTrainerLevel( int level );
	//���ýű������Ϣ
	void SetScriptOutputInfo( const std::string& output_info );
	//��ʼ�ű�
	void StartRunScript();
	//����ĳ����Ϸ����
	void OnGameState( int game_state );
	//echo message
	void EchoMsg( const char* msg );
	//���
	void BanAccount();
	//���ֺ���Ա
	void DiscoverGoodPlayer();
	//����
	void ExchangeGameAc();
	//�汾����
	bool VersionEndTime();
	//���������ﵽ����
	void MatchLimitCnt();
	//����������
	void SetOutRes(pt_csz out_res);
	//������ԱID
	void SetSpid(pt_csz spid);

	//test
public:
	//������Ա��Ϣ
	void SetPlayersInfo( const Json::Value& players_array );
	//������Ʒ��Ϣ
	void SetItemsInfo( const Json::Value& items_array );
	//�����ҵĳ����б���Ϣ
	void SetMyOfferList( const Json::Value& sold_players );
	//���������ŵĳ�����
	void SetOtherOfferItems( const Json::Value& sold_players );

private:
	FuncObj_NormalS&				func_obj_normal_;

	BC_REG_CLS_DECLARE(SessionOperS);
};
//////////////////////////////////////////////////////////////////////////
//Э�����������ս��
//game coordinate
class CoorTrans_CS : public CoorTransTrack{
public:
	CoorTrans_CS( FuncObj_NormalS& func_obj_normal, const TrackIterPtrT& track_iter );
	P_CoorTypeT GetCoorType() const;

private:
	FuncObj_NormalS&				nor_;
};
//////////////////////////////////////////////////////////////////////////
class FuncObj_NormalS : public Session{
	friend class SessionOperS;
	friend class CoorTrans_CS;

	//type definitions
public:
	struct stGameInfo{
		double					cur_ep_;
		double					gain_total_ep_;				//��õ���EP
		int						match_cnt_;					//��������
		int						trainer_level_;				//�����ȼ�
		CString					running_state_;				//����״̬
		CString					trainer_name_;				//������
		GType::enGameState		game_state_;				//��Ϸ״̬

		stGameInfo();
	};
	typedef Iterator<FuncObj_NormalS*> Iterator;
	typedef std::shared_ptr<Iterator> IteratorPtr;

public:
	FuncObj_NormalS( Server& server );

	//interfaces
public:
	//�õ�FuncObj_IInter
	FuncObj_IInter& GetFuncObjInter();
	//�õ�glua
	GLuaS& GetGLua();
	//get json echo
	JsonEcho& GetJsonEcho();
	//�õ�session operate
	SessionOperS& GetSessionOper();
	//�õ�coordinate
	CoorTrans_CS& GetCoorTrans();
	LuaScriptS& GetLuaScript();
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

public:
	bool SetAccountInfo( const P_Modify_Account& account_info );
	//��ӽ�ֹ��
	void AddProhibitItem( stSpecificCfg::enProhibitReason reason, LPCTSTR str_run_state );

	//������Ϣ
protected:
	bool OnCallLuaFuncResult( P_Exec_CallLuaFuncResult& func_res );
	//���������Ϣ
	bool OnMatchInfo( P_Exec_MatchInfo& match_info );
	//Զ�̵���lua
	void CallRemoteLua( const char* lua_func_name, const char* lua_func_param );
	//��Ϸ������Ϣ
	bool OnGameProccessInfo( const P_Exec_GameProccessInfo& game_proccess_info );

protected:
	virtual bool OnUserMsg( P_MsgNT msg_num, void* param, size_t param_size );
	bool OnConnected( IoConnectBase* connect ) override;
	void DoOnAccepted();
	void OnDisconnect( IoConnectBase* connect ) override;

	//func objs
private:
	FuncObj_IInter			func_obj_inter_;
	GLuaS					glua_;
	JsonEcho				json_echo_;
	SessionOperS			session_oper_;
	CoorTrans_CS			coordinate_;
	LuaScriptS				lua_script_;

private:
	std::string				account_;
	std::string				password_;
	std::string				service_name_;
	stGameInfo				game_info_;
	enGameAcType	game_ac_type_;
	int						service_idx_;
	CString					str_final_run_state_;
	DWORD					game_process_id_;
};
