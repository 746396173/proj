#pragma once
/*
@author zhp
@date 2016/4/11 21:39
*/
#include <ProtocolX/P_DefinesX.h>
#include <cstddef>
#include <Windows.h>
#include "CD_StructsBase.h"

#pragma pack(push)
#pragma pack(1)
//////////////////////////////////////////////////////////////////////////
//MM0_RECV_REQ_ITEM_BY_TYPE
struct stCD_MsgR_ReqItemByType{
	DWORD	dwReqItemById;		// ��������Ʒid������Ʒid����Ҫ���ȷ����Ʒid
	DWORD	dwReqItemByKey;		// ����������Ʒ��Ҫ�õ���keyֵ
	DWORD	dwUnKnow1;
	DWORD	dwUnKnow2;
	char	szReqItemByPlayerName[kRoleBufferMaxSize];
	pt_byte	bFlag;
	DWORD	dwUnKnow3;
	int		nReqItemByPrice1;		// ���ļ�
	int		nReqItemByPrice2;		// һ�ڼ�
	int		nReqItemByPrice3;		// ���ļ�
	p_mem_placeholder(g_o_msg_req_item_1_ - 4 - 61);
	pt_word	ukn_;		//UPDATES_MMOCLIENT_REVERSAL_RECV_REQ_ITEM_BY_GET_ITEM_ID_OFFSET1
	int		ukn_id_;	//UPDATES_MMOCLIENT_REVERSAL_RECV_REQ_ITEM_BY_GET_ITEM_ID_OFFSET2
	p_mem_placeholder(0xef - 4 - g_o_msg_req_item_2_);
};
static_assert(offsetof(stCD_MsgR_ReqItemByType, nReqItemByPrice3) == 61, "");
static_assert(sizeof(stCD_MsgR_ReqItemByType) == 65 + 0xae, "");
static_assert(offsetof(stCD_MsgR_ReqItemByType, ukn_) == g_o_msg_req_item_1_, "");
static_assert(offsetof(stCD_MsgR_ReqItemByType, ukn_id_) == g_o_msg_req_item_2_, "");

struct stCD_MsgR_OnRefreshMySellList{
	p_mem_placeholder(8);
	stCD_MsgArray<stCD_MsgR_ReqItemByType, pt_word, 1> req_items_;		//MMOCLIENT_REVERSAL_PACKET_RECV_MSG_MY_REQ_COUNT_OFFSET___ MMOCLIENT_REVERSAL_PACKET_RECV_MSG_MY_REQ_DATA_OFFSET___
};

//MMO_RECV_REQ_ITEM_BY_HEADER
struct stCD_MsgR_OnGainAuctionPageInfo{
	DWORD	dwRet;		// ����ֵ
	int		nDoCount;	// ����
	DWORD	dwUnKnow;	// ���������֪��
	int		nReqItemCount;	// ��Ʒ����������ҳ����Ҫ����8�����������������Ҫ��+1
	stCD_MsgArray<stCD_MsgR_ReqItemByType, pt_word, 1> req_items_;
};

//�������ṹ MM0_PLAYER_LIST
struct stCD_MsgR_RoleList_Role{
	pt_dint		ukn1_;
	DWORD		dwPlayerId;
	char		szPlayerName[kRoleBufferMaxSize];
	pt_byte		bChosseFlag;
	int			nPlayerLevel;
	pt_byte		bszUnKnow[0x501 - 0x31];
};
static_assert(sizeof(stCD_MsgR_RoleList_Role) == 0x501, "");

struct stCD_MsgR_RoleList{
	int			ukn_[3];
	stCD_MsgArray<stCD_MsgR_RoleList_Role, pt_word, 6>	role_list_;	//MMOCLIENT_REVERSAL_RECV_PLAYER_LIST_COUNT___  MMOCLIENT_REVERSAL_RECV_PLAYER_INFO_OFFSET___
};

//MMO_GAME_IN_FB_RET_PACKET
struct stCD_MsgR_OnEnterFb{
	DWORD	dwRolePacketId;
	int		nError;		// 0��ʾ�����������븱��  ��0��ʾ���ɽ��븱�����缤�˸���ƣ��״̬������ί�и����Ѿ����꣬ע�⣺���ḱ�����Դ�3�Σ�����ÿ������ֻ�ܴ�һ��
	//int		nRet;		// 1��ʾ��ͨ��������ֵ�ͼ��˸�������ֵ  2��ʾ���ḱ������ֵ 
};
//sizeof(stCD_MsgR_OnEnterFb)==66

