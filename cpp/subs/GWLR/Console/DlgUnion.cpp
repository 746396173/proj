// DlgUnion.cpp : implementation file
//

#include "stdafx.h"
#include "Console.h"
#include "DlgUnion.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "GLuaS.h"
#include "Common/UsefulFunc.h"
#include <boost/filesystem.hpp>
#include "protect/Protect.h"
#include "CheckLoginC.h"
#include "Console.h"
#include "AntiCrack.h"
#include "ServerIpInfo.h"

DlgAddAccountHelper::DlgAddAccountHelper(CWnd* pParent /*=NULL*/)
	: DlgUseful(DlgAddAccountHelper::IDD, pParent)
{
	 
}

DlgAddAccountHelper::~DlgAddAccountHelper()
{
}

void DlgAddAccountHelper::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ADD_THE_ACCOUNT, edit_account_);
	DDX_Control(pDX, IDC_EDIT_ADD_THE_PASSWORD, edit_password_);
	DDX_Control(pDX, IDC_COMBO_ADD_AC_SELECT_SERVICE, combo_select_service_);
}

BOOL DlgAddAccountHelper::OnInitDialog()
{
	if ( !__super::OnInitDialog() )
	{
		return FALSE;
	}
	auto service_mgr = GameServiceMgr::GetInstance();
	if ( !service_mgr )
	{
		assert(false);
		return FALSE;
	}

	const auto& services_info = service_mgr->GetServicesInfo();
	for ( const auto& it : services_info )
	{
		combo_select_service_.AddString(CA2CT(it.first.c_str()));
	}
	combo_select_service_.SetCurSel(0);

	edit_account_.LimitText(kAccountMaxLen);
	edit_password_.LimitText(kPasswordMaxLen);
	return TRUE;
}

void DlgAddAccountHelper::OnOK()
{
	TCHAR szbuffer[MAX_PATH];
	ZeroMemory(szbuffer, sizeof(szbuffer));
	auto first_line = edit_account_.GetFirstVisibleLine();
	if ( first_line >= 0 )
	{
		edit_account_.GetLine(first_line, szbuffer, edit_account_.LineLength(first_line));
		str_account_ = szbuffer;
		ZeroMemory(szbuffer, sizeof(szbuffer));
	}

	first_line = edit_password_.GetFirstVisibleLine();
	if ( first_line >= 0 )
	{
		edit_password_.GetLine(first_line, szbuffer, edit_password_.LineLength(first_line));
		str_password_ = szbuffer;
	}

	/*__super::OnOK();
	return;*/
	//////////////////////////////////////////////////////////////////////////
	if ( str_account_.GetLength() < kAccountMinLen )
		return;

	if ( str_password_.GetLength() < kPasswordMinLen )
		return;

	auto ctrl_list = PageAccount_List::GetInstance();
	if ( !ctrl_list )
		return;

	assert(combo_select_service_.GetCurSel() != CB_ERR);
	CString cstr_ser_name;
	combo_select_service_.GetWindowText(cstr_ser_name);
	ctrl_list->Insert_Item(str_account_, str_password_, cstr_ser_name);
}

const CString& DlgAddAccountHelper::GetAccount() const
{
	return str_account_;
}

const CString& DlgAddAccountHelper::GetPassword() const
{
	return str_password_;
}

DlgLoginBase::DlgLoginBase( UINT id ) : DlgUseful(id, AfxGetMainWnd())
{
	is_doing_ = false;
}

void DlgLoginBase::DoDataExchange( CDataExchange* pDX )
{
	VMP_BEGIN_EX;
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LOGIN_ACCOUNT, str_account_);
	DDX_Text(pDX, IDC_EDIT_LOGIN_PASSWORD, str_password_);

	DDX_Control(pDX, IDC_EDIT_LOGIN_ACCOUNT, edit_account_);
	DDX_Control(pDX, IDC_EDIT_LOGIN_PASSWORD, edit_password_);
	VMP_END;
}

BOOL DlgLoginBase::OnInitDialog()
{
	if (str_account_.IsEmpty())
	{
		const auto& singleton_cfg  = stSingletonCfg::GetMe();
		str_account_ = singleton_cfg.authen_account_;
		str_password_ = singleton_cfg.authen_password_;
	}
	
	if ( !__super::OnInitDialog() )
		return FALSE;
	edit_password_.SetPasswordChar(_T('*'));
	edit_account_.LimitText(kUserNameMaxLen);
	edit_password_.LimitText(kUserPwdMaxLen);
	return TRUE;
}
BEGIN_MESSAGE_MAP(DlgLoginBase, CDialog)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BT_REMOVE_BIND, &DlgLoginBase::OnBnClickedBtRemoveBind)
END_MESSAGE_MAP()


