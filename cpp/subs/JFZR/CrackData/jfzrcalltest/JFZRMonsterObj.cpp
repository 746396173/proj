#include "StdAfx.h"
#include "JFZRMonsterObj.h"

DWORD	g_dwLocalObjAddr = 0;
CMyLock	g_theGetLOcalObjAddrLock;

JFZRMonsterObj	theMonsterObj;

JFZRMonsterObj::JFZRMonsterObj(void)
{
	bPrintcsTxtFlag = false;
	memset(m_MonsterObj,0,sizeof(m_MonsterObj));
	m_dwMonsterObjIndex = 0;
}

JFZRMonsterObj::~JFZRMonsterObj(void)
{
}

_declspec(naked) void HookGetLocalObjAddr()
{
	__asm
	{
		mov g_dwLocalObjAddr, ecx
	}
	__asm
	{
		PUSH EBP
		MOV EBP,ESP
		PUSH -0x1

		mov eax, JFZR_REVERSAL_LOCAL_OBJ_ADDR_HOOK
		add eax, 5
		jmp eax
	}
}

// �������󣬰��� �����е� ��ң�����谭�������Ʒ  ������ NPC�����
_declspec(naked) void TraverseLocalObj()	// 00850310
{
	__asm
	{
		MOV EAX,ECX
		MOV EDX,DWORD PTR DS:[EAX]                        ; oldnode
		CMP BYTE PTR DS:[EDX+0x19],0x0                    ; cmp byte ptr[oldnode+19],0
		JNZ SHORT local_end
		MOV ECX,DWORD PTR DS:[EDX+0x8]                    ; R
		CMP BYTE PTR DS:[ECX+0x19],0x0
		JNZ SHORT local_r
		MOV EDX,DWORD PTR DS:[ECX]                        ; P
		CMP BYTE PTR DS:[EDX+0x19],0x0
		JNZ SHORT local_p
		JMP SHORT local_1
		LEA ECX,DWORD PTR DS:[ECX]
local_1:
		MOV ECX,EDX
		MOV EDX,DWORD PTR DS:[ECX]
		CMP BYTE PTR DS:[EDX+0x19],0x0
		JE SHORT local_1
local_p:
		MOV DWORD PTR DS:[EAX],ECX
		RETN
local_r:
		MOV EDX,DWORD PTR DS:[EDX+0x4]                    ; L
		CMP BYTE PTR DS:[EDX+0x19],0x0
		JNZ SHORT local_2
local_3:
		MOV ECX,DWORD PTR DS:[EAX]                        ; mov ecx, oldnode
		CMP ECX,DWORD PTR DS:[EDX+0x8]                    ; cmp oldnode, [[oldnode+4]+8]
		JNZ SHORT local_2
		MOV DWORD PTR DS:[EAX],EDX
		MOV EDX,DWORD PTR DS:[EDX+0x4]
		CMP BYTE PTR DS:[EDX+0x19],0x0
		JE SHORT local_3
local_2:
		MOV DWORD PTR DS:[EAX],EDX
local_end:
		RETN
	}
}

CString  g_csTraverseObjTxt;
bool JFZRMonsterObj::TraverseObj(bool bPrintFlag)
{
	CString  csTraverseObjTxt;
	csTraverseObjTxt = "";
	m_dwMonsterObjIndex = 0;
	// ��ȡ��ǰ�����ַ
	Hook(JFZR_REVERSAL_LOCAL_OBJ_ADDR_HOOK,HookGetLocalObjAddr);		// 00876700    55              PUSH EBP

	while (!g_dwLocalObjAddr)
	{
		Sleep(10);
	}

	DWORD	dwBeginObjListAddr = 0;
	DWORD	dwNextObjListAddr = 0;
	DWORD	dwCurObjListAddr = 0;

	_ReadProcessMemory(g_dwLocalObjAddr+JFZR_REVERSAL_LOCAL_OBJ_LIST_OFFSET,&dwBeginObjListAddr,sizeof(dwBeginObjListAddr));
	_ReadProcessMemory(dwBeginObjListAddr,&dwBeginObjListAddr,sizeof(dwBeginObjListAddr));

	dwCurObjListAddr = dwBeginObjListAddr;
	while (true)
	{
		if( m_dwMonsterObjIndex > 0x100 )
		{
			break;
		}
		DWORD	dwTempObjAddr = 0;
		_ReadProcessMemory(dwCurObjListAddr+JFZR_REVERSAL_LOCAL_OBJ_OFFSET1,&dwTempObjAddr,sizeof(dwTempObjAddr));
		_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_OFFSET2,&dwTempObjAddr,sizeof(dwTempObjAddr));
		_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_OFFSET3,&dwTempObjAddr,sizeof(dwTempObjAddr));
		_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_OFFSET4___,&dwTempObjAddr,sizeof(dwTempObjAddr));

		if( dwTempObjAddr != 0 )
		{
			DWORD	dwSerial = 0;
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_SERIAL_OFFSET___,&dwSerial,sizeof(dwSerial));

