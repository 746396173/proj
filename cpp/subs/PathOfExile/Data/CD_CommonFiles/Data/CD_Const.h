#pragma once
/*
@author zhp
@date 2017/1/24 17:21
*/
#include <ProtocolX/P_DefinesX.h>
#include <string>

//state name
const std::wstring CD_StateNamePreGameState = L"PreGameState";
const std::wstring CD_StateNameSelectCharacterState = L"SelectCharacterState";
const std::wstring CD_StateNameCreateCharacterState = L"CreateCharacterState";		//������ɫ��ʱ��������״̬
const std::wstring CD_StateNameInGameState = L"InGameState";
const std::wstring CD_StateNameAreaLoadingState = L"AreaLoadingState";		//���ص�ͼ
const std::wstring CD_StateNameEscapeState = L"EscapeState";				//EscapeMenu������ʱ��
const std::wstring CD_StateNameLoginState = L"LoginState";

//������
#ifdef VER_GJ_
const pt_cwsz kMonTransitionableName[] = {
	L"Azmeri Ancestor",
	L"Doedre the Vile",
	L"Lunaris, Eternal Moon",
	L"Solaris, Eternal Sun",
	L"Threshold of Anger",
	L"Threshold of Hatred",
	L"Threshold of Wrath"
};
#else
const pt_cwsz kMonTransitionableName[] = {
	L"����Ī������",
	L"���ߵ���",
	L"��������",
	L"��������",
	L"��������", 
	L"��Ǽ�����",
	L"�ɵ�",
	L"����֮��������",
	L"��ҫ֮��ʷ����Ŭ˹",
	L"��������ȭ�¿���ά��",
	L"������",
	L"��ӰѦ��",
	L"���������׸���",
	L"����֮��³��˹",
	L"������׸���",
	L"��Ӱ������-ĺɫ",
	L"��ҫ������-����",
	L"����ʹͽ��ʿ",
};
#endif

//�Զ�ѡ������
const std::wstring CD_AutoSelectGateway = L"Auto-select Gateway";

//���������
const std::wstring CD_RenderName_CityPortalDoor = L"��������";
const std::wstring CD_RenderName_YiJieDoor = L"���֮��";

const int CD_kMaxStrLen = 0x100;
const int CD_kMaxNameLen = 50;
const int CD_kMaxFilePathLen = 0x100;

//ְҵ����
enum enCD_ProfessionType : pt_byte{
	kPT_GuiZu = 0,					//����
	kPT_YeManRen = 1,				//Ұ����
	kPT_YouXia = 2,					//����
	kPT_NvWu = 3,					//Ů��
	kPT_JueDouZhe = 4,				//������
	kPT_ShengTangWuSeng = 5,		//ʥ����ɮ
	kPT_AnYing = 6,					//��Ӱ
	kPT_Mask = 7,					//�ܹ�7��ְҵ
};

//��ͼϵ��
const int CD_kMapRatio = 0x17;
//> 0��ͨ��
enum enCD_MapDataFlag : pt_byte{
	//���Ϊ0��ʾ�õ�������
	kMDF_EmptyPoint = 0,		//��һ��ʼҲ��0���򿪺�ͱ��5(Ҳ�п���������ֵ���ø��ݵ�ʱ�ĵ���������)
	kMDF_Mountain = 1,			//������ɽ
	kMDF_Grass = 2,				//�ݵ�
	kMDF_LikeGrass = 3,			//�Ȳݵ�Ҫϡ��ĵ�
	kMDF_GroundFlat = 5,		//����ƽ̹
	kMDF_MaxMask = 0xf,			//��಻�ᳬ��0xf
};