void DlgLoginBase::OnOK()
{
	auto bt_ok = GetDlgItem(IDOK);
	if (bt_ok)
		bt_ok->EnableWindow(FALSE);
	VMP_BEGIN;
	UpdateData();
	if ( str_account_.GetLength() < kUserNameMinLen )
		return;

	if ( str_password_.GetLength() < kUserPwdMinLen )
		return;
	auto tab_option = CTabOption::GetInstance();
	if ( !tab_option )
	{
		assert(false);
		return;
	}
	if (tab_option->IsLoginSucceed())
		return;
	VMP_END;

	GetDlgItem(IDOK)->EnableWindow(FALSE);

	std::string account = CT2CA(str_account_);
	std::string password = CT2CA(str_password_);

	GetIoService().post([=](){
		auto check_login = CheckLoginC::GetSelfPtr();
		if ( !check_login )
			return;
		auto& user_oper = check_login->GetUserOper();
		user_oper.Login(true, account.c_str(), password.c_str(), kConsoleMinVer);
		if ( !IsWindow(m_hWnd) )
			return;
		auto bt_ok = GetDlgItem(IDOK);
		if (bt_ok)
			bt_ok->EnableWindow(TRUE);
	});
}

void DlgPay::OnOK()
{
	if (is_doing_)
		return;
	UpdateData();

	if ( str_account_ != str_confirm_account_ )
		return;
	
	//GetDlgItem(IDOK)->EnableWindow(FALSE);
	//SetTimer(kEnableTimer, 3000, nullptr);

	if ( str_account_.GetLength() < kUserNameMinLen )
		return;
	/*if ( str_card_serial_.GetLength() != kCardIdLen )
		return;*/
	const auto kCardIdSize = str_card_serial_.GetLength();
	if ( kCardIdSize != kCardIdLen && kCardIdSize != kCardIdLenEx )
		return;

	/*if ( str_card_password_.GetLength() != kCardPwdLen )
		return;*/
	if ( str_card_password_.GetLength() != kCardPwdLen && str_card_password_.GetLength() != kCardPwdLenEx )
		return;

	SetDoing(true);
	
	std::string account = CT2CA(str_account_);
	std::string card_serial = CT2CA(str_card_serial_);
	std::string card_password = CT2CA(str_card_password_);

	GetIoService().post([=](){
		auto check_login = CheckLoginC::GetSelfPtr();
		if ( !check_login )
			return;
		auto& user_oper = check_login->GetUserOper();
		user_oper.UserPay(account.c_str(), card_serial.c_str(), card_password.c_str());

		auto dlg_pay = DlgPay::GetInstance();
		if (dlg_pay)
			dlg_pay->SetDoing(false);
	});
}

BEGIN_MESSAGE_MAP(DlgPay, DlgUseful)
	ON_WM_TIMER()
END_MESSAGE_MAP()

DlgPay::DlgPay() : DlgUseful(IDD_DLG_PAY, AfxGetMainWnd())
{
	is_doing_ = false;
}

void DlgPay::DoDataExchange( CDataExchange* pDX )
{
	__super::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PAY_CARD_SERIAL, str_card_serial_);
	DDX_Text(pDX, IDC_EDIT_PAY_CARD_PASSWORD, str_card_password_);
	DDX_Text(pDX, IDC_EDIT_PAY_THE_ACCOUNT, str_account_);
	DDX_Text(pDX, IDC_EDIT_PAY_CONFIRM_ACCOUNT, str_confirm_account_);

	DDX_Control(pDX, IDC_EDIT_PAY_CARD_SERIAL, edit_card_id_);
	DDX_Control(pDX, IDC_EDIT_PAY_CARD_PASSWORD, edit_card_password_);
	DDX_Control(pDX, IDC_EDIT_PAY_THE_ACCOUNT, edit_account_);
	DDX_Control(pDX, IDC_EDIT_PAY_CONFIRM_ACCOUNT, edit_confirm_account_);
}

BOOL DlgPay::OnInitDialog()
{
	if ( !__super::OnInitDialog() )
		return FALSE;
	//edit_card_password_.SetPasswordChar(_T('*'));
	edit_account_.LimitText(kUserNameMaxLen);
	edit_confirm_account_.LimitText(kUserNameMaxLen);
	edit_card_id_.LimitText(kCardIdLen);
	edit_card_password_.LimitText(kCardPwdLen);
	return TRUE;
}

void DlgPay::OnTimer( UINT_PTR nIDEvent )
{
	if ( kEnableTimer == nIDEvent )
	{
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		KillTimer(nIDEvent);
		return;
	}
	__super::OnTimer(nIDEvent);
}

void DlgPay::SetDoing( bool is_doing )
{
	if ( !::IsWindow(m_hWnd) )
		return;
	auto bt_ok = GetDlgItem(IDOK);
	if (bt_ok)
		bt_ok->EnableWindow(!is_doing);
	is_doing_ = is_doing;
}

