// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <Common/LogOut.h>
#include <Common/UsefulClass.h>
#include <boost/thread.hpp>
#include "LoginH_Lua.h"
#include "LoginAssistC.h"
#include <Communicate/LLH_Defines.h>
#include "BugTrace.h"

bool InitCodeHooker();
/*
void IoRun(){
	LOG_ENTER_FUNC;
	try{
		LOG_O(Log_info) << "thread id=" << GetCurrentThreadId();
		
		LoginH_Lua lua;
		if ( !lua.InitScript(_T("LoginH.dll"), _T("main.lua")) )
		{
			LOG_ENTER_FUNC;
			LOG_O(Log_error) << "login helper init lua failed";
			return;
		}
		boost::shared_ptr<LoginAssistC> con_account(new LoginAssistC);
		con_account->ConnectAsync();
		auto& io_s = GetIoService();
		//�ָ���Ϸ�߳�
		//SupendProcess(false);
		LOG_O(Log_trace) << "������½֮��ʼִ��io run";
		io_s.run();
		LOG_O(Log_info) << "ִ���߳������������ر�����log���";
	}
	catch ( std::exception& e )
	{
		LOG_ENTER_FUNC;
		auto err_info = e.what();
		LOG_O(Log_fatal) << err_info;
	}
	catch (...){
		LOG_O(Log_fatal) << "IoRun�е�io_service::run�������쳣���ر�����log���";
	}
}*/

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{
	using namespace AheadLib;
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		ModuleHelper::GetMe().SetSelfModuleHandle(hModule);
		LogSinkInitor_dbgview::InstanceHelper log_dbgview_creator;
		DisableThreadLibraryCalls(hModule);
		LOG_ENTER_FUNC;
		LOG_O(Log_info) << "process attach";
		/*boost::thread t([](){
			PreIoRun(&IoRun);
		});*/
		/*if ( !InitCodeHooker() )
		{
			assert(false);
			return FALSE;
		}*/
		/*auto& file_map = LLH_MemFileMap::GetMe();
		VERIFY(file_map.CreateFileMap());*/
		return Load();
		
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_info) << "process dettach";
		LogSinkInitor::CloseAllLogOutput();
		Free();
	}

	return TRUE;
}