//��ǰ��ͼ�Ѷ�
enum enCD_kMapDifficulty : int{
	kMD_Invalid = 0,	//˳��Ҫ��
	kMD_Normal,			//һ��
	kMD_Cruel,			//�п�
	kMD_Merciless,		//����
	KMD_Max,
};
//////////////////////////////////////////////////////////////////////////
const pt_csz CD_kAttrInfoMonster = "Monster";
const pt_csz CD_kAttrInfoPlayer = "Player";
const pt_csz CD_kAttrInfoClientNpc = "ClientNPC";
const pt_csz CD_kAttrInfoNpc = "NPC";
const pt_csz CD_kAttrInfoMinimapIcon = "MinimapIcon";
const pt_csz CD_kAttrInfoAreaTransition = "AreaTransition";
const pt_csz CD_kAttrInfoBase = "Base";		//����ȡ��Ʒ�Ļ�������
const pt_csz CD_kAttrInfoQuality = "Quality";
const pt_csz CD_kAttrInfoStack = "Stack";
const pt_csz CD_kAttrInfoAttributeRequirements = "AttributeRequirements";
const pt_csz CD_kAttrInfoMods = "Mods";
const pt_csz CD_kAttrInfoSockets = "Sockets";
const pt_csz CD_kAttrInfoArmour = "Armour";
const pt_csz CD_kAttrInfoSkillGem = "SkillGem";
const pt_csz CD_kAttrInfoRender = "Render";
const pt_csz CD_kAttrInfoPositioned = "Positioned";
const pt_csz CD_kAttrInfoLife = "Life";
const pt_csz CD_kAttrInfoActor = "Actor";
const pt_csz CD_kAttrInfoPathfinding = "Pathfinding";
const pt_csz CD_kAttrInfoChest = "Chest";
const pt_csz CD_kAttrInfoWorldItem = "WorldItem";
const pt_csz CD_kAttrInfoTransitionable = "Transitionable";
const pt_csz CD_kAttrInfoPortal = "Portal";		//ʹ�ô��;��ᣬ��������ź󣬱����͵��ĵط�����RenderName:��������
const pt_csz CD_kAttrInfoUsable = "Usable";
const pt_csz CD_kAttrInfoCharges = "Charges";
const pt_csz CD_kAttrInfoFlask = "Flask";
const pt_csz CD_kAttrInfoTargetable = "Targetable";
const pt_csz CD_kAttrInfoDiesAfterTime = "DiesAfterTime";		//��Ҫ�����Ĺ������������
const pt_csz CD_kAttrInfoTriggerableBlockage = "TriggerableBlockage";		//������������Եģ����ź󣬻���ĵ�ͼ����Ϊ��ͨ���ġ�
const pt_csz CD_kAttrInfoMovement = "Movement";

//////////////////////////////////////////////////////////////////////////
const pt_cwsz CD_kMetaMonster = L"/Monsters";
const pt_cwsz CD_kMetaPlayer = L"/Characters";
const pt_cwsz CD_kMetaNpc = L"/NPC";
const pt_cwsz CD_kMetaWaypoint = L"/Waypoint";
const pt_cwsz CD_kMetaAreaTransition = L"/AreaTransition";
const pt_cwsz CD_kMetaItems = L"/Items";
const pt_cwsz CD_kMetaStash = L"Objects/Stash";							//Metadata/MiscellaneousObjects/Stash
const pt_cwsz CD_kMetaNoticeBoard = L"Objects/NoticeBoard";				//Metadata/MiscellaneousObjects/NoticeBoard
const pt_cwsz CD_kMetaNoticeBoardPvP = L"Objects/NoticeBoardPvP";		//Metadata/MiscellaneousObjects/NoticeBoardPvP
const pt_cwsz CD_kMetaWorldItem = L"/WorldItem";			//Metadata/MiscellaneousObjects/WorldItem
const pt_cwsz CD_kMetaChest = L"/Chests/";				//Metadata/Chests/ProdWounded1
const pt_cwsz CD_kMetaMapDevice = L"MiscellaneousObjects/MapDevice";
const pt_cwsz CD_kMetMappingDevice = L"Hideouts/Objects/StrDexIntMappingDevice";
const pt_cwsz CD_kMetBellyArenaTransition = L"/Belly/Objects/BellyArenaTransition";
const pt_cwsz CD_kMetMaligaroOrrery = L"QuestObjects/Act7/MaligaroOrrery";
const pt_cwsz CD_kMetKaruiSlave = L"Monsters/KaruiSlave/KaruiSlave";
//////////////////////////////////////////////////////////////////////////
//******************��Ʒ���
const int CD_kBagItemArraySideSize = 50;
//�����������ߴ�
const int CD_kBagItemArrayMaxSize = CD_kBagItemArraySideSize * CD_kBagItemArraySideSize;
//��ʯ��������
const int CD_kGemSlotMaxCnt = 6;
//����ƿ���������
const int CD_kBodyFlaskMaxCnt = 5;

//��ʯ�����ɫ
enum enCD_GemSlotColor{
	kGSC_Red = 1,		//��ɫ
	kGSC_Green = 2,		//��ɫ
	kGSC_Blue = 3,		//��ɫ
	KGSC_White = 4,		//��ɫ
	kGSC_Invalid = 5,	//��Ч
};

