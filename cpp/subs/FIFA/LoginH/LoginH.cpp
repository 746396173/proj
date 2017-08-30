// LoginH.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <Common/Hooker.h>
#include <Common/UsefulFunc.h>
#include "Addr.h"
#include <Protocol/P_Defines.h>
#include <string>
#include <Common/LogOut.h>
#include "LoginAssistC.h"
#include <Communicate/LLH_Defines.h>

void* Hooker_SafeCheckDone( IHooker& hooker )
{
	/*LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "��½������";

	struct Helper{
		Helper(){
			auto str_src = GenUuidStr(kLogin_SafeCheckEventName);
			str_event_name_ = CA2CT(str_src.c_str());
		}

		CString			str_event_name_;
	};
	static Helper helper;
	auto handle = ::CreateEvent(nullptr, FALSE, TRUE, helper.str_event_name_);
	bool res = ERROR_ALREADY_EXISTS != GetLastError();

	CString str_tmp;
	str_tmp.Format(_T("zhp:create event,handle->%u\tres->%d"), handle, res);
	OutputDebugString(str_tmp);*/
	
	/*GetIoService().post([](){
		auto login_assist = LoginAssistC::GetInstance();
		if ( !login_assist )
		{
			assert(false);
			LOG_ENTER_FUNC;
			LOG_O(Log_error) << "login assist������";
			return;
		}
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "��½����֮��½�ɹ�";
		login_assist->GetLoginAssistOper().ThisMemCall(nullptr, "SafeCheckDone", nullptr);
	});*/
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "��½����֮��ȫ������";
	/*auto& file_map = LLH_MemFileMap::GetMe();
	if ( !file_map.IsValid() )
	{
		LOG_O(Log_error) << "�ڴ�ӳ���ļ�������Ч״̬";
		return hooker.GetCodeOrig();
	}
	auto commu = file_map.WriteAsCommu();
	if ( !commu )
	{
		LOG_O(Log_error) << "commuΪ��";
		return hooker.GetCodeOrig();
	}
	assert(!commu->safe_check_done_);
	commu->safe_check_done_ = true;*/
	return hooker.GetCodeOrig();
}

void* Hooker_LoginResult( IHooker& hooker )
{
	auto ambient = hooker.GetAmbient();
	if ( !ambient )
		return hooker.GetCodeOrig();

	return hooker.GetCodeOrig();
}

bool InitCodeHooker()
{
	//return true;
	auto& hooker_factory = HookerFactory::GetMe();
	//��ȫ������
	{
		auto tcls = LoadLibrary(GetModulePath(nullptr) + _T("SecureCheck.dll"));
		assert(tcls);
		if ( !tcls )
		{
			return false;
		}
		static auto hooker_gain_CaptchaPic = hooker_factory.CreateCodeHooker<tagHookSafeCheckDone
		>((void*)((char*)tcls + g_pHookSafeCheckDone),
		Hooker_SafeCheckDone, false);
	}
	//��½���
	/*{
		auto oleaut32 = LoadLibrary(_T("oleaut32.dll"));
		assert(oleaut32);
		if ( !oleaut32 )
			return false;
		auto func_addr = GetProcAddress(oleaut32, "SysAllocStringLen");
		if ( !func_addr )
			return false;
		static auto hooker_login_res = hooker_factory.CreateCodeHooker<tagHookSafeCheckDone
		>((void*)((char*)func_addr),
		Hooker_LoginResult, false);
	}*/
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "login helper hook�ɹ�";
	return true;
}