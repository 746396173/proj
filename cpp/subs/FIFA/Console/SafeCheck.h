#pragma once
/*
@author zhp
@date 2014/6/10 15:24
@purpose for safe check
*/
#include "stdafx.h"
#include <Common/UsefulClass.h>
#include <CD_CommonFiles/CD_AntiCrack.h>

//��ֹ�������Լ��İ�ȫ����LPK
const char* const kMemMapName_CheckLpk = kCheckFileMapName;
//���ĳ���
const unsigned int kMemMap_ConstValue = kXorConstValue;
#ifdef OPEN_CHECK_LPK_
//��֤lpk��uuid string
const char* const kUuidStr_SafeCheckLpk = 
	"79a7b3c6-40a2-5267-8935-be0fb1a714bc";
#endif

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