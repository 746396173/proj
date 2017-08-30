
#pragma once
/*
@author zhp
@date 2017/2/5 22:36
@purpose for game const variable
*/
#include <string>
#include <CD_CommonFiles/Data/CD_Interface.h>

//��ɫ����󳤶�
const pt_dword kRoleNameMaxCnt = 20;
const int kCellMaxCnt = 8;	//��Ʒ��ռ��������
const pt_dword kEludeMonHp = 50;
const DWORD kMonsterInvalidPacketId = std::numeric_limits<DWORD>::max();
//game object type
enum enGameObjType{
	kGOT_Npc,
	kGOT_Monster,
	kGOT_Player,			//���
	kGOT_Waypoint,			//���͵�
	kGOT_AreaTransition,	//������
	kGOT_Stash,				//�ֿ�
	kGOT_NoticeBoard,		//��ʾ��
	kGOT_NoticeBoardPvP,	//���ʾ��
	kGOT_Chest,				//���� �����ߵ�����
	kGOT_WorldItem,			//������		
	kGOT_Transitonable,		//�ɴ��Ͷ���
	kGOT_Movement,			//���ƶ�����
	kGOT_Max,
	kGOT_Invalid,
};

//��Ʒ���,item category
enum enItemCate{
	kICATE_Usable,
	kICATE_Flask,
	kICATE_Decoration,	//��Ʒ
	kICATE_Ring,
	kICATE_Armor,		//����
	kICATE_Weapon,
	kICATE_Gem,
	kICATE_Quest,		//������Ʒ
	kICATE_Other,
	kICATE_Invalid,
};

//����������˳��Ҫ���ı�
enum enWeaponCompositeCate{
	kWCC_OneHand = 0,		//���֣������ֶ�����װ��������ͬʱװ���������ⵥ��
	kWCC_TwoHand,		//˫�֣�ֻ������װ�������ֲ���װ���κζ���
	kWCC_Restricted,	//�޶�λ�õģ�ֻ�ܷ������֣���ֻ�ܷ������֣������Ǵ�װ���Ƿ������ֵģ�����ֻ��װ��ָ��װ��
	kWCC_Invalid,
	kWCC_Max,
};

enum enMoveItemToRes{
	kMITR_MoveToThereFailed,
	kMITR_CanNotBePutted,	//����������������Ʒ
	kMITR_Fulled,			//����
	kMITR_Failed,
	kMITR_Succeed,
};

enum enTakeoffGemRes{
	kTOGR_HasNotGem,
	kTOGR_Fulled,
	kTOGR_Failed,
	kTOGR_Succeed,
};

enum enInsideGemRes{
	kIGR_CanNotBeInsided,
	kIGR_DiffColor,
	kIGR_Failed,
	kIGR_Succeed,
};

enum enPutItemDownRes{
	kPIDR_CanNotBePutted,
	kPIDR_Failed,
	kPIDR_Succeed,
};

//˳��Ҫ��
enum enOpenVisitorRes{
	kOVR_NoNeedOpen,
	kOVR_Openning,
	kOVR_Error,
	//�����ǳɹ�
	kOVR_Succeed,
	kOVR_Opened,
};

enum enTalkToNpcRes{
	kTTNR_NpcIsClosed,
	kTTNR_HaveNotTheLable,
	kTTNR_Error,
	kTTNR_Succeed,
	kTTNR_NotNeedHandle,
};

enum enItemFilterType{
	kIFT_QuestItem,
	kIFT_BlackName,
	kIFT_WhiteName,
	kIFT_Slot,
	kIFT_Colour,
	kIFT_Quality,
	kIFT_Type,
	kIFT_GemLink,
	kIFT_ItemCnt,
	KIFT_Level,
	KIFT_Bind,
	KIFT_Group,
	KIFT_ThreeColorLink,
	KIFT_Emboitement,
	kIFT_ItemProp,
	kIFT_Equip,
	kIFT_Level,
	KIFT_InvalidGem,
	kIFT_Max,
};

enum enGradeValue{
	kGV_Invalid,
	kGV_EquipColor,
	kGV_SlotLink,
	kGV_SlotColor,
	kGV_Quality,
	kGV_Weapon,
	kGV_Prop
};

enum enFilterType{
	kFT_PickUp,
	kFT_Sell,
	kFT_Store,
	KFT_Again,
};

enum enOpenChestFlag{
	kOCF_Enable = 1 << 1,
	kOCF_OnlyShowName = 1 << 2,
};

enum enGroupPropflag{
	kGPF_BaseProp = 1 << 0,
	kGPF_SubjoinProp = 1 << 1,
	kGPF_AllProp = kGPF_BaseProp | kGPF_SubjoinProp,
};

