#include "stdafx.h"
#include "LoginC.h"
#include "Socket/IoTimer.h"
#include "P_LoginMsg.h"
#include "Common/Toolhelp.h"
#include "atlpath.h"
#include <Communicate/CL_Defines.h>
#include <Communicate/CGL_Defines.h>
#include <protect/Protect.h>
#include <Communicate/LLH_Defines.h>

LoginC::LoginC() : Connection_Aes(kSelfIpStr, P_Port_Login), lua_l_(this), json_echo_(lua_l_, *this), login_oper_(*this)
{
	crack_captcha_ = &local_crack_captcha_;

}

typedef struct  
{
	HWND	str_hParWnd;						// �����ھ��
	TCHAR	str_szExeFile[MAX_ZONE_PATH];		// ��������,���޴�Сд,������д
	TCHAR	str_szWndName[MAX_ZONE_PATH];		// ��������
	TCHAR	str_szClassName[MAX_ZONE_PATH];		// ��������
	DWORD	str_GWL_STYLE;						// ���ڷ��
	DWORD	str_GWL_EXSTYLE;					// ��չ���ڷ��
	DWORD	str_GCL_STYLE;						// ������ķ��
	DWORD	str_x;								// x
	DWORD	str_y;								// y
}FINDWINDOW,*PFINDWINDOW;

BOOL    CALLBACK    EnumProc(HWND hWnd,LPARAM lPraram);
class EnumPidWnd
{
public:
	HWND	m_hWnd;
	DWORD	m_dwPid;
	bool	m_bIsHaveWnd;
	BOOL	m_bIsWindowVisible;
	PFINDWINDOW	m_pWnd;