// 			DWORD	dwJobNameLen_ = 0;
// 			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_JOBLEN_OFFSET___,&dwJobNameLen_,sizeof(dwJobNameLen_));
// 
// 			DWORD dwJobNameAddr = 0;
// 			if( dwJobNameLen_ > 7 )
// 			{
// 				_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOACL_OBJ_JOBNAME_OFFSET___,&dwJobNameAddr,sizeof(dwJobNameAddr));
// 			}
// 			else
// 			{
// 				dwJobNameAddr = dwTempObjAddr+JFZR_REVERSAL_LOACL_OBJ_JOBNAME_OFFSET___;
// 			}
// 
// 			char szReadJobData[256] = {0};
// 			_ReadProcessMemory(dwJobNameAddr,szReadJobData,dwJobNameLen_*2);
// 
// 			DWORD dwJobNameLen = WideCharToMultiByte(CP_OEMCP,NULL,(LPCWSTR)szReadJobData,-1,NULL,0,NULL,FALSE);
// 
// 			char* pszObjJobName = NULL;
// 			pszObjJobName = new char[dwJobNameLen+2];
// 
// 			if( pszObjJobName != NULL )
// 			{
// 				memset(pszObjJobName,0,dwJobNameLen+2);
// 				WideCharToMultiByte(CP_OEMCP,NULL,(LPCWSTR)szReadJobData,-1,pszObjJobName,dwJobNameLen,NULL,FALSE);
// 			}

			GAME_STRING_ID	theJobName;
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOACL_OBJ_JOBNAME_OFFSET___,&theJobName,sizeof(theJobName));



// 			DWORD dwObjNameLen_ = 0;
// 			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_NAMELEN_OFFSET___,&dwObjNameLen_,sizeof(dwObjNameLen_));
// 
// 			DWORD dwNameAddr = 0;
// 			if( dwObjNameLen_ > 7 )
// 			{
// 				_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOACL_OBJ_NAME_OFFSET___,&dwNameAddr,sizeof(dwNameAddr));
// 			}
// 			else
// 			{
// 				dwNameAddr = dwTempObjAddr+JFZR_REVERSAL_LOACL_OBJ_NAME_OFFSET___;
// 			}
// 
// 
// 			wchar_t	wszObjName[256] = {0};
// 			_ReadProcessMemory(dwNameAddr,wszObjName,dwObjNameLen_*2);
// 
// 			char szReadNameData[256] = {0};
// 			_ReadProcessMemory(dwNameAddr,szReadNameData,dwObjNameLen_*2);
// 
// 			DWORD dwObjNameLen = WideCharToMultiByte(CP_OEMCP,NULL,(LPCWSTR)szReadNameData,-1,NULL,0,NULL,FALSE);
// 
// 			char* pszObjName = NULL;
// 			pszObjName = new char[dwObjNameLen+2];
// 
// 			if( pszObjName != NULL )
// 			{
// 				memset(pszObjName,0,dwObjNameLen+2);
// 				WideCharToMultiByte(CP_OEMCP,NULL,(LPCWSTR)szReadNameData,-1,pszObjName,dwObjNameLen,NULL,FALSE);
// 			}

			GAME_STRING_ID	theObjName;
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOACL_OBJ_NAME_OFFSET___,&theObjName,sizeof(theObjName));

			float fx = 0.0f;
			float fy = 0.0f;
			float fz = 0.0f;

			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_X_OFFSET,&fx,sizeof(fx));
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_Z_OFFSET,&fz,sizeof(fz));
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_Y_OFFSET,&fy,sizeof(fy));

			DWORD dwTypeAddr = 0;

