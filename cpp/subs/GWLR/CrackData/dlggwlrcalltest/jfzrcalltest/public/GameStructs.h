#pragma once
#include "../gwlrbase.h"
#include <string>

#pragma pack(push)
#pragma pack (1)

typedef struct
{
	int		nSayType;
	char	pszSayBuf[MMOCLIENT_REVERSAL_PACKET_BUF_SIZE___*4];
}MMO_SAY_MESSAGE,*PMMO_SAY_MESSAGE;

//��ά����������������ʾ�����
struct MMO_Vector3{
	float	fx;
	float	fy;
	float	fz;
};
typedef MMO_Vector3 MMO_Direction3;

//��ά����������������ʾ�����
//dir��direction���������д
struct MMO_Direction2{
	float	dir_x;
	float	dir_y;
};

// �������Ľ�ɫ����Ľṹ��
struct MMO_ActorVector
{
	MMO_Direction3  dir_1;
	float			fx;
	MMO_Direction3  dir_2;
	float			fy;
	MMO_Direction3	dir_3;
	float			fz;
};


typedef struct  
{
	DWORD	str_dwUnKnow;
	DWORD	str_dwNextAddrParent;
	DWORD	str_dwNextAddrLeft;
	DWORD	str_dwNextAddrRight;
}NODE,*PNODE;

typedef struct
{
	NODE	theNode;
	DWORD	dwObjId;
	DWORD	dwObjAddr;
}MMO_ACTOR,*PMMO_ACTOR;

typedef	struct
{
	DWORD				str_dwBeginAddr;
	DWORD				str_dwEndAddr1;
	DWORD				str_dwEndAddr2;
	DWORD				str_dwCommandAddr;
}GAME_STRUCT_ARRAY_POINT,*PGAME_STRUCT_ARRAY_POINT;

typedef	struct
{
	DWORD				str_dwBeginAddr;
	DWORD				str_dwEndAddr1;
	DWORD				str_dwEndAddr2;
}GAME_STRUCT_ARRAY_POINT2,*PGAME_STRUCT_ARRAY_POINT2;

typedef struct
{
	DWORD	dwVFunAddr;
	DWORD	dwTaskType;
	DWORD	dwZero1;
	DWORD	dwZero2;
	DWORD	dwUnKnow1;
	GAME_STRUCT_ARRAY_POINT	theTaskArray;
	DWORD	dwZero3;
}TASK_FB_INFO,*PTASK_FB_INFO;


typedef struct  
{
	DWORD	dwUnKnow1;
	int		nZhangIndex;	// �½����
	char*	pszZhangStr;	// �½��ַ���
	DWORD	dwTaskFbId;		// ���񸱱�id
	int		nZhangTaskIndex;	// �½�����������
	GAME_STRUCT_ARRAY_POINT2	theZhangTaskJieSuoArray;	// �������������Ӧ��ϵ
	int		x;
	int		y;
	DWORD	dwCityId;		// ���񸱱����ڳ���id
	int		nShowFlag;		// �Ƿ���ʾ�ı�־
	char	szEnterInstance[0x14];
	char*	pszEnterInstance;
	char	szLevelType[0x14];
	char*	pszLevelType;
}ZHANG_TASK_FB_INFO,*PZHANG_TASK_FB_INFO;


typedef struct
{
	DWORD dwUnKnow1;
	DWORD dwUnKnow2;
	DWORD dwKingQuestId;
	DWORD dwUnKnow3;
	DWORD dwUnKnow4;
	DWORD dwCityId;
	char* pszFbTitle;
	char  szBuffer1[4*5];
	char* pszBuffer1;
	char  szBuffset2[4*5];
	char* pszBuffer2;
}KING_QUEST_INFO,*PKING_QUEST_INFO;	// ������������


//////////////////////////////////////////////////////////////////////////
// �����ṹ��
typedef struct		// ���ͷ
{
	WORD	wPacketMsgId;
	WORD	wPacketMsgType;
	DWORD	dwPacketMsgLen;
	DWORD	dwPacketZero1;
	DWORD	dwPacketZero2;
}MMO_PACKET_HEADER,*PMMO_PACKET_HEADER;

