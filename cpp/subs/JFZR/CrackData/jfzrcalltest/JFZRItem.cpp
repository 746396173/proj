#include "StdAfx.h"
#include "JFZRItem.h"


JFZRItem::JFZRItem(void)
{
}

JFZRItem::~JFZRItem(void)
{
}


CString		g_csItemPrintStr;

FLOAT		g_fItemStatusValue = 0.0f;

void ItemValuePrint(DWORD lpSubTreeRoot)
{
	ITEM_STATUS_VALUE	theItemStatusValue = {0};
	_ReadProcessMemory(lpSubTreeRoot,&theItemStatusValue,sizeof(theItemStatusValue));

	wchar_t	wszPrint[256] = {0};
	swprintf_s(wszPrint,L"��Ʒ��������: status = %s value = %f\r\n",GetString(&theItemStatusValue.str_theStatusId),theItemStatusValue.str_fValue);

	if( wcscmp(L"AttackPower",GetString(&theItemStatusValue.str_theStatusId)) == 0 )
		g_fItemStatusValue = theItemStatusValue.str_fValue;
	
	g_csItemPrintStr += wszPrint;
}

DWORD JFZRItem::TraverseItem2(int nType)
{
	DWORD	dwBagItemAddr = 0;
	_ReadProcessMemory(JFZR_REVERSAL_ROLE_OBJ_ADDR+JFZR_REVERSAL_ITEM_BAG_OFFSET1+JFZR_REVERSAL_ITEM_BAG_OFFSET2,&dwBagItemAddr,sizeof(dwBagItemAddr));
	assert(dwBagItemAddr);
	_ReadProcessMemory(dwBagItemAddr+JFZR_REVERSAL_ITEM_BAG_OFFSET3+JFZR_REVERSAL_ITEM_BAG_OFFSET4,&dwBagItemAddr,sizeof(dwBagItemAddr));
	assert(dwBagItemAddr);

	DWORD	dwCurItemAddr = 0;
	DWORD	dwEndItemAddr = 0;

	switch(nType)
	{
	case  1:	// ��ͨ
		{
			g_csItemPrintStr = "��ͨ//\r\n";
			_ReadProcessMemory(dwBagItemAddr,&dwCurItemAddr,sizeof(dwCurItemAddr));
			_ReadProcessMemory(dwBagItemAddr+4,&dwEndItemAddr,sizeof(dwEndItemAddr));
		}
		break;
	case 2:		// ����Ʒ
		{
			g_csItemPrintStr += "����Ʒ//\r\n";
			_ReadProcessMemory(dwBagItemAddr+0x10,&dwCurItemAddr,sizeof(dwCurItemAddr));
			_ReadProcessMemory(dwBagItemAddr+0x14,&dwEndItemAddr,sizeof(dwEndItemAddr));
		}
		break;
	case 3:		// ����
		{
			g_csItemPrintStr += "����//\r\n";
			_ReadProcessMemory(dwBagItemAddr+0x20,&dwCurItemAddr,sizeof(dwCurItemAddr));
			_ReadProcessMemory(dwBagItemAddr+0x24,&dwEndItemAddr,sizeof(dwEndItemAddr));
		}
		break;
	case 4:		// ����
		{
			g_csItemPrintStr += "����//\r\n";
			_ReadProcessMemory(dwBagItemAddr+0x30,&dwCurItemAddr,sizeof(dwCurItemAddr));
			_ReadProcessMemory(dwBagItemAddr+0x34,&dwEndItemAddr,sizeof(dwEndItemAddr));
		}
		break;
	case 5:		// ʱװ1,2,3
		{
			g_csItemPrintStr += "ʱװ//\r\n";
			_ReadProcessMemory(dwBagItemAddr+0x40,&dwCurItemAddr,sizeof(dwCurItemAddr));
			_ReadProcessMemory(dwBagItemAddr+0x44,&dwEndItemAddr,sizeof(dwEndItemAddr));
		}
		break;
	case 6:		// ����װ��
		{
			g_csItemPrintStr += "װ��//\r\n";
			_ReadProcessMemory(JFZR_REVERSAL_ROLE_OBJ_ADDR+JFZR_REVERSAL_ITEM_BAG_OFFSET1+JFZR_REVERSAL_ITEM_BAG_OFFSET2,&dwBagItemAddr,sizeof(dwBagItemAddr));
			assert(dwBagItemAddr);
			_ReadProcessMemory(dwBagItemAddr+JFZR_REVERSAL_EQUIP_ITEM_OFFSET3+JFZR_REVERSAL_EQUIP_ITEM_OFFSET4,&dwBagItemAddr,sizeof(dwBagItemAddr));
			assert(dwBagItemAddr);
			_ReadProcessMemory(dwBagItemAddr+0x0,&dwCurItemAddr,sizeof(dwCurItemAddr));
			_ReadProcessMemory(dwBagItemAddr+0x4,&dwEndItemAddr,sizeof(dwEndItemAddr));
		}
		break;
	case 7:		// ����ʱװ
		{
			g_csItemPrintStr += "ʱװ//\r\n";
			_ReadProcessMemory(JFZR_REVERSAL_ROLE_OBJ_ADDR+JFZR_REVERSAL_ITEM_BAG_OFFSET1+JFZR_REVERSAL_ITEM_BAG_OFFSET2,&dwBagItemAddr,sizeof(dwBagItemAddr));
			assert(dwBagItemAddr);
			_ReadProcessMemory(dwBagItemAddr+JFZR_REVERSAL_EQUIP_ITEM_OFFSET3+JFZR_REVERSAL_EQUIP_ITEM_OFFSET4,&dwBagItemAddr,sizeof(dwBagItemAddr));
			assert(dwBagItemAddr);
			_ReadProcessMemory(dwBagItemAddr+0x10,&dwCurItemAddr,sizeof(dwCurItemAddr));
			_ReadProcessMemory(dwBagItemAddr+0x14,&dwEndItemAddr,sizeof(dwEndItemAddr));
		}
		break;
	default:
		{
			assert(false);
		}
	}

	assert(dwCurItemAddr);
	assert(dwEndItemAddr);

	int nItemCount = (int)((dwEndItemAddr-dwCurItemAddr)/JFZR_REVERSAL_ITEM_OBJ_SIZE___);		// 10.30��Ʒ�ṹ���С�ı�
	for (int i=0; i<nItemCount; i++,dwCurItemAddr+=JFZR_REVERSAL_ITEM_OBJ_SIZE___)
	{
		APPLE_ITEM	theAppleItem = {0};
		_ReadProcessMemory(dwCurItemAddr,&theAppleItem,sizeof(theAppleItem));
		
		if( theAppleItem.str_llSerial != 0  )
		{
			wchar_t szItemName[1024] = {0};
			try
			{
				swprintf_s(szItemName,L"i = %d Item addr = %p Item name = %s quality = %s �;� = %f ���� = %d ��ӡ = %d ���� = %d nCount = %d\r\n",
					i,					// ����ʱ����Ҫ�� EquipSlot��InvenSlot
					dwCurItemAddr,		// �����ַ
					GetString(&theAppleItem.str_theItemId),		// ��Ʒid
					GetString(&theAppleItem.str_theGradeId),	// ��ƷƷ��
					theAppleItem.str_fDurability,			// �;�
					theAppleItem.str_bIsUnidentified,		// ����
					theAppleItem.str_bIsSealed,				// ��ӡ
					theAppleItem.str_bIsTradable,			// ����
					theAppleItem.str_dwStackCount			// ��Ʒ����
					);

				g_csItemPrintStr += szItemName;
			}
			catch (...)
			{
				assert(false);
			}


			SDB_ITEM_INFO	theItemInfo = {0};
			_ReadProcessMemory(theAppleItem.str_dwItemObjAddr,&theItemInfo,sizeof(theItemInfo));
// 
// 			// ��Ʒ��;
// 			GAME_STRING_ID	theItemUseName = {0};
// 			_ReadProcessMemory(theAppleItem.str_dwItemObjAddr+JFZR_REVERSAL_ITEM_OBJ_USE_OFFSET___,&theItemUseName,sizeof(theItemUseName));
// 
// 
// 			// ��Ʒ����
// 			GAME_STRING_ID	theItemTypeName = {0};
// 			_ReadProcessMemory(theAppleItem.str_dwItemObjAddr+JFZR_REVERSAL_ITEM_OBJ_TYPE_OFFSET___,&theItemTypeName,sizeof(theItemTypeName));
// 

			try
			{
				swprintf_s(szItemName,L"id = %s, grade = %d, category = %d, level = %d, use = %s, type = %s, name = %s\r\n",
					GetVString(&theItemInfo.str_theId),
					theItemInfo.str_dwGrade,
					theItemInfo.str_dwCategory,
					theItemInfo.str_dwItemLevel,
					"",//GetString(&theItemUseName),
					"",//GetString(&theItemTypeName),
					GetVString(&theItemInfo.str_theName)
					);

				g_csItemPrintStr += szItemName;
			}
			catch (...)
			{
				assert(false);
			}

			try
			{
				if( theAppleItem.str_theStatus.str_dwCount > 0 && theAppleItem.str_theStatus.str_dwBinaryTreeNullMapAddr != NULL )
				{
					NODE	theNode = {0};
					_ReadProcessMemory(theAppleItem.str_theStatus.str_dwBinaryTreeNullMapAddr,&theNode,sizeof(theNode));
					ASSERT(theNode.str_dwNextAddrParent);

					Traverse(theNode.str_dwNextAddrParent,theAppleItem.str_theStatus.str_dwBinaryTreeNullMapAddr,ItemValuePrint);

					if( nType == 6 && i == 0)
					{
						char szPrint[256] = {0};
						sprintf_s(szPrint,"[JFZR] %f",g_fItemStatusValue);
						OutputDebugString(szPrint);
						return (DWORD)g_fItemStatusValue;
					}
				}
			}
			catch (...)
			{
				assert(false);
			}
	
			try
			{
				for (DWORD j = theAppleItem.str_theIncreaseStatusList.str_dwBeginAddr; j<theAppleItem.str_theIncreaseStatusList.str_dwEndAddr1; j+=sizeof(ITEM_STATUS_VALUE_))
				{
					ITEM_STATUS_VALUE_	theItemStatusValue = {0};
					_ReadProcessMemory(j,&theItemStatusValue,sizeof(theItemStatusValue));

					wchar_t		wszPrint[256] = {0};
					swprintf_s(wszPrint,L"��Ʒ��չ����: status = %s value = %f value2 = %f\r\n",GetString(&theItemStatusValue.str_theStatusId),theItemStatusValue.str_fValue,theItemStatusValue.str_fRelativeRate);
					g_csItemPrintStr += wszPrint;
				}
			}
			catch (...)
			{
				assert(false);
			}
	
			try
			{
				for (DWORD k = theAppleItem.str_theIdentifiedOptions.str_dwBeginAddr; k<theAppleItem.str_theIdentifiedOptions.str_dwEndAddr1; k+=sizeof(ITEM_STATUS_VALUE_))
				{
					ITEM_STATUS_VALUE_	theItemStatusValue = {0};
					_ReadProcessMemory(k,&theItemStatusValue,sizeof(theItemStatusValue));

					wchar_t		wszPrint[256] = {0};
					swprintf_s(wszPrint,L"��Ʒ��������: status = %s value = %f\r\n",GetString(&theItemStatusValue.str_theStatusId),theItemStatusValue.str_fValue,theItemStatusValue.str_fRelativeRate);
					g_csItemPrintStr += wszPrint;
				}
			}
			catch (...)
			{
				assert(false);
			}
		
		
		}
	}
	return true;
}

