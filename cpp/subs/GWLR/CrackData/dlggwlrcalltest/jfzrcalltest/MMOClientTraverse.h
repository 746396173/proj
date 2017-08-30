#pragma once
#include "public/GameStructs.h"


class MMOActor
{
public:
	MMOActor();
	~MMOActor();
public:
	DWORD				m_dwActorObjAddr;				// ��������ʱ�ĵ�ַ����addr2
	DWORD				m_dwActorId;					// ��ɫ����id
	MMO_ActorVector*	m_ptheActorVector;				// ��ɫ���꣬������Ϣ
	DWORD				m_dwActorPacketId;				// ��ɫ���id
	int					m_nActorXianLu;					// ��ɫ�ڼ���
	int					m_nLieShouXuKeZhengCount;		// �������֤������Ҳ���ǽ��븱��ʣ����ٴ�
public:
	bool ReadActor();
	CString GetRoleInMap();		// ���������ڵ�ͼ
	void WirtePos(float fx, float fy, float fz, float fdir);
	void WirtePos2(float fx, float fy, float fz, float fdir);
	void WirtePos3(float fx, float fy, float fz, float fdir);
};

void NpcWirtePos(DWORD dwObjAddr1,float fx, float fy, float fz);


CString TraverseObj();
CString TraversePlayer();
CString TraverseItem();
CString GetTaskInfo();
CString GetReceivedTaskInfo();
CString GetUiInfo();
CString TraverseReceivedTask();
CString GetReceivedNpcTask();
CString GetSuoYouShiXianDuiXiang(DWORD Dwtype =-1);
CString GetInFbInfo();
CString GetTemplateItemInfo();
CString GetMailInfo();
CString GetCollectObjAddr2();
CString GetShopInfo(int nNpcIndex);
CString GetCraftInfo();
CString GetManuFactureInfo();
CString GetCDialogInfo();
CString GetFarmSeedInfo();
CString GetFarmFacilityInfo();
CString GetFarmFacilityState();
CString GetRequireCurSlotSupplysAll();
CString GetRoleBuffState();
CString GetBuffInfo();
CString GetGiftBagInfo();
CString GetCPlayerLevelUpInfo();
CString GetTaskFbInfo();
CString GetShangJinTaskInfo();
CString GetKingQuestInfo();

void HookMonsterHpCall();
void HookActorHpCall();
void HookLoadMapCallEnd();
void HookDialogInfoCall();
void HookJingcai();//HOOK���ʾ�ͷ
// ˲��
void WritePos(float fx, float fy, float fz);