enum enLoginAccountRes{
	kLAR_AcBaned,
	kLAR_AcError,
	kLAR_PwdError,
	kLAR_Timeout,
	kLAR_WaitLoginRes,
	kLAR_Error,
	kLAR_Succeed,
};

//ͨ��һ�κ󣬾Ͳ���ͨ���ˡ�
enum enAreaPassState{
	kAPS_NotPass,		//��������ͨ��
	kAPS_CanPass,		//����ͨ��
	kAPS_FristPass,		//��һ��ͨ��
};
//////////////////////////////////////////////////////////////////////////
//**************ģ̬�Ի�����ʾ�ַ���
const std::wstring kDlgModalStr_LoginError = L"Login Error";
const std::wstring kDlgModalStr_PwdError = L"The password is not correct for this account.";
const std::wstring kDlgModalStr_AcError = L"The specified account does not exist.";
const std::wstring kDlgModalStr_AcBaned = L"Your account has been banned by an administrator.";
//////////////////////////////////////////////////////////////////////////

//�ƶ�������
const int kMoveOpenChestDistance = 60;
//�ƶ�ʰȡ��Ʒ������
const int kMovePickupItemDistance = 60;
//�ƶ����ž��롣�ŵľ���һ������С��������в����Ŷ�ֱ�ӷż��ܵ�����
const int kMoveOpenTranstionableDistance = 70;
//Ĭ���ҵ��������
const pt_dword kOpenObjValidDistance = 1000000;
//ҩƿ�������
const pt_dword kFlaskMaxCnt = 5;
//�ż���
const pt_dword kEmboitementCnt = 9;
//a*
const int kAStar_RectifyRadius = 50;
const int kAStar_CompressRadius = 50;

//ʹ�ü��ܽ����ö��˳��Ҫ��
enum enUseSkillRes{
	kUSR_Error,
	kUSR_DstNotValid,
	kUSR_Succeed,
};

enum enStopQuestReason{
	kSQR_Invalid,
	kSQR_AcceptNewQuest,
};

enum enTerrainParserFlag{
	kTPF_Cmp = 1 << 1,
	kTPF_Strstr = 1 << 2,
	kTPF_ObjDbPath = 1 << 3,
};

enum enInventoryItemChecksum{
	kIIC_ItemCnt = 0,
	kIIC_Pos = 8,
	kIIC_ItemName = 12,
	kIIC_ItemId = 15,
	kIIC_Weight = 17,
	kIIC_ItemInventoryType = 21,
	kIIC_BasePro = 24,
	kIIC_ItemValues = 32,
	kIIC_TipsFormatStr = 36,
	kIIC_Price = 40,
	kIIC_ItemTips = 48,
	kIIC_InventoryType = 60,
};
const int kDummyChecksumBagWidth = 6;
//////////////////////////////////////////////////////////////////////
//Ĭ�ϲֿ�ҳ
const std::string kStashPageDefault[4] = { "1", "2", "3", "4"};
const stCD_VecInt kInvalidVecInt(-1, -1);
const stSizeInt kItemMaxSize(2,4);
//////////////////////////////////////////////////////////////////////////
//***************npc talk label
const std::wstring kNTL_Cotinue = CD_kNTL_Cotinue;
const std::wstring kNTL_Bye = CD_kNTL_Bye;
const std::wstring kNTL_Buy = CD_KNTL_Buy;
const std::wstring kNTL_Sell = CD_KNTL_Sell;



#ifdef VER_GJ_
const std::string kNoAutoOpenObj[] = {
	"Trial of Ascendancy",
	"Undying Blockage",
	"Thaumetic Seal",
	"Medicine Chest",
	"Strange Glyph Wall",
	"Tolman's Bracelet",	
	"Maligaro's Spike",
	"Golden Hand",
	"Thaumetic Sulphite",
	"Oak's Amulet",
	"Kraityn's Amulet",
	"Alira's Amulet",
	"Allflame",
	"Chitus' Plum",	
	"The Eye of Fury",
	//"The Black Core",
	"Hinekor's Hair",
	"Tukohama's Tooth",
	"Bestel's Manuscript",
	"Miasmeters",
	"Cradle of Purity",
	"Valako's Jaw",
	"The Black Flag",
	"Maligaro's Map",
	"Map Device",
	"Silver Locket",
	"Firefly",
	"Moon Orb",
	"Sun Orb",
	"Statue of The Sisters",
	"Locked Door",
	"Switch",
	"Portal",
	"Sign of Purity",
	//"Fortress Gate",
	//"Eye of Conquest",
	"Ignition Switch",
	"Secret Passage",
	"Ankh of Eternity",
	"Timed Crank",
	"Basilisk Acid",
};

