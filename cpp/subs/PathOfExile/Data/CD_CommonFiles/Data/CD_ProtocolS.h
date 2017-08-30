#pragma once
/*
@author zhp
@date 2017/1/24 17:22
*/
#include "CD_Serialize.hpp"
#include "CD_StructBase.h"

#pragma pack(push)
#pragma pack(1)

/*
PreGameState��InGameState�ֱ��������׽��֣���ϢID�ǲ�ͬ�ģ����ǵײ�Э����һ���ġ�
ÿ�ν����ͼ����Ͽ�֮ǰ�����ӣ�������һ���µ����ӣ�˵��һ����ͼ����һ����������
*/
//////////////////////////////////////////////////////////////////////////
enum CD_enPreMsgIdS : pt_word{
	kPMIS_PlayGame = 0xa,			//ѡ���ɫ������Ϸ
};
//////////////////////////////////////////////////////////////////////////
enum CD_enMsgIdS : pt_word{
#ifdef VER_GJ3_
	kMIS_FirstPacket = 0x1,			//������ܶ�������ᷢ��������Ʒ��ʹ�ü���֮��ģ��������ܹ���ס�ϴεķ��������ɣ�������
	kMIS_EnterMapConnection,
	kMIS_EnterMap,					//�л���ͼ��ʱ���ȷ�������ٷ������Ǹ����������ŷ��͵ġ���������ȱһ���ɡ�
	kMIS_OperCommand = 0x9,			//�������������ݻ���Ʒ�ᷢ�����
	kMIS_CreateRole = 0x0d,			//�Ѹ���
	kMIS_HeartBeat = 0x10,			//δ���£�����Ҫ����
	kMIS_OpenObject = 0x13,
	kMIS_UseSkill = 0x14,
	kMIS_SkillUsing = 0x14,			//���ʷ�û�����
	kMIS_UseSkillEnd = 0x14,		//���ʷ�û�����
	kMIS_TakeupItem = 0x17,
	kMIS_ThrowItem = 0x18,
	kMIS_PutdownItem = 0x19,
	kMIS_TakeoffGem = 0x1a,
	kMIS_InsideGem = 0x1b,
	kMIS_LvlUpGem,
	kMIS_LvlUpPassiveSkill = 0x1e,		//������棬��UIʵ�ֺ��鷳�ġ�
	kMIS_MergeItem = 0x26,
	kMIS_WayPoint = 0x29,
	kMIS_Revive = 0x2c,
	kMIS_UseItem = 0x2e,
	kMIS_UseFlask = 0x33,
	kMIS_UseItemTo = 0x34,
	kMIS_SplitItem = 0x3c,
	kMIS_ChangedMapFirstPackage = 0x3b,
	kMIS_NpcTalkItem = 0x40,
	kMIS_CloseNpc = 0x44,
	kMIS_NpcInventoryItemPutToSelfInventory = 0x46,
	kMIS_BuyItem_ToBag = 0x48,
	kMIS_InstanceManager = 0x5c,	//new fb
	kMIS_Sell_Cancle = 0x5e,
	kMIS_PutItemToShop = 0x5f,
	kMIS_PutbackItemFromShop = 0x60,
	kMIS_Sell_Accept,
	kMIS_UknItemOper = 0xb9,		//δ���£�����Ҫ����
	kMIS_HelpKillNpc = 0x63,
	kMIS_SwitchStashPage = 0x6d,
	kMIS_SwitchStashPageIdxChange = 0x6e,
	kMIS_BagToStash = 0x79,
	kMIS_StashToBag = 0x7a,
#elif VER_GJ_
	kMIS_FirstPacket = 0x1,			//������ܶ�������ᷢ��������Ʒ��ʹ�ü���֮��ģ��������ܹ���ס�ϴεķ��������ɣ�������
	kMIS_EnterMapConnection,
	kMIS_EnterMap,					//�л���ͼ��ʱ���ȷ�������ٷ������Ǹ����������ŷ��͵ġ���������ȱһ���ɡ�
	kMIS_OperCommand = 0x8,			//�������������ݻ���Ʒ�ᷢ�����
	kMIS_CreateRole = 0x0c,			//�Ѹ���
	kMIS_HeartBeat = 0xf,			//δ���£�����Ҫ����
	kMIS_OpenObject = 0x12,
	kMIS_UseSkill = 0x13,
	kMIS_SkillUsing = 0x13,			//���ʷ�û�����
	kMIS_UseSkillEnd = 0x13,		//���ʷ�û�����
	kMIS_TakeupItem = 0x16,
	kMIS_ThrowItem = 0x17,
	kMIS_PutdownItem = 0x18,
	kMIS_TakeoffGem = 0x19,
	kMIS_InsideGem = 0x1a,
	kMIS_LvlUpGem,
	kMIS_LvlUpPassiveSkill = 0x1d,		//������棬��UIʵ�ֺ��鷳�ġ�
	kMIS_MergeItem = 0x25,
	kMIS_WayPoint = 0x28,
	kMIS_Revive = 0x2b,
	kMIS_UseItem = 0x2d,
	kMIS_UseFlask = 0x31,
	kMIS_UseItemTo = 0x32,
	kMIS_SplitItem = 0x3a,
	kMIS_ChangedMapFirstPackage = 0x3b,
	kMIS_NpcTalkItem = 0x40,
	kMIS_CloseNpc = 0x42,
	kMIS_NpcInventoryItemPutToSelfInventory = 0x44,
	kMIS_BuyItem_ToBag = 0x46,
	kMIS_InstanceManager = 0x5a,	//new fb
	kMIS_Sell_Cancle = 0x5c,
	kMIS_PutItemToShop = 0x5d,
	kMIS_PutbackItemFromShop = 0x5e,
	kMIS_Sell_Accept,
	kMIS_UknItemOper = 0xb7,			//δ���£�����Ҫ����
	kMIS_HelpKillNpc = 0x65,
	kMIS_SwitchStashPage = 0x6b,
	kMIS_SwitchStashPageIdxChange = 0x70,
	kMIS_BagToStash = 0x7b,
	kMIS_StashToBag = 0x7c,
	//kMIS_
#else
	kMIS_FirstPacket = 0x1,			//������ܶ�������ᷢ��������Ʒ��ʹ�ü���֮��ģ��������ܹ���ס�ϴεķ��������ɣ�������
	kMIS_EnterMapConnection,
	kMIS_EnterMap,					//�л���ͼ��ʱ���ȷ�������ٷ������Ǹ����������ŷ��͵ġ���������ȱһ���ɡ�
	kMIS_OperCommand = 0xb,			//�������������ݻ���Ʒ�ᷢ�����
	kMIS_CreateRole = 0x0c,
	kMIS_HeartBeat = 0xf,
	kMIS_OpenObject = 0x16,
	kMIS_UseSkill = 0x17,
	kMIS_SkillUsing = 0x17,
	kMIS_UseSkillEnd = 0x17,
	kMIS_TakeupItem = 0x19,
	kMIS_ThrowItem = 0x1a,
	kMIS_PutdownItem = 0x1b,
	kMIS_TakeoffGem = 0x1c,
	kMIS_InsideGem = 0x1d,
	kMIS_LvlUpGem,
	kMIS_LvlUpPassiveSkill = 0x22,		//������棬��UIʵ�ֺ��鷳�ġ�
	kMIS_MergeItem = 0x28,
	kMIS_WayPoint = 0x2b,
	kMIS_UseItem = 0x30,
	kMIS_UseFlask = 0x34,
	kMIS_UseItemTo = 0x35,
	kMIS_SplitItem = 0x3d,
	kMIS_ChangedMapFirstPackage = 0x3b,
	kMIS_NpcTalkItem = 0x40,
	kMIS_CloseNpc = 0x45,
	kMIS_NpcInventoryItemPutToSelfInventory = 0x47,
	kMIS_BuyItem_ToBag = 0x46,
	kMIS_InstanceManager = 0x5a,	//new fb
	kMIS_Sell_Cancle = 0x5c,
	kMIS_PutItemToShop = 0x60,
	kMIS_PutbackItemFromShop = 0x61,
	kMIS_Sell_Accept,
	kMIS_SwitchStashPage = 0x6e,
	kMIS_UknItemOper = 0xb7,
	kMIS_Revive = 0x12b,
	kMIS_HelpKillNpc = 0x65,
	kMIS_SwitchStashPageIdxChange = 0x70,
	kMIS_BagToStash = 0x7b,
	kMIS_StashToBag = 0x7c,
#endif
};

