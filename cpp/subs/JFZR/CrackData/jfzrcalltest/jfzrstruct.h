
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �����Ľṹ��
#ifndef JFZR_STRUCT_91044C184E5B46508DDB073DA8DEFC42
#define JFZR_STRUCT_91044C184E5B46508DDB073DA8DEFC42
// Source code here

typedef struct  
{
	DWORD	str_dwNextAddrLeft;
	DWORD	str_dwNextAddrParent;
	DWORD	str_dwNextAddrRight;
}NODE,*PNODE;

typedef struct
{
	DWORD	str_dwUnKnowAddr;
	DWORD	str_dwBinaryTreeNullMapAddr;			// ָ��������սڵ�
	DWORD	str_dwCount;							// ��������Ч�ڵ�������������սڵ�
	DWORD	str_dwUnKnowAddr2;
}BINARY_TREE_MAP,*PBINARY_TREE_MAP;

typedef	struct
{
	DWORD				str_dwBeginAddr;
	DWORD				str_dwEndAddr1;
	DWORD				str_dwEndAddr2;
	DWORD				str_dwCommandAddr;
}GAME_STRUCT_ARRAY_POINT,*PGAME_STRUCT_ARRAY_POINT;

typedef struct  
{
	FLOAT		fx;
	FLOAT		fz;
	FLOAT		fy;
}XYZ;


typedef struct
{
	union
	{
		wchar_t*	wstr_ptr_id;
		wchar_t		wstr_id[8];	
	};
	DWORD	str_dwStrLen;
	DWORD	str_dwStrLen_;
	DWORD	str_dwUnKnow1;
}GAME_STRING_ID,*PGAME_STRING_ID;

typedef struct
{
	union
	{
		wchar_t*	wstr_ptr_id;
		wchar_t		wstr_id[8];	
	};
	DWORD	str_dwStrLen;
	DWORD	str_dwStrLen_;
	DWORD	str_dwUnKnow1;
	DWORD	str_dwUnKnow2;
}GAME_STRING_ID_,*PGAME_STRING_ID_;


typedef struct
{
	DWORD	str_dwVFunAddr;		// �麯��
	union
	{
		wchar_t*	wstr_ptr_id;
		wchar_t		wstr_id[8];	
	};
	DWORD	str_dwStrLen;
	DWORD	str_dwStrLen_;
	DWORD	str_dwUnKnow1;
}GAME_STRING_VF_ID,*PGAME_STRING_VF_ID;



extern wchar_t* GetString(PGAME_STRING_ID ptheGameString);
extern wchar_t* GetVString(PGAME_STRING_VF_ID ptheGameString);
extern wchar_t* GetString_(PGAME_STRING_ID_ ptheGameString);



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ְҵ����
typedef struct  
{
	DWORD	str_dwNextAddrLeft;
	DWORD	str_dwNextAddrParent;
	DWORD	str_dwNextAddrRight;
	DWORD	str_dwid;						// ����id
	DWORD	str_dwTaskObjAddr;				// �������
	DWORD	str_dwTaskObjPointAddr;			// ָ���������
	bool	str_bFlag;
	DWORD	str_dwUnKnow;
}TASK_OBJ,*PTASK_OBJ;						// �������������ʱ���ڵ����

typedef struct		// Apple::StaticDatabase::Quest
{
	GAME_STRING_VF_ID	str_theTaskId;				// ��������id
	GAME_STRUCT_ARRAY_POINT		str_theStageIds;	// ������������  10.30��ɾ�������ֶα仯�������ٵ�һ��
	GAME_STRING_VF_ID	str_theMainTitleId;			// ������Ӣ��ӳ��
	GAME_STRING_VF_ID	str_theSubTitleId;			// ������Ӣ��ӳ��
	DWORD				str_dwCategory;				// �������	==>    4,��ͨ����֮����ɱ������  5,��������  6,��ͨ����֮�ռ��������� ����δ֪
	DWORD				str_dwLevel;				// ����ȼ�
	GAME_STRING_VF_ID	str_theBeginDescId;			// �鿴����ʱ���Ҵ��ڵı���
	GAME_STRING_VF_ID	str_theEndDescId;			// �鿴����ʱ���Ҵ��ڵ�����
}TASK_INFO,*PTASK_INFO;

typedef struct  
{
	GAME_STRING_ID		str_theAcceptTaskNpcId;		// ������NPC id
	GAME_STRING_ID		str_theCompleteNpcId;		// ������NPC id
}ACCEPT_COMPLETE,*PACCEPT_COMPLETE;

typedef struct
{
	NODE				str_theNode;
	GAME_STRING_ID		str_theCollectItemNameId;		// ��Ҫ�ռ���Ʒ������id
	DWORD				str_dwCollectItemCount;			// ��Ҫ�ռ���Ʒ������
}COLLECT_ITEM,*PCOLLECT_ITEM;							// �ռ���Ʒ

typedef struct	// Apple::Condition
{
	DWORD				str_dwVFunAddr;
	union  
	{
		DWORD			str_dwClasses;
		DWORD			str_dwClassesArray[4];
	};
	union  
	{
		FLOAT			str_fLevel;
		FLOAT			str_fLevelArray[2];
	};
	DWORD				str_dwGold;
	union  
	{
		DWORD			str_dwRequiredTierAttackPower;
		DWORD			str_dwRequiredTierAttackPowerArray[2];
	};
	DWORD				str_dwAwakening;		// +0x28
	//DWORD				str_dwPvpPoint;

	BINARY_TREE_MAP				str_thePvpWinCounts;
	BINARY_TREE_MAP				str_thePvpLoseCounts;
	BINARY_TREE_MAP				str_thePvpTotalCounts;
	BINARY_TREE_MAP				str_theItems;						// �ռ���Ʒ
	BINARY_TREE_MAP				str_theLicenses;					// +0x6C
	GAME_STRUCT_ARRAY_POINT		str_theInacceptableQuests;
	DWORD						str_dwInacceptableWhenCompleted;	// 11.30�������ݶ�
	GAME_STRUCT_ARRAY_POINT		str_thePrecedingQuests;				// ��һ������
	GAME_STRUCT_ARRAY_POINT		str_thePrecedingQuestsTypeOr;

	DWORD				str_dwDifficulty;
	DWORD				str_dwCompleteType;

	GAME_STRUCT_ARRAY_POINT		str_theNpcConditions;				// ��ɱ����
	GAME_STRUCT_ARRAY_POINT		str_thePvpConditions;
	BINARY_TREE_MAP				str_theStageConditions;				// ����
	GAME_STRUCT_ARRAY_POINT		str_theUseItems;
	GAME_STRUCT_ARRAY_POINT		str_theEnhanceItems;
	BINARY_TREE_MAP				str_theEquipmentSetInfos;
	BINARY_TREE_MAP				str_theStatusConditions;

	DWORD				str_dwInventoryCapacity;
	DWORD				str_dwPlayerBankCapacity;
	DWORD				str_dwAccountBankCapacity;
}ACCPET_CONDITION,COMPLETE_CONDITION,*PACCPET_CONDITION,*PCOMPLETE_CONDITION;		// �����������������

