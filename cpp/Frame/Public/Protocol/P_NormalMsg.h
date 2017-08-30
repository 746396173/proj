#pragma once
#include "stdafx.h"
#include "P_Defines.h"
#include "../DependSelfLib.h"

//account
struct P_Modify_Account{
	enum 
	{
		value = 1
	};

	bool			auto_run_script_;					//�Ƿ��Զ����нű�
	char			account_[kAccountMaxLen + 1];
	char			password_[kPasswordMaxLen + 1];
	char			service_name_[50];
};

//���ز���DLL
struct P_Exec_TestLoadLib{
	P_Exec_TestLoadLib();
	enum
	{
		value = 2
	};
	char			str_dll_full_file_path_[MAX_PATH];		//dll��ȫ·��
};
//ж�ز���DLL
struct P_Exec_TestUnloadLib
{
	enum
	{
		value = 3
	};
};

//����Lua�еĺ�����LuaTest
struct P_Exec_CallLuaFunction
{
	P_Exec_CallLuaFunction();
	enum
	{
		value = 4
	};
	enum
	{
		kStrSize = 100
	};
	char			call_func_name[kStrSize];
	char			func_param[kStrSize];
};

struct P_Exec_CallLuaFuncResult : public P_Exec_CallLuaFunction
{
	P_Exec_CallLuaFuncResult();
	enum
	{
		value = 5
	};
	
	char			func_result[kStrSize];
};

//������Ϣ
struct P_Exec_MatchInfo
{
	enum
	{
		value = 6
	};
	time_t				time_match_begin;			//������ʼʱ��
	time_t				time_match_end;				//��������ʱ��
	int					match_cnt;					//��������
};

//��Ϸ����id
struct P_Exec_GameProccessInfo
{
	enum
	{
		value = 7
	};

	DWORD				login_client_proccess_id_;			//��½����ID
	DWORD				self_process_id_;
};

struct P_Exec_Login_AcPwd{
	enum 
	{
		value = 8
	};

	char			account_[kAccountMaxLen + 1];
	char			password_[kPasswordMaxLen + 1];
};