enum CDS_enOperCommandSubMsgId : pt_byte{
	kOCSMID_DestroyItem = 9,
};
//////////////////////////////////////////////////////////////////////////
template<pt_word MsgId>
struct stCDS_CheckAny : stCDS_MsgBase<MsgId, 0, false>{
	template<class Archive>
	bool CheckRead(Archive & ar){
		ar.IgnoreAll();
		return true;
	}
};
//////////////////////////////////////////////////////////////////////////
struct stCDS_CreateRole : stCDS_MsgBase<kMIS_CreateRole, 1>{
	stCDS_CreateRole();
	template<class Archive>
	void serialize(Archive & ar) const{
		ar & role_name_
			& area_name_
			& ukn_zero_
			& ukn_stack_addr_
			& str_name_
			& all_zero_;
	}

	pt_cwsz		role_name_;
	pt_cwsz		area_name_;
	pt_dword	ukn_zero_;					//=0
	pt_dword	ukn_stack_addr_;			//���ﾹȻ�Ƕ�ջ�ĵ�ַ
	pt_cwsz		str_name_;		//StrDexIntDefault
	pt_byte		all_zero_[0x20];
};

//������Ĵ�С���̶�����ʱ��࣬��ʱ���٣��������������ص������Զ϶�ã��Ͷ���������ˡ�
struct stCDS_FirstPacket : stCDS_MsgBase<kMIS_FirstPacket>{

};