typedef struct
{
	DWORD				str_dwVFunAddr;
	DWORD				str_dwNpcConditionType;
	GAME_STRING_ID		str_theKey;							// NPC id
	DWORD				str_dwValue;						// ��Ҫ��ɱ������
	DWORD				str_dwBackAttackCount;
	DWORD				str_dwSpecialAttackUseCount;
	DWORD				str_dwDeadlySkillUseCount;
	GAME_STRUCT_ARRAY_POINT		str_theSkillUsageCounts;
	GAME_STRUCT_ARRAY_POINT		str_theApprovedStages;		// �������ڸ�����ͼ
	BINARY_TREE_MAP				str_theNpcKillBySkill;
}NPC_CONDITION,*PNPC_CONDITION;								// ����NPC����

typedef struct	// Apple::StaticDatabase::Quest::Reward
{
	DWORD				str_dwVFunAddr;
	DWORD				str_dwExpRate;
	DWORD				str_dwBonusExp;		// 11.30��ɾ���ı��ֶ�
	DWORD				str_dwGold;
	DWORD				str_dwRemoveGold;
	BINARY_TREE_MAP		str_theBuffsToGive;
	BINARY_TREE_MAP		str_theBuffsToRemove;
	BINARY_TREE_MAP		str_theItemsToGive;
	BINARY_TREE_MAP		str_theItemsToGiveMail;		// 11.30��ɾ�������ֶ�
	BINARY_TREE_MAP		str_theItemsToRemove;
	BINARY_TREE_MAP		str_theSelectableItems;				// ѡ������Ʒ
	BINARY_TREE_MAP		str_theLicensesToGive;
	BINARY_TREE_MAP		str_theLicensesToRemove;
	GAME_STRING_VF_ID	str_theChangeClass;
	DWORD				str_dwMakeAwaken;
	DWORD				str_dwAwakenPoint;
	GAME_STRUCT_ARRAY_POINT		str_theUnlockBasicEquipSlots;
	GAME_STRING_ID		str_theTitle;				// 11.30�ṹ��ı�
	DWORD				str_dwAccountMileage;		// 11.30��ɾ�������ֶ�
	FLOAT				str_fTierAttackPower;		// 11.30��ɾ�������ֶ�
}QUEST_REWARD,*PQUEST_REWARD;					//������

typedef struct
{
	GAME_STRING_VF_ID			str_theVillageId;
	struct  
	{
		FLOAT	x;
		FLOAT	z;
		FLOAT	y;
	}str_thePosition;
	struct  
	{
		FLOAT	x;
		FLOAT	z;
		FLOAT	y;
	}str_theDirection;
}TELEPORTLOCATION,*PTELEPORTLOCATION;			// TeleportLocation




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �ѽ�����
typedef	struct  
{
	NODE				str_theNode;
	DWORD				str_dwUnknow;
	GAME_STRING_ID		str_theGameTaskId;
}RECEIVED_TASK,*PRECEIVED_TASK;

typedef struct
{
	DWORD				str_dwVFun;
	GAME_STRING_ID		str_theGameNpcType;
	GAME_STRING_ID		str_theGameNpcNameId;		// ������Ҫ����NPC������id
	DWORD				str_dwConditionsCount;		// ��Ҫ����NPC����ĸ���
}CONDITIONS_NPC_TASK,*PCONDITIONS_NPC_TASK;			// ����NPC�������

typedef struct
{
	DWORD				str_dwVFunAddr;
	GAME_STRING_ID		str_theType;
	GAME_STRING_ID		str_theKey;						// ������Ҫ����NPC������id
	DWORD				str_dwValue;					// ��Ҫ����NPC����ĸ���
	DWORD				str_dwBackAttackCount;						// ���󹥻�����
	DWORD				str_dwSpecialAttackUseCount;				// ���⹥��ʹ����
	DWORD				str_dwDeadlySkillUseCount;					// �����ļ���ʹ����
	GAME_STRUCT_ARRAY_POINT			str_theSkillUsageCounts;		// ���ܵ�ʹ������
	GAME_STRUCT_ARRAY_POINT			str_theStages;					// ����׶Σ���������ͼ
	BINARY_TREE_MAP					str_theNpcKillBySkill;			// ʹ�ü���ɱ������
}REMAIN_NPC_CONDITION,*PREMAIN_NPC_CONDITION;						// RemainNpcCondition

