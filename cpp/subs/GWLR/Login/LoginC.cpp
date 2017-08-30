#include "stdafx.h"
#include "LoginC.h"
#include "Net/IoTimer.h"
#include "P_LoginMsg.h"
#include "Common/Toolhelp.h"
#include "atlpath.h"
#include <Communicate/CL_Defines.h>
#include <Communicate/CGL_Defines.h>
#include <protect/Protect.h>
#include <Communicate/LLH_Defines.h>
#include <Protocol/P_NormalMsg.h>

LoginC::LoginC() : Connection(kSelfIpStr, P_Port_ForLogin), lua_l_(this), json_echo_(lua_l_, *this), login_oper_(*this)
{
	crack_captcha_ = &local_crack_captcha_;
	is_dmtest_ = true;
}

bool LoginC::Init()
{
	VMP_BEGIN_EX;
	if ( !lua_l_.InitScript(nullptr, _T("main")) )
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
		return false;

	struct Helper{
		POINT		pt;
		Helper( LoginC* login_c ){			
			pt.x = login_c->lua_l_.Call<long>("Login_GetAccountCtrlPosX", 0);
			pt.y = login_c->lua_l_.Call<long>("Login_GetAccountCtrlPosY", 0);
		}
	};

	//HWND hWnd = ::FindWindow(kLoginMainClsName, kLoginMainWndName);

	// �����˺�
	HWND hWnd = GetAcWnd();
	if ( !::IsWindow(hWnd) )
		return false;
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
	EnumPidWnd::FindInfo theWnd;
	_tcscpy_s(theWnd.str_szExeFile, _T("TASLogin.exe"));
	_tcscpy_s(theWnd.str_szClassName, _T("Edit"));
	theWnd.str_x = 212;
	theWnd.str_y = 21;
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

	DummySleep(500);
	//��������
	for (auto c : password_)
	{
		InputKeybdEventChar(c);
	}
	
	SetIoTimer(2000, [=]( IoTimer* timer ){
		assert(timer);
		if ( !this->LoginGame() )
			timer->Continue();
	});
	return true;
}

bool LoginC::LoginGame()
{
	LOG_ENTER_FUNC;
	
	HWND hWnd = ::FindWindow(nullptr, kLoginMainWndName);
	if ( !::IsWindow(hWnd) )
	{
		LOG_O(Log_trace) << "�����½��Ϸ��ʧ��";
		return false;
	}
	LOG_O(Log_trace) << "�����½��Ϸ���ɹ�";

	struct Helper{
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
	});

	StartCloseLoginAdvert();
	return true;
}