void DlgReg::OnOK()
{
	if (is_doing_)
		return;
	UpdateData();

	if ( str_account_.GetLength() < kUserNameMinLen )
		return;
	if ( str_password_.GetLength() < kUserPwdMinLen )
		return;
	if ( str_password_ != str_confirm_password_ )
		return;
	if ( str_reg_key_.GetLength() != kRegKeyIdLen && str_reg_key_.GetLength() != kRegKeyIdLenEx )
		return;
	const auto kQQSize = str_qq_.GetLength();
	if ( kQQSize > kQQMaxLen || kQQSize < kQQMinLen )
		return;

	//GetDlgItem(IDOK)->EnableWindow(FALSE);
	//SetTimer(kEnableTimer, 10000, nullptr);

	std::string account = CT2CA(str_account_);
	std::string password = CT2CA(str_password_);
	std::string qq = CT2CA(str_qq_);
	std::string reg_key_id = CT2CA(str_reg_key_);

	SetDoing(true);

	GetIoService().post([=](){
		auto check_login = CheckLoginC::GetSelfPtr();
		if ( !check_login )
			return;
		auto& user_oper = check_login->GetUserOper();
		user_oper.RegUser(account.c_str(), password.c_str(), qq.c_str(), reg_key_id.c_str());
		auto dlg = DlgReg::GetInstance();
		if (dlg)
			dlg->SetDoing(false);
	});
}

void DlgReg::DoDataExchange( CDataExchange* pDX )
{
	__super::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_REG_ACCOUNT, str_account_);
	DDX_Text(pDX, IDC_EDIT_REG_PASSWORD, str_password_);
	DDX_Text(pDX, IDC_EDIT_REG_CONFIRM_PASSWORD, str_confirm_password_);
	DDX_Text(pDX, IDC_EDIT_REG_QQ, str_qq_);
	DDX_Text(pDX, IDC_EDIT_REG_KEY, str_reg_key_);

	DDX_Control(pDX, IDC_EDIT_REG_ACCOUNT, edit_account_);
	DDX_Control(pDX, IDC_EDIT_REG_PASSWORD, edit_password_);
	DDX_Control(pDX, IDC_EDIT_REG_CONFIRM_PASSWORD, edit_confirm_password_);
	DDX_Control(pDX, IDC_EDIT_REG_QQ, edit_qq_);
	DDX_Control(pDX, IDC_EDIT_REG_KEY, edit_reg_key_);
}

BEGIN_MESSAGE_MAP(DlgReg, DlgUseful)
	ON_WM_TIMER()
END_MESSAGE_MAP()

DlgReg::DlgReg() : DlgUseful(IDD_DLG_REG, AfxGetMainWnd())
{
	is_doing_ = false;
}

BOOL DlgReg::OnInitDialog()
{
	if ( !__super::OnInitDialog() )
		return FALSE;

	edit_password_.SetPasswordChar(_T('*'));
	edit_confirm_password_.SetPasswordChar(_T('*'));

	edit_account_.LimitText(kUserNameMaxLen);
	edit_password_.LimitText(kUserPwdMaxLen);
	edit_confirm_password_.LimitText(kUserPwdMaxLen);
	return TRUE;
}

void DlgReg::OnTimer( UINT_PTR nIDEvent )
{
	if ( kEnableTimer == nIDEvent )
	{
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		KillTimer(kEnableTimer);
		return;
	}
	__super::OnTimer(nIDEvent);
}

void DlgReg::SetDoing( bool is_doing )
{
	if ( !::IsWindow(m_hWnd) )
		return;
	auto bt_ok = GetDlgItem(IDOK);
	if (bt_ok)
		bt_ok->EnableWindow(!is_doing);
	is_doing_ = is_doing;
}

void DlgLoginBase::OnBnClickedBtRemoveBind()
{
	UpdateData();

	if ( str_account_.GetLength() < kUserNameMinLen )
		return;

	if ( str_password_.GetLength() < kUserPwdMinLen )
		return;

	auto bt_remove_bind = GetDlgItem(IDC_BT_REMOVE_BIND);
	if (bt_remove_bind)
		bt_remove_bind->EnableWindow(FALSE);

	std::string account = CT2CA(str_account_);
	std::string password = CT2CA(str_password_);

	GetIoService().post([=](){
		VMP_BEGIN_EX;
		auto check_login = CheckLoginC::GetSelfPtr();
		if ( !check_login )
			return;
		auto& user_oper = check_login->GetUserOper();
		user_oper.RemoveBind(account.c_str(), password.c_str());
		if ( !IsWindow(m_hWnd) )
			return;
		auto bt_remove_bind = GetDlgItem(IDC_BT_REMOVE_BIND);
		if (bt_remove_bind)
			bt_remove_bind->EnableWindow(FALSE);
		VMP_END;
	});
}

void DlgLoginBase::OnTimer( UINT_PTR nIDEvent )
{
	if ( kEnableTimer == nIDEvent )
	{
		KillTimer(kEnableTimer);
		return;
	}
	__super::OnTimer(nIDEvent);
}

void DlgLoginBase::OnClose()
{
	auto& singleton_cfg = stSingletonCfg::GetMe();
	singleton_cfg.authen_account_ = str_account_;
	singleton_cfg.authen_password_ = str_password_;

	__super::OnClose();
}

void DlgLoginBase::SetDoing( bool is_doing )
{
	return;
	is_doing_ = is_doing;
}

const CString& DlgLoginBase::GetAc() const
{
	return str_account_;
}