typedef struct
{
	GAME_STRING_VF_ID		str_theId;
	DWORD					str_dwConditions;
	BYTE					str_bCompletable;
	BYTE					str_bZeor1[3];
	struct
	{
		DWORD						str_dwVFunAddr2;
		GAME_STRUCT_ARRAY_POINT		str_theRemainUseItems;
		GAME_STRUCT_ARRAY_POINT		str_theRemainKillNpcInfos;			// ʣ��ɱ������
		GAME_STRUCT_ARRAY_POINT		str_theRemainPvpConditions;
		BINARY_TREE_MAP				str_theRemainStageIds;
		GAME_STRUCT_ARRAY_POINT		str_theRemainEnhance;
		BINARY_TREE_MAP				str_theRemainStatus;
	}str_theRemainCondition;

	DWORD					str_dwNullAddr;
	struct
	{
		DWORD				str_dwOidActiveCondition1;
		DWORD				str_dwOidActiveCondition2;
	}str_theOidActiveCondition;
}ACTIVE_CONDITION,*PACTIVE_CONDITION;


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Stageģ��
typedef struct  
{
	DWORD						str_dwVFunAddr;
	GAME_STRUCT_ARRAY_POINT		str_theWarpGeteLinkInfosNode;
}WARP_GATE_LINK_INFOS_NODE,*PWARP_GATE_LINK_INFOS_NODE;	//WarpGateLinkInfos

typedef struct 
{
	DWORD				str_dwVFunAddr;
	DWORD				str_dwStageType;			// ����=1,����=0
	GAME_STRING_ID		str_theId;					// +8
	GAME_STRING_ID		str_theStartingSectorId;	// +24
	GAME_STRING_ID		str_theEnteringWarpGateId;	// +40	10.30��ɾ����������
	GAME_STRING_VF_ID	str_theName;				// +5C
	GAME_STRING_VF_ID	str_theClearConditionDesc;	// +7C
	DWORD				str_dwRecommandLevel[2];	// +9C
	DWORD				str_dwEnterLevelRange[2];	// +A4	20150316

	DWORD				str_dwRecommandDPS;			// 10.30��ɾ����������  dps ����
	DWORD				str_dwExperiencedDifficulty;
	XYZ					str_theStartingDirection;	// +AC
	GAME_STRUCT_ARRAY_POINT		str_theWarpGateLinkInfos;		// +B8  ������������Ϣ
	BINARY_TREE_MAP				str_theSectors;					// +CC  ��ǰ��ͼ�ķ���
	GAME_STRUCT_ARRAY_POINT		str_theRandomRoute;				// +D8
	GAME_STRUCT_ARRAY_POINT		str_theUniqueDropListForShowing;
	GAME_STRUCT_ARRAY_POINT		str_theClearBuffListForShowing;	// +F8
	DWORD						str_dwClearExp;						// +108
	DWORD						str_dwClearGold;
	GAME_STRING_ID				str_theClearMedal;					// +110
	BINARY_TREE_MAP				str_theStageObjectNpcs;				// BOOS
	BINARY_TREE_MAP				str_theStageFailObjectNpcs;			// +13C
	GAME_STRUCT_ARRAY_POINT		str_theClearConditions;
	GAME_STRUCT_ARRAY_POINT		str_theFailConditions;				// 
	FLOAT						str_fStartingPositionX;
	FLOAT						str_fStartingPositionY;
	DWORD						str_dwMinimumLevelToGetLicense;
	DWORD						str_dwGetResurrectionSicknessWhenFailed;
	GAME_STRING_ID_				str_theMinimapPath;					// +17C
	GAME_STRING_ID_				str_theFishingSiteMinimapPath;		// 1230����
	GAME_STRUCT_ARRAY_POINT		str_theCameraEffectPaths;
	DWORD						str_dwLevel;		// 
	DWORD						str_dwFatigue;		// ����ƣ��ֵ
	BYTE						str_bEnableStageFailBuff;
	BYTE						str_bIsRestartable;
	WORD						str_wUnKnow1;
	BINARY_TREE_MAP				str_theMonsterStatusBonus;
	BINARY_TREE_MAP				str_theMonsterStatusBonusByDelta;
	GAME_STRING_ID				str_theBgmCue;
	GAME_STRING_ID				str_theBossBgmCue;
	BINARY_TREE_MAP				str_theAmbientSoundEvents;
	FLOAT						str_fStartingRectangleX;
	FLOAT						str_fStartingRectangleY;
	// ...
}SDB_STAGE_INFO,*PSDB_STAGE_INFO;		// StageInfo

typedef struct
{
	DWORD				str_dwVFunAddr;
	GAME_STRING_ID		str_theStageId;			// id
	GAME_STRING_ID		str_theSectorId;		// �������
	GAME_STRING_ID		str_theWarpGateId;		// ��
	BYTE				str_bEnable;			// �Ƿ����� 1Ϊ��ͨ����0Ϊ����ͨ��
	BYTE				str_bUnknow1;
	WORD				str_wUnknow2;
}WARP_GATE,*PWARP_GATE;

typedef struct  
{
	WARP_GATE	str_theWarpGate1;
	WARP_GATE	str_theWarpGate2;
}WARP_GATE_LINK,&PWARP_GATE_LINK;