	DWORD	m_dwWndCount;
public:
	EnumPidWnd(void){
		m_dwPid = 0;
		m_bIsHaveWnd = false;
	}
	HWND FindWindow(PFINDWINDOW pfindwnd, bool bIsWindowVisible = true){
		if( _tcslen(pfindwnd->str_szExeFile) == 0 )
		{
			return false;
		}

		m_bIsHaveWnd = false;
		m_bIsWindowVisible = bIsWindowVisible;
		m_pWnd = pfindwnd;

		m_dwPid = GetPidByName(pfindwnd->str_szExeFile);

		if(0!=m_dwPid)
		{
			::EnumWindows(EnumProc,(LPARAM)this);
		}

		if( m_bIsHaveWnd )
		{
			return m_hWnd;
		}

		return NULL;
	}
	unsigned long GetPidByName(LPCTSTR pname){
		unsigned long    pid=0;

		TCHAR name[256] = {0};
		_tcscpy_s(name, pname);

		::CharLower(name);

		PROCESSENTRY32    lp;
		HANDLE            lh=NULL;
		memset(&lp,0,sizeof(lp));
		lp.dwSize    =    sizeof(lp);

		lh            =    ::CreateToolhelp32Snapshot(    TH32CS_SNAPPROCESS, 0 );
		BOOL ok        =    ::Process32First( lh,&lp);

		CString str_tmp;
		while(ok)
		{
			str_tmp = lp.szExeFile;
			str_tmp.MakeLower();
			if ( str_tmp == name )
			{
				pid = lp.th32ProcessID;        
				break;
			}
			ok = ::Process32Next(lh,&lp);
		}
		return pid;
	}
};
BOOL    CALLBACK    EnumProc(HWND hWnd,LPARAM lPraram){
	if( NULL==hWnd ){ return FALSE;}

	EnumPidWnd* pEnumPidWnd = (EnumPidWnd*)lPraram;

	// �Ѿ��ҵ����ڣ�����Ҫ�ڱȽ���
	if( pEnumPidWnd->m_bIsHaveWnd == true )
	{
		return true;
	}

	if( ::IsWindow(hWnd) )
	{
		DWORD    pid=0;
		::GetWindowThreadProcessId(hWnd,&pid);
		if( pid==pEnumPidWnd->m_dwPid )
		{
			// �жϴ����Ƿ���ʾ
			BOOL  isS= ::IsWindowVisible(hWnd);

			if( isS == pEnumPidWnd->m_bIsWindowVisible )
			{
				TCHAR szWndName[256] = {0};
				::GetWindowText(hWnd, szWndName,256);

				// �Աȴ�������
				if( _tcslen(pEnumPidWnd->m_pWnd->str_szWndName) != 0 )
				{
					if( _tcscmp(pEnumPidWnd->m_pWnd->str_szWndName,szWndName) != 0 )
					{
						return true;
					}
				}

				// ���ڷ��
				if( pEnumPidWnd->m_pWnd->str_GWL_STYLE != 0 )
				{
					if( pEnumPidWnd->m_pWnd->str_GWL_STYLE != ::GetWindowLong(hWnd,GWL_STYLE) )
					{
						return true;
					}
				}

				// ��չ���ڷ��
				if( pEnumPidWnd->m_pWnd->str_GWL_EXSTYLE != 0 )
				{
					if( pEnumPidWnd->m_pWnd->str_GWL_EXSTYLE != ::GetWindowLong(hWnd,GWL_EXSTYLE) )
					{
						return true;
					}
				}

				// ָ�����ڵı߿���εĳߴ�
				if( pEnumPidWnd->m_pWnd->str_x != 0 && pEnumPidWnd->m_pWnd->str_y != 0 )
				{
					RECT rRect;
					if( ::GetWindowRect(hWnd,&rRect) )
					{
						if( pEnumPidWnd->m_pWnd->str_x != (rRect.right-rRect.left) || pEnumPidWnd->m_pWnd->str_y != (rRect.bottom-rRect.top) )
						{
							return true;
						}
					}
				}

				// �����������������
				if( _tcslen(pEnumPidWnd->m_pWnd->str_szClassName) != 0 )
				{
					TCHAR szClassName[256] = {0};
					if( ::GetClassName(hWnd,szClassName,sizeof(szClassName)) )
					{
						if( _tcscmp(pEnumPidWnd->m_pWnd->str_szClassName,szClassName) != 0 )
						{
							return true;
						}
					}
				}

				//������ķ��
				if( pEnumPidWnd->m_pWnd->str_GCL_STYLE != 0 )
				{
					if( pEnumPidWnd->m_pWnd->str_GCL_STYLE != ::GetClassLong(hWnd,GCL_STYLE) )
					{
						return true;
					}
				}


				//�����ھ��
				if( pEnumPidWnd->m_pWnd->str_hParWnd != NULL )
				{
					if( pEnumPidWnd->m_pWnd->str_hParWnd != ::GetParent(hWnd) )
					{
						return true;
					}
				}

				pEnumPidWnd->m_bIsHaveWnd = true;
				pEnumPidWnd->m_hWnd = hWnd;
			}

			return TRUE;
		}
	}

	return TRUE;
}

bool LoginC::Init()
{
	VMP_BEGIN_EX;
	if ( !lua_l_.InitScript(_T("Login.dll"), _T("main.lua")) )
		return false;
	if ( !CheckAssistVersion() )
	{
		assert(false);

		SetIoTimer(10 * 1000, []( IoTimer* ){
			VMP_BEGIN_EX;
			throw CmnExitIoThreadException("le");
			VMP_END;
		});
	}
	VMP_END;
	return true;
}

JsonEcho& LoginC::GetJsonEcho()
{
	return json_echo_;
}

void LoginC::BeginLogin()
{
	/*SetIoTimer(20, [=]( IoTimer* timer ){
		assert(timer);
		if ( 0 == this->Do_CheckSafeSubProcessId() )
			timer->Continue();
	});*/
	/*SetIoTimer(5 * 1000, [=]( IoTimer* timer ){
		assert(timer);
		if ( !this->InputAccount() )
			timer->Continue();
	});*/
	SetIoTimer(50, [=]( IoTimer* timer ){
		assert(timer);
		if ( !this->OpenMemFileMap() )
			timer->Continue();
	});
}

