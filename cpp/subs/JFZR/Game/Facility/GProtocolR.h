#pragma once
/*
@author zhp
@date 2014/8/19 15:44
@purpose for recv/read
*/
#include "GProtocolBase.h"
#include "GameArray.h"
#include <memory>
#include <Communicate/CG_Defines.h>
#include <boost/optional.hpp>

struct CMDR_HeaderBase : CMD_HeaderBase{
protected:
	CMDR_HeaderBase();

public:
	WORD		hash_uri_;			//��Ϣ��

	const void* GetRealMsgAddr() const{
		static_assert(sizeof(*this) == 6, "");
		return (char*)this + sizeof(*this);
	}
	WORD GetRealMsgSize() const{
		assert(total_length_ >= sizeof(*this));
		return total_length_ - sizeof(*this);
	}
};
static_assert(sizeof(CMDR_HeaderBase) == sizeof(PACKET_HEADER), "");

typedef stBStreamInput CMDR_InBase;
struct CMDR_MsgBase : CMDR_InBase, std::enable_shared_from_this<CMDR_MsgBase>{
public:
	typedef std::shared_ptr<CMDR_MsgBase> SelfPtr;
	using CMDR_InBase::Read;

public:
	B_STREAM_INPUT(CMDR_MsgBase)
	virtual CMDR_MsgBase* Clone() const;
	virtual void OnReceived() const;
	virtual boost::optional<WORD> NewRetOffset() const;
};
#define CMDR_INPUT_IMPL(DerivedT) B_STREAM_INPUT(DerivedT)	\
	DerivedT* Clone() const{	\
	return new DerivedT;	\
}	\
/**/

//ѡ��Ƶ��ʱȡֵ����
struct CMDR_AllowSwitchChannel : CMDR_MsgBase{
	struct stServerInfo : CMDR_InBase{
		stServerInfo();
		bool Read( StrInputBStreamBase& istm );
		B_STREAM_INPUT(stServerInfo)

		WORD		allm_net_address_;
		std::string	str_ip_;
		WORD		port_;
	};

	CMDR_AllowSwitchChannel();
	bool Read( StrInputBStreamBase& istm );
	CMDR_INPUT_IMPL(CMDR_AllowSwitchChannel)

	DWORD						unknown_result_;
	std::wstring				channel_id_;
	std::wstring				account_id_;
	std::wstring				session_key_;
	WORD						stage_server_addresses_;
	GameArrayT<stServerInfo>	server_info_;
	std::wstring				prev_channel_id_;
};

//Ƶ������
struct CMDR_ChannelList : CMDR_MsgBase{
	struct stChannelInfo : CMDR_InBase{
		stChannelInfo();
		bool Read( StrInputBStreamBase& istm );
		B_STREAM_INPUT(stChannelInfo)
		//����Ȩ��
		int CalcFreeWeight() const;

		WORD			wApple_ChannelElementForClient;
		DWORD			dwChannelNumber;
		std::wstring	channel_id_;					// Ƶ��id �磺 "channel_03_01"
		std::wstring	title_;						// ���� �磺Ƶ��1
		bool			enabled_;						// ����״̬  1Ϊ�ɵ�½  0Ϊ���ɵ�½
		int				capacity_;						// �ɽ���Ƶ���������
		int				player_count_;					// ʵ���������
		DWORD			dwMinPvpPoint;
		DWORD			dwMaxPvpPoint;
		DWORD			dwChannelPropertyId;
	};

	CMDR_ChannelList();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_ChannelList)

	WORD						channels_;
	GameArrayT<stChannelInfo>	channels_info_;;
};

//ѡ���ɫ��������ɫ��Ϣ
struct CMDR_PartialListPlayersStaticInfo : CMDR_MsgBase{
	CMDR_PartialListPlayersStaticInfo();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	bool ConvertToRoleInfo( CG_RoleInfo& role_info ) const;
	CMDR_INPUT_IMPL(CMDR_PartialListPlayersStaticInfo)

	std::wstring				account_id_;
	WORD						wStaticInfo;
	WORD						wApple_StaticPlayerInfo;
	std::wstring				player_name_;			// �������
	LONGLONG					lPlayerSerial;
	std::wstring				strPlayerGender;		// ����Ա�
	std::wstring				player_job_name_;			// ְҵ����
	WORD						wCreatedDateTime;
	WORD						wApple_DateTime;
	WORD						wYear;
	WORD						wMonth;
	WORD						wDay;
	WORD						wHour;
	DWORD						dwMinute;
	DWORD						dwSecond;
	DWORD						dwMilliSec;
	bool						bIsInfinity;
	bool						is_deleted_;				// ��ɫ�Ƿ���ɾ��״̬  00 ����״̬�� 01 ɾ��״̬
};

