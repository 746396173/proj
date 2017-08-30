
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
const DWORD kMonsterInvalidPacketId = std::numeric_limits<DWORD>::max();
//game object type
enum GameObjType{
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
	kOVR_NotVisitAgain,
	kOVR_Opened,
};

enum enTalkToNpcRes{
	kTTNR_NpcIsClosed,
	kTTNR_HaveNotTheLable,
	kTTNR_Error,
	kTTNR_Succeed,
	kTTNR_NotNeedHandle,
};

enum en_ItemFilterType
{
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
	KIFT_Prop,
	KIFT_Bind,
	KIFT_Group,
	KIFT_ThreeColorLink,
	KIFT_Emboitement,
	kIFT_Max,
};

enum en_NpcMonster
{
	kNM_Invalid,
	kNM_BeatFailure,
	kNM_Help,
	kNM_Visit,
};

enum en_GradeValue
{
	kGV_Invalid,
	kGV_EquipColor,
	kGV_SlotLink,
	kGV_SlotColor,
	kGV_Quality,
};

//�ƶ�������
const int kMoveOpenChestDistance = 40;
//�ƶ�ʰȡ��Ʒ������
const int kMovePickupItemDistance = 50;
//�ƶ����ž��롣�ŵľ���һ������С��������в����Ŷ�ֱ�ӷż��ܵ�����
const int kMoveOpenTranstionableDistance = 60;
//�򿪶����ӳ٣��ӳٱ�����У�����̫�죬��������û��Ӧ��
//const pt_dword kOpenObjTimeSpan = 600;
//Ĭ���ҵ��������
const pt_dword kOpenObjValidDistance = 1000000;
//ҩƿ�������
const pt_dword kFlaskMaxCnt = 5;
//�ż���
const pt_dword kEmboitementCnt = 9;

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
"�д�֮��",
"����֮Կ",
"�������صĺ���",
"��ŭ֮��"
};
//////////////////////////////////////////////////////////////////////////
//***************������
const std::string kObjName_Waypoint = "���͵�";
const std::string kObjName_Storage = "�ֿ�";
const std::string kObjName_Identify = "֪ʶ����"; 
const std::string kObjName_PortalIdentify = "���;���";
const std::string kObjName_DefaultSkill = "��ͨ����";
const std::string kObjName_RegretBook = "���֮��";
const std::string kObjName_SkillBook = "����֮��";
const std::string kObjName_NpcNoVisit = "������";
const std::string kObjName_MapDevice = "��ͼװ��";
//////////////////////////////////////////////////////////////////////////
//***************��ͼ��
const std::string kMapName_JueWangYanTan = "������̲";
//////////////////////////////////////////////////////////////////////////
//***************������
const std::string kTaskName_StartQuest = "��ʼ����";

//////////////////////////////////////////////////////////////////////////
//**************�¼����
const std::string kEventName_Die = "�����¼�";
const std::string kEventName_Die_ChangeMap = "����������ͼ�¼�";
const std::string kEventName_BagIsFull = "���������¼�";
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