//��Ʒ��ɫ����Ʒ���ֵ���ɫ
enum enCD_ItemColor{
	kIC_Non = -1,
	kIC_White = 0,	//��
	kIC_Blue,		//��
	kIC_Yellow,		//��
	kIC_Gold,		//��
	KIC_Max,
};

//��Ʒ�������ԣ���������������
enum enCD_ItemRequireAttr{
	kIRA_Power = 0,	//����
	kIRA_Smart,		//����
	kIRA_Brain,		//����
	kIRA_Max,
};

//�����ṹ����
enum enCD_InventoryType{
	kIT_Invalid = 0,			//ö��˳��Ҫ�ı�
	kIT_MainBag = 1,			//���ﱳ��
	kIT_BodyArmour,				//�·�����
	kIT_WeaponLeft,				//����������ֻ�ܱ�������ǰѡ�����������
	kIT_WeaponRight,			//��������
	kIT_Helm,					//ͷ��
	kIT_Necklace,				//����
	kIT_RingLeft,				//���ֽ�ָ
	kIT_RingRight,				//���ֽ�ָ
	kIT_Glove,					//����
	kIT_Shoe,					//Ь��
	kIT_Belt,					//����
	kIT_Flasks,					//ƿ�ӣ�5��ƿ�Ӷ����������
	kIT_Cursor1,
	kIT_Map1,
	kIT_WeaponLeftHide,			//������������ǰû��ѡ����Ǹ���������
	kIT_WeaponRightHide,		//������������ǰû��ѡ����Ǹ���������
	kIT_AltarSmall1,
	kIT_AltarSmall2,
	kIT_AltarMedium1,
	kIT_AltarMedium2,
	kIT_AltarMedium3,
	kIT_AltarLarge1,
	kIT_AltarLarge2,
	kIT_AltarLarge3,
	kIT_BodyEquiqMax,
	//�ֿ�
	kIT_StashTab_1 = 31,		//�򿪲ֿ��ʱ��������ڵ���Щ 2
	kIT_StashTab_2,	
	kIT_StashTab_3,	
	kIT_StashTab_4,
	kIT_Max,
};

enum enCD_AttrInventoryEquipType{
	kAIET_WeaponLeft = 0,
	kAIET_WeaponRight,
	kAIET_BodyArmour,		//�·�����
	kAIET_Helm,				//ͷ��
	kAIET_Necklace_Glove,	//�������֣����Ǹ�bug
	kAIET_Shoe,				//Ь��
	kAIET_Ukn,
	kAIET_RingLeft,			//���ֽ�ָ
	kAIET_RingRight,		//���ֽ�ָ
	kAIET_Belt,				//����
	kAIET_Max,
};

//��Ϸ�ﲢû�������ö�ٳ������Լ������ⶨ����ֵ
enum enCD_ItemType{
	kITYPE_Invalid = 0,
	kITYPE_LifeFlask,				//����ҩ��
	kITYPE_ManaFlask,				//ħ��ҩ��
	kITYPE_HybridFlask,				//����ҩ��
	kITYPE_UtilityFlask,			//����ҩ��
	kITYPE_UtilityFlaskCritical,	//����ҩ��
	kITYPE_StackableCurrency,		//�ɶѵ�ͨ��
	kITYPE_ActiveSkillGem,		//�������ܱ�ʯ
	kITYPE_SupportSkillGem,		//�������ܱ�ʯ
	kITYPE_Helmet,				//ͷ��
	kITYPE_Amulet,				//����
	kITYPE_Belt,				//����
	kITYPE_Ring,				//��ָ
	kITYPE_Boots,				//Ь��
	kITYPE_Gloves,				//����
	kITYPE_BodyArmour,			//�ؼ�
	kITYPE_Shield,				//��			--����
	kITYPE_Currency,			//ͨ��
	kITYPE_Claw,				//צ			--����  �����ֶ����Դ�  �������뷨�ȴ���
	kITYPE_Dagger,				//ذ��		--����  �����ֶ����Դ�
	kITYPE_Wand,				//����		--����  ֻ�������� ����ͬ���͵����
	kITYPE_QuestItem,			//������Ʒ
	kITYPE_OneHandSword,		//���ֽ�
	kITYPE_ThrustingOneHandSword,	//ϸ��
	kITYPE_OneHandAxe,			//���ָ�
	kITYPE_OneHandMace,			//���ִ�		--����  �����ֶ����Դ�
	kITYPE_Bow,					//��
	kITYPE_Staff,				//����		--˫��
	kITYPE_TwoHandSword,		//˫�ֽ�
	kITYPE_TwoHandAxe,			//˫�ָ�
	kITYPE_TwoHandMace,			//˫�ִ�
	kITYPE_Quiver,				//����
	kITYPE_SmallRelic,			//С��ʥ��
	kITYPE_MediumRelic,			//����ʥ��
	kITYPE_LargeRelic,			//����ʥ��
	kITYPE_Sceptre,				//����
	kITYPE_Map,					//����ͼ
	kITYPE_FishingRod,			//���
	kITYPE_MapFragment,			//��ͼ��Ƭ
	kITYPE_HideoutDoodad,		//����װ��
	kITYPE_Microtransaction,	//�̳���Ʒ
	kITYPE_Jewel,				//�鱦
	kITYPE_DivinationCard,		//���˿�
	kITYPE_LabyrinthItem,		//�Թ���Ʒ
	kITYPE_LabyrinthTrinket,	//�Թ���Ʒ
	kITYPE_LabyrinthMapItem,	//����Թ���Ʒ
	kITYPE_Breachstone,			//��϶֮ʯ
	kITYPE_Leaguestone,			//����ʯ
	kITYPE_Unarmed,				//û��������  --- ����ı���û������
	kITYPE_Max,
};

