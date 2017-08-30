#pragma once
#include "stdafx.h"
#include <Net/client.h>
#include <Protocol/P_NormalMsg.h>
#include "Net/IoTimer.h"
#include "Facility/GTypes.h"
#include "FuncObjs/FuncObjInter.h"
#include "GLua/GLuaC.h"
#include <Net/Bufcall_Socket.h>
#include "Facility/GClass.h"
#include <Poco/DateTime.h>
#include <Communicate/CG_Defines.h>
#include <Net/BufCallCoorTrans.h>
#include <Common/CmnPriLuaData.h>
#include "Facility/GProtocolR.h"
//////////////////////////////////////////////////////////////////////////
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
	void SetStrDatas( const Json::Value& str_datas );
	//У�����̨
	void CheckConsoleUuid( const std::string& str_uuid, DWORD console_process_id );

	//Э�����
public:

	//��ȡ����
public:
	void SetMultiHit( int multi_hit_rate );

	//��Ϸ�߼�
public:
	bool CreateRandNameRole();
	bool SelectRole( pt_csz role_name );
	void SetRightBtHit( bool is_right_hit );
	void SetOpenVillagePath( bool open_village_path );
	void SetYouHua(bool is_you_hua);

	//����
public:
	//���÷���id
	void SetGameSerIdx( int ser_idx );
	//������Ϸ�ŵ�����
	void SetGameAcType( int game_ac_type );
	//�ӿ���̨����game�Ĺ̶����ַ���
	void StableString( const std::string& stable_str );
	//�ô�����ʾ����ǰ
	void ForegroundTheWindow();
	void GetRunInfo(int cnt);

	//�������
public:
	//�õ��ҵĳ����б�
	void GetMySellList();
	//�õ������ŵĳ�����
	void GetOtherSellInfo();

	//������
public:

private:
	FuncObj_NormalC&				func_obj_normal_;

	BC_REG_CLS_DECLARE(SessionOperC);
};
//////////////////////////////////////////////////////////////////////////
bool MakeTransRoute( P_CoorPacketToT& out_route, enGameAcType game_ac_type, int ser_id );
P_CoorPacketToT MakeTransRoute( enGameAcType game_ac_type, int ser_id );
const P_CoorPacketToT& GetTransRouteAny();
class BufCallCoorTransImpl : public BufCallCoorTrans{
public:
	BufCallCoorTransImpl( FuncObj_NormalC& func_obj_normal );

	//����Ϣ���㲥
public:
	//��öԷ�������Ϣ
	void GainOtherSidePrivateItems();
	//�����������
	void SendAddPrivateItems( const Json::Value& j_value );
	//�������͸��Է���Ӫ��ɾ��
	void SendErasePrivateItems_OtherSide( const Json::Value& j_value );
	//�������͸�������Ӫ��ɾ��
	void SendErasePrivateItems_AllSide( const Json::Value& j_value );

	//��Ӧ��Ϣ
public:
	void OnGainOtherSidePrivateItems();
	//��Ӧ���
	void OnAddPrivateItems( const Json::Value& j_value );
	//��Ӧɾ��
	void OnErasePrivateItems( const Json::Value& j_value );

	//test
public:

private:
	FuncObj_NormalC&		nor_;

	BC_REG_CLS_DECLARE(BufCallCoorTransImpl);
};
//////////////////////////////////////////////////////////////////////////
class FuncObj_NormalC : public Connection, public Singleton<FuncObj_NormalC, Singleton_Instance>{
	friend class SessionOperC;
	friend class BufCallCoorTransImpl;

	//type definition
public:
	//�ؼ�����
	typedef std::vector<DWORD> AddrDatasT;
	typedef std::vector<std::string> StrDatasT;
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
	//�õ�session operate
	SessionOperC& GetSessionOper();
	//�õ�coordinate
	BufCallCoorTransImpl& GetCoorTrans();
	//���ùؼ�����
	void SetAddrDatas( const AddrDatasT& addr_datas );
	void SetStrDatas( const StrDatasT& str_datas );
	void SetGameState( GType::enGameState game_state );
	bool WaitUntilGameState( GType::enGameState game_state, std::size_t time_out );
	GType::enGameState GetGameState() const;
	int GetMultiHitRate() const;
	std::shared_ptr<CmnPriLuaData>& GetHandleAtHitting();
	std::shared_ptr<CmnPriLuaData>& GetHandleAfterEnteredFb();
	std::shared_ptr<CmnPriLuaData>& GetHandlersAtScriptStoped();
	void SetRolesList( const std::shared_ptr<CMDR_PlayerList>& player_list );
	const std::shared_ptr<CMDR_PlayerList>& GetRolesList() const;
	void ClrRolesList();
	void SetCreateRoleRes( const std::shared_ptr<CMDR_OnCreatePlayer>& on_create_role );
	enGameAcType SwitchGameAcType() const;
	void AfterRunScript();