bool LoginC::InputAccount()
{
	if (account_.empty())
	{
		assert(false);
		return false;
	}

	struct Helper{
		POINT		pt;
		Helper( LoginC* login_c ){			
			pt.x = login_c->lua_l_.Call<long>("Login_GetAccountCtrlPosX", 0);
			pt.y = login_c->lua_l_.Call<long>("Login_GetAccountCtrlPosY", 0);
		}
	};

	//HWND hWnd = ::FindWindow(kLoginMainClsName, kLoginMainWndName);

	// �����˺�
	HWND hWnd = FindAcWnd();
	if ( !::IsWindow(hWnd) )
	{
		assert(false);
		return false;
	}
	//�ö�����
	ForegroundWnd(hWnd);

	static Helper helper(this);

	::PostMessage(hWnd, WM_LBUTTONDOWN, 1, MAKELPARAM(helper.pt.x, helper.pt.y));
	::PostMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(helper.pt.x, helper.pt.y));

	for ( int i = 0; i < 20; ++i )
	{
		::PostMessage(hWnd, WM_KEYDOWN, VK_DELETE, 0);
		::PostMessage(hWnd, WM_KEYUP, VK_DELETE, 0);
		::PostMessage(hWnd, WM_KEYDOWN, VK_BACK, 0);
		::PostMessage(hWnd, WM_KEYUP, VK_BACK, 0);
	}

	for ( auto it = account_.begin(); it != account_.end(); ++it )
	{
		::PostMessage(hWnd, WM_IME_CHAR, *it, 0);
	}

	SetIoTimer(1000, [=]( IoTimer* timer ){
		assert(timer);
		if ( !this->InputPassword() )
			timer->Continue();
	});
	SetIoTimer(500, [=]( IoTimer* timer ){
		assert(timer);
		if ( !this->HandleLoginResult() )
			timer->Continue();
	});
	return true;
}

void LoginC::SetAccount_Password( const char* account, const char* password )
{
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "�����ʺź����룬�ʺ��ǣ�" << account;
	account_ = account;
	password_ = password;
}

void LoginC::SetJoinedService( int pos_x, int pos_y )
{
	service_pos_.SetPoint(pos_x, pos_y);
}

void InputKeybdEvent_( const std::string& str )
{
	if(LOBYTE(GetKeyState(VK_CAPITAL)))
		//�رմ�Сд��
	{
		keybd_event(VK_CAPITAL, 0, 0, 0);
		Sleep(50);
		keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
	}
	for ( auto it = str.begin(); it != str.end(); ++it )
	{
		auto key = *it;
		if (std::isupper(key))
		{
			//����Shift��
			keybd_event(VK_SHIFT, 0, 0, 0);
			//Sleep(200);
			//���´�д����ĸ��
			keybd_event(key, 0, 0, 0);
			//Sleep(200);
			//�ɿ���д����ĸ��
			keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
			//Sleep(200);
			//�ɿ�Shift��
			keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
			continue;
		}
		else if (std::islower(key))
		{
			key = std::toupper(key);
		}
		Sleep(50);
		//���¼�
		keybd_event(key, 0, 0, 0);
		//�ɿ���
		keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
		//Sleep(200);
	}
}

bool LoginC::InputPassword()
{
	struct Helper{
		POINT		pt;
		Helper( LoginC* login_c ){			
			pt.x = login_c->lua_l_.Call<long>("Login_GetPasswordCtrlPosX", 0);
			pt.y = login_c->lua_l_.Call<long>("Login_GetPasswordCtrlPosY", 0);
		}
	};

	//HWND hWnd = ::FindWindow(kLoginMainClsName, kLoginMainWndName);
	// �������� 
	FINDWINDOW	theWnd;
	memset(&theWnd, 0, sizeof(theWnd));
	_tcscpy_s(theWnd.str_szExeFile, _T("TASLogin.exe"));
	_tcscpy_s(theWnd.str_szClassName, _T("Edit"));
	theWnd.str_x = 196;
	theWnd.str_y = 20;
	theWnd.str_GWL_STYLE = 0x94010020;
	EnumPidWnd theEnumPidWnd;
	HWND hWnd = theEnumPidWnd.FindWindow(&theWnd);

	if ( !::IsWindow(hWnd) )
		return false;
	static Helper helper(this);

	::PostMessage(hWnd, WM_LBUTTONDOWN, 1, MAKELPARAM(helper.pt.x, helper.pt.y));
	::PostMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(helper.pt.x, helper.pt.y));
	//�ö�
	ForegroundWnd(hWnd);

	//��������
	InputKeybdEvent_(password_);
	DummySleep(1000);
	
	//���س���
	keybd_event(VK_RETURN ,0,0,0);
	keybd_event(VK_RETURN ,0,KEYEVENTF_KEYUP,0);

	/*SetIoTimer(2000, [=]( IoTimer* timer ){
		assert(timer);
		if ( !this->LoginGame() )
			timer->Continue();
	});*/
	SetIoTimer(1000, [=]( IoTimer* timer ){
		assert(timer);
		if ( !this->HandleCaptcha() )
			timer->Continue();
	});
	return true;
}

