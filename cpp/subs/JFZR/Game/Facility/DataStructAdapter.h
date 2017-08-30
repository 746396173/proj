#pragma once
/*
@author zhp
@date 2014/9/9 17:14
@purpose for struct switch
*/
#include "GClass.h"

struct stSdbItemTemplate{
	GClass::stGameStringEx	str_theId;						// +4
	GClass::stGameStringEx	str_theName;					// +20
	GAME_STRING_VF_ID		str_theDesc;					// +40
	DWORD					str_dwGrade;					// +60	װ��ǿ���ȼ�
	DWORD					str_dwCategory;					// ����
	DWORD					str_dwItemLevel;				// װ���ȼ�
	DWORD					str_dwMaxStackCount;			// ����������
	DWORD					str_dwMaxPossessionLimit;		// ���ӵ������
	GAME_STRING_ID_			str_theIconPath;				// +74
	BINARY_TREE_MAP			str_theIconPathByGrade;			// +94
	GAME_STRING_ID			str_theUITextColor;				// +A4
	BYTE					str_bDisassemblable;			// +C0
	BYTE					str_bQuickSlotable;
	BYTE					str_bNoDropFromNpc;
	BYTE					str_bNoDropFromStageClear;
	BYTE					str_bAutoUseWhenPickUp;
	BYTE					str_bAutoPickUp;
	BYTE					str_bIsPickableWhenStableAction;
	bool					str_bCanSellTotheShop;			// �Ƿ���������̵�
	BYTE					str_bReusable;
	BYTE					str_bPcCafeExclusive;
	WORD					str_wZeor1;
	DWORD					str_dwBindType;					// ������
	GClass::stGameString			str_theMarketCategory;			// +D0	�г����࣬Ӧ������������
	GAME_STRING_ID			str_thePriceCategory;			// +EC  ���÷��� ��:װ�������ϣ�������Ʒ��	CONSUME:����Ʒ
	GClass::stGameString	str_theSoundCategory;			// +108 ��Ʒ���� ���� ��:Ƥ��,����,�ؼ׵�   QUEST:������
	GAME_STRING_ID			str_theDropModelCategory;		// +124 װ��ʹ�ò�λ���� ��:�ϰ���,�ֲ���	QUEST:������
	GType::enTabCategory					str_dwInventoryTab;				// +140 �ڱ�������������  ��ͨ=0,����Ʒ=1 ��ϸ���ݼ�������Ʒ
	DWORD					str_dwSellPrice;				// 1230����

	BINARY_TREE_MAP			str_theStatusCondition;			// 20150317

	struct
	{
		DWORD				str_dwVFunAddr;
		DWORD				str_dwExpirationType;			// ��Ʒ��������
		struct
		{
			DWORD				str_dwVFunAddr;
			DWORD				str_dwYear;
			DWORD				str_dwMonth;
			DWORD				str_dwDay;
			DWORD				str_dwHour;
			DWORD				str_dwMinute;
		}theDateInfo;
	}theExpireInfo;		// +148		������Ϣ
	struct
	{
		DWORD				str_dwVFunAddr;
		bool				str_bEnable;			// ���ñ�־
		BYTE				str_bZeor1;				// �ڴ����
		WORD				str_wZeor2;				// �ڴ����
		GType::enEquipPart	str_dwEquipPart;		// װ��ʹ�ò�λ����������װ��ʱ��Ҫ�õ��� EquipSlot
		DWORD				str_dwLimitLevel[2];	// ���Ƶȼ�
		DWORD				str_dwLimitMinLevelMinus;	// 10.30��ɾ�������µ��ֶ�
		FLOAT				str_fMaxDurability;		// ����;�
		bool				str_bIdentified;		// ����
		bool				str_bSealed;			// ��ӡ
		BYTE				str_bIsTemplateItem;	// �Ƿ���Խ��� Rradable 1:�����̵����ͨװ��  0:��Ʒװ���������̵�(����100%ȷ��)
		BYTE				str_bZeor4;
		GClass::stGameString		str_theEquipCategory;	// װ����� ��:Ƥ��,����,�ؼ׵�
		BINARY_TREE_MAP		str_theStatus;			// ��Ʒ����
		BINARY_TREE_MAP		str_theSkillBonus;		// ��������
		DWORD				str_dwEquipableType;	// װ���������� +0x5C
		GAME_STRUCT_ARRAY_POINT		str_theMeshPaths;
		GAME_STRING_ID_				str_theEffectPath;
		BINARY_TREE_MAP				str_theMeshPathByGrade;  // +0x90
		BINARY_TREE_MAP				str_theMeshPathByClass;
		GAME_STRUCT_ARRAY_POINT		str_theEventOptionList;
		GAME_STRUCT_ARRAY_POINT		str_theMasteryStatusIds;
		GAME_STRUCT_ARRAY_POINT		str_theSubEquipParts;
		GAME_STRUCT_ARRAY_POINT		str_theHideMeshTypes;
		DWORD						str_dwColorChannelCount;
		GAME_STRUCT_ARRAY_POINT		str_theChannelColors;
		GAME_STRING_ID				str_theEquipmentSetInfoId;
		GAME_STRUCT_ARRAY_POINT		str_theOverrideProjectileByTag;	// +0x120
		GAME_STRUCT_ARRAY_POINT		str_theSkillCoolDownInfo;
		GAME_STRING_ID				str_theAdditionalUnsealItemType; // +0x140
		struct
		{
			DWORD				str_dwVFunAddr;
			DWORD				str_dwBaitSlotCount;
			BINARY_TREE_MAP		str_theStatus;
			GAME_STRUCT_ARRAY_POINT	str_theFishingEventOptions;
		}theFishingInfo;	// 1230����
	}theEquipInfo;		// +168		װ����Ϣ