//ʹ������
enum enCD_UsableType{
	kUT_Invalid = 0,
	kUT_UseItem = 1,		//����Ҽ�����ֱ��ʹ��
	kUT_UseItemTo,			//ʹ����Ʒ������
	kUT_Ukn1,
	kUT_Ukn2,
	kUT_Ukn3,
	kUT_Ukn4,
	kUT_Max,
};
static_assert(7 == kUT_Max, "");

//ö��˳�����ֵ��Ҫ���ı�
enum enCD_FlaskType{
	kFT_Invalid = 0,
	kFT_Hp,				//Metadata/Items/Flasks/FlaskLife11
	kFT_Mp,				//Metadata/Items/Flasks/FlaskMana11
	kFT_Hybrid,			//������ҩ��������Ѫ�ּ�����Metadata/Items/Flasks/FlaskHybrid2
	kFT_Utility,		//�������Եģ���Ҫ�����ƶ��ٶȰ�,Metadata/Items/Flasks/FlaskUtility6
	kFT_Max,
};

enum enCD_ValueType{
	kVT_Hp = 0xd,
	kVT_Mp = 0xf,
	kVT_Time = 0x12,		//����������ڻظ�һ����������kFVI_Time��value / 10 = �롣Ҳ�����ǳ���ʱ�䣬�������������
};