bool LoginC::LoginGame()
{
	LOG_ENTER_FUNC;
	//���س���
	keybd_event(VK_RETURN ,0,0,0);
	keybd_event(VK_RETURN ,0,KEYEVENTF_KEYUP,0);

	/*HWND hWnd = ::FindWindow(/ *kLoginSelectServiceWndClsName* /nullptr, kLoginMainWndName);
	if ( !::IsWindow(hWnd) )
	{
		LOG_O(Log_trace) << "�����½��Ϸ��ʧ��";
		return false;
	}
	LOG_O(Log_trace) << "�����½��Ϸ���ɹ�";*/

	/*struct Helper{
		POINT		pt;
		Helper( LoginC* login_c ){			
			pt.x = login_c->lua_l_.Call<long>("Login_BeginGameBtX", 0);
			pt.y = login_c->lua_l_.Call<long>("Login_BeginGameBtY", 0);
		}
	};
	static Helper helper(this);

	::PostMessage(hWnd, WM_LBUTTONDOWN, 1, MAKELPARAM(helper.pt.x, helper.pt.y));
	::PostMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(helper.pt.x, helper.pt.y));

	SetIoTimer(1000, [=]( IoTimer* timer ){
		assert(timer);
		if ( !this->HandleCaptcha() )
			timer->Continue();
	});*/
	return true;
}

bool LoginC::SelectService()
{
	SetIoTimer(1000, [=]( IoTimer* timer ){
		assert(timer);
		HWND hWnd = ::FindWindow(nullptr, kLoginMainWndName);
		if ( !::IsWindow(hWnd) )
		{
			timer->Continue();
			return;
		}

		::PostMessage(hWnd, WM_LBUTTONDOWN, 1, MAKELPARAM(service_pos_.x, service_pos_.y));
		::PostMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(service_pos_.x, service_pos_.y));

		DummySleep(1000);

		/*if ( !this->SelectedService() )
			timer->Continue();*/

		SelectedService();
		timer->Continue();
	});
	return true;
}

bool LoginC::SelectedService()
{
	struct Helper{
		POINT		pt;
		Helper( LoginC* login_c ){			
			pt.x = login_c->lua_l_.Call<long>("Login_SelectedServicePosX", 0);
			pt.y = login_c->lua_l_.Call<long>("Login_SelectedServicePosY", 0);
		}
	};

	static Helper helper(this);
	static bool is_find_wnd = false;

	HWND hWnd = ::FindWindow(/*kLoginSelectServiceWndClsName*/nullptr, kLoginMainWndName);
	if ( !::IsWindow(hWnd) )
	{
		if (is_find_wnd)
		{
			/*LOG_ENTER_FUNC;
			LOG_O(Log_trace) << "ȷ��ѡ��������ˣ��ر�socket";
			Disconnect();*/
			return true;
		}
		return false;
	}
	//ForegroundWnd(hWnd);
	is_find_wnd = true;
	/*for ( int i = 0; i != 10; ++i )
	{
		::PostMessage(hWnd, WM_LBUTTONDOWN, 1, MAKELPARAM(helper.pt.x, helper.pt.y));
		::PostMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(helper.pt.x, helper.pt.y));
	}

	Disconnect();
	return true;*/

	::PostMessage(hWnd, WM_LBUTTONDOWN, 1, MAKELPARAM(helper.pt.x, helper.pt.y));
	::PostMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(helper.pt.x, helper.pt.y));
	return false;
}

