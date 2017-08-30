#pragma once
/*
@author zhp
@date 2014/7/26 12:27
@purpose communicate of login.dll and LoginH.dll
*/
#include <Common/FileMap.h>
#include <Common/UsefulClass.h>

class LLH_MemFileMap : public MemFileMap, public Singleton<LLH_MemFileMap, Singleton_MakeMe>{
	//type definition
public:
	struct stCommunicate{
		bool			safe_check_done_;			//��ȫ���
		bool			pwd_input_error_;			//�����������
		bool			ac_freeze_;					//�ʺű�����
		bool			login_succeed_;				//��¼�ɹ�

		stCommunicate();
	};

public:
	LLH_MemFileMap();
	//Read
	const stCommunicate* ReadAsCommu() const;
	//Write
	stCommunicate* WriteAsCommu();
};