//�������ͽ�ɫ��Ϣ�ķ��
struct CMDR_EndPartialListPlayers : CMDR_MsgBase{
	CMDR_EndPartialListPlayers();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_EndPartialListPlayers)

	std::wstring	account_id_;
	std::wstring	selected_player_id_;
	DWORD			dwConnectionSerial;
	DWORD			dwSendingType;
};

//��Ӧ������ɫ
struct CMDR_OnCreatePlayer : CMDR_MsgBase{
	enum enResult{
		kSucceed = 0,
		kWordProhibit = 1,			//����Υ���ַ�
		kNameIsUsed = 6,			//��ɫ���ѱ�ʹ��
	};
	CMDR_OnCreatePlayer();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnCreatePlayer)

	enResult			result_;
};

//��Ӧ�ʼ�
struct CMDR_OnMailList : CMDR_MsgBase{
	struct stMailItem : CMDR_InBase{
		stMailItem();
		bool Read( StrInputBStreamBase& istm );
		B_STREAM_INPUT(stMailItem)

		LONGLONG			mail_serial_;
		std::wstring		title_;
		std::wstring		sender_;
		LONGLONG			gold_;
		std::wstring		sample_item_id_;
		std::wstring		mail_type_;
	};

	CMDR_OnMailList();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnMailList)

	DWORD					result_;
	GameArrayT<stMailItem>	mail_items_;
};

//�����ʼ���Ʒ�󣬸��´��ʼ�����
struct CMDR_RecvMailContents : CMDR_MsgBase{
	CMDR_RecvMailContents();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_RecvMailContents)

	int				result_;
	LONGLONG		mail_serial_;
	int				mail_item_cnt_;
};

//��Ӧget attachments
struct CMDR_OnGetAttachments : CMDR_MsgBase{
	CMDR_OnGetAttachments();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnGetAttachments)

	int				result_;
	LONGLONG		mail_serial_;
};

//��Ӧ�ҵ������б�
struct CMDR_OnMyProductList : CMDR_MsgBase{
	struct stMyProduct : CMDR_InBase{
		stMyProduct();
		bool Read( StrInputBStreamBase& istm );
		B_STREAM_INPUT(stMyProduct)

		LONGLONG			oid_market_;
		std::wstring		item_id_;
		int					item_cnt_;
		int					item_grade_;		//��Ҫ��ƷƷ������Ʒ�ȼ��������Ϣ�������ȷ���Ƿ�����ƷƷ�ʵ���Ϣ
		LONGLONG			price_;
	};

	CMDR_OnMyProductList();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnMyProductList)

	GameArrayT<stMyProduct>		my_products_;
	int							result_;
};

//��Ӧ������
struct CMDR_OnRegisterProduct : CMDR_MsgBase{
public:
	enum enRegisterProductResult{
		kRPR_Succeed,
		kRPR_PerAcLimit,
		kRPR_PerRoleLimit,
		kRPR_CanNotMoveItem,
		kRPR_Invalid,
	};

public:
	CMDR_OnRegisterProduct();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnRegisterProduct)

	enRegisterProductResult		result_;
};

//��Ӧ��������Ʒ
struct CMDR_OnBuyProduct : CMDR_MsgBase{
	CMDR_OnBuyProduct();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnBuyProduct)

	int		result_;
};

//��Ӧ������Ʒ��Ϣ
struct CMDR_OnRequestProductInfo : CMDR_MsgBase{
	CMDR_OnRequestProductInfo();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnRequestProductInfo)

	int			result_;
	LONGLONG	average_price_;			//������ܵ�
	int			trade_count_;			//������״���
	LONGLONG	lower_price_;
};

struct CMDR_OnRequestProductList : CMDR_MsgBase{
	struct stProductItem : CMDR_InBase{
		stProductItem();
		bool Read( StrInputBStreamBase& istm );
		B_STREAM_INPUT(stProductItem)

		LONGLONG			oid_market_;
		std::wstring		item_id_;
		std::wstring		item_ch_name_;
		int					item_cnt_;
		int					item_grade_;		//��Ҫ��ƷƷ������Ʒ�ȼ��������Ϣ�������ȷ���Ƿ�����ƷƷ�ʵ���Ϣ
		LONGLONG			price_;
	};

	CMDR_OnRequestProductList();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnRequestProductList)

	GameArrayT<stProductItem>	product_items_;
	int							result_;
};