//****************�����䲻��Ҫ����·��� --����
const std::string kRoomConnectFilter[] = {
	"Sanctum of Innocence",
	"Caldera of The King",
	"The Black Core",
	"The Black Heart",
	"Cathedral Apex",
	"Tukohama's Keep",
	"Prison Rooftop",
	"The Brine King's Throne",
	"Maligaro's Workshop",
	"Portal",
	"The Spawning Ground",
	"The Fortress Encampment",
	"Arakaali's Web",
	"The Cauldron",
	"The Sky Shrine",
	"Arena",
	"Maligaro's Misery",
	"Shavronne's Sorrow",
	"Doedre's Despair",
	"The Black Heart"
};
#else
const std::string kNoAutoOpenObj[] = {
	"������",
	"��������",
	"��������",
	"����Ͽ�֮ӡ",
	"ҽҩ��",
	"���ŵ��Ƶ����ǽ��",
	"�������صķ�ӡ",
	"�ж���",
	"�ж���������",
	"���׸��޵ļ��",
	"�ƽ�֮��",
	"����Ͽ�������",
	"ŷ�˵Ĺ���֮��",
	"���׶ٵĹ���֮��",
	"�����ǵĹ���֮��",
	"����֮��",
	"�д�֮��",
	"����֮Կ",
	"�������صĺ���",
	"��ŭ֮��",
	"����֮ӡ",
	"����֮��",
	"��𿪹�",
	"���׸��޵ĵ�ͼ",
	"��������",
	"����Ī������",
	"ө���",
	//"���������ľ���",
	"�߹���Һ"
};

//****************�����䲻��Ҫ����·��� --����
const std::string kRoomConnectFilter[] = {
	"֯���߳�Ѩ",
	//"������",
	"��Ȩ֮��(����)",
	"����֮��",
	"����֮��",
	"����֮��",
	"����ʥ��",
	"����֮��",
	"ͼ�˹����Ҫ��",
	"����֮��(����)",
	"������ɽ��",  //�������ŵ�ͼ�ķ���
	"������֮��",
	"�ɻ���ɽ��",
	"��������",
	"�׸��޵Ĺ�����",
	"��ɭ��Ӫ��",
	"���͹�¯",
	"������",
	"���׸��޵Ŀ�ʹ",
	"Ѧ�ʵĻں�",
	"����ľ���",
	"���������ľ���"
};
#endif

//////////////////////////////////////////////////////////////////////////
//***************lua��ֵ
const std::string kLuaKeyNameItemType = "��Ʒ����";
const std::string kLuaKeyNamePropInfo = "������Ϣ";
const std::string kLuaKeyItemLevel = "��Ʒ�ȼ�";

//****************������
const std::string kPropQualityName = "Ʒ��";



//***************������
#ifdef VER_GJ_			//���ʷ�
const std::string kObjName_Waypoint = "Waypoint";
const std::string kObjName_Storage = "Stash";
const std::string kObjName_Identify = "Scroll of Wisdom";	//֪ʶ����
const std::string kObjName_PortalIdentify = "Portal Scroll"; //���;���
const std::string kObjName_DefaultSkill = "Default Attack";  //��ͨ����
const std::string kObjName_NpcNoVisit = "Navali";
const std::string kObjName_RegretBook = "Book of Regrets";
const std::string kObjName_SkillBook = "Book of Skill";
const std::string kObjName_MapDevice = "Map Device";
const std::string kObjName_HideoutMapDevice = "Map Device";
const std::string kObjName_LabyrinthDevice = "Labyrinth Activation Device";		//�Թ������豸
const std::string kObjName_LabyrinthTrialAtCity = "Ascendancy Plaque";			//��3�³����������
const std::string kObjName_LabyrinthTrialAtFb = "Trial of Ascendancy Plaque";
const std::string kObjName_JinGuShiXiang = "����ʯ��";
#else					//����
const std::string kObjName_Waypoint = "���͵�";
const std::string kObjName_Storage = "�ֿ�";
const std::string kObjName_Identify = "֪ʶ����"; 
const std::string kObjName_PortalIdentify = "���;���";
const std::string kObjName_DefaultSkill = "��ͨ����";
const std::string kObjName_RegretBook = "���֮��";
const std::string kObjName_SkillBook = "����֮��";
const std::string kObjName_NpcNoVisit = "������";
const std::string kObjName_MapDevice = "��ͼװ��";
const std::string kObjName_HideoutMapDevice = "�ƽ���ͼ��";
const std::string kObjName_LabyrinthTrialAtCity = "������";			//��3�³����������
const std::string kObjName_LabyrinthTrialAtFb = "Trial of Ascendancy Plaque";
const std::string kObjName_LabyrinthDevice = "Labyrinth Activation Device";		//�Թ������豸
const std::string kObjName_JinGuShiXiang = "����ʯ��";
#endif