bool LoginC::HandleCaptcha()
{
	//�ж��Ƿ���뵽ѡ�����������
	/*HWND hWnd = ::FindWindow(_T("NetSpeedDetectorModuleWindow"), _T("NetSpeedDetectorModuleWindow"));
	if ( hWnd && ::IsWindow(hWnd) )*/
	if ( !FindAcWnd() )
		//����Ҫ����֤��
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "δ�ҵ��ʺ�Edit��";
		/*SetIoTimer(1000, [=]( IoTimer* timer ){
			assert(timer);
			if ( !this->SelectService() )
				timer->Continue();
		});*/
		SelectSerRegion();
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	/*FINDWINDOW	theWnd;
	memset(&theWnd,0,sizeof(theWnd));
	theWnd.str_hParWnd = ::FindWindow(kLoginMainClsName, kLoginMainWndName);
	_tcscpy_s(theWnd.str_szExeFile, kLoginClientName);
	_tcscpy_s(theWnd.str_szClassName, kLoginMainClsName);
	theWnd.str_x = 526;
	theWnd.str_y = 307;
	theWnd.str_GWL_STYLE = 0x0d6020000;
	theWnd.str_GWL_EXSTYLE = 0x00080000;
	theWnd.str_GCL_STYLE = 0x8;

	EnumPidWnd theEnumPidWnd;
	hWnd = theEnumPidWnd.FindWindow(&theWnd);

	if(hWnd)
	{
		CPath chaptcha_pic = GetModulePath(nullptr) + kCaptchaPicNewName;
		if ( !chaptcha_pic.FileExists() )
		{
			LOG_ENTER_FUNC;
			LOG_O(Log_trace) << "ָ������֤��ͼƬ��������:\t" << (LPCSTR)CT2CA(chaptcha_pic);
			return false;
		}
		std::string captcha;
		if (crack_captcha_->GetResult((LPCSTR)CT2CA(chaptcha_pic), captcha))
		{
			struct Helper{
				POINT		pt;
				Helper( LoginC* login_c ){			
					pt.x = login_c->lua_l_.Call<long>("Login_GetCaptchaInputPosX", 0);
					pt.y = login_c->lua_l_.Call<long>("Login_GetCaptchaInputPosY", 0);
				}
			};
			static Helper helper(this);

			::PostMessage(hWnd, WM_LBUTTONDOWN, 1, MAKELPARAM(helper.pt.x, helper.pt.y));
			::PostMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(helper.pt.x, helper.pt.y));

			const auto kCaptchaCnt = captcha.size();
			for ( std::size_t i = 0; i < kCaptchaCnt; ++i )
			{
				::PostMessage(hWnd, WM_CHAR, captcha[i], MAKELPARAM(captcha[i], WM_KEYDOWN));
			}

			::PostMessage(hWnd, WM_KEYDOWN, VK_RETURN, 0);
			::PostMessage(hWnd, WM_KEYUP, VK_RETURN, 0);

			LOG_ENTER_FUNC;
			LOG_O(Log_trace) << "������֤�룺" << captcha;
		}
		else
		{
			LOG_ENTER_FUNC;
			LOG_O(Log_warning) << "����ʧ��";
		}
	}
	else
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "û���ҵ���֤��Ի���,����LoginGame";
		SetIoTimer(2000, [=]( IoTimer* timer ){
			assert(timer);
			if ( !this->LoginGame() )
				timer->Continue();
		});
		return true;
	}*/

	//////////////////////////////////////////////////////////////////////////
	//CPath chaptcha_pic = GetModulePath(nullptr) + kCaptchaPicNewName;
	const TCHAR* const kPicRelativePath = _T("TenProtect\\ui\\res\\");
	CPath chaptcha_pic = GetModulePath(nullptr) + kPicRelativePath + _T("pic.png");

	if ( !chaptcha_pic.FileExists() )
	{
		CPath chaptcha_pic1 = GetModulePath(nullptr) + kPicRelativePath + _T("pic1.png");
		if ( !chaptcha_pic1.FileExists() )
		{
			LOG_ENTER_FUNC;
			LOG_O(Log_trace) << "û���ҵ���֤��ͼƬ,����InputPassword";
			SetIoTimer(2000, [=]( IoTimer* timer ){
				assert(timer);
				if ( !this->InputPassword() )
					timer->Continue();
			});
			return true;
		}
		chaptcha_pic = chaptcha_pic1;
	}

	std::string captcha;
	if (crack_captcha_->GetResult((LPCSTR)CT2CA(chaptcha_pic), captcha))
	{
		VERIFY(::DeleteFile(chaptcha_pic));
		struct Helper{
			POINT		pt;
			Helper( LoginC* login_c ){			
				pt.x = login_c->lua_l_.Call<long>("Login_GetCaptchaInputPosX", 0);
				pt.y = login_c->lua_l_.Call<long>("Login_GetCaptchaInputPosY", 0);
			}
		};
		static Helper helper(this);

		auto kMainWnd = ::FindWindow(nullptr, kLoginMainWndName);
		if ( !kMainWnd || !::IsWindow(kMainWnd) )
		{
			LOG_ENTER_FUNC;
			LOG_O(Log_debug) << "������֤���ʱ�򣬾�Ȼ�Ҳ���������";
			return false;
		}
		/*::PostMessage(kMainWnd, WM_LBUTTONDOWN, 1, MAKELPARAM(helper.pt.x, helper.pt.y));
		::PostMessage(kMainWnd, WM_LBUTTONUP, 0, MAKELPARAM(helper.pt.x, helper.pt.y));

		const auto kCaptchaCnt = captcha.size();
		for ( std::size_t i = 0; i < kCaptchaCnt; ++i )
		{
			::PostMessage(kMainWnd, WM_CHAR, captcha[i], MAKELPARAM(captcha[i], WM_KEYDOWN));
		}

		::PostMessage(kMainWnd, WM_KEYDOWN, VK_RETURN, 0);
		::PostMessage(kMainWnd, WM_KEYUP, VK_RETURN, 0);
		*/

		InputKeybdEvent_(captcha);
		DummySleep(1000);

		::PostMessage(kMainWnd, WM_KEYDOWN, VK_RETURN, 0);
		::PostMessage(kMainWnd, WM_KEYUP, VK_RETURN, 0);

		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "������֤�룺" << captcha;
	}
	else
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "����ʧ��";
	}
	//////////////////////////////////////////////////////////////////////////
	return false;
}