typedef struct
{
	NODE				str_theNode;
	GAME_STRING_ID		str_theId_;
	DWORD				str_dwVFunAddr;
	GAME_STRING_ID_		str_theSectorPath;
	GAME_STRING_ID		str_theId;
	DWORD				str_dwSectorResetType;				// ������������
	GAME_STRUCT_ARRAY_POINT		str_theSectorLimitPoints;
	GAME_STRUCT_ARRAY_POINT		str_theRestrictions;
	GAME_STRUCT_ARRAY_POINT		str_theLocations;
	BYTE						str_bIsBossSector;			// �Ƿ�ΪBOOS����
	DWORD						str_dwMinimapOffset[2];
	DWORD						str_dwMinimapSize[2];
	BINARY_TREE_MAP				str_theWarpGates;			// +88 ���䴫����	
	GAME_STRUCT_ARRAY_POINT		str_theStageStartWarpGates;	// stage��ʼ������
	GAME_STRUCT_ARRAY_POINT		str_thePopInfos;
	GAME_STRUCT_ARRAY_POINT		str_theFixedNpcs;			// ����NPC
	GAME_STRUCT_ARRAY_POINT		str_theInteractiveNpcs;		
	GAME_STRUCT_ARRAY_POINT		str_theFixedNpcsByQuest;
	GAME_STRUCT_ARRAY_POINT		str_theBuffFloors;
	GAME_STRUCT_ARRAY_POINT		str_theStartingRedWall;
	GAME_STRUCT_ARRAY_POINT		str_theStartingBlueWall;
	GAME_STRUCT_ARRAY_POINT		str_theAdditionalNpcPopInfos;
	GAME_STRING_ID				str_theReverbPreset;
	struct  
	{
		DWORD					str_dwVFunAddr;
		GAME_STRING_ID			str_theCinematicDialogId;
		GAME_STRUCT_ARRAY_POINT	str_theCreateItems;
	}theClearEventInfo;		// +144
	struct  
	{
		DWORD					str_dwVFunAddr;
		GAME_STRING_ID			str_theWarpGateId;
		DWORD					str_dwDelayTime;
	}theAutoWarpGateAfterSectorClearInfo;		// +174
	struct  
	{
		DWORD					str_dwVFunAddr;
		GAME_STRING_ID			str_theUnknow1;
	}theUnKnow1;
	XYZ							str_theSectorCenterPosition;
	XYZ							str_theSectorRebirthPosition;
	XYZ							str_theSectorRebirthDirection;
	XYZ							str_theSectorEscortPosition;
	struct  
	{
		DWORD					str_dwVFunAddr;
		struct  
		{
			DWORD				str_dwVFunAddr;
			GAME_STRING_ID		str_theEnterMessage;
		}theEnterMessage;
		struct  
		{
			DWORD				str_dwVFunAddr;
			GAME_STRING_ID		str_theClearMessage;
		}theClearMessage;
		GAME_STRUCT_ARRAY_POINT		str_theTimeMessage;
		GAME_STRUCT_ARRAY_POINT		str_theMonsterMessage;
	}theSectorMessageInfo;
}SDB_SECTOR,*PSDB_SECTOR;		// Sector

typedef struct
{
	DWORD				str_dwVFunAddr;
	GAME_STRING_ID		str_theId;
	FLOAT				str_fPositionX;
	FLOAT				str_fPositionY;
	XYZ					str_theDirection;
	XYZ					str_theScale;
	struct  
	{
		DWORD			str_dwVFunAddr;	
		DWORD			str_dwStamps;
		GAME_STRUCT_ARRAY_POINT	str_thefixedNpcMovement;
	}theMovementInfo;
}FIXD_NPC,*PFIXD_NPC;		// FixedNpc

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ������Ʒģ����Ϣ
typedef struct
{
	GAME_STRING_VF_ID		str_theId;						// +4
	GAME_STRING_VF_ID		str_theName;					// +20
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
	BYTE					str_bCanSellTotheShop;			// �Ƿ���������̵�
	BYTE					str_bReusable;
	BYTE					str_bPcCafeExclusive;
	WORD					str_wZeor1;
	DWORD					str_dwBindType;					// +CC  ������
	GAME_STRING_ID			str_theMarketCategory;			// +D0	�г����࣬����������Ҫ�õ�
	GAME_STRING_ID			str_thePriceCategory;			// +EC  ���÷��� ��:װ�������ϣ�������Ʒ��	CONSUME:����Ʒ  EQUIPMENT:װ��
	GAME_STRING_ID			str_theSoundCategory;			// +108 ��Ʒ���� ���� ��:Ƥ��,����,�ؼ׵�   QUEST:������ ARMOR_HEAVYARMOR:�ؼ�
	GAME_STRING_ID			str_theDropModelCategory;		// +124 װ��ʹ�ò�λ���� ��:�ϰ���,�ֲ���	QUEST:������
	DWORD					str_dwInventoryTab;				// +140 �ڱ�������������  ��ͨ=0,����Ʒ=1 ��ϸ���ݼ�������Ʒ
	DWORD					str_dwSellPrice;				// +144

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
		BYTE				str_bEnable;			// ���ñ�־
		BYTE				str_bZeor1;				// �ڴ����
		WORD				str_wZeor2;				// �ڴ����
		DWORD				str_dwEquipPart;		// װ��ʹ�ò�λ����������װ��ʱ��Ҫ�õ��� EquipSlot
		DWORD				str_dwLimitLevel[2];	// ���Ƶȼ�
		DWORD				str_dwLimitMinLevelMinus;	// 10.30��ɾ�������µ��ֶ�
		FLOAT				str_fMaxDurability;		// ����;�
		BYTE				str_bIdentified;		// ����
		BYTE				str_bSealed;			// ��ӡ
		BYTE				str_bIsTemplateItem;	// �Ƿ���Խ��� Rradable 1:�����̵����ͨװ��  0:��Ʒװ���������̵�(����100%ȷ��)
		BYTE				str_bZeor4;
		GAME_STRING_ID		str_theEquipCategory;	// װ����� ��:Ƥ��,����,�ؼ׵�
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
		BYTE				str_bCanUseInVillage;				// �Ƿ�����ٳ�����ʹ��
		WORD				str_wZeor1;
		GAME_STRING_ID		str_theCooldownCategory;			// �����飺ʶ��(Identify)
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
}SDB_ITEM_INFO,*PSDB_ITEM_INFO;		// ItemInfo




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ����ģ��
typedef struct  
{
	NODE			str_theNode;
	DWORD			str_dwId;
	DWORD			str_dwObjAddr;
	DWORD			str_dwObjAddrPoint;
	DWORD			str_dwUnKnowFlag;
}SDB_INDEX,*PSDB_INDEX;