//��Ӧ��½���
struct CMDR_OnLoginResult : CMDR_MsgBase{
	enum enResult{
		kSucceed = 0,
		kBanAc = 3,			//���
	};
	CMDR_OnLoginResult();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnLoginResult)

	int							result_;
};

//����Ʒ��Ӧ���
struct CMDR_OnSellItemResult : CMDR_MsgBase{
	enum enResult{
		kSucceed = 0,
		kRestrict = 6,
	};
	CMDR_OnSellItemResult();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnSellItemResult)

	enResult					result_;
};

//��Ӧ������
struct CMDR_OnAcceptQuestResult : CMDR_MsgBase{
	enum enResult{
		kSucceed = 0,
		kRestrict = 0x12,
	};
	CMDR_OnAcceptQuestResult();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnAcceptQuestResult)

	enResult					result_;
};

//���븱�����
struct CMDR_OnStartStageResult : CMDR_MsgBase{
	enum enResult{
		kSucceed = 0,
		kLimitCnt = 6,		//�ѳ����볡��������
		kRestrict = 0x0f,	//�����ƽ��븱��
	};
	CMDR_OnStartStageResult();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnStartStageResult)

	struct stPlayersInfo : CMDR_InBase{
		bool Read( StrInputBStreamBase& istm );
		B_STREAM_INPUT(stPlayersInfo)

		std::wstring	player_id_;
	};

	GameArrayT_<stPlayersInfo>	players_info_;
	enResult					result_;
};

//hook change village
struct CMDR_OnChangeVillage : CMDR_MsgBase{
	enum enResult{
		kSucceed = 0,
		kRestrict = 1,		//�����ƽ��븱��
	};
	CMDR_OnChangeVillage();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnChangeVillage)

	enResult					result_;
};

//create NPC
struct CMDR_OnCreateNPC : CMDR_MsgBase{
	CMDR_OnCreateNPC();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnCreateNPC)

	std::wstring			obj_id_;
	std::wstring			team_id_;
	bool					is_dummy_;
	bool					has_valid_data_;
	DWORD					valid_data_x_;
	DWORD					valid_data_y_;
};

struct CMDR_OnCreateNpcByClient : CMDR_MsgBase{
	CMDR_OnCreateNpcByClient();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnCreateNpcByClient)

	DWORD				task_npc_serial_;
};

struct CMDR_OnPlayerDead : CMDR_MsgBase{
	CMDR_OnPlayerDead();
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_OnPlayerDead)

	DWORD				player_serial_;
};
//////////////////////////////////////////////////////////////////////////
//*************************hook send msg**********************************
//hookÿ������������ᷢ�İ�
struct CMDR_Hook_EnteredCloneMap : CMDR_MsgBase{
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_Hook_EnteredCloneMap)
};

//��Ӧѡ���ɫ
struct CMDR_Hook_SelectPlayer : CMDR_MsgBase{
	bool Read( StrInputBStreamBase& istm );
	void OnReceived() const;
	CMDR_INPUT_IMPL(CMDR_Hook_SelectPlayer)
};

//hook��Ϸ����ѡ��Ƶ���ķ��
struct CMDR_Hook_RequestSwitchChannel : CMDR_MsgBase{
	bool Read( StrInputBStreamBase& istm );
	boost::optional<WORD> NewRetOffset() const;
	CMDR_INPUT_IMPL(CMDR_Hook_RequestSwitchChannel)
};

//hook�������
struct CMDR_Hook_RequestProjectileHit : CMDR_MsgBase{
	bool Read( StrInputBStreamBase& istm );
	CMDR_INPUT_IMPL(CMDR_Hook_RequestProjectileHit)
};

//hook add buff
struct CMDR_Hook_RequestAddBuff : CMDR_MsgBase{
	bool Read( StrInputBStreamBase& istm );
	boost::optional<WORD> NewRetOffset() const;
	CMDR_INPUT_IMPL(CMDR_Hook_RequestAddBuff)
};

//hook change hp
struct CMDR_Hook_RequestChangeHp : CMDR_MsgBase{
	bool Read( StrInputBStreamBase& istm );
	CMDR_INPUT_IMPL(CMDR_Hook_RequestChangeHp)
};

//change sector
struct CMDR_Hook_ChangeSector : CMDR_MsgBase{
	bool Read( StrInputBStreamBase& istm );
	boost::optional<WORD> NewRetOffset() const;
	CMDR_INPUT_IMPL(CMDR_Hook_ChangeSector)
};
//////////////////////////////////////////////////////////////////////////