void DlgLoginBase::OnLoginSucceed()
{
	VMP_BEGIN_EX;
	auto& singleton_cfg = stSingletonCfg::GetMe();
	singleton_cfg.authen_account_ = str_account_;
	singleton_cfg.authen_password_ = str_password_;
	singleton_cfg.Save();
	VMP_END;
}

const CString& DlgLoginBase::GetPwd() const
{
	return str_password_;
}

DlgSelectScript::DlgSelectScript( CWnd* pParent )
	: CDialog(DlgSelectScript::IDD, pParent)
{
}

DlgSelectScript::~DlgSelectScript()
{
}

void DlgSelectScript::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SELECT_SCRIPT, combo_scripts_);
}

BOOL DlgSelectScript::OnInitDialog()
{
	if ( !__super::OnInitDialog() )
		return FALSE;

	using namespace boost::filesystem;
	boost::filesystem::path file_path(GetScriptDirectory());

	try
	{
		if (exists(file_path))    // does p actually exist?
		{
			if (is_directory(file_path))      // is p a directory?
			{
				directory_iterator it(file_path), it_end;

				for ( ; it != it_end; ++it )
				{
					const auto& file_path = it->path();
					
					if ( 0 == _stricmp(file_path.extension().string().c_str(), ".lua") )
					{
						const auto& file_name = file_path.filename().string();
						/*if ( file_name != "Scri_Commands.lua" )
						combo_scripts_.AddString(CA2CT(file_name.c_str()));*/
						combo_scripts_.AddString(CA2CT(file_name.c_str()));
					}
				}

				combo_scripts_.SelectString(0, script_name_);
			}
			else
			{
				LOG_ENTER_FUNC;
				LOG_O(Log_debug) << file_path << " exists, but is not a directory";
			}
		}
		else
		{
			LOG_ENTER_FUNC;
			LOG_O(Log_debug) << file_path << " does not exist";
		}
	}
	DO_CATCH_THE_EXCEPTION( const filesystem_error& e, {
		LOG_ENTER_FUNC;
		LOG_O(Log_debug) << e.what();
	})
	return TRUE;
}

void DlgSelectScript::OnOK()
{
	auto item = combo_scripts_.GetCurSel();
	if ( item != CB_ERR )
	{
		combo_scripts_.GetWindowText(script_name_);
	}
	__super::OnOK();
}

const CString& DlgSelectScript::GetSelectedScriptName() const
{
	return script_name_;
}

DlgUseful::DlgUseful( LPCTSTR lpszTemplateName, CWnd* pParentWnd /*= nullptr */ ) : CDialog(lpszTemplateName, pParentWnd)
{

}

DlgUseful::DlgUseful( UINT nIDTemplate, CWnd* pParentWnd /*= nullptr */ ) : CDialog(nIDTemplate, pParentWnd)
{

}

bool DlgUseful::GetStringFromEdit( CEdit& edit_obj, std::string& str_out )
{
	TCHAR buffer[MAX_PATH];
	ZeroMemory(buffer, sizeof(buffer));
	auto idx = edit_obj.GetFirstVisibleLine();
	if ( idx >= 0 )
	{
		edit_obj.GetLine(idx, buffer, edit_obj.LineLength(idx));
		str_out = CT2CA(buffer);
		return true;
	}

	return false;
}

void DlgUseful::SetWndText( const char* wnd_text )
{
	VMP_BEGIN;
	if ( !wnd_text )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_debug) << "���ڵ�����Ϊ��";
		return;
	}
	if ( !m_hWnd || !IsWindow(m_hWnd) )
	{
		return;
	}

	if (wnd_text_old_.IsEmpty())
	{
		GetWindowText(wnd_text_old_);
	}
	CString cstr_wnd_text = wnd_text_old_;
	cstr_wnd_text += _T("--->|*");
	cstr_wnd_text += CA2CT(wnd_text);
	cstr_wnd_text += _T("*|");
	SetWindowText(cstr_wnd_text);
	VMP_END;
}

void DlgUseful::SetWndTxt( const std::string& wnd_text )
{
	SetWndText(wnd_text.c_str());
}

SelectGameService::SelectGameService( CWnd* parent ) : CDialog(IDD_DLG_SELECT_SERVICE, parent)
{
}

void SelectGameService::DoDataExchange( CDataExchange* pDX )
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_SELECT_SERVICE, combo_select_service_);
}

BOOL SelectGameService::OnInitDialog()
{
	if ( !__super::OnInitDialog() )
		return FALSE;
	auto service_mgr = GameServiceMgr::GetInstance();
	if ( !service_mgr )
	{
		assert(false);
		return FALSE;
	}

	const auto& services_info = service_mgr->GetServicesInfo();
	for ( const auto& it : services_info )
	{
		combo_select_service_.AddString(CA2CT(it.first.c_str()));
	}
	
	combo_select_service_.SetCurSel(0);
	return TRUE;
}

void SelectGameService::OnOK()
{
	assert(combo_select_service_.GetCurSel() != CB_ERR);
	combo_select_service_.GetWindowText(selected_service_);
	__super::OnOK();
}

const CString& SelectGameService::GetSelectedService() const
{
	return selected_service_;
}