typedef struct
{
	GAME_STRING_VF_ID		str_theId;
	GAME_STRING_VF_ID		str_theName;
	DWORD					str_dwNeedTarget;						// ��ҪĿ��
	DWORD					str_dwMaxRangeOnTarget;					// ���Ŀ�귶Χ
	GAME_STRING_VF_ID		str_theDesc;							// ����˵��
	DWORD					str_dwElementalAttribute;				// Ԫ������  ��Ӧ�������ʱ "FIRE"  ElementalAttribute
	DWORD					str_dwTargetTypes;						// Ŀ������
	DWORD					str_dwSkillType;						// �������� : ��������=0;��������=1;���⼼=2;
	DWORD					str_dwTargetInfo[6];					// Ŀ����Ϣ
	GAME_STRUCT_ARRAY_POINT		str_theSkillInfoPerLevels;			// ���ܸ��ȼ���ϸ��Ϣ
	GAME_STRUCT_ARRAY_POINT		str_thePrecedingSkills;				// ǰ�ü���, ѧϰ����ʱҪ�������жϵ�
	GAME_STRUCT_ARRAY_POINT		str_theSecondaryAwakeningSkills;	// ���ξ��Ѽ���
	BYTE					str_bEnableAutoTarget;					// �Զ�ʹ��Ŀ��
	BYTE					str_OneClickUse;						// ���ʹ��
	WORD					str_wZeor1;
	FLOAT					str_fAutoTargetDistanceRangeX;			// �Զ�Ŀ�귶Χ
	FLOAT					str_fAutoTargetDistanceRangeY;	
	FLOAT					str_fAutoTargetAngleRangeX;				// �Զ�Ŀ�����Ƿ�Χ
	FLOAT					str_fAutoTargetAngleRangeY;
	BYTE					str_bAutoTargetingIsOnlyFirstAction;
	BYTE					str_bEnableAOEAutoTarget;	
	WORD					str_wZeor2;
	FLOAT					str_fAOEAutoTargetDistanceRangeX;
	FLOAT					str_fAOEAutoTargetDistanceRangeY;
	FLOAT					str_fAOEAutoTargetAngleRangeX;
	FLOAT					str_fAOEAutoTargetAngleRangeY;
	GAME_STRING_ID			str_theIconPath;
	DWORD					str_dwZeor1;
	struct  
	{
		DWORD				str_dwVFunAddr;
		DWORD				str_dwEnable;
		GAME_STRING_ID		str_theScriptFuncName;		// �ű�����������
	}theSkillActivateCondition;
	struct
	{
		DWORD				str_dwVFunAddr;
		GAME_STRING_ID		str_theUnKnow;
	}theUnKnow1;
	struct  
	{
		DWORD				str_dwVFunAddr;
		DWORD				str_dwEnable;				// ����
		DWORD				str_dwLevel;
		DWORD				str_dwRadius;				// �뾶��Χ
		DWORD				str_dwMaxRange;				// ���Χ
		DWORD				str_dwCheckSectorLimit;
		GAME_STRING_VF_ID	str_theAoeVisualId;			// Ч����Χ�Ӿ�id
	}theAoeInfo;
	GAME_STRUCT_ARRAY_POINT	str_theOverrideAoeInfos;	// ����Ч����Χ��Ϣ
	DWORD					str_dwEnableSkillUseWhenCooldown;		// ʹ������ȴʱʹ��
	GAME_STRING_ID			str_theCommandTag;						// �����ǩ
	BYTE					str_bIsDeadlySkill;						// �Ƿ�Ϊ��������
	DWORD					str_dwDeadlySkillFullGaugeSpending;
	GAME_STRING_ID			str_theDeadlySkillId;
	BYTE					str_bAffectedByAwaken;
	BYTE					str_bIsAwakeningSkill;
	BYTE					str_bBeAwakenToLearn;
	BYTE					str_bIsGuildSkill;
	GAME_STRING_ID_			str_theMoviePath;
	struct  
	{
		DWORD				str_dwVFunAddr;
		GAME_STRING_ID		str_theInstructionDesc;
	}theInstructionDesc;
	GAME_STRUCT_ARRAY_POINT	str_theIncompatibleSkills;
	DWORD					str_dwPvpPrecooldown;
	DWORD					str_dwPvpAttackPowerRate;
}SDB_SKILL,*PSDB_SKILL;

typedef struct
{
	DWORD					str_dwVFunAddr;
	DWORD					str_dwLevel;				// ���ܵȼ�
	DWORD					str_dwMinLevelToLearn;		// ѧϰ������Ҫ�Ľ�ɫ�ȼ�
	DWORD					str_dwSpToLearn;			// ѧϰ������Ҫ��sp��
	DWORD					str_dwGoldToLearn;			// ѧϰ����������
	DWORD					str_dwAwakeningPointToLearn;// ѧϰ����������ѵ� 
	DWORD					str_dwTierAttackPowerToLearn;	// 10.30��ɾ�������ֶ�
	GAME_STRING_ID			str_theActionId;
	FLOAT					str_fConsumeHp;				// ����hp
	FLOAT					str_fConsumeMp;				// ����mp
	FLOAT					str_fConsumeRage;			// ���ķ�ŭ
	FLOAT					str_fConsumeBloodPoint;		// ����Ѫֵ
	FLOAT					str_fAvailablePeriod;		// ʹ��ʱ��
	FLOAT					str_fCooldown;				// ��ȴʱ��
	FLOAT					str_fReusingInterval;		// ���ü��
	FLOAT					str_fAttackPowerRate;		// �����ٶȣ�����˺�������Ҫ�õ�
	GAME_STRUCT_ARRAY_POINT		str_theActionIdList;
	BINARY_TREE_MAP				str_theDescParams;			// �������͹�������
	BINARY_TREE_MAP				str_theParams;
	GAME_STRUCT_ARRAY_POINT		str_theIncreaseStatus;		// ����״̬
	GAME_STRING_ID				str_theOverrideActionId;
	GAME_STRUCT_ARRAY_POINT		str_theEventOptionIds;
	GAME_STRUCT_ARRAY_POINT		str_theReduceCooldowns;
	DWORD						str_dwIncreaseStatusByEquipCategory;
	GAME_STRING_VF_ID			str_theUnKnow1;
	DWORD						str_dwUnKnow1[3];
}SKILL_INFO_PER_LEVEL,*PSKILL_INFO_PER_LEVEL;		// SkillInfoPerLevel


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��Ʒģ��
typedef struct
{
	DWORD				str_dwVFunAddr;
	GAME_STRING_ID		str_theId;
	DWORD				str_dwShopType;
	GAME_STRUCT_ARRAY_POINT		str_theTargetVillages;
	GAME_STRING_ID				str_theArenaId;
	GAME_STRUCT_ARRAY_POINT		str_theSellItems;
	GAME_STRUCT_ARRAY_POINT		str_theSkillTrainClasses;
	BINARY_TREE_MAP				str_theCraftItems;
	DWORD						str_dwItemCategoryInfos[5];	// δ֪��������
}SDB_SHOP_INFO,*PSDB_SHOP_INFO;