	struct  
	{
		DWORD						str_dwVFunAddr;
		BINARY_TREE_MAP				str_thePeriodStatus;
		BINARY_TREE_MAP				str_thePeriodSkillBonus;
		GAME_STRUCT_ARRAY_POINT		str_thePeriodEventOptionList;
		GAME_STRING_ID				str_thePeriodOptionExclusiveClassId;	// 10.30��ɾ���������ݶ�
		struct
		{
			DWORD					str_dwVFunAddr;
			DWORD					str_dwExpirationType;
			struct
			{
				DWORD				str_dwVFunAddr;
				DWORD				str_dwYear;
				DWORD				str_dwMonth;
				DWORD				str_dwDay;
				DWORD				str_dwHour;
				DWORD				str_dwMinute;
			}theDate;
		}theExpire;
	}theExtendInfo;			// +2EC		��չ��Ϣ

	struct 
	{
		DWORD				str_dwVFunAddr;
		BYTE				str_bEnable;						// ���ñ�־
		bool				str_bCanUseInVillage;				// �Ƿ�����ٳ�����ʹ��
		WORD				str_wZeor1;
		GClass::stGameString		str_theCooldownCategory;			// �����飺ʶ��(Identify),Unseal
		DWORD				str_dwUseEffect;					// ʹ��Ч��
		DWORD				str_dwTargetLimitItemLevel[2];		// ����Ŀ����Ʒ�ȼ�	�����飺������Ʒ�ȼ�
		DWORD				str_dwTargetLimitGrade[2];			// ����Ŀ��ɾ����ȼ�
		DWORD				str_dwLimitLevel[2];				// ���Ƶȼ�
		DWORD				str_dwLimitTierAttackPower[2];		// ���ƹ���ǿ��
		BINARY_TREE_MAP		str_theParams;
		GAME_STRUCT_ARRAY_POINT		str_thePlayerInfoStates;
		GAME_STRUCT_ARRAY_POINT		str_theUnKnow2;
		GAME_STRUCT_ARRAY_POINT		str_theBuffs;
		DWORD						str_dwUsableType;
		GAME_STRING_ID				str_theCinematicDialogInfoId;
		GAME_STRING_ID				str_theAcceptQuestId;
		GAME_STRUCT_ARRAY_POINT		str_theExceptedBuffIds;
	}theUsableInfo;		// +35C		������Ϣ

	struct  
	{
		DWORD				str_dwVFunAddr;
		DWORD				str_dwEnable;					// ���ñ�־
		DWORD				str_dwEnhanceType;
		DWORD				str_dwInitialEnhanceLevel;
		BINARY_TREE_MAP		str_theEnhanceFactors;
	}theEnhanceInfo;		// +3E4		��ǿ��Ϣ
	BYTE			str_bAutoComplete;
	BYTE			str_bIsCash;
	BYTE			str_bCanBeCombineOutput;
};
static_assert(sizeof(stSdbItemTemplate) == sizeof(SDB_ITEM_INFO), "");