typedef struct
{
	LONGLONG	llDynamic;
	MMO_Vector3	dst_pos;	//Ŀ������
	DWORD	dwUnKnow2;
	DWORD	dwUnKnow3;
	MMO_Direction2	dir;	//�ƶ��ķ���
}MMO_WALK,*PMMO_WALK;

typedef struct
{
	MMO_Vector3		theDoorCoord;		// �ŵ�����
	char			szDoorCmd[64];
}MMO_PACKET_GOTO_DOOR,*PMMO_PACKET_GOTO_DOOR;

typedef struct
{
	DWORD	dwUnknow1;
	DWORD	dwUnKnow2;
	DWORD	dwFbId;		// ����id
	int		nFbDiffLevel;	// ������ս�ȼ�
	DWORD	dwFbType;	// ��������
}GO_TO_FB1,*PGO_TO_FB1;


typedef struct
{
	DWORD	dwFbId;		// ����id
	DWORD	dwMode;
}GO_TO_FB_CHOOSEMODE,*PGO_TO_FB_CHOOSEMODE;



typedef struct  
{
	DWORD	dwKey1;
	DWORD	dwKey2;
	byte	bScrItemTabIndex;	// ���ƶ�����Ʒ���ĸ���
	WORD	wScrItemSlotIndex;	// ���ƶ�����Ʒ�ڵڼ���
	byte	bDstItemTabIndex;	// �ƶ�����Ʒ���ĸ���
	WORD	wDstItemSlotIndex;	// �ƶ�����Ʒ�ڵڼ���
}MMO_ITEM_MOVE_TO,*PMMO_ITEM_MOVE_TO;

typedef struct  
{
	DWORD	dwMoveItemKey1;		// ���ƶ�����Ʒkey
	DWORD	dwMoveItemKey2;
	byte	bScrItemTabIndex;	// ���ƶ�����Ʒ���ĸ���
	WORD	wScrItemSlotIndex;	// ���ƶ�����Ʒ�ڵڼ���
	WORD	wMoveItmeCount;		// �ƶ���Ʒ������
	byte	bDstItemTabIndex;	// �ƶ�����Ʒ���ĸ���
	WORD	wDstItemSlotIndex;	// �ƶ�����Ʒ�ڵڼ���
	DWORD	dwToItemKey1;		// �ƶ�����Ʒ��key
	DWORD	dwToItemKey2;
}MMO_ITEM_MOVE_TO_COUNT,*PMMO_ITEM_MOVE_TO_COUNT;

typedef struct
{
	int		nItemSlotIndex;
	DWORD	dwItemId;
	DWORD	dwItemCount;
}MMO_DO_BU_JI_XIANG,*PMMO_DO_BU_JI_XIANG;		// ������


typedef struct  
{
	int nItemTabIndex;
	int nItemSlotIndex;
	int nItemCount;
}MMO_SELL_ITEM,*PMMO_SELL_ITEM;			// ������Ʒ

typedef struct
{
	LONGLONG	llMailId;
	byte		bFlag;
	int			nUnKnow;
	int			nItemTabIndex;
}MMO_GET_MAIL_ITEM,*PMMO_GET_MAIL_ITEM;

typedef struct
{
	byte		bUnknow;
	LONGLONG	llMailId;
}MMO_GET_MAIL_ITEM_INFO,*PMMO_GET_MAIL_ITEM_INFO;

typedef struct
{
	int		nMailDeleteFlag;
	LONGLONG llMailId;
}MMO_DELETE_MAIL,*PMMO_DELETE_MAIL;

typedef struct
{
	DWORD dwBuyItemFlag;
	DWORD dwShopId;
	int	  nCount;
	DWORD dwFFFFFFFF1;
	DWORD dwFFFFFFFF2;
}MMO_BUY_ITEM,*PMMO_BUY_ITEM;

typedef struct
{
	LONGLONG	llUpEquipSeiral;			// ������Ʒʱ����Ʒ���к�
	byte		bSoltTableIndex;		// װ����=3 ������=0 �ֿ���=2
	WORD		wSoltIndex;				// �۵���ţ����ڼ��񣬴�0��ʼ
	DWORD		dwEquipItemId;			// ���������Ʒid
}MMO_SEND_UP_EQUIP_PACKET,*PMMO_SEND_UP_EQUIP_PACKET;

