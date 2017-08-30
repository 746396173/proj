// LoginAssist.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <Common/LogOut.h>
#include <Common/UsefulFunc.h>
#include "Addr.h"
#include <Common/EnsureCleanup.h>
#include <Communicate/LLH_Defines.h>

void Hook(DWORD dwHookAddr,LPVOID pfun)
{
	try
	{
		unsigned char code = 0xe9;
		DWORD dwDoHookAddr = (DWORD)(void*)pfun;
		DWORD dwcAddr = dwDoHookAddr - dwHookAddr - 1 - 4;

		// �жϵ�ǰ��ַ�Ƿ�hook
		unsigned char readcode;
		ReadProcessMemory((void*)-1,(void*)dwHookAddr,&readcode,sizeof(readcode),NULL);

		if( readcode == code )
		{
			DWORD	dwReadAddr = 0;
			ReadProcessMemory((void*)-1,(void*)(dwHookAddr+1),&dwReadAddr,sizeof(dwReadAddr),NULL);

			if( dwReadAddr == dwcAddr )
			{
				return ;
			}
		}

		WriteProcessMemory((void*)-1,(void*)dwHookAddr,&code,1,NULL);

		WriteProcessMemory((void*)-1,(void*)(dwHookAddr+1),&dwcAddr,4,NULL);
	}
	catch (...)
	{
		MessageBoxA(NULL,"������","������",MB_OK);
	}
}

void CheckModule()
{
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "��ȫģ�������";
	auto& file_map = LLH_MemFileMap::GetMe();
	auto commu = file_map.WriteAsCommu();
	if ( !commu )
	{
		LOG_O(Log_debug) << "commu is zero";
		return;
	}
	commu->safe_check_done_ = true;
}

_declspec(naked) void HookCheckModule()
{
	__asm
	{
		pushfd
			pushad

			lea eax, CheckModule
			call eax
	}

	__asm
	{
		popad
			popfd

			XOR EAX,EAX
			POP ESI
			LEAVE
			RETN
	}
}

void OnLoginFailed( const wchar_t* login_str, UINT char_cnt )
{
	static bool enter_once = false;

	if (enter_once)
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "�Ѿ�������";
		return;
	}
	if ( !login_str || char_cnt <= 0 )
		return;
	enter_once = true;
	auto enter_ptr = &enter_once;
	auto func = [enter_ptr](){
		*enter_ptr = false;
	};
	CleanAtScopeExit<decltype(func)> at_exit(func);
	
	
	/*
#ifndef _LOG_OUTPUT_EMPTY
	CStringW str_output;
	str_output.Format(L"zhp:OnLoginFailed,�ַ�������%d,%s", char_cnt, login_str);
	OutputDebugStringW(str_output);
#endif
*/

	static const wchar_t kPwdError[] = L"���벻��ȷ";
	static const wchar_t kFreezeAc[] = L"����QQ��ʱ�޷���¼";

	const auto kLoginStrEnd = login_str + char_cnt;
	auto it = std::search(login_str, kLoginStrEnd, kPwdError, kPwdError + _countof(kPwdError) - 1);
	if ( it != kLoginStrEnd )
	{
		//LOG_ENTER_FUNC;
		//LOG_O(Log_trace) << "�������,������->" << login_str;
#ifndef _LOG_OUTPUT_EMPTY
		CStringW str_tmp;
		str_tmp.Format(L"zhp:���벻��ȷ��������->%s", login_str);

		OutputDebugStringW(str_tmp);
#endif		
		auto& file_map = LLH_MemFileMap::GetMe();
		auto commu = file_map.WriteAsCommu();
		if ( !commu )
		{
#ifndef _LOG_OUTPUT_EMPTY
			OutputDebugString(_T("zhp:commu error"));
#endif
			return;
		}
		commu->pwd_input_error_ = true;
		return;
	}
	it = std::search(login_str, kLoginStrEnd, kFreezeAc, kFreezeAc + _countof(kFreezeAc) - 1);
	if ( it != kLoginStrEnd )
	{
#ifndef _LOG_OUTPUT_EMPTY
		CStringW str_tmp;
		str_tmp.Format(L"zhp:�����ʺ���->%s", login_str);

		OutputDebugStringW(str_tmp);
#endif
		auto& file_map = LLH_MemFileMap::GetMe();
		auto commu = file_map.WriteAsCommu();
		if ( !commu )
		{
#ifndef _LOG_OUTPUT_EMPTY
			OutputDebugString(_T("zhp:commu error"));
#endif
			return;
		}
		commu->ac_freeze_ = true;
		return;
	}
}

_declspec(naked) void HookCheckLoginResult()
{
	__asm
	{
		pushfd
			pushad
			mov ebp, esp
			push [ebp+0x2c]
			push [ebp+0x28]
		lea eax, OnLoginFailed
			call eax
			add esp, 8
	}

	__asm
	{
		popad
			popfd

			mov edi,edi
			push ebp
			mov ebp, esp

			mov eax, g_pCheckLoginFailed
			add eax, 5
			jmp eax
	}
}

void OnCheckLoginSucceed( DWORD flag )
{
	/*LOG_ENTER_FUNC;
	LOG_O(Log_trace) << flag;
	if ( 0 != flag )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "��½�ɹ�";
		auto& file_map = LLH_MemFileMap::GetMe();
		auto commu = file_map.WriteAsCommu();
		if ( !commu )
		{
			LOG_O(Log_debug) << "commu is zero";
			return;
		}
		commu->login_succeed_ = true;
	}*/
}

_declspec(naked) void HookCheckLoginSucceed()
{
	__asm
	{
		pushfd
			pushad
			push eax
			lea eax, OnCheckLoginSucceed
			call eax
			add esp, 4
	}

	__asm
	{
		popad
			popfd

			POP ESI
			LEAVE
			RETN 0xC
	}
}

bool InitCodeHooker()
{
	//return true;
	//��ȫ������
	{
		auto tcls = LoadLibrary(GetModulePath(nullptr) + _T("SecureCheck.dll"));
		assert(tcls);
		if ( !tcls )
		{
			return false;
		}
		Hook((DWORD)tcls + g_o_HookSafeCheckDone, HookCheckModule);
	}
	//��½ʧ�ܵ��ж�
	{
		auto oleaut32 = LoadLibrary(_T("oleaut32.dll"));
		assert(oleaut32);
		if ( !oleaut32 )
			return false;
		g_pCheckLoginFailed = GetProcAddress(oleaut32, "SysAllocStringLen");
		if ( !g_pCheckLoginFailed )
			return false;
		Hook((DWORD)g_pCheckLoginFailed, HookCheckLoginResult);
	}
	//��½�ɹ����ж�
	/*{
		auto ssoc = LoadLibrary(_T("SSOCommon.dll"));
		if ( !ssoc )
			return false;
		Hook((DWORD)ssoc + g_o_login_succeed, HookCheckLoginSucceed);
	}*/
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "login helper hook�ɹ�";
	return true;
}