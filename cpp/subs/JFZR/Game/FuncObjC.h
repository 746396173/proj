#pragma once
#include "stdafx.h"
#include <socket/client.h>
#include <Protocol/P_NormalMsg.h>
#include "Socket/IoTimer.h"
#include "Facility/GTypes.h"
#include "FuncObjs/FuncObjInter.h"
#include "GLua/GLuaC.h"
#include "Script/JsonCall.h"
#include <dinput.h>
#include "Facility/GClass.h"
#include <Poco/DateTime.h>
#include <Communicate/CG_Defines.h>
#include <Socket/JsonEchoCoorTrans.h>

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
class FuncObj_NormalC;
class SessionOperC : public JsonEchoBase{
public:
	SessionOperC( FuncObj_NormalC& func_obj_normal );

	//������֤
public:
	//�����Ƿ��½�ɹ�
	void SetLoginSucceed( bool succeed );
	//�����û�����ʱ��
	void SetEndDateTime( Poco::UInt32 timestamp_lower, Poco::UInt32 timestamp_upper );
	//���ùؼ�����
	void SetAddrDatas( const Json::Value& addr_datas );

	//Э�����
public:

	//��ȡ����
public:
	//��ü�����Ϣ
	Json::Value GetSkillsInfo();
	//�����Ϸ������Ϣ
	Json::Value GetGameObjsInfo();
	//�����Ʒ��Ϣ
	Json::Value GetAllItems();
	//��÷�����Ϣ
	Json::Value GetRoomInfo();
	//�õ��ҵĳ����б�
	void GetMyOfferList();
	//�õ������ŵĳ�����
	void GetOtherOfferItems();

	//��Ϸ�߼�
public:
	bool CreateRandNameRole();
	bool SelectRole( const std::string& role_name );

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
	//�ô�����ʾ����ǰ
	void ForegroundTheWindow();

	//������
public:

protected:
	virtual bool OnThisMemCall( const stThisCallHelper& helper );

private:
	FuncObj_NormalC&				func_obj_normal_;
};
//////////////////////////////////////////////////////////////////////////
bool MakeTransRoute( P_CoorPacketHeadT& out_route, enGameAcType game_ac_type );
P_CoorPacketHeadT MakeTransRoute( enGameAcType game_ac_type );
class JECoorTransImpl : public JECoorTrans{
public:
	JECoorTransImpl( FuncObj_NormalC& func_obj_normal );

	//��Ӧ�㲥��Ϣ
public:
	bool GainPriProductsInfo();
	bool GainProductsInfo( int ac_type );

	//��Ӧ������Ϣ
public:
	void OnProductsInfo( const Json::Value& json_uuid, const Json::Value& json_v );
	//�õ�������Ա����
	void GetPlayersInfo();
	//�õ�������Ʒ����
	void GetItemsInfo();
	//�õ��ҵĳ����б�
	void GetMyOfferList();
	//�õ������ŵĳ�����
	void GetOtherOfferItems();

	//another
public:

	//test
public:

protected:
	bool OnThisMemCall( const stThisCallHelper& helper );

private:
	FuncObj_NormalC&		nor_;
};
//////////////////////////////////////////////////////////////////////////
class FuncObj_NormalC : public Connection_Aes, public Singleton<FuncObj_NormalC, Singleton_Instance>{
	friend class SessionOperC;
	friend class GCoordinateC;

	//type definition
public:
	//�ؼ�����
	typedef std::vector<DWORD> AddrDatasT;
	class InjectedGWnd : public FuncObj_GWnd{
	public:
		InjectedGWnd( HWND hwnd, FuncObj_Inter* sink );
		LRESULT HandleWndMsg_( UINT message, WPARAM wParam, LPARAM lParam );
		void HandleWndMsg( UINT message, WPARAM wParam, LPARAM lParam );
		void ButtonClick( int x, int y );
		//VK_ESCAPE
		void KeyClick( DWORD virtual_key );
	};

	class InjectGWndComposite : public FuncObj_Inject{
	public:
		InjectGWndComposite( FuncObj* parent, HWND hwnd );
		InjectedGWnd& GetInterGWnd();
		void DeleteSelf();