struct stCDS_EnterMapConnection : stCDS_CheckAny<kMIS_EnterMapConnection>{
	template<class Archive>
	bool CheckRead(Archive & ar){
		//assert(!"��������ᵥ�����͵İɣ�");
		ar.IgnoreAll();
		return true;
	}
};

struct stCDS_EnterMap : stCDS_MsgBase<kMIS_EnterMap, 0, false>{
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(ukn_dw_))
			return false;
		//LOG_O(Log_trace) << "msg, stCDS_EnterMap, ukn_dw_:" << (pt_pcvoid)ukn_dw_;
		return true;
	}

	enCD_EnterMapUknId		ukn_dw_;
};

//�ݻ���ƷҲ�������
struct stCDS_OperCommand : stCDS_MsgBase<kMIS_OperCommand>{
	stCDS_OperCommand();
	template<class Archive>
	void serialize(Archive & ar) const{
		if (sub_msg_id_ == kOCSMID_DestroyItem)
		{
			assert(0 == ukn_w_);
			ar & sub_msg_id_ & ukn_w_;
		}
		else
			assert(false);
	}

	CDS_enOperCommandSubMsgId		sub_msg_id_;

private:
	pt_word			ukn_w_;			//һֱ=0
};

//������Ĵ�С�ǹ̶��ģ���һ���ֶ�
struct stCDS_Heartbeat : stCDS_MsgBase<kMIS_HeartBeat>{
	pt_dword		ukn_dw_;		//һֱ����0��������������������μ���
};

/*
�������ֻ���һ�£���ô�ȷ�0xcb���ٷ�0xcf��ֻ����������
������갴�²��ţ��ȷ�0xcb��һֱ��0xcd���ɿ���귢0xcf��
*/
//��·Ҳ�ᷢ���������һ���������ط���
struct stCDS_UseSkill : stCDS_MsgBase<kMIS_UseSkill>{
	stCDS_UseSkill();
	template<class Archive>
	void serialize(Archive & ar) const{
		ar & dst_pos_ & skill_id_ 
			& skill_use_cnt_
			& ukn_flag_;
	}
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(dst_pos_))
			return false;
		if (!ar.Read(skill_id_))
			return false;
		if (!ar.Read(skill_use_cnt_))
			return false;
		if (!ar.Read(ukn_flag_))
			return false;
		if (ukn_flag_ != kTTSF_Normal)
		{
			assert(false);
			//ukn_flag_ = kTTSF_Normal;
			return false;
		}
		//LOG_O(Log_trace) << "UseSkill,skillId:" << (pt_pcvoid)skill_id_ << ",dstPos:" << dst_pos_ << ",SkillCnt:" << skill_use_cnt_ << ",flag:" << ukn_flag_;
		return ar.empty();
	}
	
	stCD_VecInt	dst_pos_;
	/*
	0x2909		��·ʱ
	*/
	pt_word		skill_id_;			//0x8401�������Ǽ���ID
	pt_word		skill_use_cnt_;		//����ʹ�ô���

private:
	enCD_TouchTargetSmallFlag	ukn_flag_;			//�Ǹ���־��һֱ=0x8�� OR BL, 0x8
};
static_assert(sizeof(stCDS_UseSkill) == 0xf, "");

//ʹ��֮�ڶ�������
struct stCDS_SkillUsing : stCDS_MsgBase<kMIS_SkillUsing>{
	stCD_VecInt		dst_pos_;

	template<class Archive>
	void serialize(Archive & ar) const{
		ar & dst_pos_;
	}
};

//ʹ�ü��ܽ���
struct stCDS_UseSkillEnd : stCDS_MsgBase<kMIS_UseSkillEnd>{
	template<class Archive>
	void serialize(Archive & ar) const{}
};

struct stCDGS_TakeupItem : stCD_GameMsgBase{
	enCD_InventoryType		inventory_type_;
	pt_dword				item_id_;
	enCD_SendItemOperFlag	ukn_flag_;
};
static_assert(0x10 == offsetof(stCDGS_TakeupItem, ukn_flag_), "");
//������Ʒ
struct stCDS_TakeupItem : stCDS_MsgBase<kMIS_TakeupItem>{
	stCDS_TakeupItem();
	template<class Archive>
	void serialize(Archive & ar) const{
		ar & CD_Encrypt<CD_TagEncrypt1>(inventory_type_) & item_id_ & CD_Encrypt<CD_TagEncrypt1>(ukn_flag_);
	}
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(inventory_type_))
			return false;
		if (!ar.Read(item_id_))
			return false;
		if (!ar.Read(ukn_flag_))
			return false;
		return ar.empty();
	}

	enCD_InventoryType		inventory_type_;		//��Ʒ���ڱ�������
	pt_dword				item_id_;				//ÿ����һ�ξͼ�2

private:
	enCD_SendItemOperFlag	ukn_flag_;				//һֱ����0
};

//����Ʒ������
struct stCDS_ThrowItem : stCDS_MsgBase<kMIS_ThrowItem>{
	template<class Archive>
	void serialize(Archive & ar) const{}
};

//������Ʒ
/*���Ƿ��µ�Ŀ��λ������Ʒb���������Ʒ��Ȼ��������Ʒb*/
struct stCDS_PutdownItem : stCDS_MsgBase<kMIS_PutdownItem>{
	stCDS_PutdownItem();
	template<class Archive>
	void serialize(Archive & ar) const{
		ar & dst_inventory_type_ & dst_left_top_idx_ & ukn_bool_;
	}
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(dst_inventory_type_))
			return false;
		if (!ar.Read(dst_left_top_idx_))
			return false;
		if (!ar.Read(ukn_bool_))
			return false;
		if ((int)ukn_bool_ != 0)
		{
			assert(false);
			return false;
		}
		return ar.empty();
	}

	enCD_InventoryType		dst_inventory_type_;	//��ƷҪ�ŵ�Ŀ��inventory_type
	stCD_VecInt				dst_left_top_idx_;		//Ҫ�ŵ������ϵ�λ�ã�����0��ʼ����

private:
	pt_bool					ukn_bool_;				//һֱ����0
};

template<pt_word MsgId>
struct stCDS_Takeoff_InsideGem : stCDS_MsgBase<MsgId>{
	stCDS_Takeoff_InsideGem(){
		CD_ZERO_MSGS();
	}
	template<class Archive>
	void serialize(Archive & ar) const{
		ar & inventory_type_ & equip_item_id_ & slot_idx_;
	}
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(inventory_type_))
			return false;
		if (!ar.Read(equip_item_id_))
			return false;
		if (!ar.Read(slot_idx_))
			return false;
		return ar.empty();
	}

	enCD_InventoryType	inventory_type_;	//װ������inventory_type
	pt_dword			equip_item_id_;
	pt_dword			slot_idx_;			//�ڼ����ۣ���0��ʼ
};