AutoRunScript_LoginSucceed::AutoRunScript_LoginSucceed( CWnd* parent ) : CDialog(IDD_DLG_AUTO_RUN_SCRIPT, parent)
{
	is_auto_run_ = false;
}

bool AutoRunScript_LoginSucceed::IsAutoRunScript() const
{
	return is_auto_run_;
}

void AutoRunScript_LoginSucceed::DoDataExchange( CDataExchange* pDX )
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_AUTO_RUN_SCRIPT, combo_auto_run_);
}

BOOL AutoRunScript_LoginSucceed::OnInitDialog()
{
	if ( !__super::OnInitDialog() )
		return FALSE;
	combo_auto_run_.InsertString(0, _T("��"));
	combo_auto_run_.InsertString(1, _T("��"));
	combo_auto_run_.SetCurSel(0);
	return TRUE;
}

void AutoRunScript_LoginSucceed::OnOK()
{
	is_auto_run_ = 0 == combo_auto_run_.GetCurSel();
	__super::OnOK();
}

CrackCaptcha_SetAccountDlg::CrackCaptcha_SetAccountDlg( CWnd* parent ) : CDialog(IDD_DLG_CRACK_CAPTCHA_SET_ACCOUNT, parent)
{

}

const CString& CrackCaptcha_SetAccountDlg::GetAccount() const
{
	return str_account_;
}

const CString& CrackCaptcha_SetAccountDlg::GetPassword() const
{
	return str_password_;
}

void CrackCaptcha_SetAccountDlg::DoDataExchange( CDataExchange* pDX )
{
	__super::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_CRACK_CATPCHA_ACCOUNT, str_account_);
	DDX_Text(pDX, IDC_EDIT_CRACK_CAPTCHA_PASSWORD, str_password_);
}

BOOL CrackCaptcha_SetAccountDlg::OnInitDialog()
{
	const auto& singleton_cfg = stSingletonCfg::GetMe();
	str_account_ = CA2CT(singleton_cfg.crack_captcha_mode_.account_.c_str());
	str_password_ = CA2CT(singleton_cfg.crack_captcha_mode_.password_.c_str());

	if ( !__super::OnInitDialog() )
		return FALSE;

	return TRUE;
}

void CrackCaptcha_SetAccountDlg::OnOK()
{
	UpdateData();
	auto& singleton_cfg = stSingletonCfg::GetMe();
	singleton_cfg.crack_captcha_mode_.account_ = CT2CA(str_account_);
	singleton_cfg.crack_captcha_mode_.password_ = CT2CA(str_password_);
	__super::OnOK();
}

CrackCapthcha_SetServiceInfo::CrackCapthcha_SetServiceInfo( CWnd* parent ) : CDialog(IDD_DLG_CRACK_CATPCHA_SET_SERVICE_INFO, parent)
{
	port_ = 0;
	ip_address_ = 0;
}

void CrackCapthcha_SetServiceInfo::DoDataExchange( CDataExchange* pDX )
{
	__super::DoDataExchange(pDX);

	DDX_IPAddress(pDX, IDC_IPADDR_CRACK_CAPTCHA, ip_address_);
	auto port_tmp = (UINT)port_;
	DDX_Text(pDX, IDC_EDIT_CRACK_CATPCHA_REMOTE_PORT, port_tmp);
	port_ = port_tmp;
}

void CrackCapthcha_SetServiceInfo::OnOK()
{
	UpdateData();
	__super::OnOK();
}

void CrackCapthcha_SetServiceInfo::SetIpInfo( const char* ip_str, WORD port )
{
	if ( !ip_str )
	{
		assert(false);
		return;
	}
	auto ip_addr = boost::asio::ip::address::from_string(ip_str);
	if (ip_addr.is_v4())
		SetIpInfo(ip_addr.to_v4().to_ulong(), port);
	else
	{
		assert(false);
		(void*)0;
	}
}

DWORD CrackCapthcha_SetServiceInfo::GetIpAddr() const
{
	return ip_address_;
}

void CrackCapthcha_SetServiceInfo::SetIpInfo( DWORD ip, WORD port )
{
	ip_address_ = ip;
	port_ = port;
}

std::string CrackCapthcha_SetServiceInfo::GetIpString() const
{
	boost::asio::ip::address_v4 addr(ip_address_);
	return addr.to_string();
}

WORD CrackCapthcha_SetServiceInfo::GetPort() const
{
	return port_;
}

DlgCheckServerInfo::DlgCheckServerInfo() : CDialog(IDD_DLG_CHECK_SERVER_INFO, nullptr)
{
	ip_address_ = 0;
	is_connecting_ = false;

	SetIpInfo(kSelfIpStr);

	auto fn = [](){
		WaitUntil([]()->bool{
			return !DlgCheckServerInfo::GetInstance();		
		});
	};
	GetIoService().post(fn);
}

void DlgCheckServerInfo::DoDataExchange( CDataExchange* pDX )
{
	__super::DoDataExchange(pDX);

	DDX_IPAddress(pDX, IDC_IPADDRESS_CHECK_SERVER, ip_address_);
}