enum enCD_SendItemOperFlag : pt_byte{
	kSIOF_Normal = 0,
};
//////////////////////////////////////////////////////////////////////////
//********************GameLogic��OperateCommand
const pt_cwsz CD_kLOC_Destroy = L"destroy";
const pt_cwsz CD_kLOC_Remaining = L"remaining";
//////////////////////////////////////////////////////////////////////////
//*********************�ļ�db·��
const pt_cwsz CD_kFileDbPath_Words = L"Data/Words.dat";
const pt_cwsz CD_kFileDbPath_PassiveSkill = L"Data/PassiveSkills.dat";
const pt_cwsz CD_kFileDbPath_PassiveSkillGraph = L"Metadata/PassiveSkillGraph.psg";
const pt_cwsz CD_kFileDbPath_Quest = L"Data/Quest.dat";
const pt_cwsz CD_kFileDbPath_QuestStates = L"Data/QuestStates.dat";
const pt_cwsz CD_kFileDbPath_ActiveSkills = L"Data/ActiveSkills.dat";
const pt_cwsz CD_kFileDbPath_BaseItemTypes = L"Data/BaseItemTypes.dat";
const pt_cwsz CD_kFileDbPath_ItemClasses = L"Data/ItemClasses.dat";
const pt_cwsz CD_kFileDbPath_SkillGems = L"Data/SkillGems.dat";
const pt_cwsz CD_kFileDbPath_GemTags = L"Data/GemTags.dat";
const pt_cwsz CD_kFileDbPath_GrantedEffects = L"Data/GrantedEffects.dat";
const pt_cwsz CD_kFileDbPath_GrantedEffectsPerLevel = L"Data/GrantedEffectsPerLevel.dat";		//�ṹ��û�з�����ȫ������Ϊû��Ҫ
const pt_cwsz CD_kFileDbPath_WorldAreas = L"Data/WorldAreas.dat";
const pt_cwsz CD_kFileDbPath_LabyrinthTrials = L"Data/LabyrinthTrials.dat";
const pt_cwsz CD_kFileDbPath_Labyrinths = L"Data/Labyrinths.dat";
const pt_cwsz CD_kFileDbPath_LabyrinthAreas = L"Data/LabyrinthAreas.dat";		//ħ���Թ�
const pt_cwsz CD_kFileDbPath_LabyrinthSection = L"Data/LabyrinthSection.dat";
const pt_cwsz CD_kFileDbPath_LabyrinthSectionLayout = L"Data/LabyrinthSectionLayout.dat";
const pt_cwsz CD_kFileDbPath_LabyrinthExclusionGroups = L"Data/LabyrinthExclusionGroups.dat";
const pt_cwsz CD_kFileDbPath_LabyrinthNodeOverrides = L"Data/LabyrinthNodeOverrides.dat";
const pt_cwsz CD_kFileDbPath_Difficulties = L"Data/Difficulties.dat";
const pt_cwsz CD_kFileDbPath_MapPins = L"Data/MapPins.dat";			//��ͼ���������WorldArea
const pt_cwsz CD_kFileDbPath_MinimapIcons = L"Data/MinimapIcons.dat";
const pt_cwsz CD_kFileDbPath_NPCs = L"Data/NPCs.dat";
const pt_cwsz CD_kFileDbPath_NPCShop = L"Data/NPCShop.dat";
const pt_cwsz CD_kFileDbPath_NPCAudio = L"Data/NPCAudio.dat";
const pt_cwsz CD_kFileDbPath_NPCTalk = L"Data/NPCTalk.dat";
const pt_cwsz CD_kFileDbPath_NPCTextAudio = L"Data/NPCTextAudio.dat";
const pt_cwsz CD_kFileDbPath_MapConnections = L"Data/MapConnections.dat";
const pt_cwsz CD_kFileDbPath_Tags = L"Data/Tags.dat";
const pt_cwsz CD_kFileDbPath_DropPool = L"Data/DropPool.dat";
const pt_cwsz CD_kFileDbPath_Characters = L"Data/Characters.dat";
const pt_cwsz CD_kFileDbPath_NPCMaster = L"Data/NPCMaster.dat";
const pt_cwsz CD_kFileDbPath_NPCMasterExperiencePerLevel = L"Data/NPCMasterExperiencePerLevel.dat";
const pt_cwsz CD_kFileDbPath_Mods = L"Data/Mods.dat";
const pt_cwsz CD_kFileDbPath_ModType = L"Data/ModType.dat";
const pt_cwsz CD_kFileDbPath_ModSellPriceTypes = L"Data/ModSellPriceTypes.dat";
const pt_cwsz CD_kFileDbPath_Stats = L"Data/Stats.dat";
const pt_cwsz CD_kFileDbPath_AchievementItems = L"Data/AchievementItems.dat";
const pt_cwsz CD_kFileDbPath_CurrencyItems = L"Data/CurrencyItems.dat";		//����ͨ����Ʒ
const pt_cwsz CD_kFileDbPath_Topologies = L"Data/Topologies.dat";
const pt_cwsz CD_kFileDbPath_SoundEffects = L"Data/SoundEffects.dat";
const pt_cwsz CD_kFileDbPath_Chests = L"Data/Chests.dat";
const pt_cwsz CD_kFileDbPath_WeaponTypes = L"Data/WeaponTypes.dat";
const pt_cwsz CD_kFileDbPath_MonsterResistances = L"Data/MonsterResistances.dat";
const pt_cwsz CD_kFileDbPath_MonsterTypes = L"Data/MonsterTypes.dat";
const pt_cwsz CD_kFileDbPath_MonsterVarieties = L"Data/MonsterVarieties.dat";
const pt_cwsz CD_kFileDbPath_BloodTypes = L"Data/BloodTypes.dat";
const pt_cwsz CD_kFileDbPath_ClientStrings = L"Data/ClientStrings.dat";
const pt_cwsz CD_kFileDbPath_ItemVisualIdentity = L"Data/ItemVisualIdentity.dat";
const pt_cwsz CD_kFileModel_ArmoursShields = L"Art/Models/Items/Armours/Shields/ShieldInt/ShieldI";
const pt_cwsz CD_kFileDbPath_Environments = L"Data/Environments.dat";
const pt_cwsz CD_kFileDbPath_Music = L"Data/Music.dat";
const pt_cwsz CD_kFileDbPath_BuffDefinitions = L"Data/BuffDefinitions.dat";
const pt_cwsz CD_kFileDbPath_SkillStatDescriptions = L"Metadata/StatDescriptions/skillpopup_stat_filters.txt";
const pt_cwsz CD_kFileDbPath_MinionSpellSkillStat = L"Metadata/StatDescriptions/minion_spell_skill_stat_descriptions.txt";
const pt_cwsz CD_kFileDbPath_CraftingBenchOptions = L"Data/CraftingBenchOptions.dat";
const pt_cwsz CD_kFileDbPath_ChestEffects = L"Data/ChestEffects.dat";
const pt_cwsz CD_kFileDbPath_Strongboxes = L"Data/Strongboxes.dat";
//////////////////////////////////////////////////////////////////////////
//*****************�������
//��������ӵ�����
enum enCD_DownInventoryType{
	kDIT_Invalid = -1,
	kDIT_Flask1 = 0,	//ƿ��1
	kDIT_Flask2,
	kDIT_Flask3,
	kDIT_Flask4,
	kDIT_Flask5,
	kSGT_LeftBt,		//������
	kSGT_MiddleBt,
	kSGT_RightBt,
	kSGT_KeyQ,
	kSGT_KeyW,
	kSGT_KeyE,
	kSGT_KeyR,
	kSGT_KeyT,
};

