#pragma once
/*
@author zhp
@date 2014/9/15 18:33
@purpose cmn events name
*/
#include <string>
/*
PEN->proto event name
CEN->custom event name
PPEN->private proto event name
*/

//////////////////////////////////////////////////////////////////////////
const std::string kPEN_AutoTouchGameEvent("�Զ�����һ����Ϸ�¼�");
const std::string kPEN_SelectChannel("ѡ��Ƶ���¼�");
const std::string kPEN_SelectRole("ѡ���ɫ�¼�");
//const std::string kPEN_CreateRole("������ɫ�¼�");
const std::string kPEN_RoleInGame("��ɫ���뵽��Ϸ�¼�");
const std::string kPEN_RetCity("�Ӹ������ص������¼�");
const std::string kPEN_EnterToFb("���뵽�����¼�");
const std::string kPEN_AutoRunOneTaskHandler("�Զ���һ���������¼�");
const std::string kPEN_AfterDoneOneTask("������һ�������¼�");
const std::string kPEN_FatigueZero("ƣ��ֵʹ�����¼�");
const std::string kPEN_ChangeJob("תְ�¼�");
const std::string kPEN_AutoDoOneTask("�Զ��Ӻ��������¼�");
const std::string kPEN_HandleMails("�����ʼ��¼�");
const std::string kPEN_HandleDonAllMails("�ʼ���������¼�");
const std::string kPEN_HandleTrade("�������¼�");
const std::string kPEN_DoneTrade("��������¼�");
//////////////////////////////////////////////////////////////////////////
const std::string kPPEN_AcceptTaskHandlerTasks("_72765A3DFC4C_");
const std::string kPPEN_RunOneAcceptedTaskHandler("_B20354E405E7_");
const std::string kPPEN_RuneOneCompletableTaskHandler("_673E6A8E3E5A_");
const std::string kPPEN_AfterDoneRunOneTaskHandler("_89BC43F3E1A_");
const std::string kPPEN_HandleMails("_1C875673DF5_");
const std::string kPPEN_HandleMailsImpl("_588DD15CA0AF7_");
const std::string kPPEN_HandleMailRelation("_B9069E578B7_");
const std::string kPPEN_HandleTrade("_0E7B074C5131_");
const std::string kPPEN_HandleTradeImpl("_87BBECB29AF7_");
const std::string kPPEN_HandleTradeRelation("_89A887CD3B5D_");
const std::string kPPEN_HandleBuyOtherProducts("_A30B54E4D40B_");
const std::string kPPEN_KeepScriptRunningTimer("_437DE16395BB_");
const std::string kPPEN_WaitRetSelectRole("_E98F6EB90ECC_");
//////////////////////////////////////////////////////////////////////////