void LoginC::SetCrackCaptchaMode( int ccm, const char* account, const char* password, const char* remote_ip, WORD remote_port )
{
	crack_captcha_mode_.ccm_ = (stCrackCaptchaMode::enCrackCaptchaMode)ccm;
	if ( account && password )
	{
		crack_captcha_mode_.account_ = account;
		crack_captcha_mode_.password_ = password;
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "���ô��뷽ʽ��ccm:" << crack_captcha_mode_.ccm_ << "\taccount:" << crack_captcha_mode_.account_ << 
			"\tpassword:" << crack_captcha_mode_.password_;
	}
	else
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "���ô��뷽ʽ��ccm:" << crack_captcha_mode_.ccm_;
	}

	if (remote_ip)
	{
		crack_captcha_mode_.remote_ip_ = remote_ip;
		crack_captcha_mode_.remote_port_ = remote_port;
	}

	switch (crack_captcha_mode_.ccm_)
	{
	case stCrackCaptchaMode::kCCM_Local:
		{
			local_crack_captcha_.SetServiceInfo(crack_captcha_mode_.remote_ip_.c_str(), crack_captcha_mode_.remote_port_);
			crack_captcha_ = &local_crack_captcha_;
			break;
		}
	case stCrackCaptchaMode::kCCM_DaMaTu:
		{
			da_ma_tu_.SetAccountPassword(crack_captcha_mode_.account_.c_str(), crack_captcha_mode_.password_.c_str());
			crack_captcha_ = &da_ma_tu_;
			break;
		}
	default:
		break;
	}

	if ( !crack_captcha_->Init() )
	{
		assert(false);
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "�����ʼ��ʧ��";
	}
}