//��ͨ�������ͣ�Ҳ��������ͨ���ܵ�ID
//������Ч��ID�ɣ�����װ���˹���������ı������ֵ����ֻ�������ż��Ķ�������û�м�ʸ����Ч�����ˡ�
enum enCD_WeaponSkillType{
	kWST_Zhua = 0x7,				//צ
	kWST_BiShou = 0x8,			//ذ��
	kWST_SingleShortJian = 0xa,	//���ֽ����⽣�������С�����
	kWST_SingleFu = 0xc,		//���ָ�
	kWST_SingleChui = 0xd,		//���ִ�
	kWST_GongJian = 0xe,		//����
	kWST_LongZhang = 0xf,	//����
	kWST_DoubleJian = 0x10,	//˫�ֽ�
	kWST_DoubleFu = 0x11,	//˫�ָ�
	kWST_DoubleChui = 0x12,	//˫�ִ�
	kWST_SingleZhang = 0x21,		//���ִ���Ӱ�����
	kWST_EmptyWeapon = 0x25,		//��ɫĬ�ϵ���ֵ��������ʱ����ֵ
};
//����������ֿ����й�
enum enCD_SkillTypeValue{
	kSTV_Normal = 0x30,
};

const pt_word CD_kSkillId_NormalHit = 0x4000;		//��ͨ����

//*******buff��
//�������������buff
const std::wstring CD_kBuffEnName_hidden_monster_disable_minions = L"hidden_monster_disable_minions";
const std::wstring CD_kBuffEnName_visual_display_buff_not_hidden = L"visual_display_buff_not_hidden";
const std::wstring CD_kBuffEnName_cannot_be_damaged = L"cannot_be_damaged";
//����ֽⶳ�������buff
const std::wstring CD_kBuffEnName_monolith_monster_freedom = L"monolith_monster_freedom";
//����ֵ�boss
const std::wstring CD_kBuffEnName_monster_rare_effect_buff = L"monster_rare_effect_buff";
//////////////////////////////////////////////////////////////////////////
enum enCD_SkillId : pt_word{
	kSI_OpenObj = 0x266,
};

//���pt_char��Ҫ�ģ���ΪҪ�жϸ�����
enum enCD_TouchTargetSmallFlag : pt_char{
	//kTTSF_Normal = 0x8,			//ԭ����8�����ڱ��0�ˣ�2017/8/7 22:56
	kTTSF_Normal = 0,
	//kTTSF_WithLeftCtrl = 0xc,		//����ctrl���ƶ��ʹ򿪶����Ǵ�ֵ��ԭ����0xc��������4
	kTTSF_WithLeftCtrl = 4,
};