	private:
		InjectedGWnd			injected_gwnd_;
	};

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
	//����½ʧ�ܴ���
	void BeginCheckLoginFailed();
	//�õ�inter inject
	FuncObj_Inject* GetInterInject();
	//�õ�inter GWnd
	InjectedGWnd* GetInterGWnd();
	//�õ�glua
	GLuaC& GetGLua();
	LuasScriptEchoC_Impl& GetLuaScript();
	//get json echo
	JsonEcho& GetJsonEcho();
	//�õ��ʺ�
	const std::string& GetAccount() const;
	//get dx input press key queue
	DI_PressKeyPtr GetDI_PressKeyPtr();
	//�õ�session operate
	SessionOperC& GetSessionOper();
	//�õ�coordinate
	JECoorTransImpl& GetCoorTrans();
	//���ùؼ�����
	void SetAddrDatas( const AddrDatasT& addr_datas );
	void SetGameState( GType::enGameState game_state );
	bool WaitUntilGameState( GType::enGameState game_state, std::size_t time_out );
	GType::enGameState GetGameState() const;
	
	//�ɹ�����̨����
public:
	

	//���ܺ���
public:
	//�ر����д򿪵�UI
	void CloseAllUi();
	//���dx����İ���
	void PressDxinputKey( BYTE di_key );
	void OnCreatePlayerResult( CMDR_OnCreatePlayer::enResult result );

	//for lua
public:
	void OnDisconnect( IoConnectBase* connect );
	//���
	void BanAccount();

	//�������
public:
	//ѡ��Ƶ��
	bool ChooseChannel();
	void SetChannelId( const std::wstring& channel_id );
	//������ɫ
	boost::optional<bool> CreateRole( const std::wstring& role_name, GType::enJobCategory job );
	bool CreateRandNameRole( GType::enJobCategory job );
	//ѡ���ɫ
	bool SelectRole( const std::wstring& role_name );
	bool SelectRoleA( const std::string& role_name );
	//�Ƿ�ѡ�����ɫ��
	bool IsSelectedRole() const;
	void SetSelectedRole( bool selected_role );
	//�Զ�������ѡ���ɫ
	bool AutoCreateOrSelectRole();
	//���ص���ɫѡ�����
	bool RetChooseRoleScene();
	//��ESPֱ��������Ϸ�˵�
	bool UntilShowGameMenuByPressEsp();
	//button click
	bool ButtonClick( int x, int y );
	bool KeyClick( DWORD virtual_key );

	//another
public:
	
	//�޸ķ������,����Ϸ�̵߳���
public:

	//��̬����
public:
	//Ψһʵ��
	static FuncObj_NormalC* GetInstance();
	//�õ�inter GWnd
	static InjectedGWnd* GetGWnd();

	//test
public:
	void Test();

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
	virtual bool OnModify( P_MsgNT msg_num, void* param, size_t param_size );
	virtual bool OnExec( P_MsgNT msg_num, void* param, size_t param_size );
	virtual bool PreConnect();
	bool OnConnected( IoConnectBase* connect );

private:
	std::string					account_;
	std::string					password_;
	bool						auto_run_script_;
	HMODULE						test_dll_;

private:
	InjectGWndComposite*			inject_;			//������ע���߳�
	GLuaC							glua_;
	JsonEcho						json_echo_;
	DI_PressKeyPtr					di_press_key_ptr_;
	SessionOperC					session_oper_;
	JECoorTransImpl					coor_trans_;
	LuasScriptEchoC_Impl			lua_script_;

	//��Ϸ��������
private:
	int								game_ser_idx_;		//��Ϸ������ID
	GType::enGameState				game_state_;
	std::wstring					channel_id_;
	boost::optional<CMDR_OnCreatePlayer::enResult>		on_create_player_result_;
	bool							selected_role_;		//�Ƿ�ѡ�����ɫ��

	//��֤���
private:
	CryptoStrCompose::SubCryptoT	public_key_;			//��֤��Կ
	CryptoStrCompose::SubCryptoT	private_key_;
	boost::optional<bool>			login_succeed_;			//��֤��½�Ƿ�ɹ�
	boost::optional<Poco::DateTime>	end_date_time_;			//��֤����ʱ��
	enGameAcType					game_ac_type_;			//�ʺ�����
	Poco::DateTime					time_normal_trade_;		//��ͨ�Ž������̵ļ�ʱ
	IoTimerPtr						timer_check_login_valid_;
	IoTimerPtr						timer_check_respond_;	//�����Ƿ�����Ӧ
};