#pragma once
/*
@author zhp
@date 2014/6/15 15:12
@purpose console.exe/game.dll/login.dll֮��Ľ���
*/

//�汾uuid�����
const unsigned char kAssistVersionXor = 0xa3;
//�汾�¼�������
const char* const kAssistVersionEventObj = "_ComAtlStUads_";

//�����汾У��
bool CreateCheck_AssistVersion();
//���а汾У��
bool CheckAssistVersion();

//��Ϸģ������
#define P_INJECTED_GAME_NAME _T("fifazf.exe")

//�汾��Ч��ֹ����
const int kVersionEndTime_Year = 2017;
const int kVersionEndTime_Month = 11;
const int kVersionEndTime_Day = 1;

const unsigned short kAssistVersion = 0x0059;
#ifdef __PROJ_JIN_GANG_
const char* const kAssistVersionUuidGenerator = "23C92F9F-F1264-46EE-9E1E-82A23195BE7fd";
const char* const g_call_fn_name_set_login_succeed = "pldsc";
const char* const g_call_fn_name_set_ep = "aghks";
const char* const g_call_fn_name_set_trainer_name = "lkers";
const char* const g_call_fn_name_set_accout_wpd = "ercvh";

const unsigned int kGameConnectionMaxCnt = 20;
#elif defined(__PROJ_XIAO_ER_)
const char* const kAssistVersionUuidGenerator =	"36B2388DF-F299-4196-8AAD-22B9E7EB51Dc2";
const char* const g_call_fn_name_set_login_succeed = "jiolds";
const char* const g_call_fn_name_set_ep = "uioa";
const char* const g_call_fn_name_set_trainer_name = "werdx";
const char* const g_call_fn_name_set_accout_wpd = "okmys";

const unsigned int kGameConnectionMaxCnt = 20;
#endif

//////////////////////////////////////////////////////////////////////////
//kAcceptableGameConnectionCnt�����������������಻�ܳ���kGameConnectionMaxCnt
//ÿ���ʺſɽ��ܵ���������
static const int kAcceptableGameConnectionCnt[] = {
	kGameConnectionMaxCnt
};
//��������
struct ConnectCntInfo{
	//�����������
	static const int kGameConnectionMaxCnt = kGameConnectionMaxCnt;
	//����kAcceptableGameConnectionCnt���еģ�Ҳ���ǳ����ģ�ȫ����Ϊ��������
	static const unsigned int kDefConnectCntAtOverflow = 0;
	static auto ConnectItemCnt() -> decltype(kAcceptableGameConnectionCnt)&{
		return kAcceptableGameConnectionCnt;
	}
};
//////////////////////////////////////////////////////////////////////////