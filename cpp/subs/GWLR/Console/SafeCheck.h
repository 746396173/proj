#pragma once
/*
@author zhp
@date 2014/6/10 15:24
@purpose for safe check
*/
#include "stdafx.h"
#include <Common/UsefulClass.h>
#include "../CrackData/CD_CommonFiles/CD_AntiCrack.h"

//��ֹ�������Լ��İ�ȫ����LPK
const char* const kMemMapName_CheckLpk = kCheckFileMapName;
//���ĳ���
const unsigned int kMemMap_ConstValue = kXorConstValue;
#ifdef OPEN_CHECK_LPK_
//��֤lpkb��uuid string
const char* const kUuidStr_SafeCheckLpk = 
	/*kUuidStr_SafeCheckLpk*/"1f987860-23f7-5ef0-865a-135df1e65aff";
#endif

//����������
const TCHAR* const kMainWndClsName = _T("fuckathecrack");

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