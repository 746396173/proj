#pragma once
/*
@author zhp
@date 2014/8/1 5:25
@purpose for game const variable
*/
#include <string>

//��ɫ����󳤶�,��Ҫ����19
const int kRoleNameMaxLen = 19;
const int kRoleNameMinLen = 4;
const int kMaxTaskId = 0x2000;
const int kItemTemplateMax = 0x20000;
const int kCraftMaxId = 0x60000;
const int kManuFactureMaxId = 0x2000;
const int kJingSuanDianMax = 0x1000;
const int kCurJingSuanDianMax = 6;
const int kFarmSeedMax = kItemTemplateMax;
const int kCaoYaoTianMax = 3;
//�ʼ��������
const int kSendMailMaxCnt = 10;
//�ʼĵȼ�����
const int kSendMailMinRoleLvl = 20;
//����ȯ֤���������
const int kShouLieQuanMax = 30;
//��������������
const int kDealMaxGridCnt = 30;
//��������Чʱ�䣬��λ��
const int kQuestDealValidTime = 15 - 1;
//���潻�׵ĵȼ�����
const int kRoleMinLvl_FaceToFaceDeal = 20;

//������
const std::string kVillageName_XiMeiLunShanLu = "ϣ����ɽ·";
const std::string kVillageName_LongZhiHu = "��ֺ��";
const std::string kVillageName_MiLaDeCun = "�����´�";
const std::string kVillageName_MeiJiePoErTan = "÷�ܲ���̹";
const std::string kVillageName_YaoYueLin = "ҫ����";
const std::string kVillageName_YinBaiAiKou = "���װ���";
//const std::string kVillageName_LieTaunYingDi = "����Ӫ��";
/*
÷�ܲ���̹�ķ��䣺
��������Ӫ�أ�1
��¶�����أ�2
*/

//������
const std::string kFbName_BeginDream = "[�ε����]";

const int kMinFbId = 0x00018000;
const int kMaxFbId = 0x00045000;

const DWORD kMonsterInvalidPacketId = std::numeric_limits<DWORD>::max();
const int kInvalidTaskId = -1;
const int kInvalidFbId = -1;

const std::string kHandleAtHitting = "2A239250BBAB";
const std::string kHandleAfterEnterFb = "0BED2498D256";
const std::string kHandlersOnScriptStoped = "2D613C6E329B4CD0816FB";

//npc name
const std::string kNpcName_Sociaty = "������ɯ��";

//����ҳ������
const int kAuctionPageCnt = 8;

//�������
//����������ȼ�����
const int kRoleLvlLimit_Auction = 25;

//��󷿼��
const int kMaxRoomId = 20;

//��Ʒ������/������
const char* const kItemBlackWhiteList_PriTblName = "97CCFE37";
//��Ʒ������
const std::string kItemBlackListName = "CC19DA40";
//��Ʒ������
const std::string kItemWhiteListName = "0E9D1F23";

//���䵽�����Ȩ��
const double kRoomNum2DistWeight = 0x9fffff9;

//��Ϣ���صĴ�����
//��ͨ�����ķ���ֵ
//�ж�������
const int kMsgRetError_XingDongLiBuZu = 300007;
//
const int kMsgRetError_DoneIt = 360046;

const int kLianQiCaoFullValue = 100;

const char* const kFbSubName_ShiLian = "����";
const char* const kFbSubName_TiaoZhan = "��ս";
const char* const kFbSubName_JiXian = "����";

const int kZhanWeiZhiMin = 1000000;

//buff name
const std::string kBuffName_Hot = "����";
const std::string kBuffName_Cold = "����";
const std::string kBuffName_LengYin = "����";
const std::string kBuffName_ReYin = "����";
const std::string kBuffName_AoYiJueXing = "�������";
const std::string kBuffName_NiRen = "����";
const std::string kBuffName_RanShao = "ȼ��";
const std::string kBuffName_ErChou = "���";
const std::string kBuffName_SnowMan = "ѩ��";
const std::string kBuffName_ChanRao = "����";
//buff desc
const std::string kBuffDesc_Hot = "��о�������";
const std::string kBuffDesc_Cold = "��о�������";
//const std::string kBuffDesc_RanShao = "ÿ������ʧһ��������ֵ";