DWORD LoginC::Do_CheckSafeSubProcessId()
{
	struct Helper{
		Helper(){
			cur_process_id_ = ::GetCurrentProcessId();
			CString safe_check_exe = GetModulePath(nullptr);
			safe_check_exe += _T("TenProtect\\TASLogin.exe");
			CPath path_tmp(safe_check_exe);
			path_safe_check_exe_ = path_tmp;
		}
		CPath		path_safe_check_exe_;
		DWORD		cur_process_id_;
	};
	static Helper helper;
	const DWORD kCurProcessId = helper.cur_process_id_;

	DWORD res = 0;
	CToolhelp::DoProcessIdUntil(helper.path_safe_check_exe_, [kCurProcessId, &res]( DWORD process_id ){
		if ( kCurProcessId == CToolhelp::GetParentProcessID(process_id) )
		{
			res = process_id;
			return true;
		}
		return false;
	});
	if ( 0 != res )
	{
		LOG_ENTER_FUNC;
		if ( !InjectLoginHelper(res) )
		{
			LOG_O(Log_debug) << "ע��LoginH.dllʧ��";
			return res;
		}
		LOG_O(Log_trace) << "ע��LoginH.dll�ɹ�";
		/*SetIoTimer(500, [=]( IoTimer* timer ){
			assert(timer);
			if ( !this->Do_SafeCheckEventExist() )
				timer->Continue();
		});*/
	}
	return res;
}

bool LoginC::Do_SafeCheckEventExist()
{
	assert(false);
	struct Helper{
		Helper(){
			/*auto str_src = GenUuidStr(kLogin_SafeCheckEventName);
			str_event_name_ = CA2CT(str_src.c_str());*/
		}

		CString			str_event_name_;
	};
	static Helper helper;
	//���¼�����
	auto event_handle = ::OpenEvent(DELETE, FALSE, helper.str_event_name_);
	if (event_handle)
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "��ȫ����¼�����򿪳ɹ�";
		::CloseHandle(event_handle);
		SetIoTimer(2 * 1000, [=]( IoTimer* timer ){
			assert(timer);
			if ( !this->InputAccount() )
				timer->Continue();
		});
		return true;
	}
	return false;
}

bool LoginC::InjectLoginHelper( DWORD process_id )
{
	auto str_dll = ModuleHelper::GetMe().GetFullFilePath() + _T("LoginH.dll");
	return !!InjectLib(process_id, str_dll);
}

bool LoginC::OpenMemFileMap()
{
	auto& file_map = LLH_MemFileMap::GetMe();
	if ( !file_map.OpenFileMap() )
		return false;
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "���ڴ�ӳ���ļ��ɹ�";
	SetIoTimer(500, [this]( IoTimer* timer ){
		assert(timer);
		auto& file_map = LLH_MemFileMap::GetMe();
		auto commu = file_map.ReadAsCommu();
		if ( !commu )
		{
			assert(false);
			timer->Continue();
			return;
		}
		if ( !commu->safe_check_done_ )
		{
			timer->Continue();
			return;
		}
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "safe check done->" << commu->safe_check_done_;
		DummySleep(3000);
		InputAccount();
	});
	return true;
}

bool LoginC::HandleLoginResult()
{
	auto& file_map = LLH_MemFileMap::GetMe();
	auto commu = file_map.ReadAsCommu();
	if ( !commu )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "commuΪ��";
		return false;
	}
	if (commu->pwd_input_error_)
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "�ʺŻ������������";
		bool res = false;
		login_oper_.ThisMemCallSync(nullptr, "AcOrPwdErr", nullptr, JsonEcho::MakeResult(res, res));
		
		throw CmnExitIoThreadException("�ʺŻ������������");
		return true;
	}
	if (commu->ac_freeze_)
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "�ʺű�����";
		bool res = false;
		login_oper_.ThisMemCallSync(nullptr, "AcFreeze", nullptr, JsonEcho::MakeResult(res, res));

		throw CmnExitIoThreadException("�ʺű�����");
		return true;
	}
	/*if (commu->login_succeed_)
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_info) << "��¼�ɹ�";
		SetIoTimer(1000, [=]( IoTimer* timer ){
			assert(timer);
			if ( !this->SelectedService() )
				timer->Continue();
		});
		return true;
	}*/
	return false;
}

