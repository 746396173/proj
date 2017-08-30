#pragma once
/*
@author zhp
@date 2014/6/15 15:12
@purpose console.exe/game.dll/login.dll֮��Ľ���
*/
//////////////////////////////////////////////////////////////////////////
//*******************����������������addr���ݺ�str����**********************
//addr data
enum enCheckAddrDataIndex{
	kCADI_LastestVersion = 1,		//���µİ汾��
};
//str data
enum enCheckStrDataIndex{
	kCSDI_LpkbUuid = 1,				//lpkb��uuid
	kCSDI_ConsoleUuidMb,			//console��uuid������
	kCSDI_ConsoleUuidXe,			//console��uuid��С��
};
//////////////////////////////////////////////////////////////////////////
//�汾�ַ���
//�汾��
const unsigned short kAssistVersion = 0x002e;
#ifdef __PROJ_GWLR_MB_
const char* const kAssistVersionUuidGenerator =
	/*kAssistVersionUuidGenerator_mb*/"3e47abaa-85e1-4f78-8796-b04cc8813e7c";
#elif (__PROJ_GWLR_XE_)
const char* const kAssistVersionUuidGenerator =
	/*kAssistVersionUuidGenerator_xe*/"ca523e4a-a907-433c-bd86-a99c8b52f404";
#elif (__PROJ_GWLR_MBP_)
const char* const kAssistVersionUuidGenerator =
	/*kAssistVersionUuidGenerator_mbp*/"607fb79d-a020-4f5d-8c77-9b2b898349ea";
#endif
//�汾uuid�����
const unsigned char kAssistVersionXor = 0xc4;
//////////////////////////////////////////////////////////////////////////
//kAcceptableGameConnectionCnt�����������������಻�ܳ���kGameConnectionMaxCnt
//ÿ���ʺſɽ��ܵ���������
static const int kAcceptableGameConnectionCnt[] = {
	2, 1, 1, 5, 1
};
//��������
struct ConnectCntInfo{
	//�����������
	static const int kGameConnectionMaxCnt = 30;
	//����kAcceptableGameConnectionCnt���еģ�Ҳ���ǳ����ģ�ȫ����Ϊ��������
	static const unsigned int kDefConnectCntAtOverflow = 2;
	static auto ConnectItemCnt() -> decltype(kAcceptableGameConnectionCnt)&{
		return kAcceptableGameConnectionCnt;
	}
};
//////////////////////////////////////////////////////////////////////////

//�汾�¼�������
const char* const kAssistVersionEventObj = "_ComAtlStUads_";

//�����汾У��
bool CreateCheck_AssistVersion();
//���а汾У��
bool CheckAssistVersion();

//��Ϸģ������
#define P_INJECTED_GAME_NAME _T("MHOClient.exe")

const unsigned short P_Port_ForGame = 35316;
const unsigned short P_Port_ForLogin = 35323;

//game do some
#define GAME_MODULE_NAME "gdoso"
#define LOGIN_MODULE_NAME "lgdos"
