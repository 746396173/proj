#pragma once
/*
@author zhp
@date 2016/4/11 21:38
*/
#include <ProtocolX/P_DefinesX.h>

pt_cdword kInvalidDwValue = (pt_dword)-1;
pt_cint kInvalidIntValue = (pt_int)-1;
pt_cdword kInvalidPacketId = (pt_dword)-1;
pt_cdword kInvalidLocalId = (pt_dword)-1;
//�������ַ�����󳤶�
pt_cdword kMaxNameStrLen = 250;
pt_cdword kMaxItemDbCnt = 0x20000;
pt_cdword kMaxTaskDbId = 0x2000;
/*
const int kMinFbId = 0x00018000;
const int kMaxFbId = 0x00045000;*/
pt_cdword kMaxFbDbId = 0x00850000;
const int kMaxFarmDbId = 0x1000;
const int kMaxShopDbId = 0x200;
const int kMaxSeedDbId = kMaxItemDbCnt;
const int kMaxCraftDbId = 0x60000;
const int kMaxMenufactureDbId = 0x2000;
const int kMaxBuffDbId = 0x05000000;


//��ɫ���ȼ�
const int kMaxRoleLvl = 50;
//��ɫ���ֻ���������
const int kRoleBufferMaxSize = 0x20;

//��Ϸ���з�����������󳤶�
pt_cdword kMaxSendBufferSizeOfGame = 0x00080000;
//������������󳤶�
pt_cdword kMaxSendBufferSize = kMaxSendBufferSizeOfGame / 2;
//����ϢID
pt_cword kMainMsgId = 1;
//////////////////////////////////////////////////////////////////////////
//ui
const char* const kRoleListButtons[6] = {
	"root1.rolelist.item1.btnBg.mc_role",
	"root1.rolelist.item2.btnBg.mc_role",
	"root1.rolelist.item3.btnBg.mc_role",
	"root1.rolelist.item4.btnBg.mc_role",
	"root1.rolelist.item5.btnBg.mc_role",
	"root1.rolelist.item6.mc_norole"
};
//MMOCLINET_UI_BTN_STARGAME
const pt_csz kUiStr_StartGame = "root1.btn_startgame"; //��ʼ��Ϸ��ť
//MMOCLINET_UI_CR_BTN_MC_RAND
const pt_csz kUiStr_RandomSkin = "root1.panel.down_mc.randombtn"; // ���Ƥ��������
//MMOCLINET_UI_CR_BTN_MC_NEXTSTEP
const pt_csz kUiStr_CreateRoleNextStep = "root1.btn_nextstep";	//����ѡ�����Ե���һ��
//MMOCLINET_UI_CR_BTN_CREATEOK
const pt_csz kUiStr_CreateRoleOk = "root1.btn_CreateRoleOk";	//������ɰ�ť
//MMOCLINET_UI_CR_BTN_OLDPLAY
const pt_csz kUiStr_IamOlPlayer = "root1.playerSetting.oldplayer"; //�ҵ�������
//MMOCLINET_UI_CN_EDIT_CREATENAME
const pt_csz kUiStr_CreateRole_InputNameEdit = "root1.mc_creatroleinput.input";	//������ɫ��ʱ�����������
//////////////////////////////////////////////////////////////////////////
// ����to������ַ���
//MMOCLIENT_REVERSAL_XI_MEI_LUN_SHAN_LU_TO_LONG_ZHI_HU
const pt_csz kMoveCmd_XiMeiLun2LongZhiHu = "Hub1ToHub2Triigger";		// ϣ����ɽ· 	==> ��ֺ��	Hub1ToHub2Triigger
//MMOCLIENT_REVERSAL_LONG_ZHI_HU_TO_XI_MEI_LUN_SHAN_LU
const pt_csz kMoveCmd_LongZhiHu2XiMeiLun = "Teleporter_To_Hub001";		// ��ֺ��		==> ϣ����ɽ·	Teleporter_To_Hub001
//MMOCLIENT_REVERSAL_XI_MEI_LUN_SHAN_LU_TO_MI_DE_LA_CUN
const pt_csz kMoveCmd_XiMeiLun2MiLaDeCun = "HubToVillageTrigger";		// ϣ����ɽ· 	==> �����´�	HubToVillageTrigger
//MMOCLIENT_REVERSAL_MI_DE_LA_CUN_TO_XI_MEI_LUN_SHAN_LU
const pt_csz kMoveCmd_MiLaDe2XiMeiLun = "VillageToHubTrigger";		// �����´�		==> ϣ����ɽ·	VillageToHubTrigger
//MMOCLIENT_REVERSAL_LONG_ZHI_HU_TO_MEI_JIE_BO_ER_TAN
const pt_csz kMoveCmd_LongZhiHu2MeiJie = "Teleporter_To_Village02";	// ��ֺ��		==> ÷�ܲ���̹	Teleporter_To_Village02
//MMOCLIENT_REVERSAL_MEI_JIE_BO_ER_TAN_TO_LONG_ZHI_HU
const pt_csz kMoveCmd_MeiJie2LongZhi = "Village2_To_Hub2_Trigger";	// ÷�ܲ���̹	==> ��ֺ��	Village2_To_Hub2_Trigger
//MMOCLIENT_REVERSAL_MEI_JIE_BO_ER_TAN_TO_YAO_YUE_LIN
const pt_csz kMoveCmd_MeiJie2RaoYueLin = "Village2_To_Hub3_Trigger";	// ÷�ܲ���̹	==> ҫ����	Village2_To_Hub3_Trigger
//MMOCLIENT_REVERSAL_YAO_YUE_LIN_TO_MEI_JIE_BO_ER_TAN
const pt_csz kMoveCmd_RaoYueLin2MeiJie = "TeleporterToVillage02";		// ҫ����		==> ÷�ܲ���̹	TeleporterToVillage02
//���װ��ڵ�ҫ����
const pt_csz kMoveCmd_YinBaiAiKou2YaoYueLin = "TeleportToHub03";
//ҫ���ֵ����װ���
const pt_csz kMoveCmd_YaoYueLin2YinBaiAiKou = "TeleporterToHub04";
//////////////////////////////////////////////////////////////////////////
const pt_csz kD3d9DllName = "CryRenderD3D9.dll";