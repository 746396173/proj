#pragma once
/*
@author zhp
@date 2014/6/2 10:44
@purpose for login helper address
*/
#include "stdafx.h"

class tagHookSafeCheckDone{};
const unsigned int		g_o_HookSafeCheckDone(0x1DEBF);		//hook��ȫ������,SecureCheck.dll�����ƫ��
static HOOKPROC game_hook_call_back = nullptr;			//fszwd.dat,��Ҫѩ������λ��ַ
extern void*			g_pCheckLoginFailed;
//const int				g_o_login_succeed = 0xA24B;


struct GlobalSetter{
	static GlobalSetter& GetMe();
	void SetSelfModuleHandle(HMODULE hModule){
		hModule_ = hModule;
	}
	void SetIoThreadId(DWORD thrd_id){
		thrd_id_ = thrd_id;
	}
	DWORD GetCurProcessId(){
		return ::GetCurrentProcessId();
	}

	HMODULE hModule_;
	DWORD	thrd_id_;
};