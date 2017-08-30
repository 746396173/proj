#pragma once
/*
@author zhp
@date 2014-2-18 13:49
@purpose function objects of console
*/
#include "Socket/server.h"
#include "Protocol/P_BaseStruct.h"
#include "FuncObjs/FuncObjInter.h"
#include "GLuaS.h"
#include "Protocol/P_NormalMsg.h"
#include "Script/JsonCall.h"
#include "CfgStruct.h"
#include <Communicate/CG_Defines.h>
#include <Funcobjs/FuncObjCoor.h>

class FuncObj_CreateTrainerS : public FuncObj_Game{
public:
	FuncObj_CreateTrainerS( FuncObj* parent );

protected:
	virtual void Accept( FuncObjVisitor* visitor );

private:
	stPlayerInfo			player_info_;
};

class FuncObj_NormalS;
class SessionOperS : public JsonEchoBase{
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
	//����HP
	void SetCurHp( int hp );
	//���ý�ɫ��
	void SetRoleName( const std::string& role_name );
	//���ý�ɫ�ȼ�
	void SetRoleLvl( int role_lvl );
	//����ƣ��ֵ
	void SetFatigueData( int fatigue_data );
	//�������ڵ�ͼ�򷿼�
	void SetCurMapRoomName( const std::string& map_room_name );
	//���õ�ǰ���
	void SetCurGold( int cur_gold );
	//����ְҵ��
	void SetJobName( const std::string& job_name );
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

protected:
	virtual bool OnThisMemCall( const stThisCallHelper& helper );

private:
	FuncObj_NormalS&				func_obj_normal_;
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
class FuncObj_NormalS : public Session_Aes{
	friend class SessionOperS;
	friend class CoorTrans_CS;

	//type definitions
public:
	struct stGameInfo{
		CString					running_state_;				//����״̬
		int						cur_hp_;
		CString					role_name_;					//��ɫ��
		std::string				role_name_a_;
		int						role_lvl_;
		CString					map_room_name_;
		int						cur_gold_;
		int						gained_gold_;
		CString					job_name_;
		int						fatigue_data_;

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

public:
	void OnDisconnect( IoConnectBase* connect );
	virtual void Accept( FuncObjVisitor* visitor );

public:
	void SetAccountInfo( const P_Modify_Account& account_info );
	//��ӽ�ֹ��
	void AddProhibitItem( stSpecificCfg::enProhibitReason reason, LPCTSTR str_run_state );

	//������Ϣ
protected:
	bool OnCallLuaFuncResult( P_Exec_CallLuaFuncResult& func_res );
	//Զ�̵���lua
	void CallRemoteLua( const char* lua_func_name, const char* lua_func_param );
	//��Ϸ������Ϣ
	bool OnGameProccessInfo( const P_Exec_GameProccessInfo& game_proccess_info );

protected:
	virtual bool OnExec( P_MsgNT msg_num, void* param, size_t param_size );
	bool OnConnected( IoConnectBase* connect );
	void DoSomeConnected();

private:
	FuncObj_CreateTrainerS* CreatePlayer( const char* player_name );

	//func objs
private:
	FuncObj_IInter			func_obj_inter_;
	GLuaS					glua_;
	JsonEcho				json_echo_;
	SessionOperS			session_oper_;
	CoorTrans_CS			coor_trans_;
	LuaScriptS				lua_script_;

private:
	std::string				account_;
	std::string				password_;
	std::string				service_name_;
	stGameInfo				game_info_;
	enGameAcType			game_ac_type_;
	int						service_idx_;
	CString					str_final_run_state_;
	DWORD					game_process_id_;
};

class FuncObjVisitor{
public:
	virtual void Visit( FuncObj_NormalS* session_account ){}
	virtual void Visit( FuncObj_CreateTrainerS* player ){}
};