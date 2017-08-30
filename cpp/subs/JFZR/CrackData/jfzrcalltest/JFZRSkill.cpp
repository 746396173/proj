#include "StdAfx.h"
#include "JFZRSkill.h"

extern BOOL _ReadProcessMemory(DWORD dwReadAddr,void* pReadData,DWORD dwReadlen);
extern BOOL _WriteProcessMemory(DWORD dwWriteAddr,void* pWriteData,DWORD dwWritelen);

JFZRSkill::JFZRSkill(void)
{
	memset(m_SkillObj,0,sizeof(m_SkillObj));
	m_dwSkillObjIndex = 0;
}

JFZRSkill::~JFZRSkill(void)
{
}

/*++
$ ==>    261B62A4    0137A700  JFZR.0137A700
$+4      261B62A8    1C042FA4  UNICODE "SpinClaw"
$+8      261B62AC    00000000
$+C      261B62B0    00000000
$+10     261B62B4    00000000
$+14     261B62B8    00000008
$+18     261B62BC    0000000F		// �������Ƴ���
$+1C     261B62C0    00000000
$+20     261B62C4    00000015		// ���ܵȼ�
$+24     261B62C8    00000000
$+28     261B62CC    00000000
$+2C     261B62D0    00000000
$+30     261B62D4    00000000
$+34     261B62D8    00000000
$+38     261B62DC    000AE351
$+3C     261B62E0    00000000
$+40     261B62E4    00000000
$+44     261B62E8    3C21F361		// ����ID
--*/