typedef struct
{
	DWORD	dwItemKey1;
	DWORD	dwItemKey2;
	byte	bItemTabIndex;
	WORD	wItemSlotIndex;
	WORD	wItemCount;
}MMO_DISMANTLING_,*PMMO_DISMANTLING_;

typedef struct
{
	int					nDismantlingCount;
	MMO_DISMANTLING_	theDismantling[20];
}MMO_DISMANTLING,*PMMO_DISMANTLING;

typedef struct
{
	DWORD	dwTaskFlag;
	DWORD	dwTaskFbLevel;
	DWORD	dwTaskFbId;
	DWORD	dwUnKnow;
}MMO_ACCEPT_GONG_HUI_TASK,*PMMO_ACCEPT_GONG_HUI_TASK;

typedef struct
{
	int nTabIndex;		// ѡ����ĸ�ѡ��
	int nPageIndex;		// ��һҳ Ϊ 8 �ڶ�ҳΪ 16 ��������
	int nPageCount;		// û�б�����²�Ϊ��������
}MMO_GET_SEARCH_ITEM_LIST_BY_PAGE,*PMMO_GET_SEARCH_ITEM_LIST_BY_PAGE;

typedef struct
{
	DWORD	dwReqItemId;	// ������Ʒid
	DWORD	dwReqItemKey;	// �հ��к�������Ʒidһ��key
	int		nPrice;			// ��Ǯ
	DWORD	dwItemId;		// ��Ʒid
	int		nItemCount;		// ��������
}MMO_REQ_BUY_ITEM,*PMMO_REQ_BUY_ITEM;

typedef struct
{
	byte	bTabIndex;		// ��Ʒ��  ����=0 �ֿ�=2
	WORD	wSlotIndex;		// ������ţ����ڼ���
	DWORD	dwItemId;		// ��Ʒid
	WORD	wItemCount;		// ��Ʒ����
	int		nPrice1;		// ���ļ�
	int		nPrice2;		// һ�ڼ�
	int		nTimeFalg;		// ����ʱ�� 2Сʱ=0 8Сʱ=1 24Сʱ=2
}MMO_SHANG_JIA_AUCTION_ITEM,*PMMO_SHANG_JIA_AUCTION_ITEM;

typedef struct
{
	DWORD	dwActorPacketId;
	char	szTeamPwd[9];
}MMO_JOIN_TEAM,*PMMO_JOIN_TEAM;


typedef struct
{
	DWORD dwFbKeyFlag;			// ���ḱ�� = 0x0000985E �������� = 0x000075C2  ǧ������ = 0x000075B6	
//	DWORD dwFbTypeIndex;		// ���ḱ�� = 1 ǧ������ = 4 �������� = 3
}MMO_REQUEST_ENTRUST_LIST,*PMMO_REQUEST_ENTRUST_LIST;

typedef struct
{
	DWORD		dwUnKnow1;
	char		szMailActorName[0x15];	// �ռ�������
	char		szUnKnow1[0x0C];
	char		szMailTitle[0x19];		// �ʼ�����
	char		szUnKnow2[0x27];
	char		szMailData[0x258];		// �ʼ�����
	int			nGold;					// �ʼĽ��
	int			nAttachmemtCount;		// ��������
	struct
	{
		byte	bTableIndex;		// ����=0 �ֿ�=2	
		WORD	wSlotIndex;			// ��Ʒ���ڸ������
		LONGLONG llItemSerial;
		int		nItemCount;			// ��Ʒ����
		WORD	wUnKnow;
	}theAttachmemt[2];		// �����������̶���5
}MMO_SEND_MAIL,*PMMO_SEND_MAIL;	

typedef struct
{
	WORD	wTabSoltIndex;		// �ֿ�=2 ����=0
	byte	bUnKnow1;			// Ϊ0
	WORD	wSoltCount;			// ��Ч���ӵ���������0��ʼ
	WORD	wItemCount;			// ��Ʒ����
	struct
	{
		LONGLONG	llkey;
		byte		bUnKnow;
		int			nSloltIndex;
	}theTidyItemInfo[1000];		// ����ֿ����Ϊ1000��
}MMO_TIDY_ITEM,*PMMO_TIDY_ITEM;