void DlgCheckServerInfo::SetIpInfo( const char* ip_str )
{
	if ( !ip_str )
	{
		assert(false);
		return;
	}
	auto ip_addr = boost::asio::ip::address::from_string(ip_str);
	if (ip_addr.is_v4())
		SetIpInfo(ip_addr.to_v4().to_ulong());
	else
	{
		assert(false);
		(void*)0;
	}
}

void DlgCheckServerInfo::SetIpInfo( DWORD ip )
{
	ip_address_ = ip;
}

std::string DlgCheckServerInfo::GetIpString() const
{
	boost::asio::ip::address_v4 addr(ip_address_);
	return addr.to_string();
}

void DlgCheckServerInfo::OnOK()
{
	if (is_connecting_)
		return;
	assert(false);

	SetConnecting(true);

	UpdateData();

	GetIoService().post([this](){
		auto check_login = CheckLoginC::GetSelfPtr();
		if (check_login)
		{
			check_login->Disconnect();
		}
		assert(CheckLoginC::GetSelfPtr());
	});	
}

void DlgCheckServerInfo::SetConnecting( bool connecting )
{
	is_connecting_ = connecting;
	auto bt_ok = GetDlgItem(IDOK);
	if (bt_ok)
	{
		bt_ok->EnableWindow(!connecting);
	}
}

void DlgCheckServerInfo::ConnectSucceed()
{
	EndDialog(IDOK);
}

DlgSetMaxLogin::DlgSetMaxLogin( CWnd* parent ) : CDialog(IDD_DLG_SET_MAX_LOGIN, parent)
{
	const auto& single_cfg = stSingletonCfg::GetMe();
	max_login_ = single_cfg.max_login_;
}

void DlgSetMaxLogin::DoDataExchange( CDataExchange* pDX )
{
	__super::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_SET_MAX_LOGIN, max_login_);
}

void DlgSetMaxLogin::OnOK()
{
	UpdateData();
	if (max_login_ > 2)
		max_login_ = 2;
	stSingletonCfg::GetMe().max_login_ = max_login_;

	UpdateData(TRUE);
	__super::OnOK();
}

// DlgMgrAc dialog
DlgMgrAc::DlgMgrAc(CWnd* pParent /*=NULL*/)
	: CDialog(DlgMgrAc::IDD, pParent)
{
	use_old_format_ = 0;
}

DlgMgrAc::~DlgMgrAc()
{
}

void DlgMgrAc::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_USE_OLD_FORMAT, use_old_format_);
}

BEGIN_MESSAGE_MAP(DlgMgrAc, CDialog)
	ON_BN_CLICKED(IDC_BT_IMPORT_AC, &DlgMgrAc::OnBnClickedBtImportAc)
	ON_BN_CLICKED(IDC_BT_EXPORT_AC, &DlgMgrAc::OnBnClickedBtExportAc)
END_MESSAGE_MAP()

void DlgMgrAc::OnBnClickedBtImportAc()
{
	CFileDialog file_dlg(TRUE, _T(".ini"), nullptr, OFN_HIDEREADONLY, 
		_T("*.ini") _T("|") _T("*.ini") _T("||"));
	if ( IDOK != file_dlg.DoModal() )
		return;
	UpdateData();

	AcIniCfgMgr cfg_mgr_old;
	AcIniCfgMgr_New cfg_mgr_new;
	AcIniCfgMgr* cfg_mgr_ptr;
	if (use_old_format_)
		cfg_mgr_ptr = &cfg_mgr_old;
	else
		cfg_mgr_ptr = &cfg_mgr_new;
	cfg_mgr_ptr->Load(CPath(file_dlg.GetPathName()));

	const auto& cfg_cont = cfg_mgr_ptr->GetCont();
	if (cfg_cont.empty())
		return;

	auto ctrl_list = PageAccount_List::GetInstance();
	if ( !ctrl_list )
		return;

	auto service_mgr = GameServiceMgr::GetInstance();
	if ( !service_mgr )
	{
		assert(false);
		return;
	}

	const auto& services_info = service_mgr->GetServicesInfo();
	
	ctrl_list->DeleteAllItems();

	std::string str_service;
	for ( auto it = cfg_cont.begin(); it != cfg_cont.end(); ++it )
	{
		str_service = CT2CA(it->service_name_);
		if ( std::find_if(services_info.begin(), services_info.end(), [&str_service]( const GameServiceMgr::ServiceInfoT& service_info ){
			return service_info.first == str_service;
		}) == services_info.end() )
			continue;
	
		ctrl_list->Insert_Item(it->ac_, it->pwd_, it->service_name_);
	}
}