HWND LoginC::FindAcWnd()
{
	// �����˺�
	FINDWINDOW	theWnd;
	memset(&theWnd, 0, sizeof(theWnd));
	_tcscpy_s(theWnd.str_szExeFile, _T("TASLogin.exe"));
	_tcscpy_s(theWnd.str_szClassName, _T("Edit"));
	theWnd.str_x = 196;
	theWnd.str_y = 20;
	//theWnd.str_GWL_STYLE = wnd_style;
	//theWnd.str_GWL_STYLE = 0x940120ef;
	EnumPidWnd theEnumPidWnd;
	return theEnumPidWnd.FindWindow(&theWnd);
}

bool LoginC::OnConnected( IoConnectBase* connect )
{
	if ( !__super::OnConnected(connect) )
		return false;
	if ( !Init() )
		return false;

	P_Exec_BindLoginPid msg;
	msg.login_pid_ = GetCurrentProcessId();

	return Exec(kLoginMsg_BindLoginPid, &msg, sizeof(msg));
}

bool LoginC::HandleServiceFull()
{
	SetIoTimer(1000, [=]( IoTimer* timer ){
		HWND hWnd = ::FindWindow(nullptr, kLoginMainWndName);
		if ( !::IsWindow(hWnd) )
		{
			timer->Continue();
			return;
		}
		const int pos_x = 552;
		const int pos_y = 561;
		::PostMessage(hWnd, WM_LBUTTONDOWN, 1, MAKELPARAM(pos_x,pos_y));
		::PostMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(pos_x,pos_y));
		timer->Continue();
	});
	return true;
}

bool LoginC::SelectSerRegion()
{
	SetIoTimer(1000, [=]( IoTimer* timer ){
		assert(timer);
		HWND hWnd = ::FindWindow(nullptr, kLoginMainWndName);
		if ( !::IsWindow(hWnd) )
		{
			timer->Continue();
			return;
		}

		::PostMessage(hWnd, WM_LBUTTONDOWN, 1, MAKELPARAM(ser_region_pos_.x, ser_region_pos_.y));
		::PostMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(ser_region_pos_.x, ser_region_pos_.y));

		DummySleep(1000);

		/*if ( !this->SelectedService() )
			timer->Continue();*/

		SelectService();
		timer->Continue();
	});
	return true;
}

void LoginC::SetSerRegion( int pos_x, int pos_y )
{
	ser_region_pos_.SetPoint(pos_x, pos_y);
}

LoginOperC::LoginOperC( LoginC& login_c ) : login_c_(login_c), JsonEchoBase(*Lua_l::GetInstance(), login_c, kObjId_LoginOper)
{

}

bool LoginOperC::OnThisMemCall( const stThisCallHelper& helper )
{
	return OnThisFuncCallImpl(this, helper);
}

bool LoginOperC::CheckLoginStr( const std::string& console_str )
{
	VMP_BEGIN_EX;
	bool res = false;
	if ( console_str != GenUuidStr(VMP_PROTECT_STR(kStableStr_ConsoleToLogin)) )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_debug) << "��֤��½�ַ���ʧ��";
		SetIoTimer(1 * 1000, []( IoTimer* ){
			VMP_BEGIN_EX;
			const auto* const kThrowStr = 
#ifdef _DEBUG
				"check login str error"
#else
				"clse"
#endif
				;
			assert(false);
			throw CmnExitIoThreadException(kThrowStr);
			VMP_END;
		});
		res = false;
	}
	res = true;
	ThisMemCall(nullptr, "oclvr", &JsonEcho::MakeParams(res));
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "��֤��½�ַ����ɹ�";
	return res;
	VMP_END;
}

const char* LoginC::DaMaTu_JFZR::SoftKey() const
{
	return "b3a64c67072ba35fc12e5ebd5bd204d2";
}