bool LoginC::SelectService()
{
	HWND hWnd = ::FindWindow(nullptr, kLoginMainWndName);
	if ( !::IsWindow(hWnd) )
		return false;

	::PostMessage(hWnd, WM_LBUTTONDOWN, 1, MAKELPARAM(service_pos_.x, service_pos_.y));
	::PostMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(service_pos_.x, service_pos_.y));

	SetIoTimer(1000, [=]( IoTimer* timer ){
		assert(timer);
		if ( !this->SelectedService() )
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

	HWND hWnd = ::FindWindow(nullptr, kLoginMainWndName);
	if ( !::IsWindow(hWnd) )
	{
		if (is_find_wnd)
		{
			/*LOG_ENTER_FUNC;
			LOG_O(Log_info) << "ȷ��ѡ��������ˣ��ر�socket";
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
	//�رվ����
	const CPoint pos(537, 484);
	::PostMessage(hWnd, WM_LBUTTONDOWN, 1, MAKELPARAM(pos.x, pos.y));
	::PostMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(pos.x, pos.y));


	::PostMessage(hWnd, WM_LBUTTONDOWN, 1, MAKELPARAM(helper.pt.x, helper.pt.y));
	::PostMessage(hWnd, WM_LBUTTONUP, 0, MAKELPARAM(helper.pt.x, helper.pt.y));
	return false;
}

bool LoginC::HandleCaptcha()
{
	//�ж��Ƿ���뵽ѡ�����������
	/*if ( !GetAcWnd() )
		//����Ҫ����֤��
	{
		EndCloseLoginAdvert();
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "��½��ѡ�����������";
		SetIoTimer(1000, [=]( IoTimer* timer ){
			assert(timer);
			if ( !this->SelectService() )
				timer->Continue();
		});
		DMTest();
		return true;
	}*/

	//////////////////////////////////////////////////////////////////////////
	//CPath chaptcha_pic = GetModulePath(nullptr) + kCaptchaPicNewName;
	CPath chaptcha_pic = GetModulePath(nullptr) + kDaMaPicRelativePath + _T("pic.png");

	if ( !chaptcha_pic.FileExists() )
	{
		CPath chaptcha_pic1 = GetModulePath(nullptr) + kDaMaPicRelativePath + _T("pic1.png");
		if ( !chaptcha_pic1.FileExists() )
		{
			if (GetAcWnd())
			{
				LOG_ENTER_FUNC;
				LOG_O(Log_trace) << "û���ҵ���֤��ͼƬ,�������������LoginGame";
				SetIoTimer(2000, [=]( IoTimer* timer ){
					assert(timer);
					if ( !this->InputPassword() )
					{
						if (GetAcWnd())
							timer->Continue();
						else
						{
							SetIoTimer(2000, [=]( IoTimer* timer ){
								assert(timer);
								if ( !this->LoginGame() )
									timer->Continue();
							});
						}
					}
				});
				DMTest();
				return true;
			}
			else
			{
				SelectedService();
				return false;
			}
		}
		chaptcha_pic = chaptcha_pic1;
	}

	std::string captcha;
	LOG_O(Log_trace) << "����֮��ʼ��ȡ��";
	if (crack_captcha_->GetResult((LPCSTR)CT2CA(chaptcha_pic), captcha))
	{
		//LOG_O(Log_trace) << "����֮��ȡ�𰸳ɹ�";
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
			LOG_O(Log_error) << "������֤���ʱ�򣬾�Ȼ�Ҳ���������";
			return false;
		}
		::PostMessage(kMainWnd, WM_LBUTTONDOWN, 1, MAKELPARAM(helper.pt.x, helper.pt.y));
		::PostMessage(kMainWnd, WM_LBUTTONUP, 0, MAKELPARAM(helper.pt.x, helper.pt.y));

		const auto kCaptchaCnt = captcha.size();
		for ( std::size_t i = 0; i < kCaptchaCnt; ++i )
		{
			::PostMessage(kMainWnd, WM_CHAR, captcha[i], MAKELPARAM(captcha[i], WM_KEYDOWN));
		}

		::PostMessage(kMainWnd, WM_KEYDOWN, VK_RETURN, 0);
		::PostMessage(kMainWnd, WM_KEYUP, VK_RETURN, 0);

		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "������֤�룺" << captcha;
	}
	else
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "����ʧ��";
		DMTest();
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
	case stCrackCaptchaMode::kCCM_DaMaTu:
		{
			da_ma_tu_.SetAccountPassword(crack_captcha_mode_.account_.c_str(), crack_captcha_mode_.password_.c_str());
			crack_captcha_ = &da_ma_tu_;
			break;
		}
	case stCrackCaptchaMode::kCCM_Local:
		{
			local_crack_captcha_.SetServiceInfo(crack_captcha_mode_.remote_ip_.c_str(), crack_captcha_mode_.remote_port_);
			crack_captcha_ = &local_crack_captcha_;
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
			LOG_O(Log_error) << "ע��LoginH.dllʧ��";
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
	auto str_dll = GlobalSetter::GetMe().GetSelfModuleFullFilePath() + _T("LoginH.dll");
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

		DummySleep(300);
		SetIoTimer(500, [this]( IoTimer* timer ){
			if ( !InputAccount() )
				timer->Continue();

		});
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

		//throw CmnExitIoThreadException("�ʺŻ������������");
		return true;
	}
	if (commu->ac_freeze_)
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "�ʺű�����";
		bool res = false;
		login_oper_.ThisMemCallSync(nullptr, "AcFreeze", nullptr, JsonEcho::MakeResult(res, res));

		//throw CmnExitIoThreadException("�ʺű�����");
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

HWND LoginC::GetAcWnd()
{
	EnumPidWnd::FindInfo theWnd;
	_tcscpy_s(theWnd.str_szExeFile, _T("TASLogin.exe"));
	_tcscpy_s(theWnd.str_szClassName, _T("Edit"));
	theWnd.str_x = 212;
	theWnd.str_y = 21;
	theWnd.str_GWL_STYLE = 0x940120ef;
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

	return UserMsg(kLoginMsg_BindLoginPid, &msg, sizeof(msg));
}

void LoginC::StartCloseLoginAdvert()
{
	return;
	if ( !close_login_advert_ )
	{
		close_login_advert_ = CreateIoTimer(300, [this]( IoTimerPtr timer ){
			StartCloseLoginAdvert();
			timer->Continue();
		}, true);
	}
	EnumPidWnd::FindInfo theWnd;
	theWnd.str_hParWnd = ::FindWindow(NULL, _T("Fifa Online 3��¼����"));
	_tcscpy_s(theWnd.str_szExeFile, _T("Client.exe"));
	_tcscpy_s(theWnd.str_szClassName, _T("TWINCONTROL"));
	theWnd.str_x = 518;
	theWnd.str_y = 325;
	theWnd.str_GWL_STYLE = 0xD6020000;
	theWnd.str_GWL_EXSTYLE = 0x00000000;
	theWnd.str_GCL_STYLE = 0x8;
	EnumPidWnd theEnumPidWnd;
	HWND hWnd = theEnumPidWnd.FindWindow(&theWnd);
	if (hWnd)
		::PostMessage(hWnd,WM_CLOSE,NULL,NULL);
}

void LoginC::EndCloseLoginAdvert()
{
	if (close_login_advert_)
	{
		close_login_advert_->Cancel();
		close_login_advert_.reset();
	}
}

void LoginC::SetGamePath( const std::string& game_path )
{
	auto the_path = game_path + "\\CrashDumps\\*.dmp";
	std::system(("del /f /s /q \"" + the_path + "\"").c_str());
	std::system("del /f /s /q C:\\Users\\administrator\\appData\\local\\temp\\*.tmp");
}

void LoginC::DMTest()
{
	/*using namespace Gdiplus;
	int s_width = 4 * 11.5;
	const auto dm_pic1 = LoadRcdataRes(GlobalSetter::GetMe().GetSelfModuleHandle(), _T("DM_TEST"));
	
	HGLOBAL m_hMem = GlobalAlloc(GMEM_FIXED, dm_pic1.second);  
	BYTE* pmem = (BYTE*)GlobalLock(m_hMem);  
	memcpy(pmem, dm_pic1.first, dm_pic1.second);  
	IStream* pstm = nullptr;  
	CreateStreamOnHGlobal(m_hMem,FALSE,&pstm);  
	// load from stream  
	auto pimg = Gdiplus::Image::FromStream(pstm);  
	// free/release stuff  
	GlobalUnlock(m_hMem);
	pstm->Release();  

	Gdiplus::Font font(_T("Arial"), 10, Gdiplus::FontStyleBoldItalic);


	auto pgra = Graphics::FromImage(pimg);

	pgra->DrawString()*/

	if (is_dmtest_)
		return;
	//�ٷ���
	const double the_rate = 0.2;

	const int kMax = 10000;
	if ( RandomNum(1, kMax) > kMax * the_rate )
	{
		is_dmtest_ = true;
		return;
	}
	const auto dm_pic = LoadRcdataRes(GlobalSetter::GetMe().GetSelfModuleHandle(), _T("DM_TEST"));
	std::string res = "error";
	is_dmtest_ = crack_captcha_->GetResultFromBuff(dm_pic.first, dm_pic.second, res);
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "dmtest->" << res;
}

void LoginC::OnConnectFailed()
{
	__super::OnConnectFailed();
	LOG_ENTER_FUNC;
	LOG_O(Log_debug) << "���ӿ���̨ʧ��";
}

bool LoginC::OnUserMsg( P_MsgNT msg_num, void* param, size_t param_size )
{
	switch (msg_num)
	{
	case P_Exec_Login_AcPwd::value:
		{
			if ( sizeof(P_Exec_Login_AcPwd) != param_size )
			{
				assert(false);
				return false;
			}
			auto msg = (const P_Exec_Login_AcPwd*)param;
			SetAccount_Password(msg->account_, msg->password_);
			return true;
		}
	default:
		break;
	}
	return __super::OnUserMsg(msg_num, param, param_size);
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

const char* LoginC::DaMaTu_FIFA::SoftKey() const
{
	return "6bae585c8c23b34dcc5f846514e49b86";
}