void DlgMgrAc::OnBnClickedBtExportAc()
{
	CPath folder = GetBrowseFolder(this->m_hWnd);
	if ( !folder.FileExists() )
		return;
	auto ctrl_list = PageAccount_List::GetInstance();
	if ( !ctrl_list )
		return;

	AcIniCfgMgr cfg_mgr_old;
	AcIniCfgMgr_New cfg_mgr_new;
	AcIniCfgMgr* cfg_mgr_ptr;
	if (use_old_format_)
		cfg_mgr_ptr = &cfg_mgr_old;
	else
		cfg_mgr_ptr = &cfg_mgr_new;
	if ( !ctrl_list->DoItem([cfg_mgr_ptr]( int item, const ListNormal& l_ctrl ){
		cfg_mgr_ptr->Add(l_ctrl.GetItemText(item, kSubitemAccount), l_ctrl.GetItemText(item, kSubitemPassword),
			l_ctrl.GetItemText(item, kSubitemService));
		return true;
	}) )
		return;

	VERIFY(cfg_mgr_ptr->Save(CPath(folder + _T("��Ϸ�ʺ�����.ini"))));
}

DlgSelectGameAcType::DlgSelectGameAcType( CWnd* parent ) : CDialog(IDD_DLG_SELECT_GAME_AC_TYPE, parent)
{
	game_ac_type_ = kGAT_Normal;
}

void DlgSelectGameAcType::DoDataExchange( CDataExchange* pDX )
{
	__super::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_COMBO_SELECT_GAME_AC_TYPE, combo_ac_type_);
}

void DlgSelectGameAcType::OnOK()
{
	game_ac_type_ = (enGameAcType)combo_ac_type_.GetCurSel();
	__super::OnOK();
}

BOOL DlgSelectGameAcType::OnInitDialog()
{
	if ( !__super::OnInitDialog() )
		return FALSE;

	combo_ac_type_.InsertString(kGAT_Normal, _T("��ͨ��"));
	combo_ac_type_.InsertString(kGAT_Stored, _T("�ֿ��"));

	combo_ac_type_.SetCurSel(kGAT_Normal);
	return TRUE;
}

enGameAcType DlgSelectGameAcType::GetGameAcType() const
{
	return game_ac_type_;
}

BEGIN_MESSAGE_MAP(DlgMsgBoard, DlgUseful)
END_MESSAGE_MAP()

DlgMsgBoard::DlgMsgBoard() : DlgUseful(IDD_DLG_MSG_BOARD, AfxGetMainWnd())
{
	is_doing_ = false;
}

void DlgMsgBoard::DoDataExchange( CDataExchange* pDX )
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MSG_BOARD, msg_board_);
	DDX_Text(pDX, IDC_EDIT_MSG_BOARD, str_msg_board_);
}

void DlgMsgBoard::OnOK()
{
	if (is_doing_)
		return;

	VMP_BEGIN;
	UpdateData();
	if ( str_msg_board_.GetLength() > kMsgBoardMsgMaxLen )
	{
		assert(false);
		return;
	}
	std::string str_msg = CT2CA(str_msg_board_);
	SetDoing(true);

	GetIoService().post([this, str_msg](){
		CheckLoginC::AfterLoginSucced([this, &str_msg]( CheckLoginC::SelfPtr& conne ){
			conne->GetUserOper().LeaveMsg(str_msg.c_str());
		});
		auto dlg = DlgMsgBoard::GetInstance();
		if (dlg)
			dlg->SetDoing(false);
	});
	VMP_END;
}

BOOL DlgMsgBoard::OnInitDialog()
{
	if ( !__super::OnInitDialog() )
		return FALSE;
	//msg_board_.LineLength(12);
	msg_board_.LimitText(kMsgBoardMsgMaxLen / 2);
	return TRUE;
}

void DlgMsgBoard::SetDoing( bool is_doing )
{
	if ( !::IsWindow(m_hWnd) )
		return;
	is_doing_ = is_doing;
	auto bt_ok = GetDlgItem(IDOK);
	if (bt_ok)
		bt_ok->EnableWindow(!is_doing);
}

BEGIN_MESSAGE_MAP(DlgAddLoginAc, DlgUseful)
END_MESSAGE_MAP()

DlgAddLoginAc::DlgAddLoginAc( IDlgAddLoginSink* sink )  : DlgUseful(IDD_DLG_ADD_LOGIN_AC, AfxGetMainWnd())
{
	sink_ = sink;
}

void DlgAddLoginAc::DoDataExchange( CDataExchange* pDX )
{
	__super::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ADD_LOGIN_AC, ac_);
	DDX_Text(pDX, IDC_EDIT_ADD_LOGIN_PWD, pwd_);
}

void DlgAddLoginAc::OnOK()
{
	UpdateData();
	if ( ac_.GetLength() < kUserNameMinLen || ac_.GetLength() > kUserPwdMaxLen )
		return;
	if ( pwd_.GetLength() < kUserPwdMinLen || pwd_.GetLength() > kUserPwdMaxLen )
		return;
	if (sink_)
		sink_->OnAdd(*this);
}

DlgLogin::DlgLogin() : DlgLoginBase(IDD_DLG_LOGIN)
{

}

DlgRemoveBind::DlgRemoveBind() : DlgLoginBase(IDD_DLG_REMOVE_BIND)
{

}

BEGIN_MESSAGE_MAP(DlgAutoDial, DlgUseful)
	ON_BN_CLICKED(IDC_CHECK_OPEN_AUTO_DIAL, &DlgAutoDial::OnBtIsAutoDial)
	ON_CBN_SELCHANGE(IDC_COMBO_DIAL_MODE, &DlgAutoDial::OnSelchangeDialMode)