//////////////////////////////////////////////////////////////////////////
//***************��ͼ��
#ifdef VER_GJ_
const std::string kMapName_JueWangYanTan = "The Twilight Strand";  //������̲
const std::string kMapName_CangShenChu = "Your Hideout";
const pt_cwsz kMapName_ShiYanShouWang = L"Lioneye's Watch";		//ʨ������
const pt_cwsz kMapName_NanBuSenLin = L"The Southern Forest";
const pt_cwsz kMapName_SaEnChenFeiXu = L"The City of Sarn";
const pt_cwsz kMapName_TongDao = L"Passageway";
const pt_cwsz kMapName_CitySarn = L"The City of Sarn";  //��������
const std::string kMapName_Aspirants = "Aspirants' Plaza"; 
const std::string kMapName_Hifhgate = "Highgate";
const std::string kMapName_BellyBeast = "The Belly of the Beast Level 2";
const std::string kMapName_DeHuanJing = "Daresso's Dream";

//*****************������
const pt_cwsz kMonName_WaErChaoLing = L"Vaal Oversoul";  
//const pt_cwsz kMonName_DominusAscendant = L"Dominus Ascendant";  
const pt_cwsz kMonName_DominusHigh = L"Dominus, High Templar";  
const pt_cwsz kMonName_Weaver = L"The Weaver"; 

//****************Buff��
const std::string kBuffName_GracePeriod = "Grace Period";
const std::string kBuffName_SummonRagingSpirit = "Summon Raging Spirit";
//��������
const std::string kTaskName_Labyrinth = "The Lord's Labyrinth";		//���˵������Թ�����

#else
const std::string kMapName_JueWangYanTan = "������̲";
const std::string kMapName_CangShenChu = "���� - ";
const pt_cwsz kMapName_ShiYanShouWang = L"ʨ������";
const pt_cwsz kMapName_NanBuSenLin = L"�ϲ�ɭ��";
const pt_cwsz kMapName_SaEnChenFeiXu = L"�����Ƿ���";
const pt_cwsz kMapName_TongDao = L"ͨ��";
const pt_cwsz kMapName_CitySarn = L"�����Ƿ���"; 
const std::string kMapName_Hifhgate = "ͳ����֮��";
const std::string kMapName_BellyBeast = "�������� 2 ��";
const std::string kMapName_DeHuanJing = "�������Ļþ�";
const std::string kMapName_YULingZhiShi = "����֮��";
const std::string kMapName_laboratory = "ʥ�ý���ʵ����";
const std::string kMapName_GangwanBridgey = "�������";

const std::string kMapName_Aspirants = "�����߹㳡";	//������ͼ
const pt_cwsz kMonName_WaErChaoLing = L"�߶�����";  
const pt_cwsz kMonName_DominusHigh = L"Dominus, High Templar";
const pt_cwsz kMonName_Weaver = L"The Weaver";
const std::string kMonName_HateFlag = "��������";
const std::string kMonName_parasite = "������";
const std::string kMonName_LaSaEgg = "��˹��������";

//****************Buff��
const std::string kBuffName_GracePeriod = "��Ϸ����δ����";
const std::string kBuffName_SummonRagingSpirit = "�ٻ���ŭ����";
//��������
const std::string kTaskName_Labyrinth = "���������Թ�";		//���˵������Թ�����
#endif

//��ͼλ����Ϣ
#ifdef VER_GJ_
const std::string kMapPosName_UpLouTi = "Stairs_up";
const std::string kMapPosName_DownLouTi = "Stairs1_down";
#else
const std::string kMapPosName_UpLouTi = "Stairs_up";
const std::string kMapPosName_DownLouTi = "Stairs1_down";
#endif

//////////////////////////////////////////////////////////////////////////
//***************������
const std::string kTaskName_StartQuest = "��ʼ����";

const std::string kMapName_Coast = "The Coast [Update]";  //��ʱ��֪���õ�ͼ�ô� ������� �ȹ���

//////////////////////////////////////////////////////////////////////////
//**************�¼����
const std::string kEventName_Die = "�����¼�";
const std::string kEventName_Die_ChangeMap = "����������ͼ�¼�";
const std::string kEventName_BagIsFull = "���������¼�";
const std::string kEventName_ReviveFront = "��������ǰ�¼�";

//////////////////////////////////////////////////////////////////////////
const enCD_ItemType kEmboitementType[] = {
	kITYPE_Helmet,				//ͷ��
	kITYPE_Amulet,				//����
	kITYPE_Belt,				//����
	kITYPE_Ring,				//��ָ
	kITYPE_Boots,				//Ь��
	kITYPE_Gloves,				//����
	kITYPE_BodyArmour,			//�ؼ�
	kITYPE_TwoHandSword
};
//////////////////////////////////////////////////////////////////////////