// 			DWORD dwObjTypeLen_ = 0;
// 			_ReadProcessMemory(dwTempObjAddr+JRZR_REVERSAL_LOCAL_OBJ_TYPELEN_OFFSET___,&dwObjTypeLen_,sizeof(dwObjTypeLen_));
// 			if( dwObjTypeLen_ > 7 )
// 			{
// 				_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_TPYE_OFFSET___,&dwTypeAddr,sizeof(dwTypeAddr));
// 			}
// 			else
// 			{
// 				dwTypeAddr = dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_TPYE_OFFSET___;
// 			}
// 
// 			char szReadTypeData[256] = {0};
// 			_ReadProcessMemory(dwTypeAddr,szReadTypeData,dwObjTypeLen_*2);
// 
// 			DWORD dwObjTypeLen = WideCharToMultiByte(CP_OEMCP,NULL,(LPCWSTR)szReadTypeData,-1,NULL,0,NULL,FALSE);
// 
// 			char* pszTypeName = NULL;
// 			pszTypeName = new char[dwObjTypeLen+2];
// 
// 			if( pszTypeName != NULL )
// 			{
// 				memset(pszTypeName,0,dwObjTypeLen+2);
// 				WideCharToMultiByte(CP_OEMCP,NULL,(LPCWSTR)szReadTypeData,-1,pszTypeName,dwObjTypeLen,NULL,FALSE);
// 			}

			GAME_STRING_ID theTypeName;
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_TPYE_OFFSET___,&theTypeName,sizeof(theTypeName));

			DWORD	dwCurrentHp = 0;
			DWORD	dwCeilingHp = 0;
			DWORD	dwCurrentMp = 0;
			DWORD	dwCeilingMp = 0;
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_HP_OFFSET___,&dwCurrentHp,sizeof(dwCurrentHp));
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_MAXHP_OFFSET___,&dwCeilingHp,sizeof(dwCeilingHp));
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_MP_OFFSET___,&dwCurrentMp,sizeof(dwCurrentMp));
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_MAXMP_OFFSET___,&dwCeilingMp,sizeof(dwCeilingMp));

			DWORD	dwLevel = 0;
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_ACTOR_OBJ_LEVEL_OFFSET___,&dwLevel,sizeof(dwLevel));