//�Ǹ�byte
enum enCD_TransitionableState : pt_byte{
	kTranState_Block = 1,		//�����ŵģ�����ͨ����
	kTranState_Opened,			//��ͨ���ģ��Ѵ򿪵ġ�����ĳЩ�����ţ����� Թ��֮�����ԭ����1����������boss��Ȼ��������ص��󣬴�ֵ�ͱ��2�ˡ�
};
//////////////////////////////////////////////////////////////////////////
//**************UI���
const int CD_kUiNextStateInfoMax = 0xe;
//������Ϸ״̬�£�Ĭ����ʾ�ĶԻ�������
#ifdef VER_GJ3_
const int CD_kInGameNormalShowDlgMaxCnt = 19;
#elif VER_GF_
const int CD_kInGameNormalShowDlgMaxCnt = 19;
#endif
//EscapeMenu��button
enum enCD_EscapeMenuButton{
	kEMB_Continue = 1,		//������Ϸ
	kEMB_Setting,			//�趨
	kEMB_RetSelect,			//�ص���ɫѡ����
	kEMB_LeaveGame,			//�뿪��Ϸ
};
#ifdef VER_GJ_			//���ʷ�
const std::string CD_kNTL_CotinueA = "Continue";
const std::wstring CD_kNTL_Cotinue = L"Continue";
const std::string CD_kNTL_ByeA = "Goodbye";
const std::wstring CD_kNTL_Bye = L"Goodbye";
const std::string CD_KNTL_BuyA = "Purchase Items";
const std::wstring CD_KNTL_Buy = L"Purchase Items";
const std::string CD_KNTL_SellA = "Sell Items";
const std::wstring CD_KNTL_Sell = L"Sell Items";
const std::wstring CD_kBtTitle_SkillAllTutorials = L"skip all tutorials";
#else					//����
const std::string CD_kNTL_CotinueA = "����";
const std::wstring CD_kNTL_Cotinue = L"����";
const std::string CD_kNTL_ByeA = "�ٻ�";
const std::wstring CD_kNTL_Bye = L"�ٻ�";
const std::string CD_KNTL_BuyA = "������Ʒ";
const std::wstring CD_KNTL_Buy = L"������Ʒ";
const std::string CD_KNTL_SellA = "������Ʒ";
const std::wstring CD_KNTL_Sell = L"������Ʒ";
const std::wstring CD_kBtTitle_SkillAllTutorials = L"��������ָ��";
#endif

//////////////////////////////////////////////////////////////////////////
enum class enCD_EntityAttr_Player{
	kEAP_Positioned = 0,
	kEAP_Stats,
	kEAP_Pathfinding,
	kEAP_Life,
	kEAP_Animated,
	kEAP_Player,		//5
	kEAP_Inventories,
	kEAP_Actor,
	kEAP_Render,
	kEAP_Targetable,		//��ѡ��
	kEntityAttrMaxCnt,		//�ܹ���10��
};

enum class enCD_EntityAttr_Npc{
	kEAN_Positioned = 0,
	kEAN_Animated,
	kEAN_BaseEvents,		//�����¼�
	kEAN_NPC,
	kEAN_MinimapIcon,
	kEAN_Render,		//5
	kEAN_Targetable,
	kEAN_ClientNPC,			//��������Բſ��Է��ʸ�npc
	kEntityAttrMaxCnt,		//�ܹ���8��
};

//���͵�/������
/*
Metadata/Effects/Environment/waypoint/new/WaypointEffect		//���͵���Χ����Ч�����������ǲ������͵㣬���ܽӽ��ĵط���
Metadata/MiscellaneousObjects/Waypoint			//���͵�������
Metadata/MiscellaneousObjects/AreaTransition	//�����ţ������ ʨ������ �� ĺ�⺣̲ �Ĵ�����
*/
enum class enCD_EntityAttr_Waypoint{
	kEAW_Positioned = 0,
	kEAW_BaseEvents,
	kEAW_Animated,
	kEAW_MinimapIcon,
	kEAW_Render,		//4
	kEAW_Targetable,
	kEntityAttrMaxCnt,
};

//������
enum class enCD_EntityAttr_AreaTransition{
	kEAAT_Positioned = 0,
	kEAAT_BaseEvents,
	kEAAT_Animated,
	kEAAT_AreaTransition,
	kEAAT_Stats,		//4
	kEAAT_ObjectMagicProperties,
	kEAAT_Render,
	kEAAT_Targetable,
	kEntityAttrMaxCnt,		//8
};