//ȡ����ʯ
struct stCDS_TakeoffGem : stCDS_Takeoff_InsideGem<kMIS_TakeoffGem>{};

//��Ƕ��ʯ
struct stCDS_InsideGem : stCDS_Takeoff_InsideGem<kMIS_InsideGem>{};

struct stCDS_LvlUpGem : stCDS_MsgBase<kMIS_LvlUpGem>{
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(inventory_type_))
			return false;
		if (!ar.Read(item_id_))
			return false;
		if (!ar.Read(gem_idx_))
			return false;
		return ar.empty();
	}

	enCD_InventoryType		inventory_type_;
	pt_dword				item_id_;
	pt_dword				gem_idx_;		//slot_idx
};

//�����츳
struct stCDS_LvlUpPassiveSkill : stCDS_MsgBase<kMIS_LvlUpPassiveSkill>{
	stCDS_LvlUpPassiveSkill();
	template<class Archive>
	void serialize(Archive & ar) const{
		ar & skill_id_;
	}
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(skill_id_))
			return false;
		return ar.empty();
	}

	pt_dword		skill_id_;
};

struct stCDS_Revive : stCDS_MsgBase<kMIS_Revive>{
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(revive_mode_))
			return false;
		return ar.empty();
	}

	pt_byte		revive_mode_;		//����ģʽ
};

//ʹ����Ʒ��ֻ��ͨ���Ҽ���꼴��ʹ����Ʒ
struct stCDS_UseItem : stCDS_MsgBase<kMIS_UseItem>{
	stCDS_UseItem();
	template<class Archive>
	void serialize(Archive & ar) const{
		ar & inventory_type_ & item_id_;
	}
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(inventory_type_))
			return false;
		if (!ar.Read(item_id_))
			return false;
		return ar.empty();
	}

	enCD_InventoryType		inventory_type_;
	pt_dword				item_id_;
};

//ʹ��ҩ����ʹ��ƿ��
struct stCDS_UseFlask : stCDS_MsgBase<kMIS_UseFlask>{
	stCDS_UseFlask();
	template<class Archive>
	void serialize(Archive & ar) const{
		ar & item_idx_;
	}
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(item_idx_))
			return false;
		return ar.empty();
	}

	pt_dword		item_idx_;			//��Ʒ��inventory����������0��ʼ
};

//ʹ�ø���Ʒ��������һ����Ʒ���������
struct stCDS_UseItemTo : stCDS_MsgBase<kMIS_UseItemTo>{
	stCDS_UseItemTo();
	template<class Archive>
	void serialize(Archive & ar) const{
		ar & inventory_type_src_ & item_id_src_ & inventory_type_dst_ & item_id_dst_;
	}
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(inventory_type_src_))
			return false;
		if (!ar.Read(item_id_src_))
			return false;
		if (!ar.Read(inventory_type_dst_))
			return false;
		if (!ar.Read(item_id_dst_))
			return false;
		return ar.empty();
	}

	enCD_InventoryType		inventory_type_src_;
	pt_dword				item_id_src_;
	enCD_InventoryType		inventory_type_dst_;
	pt_dword				item_id_dst_;
};

struct stCDS_MergeItem : stCDS_MsgBase<kMIS_MergeItem>{
	stCDS_MergeItem();
	template<class Archive>
	void serialize(Archive & ar) const{
		ar & CD_Encrypt<CD_TagEncrypt2>(dst_inventory_type_) & dst_item_id_ & CD_Encrypt<CD_TagEncrypt2>(ukn_flag_);
	}

	enCD_InventoryType		dst_inventory_type_;		//���ϲ���Ʒ��Ŀ������
	pt_dword				dst_item_id_;

private:
	enCD_SendItemOperFlag	ukn_flag_;
};

struct stCDS_SplitItem : stCDS_MsgBase<kMIS_SplitItem>{};

//����Ʒ�ŵ��̵���Ʒ��
struct stCDS_PutItemToShop : stCDS_MsgBase<kMIS_PutItemToShop>{
	stCDS_PutItemToShop();
	template<class Archive>
	void serialize(Archive & ar) const{
		ar & item_inventory_type_ & item_id_ & dst_pos_;
	}
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(item_inventory_type_))
			return false;
		if (!ar.Read(item_id_))
			return false;
		if (!ar.Read(dst_pos_))
			return false;
		return ar.empty();
	}

	enCD_InventoryType		item_inventory_type_;	//��Ʒ����inventory_type
	pt_dword				item_id_;
	stCD_VecByte			dst_pos_;				//��0��ʼ
};

