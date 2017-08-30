#pragma once
#include "stdafx.h"
#include <Net/client.h>
#include <Protocol/P_NormalMsg.h>
#include "Net/IoTimer.h"
#include "Facility/GTypes.h"
#include "FuncObjs/FuncObjInter.h"
#include "GLua/GLuaC.h"
#include <Net/JsonCall.h>
#include <dinput.h>
#include "Facility/GClass.h"
#include <Poco/DateTime.h>
#include "../Console/CfgStruct.h"
#include <Net/Bufcall_Socket.h>
#include <Net/BufCallCoorTrans.h>
#include <Communicate/CG_Defines.h>


struct stDxinput_PressKey{
	BYTE				di_key_;			//dinput.h�е�DIK_ESCAPE��
	bool				is_down_;			//�Ƿ���
};
// DirectInput keyboard state buffer 
typedef BYTE (*DI_KeyStateBuffer)[256];
typedef std::queue<stDxinput_PressKey> DI_PressKeyQueue;
typedef std::pair<DI_PressKeyQueue, SharedMutex> DI_PressKeyPair;
typedef boost::shared_ptr<DI_PressKeyPair> DI_PressKeyPtr;
//////////////////////////////////////////////////////////////////////////
const P_ObjId kObjIdNormal = DEF_THE_CUSTOM_TEMPLATE_OBJ_ID_(40);
class FuncObj_NormalC;
class SessionOperC : public BufCall_SocketExcept{
public:
	SessionOperC( FuncObj_NormalC& func_obj_normal );

	//������֤
public:
	//�����Ƿ��½�ɹ�
	void SetLoginSucceed( bool succeed );
	//�����û�����ʱ��
	void SetEndDateTime( std::time_t end_time );
	//���ùؼ�����
	void SetAddrDatas( const Json::Value& addr_datas );

	//����
public:
	//���÷���id
	void SetGameSerIdx( int ser_idx );
	//������Ϸ�ŵ�����
	void SetGameAcType( int game_ac_type );
	//�ӿ���̨����game�Ĺ̶����ַ���
	void StableString( const std::string& stable_str );
	//Ч�鹫Կ
	void CheckRsaPubKey( const std::string& encode_str );

	//������
public:
	//�õ�������Ա����
	void GetPlayersInfo();
	//�õ�������Ʒ����
	void GetItemsInfo();
	//�õ��ҵĳ����б�
	void GetMyOfferList();
	//�õ������ŵĳ�����
	void GetOtherOfferItems();

private:
	FuncObj_NormalC&				func_obj_normal_;

	BC_REG_CLS_DECLARE(SessionOperC);
};
//////////////////////////////////////////////////////////////////////////
bool MakeTransRoute( P_CoorPacketToT& out_route, enGameAcType game_ac_type, int ser_id );
P_CoorPacketToT MakeTransRoute( enGameAcType game_ac_type, int ser_id );
const P_CoorPacketToT& GetTransRouteAny();
//Э�����������ս��
//game coordinate
class GCoordinateC : public BufCallCoorTrans{
public:
	GCoordinateC( FuncObj_NormalC& func_obj_normal );

	//�㲥������Ϣ
public:
	//������������
	void QuestSoldInfo();
	//�Լ����ǲֿ�ţ��򷢸���ͨ�ţ�������ͨ���򷢸��ֿ��
	void SellPlayersSwitch( const Json::Value& sold_players );
	//ȡ��������֪ͨ�Է�
	void CancelSale_OtherSide( const Json::Value& sold_players );

	//��Ӧ��Ϣ
public:
	//������������Ϣ
	void OnQuestSoldInfo();
	//��Ӧ��������Ϣ
	void OnSoldInfo( const Json::Value& sold_players );
	//��Ӧȡ������
	void OnCancelSale( const Json::Value& sold_players );

private:
	FuncObj_NormalC&				nor_;

	BC_REG_CLS_DECLARE(GCoordinateC);
};
//////////////////////////////////////////////////////////////////////////
class FuncObj_NormalC : public Connection, public Singleton<FuncObj_NormalC, Singleton_Instance>{
	friend class SessionOperC;
	friend class GCoordinateC;

	//type definition
public:
	//�ؼ�����
	typedef std::vector<DWORD> AddrDatasT;

private:
	FuncObj_NormalC& operator = ( const FuncObj_NormalC& );
	friend void IoRun();

public:
	FuncObj_NormalC();
	~FuncObj_NormalC();

public:
	//��ʼ����Ϸ
	bool InitGame();
	//��ʼ��FuncObj_InterInjectComposite
	bool InitInter( HWND game_main_wnd );
	//�õ�inter inject
	FuncObj_Inject* GetInterInject();
	//�õ�inter GWnd
	FuncObj_GWnd* GetInterGWnd();
	//�õ�glua
	GLuaC& GetGLua();
	LuasScriptEchoC& GetLuaScript();
	//get json echo
	JsonEcho& GetJsonEcho();
	//�õ��ʺ�
	const std::string& GetAccount() const;
	//get dx input press key queue
	DI_PressKeyPtr& GetDI_PressKeyPtr();
	//�õ�session operate
	SessionOperC& GetSessionOper();
	//�õ�coordinate
	GCoordinateC& GetCoordinate();
	//���ùؼ�����
	void SetAddrDatas( const AddrDatasT& addr_datas );
	TimeElapse& GetSetMatchTimer();
	enGameAcType SwitchGameAcType() const;