// 			if( /*strcmp(pszObjJobName,"") != 0 &&	*/		// ���˵�û��ְҵ������
// 				strcmp(pszObjJobName,"Alkee_Golem") != 0 &&	// ���˵� Dustin NPC
// 				strcmp(pszObjJobName,"Region02_Air_Strike_T01") != 0	// ���˵�����ը��
// 				 )

			BYTE bNpcType9D4 = 0;
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_NPC_TYPE_FLAG_2___,&bNpcType9D4,sizeof(bNpcType9D4));

			float	fDirectionX;
			float	fDirectionY;
			float	fDirectionZ;
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_DIRECTION_X_OFFSET___,&fDirectionX,sizeof(fDirectionX));
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_DIRECTION_Z_OFFSET___,&fDirectionZ,sizeof(fDirectionZ));
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_DIRECTION_Y_OFFSET___,&fDirectionY,sizeof(fDirectionY));

			GAME_STRING_ID theDefaultActionId;
			_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_LOCAL_OBJ_DEFAULT_ACTION_ID_OFFSET___,&theDefaultActionId,sizeof(theDefaultActionId));

			// ���ĳ���� ��Ҫ�� ������׻���S_Drill_Ep4��������NPC�����ڿ���ը�������Ա����˵��ˣ����⴦��
			// theMonsterObj.IsHitNpcId(wszObjName) ���������������ڣ��򷵻�true������������򷵻�false
			// bNpcType9D4 == 0 ����˱�־ = 1���򲻿ɴ��NPC
			// �������в����ڴ�NPC���� bNpcType9D4 = 0�����NPC�ɴ򣬾ͼ��뵽�ɴ�������
			if( ( ((!theMonsterObj.IsHitNpcId(GetString(&theObjName)) && bNpcType9D4 == 0) || wcscmp(GetString(&theTypeName),L"NPC") != 0)) || bPrintFlag == true )	// �Ƚ϶������ƣ���һ����־
			{
				try
				{
					memcpy(m_MonsterObj[m_dwMonsterObjIndex].str_szJobName,GetString(&theJobName),theJobName.str_dwStrLen*2+1);
					memcpy(m_MonsterObj[m_dwMonsterObjIndex].str_szObjName,GetString(&theObjName),theObjName.str_dwStrLen*2+1);
					memcpy(m_MonsterObj[m_dwMonsterObjIndex].str_szObjType,GetString(&theTypeName),theTypeName.str_dwStrLen*2+1);
					memcpy(m_MonsterObj[m_dwMonsterObjIndex].str_szDefaultActionId,GetString(&theDefaultActionId),theDefaultActionId.str_dwStrLen*2+1);
					
					m_MonsterObj[m_dwMonsterObjIndex].str_dwSerial = dwSerial;
					m_MonsterObj[m_dwMonsterObjIndex].str_fx = fx;
					m_MonsterObj[m_dwMonsterObjIndex].str_fy = fy;
					m_MonsterObj[m_dwMonsterObjIndex].str_fz = fz;
					m_MonsterObj[m_dwMonsterObjIndex].str_fDirectionX = fDirectionX;
					m_MonsterObj[m_dwMonsterObjIndex].str_fDirectionY = fDirectionY;
					m_MonsterObj[m_dwMonsterObjIndex].str_fDirectionZ = fDirectionZ;
					m_MonsterObj[m_dwMonsterObjIndex].str_dwCurrentHp = dwCurrentHp;
					m_MonsterObj[m_dwMonsterObjIndex].str_dwCeilingHp = dwCeilingHp;
					m_MonsterObj[m_dwMonsterObjIndex].str_dwCurrentMp = dwCurrentMp;
					m_MonsterObj[m_dwMonsterObjIndex].str_dwCeilingMp = dwCeilingMp;

				}
				catch(...)
				{
					assert(false);
				}
		
				if( bPrintFlag == true )
				{
					try
					{
						wchar_t wszPrint[1024] = {0};
						swprintf_s(wszPrint,L"[JFZR] obj addr = 0x%p job name = %s  obj name = %s  type name = %s status = %s serial = %p x = %f y = %f z = %f hp = %d mp = %d level = %d Direction x = %f y = %f z = %f \r\n",
							dwTempObjAddr,
							m_MonsterObj[m_dwMonsterObjIndex].str_szJobName,
							m_MonsterObj[m_dwMonsterObjIndex].str_szObjName,
							m_MonsterObj[m_dwMonsterObjIndex].str_szObjType,
							m_MonsterObj[m_dwMonsterObjIndex].str_szDefaultActionId,
							m_MonsterObj[m_dwMonsterObjIndex].str_dwSerial,
							m_MonsterObj[m_dwMonsterObjIndex].str_fx = fx,
							m_MonsterObj[m_dwMonsterObjIndex].str_fy = fy,
							m_MonsterObj[m_dwMonsterObjIndex].str_fz = fz,
							dwCurrentHp,
							dwCurrentMp,
							dwLevel,
							fDirectionX,
							fDirectionY,
							fDirectionZ);
						CString csTxt;
						csTxt = wszPrint;
						csTraverseObjTxt += csTxt;
					}
					catch (...)
					{
						//assert(false);
					}
				}
	
				if( wcsstr(m_MonsterObj[m_dwMonsterObjIndex].str_szObjType,L"UNKNOWN") != 0 )
				{
					// ItemExists
					DWORD	dwItemExistsAddr = 0;
					_ReadProcessMemory(dwTempObjAddr+JFZR_REVERSAL_ITEM_EXISTS_OFFSET___,&dwItemExistsAddr,sizeof(dwItemExistsAddr));
	
					try
					{
						if( dwItemExistsAddr != 0 )
						{
							// 10.30�ṹ���Ϊ�ͱ����Ľṹ��һ��
							APPLE_ITEM	  theAppleItem = {0};
							_ReadProcessMemory(dwItemExistsAddr,&theAppleItem,sizeof(theAppleItem));

							if( theAppleItem.str_dwItemObjAddr != 0 )
							{
								SDB_ITEM_INFO theItemInfo = {0};
								_ReadProcessMemory(theAppleItem.str_dwItemObjAddr,&theItemInfo,sizeof(theItemInfo));

								if( bPrintFlag == true )
								{
									wchar_t szItemName[256] = {0};
									swprintf_s(szItemName,L"[JFZR] id = %s, grade = %d, category = %d, level = %d, name = %s\r\n",
										GetVString(&theItemInfo.str_theId),
										theItemInfo.str_dwGrade,
										theItemInfo.str_dwCategory,
										theItemInfo.str_dwItemLevel,
										GetVString(&theItemInfo.str_theName)		// ��������OD��Ҳ�ǲ���ʶ�ģ������ֶδ���
										);
									CString csTxt;
									csTxt = szItemName;
									csTraverseObjTxt += csTxt;
								}
							}
						}
					}
					catch (...)
					{
						assert(false);
					}
				}

				m_dwMonsterObjIndex++;
			}
	
		}

		try
		{
			__asm
			{
				lea ecx, dwCurObjListAddr
				mov eax, TraverseLocalObj  
				call eax
			}

		}
		catch (...)
		{
			//assert(false);
			break;
		}
	
	
		if( *(DWORD*)dwBeginObjListAddr == dwCurObjListAddr )
		{
			break;
		}
	}

	if( bPrintFlag == true )
	{
		g_csTraverseObjTxt = csTraverseObjTxt;
	}