//�����ò���ò��������ԾͲ�������
//����ŵ��̵���Ʒ������Ʒ�Żص���ı���
struct stCDS_PutbackItemFromShop : stCDS_MsgBase<kMIS_PutbackItemFromShop>{
	stCDS_PutbackItemFromShop();
};

struct stCDS_Sell_Accept : stCDS_MsgBase<kMIS_Sell_Accept>{
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(sell_id_))
			return false;
		return ar.empty();
	}

	pt_dword		sell_id_;
};

struct stCDS_InstanceManager : stCDS_MsgBase<kMIS_InstanceManager>{
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(instance_idx_))
			return false;
		return ar.empty();
	}

	pt_byte			instance_idx_;		//��0��ʼ����ͼʵ��������
};

struct stCDS_Sell_Cancle : stCDS_MsgBase<kMIS_Sell_Cancle>{
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(ukn_dw_))
			return false;
		if (!ar.Read(ukn_by_))
			return false;
		if (ukn_dw_ != 0)
		{
			assert(false);
			return false;
		}
		if (ukn_by_ != 0)
		{
			assert(false);
			return false;
		}
		return ar.empty();
	}

	pt_dword		ukn_dw_;		//=0
	pt_byte			ukn_by_;		//=0;
};

struct stCDS_HelpKillNpc : stCDS_MsgBase<kMIS_HelpKillNpc>{
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(is_help_))
			return false;
		return ar.empty();
	}

	bool		is_help_;		//1=help,0=kill
};

struct stCDS_SwitchStashPage : stCDS_MsgBase<kMIS_SwitchStashPage>{
	stCDS_SwitchStashPage();
	template<class Archive>
	void serialize(Archive & ar) const{
		ar & tab_idx_ & ukn_byte_;
	}
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(tab_idx_))
			return false;
		if (!ar.Read(ukn_byte_))
			return false;
		if (ukn_byte_ != 0)
		{
			assert(false);
			return false;
		}
		return ar.empty();
	}

	pt_word			tab_idx_;
	pt_byte			ukn_byte_;	//=0
};

//����ѡ����������������Ʒ
struct stCDS_NpcInventoryItemPutToSelfInventory : stCDS_MsgBase<kMIS_NpcInventoryItemPutToSelfInventory>{
	stCDS_NpcInventoryItemPutToSelfInventory();
	template<class Archive>
	void serialize(Archive & ar) const{
		ar & item_id_ & dst_inventory_type_& dst_pos_ & tbl_idx_ & ukn_byte1_;
	}
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(item_id_))
			return false;
		if (!ar.Read(dst_inventory_type_))
			return false;
		if (!ar.Read(dst_pos_))
			return false;
		if (!ar.Read(tbl_idx_))
			return false;
		if (!ar.Read(ukn_byte1_))
			return false;
		if (ukn_byte1_ != 0)
		{
			assert(false);
			return false;
		}
		return ar.empty();
	}

	pt_dword			item_id_;
	enCD_InventoryType	dst_inventory_type_;		//Ҫ�����ĸ�inventory_type
	stCD_VecInt			dst_pos_;

	//������Ʒ��ѡ���������������ֵ����һ����
private:
	pt_byte				tbl_idx_;			//table_page���������ǵڼ���ҳ�棬������0��ʼ
	pt_byte				ukn_byte1_;			//0
};

struct stCDS_BuyItem_ToBag : stCDS_MsgBase<kMIS_BuyItem_ToBag>{
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(item_id_))
			return false;
		if (!ar.Read(tbl_idx_))
			return false;
		if (!ar.Read(ukn_byte1_))
			return false;
		if (ukn_byte1_ != 0)
		{
			assert(false);
			return false;
		}
		return ar.empty();
	}

	pt_dword		item_id_;
	pt_byte			tbl_idx_;			//table_page���������ǵڼ���ҳ�棬������0��ʼ
	pt_byte			ukn_byte1_;			//0
};
//////////////////////////////////////////////////////////////////////////
//*********************�������
//������npc�����ã��õ�����Ϸ�еĺ�����һ��������Ͷ��ߡ�
//��npc
struct stCDS_OpenObject : stCDS_MsgBase<kMIS_OpenObject>{
	stCDS_OpenObject();
	template<class Archive>
	void serialize(Archive & ar) const{
		ar & dst_obj_id_ & skill_id_
//#ifdef VER_GJ_
			& skill_use_cnt_
//#endif
			& ukn_byte_;
	}
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(dst_obj_id_))
			return false;
		if (!ar.Read(skill_id_))
			return false;