typedef struct
{
	DWORD dwWeekCreditIndex;			// ������ȯ��� 2
	int	  nWeekCreditCount1;			// ȡ����ȯ����
	int	  nHasReceiveWeekCreditCount;	// ��ȡ����
	int   nWeekCreditCount2;			// ȡ����ȯ����
}MMO_WEEK_CREDIT,*PMMO_MMO_WEEK_CREDIT;

typedef struct
{
	LONGLONG llSysRandom;
	MMO_Vector3	ptheAcrot;
	DWORD	dwZeor1;
	DWORD	dwZeor2;
	MMO_Direction2	theDir1;
	MMO_Direction2	theDir2;
}SYN_COOR_DINATES,*PSYN_COOR_DINATES;	// ͬ��������

typedef struct
{
	WORD	wScrItemTabIndex;	// ����=0 �ֿ��ز�=0x0A ��ͨ�ֿ�=2
	WORD	wScrItemSlotIndex;	// ������ֿ������ӣ���0��ʼ����
	WORD	wMoveItemCount;		// �ƶ���Ʒ������
	WORD	wDealSlotaIndex;	// �������ĸ��ӣ���0��ʼ����
}MMO_DEAL_MOVE_ITEM,*PMMO_DEAL_MOVE_ITEM,MMO_RECV_DEAL_MOVE_ITEM_RET,*PMMO_RECV_DEAL_MOVE_ITEM_RET;


//////////////////////////////////////////////////////////////////////////
// �հ��ṹ��
typedef struct
{
	MMO_PACKET_HEADER	thePacketHeader;
	DWORD				dwTaskId;
	DWORD				dwTaskZero;
}MMO_ACCEPT_TASK,*PMMO_ACCEPT_TASK;			// ��������


typedef struct
{
	MMO_PACKET_HEADER	thePacketHeader;
	DWORD				dwTaskId;
}MMO_GIVE_UP_TASK,*PMMO_GIVE_UP_TASK;			// ��������

typedef struct
{
	MMO_PACKET_HEADER	thePacketHeader;
	int		nSize;
	DWORD	nRetValue;			// nRetValue = 0�� nRetError = -1 ��ʾ��ȡ����ʧ��
	DWORD	dwMailId1;
	DWORD	dwMailId2;
	int		nRetError;			// nRetValue = 0x29�� nRetError = -2 ��ʾ��ȡ����ʧ��:����Я������
}MM0_ACCEPT_MAIL_RET_VALUE,*PMM0_ACCEPT_MAIL_RET_VALUE;

typedef struct
{
	DWORD	dwRolePacketId;
	int		nError;		// 0��ʾ�����������븱��  ��0��ʾ���ɽ��븱�����缤�˸���ƣ��״̬������ί�и����Ѿ����꣬ע�⣺���ḱ�����Դ�3�Σ�����ÿ������ֻ�ܴ�һ��
	//int		nRet;		// 1��ʾ��ͨ��������ֵ�ͼ��˸�������ֵ  2��ʾ���ḱ������ֵ 
}MMO_GAME_IN_FB_RET_PACKET,*PMMO_GAME_IN_FB_RET_PACKET;

typedef struct
{
	DWORD dwUnKnow1;
	DWORD dwUnKnow2;	
	DWORD dwRetValue;		// ���Է�������������ֵ=0x73 ������������ֵ=0x6A
	DWORD dwRolePacketId;	// ��ɫ�����id
	char  szRoleName[20];	// ��ɫ����
}MMO_FB_SERVER_FULL_RET,*PMMO_FB_SERVER_FULL_RET;

typedef struct			// �������ṹ
{
	DWORD dwZeor1;
	DWORD dwZero2;
	DWORD dwPlayerId;
	char  szPlayerName[0x20];
	byte  bChosseFlag;
	int	  nPlayerLevel;
	byte  bszUnKnow[0x501 - 0x31];
}MM0_PLAYER_LIST,*PMM0_PLAYER_LIST;


typedef struct
{
	int nRet;
	int nRetParamer;
}MMO_RECV_DELETE_PLAYER,*PMMO_RECV_DELETE_PLAYER;