typedef struct			// Apple::Sdb::ShopInfo::SellItem
{
	DWORD				str_dwVFunAddr;
	DWORD				str_dwId;				// ʮ������id
	GAME_STRING_ID		str_theOutputItemId;	// ��Ʒid
	struct
	{
		DWORD			str_dwVFunAddr;
		DWORD			str_dwGold;				// ���
		DWORD			str_dwFriendPoint;		// �����
		DWORD			str_dwGuildCoin;		// ����Ӳ��
		DWORD			str_dwMileage;			// 10.30�������ݶ�
		GAME_STRUCT_ARRAY_POINT			str_theCrests;		// ����Ҫ��
	}thePriceInfo;	// PriceInfo
	DWORD				str_dwRequiredLevelRange[2];			// Ҫ��ȼ���Χ
	DWORD				str_dwRequiredTierAttackPowerRange[2];	// Ҫ�󹥻�ǿ�ȷ�Χ
	DWORD				str_dwRequiredGuildLevelRange[2];		// Ҫ�󹫻�ȼ���Χ
	GAME_STRING_ID		str_theOverrideSealed;
	GAME_STRING_ID		str_theItemCategory;
	LONGLONG			str_llVisibleClassType;				// 10.30 �����ֶ�
	DWORD				str_dwRegistTime[4];				// 10.30 �����ֶ�
	DWORD				str_dwUnRegistTime[4];				// 10.30 �����ֶ�
	DWORD				str_dwRepeatTimes[4];				// 10.30 �����ֶ�
	LONGLONG			str_llLockType;						// 10.30 �����ֶ�
}SELL_ITEM,*PSELL_ITEM;		// SellItem

typedef struct
{	
	DWORD				str_dwVFunAddr;
	GAME_STRING_ID		str_theId;
	DWORD				str_dwCount;
}CREST_INFO,*PCREST_INFO;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// class
typedef struct  
{
	DWORD					str_dwVFunAddr;
	GAME_STRING_ID			str_theId;				// ��ְҵ��֧id
	GAME_STRING_ID			str_theApDisplayType;
	GAME_STRING_VF_ID		str_theClassName;		// ��Ӣ��ӳ��
	GAME_STRING_ID_			str_theModelPath;
	GAME_STRING_ID_			str_theVillageSimplifiedModelPath;
	GAME_STRING_ID_			str_theStageSimplifiedModelPath;
	XYZ						str_theScale;
	BYTE					str_theIsCreateableClass;		// �ɴ�����ɫְҵ = 1 �����ɴ�����ɫְҵ = 0
	FLOAT					str_fJumpHeight;
	FLOAT					str_fJumpGravity;
	struct  
	{
		DWORD				str_dwVFunAddr;
		DWORD				str_dwType;
		FLOAT				str_fRadius;
		FLOAT				str_fHeight;
		XYZ					str_theBoxSize;
	}theCollisionShape;
	GAME_STRING_ID			str_theSkinType;		// +F0
	GAME_STRING_ID			str_theActionListId;				// ְҵ����id
	GAME_STRING_ID			str_theStageDefaultActionId;		// ����Ĭ��״̬
	GAME_STRING_ID			str_theVillageDefaultActionId;		// ����Ĭ��״̬
	GAME_STRING_ID			str_theLevelUpActionId;
	GAME_STRING_ID			str_theClassChangeActionId;			// +17C
	GAME_STRING_ID			str_theClassSelectSoundEventId;
	GAME_STRING_ID			str_theClassCreateSoundEventId;
	BINARY_TREE_MAP			str_theDefaultStatus;						// +1D0	 Ĭ�Ͻ�ɫ״̬
	GAME_STRUCT_ARRAY_POINT	str_theEquipCategories;						// +1E0  װ�����ͣ� ��ְҵ�ɴ�����װ������
	FLOAT					str_fSpecialAttackTargetingAngleRange[2];
	BINARY_TREE_MAP			str_theSkillCategories;						// +1F8  ְҵ��֧
	BINARY_TREE_MAP			str_theSpecialAttackSettings;				// +208  ���⹥������
	GAME_STRUCT_ARRAY_POINT	str_theEffects;
	GAME_STRUCT_ARRAY_POINT	str_theDeadlySkillReadyEffects;
	BINARY_TREE_MAP			str_theDefaultMeshInfos;		// +238
	GAME_STRUCT_ARRAY_POINT	str_theDefaultBuffInfos;
	GAME_STRUCT_ARRAY_POINT	str_theDefaultSkills;			// +258  Ĭ�ϼ���
	GAME_STRUCT_ARRAY_POINT	str_theAwakenDefaultSkills;		// +268  Ĭ�Ͼ��Ѽ���
	BINARY_TREE_MAP			str_theDefaultEquipment;		// +278	 Ĭ��װ��
	BINARY_TREE_MAP			str_theDefaultQuickSlot;		// +288  Ĭ�Ͽ��������
	GAME_STRING_ID			str_theDefaultQuest;			// +298	 Ĭ������id	
	GAME_STRING_ID			str_theDefaultStage;			// +2B0	 Ĭ�ϸ���id
	struct  
	{
		DWORD				str_dwVFunAddr;
		struct  
		{
			DWORD			str_dwVFunAddr;
			GAME_STRING_ID	str_theBrief;
		}theBrief;
		GAME_STRING_ID		str_theDifficulty;
	}theDescription;		// +2D0
	GAME_STRING_ID			str_theStartModeForStage;					// +310		����ģʽΪ����ģʽ
	GAME_STRING_ID			str_theStartModeForVillage;					// +32C		����ģʽΪ��ƽģʽ
	GAME_STRUCT_ARRAY_POINT	str_theRandomModeChange;
	GAME_STRING_ID_			str_theCriticalHitSoundPath;
	GAME_STRUCT_ARRAY_POINT	str_theOverrideActions;
	struct
	{
		DWORD				str_dwVFunAddr;
		BINARY_TREE_MAP		str_theCustomizingPartInfos;
		GAME_STRUCT_ARRAY_POINT	str_theSelectableSkinColors;
	}theCustomizingInfo;												// +388
	struct
	{
		DWORD				str_dwVFunAddr;
		BINARY_TREE_MAP		str_theCustomizingPartDatas;
		DWORD				str_dwSelectedSkinColorIndex;
	}theCustomizingData;												// +3AC
	FLOAT					str_fWeaponDurabilityDecreaseRate;
	FLOAT					str_fArmorDurabilityDecreaseRate;
	FLOAT					str_fAccessoryDurabilityDecreaseRate;
	struct
	{
		DWORD				str_dwVFunAddr;
		BYTE				str_bUseHpInsteadOfMp;
		GAME_STRUCT_ARRAY_POINT		str_theAddBuffs;
		GAME_STRUCT_ARRAY_POINT		str_theRemoveBuffs;
		GAME_STRUCT_ARRAY_POINT		str_theBuffListToBeErased;
	}theClassAwakenInfo;		// +3D0
	struct  
	{
		DWORD				str_dwVFunAddr;
		GAME_STRING_ID		str_theGaugeType;
		DWORD				str_dwGaugeMaxValue;
	}theSpecialGaugeInfo;		// +408
}SDB_CLASS_INFO,*PSDB_CLASS_INFO;