//#ifdef VER_GJ_
		if (!ar.Read(skill_use_cnt_))
			return false;
//#endif
		if (!ar.Read(ukn_byte_))
			return false;
		if (ukn_byte_ != kTTSF_Normal
			&& ukn_byte_ != kTTSF_WithLeftCtrl)
		{
			assert(false);
			return false;
		}
		return ar.empty();
	}

	pt_dword					dst_obj_id_;
	enCD_SkillId				skill_id_;		//һֱ����0x266
//#ifdef VER_GJ_
	pt_word						skill_use_cnt_;	//����ʹ�ô���
//#endif

private:
	enCD_TouchTargetSmallFlag	ukn_byte_;		//һֱ����0x8
};
static_assert(std::is_enum<enCD_SkillId>::value, "");
static_assert(std::is_enum<enCD_TouchTargetSmallFlag>::value, "");
static_assert(sizeof(enCD_SkillId) == 2, "");
static_assert(sizeof(enCD_TouchTargetSmallFlag) == 1, "");

struct stCDS_ChangeMapFirstPacket : stCDS_MsgBase<kMIS_ChangedMapFirstPackage>{
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(instance_id1_))
			return false;
		if (!ar.Read(instance_id2_))
			return false;
		return ar.empty();
	}

	//������½�һ����ͼʵ�������ͬһ����ͼ������������ֵ�����䣬�²��ǵ�ͼʵ����ID�ɡ�
	pt_dword		instance_id1_;
	pt_dword		instance_id2_;
};

struct stCDS_NpcTalkItem : stCDS_MsgBase<kMIS_NpcTalkItem>{
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(talk_idx_))
			return false;
		return ar.empty();
	}

	pt_byte			talk_idx_;
};

//�ر�npc���������á�
//�ر�npc��ֻ����ϢID��û����Ϣ����
struct stCDS_CloseNpc : stCDS_MsgBase<kMIS_CloseNpc>{
	template<class Archive>
	void serialize(Archive & ar) const{}
	template<class Archive>
	bool CheckRead(Archive & ar){
		return ar.empty();
	}
};

struct stCDS_Waypoint : stCDS_MsgBase<kMIS_WayPoint>{
	stCDS_Waypoint();
	template<class Archive>
	void serialize(Archive & ar) const{
		ar & world_area_id_ & connections_num_ & ukn_byte_;
	}
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(world_area_id_))
			return false;
		if (!ar.Read(connections_num_))
			return false;
		if (!ar.Read(ukn_byte_))
			return false;
		if (int(ukn_byte_) != 0)
		{
			assert(false);
			return false;
		}
		return ar.empty();
	}

	pt_dword			world_area_id_;		//=7ad2,3275,235c
	pt_dword			connections_num_;	//0x42		,2bd

private:
	pt_byte				ukn_byte_;			//=0
};

template<pt_word MsgId>
struct stCDS_BagToStashBase : stCDS_MsgBase<MsgId>{
	stCDS_BagToStashBase(){
		CD_ZERO_MSGS();
	}
	template<class Archive>
	bool CheckRead(Archive & ar){
		if (!ar.Read(ukn_w_))
			return false;
		if (!ar.Read(item_id_))
			return false;
		if (!ar.Read(ukn_b_))
			return false;
		if (int(ukn_b_) != 0)
		{
			assert(false);
			return false;
		}
		return ar.empty();
	}

	pt_word				ukn_w_;
	pt_dword			item_id_;
	pt_byte				ukn_b_;
};
struct stCDS_BagToStash : stCDS_BagToStashBase<kMIS_BagToStash>{};
struct stCDS_StashToBag : stCDS_BagToStashBase<kMIS_StashToBag>{};
//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)