typedef struct
{
	WORD wLineIndex;
	byte bLineLevel;
	byte bUnKnow;
}MMO_GAME_LINE,*PMMO_GAME_LINE;

typedef struct
{
	DWORD	dwReqItemById;		// ��������Ʒid������Ʒid����Ҫ���ȷ����Ʒid
	DWORD	dwReqItemByKey;		// ����������Ʒ��Ҫ�õ���keyֵ
	DWORD	dwUnKnow1;
	DWORD	dwUnKnow2;
	char	szReqItemByPlayerName[0x20];
	byte	bFlag;
	DWORD	dwUnKnow3;
	int		nReqItemByPrice1;		// ���ļ�
	int		nReqItemByPrice2;		// һ�ڼ�
	int		nReqItemByPrice3;		// ���ļ�
	byte	bUnKnowCode[0x0AE];
}MM0_RECV_REQ_ITEM_BY_TYPE,*PMM0_RECV_REQ_ITEM_BY_TYPE;

typedef struct
{
	DWORD	dwRet;		// ����ֵ
	int		nDoCount;	// ����
	DWORD	dwUnKnow;	// ���������֪��
	int		nReqItemCount;	// ��Ʒ����������ҳ����Ҫ����8�����������������Ҫ��+1
	WORD	wCurPageCount;	// ��ǰҳ��������Ʒ����
}MMO_RECV_REQ_ITEM_BY_HEADER,*PMMO_RECV_REQ_ITEM_BY_HEADER;


typedef struct
{
	DWORD	dwRetValue;		// ����ֵ = 6��������ӱ��ܾ�
	DWORD	dwZeor1;
	DWORD	dwZeor2;
	char	szActorName[0x20];		// �ܾ���ӵĶ�������
}MMO_INVITE_TEAM_FAIL,*PMMO_INVITE_TEAM_FAIL;

typedef struct
{
	DWORD	dwActorPacketId;
	DWORD	dwUnKnow1;
	DWORD	dwUnKnow2;
	char	szTeamMemberName[0x20];
	int		nMemberLevel;
	byte	bCode[0x3c];
}MMO_TEAM_MEMBER_INFO,*PMMO_TEAM_MEMBER_INFO;

typedef struct
{
	DWORD	dwTeamId;
	char	szTeamTitle[0x28];		// ����
	int		nMaxMemberCount;		// ��������Ա����
	DWORD	dwZeor1;
	WORD	wFlag;
	char	szTeamPwd[0x20];		// ��������
	byte	bUnKnowCode[0x3E];
	int		nMemberCount;			// ��ǰ�����Ա����
	MMO_TEAM_MEMBER_INFO	theTeamMemberInfo[4];
}MMO_TEAM_INFO,*PMMO_TEAM_INFO;

typedef struct
{
	DWORD	dwFbType;		// ��������  ����=0x00000065 ǧ��=0x000000C9
	WORD	wCount;
	DWORD	dwTaskFbId[0x32];
}MMO_TASK_FB_INFO_,*PMMO_TASK_FB_INFO_;

typedef struct
{
	DWORD	dwRetValue;
	//DWORD	dwTaskFbType;		// 01��ʾ���ḱ��  04 ��ʾǧ������  03 ��ʾ��������
	WORD	wCount;
}MMO_TASK_FB_INFO,*PMMO_TASK_FB_INFO;

typedef struct
{
	int		nReqCount;		// �ۼ�����
	byte	bTabIndex;
	byte	bTypeIndex;
	byte	bSlotIndex;
	WORD	wUnKnow1;
	WORD	wGuDingValue1;	// 000003E7
	WORD	wGuDingValue2;	// 00000009
	byte    byUnKonw;
	char	szSearchName[0x20];		// ���������ؼ���
	byte	bItemIdCount;		// ��������Ʒid����
	DWORD	dwItemId[50];
}MMO_REQ_ITEM_BY_SEND_STRUCT,*PMMO_REQ_ITEM_BY_SEND_STRUCT;

typedef struct
{
	DWORD dwBuyItemRet;		// ����ɹ� = 0
	DWORD dwBuyReqItemId;	// �������Ʒ����id
}MMO_RECV_REQ_BUY_ITEM_RET,*PMMO_RECV_REQ_BUY_ITEM_RET;