typedef struct
{
	NODE					str_theNode;
	GAME_STRING_ID			str_theId;
	struct
	{
		DWORD				str_dwVFunAddr;
		GAME_STRING_ID		str_theId;
		GAME_STRING_VF_ID	str_theName;
		BINARY_TREE_MAP		str_theSkills;
	}theSkillCategory;
	DWORD					str_dwUnKnow1;
}SDB_SKILL_CATEGORY,*PSDB_SKILL_CATEGORY;

typedef struct
{
	NODE					str_theNode;
	GAME_STRING_ID			str_theId;
	GAME_STRING_ID			str_theId2;
	DWORD					str_dwMaxSkillLevel;
	DWORD					str_dwUnKnow2;
}SKILL_CATEGORY,*PSKILL_CATEGORY;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �����ͳ���֮���ӳ���ϵ
typedef struct
{
	DWORD					str_dwVFunAddr;
	GAME_STRING_ID			str_theId;
	GAME_STRING_VF_ID		str_theName;
	GAME_STRING_ID_			str_theWorldMapImagePath;
	GAME_STRING_ID_			str_theStageSelectBackgroundImagePath;
	GAME_STRUCT_ARRAY_POINT		str_theStageIds;					// �����ͳ���ӳ��
	GAME_STRUCT_ARRAY_POINT		str_theStageGroups;
	DWORD						str_dwMinLevelToEnter;
}SDB_REGION_INFO,*PSDB_REGION_INFO;		// Apple::Sdb::RegionInfo



// ��ɫ��̬��Ϣ
typedef struct
{
	GAME_STRING_ID				str_thePlayerName;
	DWORD						str_dwSerial;

	struct
	{
		DWORD						str_dwVFunAddr;
		DWORD						str_dwUnKnow1;
		struct
		{
			DWORD					str_dwVFunAddr;
			GAME_STRING_ID			str_thePlayerName;
			LONGLONG				str_llPlayerSerial;
			DWORD					str_dwPlayerGender;
			DWORD					str_dwClassType;			// ����ʿ = 1,ն�� = 3, ��ħʦ = 9 �ʹ�����ɫʱ��ClassType��ͬ
			DWORD					str_dwCreatedDateTime[4];
			BYTE					str_bIsDeleted;
			DWORD					str_dwUnKnow2;
		}theStaticPlayerInfo;
		struct
		{
			DWORD					str_dwVFunAddr;
			DWORD					str_dwGameLv;
			DWORD					str_dwGameXp;
			DWORD					str_dwUnKnow3[2];
			DWORD					str_dwGold;
			DWORD					str_dwFriendPoint;
			BYTE					str_bFriendApplyDenyOption;
			DWORD					str_dwFriendApplyDenyOption;
			DWORD					str_dwResurrectionStoneCount_PcCafe;
			DWORD					str_dwResurrectionStoneCount_Daily;
			DWORD					str_dwResurrectionStoneCount;
			DWORD					str_dwTalentLv;
			DWORD					str_dwFatigue;
			DWORD					str_dwEventFatigue;
			DWORD					str_dwPremiumFatigue;
			DWORD					str_dwMembershipFatigue;
			DWORD					str_dwSpentFatigue;
			DWORD					str_dwTierAttackPower;
			// ....
		}theDynamicPlayerInfo;
		// ....
	}thePlayerInfo;

}PLAYER_INFO,*PPLAYER_INFO;

typedef struct  
{
	DWORD				str_dwClassType;		// ������Ƕ�Ӧ��class����
	GAME_STRING_ID		str_theClass;			// ���罣ħ��ն�񣬽���ʿ��Ӣ�Ĵ�д������ �磺 "WARRIOR" "GLADIBERSERKER" 
}CALSS_CLASSTYPE_,*PCALSS_CLASSTYPE_;

typedef struct
{
	CALSS_CLASSTYPE_ theClass[20];		// �����Сδ֪�����Ǹ�20����
}CALSS_CLASSTYPE,*PCALSS_CLASSTYPE;

typedef struct
{
	NODE			str_theNode;
	DWORD			str_dwNullAddr;
	GAME_STRING_ID_	str_theId;
	DWORD			str_dwVFunAddr;
	DWORD			str_dwLevel;
}FB_LEVEL,*PFB_LEVEL;

typedef struct 
{
	NODE				str_theNode;
	GAME_STRING_ID		str_theSectorId;
	GAME_STRING_VF_ID	str_theMapId;
}MAP_INFO,*PMAP_INFO;