//MMO_RECV_USE_ITEM_RET
struct stCD_MsgR_OnUseItemRet1{
	byte	bRet;			// ����ֵ=1
	WORD	wUnKnow;
	DWORD	dwItemId;		// ��Ʒid
	byte	bUnKnow;
	WORD	wSlotIndex;		// ��Ʒ���ڸ���
	//��ʵ����ṹ����pod
	p_mem_placeholder(56 - 10);
};

struct stCD_MsgR_OnSendMail{
	int			res_;
	pt_dint		ukn_;		//==0
	char		str_dst_role_name_[20];			//���ʼĵ�����
};

//MMO_RECV_SEND_MAIL_RET2
struct stCD_MsgR_OnSendMail2{
	int		nRet;		// ����ֵ����ʱһֱΪ1
	DWORD	dwErrorValue;	// �������ֵ
	int		ukn_1_;		//==0
	int		ukn_2_;
	//���ﻹ�и��ֶΣ�Ӧ�ñ�ʾ�����ַ���
};

//MMO_RECV_REQUEST_DEAL_FIAL_RET
struct stCD_MsgR_OnRequestDealFail{
	enum enSubType{
		kOnDealFail = 4,
	};

	DWORD		dwRequestDealFailValue;		// ����ֵ
	DWORD		dwUnKnow1;
	pt_dint		ukn_;
	pt_byte		bUnKnow2;
	DWORD		dwUnKnow3;
	pt_byte		sub_type_;	//==4��ʱ��szRoleName�ֶβű�ʾ����
	char		szRoleName[21];
};

struct stCD_MsgR_OnRecvQuestDeal{
	pt_dword	deal_key_;
	pt_byte		ukn_1_;		//==1
	int			ukn2_;		//����ֶ�Ҫ����deal_key_��Ҫ�����ǽ����ߵ�ID
	pt_byte		ukn3_;		//==1,�Ժ���һ�����л������顣
};

//MMO_RECV_OPEN_NPC_RET
struct stCD_MsgR_OnOpenNpc{
	pt_byte	res_;		//�򿪳ɹ�����ֵ=2
	int		ukn_zero_;
	int		open_flag_;	//==1  nOpenFlag
	int		npc_packet_id_;		//100000c5
	int		ukn_2_;
	int		ukn_3_;

	int		role_packet_id_;
	int		ukn_4_;
	int		ukn_5_;
	int		ukn_6_;
	int		ukn_7_;
};

//////////////////////////////////////////////////////////////////////////
//////////////////////*******���¼̳���stCD_CheckMsgAtRuntime**************
//MMO_GAME_LINE
BC_DEFINE_POD(stCD_MsgR_SerLineInfo){
	WORD	wLineIndex;
	pt_byte bLineLevel;
	pt_byte bUnKnow;
};
struct stCD_MsgR_SerLine : stCD_CheckMsgAtRuntime{	
	template<typename T>
	void serialize(T& stm){
		stm & ser_lines_;
	}

	stCD_MsgArray<stCD_MsgR_SerLineInfo, pt_word>		ser_lines_;
};

//MMO_FB_SERVER_FULL_RET
struct stCD_MsgR_OnEnterFbError : stCD_CheckMsgAtRuntime{
	template<typename T>
	void serialize(T& stm){
		stm & dwUnKnow1
			& dwUnKnow2
			& dwRetValue
			& dwRolePacketId
			& BC_OriStrArray<decltype(szRoleName)&>(szRoleName);
	}

	DWORD dwUnKnow1;
	DWORD dwUnKnow2;
	DWORD dwRetValue;		// ���Է�������������ֵ=0x73 ������������ֵ=0x6A
	DWORD dwRolePacketId;	// ��ɫ�����id
	char  szRoleName[20];	// ��ɫ����
};

//MMO_TASK_FB_INFO_
struct stCD_MsgR_TaskFbInfo{
	DWORD	dwFbType;		// ��������  ����=0x00000065 ǧ��=0x000000C9
	stCD_MsgArray<int, pt_word, 0x32>	fb_ids_;

	template<typename T>
	void serialize(T& stm){
		stm & dwFbType & fb_ids_;
	}
};

//MMO_TASK_FB_INFO
struct stCD_MsgR_OnFbInfo : stCD_CheckMsgAtRuntime{
	template<typename T>
	void serialize(T& stm){
		stm & dwRetValue & fb_info_;
	}