//�ɴ��͵Ķ���
enum class enCD_EntityAttr_Transitionable{
	kPositioned = 0,
	kBaseEvents,
	kAnimated,
	kTransitionable,
	kMinimapIcon,		//4
	kEAAT_Render,
	kEAAT_Targetable,
	kEntityAttrMaxCnt,	//7
};

enum class enCD_EntityAttr_Monster{
	kEAM_Positioned = 0,
	kEAM_Stats,
	kEAM_ObjectMagicProperties,
	kEAM_Pathfinding,
	kEAM_Life,
	kEAM_Animated,		//5
	kEAM_Inventories,
	kEAM_Actor,
	kEAM_Monster,
	kEAM_Render,
	kEAM_Targetable,
	kEntityAttrMaxCnt,		//�ܹ���11��
};

//�����࣬����ֿ⡢��ʾ�塢���ʾ���
enum class enCD_EntityAttr_NoHuman{
	kPositioned = 0,
	kBaseEvents,
	kAnimated,
	kRender,
	kTargetable,
	kEntityAttrMaxCnt,
};

//��ʾ��
enum class enCD_EntityAttr_NoticeBoard{
	kPositioned = 0,
	kBaseEvents,
	kAnimated,
	kRender,
	Targetable,
	kEntityAttrMaxCnt,
};

//���ӡ�ľͰ�������ߵ�����
//�������9������
enum class enCD_EntityAttr_Chest{
	kPositioned = 0,
	kBaseEvents,
	kAnimated,
	kChest,
	kStats,
	kObjectMagicProperties,
	kRender,
	kTargetable,
	kEntityAttrMaxCnt,		//8
};

//������Ʒ
enum class enCD_EntityAttr_WorldItem{
	kPositioned = 0,
	kAnimated,
	kWorldItem,
	kRender,
	kTargetable,
	kEntityAttrMaxCnt,		//5
};
//////////////////////////////////////////////////////////////////////////
enum enCD_EnterMapUknId{
};
//////////////////////////////////////////////////////////////////////////
//****************����Ĳ�����Ϸ�е�����
enum enCD_TraGemSkillFlag{
	kTGSF_Gem = 1 << 0,				//������ʯ
	kTGSF_Inside = 1 << 1,			//������Ƕ��װ����ı�ʯ
	kTGSF_ActiveSkill = 1 << 2,		//������������
	kTGSF_PassiveSkill = 1 << 3,	//������������
};

enum enCD_TraUiShownFlag : int{
	kTUSF_Shown = 1 << 0,							//��ʾ
	kTUSF_UnShown = 1 << 1,							//����ʾ
	kTUSF_AllNode = 1 << 2,							//�������������
	kTUSF_ShowHide = kTUSF_Shown | kTUSF_UnShown,	//��ʾ�Ͳ���ʾ�Ķ�����
	kTUSF_All = kTUSF_ShowHide | kTUSF_AllNode,
};

enum enCD_TraUiFilterType{
	kTUFT_ByVtbl = 0,
	kTUFT_ByAddr,
	kTUFT_AllSubNodes,				//�������������
};

//ö�ٳ��������ֲ�Ҫ���Ķ�
enum enCD_NpcPanelItemsContainer{
	kNPIC_Normal = 1,		//����������
	kNPIC_TalkPanel,		//�� ���� ���������
};

enum enCD_RightMostPanel{
	kRMP_QuestLvlState = 1,		//���񡢼���״̬���
	kRMP_Ukn,
};

enum enCD_ReviveAtPosition{
	kRAP_AtCity,
	kRAP_AtRecord,
	kRAP_AtDied,		//�������㸴��
};

enum enCD_PressItemWithKey{
	kPIWK_Shift,		//VK_SHIFT
	kPIWK_Control,		//VK_CONTROL
	kPIWK_Menu,			//VK_MENU
	kPIWK_Normal,
};

enum enCD_CreateRoleBtIdx{
	kCRBI_Cancel = 0,
	kCRBI_Ok,
	kCRBI_Ukn,
	kCRBI_Max = 3,
};

enum enCD_SkillAttrValueType{
	kSAVT_CallerMaxCnt,		//���� ���ӵ�� 6 ֻ��ʬ��
};

enum enCD_SocketType{
	kST_PreGameState,
	kST_InGameState,
	kST_Ukn,
};

enum enCD_GetLabyrinthTrialFlag{
	kGLT_Completed = 1 << 0,
	kGLT_UnCompleted = 1 << 1,
	kGLT_All = kGLT_Completed | kGLT_UnCompleted,
};
//////////////////////////////////////////////////////////////////////////