typedef struct
{
	NODE				str_theNode;
	GAME_STRING_ID_		str_theId;
}BOOS_INFO,*PBOOS_INFO;

typedef struct 
{
	DWORD			str_dwVFunAddr;
	DWORD			str_dwObjAddr;
	DWORD			str_dwObjAddrPoint;
	GAME_STRING_ID	str_theId;
	DWORD			str_dwLevel;
	DWORD			str_dwUnKnow2;
	BINARY_TREE_MAP	str_theAlreadyClearSector;		// �Ѿ���������ĸ����������մ��꿪�ź�ķ���
}MAP_DATA,*PMAP_DATA;

typedef struct
{
	NODE			str_theNode;
	GAME_STRING_ID	str_theId;
}CLEAR_SECTOR,*PCLEAR_SECTOR;		// ����յķ���

typedef struct
{
	NODE				str_theNode;
	GAME_STRING_ID		str_theTaskNpcId;
	DWORD				str_dwNpcTaskObjAddr;
	DWORD				str_dwNpcTaskObjPoint;
	DWORD				str_dwAccpetFlag;			// һ��δ֪�ı�־
}TASK_NPC_OBJ,*PTASK_NPC_OBJ;

typedef struct  
{
	NODE				str_theNode;
	GAME_STRING_ID		str_theId;
}CAN_ACCPET_NPC_TASK,CAN_COMPLETE_NPC_TASK,*PCAN_ACCPET_NPC_TASK,*PCAN_COMPLETE_NPC_TASK;

typedef struct  
{
	DWORD				str_dwVFunAddr;
	GAME_STRING_ID		str_theId;
	DWORD				str_dwLevel;
	DWORD				str_dwBonusPoint;
	GAME_STRUCT_ARRAY_POINT		str_theEventOptions;
	LONGLONG					str_llOidSkill;
	DWORD						str_dwBonusCooldown;
	DWORD						str_dwSkillId;
}APPLE_SKILL,*PAPPLE_SKILL;

typedef struct
{
	NODE	theNode;
	DWORD	dwFlag;
	GAME_STRUCT_ARRAY_POINT	theSkillArrayAddr;
	bool    bUnKnow;
	bool	bFlag;
}SKILL_OBJ_ADDR,*PSKILL_OBJ_ADDR;


typedef struct		// Apple::Item
{
	DWORD				str_dwVFunAddr;
	GAME_STRING_ID		str_theItemId;					// ��Ʒid
	GAME_STRING_ID_		str_thePrefixOptionName;		// ��Ʒ����
	LONGLONG			str_llSerial;					// ��Ʒ���
	DWORD				str_dwItemObjAddr;				// ��Ʒģ�����
	DWORD				str_dwItemObjPoint;				// ��Ʒģ�����ָ�����
	DWORD				str_dwStackCount;				// ��Ʒ��������
	GAME_STRING_ID		str_theGradeId;					// ��ƷƷ��
	FLOAT				str_fDurability;				// ��Ʒ�;�
	GAME_STRUCT_ARRAY_POINT		str_theIncreaseStatusList;		// +74 װ������
	GAME_STRUCT_ARRAY_POINT		str_theEventOptions;			// +84
	GAME_STRUCT_ARRAY_POINT		str_theIdentifiedOptions;		// +94 ��������
	DWORD						str_dwUnKnow1;
	struct
	{
		DWORD					str_dwVFunAddr;
		DWORD					str_dwVersion;
		DWORD					str_dwUnBindCount;
		DWORD					str_dwReidentifyCount;
		DWORD					str_dwEventOptionChangeCount;
		DWORD					str_dwAddBonusLevel;
		DWORD					str_dwExpirationTime[4];
		GAME_STRUCT_ARRAY_POINT	str_theMasteryStatusIds;
		DWORD					str_dwRebalanceVersion;		// 10.30�������ݶ�
	}theExtendData;	// +A8
	DWORD						str_dwUnKnow2;		// 10.30����δ֪����
	BYTE						str_bIsSealed;
	BYTE						str_bIsUnidentified;
	BYTE						str_bIsTradable;
	DWORD						str_dwGoldValue;
	BINARY_TREE_MAP				str_theStatus;					// +E8	װ����������
	BINARY_TREE_MAP				str_theEnhanceFactors;
	// ...
}APPLE_ITEM,*PAPPLE_ITEM;

typedef struct
{
	NODE				str_theNode;
	GAME_STRING_ID		str_theStatusId;
	FLOAT				str_fValue;
}ITEM_STATUS_VALUE,*PITEM_STATUS_VALUE;

typedef struct
{
	DWORD				str_dwVFunAddr;
	GAME_STRING_ID		str_theStatusId;
	DWORD				str_dwIncreaseType;
	FLOAT				str_fValue;
	FLOAT				str_fRelativeRate;
}ITEM_STATUS_VALUE_,*PITEM_STATUS_VALUE_;		// "Apple::IncreaseStatus"

typedef void (*PFUN_PRINT)(DWORD lpSubTreeRoot);

void Traverse( DWORD lpSubTreeRoot, DWORD dwNullNode, PFUN_PRINT pFunPrint);

typedef struct
{
	NODE		theNode;
	DWORD		dwSerial;
	DWORD		dwLocalObjAddr;
	DWORD		dwLocalObjPointAddr;
}PREV_ACTION_PLAY_TIME_1,*PPREV_ACTION_PLAY_TIME_1;

typedef struct
{
	DWORD		dwLocalObjAddr;
	DWORD		dwSerial;
	BINARY_TREE_MAP	theMapAddr;
}PREV_ACTION_PLAY_TIME_2,*PPREV_ACTION_PLAY_TIME_2;

typedef struct
{
	NODE		theNode;
	DWORD		dwUnKnow1;
	DWORD		dwLocalObjAddr;
	DWORD		dwLocalObjPointAddr;
}PREV_ACTION_PLAY_TIME_3,*PPREV_ACTION_PLAY_TIME_3;

#endif  //_CLASSA_H_