	DWORD	dwRetValue;
	//DWORD	dwTaskFbType;		// 01��ʾ���ḱ��  04 ��ʾǧ������  03 ��ʾ��������
	stCD_MsgArray<stCD_MsgR_TaskFbInfo, pt_word, 1> fb_info_;
};

//MMO_RECV_COLLECT_ITEM_BAG_FULL_RET
struct stCD_MsgR_OnCollectRet : stCD_CheckMsgAtRuntime{
	int		nRet;			// ����ֵΪ1�����಻�ù�
	DWORD	dwCollectObjPacketId;	// ��ǰ���ɼ��Ķ���id
	DWORD	dwUnKnow1;

	struct stItemInfo{
		DWORD	dwCollectItemId;		// �ɼ��õ�����Ʒid
		int		item_cnt_;
		int		ukn_zeor_;

		template<typename T>
		void serialize(T& stm){
			stm & dwCollectItemId & item_cnt_ & ukn_zeor_;
		}
	};
	stCD_MsgArray<stItemInfo, int> gained_items_;

	template<typename T>
	void serialize(T& stm){
		stm & nRet & dwCollectObjPacketId & dwUnKnow1 & gained_items_;
	}
};

//MMO_RECV_SELL_ITEM_RET
struct stCD_MsgR_OnSoldItemToShop : stCD_CheckMsgAtRuntime{
	int		nRet;			// �ɹ�=0 ���ɳ���=8
	DWORD	dwSellItemId;	// �ɹ����г�����Ʒ��id
	int		sell_item_cnt_;
	int		ukn1_;
	stCD_MsgArray<pt_byte, pt_word>	ukn_;

	template<typename T>
	void serialize(T& stm){
		stm & nRet & dwSellItemId & sell_item_cnt_ & ukn1_ & ukn_;
	}
};
//////////////////////////////////////////////////////////////////////////
//////////////////////*******���¼̳���stCD_CheckMsgAsPOD******************
struct stCD_MsgR_OnCreateRole : stCD_CheckMsgAsPOD{
	int		res_;
	int		ukn_[2];
	pt_word	ukn1_;
};
static_assert(sizeof(stCD_MsgR_OnCreateRole) == 0xe, "");

struct stCD_MsgR_OnSafeTime : stCD_CheckMsgAsPOD{
	int		left_time_;
};

//MMO_RECV_REQ_BUY_ITEM_RET
struct stCD_MsgR_OnBuyAuction : stCD_CheckMsgAsPOD{
	DWORD dwBuyItemRet;		// ����ɹ� = 0
	pt_dint	req_item_id_;	//�������Ʒ����id
	pt_int	ukn_;		//==0xa
	pt_byte	ukn1_;		//==0
};

//PMM0_ACCEPT_MAIL_RET_VALUE
struct stCD_MsgR_OnAcceptMail : stCD_CheckMsgAsPOD{
	int		nSize;
	DWORD	nRetValue;			// nRetValue = 0�� nRetError = -1 ��ʾ��ȡ����ʧ��
	pt_dint	mail_serial_;
	int		nRetError;			// nRetValue = 0x29�� nRetError = -2 ��ʾ��ȡ����ʧ��:����Я������
	int		ukn_;		//==3
	pt_byte	ukn_1_;		//==1
};

//MMO_RECV_SHANG_JIA_ITEM_RET
struct stCD_MsgR_OnSoldAuction : stCD_CheckMsgAsPOD{
	DWORD	dwRetValue;		// �ϼܳɹ�����ֵ=0
	pt_dint	product_id_;	//�ϼ���Ʒ��ID
};

//MMO_RECV_COMPLETE_TASK_GAIL_RET
struct stCD_MsgR_OnCommitTaskFailed : stCD_CheckMsgAsPOD{
	int		nRet;		// �����������޷��ύ���� = 3���޷����ͽ�����ķ���ֵ = 1
	DWORD	dwTaskId;	// �ύ�����id
};

struct stCD_MsgR_OnDoNpcChat : stCD_CheckMsgAsPOD{
	int		task_id_;
	int		zero_;	//=0
	int		ukn_1_;	//=1
};

//MMO_RECV_FEEB_HP_RET
struct stCD_MsgR_OnBuffStatus : stCD_CheckMsgAsPOD{
	DWORD	dwActorPacketId;
	DWORD	dwUnKnow1;
	DWORD	dwUnKnow2;
	DWORD	dwUnKnow3;
	DWORD	dwUnKnow4;
	DWORD	dwPoisoningFeebHpFlag;	// �ж�������Ѫ��־ ���Ϊ0���ʾ�����������ߺ����������µĳ�����Ѫ  �����Ϊ0�����ʾ�ж�
};