bool JFZRSkill::TraverseSkill(void)
{
	m_dwSkillObjIndex = 0;
	csTxt = "";

	DWORD	dwSkillBaseAddr = JFZR_REVERSAL_ROLE_OBJ_ADDR;

	// sp

	DWORD	dwIndex = 0;
	DWORD	dwSkillSp = 0;
	GAME_STRUCT_ARRAY_POINT		theSkillSpObj = {0};

	_ReadProcessMemory(dwSkillBaseAddr+JFZR_REVERSAL_SKILL_SP_OFFSET1___+JFZR_REVERSAL_SKILL_SP_OFFSET2___,&theSkillSpObj,sizeof(theSkillSpObj));
	ASSERT(theSkillSpObj.str_dwEndAddr1);

	_ReadProcessMemory(dwSkillBaseAddr+JFZR_REVERSAL_SKILL_SP_OFFSET1___+JFZR_REVERSAL_SKILL_SP_INDEX_OFFSET___,&dwIndex,1);

	_ReadProcessMemory(theSkillSpObj.str_dwBeginAddr+dwIndex,&dwSkillSp,sizeof(dwSkillSp));

	char szPrint[256] = {0};
	sprintf_s(szPrint,"sp = %d\r\n",dwSkillSp);
	csTxt += szPrint;

	// ����ɾ�����Ը���
	{
		dwSkillBaseAddr += JFZR_REVERSAL_SKILL_OFFSET1+JFZR_REVERSAL_SKILL_OFFSET2;

		DWORD dwCmpFlag = 0;		
		dwSkillBaseAddr = GetSkillObjAddr(dwSkillBaseAddr,&dwCmpFlag);	// ���ܱ����ķ��ʣ���ԭ�ȵĻ����ϣ�����һ�����ݲ�֪�α������CALL�����ַ�����ɷ���ԭ����Ҫ�ĵ�ַ
	}


	DWORD	dwSkillBeginAddr = 0;
	DWORD	dwSkillEndAddr = 0;
	_ReadProcessMemory(dwSkillBaseAddr,&dwSkillBeginAddr,sizeof(dwSkillBeginAddr));
	assert(dwSkillBeginAddr);
	_ReadProcessMemory(dwSkillBaseAddr+4,&dwSkillEndAddr,sizeof(dwSkillEndAddr));
	assert(dwSkillEndAddr);

	for (DWORD i=dwSkillBeginAddr; i<dwSkillEndAddr; i+=JFZR_REVERSAL_SKILL_OBJ_SIZE___,m_dwSkillObjIndex++)
	{
		char szReadData[256] = {0};
		DWORD dwNameLen = 0;
		_ReadProcessMemory(i+JFZR_REVERSAL_SKILL_OBJ_NAMELEN_OFFSET___,&dwNameLen,sizeof(dwNameLen));
		assert(dwNameLen);
		DWORD dwNameAddr = 0;

		if( dwNameLen > 7 )			// ���Ƴ��ȴ���7���洢����һ��ָ�����Ƶ�ָ��
		{
			_ReadProcessMemory(i+JFZR_REVERSAL_SKILL_OBJ_NAME_OFFSET___,&dwNameAddr,sizeof(dwNameAddr));
			assert(dwNameAddr);
			_ReadProcessMemory(dwNameAddr,szReadData,dwNameLen*2);
		}
		else						// ���Ƴ���С�ڵ���7���洢�ڵ�ǰ������
		{
			_ReadProcessMemory(i+JFZR_REVERSAL_SKILL_OBJ_NAME_OFFSET___,szReadData,dwNameLen*2);
		}

		DWORD dwLen = WideCharToMultiByte(CP_OEMCP,NULL,(LPCWSTR)szReadData,-1,NULL,0,NULL,FALSE);

		char* pszObjName = NULL;
		pszObjName = new char[dwLen+2];
		assert(pszObjName);

		if( pszObjName != NULL )
		{
			memset(pszObjName,0,dwLen+2);
			WideCharToMultiByte(CP_OEMCP,NULL,(LPCWSTR)szReadData,-1,pszObjName,dwLen,NULL,FALSE);
		}

		DWORD	dwGread = 0;
		_ReadProcessMemory(i+JFZR_REVERSAL_SKILL_OBJ_LEVEL_OFFSET___,&dwGread,sizeof(dwGread));

		DWORD	dwId = 0;
		_ReadProcessMemory(i+JFZR_REVERSAL_SKILL_OBJ_ID_OFFSET___,&dwId,sizeof(dwId));

		memcpy(m_SkillObj[m_dwSkillObjIndex].str_szSkillName,pszObjName,dwLen+1);
		memcpy(m_SkillObj[m_dwSkillObjIndex].str_szSkillNameEx,szReadData,dwLen*2+2);
		m_SkillObj[m_dwSkillObjIndex].str_dwSkillLevel	= dwGread;
		m_SkillObj[m_dwSkillObjIndex].str_dwSkillId		= dwId;
		m_dwSkillObjIndex++;

		if( pszObjName != NULL )
		{
			delete[] pszObjName;
			pszObjName = NULL;
		}

		// ����
		APPLE_SKILL	theAppleSkill = {0};
		_ReadProcessMemory(i,&theAppleSkill,sizeof(theAppleSkill));

		wchar_t wszPrint[256] = {0};
		swprintf_s(wszPrint,L"addr = %p  skill name = %s  level = %d  id = %p\r\n",i,GetString(&theAppleSkill.str_theId),theAppleSkill.str_dwLevel,theAppleSkill.str_dwSkillId);

		csTxt += wszPrint;
	}

	return true;
}

// �������ܣ���ȡ���ܶ���
// ����1���������ƣ�Ӣ�İ��
// ����ֵ�����ؼ��ܶ���
PJFZR_SKILL_OBJ JFZRSkill::GetSkillObj(char* pszskillname)
{
	TraverseSkill();
	for (DWORD i=0; i<m_dwSkillObjIndex; i++)
	{
		if( strcmp(m_SkillObj[i].str_szSkillName,pszskillname) == 0 )
		{
			return &m_SkillObj[i];
		}
	}
	return NULL;
}


JFZRTHIEFSkill::JFZRTHIEFSkill(void)
{

}

JFZRTHIEFSkill::~JFZRTHIEFSkill(void)
{

}
