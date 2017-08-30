// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <cassert>
#include "Protocol/HijackXmlCfg.h"
#include <Common/UsefulFunc.h>

HMODULE	g_module = nullptr;
//��ǰ�������Ƿ�Ϊָ������Ϸ��
bool IsSpecifyProcessName( LPCTSTR specifyName )
{
	if ( !specifyName )
		return false;

	auto module_handle = GetModuleHandle(nullptr);
	if ( !module_handle )
	{
		assert(false);
		return false;
	}
	TCHAR name_buff[MAX_PATH];
	name_buff[0] = 0;
	GetModuleFileName(module_handle, name_buff, sizeof(name_buff));
	auto it = _tcsrchr(name_buff, _T('\\'));
	if ( !it )
	{
		assert(false);
		return false;
	}
	return 0 == _tcsicmp(++it, specifyName);
}

//�������DLL
void LoadGameDll( LPCTSTR full_dll_file_name )
{
	if ( !full_dll_file_name )
	{
		assert(false);
		return;
	}
	VERIFY(nullptr != LoadLibrary(full_dll_file_name));
}

const stHijackDllCfg& GetCfg()
{
	struct Helper
	{
		Helper(){
			TCHAR name_buff[MAX_PATH];
			name_buff[0] = 0;
			if (g_module)
			{
				VERIFY(GetModulePath(name_buff, sizeof(name_buff), g_module));
				_tcscat_s(name_buff, stHijackDllCfg::GetCfgFileName());
			}
			XmlCfg::RestoreHelper<stHijackDllCfg> helper(&cfg, CT2CA(name_buff));
		}
		stHijackDllCfg		cfg;
	};
	static Helper helper;
	return helper.cfg;
}

struct stProfileImpl : stHijackProfile{
	CString		str_game_name_;
	CString		str_dll_path_;
};

const stProfileImpl& GetProfile()
{
	struct Helper
	{
		Helper(){
			TCHAR name_buff[MAX_PATH];
			name_buff[0] = 0;
			if (g_module)
			{
				VERIFY(GetModulePath(name_buff, sizeof(name_buff), g_module));
				_tcscat_s(name_buff, stHijackProfile::GetCfgFileName());
				cfg.SetProfile(std::string(CT2CA(name_buff)));
				cfg.Load();
				cfg.str_game_name_ = CA2CT(cfg.injected_game_name_.c_str());
				cfg.str_dll_path_ = CA2CT(cfg.inject_dll_full_path_.c_str());
			}
			
		}
		stProfileImpl		cfg;
	};
	static Helper helper;
	return helper.cfg;
}

//�õ��ܹ���ע��Ľ�����
LPCTSTR GetInjectedGameName()
{
	return 
#ifdef HIJACK_DLL_XML_
		GetCfg().injected_game_name_;
#else
		GetProfile().str_game_name_;
#endif
}
//�õ�ע�����ϷDLL��ȫ·��
LPCTSTR GetInjectDllFullPath()
{
	return 
#ifdef HIJACK_DLL_XML_
		GetCfg().inject_dll_full_path_;
#else
		GetProfile().str_dll_path_;
#endif
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace AheadLib{
	BOOL WINAPI Load();
	VOID WINAPI Free();
}
// ��ں���
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{
	using namespace AheadLib;
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		g_module = hModule;
		DisableThreadLibraryCalls(hModule);
		if (IsSpecifyProcessName(GetInjectedGameName()))
		{
			LoadGameDll(GetInjectDllFullPath());
		}
		return Load();
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		g_module = nullptr;
		Free();
	}
	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