//MMO_RECV_BUY_ITEM_RET
struct stCD_MsgR_OnBuyItem : stCD_CheckMsgAsPOD{
	int		nRet;			// �ɹ�����0 ���������Ѵ����� 0x20
	DWORD	dwUnKnow;
	DWORD	dwShopItemId;	// ��Ʒid������Ʒid
	int		nCount;			// ��������
};

//GUO_TU_RET
struct stCD_MsgR_OnSendMoveRoomRet : stCD_CheckMsgAsPOD{
	pt_dint	ukn_;
	DWORD	dwRolePacketId;
	DWORD	dst_room_num_;		//Ŀ�귿���
	DWORD	dwUnKnow4;			//==0
	DWORD	dwUnKnow5;			//==0
	int		ukn_1_;
	int		ukn_2_;
	stCD_Direction2		theRoleDirection;
	stCD_Vector3		theRoleVector;
};

//MMO_ACCEPT_TASK
struct stCD_MsgR_OnAcceptTaskRet : stCD_CheckMsgAsPOD{
	DWORD				dwTaskId;
	DWORD				dwTaskZero;
};

//MMO_GIVE_UP_TASK
struct stCD_MsgR_OnGiveupTaskRet : stCD_CheckMsgAsPOD{
	DWORD				dwTaskId;
};

//MMO_RECV_DELETE_PLAYER
struct stCD_MsgR_OnDeleteRole : stCD_CheckMsgAsPOD{
	int nRet;
	int nRetParamer;
};

//MMO_RECV_REQUEST_DEAL_RET
struct stCD_MsgR_OnRequestDeal : stCD_CheckMsgAsPOD{
	DWORD dwRequestDealRoleId;		// �����׵Ķ���id		ע�⣺˭���󣬾�˭��ǰ�����������ͽ���ͨ�õ�
	DWORD dwByRequestDealRoleId;	// ͬ�⽻�׵Ķ���id
};

struct stCD_MsgR_OnCancelDeal : stCD_CheckMsgAsPOD{
	pt_dword	role_id_of_cancel_;
};

//MMO_RECV_DEAL_FAIL_RET
struct stCD_MsgR_OnDealFail : stCD_CheckMsgAsPOD{
	/*pt_word	res_;
	pt_word	ukn_;*/
	int		dwDealFailRet;		//��ʵ����ֶ�������word���͡�0x0029001E ��Ʒ����Я������  0x0029000B �Է��Ѿ��ڽ�����
	int		deal_role_id_;		//���׶����id
	pt_word	ukn1_[3];
};

//MMO_DEAL_MOVE_ITEM
struct stCD_MsgR_OnMoveItemToDealTab : stCD_CheckMsgAsPOD{
	WORD	wScrItemTabIndex;	// ����=0 �ֿ��ز�=0x0A ��ͨ�ֿ�=2
	WORD	wScrItemSlotIndex;	// ������ֿ������ӣ���0��ʼ����
	WORD	wMoveItemCount;		// �ƶ���Ʒ������
	WORD	wDealSlotaIndex;	// �������ĸ��ӣ���0��ʼ����
};

//MMO_RECV_MOVE_DEAL_GOLD_RET
struct stCD_MsgR_OnMoveDealGold : stCD_CheckMsgAsPOD{
	DWORD dwMoveDealGoldRoleId;
	int	  nMoveDealGoldValue;
};

//MMO_RECV_DEAL_STATUS_RET
struct stCD_MsgR_OnRecvDealStatus : stCD_CheckMsgAsPOD{
	DWORD dwDoDealRoleId;		// �������׵Ķ���id
	pt_byte  bDoDealIndex;			// 1 ��ʾȡ������ 2 ��ʾ�������������� 3��ʾ������ȷ�Ͻ���
};

struct stCD_MsgR_OnRecvDealEnd : stCD_CheckMsgAsPOD{
	pt_byte		res_;
};

struct stCD_MsgR_MonsterDead : stCD_CheckMsgAsPOD{
	p_mem_placeholder(8);
	pt_dword		monster_id_;	//MMOCLIENT_REVERSAL_PACKET_MSG_MOSTER_SIWANG_PACKET_ID
};

struct stCD_MsgR_RoleDead : stCD_CheckMsgAsPOD{
	pt_dword		packet_id_;	//MMOCLIENT_REVERSAL_RECV_PACKET_DATA_OFFSET___
};
//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)