// 	unsigned char szCode[] = {JFZR_REVERSAL_LOCAL_OBJ_HOOK_OLD_CODE};
// 	_WriteProcessMemory(JFZR_REVERSAL_LOCAL_OBJ_ADDR_HOOK,szCode,5);

	return false;
}

// �������ܣ���ȡ��ͬ���Ͷ���ĸ���
// ����1���������ͣ��磺MISC��NPC
// ����ֵ�����ض���ĸ���
int JFZRMonsterObj::GetObjCount(wchar_t* pszObjType)
{
	int nCount = 0;
	for (DWORD i=0; i<m_dwMonsterObjIndex; i++)
	{
		if( wcscmp(m_MonsterObj[i].str_szObjType,pszObjType) == 0 && m_MonsterObj[i].str_dwCurrentHp > 0 )
		{
			nCount++;
		}
	}
	return nCount;
}

// �������ܣ���ȡ�ɹ����Ĺ������
// ����1����������
// ����2��Ҫ��ȡ����ĸ���
// ����ֵ������ʵ�ʷ��ض���ĸ���
int JFZRMonsterObj::GetArrayObj(OUT PJFZR_MONSTER_OBJ_STRUCT ptheObj, int nCount)
{
	if( bPrintcsTxtFlag == true )
		csTxt = "";
	int nLocalCount = 0;
	if( m_dwMonsterObjIndex == 0 )
	{
		return 0;
	}
	for (DWORD i = 0; i<m_dwMonsterObjIndex; i++)
	{
		if( nLocalCount < nCount )
		{
			if( wcscmp(m_MonsterObj[i].str_szObjType,ptheObj->str_szType) == 0 )
			{
				// str_dwCurrentHp == 0 ,1.��ϷNPC�� 2.�����Ѿ���������������δ����
				if( m_MonsterObj[i].str_dwCurrentHp == 0 && wcscmp(m_MonsterObj[i].str_szObjType,L"NPC") == 0 )
				{
					continue;
				}

				memcpy(ptheObj->str_theMonsterObj[nLocalCount].str_szJobName,m_MonsterObj[i].str_szJobName,wcslen(m_MonsterObj[i].str_szJobName)*2+1);
				memcpy(ptheObj->str_theMonsterObj[nLocalCount].str_szObjName,m_MonsterObj[i].str_szObjName,wcslen(m_MonsterObj[i].str_szObjName)*2+1);
				memcpy(ptheObj->str_theMonsterObj[nLocalCount].str_szObjType,m_MonsterObj[i].str_szObjType,wcslen(m_MonsterObj[i].str_szObjType)*2+1);
				memcpy(ptheObj->str_theMonsterObj[nLocalCount].str_szDefaultActionId,m_MonsterObj[i].str_szDefaultActionId,wcslen(m_MonsterObj[i].str_szDefaultActionId)*2+1);
				ptheObj->str_theMonsterObj[nLocalCount].str_dwSerial	= m_MonsterObj[i].str_dwSerial;
				ptheObj->str_theMonsterObj[nLocalCount].str_fx	= m_MonsterObj[i].str_fx;
				ptheObj->str_theMonsterObj[nLocalCount].str_fy	= m_MonsterObj[i].str_fy;
				ptheObj->str_theMonsterObj[nLocalCount].str_fz	= m_MonsterObj[i].str_fz;
				ptheObj->str_theMonsterObj[nLocalCount].str_dwCurrentHp	= m_MonsterObj[i].str_dwCurrentHp;
				ptheObj->str_theMonsterObj[nLocalCount].str_dwCeilingHp	= m_MonsterObj[i].str_dwCeilingHp;
				ptheObj->str_theMonsterObj[nLocalCount].str_dwCurrentMp	= m_MonsterObj[i].str_dwCurrentMp;
				ptheObj->str_theMonsterObj[nLocalCount].str_dwCeilingMp	= m_MonsterObj[i].str_dwCeilingMp;

				wchar_t wszPrint[256] = {0};
				swprintf_s(wszPrint,L"[JFZR] obj name = %s  status = %s obj serial = %p x = %f y = %f z = %f\r\n",
											ptheObj->str_theMonsterObj[nLocalCount].str_szObjName,
											ptheObj->str_theMonsterObj[nLocalCount].str_szDefaultActionId,
											ptheObj->str_theMonsterObj[nLocalCount].str_dwSerial,
											ptheObj->str_theMonsterObj[nLocalCount].str_fx,
											ptheObj->str_theMonsterObj[nLocalCount].str_fy,
											ptheObj->str_theMonsterObj[nLocalCount].str_fz);
				//OutputDebugStringW(wszPrint);
				if( bPrintcsTxtFlag == true )
					csTxt += wszPrint;
				nLocalCount++;
			}
		}
	}
	return nLocalCount;
}



bool JFZRMonsterObj::SetUnHitNpcId(const wchar_t* pwszNpcId)
{
	POSITION pos = m_str_NpcIdList.GetHeadPosition();
	for (int i=0;i < m_str_NpcIdList.GetCount();i++)
	{
		PJFZR_NPC_ID ptheNpcId = &m_str_NpcIdList.GetNext(pos);

		if( wcscmp(ptheNpcId->str_szNpcId,pwszNpcId) == 0 )
		{
			return false;
		}
	}

	JFZR_NPC_ID theNpcId;
	wcscpy_s(theNpcId.str_szNpcId,256,pwszNpcId);
	m_str_NpcIdList.AddHead(theNpcId);
	return true;
}

bool JFZRMonsterObj::IsHitNpcId(const wchar_t* pwszNpcId)
{

	POSITION pos = m_str_NpcIdList.GetHeadPosition();
	for (int i=0;i < m_str_NpcIdList.GetCount();i++)
	{
		PJFZR_NPC_ID ptheNpcId = &m_str_NpcIdList.GetNext(pos);

		if( wcscmp(ptheNpcId->str_szNpcId,pwszNpcId) == 0 )
		{
			return true;
		}
	}

	return false;
}