	//�ɹ�����̨����
public:
	
	//���ܺ���
public:
	//���������
	void LeftButtonClick( int pos_x, int pos_y );
	void DxPressKey( DWORD virtual_key, int delay_time );
	void DxKeyUpDown( DWORD virtual_key, bool is_down );
	void DxPressKeyW();
	void DxPressKeyS();
	void DxPressKeyA();
	void DxPressKeyD();
	void DxPressKeyZ();
	void DxPressKeyQ();
	void DxPressKeySpace();
	void DxPressKeyEsc();
	void DxPressKeyGrave();

	//for lua
public:
	void OnDisconnect(IoConnectBase* connect) override;
	//���
	void BanAccount();

	//�������
public:
	//ѡ��ָ�����ֵĽ�ɫ
	bool SelectRoleByName( const std::string& role_name );
	//ѡ��ָ���Ľ�ɫ
	bool SelectRoleByIdx( int role_idx );
	//������ɫ
	bool AutoCreateRole();
	bool CreateTheRole( const std::string& role_name );
	//����ѡ���ɫ
	bool RetSelectRole();
	bool AutoCreateOrSelectRole();
	//ɾ����ɫ
	bool DeleteRole();

	//����
public:
	//ѡ���ɫ
	bool SendChooseRole( DWORD role_id, int role_idx );
	//ѡ��Ƶ��
	bool SendChooseLine( DWORD line_id );
	//������ɫ
	bool SendCreateRole( const std::string& role_name );
	//ɾ����ɫ
	bool SendDeleteRole( DWORD role_id );

	//another
public:
	void DoInitByGameState( GType::enGameState old_state, GType::enGameState new_state );
	//���нű���֪ͨ����̨
	void DoInitAfterGameState( GType::enGameState new_state, bool force_succeed_notify );
	//������Ϸ��ֻ��ʼ��һ��
	void InitOnceAfterInGame();
	//������Ϸ��Ҫִ��
	void ExecAfterInGame();
	//ÿ�ι�ͼ��
	void ExecAfterCrossMap();
	//����ʾ�Ĺر�����
	static void Disconnect_Prompt( const std::string& prompt_str );
	
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
	void Disconnect() override;

protected:
	bool OnUserMsg(P_MsgNT msg_num, void* param, size_t param_size) override;
	virtual bool PreConnect() override;
	bool OnConnected(IoConnectBase* connect) override;
	inline int DoSomeError(){
		assert(false);
		SetIoTimer(1000 * 3, [this]( IoTimer* ){
			/*static const std::string the_error_lua_str = "GPlayer_Me = {} \n RetBoolDef = {} \n LoadScriptFile = {}";
			GetGLua().DoBuffer(the_error_lua_str.c_str(), the_error_lua_str.size(), "file_main");*/
			lua_script_.is_some_err_ = true;
		});
		return 1;
	}

public:
	std::string					account_;
	std::string					password_;
	std::string					game_ser_name_;
	bool						auto_run_script_;
	HMODULE						test_dll_;

private:
	InjectGWndComposite*			inject_;			//������ע���߳�
	GLuaC							glua_;
	JsonEcho						json_echo_;
	SessionOperC					session_oper_;
	BufCallCoorTransImpl					coor_trans_;
	LuasScriptEchoC_Impl			lua_script_;
	std::shared_ptr<CmnPriLuaData>	handle_at_hitting_;
	std::shared_ptr<CmnPriLuaData>	handler_after_entered_fb_;
	std::shared_ptr<CmnPriLuaData>	handlers_on_script_stoped_;

	//��Ϸ��������
public:
	int								game_ser_idx_;		//��Ϸ������ID
	GType::enGameState				game_state_;
	std::shared_ptr<CMDR_PlayerList>		players_list_;
	std::shared_ptr<CMDR_OnCreatePlayer>	on_create_player_;
	std::shared_ptr<CMDR_PlayerLine>		on_ser_line_;
	std::shared_ptr<CMDR_Hook_CreateRole>	on_hook_create_role_;

public:
	std::shared_ptr<CMDR_PlayerList>		cur_players_list_;
	int										cur_delete_role_idx_;
	bool									change_ac_at_delete_one_role_;
	std::shared_ptr<CMDR_OnDeleteRole>		on_delete_role_;
	int										ser_line_;		//��������·

	//��֤���
private:
	boost::optional<bool>			login_succeed_;			//��֤��½�Ƿ�ɹ�
	boost::optional<DateTimeLocal>	end_date_time_;			//��֤����ʱ��
	enGameAcType					game_ac_type_;			//�ʺ�����
	//IoTimerPtr						timer_check_login_valid_;
	IoTimerPtr						timer_check_respond_;	//�����Ƿ�����Ӧ

private:
	int								multi_hit_rate_;

public:
	std::string						console_uuid_;
	DWORD							console_process_id_;
	bool							is_you_hua_;
};