END_MESSAGE_MAP()

DlgAutoDial::DlgAutoDial() : DlgUseful(IDD_DLG_AUTO_DIAL, AfxGetMainWnd())
{
	cur_role_use_out_cnt_ = 0;
	timer_for_dial_.SetLetFirstTimePass(false);
}

void DlgAutoDial::DoDataExchange( CDataExchange* pDX )
{
	__super::DoDataExchange(pDX);
	auto& single_cfg = stSingletonCfg::GetMe();
	bool need_use_timer_old = single_cfg.auto_dial_info_.is_auto_dial_ && stSingletonCfg::stAutoDialInfo::kDM_AsTime == single_cfg.auto_dial_info_.auto_dial_mode_;

	int int_tmp = single_cfg.auto_dial_info_.is_auto_dial_;
	DDX_Check(pDX, IDC_CHECK_OPEN_AUTO_DIAL, int_tmp);
	single_cfg.auto_dial_info_.is_auto_dial_ = !!int_tmp;

	int_tmp = single_cfg.auto_dial_info_.auto_dial_mode_;
	DDX_CBIndex(pDX, IDC_COMBO_DIAL_MODE, int_tmp);
	single_cfg.auto_dial_info_.auto_dial_mode_ = stSingletonCfg::stAutoDialInfo::enDialMode(int_tmp);

	DDX_Text(pDX, IDC_EDIT_SHUA_HAO_SPAN, single_cfg.auto_dial_info_.run_ac_cnt_);
	DDX_Text(pDX, IDC_EDIT_DIAL_SPAN_TIME, single_cfg.auto_dial_info_.run_time_span_);

	DDX_Control(pDX, IDC_COMBO_DIAL_MODE, combo_select_mode_);

	bool need_use_timer = single_cfg.auto_dial_info_.is_auto_dial_ && stSingletonCfg::stAutoDialInfo::kDM_AsTime == single_cfg.auto_dial_info_.auto_dial_mode_;
	if ( need_use_timer && need_use_timer != need_use_timer_old )
		timer_for_dial_.RefreshCurTime();
}

BOOL DlgAutoDial::OnInitDialog()
{
	if ( !__super::OnInitDialog() )
		return FALSE;

	combo_select_mode_.InsertString(stSingletonCfg::stAutoDialInfo::kDM_AsAc, _T("��ˢ�Ų���"));
	combo_select_mode_.InsertString(stSingletonCfg::stAutoDialInfo::kDM_AsTime, _T("��ʱ�䲦��"));
	const auto& single_cfg = stSingletonCfg::GetMe();

	combo_select_mode_.SetCurSel(single_cfg.auto_dial_info_.auto_dial_mode_);

	UpdateData();
	ValidSomeCtrls();
	return TRUE;
}

void DlgAutoDial::OnOK()
{
	UpdateData();
	__super::OnOK();

	stSingletonCfg::GetMe().Save();
}

void DlgAutoDial::ValidSomeCtrls()
{
	auto& single_cfg = stSingletonCfg::GetMe();
	auto global_witch = single_cfg.auto_dial_info_.is_auto_dial_;
	combo_select_mode_.EnableWindow(global_witch);
	auto dlg_tmp = GetDlgItem(IDC_EDIT_SHUA_HAO_SPAN);
	if (dlg_tmp)
		dlg_tmp->EnableWindow(global_witch && stSingletonCfg::stAutoDialInfo::kDM_AsAc == single_cfg.auto_dial_info_.auto_dial_mode_);
	dlg_tmp = GetDlgItem(IDC_EDIT_DIAL_SPAN_TIME);
	if (dlg_tmp)
		dlg_tmp->EnableWindow(global_witch && stSingletonCfg::stAutoDialInfo::kDM_AsTime == single_cfg.auto_dial_info_.auto_dial_mode_);
}

void DlgAutoDial::OnBtIsAutoDial()
{
	UpdateData();
	ValidSomeCtrls();
}

void DlgAutoDial::OnSelchangeDialMode()
{
	UpdateData();
	ValidSomeCtrls();
}

bool DlgAutoDial::NeedReDial()
{
	const auto& single_cfg = stSingletonCfg::GetMe();
	if ( !single_cfg.auto_dial_info_.is_auto_dial_ )
		return false;
	if ( stSingletonCfg::stAutoDialInfo::kDM_AsAc == single_cfg.auto_dial_info_.auto_dial_mode_ )
	{
		if ( cur_role_use_out_cnt_ < single_cfg.auto_dial_info_.run_ac_cnt_ )
			return false;
		cur_role_use_out_cnt_ = 0;
	}
	else if ( stSingletonCfg::stAutoDialInfo::kDM_AsTime == single_cfg.auto_dial_info_.auto_dial_mode_ )
	{
		if ( single_cfg.auto_dial_info_.run_time_span_ > 0 )
			timer_for_dial_.SetTimeDist(1000 * 60 * single_cfg.auto_dial_info_.run_time_span_);
		if ( !timer_for_dial_.DoTimeout() )
			return false;
	}

	return true;
}
