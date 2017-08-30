#pragma once
/*
@author zhp
@date 2017/1/24 17:21
*/
#include <ProtocolX/P_DefinesX.h>
#include <string>

const int CD_kMaxStrLen = 0x100;
const int CD_kMaxNameLen = 50;
const int CD_kMaxFilePathLen = 0x100;

enum enCD_RoleAttrValueType{
	kRAVT_Power = 0,					//����
	kRAVT_Smart,						//����
	kRAVT_Brain,						//����
	kRAVT_Lucky,						//����
	kRAVT_Hp,							//����
	kRAVT_HpResume,						//�����ָ�
	kRAVT_Ukn,							//���δ֪����ֵͦ��3000
	kRAVT_Energy = 7,					//����
	kRAVT_Ukn1,
	kRAVT_Ukn2,
	kRAVT_Sp = 0xa,						//����
	kRAVT_MingZhong = 0xf,				//����
	kRAVT_HuiBi = 0x10,					//�ر�
	kRAVT_BaoJiMingZhong = 0x11,		//��������
	kRAVT_BaoJiHuiBi = 0x13,			//�����ر�
	kRAVT_Defense = 0x14,				//������
	kRAVT_PhysicalAttack = 0x17,		//��������
	kRAVT_MagicAttack = 0x18,			//ħ��������
	kRAVT_PhysicalDefense = 0x19,		//����ֿ���
	kRAVT_MagicDefense = 0x1a,			//ħ���ֿ���
	kRAVT_Max = 0x22,					//�ܹ���34������
};

//��ɫ״̬
enum enCD_ObjState{
	kOS_Normal = 1,			//����״̬����ֹ����״̬
	kOS_Move = 2,			//��·
	kOS_Squat = 4,			//����״̬��һ��Ӹ߿����º�˲����и����µĶ���
	kOS_Drop = 5,			//����״̬
	kOS_Jump = 6,			//��
	kOS_ClimbStairs = 8,	//������״̬
	kOS_Skill = 16,			//����
	kOS_Npc = 22,			//��npc�Ի������׵�״̬
	kOS_Swim = 27,			//��Ӿ
	kOS_ClimbWall = 29,		//��ǽ״̬
};

//��������
enum enCD_InventoryType{
	kIT_Equip = 0,	//װ��
	kIT_Fashion,	//ʱװ
	kIT_Call,		//�ٻ�
	kIT_Material,	//����
	kIT_Life,		//����
	kIT_Task,		//����
	kIT_Gem,		//��ʯ
	kIT_Other,		//����
	kIT_Max,
};

//xml�ַ���id������
enum enCD_XmlStrIdType{
	kXSIT_Item = 1,
	kXSIT_Action = 3,
	kXSIT_Skill = 4,
};

enum enCD_QuestState{
	kQS_Doing = 1,		//��������������δ��ɵ�����
	kQS_Done = 2,		//�����
};

enum enCD_QuestType{
	kQT_Main = 0,		//����
	kQT_Branch = 1,		//֧��
	kQT_Guide = 3,		//CGuideQuest ��������
};

//����װ������
enum enCD_BodyEquipType{
	kBET_Helm = 6,			//ñ��
	kBET_Coat1 = 8,			//����
	kBET_Coat2 = 9,			//����
	kBET_Hand = 10,			//����
	kBET_Shoe = 11,			//Ь
};

enum enCD_LoginCharacterState{
	kLCS_Normal = 1,
	kLCS_Selected = 2,
};

enum enCD_TerrainType{
	kTT_Normal = 1,
	kTT_Water = 0x40,		//64��ˮ
};
//////////////////////////////////////////////////////////////////////////
const pt_csz CD_kGameObjType_GameObject = "GameObject";
const pt_csz CD_kGameObjType_DropItemNIF = "DropItemNIF";
//////////////////////////////////////////////////////////////////////////
//***************����
const pt_csz CD_kClassName_UIMainPlayerInfo = "UIMainPlayerInfo";
const pt_csz CD_kClassName_UICharacterListDialog = "UICharacterListDialog";
const pt_csz CD_kClassName_UICharacterCreateDialog = "UICharacterCreateDialog";

const pt_csz CD_kClassName_TalkAction = "TalkAction";
const pt_csz CD_kClassName_InteractAction = "InteractAction";
const pt_csz CD_kClassName_PortalAction = "PortalAction";
//////////////////////////////////////////////////////////////////////////
//***********�Լ����������
enum enCD_TraUiShowFlag{
	kTUSF_Show = 1 << 1,
	kTUSF_UnShow = 1 << 2,
};
//////////////////////////////////////////////////////////////////////////