	//�ɹ�����̨����
public:
	//�ô�����ʾ����ǰ
	void ForegroundTheWindow() const;

	//���ܺ���
public:
	//�ر����д򿪵�UI
	void CloseAllUi();
	//����״̬��(����ѡ��������)���ɷ�����
	void ReadyState_DistributeTask();
	//������Ϸ״̬
	void SetGameState( GType::enGameState game_state );
	//�õ���Ϸ״̬
	GType::enGameState GetGameState();
	static bool IsMatchingState( GType::enGameState game_state );
	bool CanChangeMatchingState( GType::enGameState game_state ) const;
	//���dx����İ���
	void PressDxinputKey( BYTE di_key );

	//for lua
public:
	//���������Ϸ
	void LuaContinueOnClick();
	//close notice dialog
	void LuaCloseNoticeDialog();
	//����ѡ��
	void LuaTrainerSelectScene( std::size_t trainer_idx );
	//����ѡ��
	void LuaTrainerSelectedScene();
	//�ر�ÿ������dialog
	void LuaCloseTaskDlg();
	//�ر���������
	void CloseLevelUpDlg( int milliseconds, int times );
	void OnDisconnect( IoConnectBase* connect );
	//���
	void BanAccount();
	//�Ƿ���Խ�����ͨ�ŵĽ�������
	bool CanNormalTradeProcedure();
	//�Ƿ���Խ��вֿ�ŵĽ�������
	bool CanStoredTradeProcedure();
	void ElapseTimers();

	//�������
public:
	//�Ƿ���뵽�����������
	bool IsEnterContinueOnClick();
	//���������Ϸ
	void ContinueOnClick( IoTimerPtr& timer );
	//��ǰ���㴰���Ƿ��ǹ���dlg
	bool IsNoticeDlgOfMosttop();
	//close notice dialog
	void CloseNoticeDialog( IoTimerPtr& timer );
	//�Ƿ��ǽ���ѡ�񳡾�
	bool IsTrainerSelectScene();
	//����ѡ��
	void TrainerSelectScene( IoTimer* timer, std::size_t trainer_idx );
	//�Ƿ����ѡ������
	bool IsTrainerSelectedScene();
	//����ѡ������
	void TrainerSelectedScene( IoTimer* timer );
	//ÿ������dialog�Ƿ񵯳�
	bool IsTaskDlgShown();
	//�ر�ÿ������dlg
	void CloseTaskDlg( IoTimer* timer );
	//��������
	void TrainerProcedure();

	//������������
public:
	void CreateTrainerProcedure( IoTimer* timer );
	//���������
	void InputCoachName( char c );

	//�޸ķ������,����Ϸ�̵߳���
public:
	//�Ƿ���Ҫ�޸ķ�������
	bool NeedReplaceSendContent();
	//�޸ķ�������
	bool ReplaceSendContent( GType::stHttpSendCall_Content& send_content );

	//��̬����
public:
	//Ψһʵ��
	static FuncObj_NormalC* GetInstance();
	//�õ�inter GWnd
	static FuncObj_GWnd* GetGWnd();

	//������Ϣ
protected:
	bool OnModifyAccount( P_Modify_Account& modify_account );
	//load library
	bool OnTestLoadLib( P_Exec_TestLoadLib& load_lib );
	//unload library
	bool OnTestUnloadLib( P_Exec_TestUnloadLib& unload_lib );
	//call LuaTest
	bool OnCallLuaFunction( P_Exec_CallLuaFunction& call_lua_test );

	//�����¼�
protected:
	
	//˽�г�Ա����
private:
	//����
	void Clear();

protected:
	bool OnUserMsg( P_MsgNT msg_num, void* param, size_t param_size );
	bool PreConnect();
	bool OnConnected( IoConnectBase* connect );

public:
	std::string					account_;
	std::string					password_;
	std::string					game_ser_name_;
	bool						auto_run_script_;
	HMODULE						test_dll_;

private:
	FuncObj_InterInjectComposite*	inject_;			//������ע���߳�
	boost::shared_ptr<JsonEcho>		json_echo_;
	DI_PressKeyPtr					di_press_key_ptr_;
	SessionOperC					session_oper_;
	GCoordinateC					coordinate_;
	boost::shared_ptr<LuasScriptEchoC>					lua_script_;

	//��Ϸ��������
private:
	GType::enGameState				game_state_;
	int								game_ser_idx_;		//��Ϸ������ID

	//��֤���
private:
	//Crypto_RsaInitor	rsa_;
	boost::optional<bool>			login_succeed_;			//��֤��½�Ƿ�ɹ�
	boost::optional<DateTimeLocal>	end_date_time_;			//��֤����ʱ��
	enGameAcType		game_ac_type_;			//�ʺ�����
	Poco::DateTime					time_normal_trade_;		//��ͨ�Ž������̵ļ�ʱ
	TimeElapse						timer_set_match_end_;

public:
	IoTimerPtr						timer_continue_on_click_;
	IoTimerPtr						timer_close_notice_dlg_;
};