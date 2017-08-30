#pragma once
/*
@author zhp
@date 2014/6/10 15:24
@purpose for safe check
*/
#include "stdafx.h"
#include <Common/UsefulClass.h>
#include "../CrackData/AntiCrack/AntiCrack.h"

//��ֹ�������Լ��İ�ȫ����LPK
const char* const kMemMapName_CheckLpk = kCheckFileMapName;
//���ĳ���
const unsigned int kMemMap_ConstValue = kXorConstValue;
//��֤lpkb��uuid string
const char* const kUuidStr_SafeCheckLpk = 
	"ee18beaf-304a-5cac-88fd-30592703145f";

//����������
const TCHAR* const kMainWndClsName = _T("fuckthecrack");

class SafeCheckLpk : public Singleton<SafeCheckLpk, Singleton_MakeMe>{
public:
	SafeCheckLpk();
	~SafeCheckLpk();

public:
	//������֤lpk���ڴ�ӳ���ļ�
	bool CreateCheckLpkFileMap();
	//д����ֵ
	bool WriteValue( unsigned int value );
	//��֤LPK UUID�������Ƿ񱻸�д
	static bool SafeCheckLpkValid();
	//�ڴ�ӳ���ļ��Ƿ���Ч
	bool IsValid() const;

private:
	HANDLE				handle_file_map_;
	LPVOID				ptr_map_view_;
};