typedef struct
{
	int		nRet;		// ����ֵ=1
	DWORD	dwFbId;		// ���˸���id
	DWORD	dwUnKnow;		
	int		nFbCount;	// ʣ�༤�˸�������
	int		nShuaXinTime;	// ʣ��ˢ�¸���ʱ��
}MMO_RECV_JI_YUN_FB,*PMMO_RECV_JI_YUN_FB;

typedef struct
{
	WORD	wRet;		// �򿪳ɹ�����ֵ=2
	struct
	{
		char	szUnKnow[3];
		int		nOpenFlag;		
		DWORD	dwObjPacketId;	// 0�±�Ϊnpc��id��1�±�Ϊ��ҵ�id
		DWORD	dwUnKnow2;
		DWORD	dwUnKnow3;
	}theOpenNpcRet[2];
}MMO_RECV_OPEN_NPC_RET,*PMMO_RECV_OPEN_NPC_RET;

typedef struct
{
	DWORD	dwRetValue;		// �ϼܳɹ�����ֵ=0
	DWORD	dwUnKnow1;
	DWORD	dwUnKnow2;
}MMO_RECV_SHANG_JIA_ITEM_RET,*PMMO_RECV_SHANG_JIA_ITEM_RET;

typedef struct
{
	int		nRet;			// �ɹ�=0 ���ɳ���=8
	DWORD	dwSellItemId;	// �ɹ����г�����Ʒ��id
}MMO_RECV_SELL_ITEM_RET,*PMMO_RECV_SELL_ITEM_RET;

typedef struct
{
	int		nRet;		// �����������޷��ύ���� = 3���޷����ͽ�����ķ���ֵ = 1
	DWORD	dwTaskId;	// �ύ�����id
}MMO_RECV_COMPLETE_TASK_GAIL_RET,*PMMO_RECV_COMPLETE_TASK_GAIL_RET;

typedef struct
{
	DWORD	dwActorPacketId;
	DWORD	dwUnKnow1;
	DWORD	dwUnKnow2;
	DWORD	dwUnKnow3;
	DWORD	dwUnKnow4;
	DWORD	dwPoisoningFeebHpFlag;	// �ж�������Ѫ��־ ���Ϊ0���ʾ�����������ߺ����������µĳ�����Ѫ  �����Ϊ0�����ʾ�ж�
}MMO_RECV_FEEB_HP_RET,*PMMO_RECV_FEEB_HP_RET;


typedef struct
{
	byte	bRet;			// ����ֵ=1
	WORD	wUnKnow;
	DWORD	dwItemId;		// ��Ʒid
	byte	bUnKnow;
	WORD	wSlotIndex;		// ��Ʒ���ڸ���
}MMO_RECV_USE_ITEM_RET,*PMMO_RECV_USE_ITEM_RET;

typedef struct
{
	LONGLONG	llItemKey;			// ������Ʒʱ��key1��key2
	byte		bUseItemTableIndex;	// ����=0
	WORD		wItemSlotIndex;		// ��Ʒ���ڲ�
}MMO_RECV_USE_ITEM_RET2,*PMMO_RECV_USE_ITEM_RET2;

typedef struct
{
	int		nRet;			// �ɹ�����0 ���������Ѵ����� 0x20
	DWORD	dwUnKnow;
	DWORD	dwShopItemId;	// ��Ʒid������Ʒid
	int		nCount;			// ��������
}MMO_RECV_BUY_ITEM_RET,*PMMO_RECV_BUY_ITEM_RET;

typedef struct
{
	int		nRet;			// ����ֵΪ1�����಻�ù�
	DWORD	dwCollectObjPacketId;	// ��ǰ���ɼ��Ķ���id
	DWORD	dwUnKnow1;
	DWORD	dwUNKnow2;
	DWORD	dwCollectItemId;		// �ɼ��õ�����Ʒid
	DWORD	dwUnKnow3;
}MMO_RECV_COLLECT_ITEM_BAG_FULL_RET,*PMMO_RECV_COLLECT_ITEM_BAG_FULL_RET;