//ׯ԰����ID
const int kSelfFarmFbId = 0x00027165;

//��ҩ��
const std::string kFarmGaoShiPai = "ׯ԰��ʾ��";

//��Ʒ��
const std::string kItemName_JingSuan = "����";
//������
const std::string kItemName_GuWenShu = "�����顤һ";
const int kUseCnt_Unlock_KingCream = 5;

//////////////////////////////////////////////////////////////////////////
//*********************˲�ơ��������**************************************
//��Щ��ֵ���������׸ı䣬�����������
//��ͼʱ����
const int kSendMoveRoomSpan = 5 * 1000;
//�����ʱ��Ѱ·��С��������
const double kFindPathMinDistLimitNormal = 4;
//���ʱ��Ѱ·��С��������
const double kFindPathMinDistLimitOnHitting = 10;
//��������Σ�վ���
const double kFindPathMaxDangerDist = kFindPathMinDistLimitOnHitting + 10;
//Ѱ·�У�������Ŀ������Ĳ�಻�ܴ��������
const double kFindingPathRoleMonsterMaxDist = 5;
//��������󣬵ȴ���Ϸ�����������ʱ��
const int kWaitSendMoveRoolAfterSetPos = 1000 * 2;
//////////////////////////////////////////////////////////////////////////
//�������߶��ж�ʧ�ܴ�������
const int kMonsterMostHighFaileMaxCnt = 200;

//�ǿ��ж����ĵȴ�ʱ��
const int kUnFreeToFreeWaitTime = 1000 * 10;
//BOSS��߸߶�����
const int kMaxPosZHigh = 6;
//BOSS��͸߶����ƣ�������������ë������͵�ֵ����Ҫ���׸Ķ�
const int kMinPosZHigh = -12;
//Z�߶Ȳ���ʱ�ӳ�ʱ��
const int kSleepTimeAtPosZError = 700;
//��ͼ֮�ȴ���ɫ���ƶ�ʱ��
const int kWaitTime_RoleCanMove = 1000 * 60 * 15;
//����ѵ����ͼģ��
const int kXinShouXunLianTemplateMapId = 1402;
//////////////////////////////////////////////////////////////////////////
//******************pause id**********************************************
//��Ϸ���ݲ�����
extern const void* const kPauseId_GameDataErr_;
DEFINE_THE_PAUSE_ID(kPauseId_GameDataErr, kPauseId_GameDataErr_);
//��ɫ������
extern const void* const kPauseId_RoleDead_;
DEFINE_THE_PAUSE_ID(kPauseId_RoleDead, kPauseId_RoleDead_);
//��ͼʧ��
extern const void* const kPauseId_PassMapErr_;
DEFINE_THE_PAUSE_ID(kPauseId_PassMapErr, kPauseId_PassMapErr_);
//�������нű�
extern const void* const kPauseId_ChangeCurRunScript_;
DEFINE_THE_PAUSE_ID(kPauseId_ChangeCurRunScript, kPauseId_ChangeCurRunScript_);
//����ɾ����ɫ
extern const void* const kPauseId_DoDeleteRole_;
DEFINE_THE_PAUSE_ID(kPauseId_DoDeleteRole, kPauseId_DoDeleteRole_);
//ȡ������
extern const void* const kPauseId_CancelDeal_;
DEFINE_THE_PAUSE_ID(kPauseId_CancelDeal, kPauseId_CancelDeal_);
//////////////////////////////////////////////////////////////////////////
//���ݴ���Ĭ�Ϸ���ֵ
const int kDefRetValueAtDataErr = 1;