DWORD JFZRItem::TraverseItem(int nType)
{
	DWORD	dwBagItemAddr = 0;
	_ReadProcessMemory(JFZR_REVERSAL_ROLE_OBJ_ADDR+JFZR_REVERSAL_ITEM_BAG_OFFSET1+JFZR_REVERSAL_ITEM_BAG_OFFSET2,&dwBagItemAddr,sizeof(dwBagItemAddr));
	assert(dwBagItemAddr);
	_ReadProcessMemory(dwBagItemAddr+JFZR_REVERSAL_ITEM_BAG_OFFSET3+JFZR_REVERSAL_ITEM_BAG_OFFSET4,&dwBagItemAddr,sizeof(dwBagItemAddr));
	assert(dwBagItemAddr);

	DWORD	dwCurItemAddr = 0;
	DWORD	dwEndItemAddr = 0;

	switch(nType)
	{
	case  1:	// ��ͨ
		{
			csTxt = "��ͨ//\r\n";
			_ReadProcessMemory(dwBagItemAddr,&dwCurItemAddr,sizeof(dwCurItemAddr));
			_ReadProcessMemory(dwBagItemAddr+4,&dwEndItemAddr,sizeof(dwEndItemAddr));
		}
		break;
	case 2:		// ����Ʒ
		{
			csTxt += "����Ʒ//\r\n";
			_ReadProcessMemory(dwBagItemAddr+0x10,&dwCurItemAddr,sizeof(dwCurItemAddr));
			_ReadProcessMemory(dwBagItemAddr+0x14,&dwEndItemAddr,sizeof(dwEndItemAddr));
		}
		break;
	case 3:		// ����
		{
			csTxt += "����//\r\n";
			_ReadProcessMemory(dwBagItemAddr+0x20,&dwCurItemAddr,sizeof(dwCurItemAddr));
			_ReadProcessMemory(dwBagItemAddr+0x24,&dwEndItemAddr,sizeof(dwEndItemAddr));
		}
		break;
	case 4:		// ����
		{
			csTxt += "����//\r\n";
			_ReadProcessMemory(dwBagItemAddr+0x30,&dwCurItemAddr,sizeof(dwCurItemAddr));
			_ReadProcessMemory(dwBagItemAddr+0x34,&dwEndItemAddr,sizeof(dwEndItemAddr));
		}
		break;
	case 5:		// ʱװ1,2,3
		{
			csTxt += "ʱװ//\r\n";
			_ReadProcessMemory(dwBagItemAddr+0x40,&dwCurItemAddr,sizeof(dwCurItemAddr));
			_ReadProcessMemory(dwBagItemAddr+0x44,&dwEndItemAddr,sizeof(dwEndItemAddr));
		}
		break;
	case 6:		// ����װ��
		{
			csTxt += "װ��//\r\n";
			_ReadProcessMemory(JFZR_REVERSAL_ROLE_OBJ_ADDR+JFZR_REVERSAL_ITEM_BAG_OFFSET1+JFZR_REVERSAL_ITEM_BAG_OFFSET2,&dwBagItemAddr,sizeof(dwBagItemAddr));
			assert(dwBagItemAddr);
			_ReadProcessMemory(dwBagItemAddr+JFZR_REVERSAL_EQUIP_ITEM_OFFSET3+JFZR_REVERSAL_EQUIP_ITEM_OFFSET4,&dwBagItemAddr,sizeof(dwBagItemAddr));
			assert(dwBagItemAddr);
			_ReadProcessMemory(dwBagItemAddr+0x0,&dwCurItemAddr,sizeof(dwCurItemAddr));
			_ReadProcessMemory(dwBagItemAddr+0x4,&dwEndItemAddr,sizeof(dwEndItemAddr));
		}
		break;
	case 7:		// ����ʱװ
		{
			csTxt += "ʱװ//\r\n";
			_ReadProcessMemory(JFZR_REVERSAL_ROLE_OBJ_ADDR+JFZR_REVERSAL_ITEM_BAG_OFFSET1+JFZR_REVERSAL_ITEM_BAG_OFFSET2,&dwBagItemAddr,sizeof(dwBagItemAddr));
			assert(dwBagItemAddr);
			_ReadProcessMemory(dwBagItemAddr+JFZR_REVERSAL_EQUIP_ITEM_OFFSET3+JFZR_REVERSAL_EQUIP_ITEM_OFFSET4,&dwBagItemAddr,sizeof(dwBagItemAddr));
			assert(dwBagItemAddr);
			_ReadProcessMemory(dwBagItemAddr+0x10,&dwCurItemAddr,sizeof(dwCurItemAddr));
			_ReadProcessMemory(dwBagItemAddr+0x14,&dwEndItemAddr,sizeof(dwEndItemAddr));
		}
		break;
	default:
		{
			assert(false);
		}
	}
	
	assert(dwCurItemAddr);
	assert(dwEndItemAddr);

	int nItemCount = (int)((dwEndItemAddr-dwCurItemAddr)/JFZR_REVERSAL_ITEM_OBJ_SIZE___);
	for (int i=0; i<nItemCount; i++,dwCurItemAddr+=JFZR_REVERSAL_ITEM_OBJ_SIZE___)
	{
		// ��Ʒ����
		DWORD	dwItemNameLen = 0;

		_ReadProcessMemory(dwCurItemAddr+JFZR_REVERSAL_ITEM_BAG_NAME_LEN_OFFSET___,&dwItemNameLen,sizeof(dwItemNameLen));

		if( dwItemNameLen == 0 )
		{
			// ��Ʒ����id�����ڣ���˵��û����Ʒ����
		}

		DWORD dwItemNameAddr = 0;
		if( dwItemNameLen > 7 )
		{
			_ReadProcessMemory(dwCurItemAddr+JFZR_REVERSAL_ITEM_BAG_NAME_OFSSET___,&dwItemNameAddr,sizeof(dwItemNameAddr));
		}
		else
		{
			dwItemNameAddr = dwCurItemAddr+JFZR_REVERSAL_ITEM_BAG_NAME_OFSSET___;
		}

		wchar_t szReadItemData[256] = {0};
		_ReadProcessMemory(dwItemNameAddr,szReadItemData,dwItemNameLen*2);

		// ��ƷƷ��
		DWORD	dwItemQualityNameLen = 0;
		_ReadProcessMemory(dwCurItemAddr+JFZR_REVERSAL_ITEM_BAG_QUALITY_NAME_LEN_OFFSET___,&dwItemQualityNameLen,sizeof(dwItemQualityNameLen));

		DWORD dwItemQualityNameAddr = 0;
		if( dwItemQualityNameLen > 7 )
		{
			_ReadProcessMemory(dwCurItemAddr+JFZR_REVERSAL_ITEM_BAG_QUALITY_NAME_OFFSET___,&dwItemQualityNameAddr,sizeof(dwItemQualityNameAddr));
		}
		else
		{
			dwItemQualityNameAddr = dwCurItemAddr+JFZR_REVERSAL_ITEM_BAG_QUALITY_NAME_OFFSET___;
		}

		assert(dwItemQualityNameAddr);

		wchar_t szReadQualityData[256] = {0};
		_ReadProcessMemory(dwItemQualityNameAddr,szReadQualityData,dwItemQualityNameLen*2);

		// �;�
		DWORD dwQurable = 0;
		FLOAT fQurable = 0.0f;
		_ReadProcessMemory(dwCurItemAddr+JFZR_REVERSAL_ITEM_BAG_DURABLE_OFFSET___,&fQurable,sizeof(fQurable));
		dwQurable = (DWORD)fQurable;

		// ��Ʒ����
		DWORD dwCount = 0;
		_ReadProcessMemory(dwCurItemAddr+JFZR_REVERSAL_ITEM_BAG_COUNT_OFFSET___,&dwCount,sizeof(dwCount));

		// ��ӡ
		BYTE bySeal = 0;
		_ReadProcessMemory(dwCurItemAddr+JFZR_REVERSAL_ITEM_BAG_SEAL_OFFSET___,&bySeal,sizeof(bySeal));

		// ����
		BYTE byIdentification = 0;
		_ReadProcessMemory(dwCurItemAddr+JFZR_REVERSAL_ITEM_BAG_IDENTIFICATION_OFFSET___,&byIdentification,sizeof(byIdentification));

		// ����
		BYTE byRradable = 0;
		_ReadProcessMemory(dwCurItemAddr+JFZR_REVERSAL_ITEM_BAG_IS_TRADABLE_OFFSET___,&byRradable,sizeof(byRradable));
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ��Ʒ����

		DWORD dwItemObjAddr = 0;
		_ReadProcessMemory(dwCurItemAddr+JFZR_REVERSAL_ITEM_BAG_OBJ_OFFSET___,&dwItemObjAddr,sizeof(dwItemObjAddr));

		// ��Ʒ
		SDB_ITEM_INFO	theItemInfo = {0};
		_ReadProcessMemory(dwItemObjAddr,&theItemInfo,sizeof(theItemInfo));

// 		// ��Ʒ��;
// 		DWORD	dwUseNameLen = 0;
// 		_ReadProcessMemory(dwItemObjAddr+JFZR_REVERSAL_ITEM_OBJ_USE_LEN_OFFSET___,&dwUseNameLen,sizeof(dwUseNameLen));
// 		DWORD dwItemUseNameAddr = 0;
// 		if( dwUseNameLen > 7 )
// 		{
// 			_ReadProcessMemory(dwItemObjAddr+JFZR_REVERSAL_ITEM_OBJ_USE_OFFSET___,&dwItemUseNameAddr,sizeof(dwItemUseNameAddr));
// 		}
// 		else
// 		{
// 			dwItemUseNameAddr = dwItemObjAddr+JFZR_REVERSAL_ITEM_OBJ_USE_OFFSET___;
// 		}
// 		wchar_t wszUseName[256] = {0};
// 		_ReadProcessMemory(dwItemUseNameAddr,wszUseName,dwUseNameLen*2);
// 
// 		// ��Ʒ����
// 		DWORD	dwTypeNameLen = 0;
// 		_ReadProcessMemory(dwItemObjAddr+JFZR_REVERSAL_ITEM_OBJ_TYPE_LEN_OFFSET___,&dwTypeNameLen,sizeof(dwTypeNameLen));
// 		DWORD dwItemTypeNameAddr = 0;
// 		if( dwTypeNameLen > 7 )
// 		{
// 			_ReadProcessMemory(dwItemObjAddr+JFZR_REVERSAL_ITEM_OBJ_TYPE_OFFSET___,&dwItemTypeNameAddr,sizeof(dwItemTypeNameAddr));
// 		}
// 		else
// 		{
// 			dwItemTypeNameAddr = dwItemObjAddr+JFZR_REVERSAL_ITEM_OBJ_TYPE_OFFSET___;
// 		}
// 
// 		wchar_t wszTypeName[256] = {0};
// 		_ReadProcessMemory(dwItemTypeNameAddr,wszTypeName,dwTypeNameLen*2);


		wchar_t szItemName[1024] = {0};
		swprintf_s(szItemName,L"i = %d Item addr = %p Item name = %s quality = %s qurable = %d Identification = %d seal = %d Tradable = %d nCount = %d\r\n",
																				i,					// ����ʱ����Ҫ�� EquipSlot��InvenSlot
																				dwCurItemAddr,		// �����ַ
																				szReadItemData,		// ��Ʒid
																				szReadQualityData,	// ��ƷƷ��
																				dwQurable,			// �;�
																				byIdentification,	// ����
																				bySeal,				// ��ӡ
																				byRradable,			// ����
																				dwCount				// ��Ʒ����
																				);

		csTxt += szItemName;

		swprintf_s(szItemName,L"id = %s, grade = %d, category = %d, level = %d, use = %s, type = %s, name = %s\r\n",
					GetVString(&theItemInfo.str_theId),
					theItemInfo.str_dwGrade,
					theItemInfo.str_dwCategory,
					theItemInfo.str_dwItemLevel,
					"",//wszUseName,
					"",//wszTypeName,
					GetVString(&theItemInfo.str_theName)
			);



		csTxt += szItemName;
	}
	
	return false;
}