typedef struct
{
	DWORD dwMoveDealGoldRoleId;
	int	  nMoveDealGoldValue;
}MMO_RECV_MOVE_DEAL_GOLD_RET,*PMMO_RECV_MOVE_DEAL_GOLD_RET;

typedef struct
{
	DWORD dwDoDealRoleId;		// �������׵Ķ���id
	byte  bDoDealIndex;			// 1 ��ʾȡ������ 2 ��ʾ�������������� 3��ʾ������ȷ�Ͻ���
}MMO_RECV_DEAL_STATUS_RET,*PMMO_RECV_DEAL_STATUS_RET;

typedef struct
{
	DWORD dwDealFailRet;		// 0x0029001E ��Ʒ����Я������  0x0029000B �Է��Ѿ��ڽ�����
	DWORD dwDealRoleId;			// ���׶����id
}MMO_RECV_DEAL_FAIL_RET,*PMMO_RECV_DEAL_FAIL_RET;

#define MMOCLIENT_REVERSAL_SEND_MAIL_ANQUAN_TIME_RET___				0x00046CE4		// ��ȫʱ��
#define MMOCLIENT_REVERSAL_SEND_MAIL_ROLE_NAME_NOT_FOUND_RET___		0x00046CD4		// ��ɫ��������
#define MMOCLIENT_REVERSAL_SEND_MAIL_PIN_FAN_RET___					0x00046CE2		// �����ʼ�Ƶ��
typedef struct
{
	int		nRet;		// ����ֵ����ʱһֱΪ1
	DWORD	dwErrorValue;	// �������ֵ
}MMO_RECV_SEND_MAIL_RET2,*PMMO_RECV_SEND_MAIL_RET2;





typedef struct
{
	DWORD	dwUnKnow1;
	DWORD	dwUnKnow2;
	DWORD	dwRolePacketId;
	DWORD	dwUnKnow3;
	DWORD	dwUnKnow4;
	DWORD	dwUnKnow5;
	MMO_Direction2	theRoleDirection;
	MMO_Vector3		theRoleVector;
}GUO_TU_RET,*PGUO_TU_RET;

typedef struct
{
	DWORD dwRequestDealRoleId;		// �����׵Ķ���id		ע�⣺˭���󣬾�˭��ǰ�����������ͽ���ͨ�õ�
	DWORD dwByRequestDealRoleId;	// ͬ�⽻�׵Ķ���id
}MMO_RECV_REQUEST_DEAL_RET,*PMMO_RECV_REQUEST_DEAL_RET;

typedef struct
{
	DWORD dwRequestDealFailValue;		// ����ֵ
	DWORD dwUnKnow1[3];
	byte  bUnKnow2;
	DWORD dwUnKnow3;
	char  szRoleName[21];
}MMO_RECV_REQUEST_DEAL_FIAL_RET,*PMMO_RECV_REQUEST_DEAL_FIAL_RET;


//////////////////////////////////////////////////////////////////////////
// ������Ʒ
typedef struct
{
	DWORD	dwItemAddr;
	DWORD	dwZero1;
	DWORD	dwZero2;
}MM0_ITEM,*PMM0_ITEM;

typedef struct
{
	LONGLONG	llDynamic;		// +0x10
	LONGLONG	llRand;			// +0x18
	MMO_Direction2	dir_zero;	// +0x20
	MMO_Direction2	dir;		// +0x28
	MMO_Vector3		scr_pos;	// +0x30
	WORD			wzero1;		// +0x3c
	MMO_Vector3		dir_unknow1;// +0x3e
	WORD			wflag;		// +0x4a
	DWORD			dwzero1[17];
	WORD	wUnKnow1;			// +0x90
	WORD	wUnKnow2;			// +0x92
	float	fHitTime;			// +0x94 ����ʱ��һ���ٶ�ֵ���������Ķ�����С��ֵ���
	float	fUnKnow2;			// +0x98
	WORD	wUnKnow3;			// +0x9a
	DWORD	dwZeor2[20];
}MMO_HIT,*PMMO_HIT;

typedef struct  
{
	DWORD	dwTaskId;
	int		nFlag;
}MM0_ACCEPT_TASK,*PMM0_ACCEPT_TASK;

typedef struct
{
	NODE	theNode;
	DWORD	dwTaskId;
	DWORD	dwTaskAddr;
}MMO_RECEIVED_TASK_POINT,*PMMO_RECEIVED_TASK_POINT;

struct stFbDoorLink{
	int				template_map_id_;	//ģ���ͼID
	int				room_id_src_;		//Դ�����
	std::string		door_name_src_;		//Դ�����е��ŵ�����
	int				room_id_dst_;		//Ŀ�귿���
};

typedef struct
{
	DWORD dwMaterialItemId;
	int	  nCount;
}MMO_MATERIAL_ITEM,*PMMO_MATERIAL_ITEM;

typedef struct
{
	DWORD	dwVFunAddr;
	GAME_STRUCT_ARRAY_POINT	theUpEquipMaterialInfo;
	DWORD	dwUnKnow1;
	DWORD	dwUpEquipItemId;
	DWORD	dwUnKnow2[6];
}MMO_UP_EQUIP_ITEM_MATERIAL_INFO,*PMMO_UP_EQUIP_ITEM_MATERIAL_INFO;

typedef struct		// ������λ�Ľṹ��
{
	byte	bUnKnowFloat[0x20];		// �Թ����ͷΪǰ��������
	MMO_Vector3		theRangeRight;	// ���ﲿλ�ұ�
	MMO_Vector3		theRangeLeft;	// ���ﲿλ���
	DWORD			dwUnKnow1;
	DWORD			dwUnKnow2;
	int				dwBuWeiId;		// ��λid
	byte	bUnKnowCode[0x34];
}MMO_BU_WEI_OBJ_STRUCT,*PMMO_BU_WEI_OBJ_STRUCT;

typedef struct
{
	DWORD	dwUnKnow1;
	int		nFarmTime;		// ��ֲʱ��
	DWORD	dwUnKnow3;
	DWORD	dwCurFarmFacilityLevel;	// ��ǰ�ɼ���ȼ�
	DWORD	dwUnKnow4;
}MMO_CUR_FARM_FACILITY,*PMMO_CUR_FARM_FACILITY;

typedef struct
{
	int		nFarmFlag;		// ��ҩ���Ƿ����ı�־ ����=1��δ����=0
	DWORD	dwSeedId;		// ��ֲ������id
	int		nUnKnow;
}MMO_FARM_FACILITY_STATE,*PMMO_FARM_FACILITY_STATE;

typedef struct
{
	DWORD	dwMaterialId;		// ��Ҫ�Ĳ���id
	DWORD	dwUnKnow[6];
	int		nMaterialCount;		// ��Ҫ�Ĳ�������
}MMO_MANU_MATERIAL,*PMMO_MANU_MATERIAL;


typedef struct
{
	int		nSlotIndex;		// ��Ʒ���ڲ�����ڼ����1��ʼ
	DWORD	dwItemId;		// ��Ʒ��id
	int		nCount;			// ��Ʒ������
	/*++
	$ ==>    >00000002
	$+4      >00001771
	$+8      >00000001
	--*/
}MMO_REQUIRE_CUR_SLOT,*PMMO_REQUIRE_CUR_SLOT;

typedef struct  
{
	DWORD dwNextNode;
	DWORD dwPreNode;
	PMMO_REQUIRE_CUR_SLOT	ptheCurSlot;
}MMO_REQUIRE_SLOT,*PMMO_REQUIRE_SLOT;


typedef struct
{
	DWORD	dwVFunAddr;
	GAME_STRUCT_ARRAY_POINT	theRewardItemAddr;		// ������Ʒ�ı����ṹ��
}MMO_TASK_REWARD_ITEM,*PMMO_TASK_REWARD_ITEM;

typedef struct
{
	DWORD	dwVFunAddr;		
	DWORD	dwItemAddr;		// ��Ʒģ��ĵ�ַ
	int		nCount;			// ������Ʒ������
}MMO_TASK_REWARD_ITEM_INFO,*PMMO_TASK_REWARD_ITEM_INFO;

typedef struct
{
	NODE	theNode;		
	DWORD	dwGiftBagId;	// �����id
	DWORD	dwGiftBagAddr;
}MMO_GIFT_BAG_INFO,*PMMO_GIFT_BAG_INFO;

#pragma pack(pop)
