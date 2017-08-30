#pragma once
/*
@author zhp
@date 2017/1/24 17:22
*/
#include <ProtocolX/P_DefinesX.h>
#include <ProtocolX/P_DefinesX.h>
#include <cstddef>
#include "CD_Vtbl.h"
#include <array>
#include <string>
#include "CD_Serialize.hpp"
#include "CD_Data.h"
#include "CD_StructBase.h"
#include <WgFacility/CmnFilter.h>
#include <StdEx/XstddefEx.h>
#include <CommonX/CmnX_StaticConts.h>

#pragma pack(push)
#pragma pack(1)
//////////////////////////////////////////////////////////////////////////
#ifdef VER3_
pt_cdword	g_so_brach_quest_state_size_ = 0x80;			//�����С�ǲ²�ģ�ȥ��tag_����ID�ж�����״̬
typedef GameBitsetTraits<g_so_brach_quest_state_size_/*0x80*/> BranchStateContT;
pt_cdword	g_so_brach_quest_state_total_size_ = sizeof(BranchStateContT);
pt_cdword	g_so_player_brach_state_ = 0x4c;
#else
pt_cdword	g_so_player_brach_state_ = (1 << CD_DATA(g_v_branch_quest_shl_deta_)) + CD_DATA(g_v_branch_quest_delta_offset_);
pt_cdword	g_so_brach_quest_state_size_ = 1 << CD_DATA(g_v_branch_quest_shl_deta_);
typedef GameBitsetTraits<g_so_brach_quest_state_size_/*0x80*/> BranchStateContT;
pt_cdword	g_so_brach_quest_state_total_size_ = sizeof(BranchStateContT) * kMD_Merciless;
#endif
//////////////////////////////////////////////////////////////////////////
struct stCD_SceneInGameState;
struct stCD_AttrDbSkillGem;
struct stCD_Player;
struct stCD_World;
struct stCD_ScenePreGameState;
struct stCD_UiObjBase;
struct stCD_WaypointPointItem;
struct stCD_DlgWaypointMap;
struct stCD_SceneEscapeState;
struct stCD_UiNpcPanelMenuItem;
struct stCD_SceneBase;
struct stCD_StateUiLogic;
struct stCD_DlgWaypointChapterContent;
typedef GameVector<enCD_MapDataFlag> stCD_MapDataVector;
struct stCD_UiPreInGameTop;
struct stCD_SceneCreateCharacterState;
struct stCD_SceneSelectCharacterState;
struct stCD_UiEdit;
struct stCD_UiCreateRole_Character;
struct stCD_SceneLoginState;
struct stCD_SkillObj;
struct stCD_UiButton;
struct stCD_UiSelectRoleTop;
//////////////////////////////////////////////////////////////////////////
struct stCD_Encryptor{
	pt_char Encrypt(const pt_char& v, CD_TagEncrypt1) const;
	pt_int Encrypt(const pt_int& v, CD_TagEncrypt1) const;
	pt_char Encrypt(const pt_char& v, CD_TagEncrypt2) const;
	pt_int Encrypt(const pt_int& v, CD_TagEncrypt2) const;
};

//session���������հ����������
struct stCD_Socket{
	typedef GameVector<pt_byte> BufferCont;

	SOCKET			handle_send_;
	p_mem_placeholder(g_so_send_packet_encrypt_ - sizeof(SOCKET));
	stCD_Encryptor*	encryptor_;
	p_mem_placeholder(g_so_send_packet_msg_total_len_ - g_so_send_packet_encrypt_ - 4);
	pt_dword		send_msg_total_len_;
	pt_dword		send_msg_offset_;
	pt_dword		recv_total_len_;			//�յ������а����ܳ��ȡ�ÿ��ע������գ����������˻���ա�
	pt_dword		recv_unserialized_packet_len_;	//δ���л��İ�����
	pt_dword		recv_msg_len_;					//��ǰ��Ϣ����
	//p_mem_placeholder(g_so_send_packet_msg_data_ - 0xc - g_so_send_packet_msg_total_len_);
	BufferCont		send_msg_data_;
	BufferCont		recv_org_buffer_;				//���ܺ����ݣ���δ����ntohs��ntohl�Ⱥ���ת����

	enCD_SocketType GetSocketType() const;
	//////////////////////////////////////////////////////////////////////////
	stCD_Encryptor* GetEncryptor() const;
	pt_dword GetSendMsgSize() const;
	pt_pcvoid GetSendMsgData() const;
	const stCD_Socket& BuildPacket(pt_pcvoid data, pt_dword size) const;
	pt_dword DoSendPacket(pt_dword encrypt_value) const;		//is_encrypt==0ֱ�ӷ��ͣ������ܣ�is_encrypt==1���ܺ��ٷ��͡����ǲµġ�
	template<typename T>
	bool Send(const T& msg) const{
		CD_SerializeS<const stCD_Socket> serialize(*this);
		if (!serialize.DoSend(msg))
		{
			assert(false);
			return false;
		}
		return true;
	}
	void ClearSendingBuffer();
	//////////////////////////////////////////////////////////////////////////
	//�õ���ǰ�հ�����
	pt_pcvoid GetRecvOrgData() const;
	//��������ǵõ��ϴ��հ�����
	pt_pcvoid GetLastRecvOrgData() const;
	//��������ȥ��ȡ����Ϊ��������
	pt_int DecryptGetInt() const;
};
static_assert(g_so_send_packet_encrypt_ == offsetof(stCD_Socket, encryptor_), "");
static_assert(g_so_send_packet_msg_total_len_ == offsetof(stCD_Socket, send_msg_total_len_), "");
static_assert(g_so_send_packet_msg_data_ == offsetof(stCD_Socket, send_msg_data_), "");

struct stCD_SocketsMgr{
	typedef GameVector<pt_pcvoid> EventCont;

	p_mem_placeholder(g_so_recv_packet_mgr_obj_cont_);
	EventCont			ukn_cont_;
};
static_assert(g_so_recv_packet_mgr_obj_cont_ == offsetof(stCD_SocketsMgr, ukn_cont_), "");

struct stCD_LoginLogic{
	p_mem_placeholder(g_so_login_session_packet_);
	stCD_Socket*	send_packet_;
};
static_assert(g_so_login_session_packet_ == offsetof(stCD_LoginLogic, send_packet_), "");
//////////////////////////////////////////////////////////////////////////
struct stCD_UiObjCont{
	typedef GameVector<stCD_UiObjBase*> SubUiCont;

	pt_pcvoid		ukn_ptr_;
	SubUiCont		sub_ui_cont_;
	SubUiCont		ukn_vector_;
};

struct stCD_UiNextStateContent{
	pt_pcvoid				vtbl_;			//�е�Ϊ0���е�Ϊvtbl
	stCD_SceneBase*			scene_state_;	//�е�Ϊ0���е�ָ��ǰ״̬
	p_mem_placeholder(g_so_ui_next_state_info_size_ - 4 * 4);
};

struct stCD_UiNextStateInfoBase{
	pt_dword					ukn_;			//һֱ����0
	stCD_UiNextStateContent*	content_ptr_;

	stCD_UiNextStateInfoBase(stCD_UiNextStateContent* content) : content_ptr_(content){}
};

struct stCD_UiNextStateInfo : stCD_UiNextStateInfoBase{
	stCD_UiNextStateInfo() : stCD_UiNextStateInfoBase(&content_){}

	stCD_UiNextStateContent		content_;
};
static_assert(g_so_ui_next_state_info_size_ == sizeof(stCD_UiNextStateInfo), "");

//����ṹ��Ĵ�СӦ����0x83c
struct stCD_UiObjBase{
	typedef std::function<bool(stCD_UiObjBase*)> Fn_TraSubUiObj;
	//��Ϸ�в�û�������
	class UiFilterBase{
	public:
		virtual bool Filter(const stCD_UiObjBase& ui) const = 0;
	};

	stCD_UiObjVtbl*			vtbl_;
	stCD_UiNextStateInfo	next_state_info_[CD_kUiNextStateInfoMax];
	stCD_UiObjCont			sub_uis_;
	p_mem_placeholder(CD_DATA(g_o_ui_obj_base_is_shown_) - g_so_ui_obj_base_sub_uis_ - sizeof(stCD_UiObjCont));
	bool					is_shown_;		//�Ƿ���ʾ
	bool					ukn_bool_;		//ͨ��Ϊfalse
	bool					is_enable_;		//����ǰ�ť��=false���򲻿ɵ�������ǻ�ɫ�ġ�
	p_mem_placeholder(1);			//����
#ifdef VER3_
	pt_pcvoid				ukn_obj_vtbl_;
	p_mem_placeholder(4 * 5);
#endif
	stCD_StateUiLogic*		ui_logic_;
	stCD_UiObjBase*			parent_;
	pt_pcvoid				ukn_ptr1_;		//�е�Ϊ�գ��еĲ�Ϊ��

	//////////////////////////////////////////////////////////////////////////
	stCD_UiObjBase* Parent() const;
	stCD_UiObjBase* Parent(int lvl) const;
	stCD_StateUiLogic* GetUiLogic() const;
	void Show(bool is_show) const;
	int GetSubUiCount() const;
	//////////////////////////////////////////////////////////////////////////
	//�������
	bool IsPropPanel() const;
	//�ֿ����
	bool IsStashPanel() const;
	//�츳�����
	bool IsPassiveSkillPanel() const;
	//���͵���塣���͵���弴�����ͼ���
	bool IsWaypointPanel() const;
	//������
	bool IsQuestAward() const;
	//������������������Ҳ���������������Ի�������Ǹ��ʺ�
	bool IsDlgGuide() const;
	//����Ի���
	bool IsDlgBuy() const;
	//�����Ի��Ի���
	bool IsDlgSell() const;
	//��ͼ������
	bool IsDlgMapLocator() const;
	//////////////////////////////////////////////////////////////////////////
	bool SameShowState(enCD_TraUiShownFlag show_flag) const;
	int TraSubUiObj(int sub_lvl, const UiFilterBase& filter, enCD_TraUiShownFlag show_flag, const Fn_TraSubUiObj& fn) const;
	int TraSubUiObjEx(int sub_lvl, pt_pcvoid addr, enCD_TraUiFilterType filter_type, enCD_TraUiShownFlag show_flag, const Fn_TraSubUiObj& fn) const;
	int TraAllSubUiObj(const UiFilterBase& filter, enCD_TraUiShownFlag show_flag, const Fn_TraSubUiObj& fn) const;
	stCD_UiObjBase* FindSubUiObj(int sub_lvl, const UiFilterBase& filter, enCD_TraUiShownFlag show_flag, int the_cnt) const;
	stCD_UiObjBase* FindSubUiObjByVtbl(int sub_lvl, pt_pcvoid vtbl, enCD_TraUiShownFlag show_flag, int the_cnt) const;
	//////////////////////////////////////////////////////////////////////////
	void DebugInfo() const;
	void DebugFullInfo(enCD_TraUiShownFlag show_flag) const;
	void DebugParentsInfo() const;
	CMN_CAST_TO

private:
	int TraAllSubUiObjImpl(const UiFilterBase& filter, enCD_TraUiShownFlag show_flag, const Fn_TraSubUiObj& fn) const;
};
static_assert(g_so_ui_obj_base_sub_uis_ == offsetof(stCD_UiObjBase, sub_uis_), "");
static_assert(CD_DATA(g_o_ui_obj_base_is_shown_) == offsetof(stCD_UiObjBase, is_shown_), "");

struct stCD_UiEventBase{
	stCD_UiEventVtbl*		vtbl_;
	CMN_CAST_TO
};

struct stCD_UiEvent : stCD_UiEventBase{
	stCD_UiObjBase*			ui_obj_;
	pt_pcvoid				fn_handle_ui_logic_;		//���������ui_obj_�ĳ�Ա������ע������ģ��¼���Ӧ����
	pt_dword				ui_obj_offset_;

	stCD_UiObjBase* GetUiObj() const;
};

struct stCD_UiEventMgr{
	typedef std::function<bool(stCD_UiObjBase*)> Fn_TraUiObjBase;

	pt_pcvoid				tmp_stack_ptr_;		//��ջ�ϵĵ�ַ
	stCD_UiEventBase*		first_obj_;

	template<typename T>
	T* FindUiObjByFn(pt_pcvoid holder_vfn, pt_pcvoid fn_ui_handle_logic) const{
		auto res = FindUiObjImpl(holder_vfn, fn_ui_handle_logic);
		if (!res) return nullptr;
		return res->CastTo<T>();
	}

protected:
	int TraUiObjImpl(pt_pcvoid holder_vfn, pt_pcvoid fn_ui_handle_logic, const Fn_TraUiObjBase& fn) const;
	stCD_UiObjBase* FindUiObjImpl(pt_pcvoid holder_vfn, pt_pcvoid fn_ui_handle_logic) const;
};

template<typename Getter>
struct stCD_UiEventMgrT : stCD_UiEventMgr{
	template<typename T>
	T* FindUiObjByFn(pt_pcvoid fn_ui_handle_logic) const{
		auto res = FindUiObjImpl((pt_pcvoid)Getter::get(), fn_ui_handle_logic);
		if (!res) return nullptr;
		return res->CastTo<T>();
	}
	template<typename T>
	int TraUiObj(pt_pcvoid fn_ui_handle_logic, const std::function<bool(T*)>& fn) const{
		return TraUiObjImpl((pt_pcvoid)Getter::get(), fn_ui_handle_logic, [&fn](stCD_UiObjBase* ui_obj){
			assert(ui_obj);
			return fn(ui_obj->CastTo<T>());
		});
	}
};

struct stCD_UiEventGetterAddr{
	static pt_dword get();
};
struct stCD_UiEventGetterAddr1{
	static pt_dword get();
};
typedef stCD_UiEventMgrT<stCD_UiEventGetterAddr> stCD_UiEventMgr_Ret8;
typedef stCD_UiEventMgrT<stCD_UiEventGetterAddr1> stCD_UiEventMgr_RetC;
//////////////////////////////////////////////////////////////////////////
struct stCD_SceneAbovePart{
	pt_pcvoid		vtbl_;
	pt_dword		flag_;		//�²���flag����Ϊ"SelectCharacterState"��"PreGameState"ʱ������4.
	pt_dword		id_;		//�²���id����Ϊ��һ��SelectCharacterState��1���ڶ���PreGameState��2.

	void DebugInfo() const;
};

struct stCD_SceneBase{
	pt_pcvoid		vtbl_;
	pt_pcvoid		flag_;		//�²���flag����Ϊ��һ��SelectCharacterState��0x2e000000���ڶ���PreGameState��0x00010101.
	GameWString		name_;		//�²���ui�����֡�
	
	CMN_CAST_TO
	template<typename T>
	const T* CastTo(const std::wstring& name) const{
		if (name != name_.c_str()) return nullptr;
		return static_cast<const T*>(this);
	}
	template<typename T>
	T* CastTo(const std::wstring& name){
		if (name != name_.c_str()) return nullptr;
		return static_cast<T*>(this);
	}
	void DebugInfo() const;
};

struct stCD_UknBase{
	stCD_UknBaseVtbl*	vtbl_;
};

struct stCD_SceneHolder : stCD_UknBase{
	//(char*)above_part_ + 0x14 = real_obj_
	typedef stCD_PairAdjacent<stCD_SceneBase, stCD_SceneAbovePart> PairSceneT;

	typedef std::function<bool(stCD_SceneBase*)> IterFnT;
	p_mem_placeholder(g_so_ukn_packet_holder2_ - sizeof(stCD_UknBase));
	GameVector<PairSceneT>		game_state_cont_;		//��Ϸ���Ƿ��������

	void TraverseState(const IterFnT& fn) const;
	stCD_SceneBase* GetStateByName(const std::wstring& state_name) const;
	stCD_SceneBase* GetTopState() const;
	bool TopStateSameName(const std::wstring& state_name) const;
	bool TopStateIsEscape() const;
	bool TopStateIsAreaLoading() const;
	stCD_ScenePreGameState* GetPreGameState() const;
	stCD_SceneInGameState* GetInGameState() const;
	stCD_SceneEscapeState* GetEscapeState() const;
	stCD_SceneCreateCharacterState* GetCreateCharacterState() const;
	stCD_SceneSelectCharacterState* GetSelectCharacterState() const;
	stCD_SceneLoginState* GetLoginState() const;
	stCD_Socket* GetSendPacket() const;
	stCD_Socket* GetInGameStateSocket() const;
	stCD_Socket* GetPreGameStateSocket() const;
	void DebugInfo() const;
};
static_assert(g_so_ukn_packet_holder2_ == offsetof(stCD_SceneHolder, game_state_cont_), "");
//////////////////////////////////////////////////////////////////////////
//***********************��Ʒ��������
struct stCD_BagAbovePart{
	pt_pcvoid		vtbl_;
	pt_dword		ukn1_;		//һֱ=2
	pt_dword		ukn2_;		//һֱ=1
	pt_pcvoid		ukn_ptr_;

	void DebugInfo() const;
};
static_assert(sizeof(stCD_BagAbovePart) == 0x10, "");

struct stCD_ItemGridsInfo{
	stCD_EntityItemBased*	item_entity_;
	stCD_ItemGridsIdxInfo	idx_info_;		//����ṹ����Ա����ʹ��
	pt_dword				item_id_;		//��Ʒid������id��������

	bool IsValid() const;
	void DebugInfo() const;
};

struct stCD_Inventory{
	typedef GameVector<stCD_ItemGridsInfo*> ItemContT;
	typedef std::function<bool(stCD_ItemGridsInfo*, stCD_EntityItemBased*)> Fn_TraItem;
	//װ������ʯ
	typedef std::function<bool(stCD_EntityItemBased*, stCD_EntityItemBased*)> Fn_TraEquipsInsideGem;
	//��ʯ
	typedef std::function<bool(stCD_EntityItemBased*)> Fn_TraSkillGem;
	//װ������ʯ������
	typedef std::function<bool(stCD_EntityItemBased*, stCD_EntityItemBased*, stCD_AttrDbSkillGem*)> Fn_TraGemSkill;

	pt_dword			ukn_flag_;
	pt_dword			ukn_flag1_;
	pt_dword			ukn_dw_;
	pt_dword			grid_width_;		//���ӿ�ȣ���ĸ�����
	pt_dword			grid_height_;		//���Ӹ߶ȣ��ߵĸ�����
	p_mem_placeholder(g_so_get_bag_ - g_so_bag_grid_width_ - 8);
	ItemContT			items_;
	pt_pcvoid			ukn_ptr_;
	pt_dword			item_cnt_;			//��Ʒ���������Ǹ�������Ŷ��

	stCD_EntityItemBased* FindItem(pt_dword item_id) const;
	int TraItems(const Fn_TraItem& fn) const;
	//�������ܱ�ʯ
	int TraSkillGems(const Fn_TraSkillGem& fn) const;
	//������Ƕ��װ����ļ��ܱ�ʯ
	int TraEquipsInsideGem(const Fn_TraEquipsInsideGem& fn) const;
	//������ʯ����
	int TraGemSkill(const Fn_TraGemSkill& fn, enCD_TraGemSkillFlag flag) const;
	stCD_EntityItemBased* GetFirstItem() const;
	void DebugInfo(bool is_debug_items) const;
	CMN_CAST_TO
};
static_assert(g_so_bag_grid_width_ == offsetof(stCD_Inventory, grid_width_), "");
static_assert(g_so_get_bag_ == offsetof(stCD_Inventory, items_), "");
static_assert(g_so_bag_item_cnt_ == offsetof(stCD_Inventory, item_cnt_), "");

struct stCD_InventoryCate{
	typedef stCD_PairAdjacent<stCD_Inventory, stCD_BagAbovePart> BagPairT;

	enCD_InventoryType	bag_type_;
	BagPairT			bag_info_;
	pt_dword			flag_;			//�²���flag

	void DebugInfo() const;
};
static_assert(sizeof(stCD_InventoryCate) == 0x10, "");

struct stCD_InventoryMgr{
	typedef stCD_Inventory::Fn_TraItem Fn_TraItem;
	typedef stCD_Inventory::Fn_TraEquipsInsideGem Fn_TraEquipsInsideGem;
	typedef stCD_Inventory::Fn_TraGemSkill Fn_TraGemSkill;
	typedef std::function<bool(enCD_InventoryType, stCD_Inventory*)> Fn_TraInventory;
	typedef CF_Value<true, enCD_InventoryType, kIT_Max, kIT_Invalid> FilterInventoryType;

	/*pt_bool							ukn_b_;
	p_mem_placeholder(3);					//����*/
	pt_pcvoid						vtbl_;					//���ʷ�����vtbl,2017/5/29 18:19
	pt_pcvoid						ukn_ptr_;
	pt_dword						ukn_values_[31];		//һЩ��ֵ����1��ʼ����
	GameVector<stCD_InventoryCate>	bag_item_cont_;

	bool CanPutItToTheInventory(const stCD_EntityItemBased* item, enCD_InventoryType dst_inventory, int dst_pos_x, int dst_pos_y) const;
	//////////////////////////////////////////////////////////////////////////
	int TraInventory(const Fn_TraInventory& fn) const;
	int TraInventory(const FilterInventoryType& filter, const Fn_TraInventory& fn) const;
	int TraTotalItems(const Fn_TraItem& fn) const;
	int TraBodyItems(const Fn_TraItem& fn, bool include_flask, bool include_hide_weapon) const;
	int TraBodyEquipsGem(const Fn_TraEquipsInsideGem& fn, bool include_hide_weapon) const;
	//�������ϱ�ʯ����
	int TraBodyGemSkill(const Fn_TraGemSkill& fn, bool active_skill, bool passive_skill, bool include_hide_weapon) const;
	//////////////////////////////////////////////////////////////////////////
	stCD_Inventory* GetInventory(enCD_InventoryType type) const;
	stCD_Inventory* GetMainBag() const;
	stCD_EntityItemBased* GetFirstItem(enCD_InventoryType type) const;
	//////////////////////////////////////////////////////////////////////////
};
static_assert(CD_DATA(g_o_bag_item_cont_) == offsetof(stCD_InventoryMgr, bag_item_cont_), "");

struct stCD_ItemWordsDat{
	pt_pcvoid			vtbl_;
	p_mem_placeholder(g_so_words_dat_path_ - 4);
	GameWString			path_;		//$+14 UNICODE "Data/Words.dat"
	pt_dword			ukn_dw_;
};
static_assert(g_so_words_dat_path_ == offsetof(stCD_ItemWordsDat, path_), "");

struct stCD_ItemWordsName{
	pt_dword		ukn1_;		//һֱ=1
	pt_cwsz			en_words_;	//Ӣ�Ĵ�׺
	p_mem_placeholder(g_so_words_ch_words_ - 8);
	pt_cwsz			cn_words_;	//���Ĵ�׺
	pt_pcvoid		ukn_ptr_;	//ͨ����ukn_ptr_ = (char*)cn_words_ + 8

	void DebugInfo() const;
};
static_assert(g_so_words_ch_words_ == offsetof(stCD_ItemWordsName, cn_words_), "");
static_assert(sizeof(stCD_ItemWordsName) == g_so_words_ch_words_ + 8, "");

//��Ʒ�������������Ϣ��������׺
struct stCD_ItemWordsInfo{
	stCD_ItemWordsDat*		words_dat_;
	stCD_ItemWordsName*		words_name_;
};
//////////////////////////////////////////////////////////////////////////
//**********************�������
struct stCD_SomeSkillId{
	pt_dword		skill_id_move_;
	pt_dword		skill_id_ukn1_;
	pt_dword		skill_id_ukn2_;
	pt_dword		skill_id_ukn3_;
	pt_dword		skill_id_ukn4_;
	pt_dword		skill_id_ukn5_;

	static stCD_SomeSkillId& GetMe();
};

struct stCD_PassiveSkillGraphMgr{
	typedef GameVector<pt_word> SkillIdContT;

	pt_pcvoid						vtbl_;
	stCD_DbPassiveSkillGraph*		db_graph_;
	SkillIdContT					learned_skill_id_cont_;		//��ѧ���ܣ�����ID������
	stCD_UknGameVector				ukn_vector1_;				//���vectorΪ��
	stCD_UknGameHash_map			ukn_hash_map_;				//$20�������һ��Ϊ�ա�
	enCD_ProfessionType				profession_type_;			//$40��ְҵ����
	p_mem_placeholder(3);		//����
	int								ukn_point1_;
	int								regret_point_;				//��ڵ���
	int								ukn_point2_;
	int								ukn_point3_;
	int								ukn_;
	int								ukn_point4_;
	int								ukn_point5_;

	//�õ��츳������û�е���츳����
	int GetTalentPoint() const;
	int GetTotalTotalPoint() const;

	void DebugInfo() const;
};
static_assert(0x20 == offsetof(stCD_PassiveSkillGraphMgr, ukn_hash_map_), "");
static_assert(0x44 == offsetof(stCD_PassiveSkillGraphMgr, ukn_point1_), "");
static_assert(CD_DATA(g_o_regret_skill_point_) == offsetof(stCD_PassiveSkillGraphMgr, regret_point_), "");
static_assert(0x4c == offsetof(stCD_PassiveSkillGraphMgr, ukn_point2_), "");
static_assert(0x50 == offsetof(stCD_PassiveSkillGraphMgr, ukn_point3_), "");
static_assert(0x58 == offsetof(stCD_PassiveSkillGraphMgr, ukn_point4_), "");
static_assert(0x5c == offsetof(stCD_PassiveSkillGraphMgr, ukn_point5_), "");

struct stCD_SkillAttrInfo{};
struct stCD_SkillAttrValue{
	typedef CmnBufferVector<pt_dword, 5> ValueCont;

	enCD_SkillAttrValueType		value_type_;
	ValueCont					values_;
};
typedef CmnStaticVector<stCD_SkillAttrValue, 20> stCD_SkillAttrValueCont;

struct stCD_SkillAttrObj{
	stCD_Vtbl_SkillAttrObj*		vtbl_;
	stCD_SkillAttrInfo*			attr_info_;
	stCD_DbStats*				db_stats_;

	stCD_SkillAttrObj();
	bool IsValid() const;
	pt_dword GetSkillAttrValue(pt_dword attr_value_id) const;
};
static_assert(0xc == sizeof(stCD_SkillAttrObj), "");

//����ṹ�岢�������0x60���ֽ�����
struct stCD_SkillInfo{
	pt_word									skill_id_;
	pt_word									ukn_w_;
	stCD_GrantedEffectsPerLevelPairT		granted_effects_per_level_;		//�ƶ�����������ۣ�����ֶ�Ϊ��
	p_mem_placeholder(4 * 4);			//������ֵ
	pt_dword								use_cnt_;						//ʹ�ô���
	pt_dword								ukn_value_[8];
#ifdef VER3_
	p_mem_placeholder(4 * 2);
#endif
	stCD_SkillAttrInfo*						attr_info_;
	
	stCD_TblItemActiveSkills* GetActiveSkillDb() const;
	stCD_SkillAttrObj GetSkillAttrObj() const;
	bool GetSkillAttrValues(stCD_SkillAttrValueCont& attr_values) const;
	void DebugInfo() const;
	void DebugSkillAttrInfo() const;
};
static_assert(0x1c == offsetof(stCD_SkillInfo, use_cnt_), "");
static_assert(g_so_skill_info_attr_ == offsetof(stCD_SkillInfo, attr_info_), "");

struct stCD_SkillRefInfo{
	pt_pcvoid		vtbl_;
	pt_dword		ref_cnt_;
	pt_dword		weak_cnt_;			//weak_cnt?
	stCD_SkillInfo	skill_info_;		//$c
};

struct stCD_Skill_IdInfo{
	typedef std::function<bool(stCD_SkillInfo*)> Fn_TraMySkill;

	stCD_SkillInfo*			skill_info_;
	stCD_SkillRefInfo*		skill_ref_info_;

	void DebugInfo() const;
};
static_assert(sizeof(stCD_Skill_IdInfo) == 8, "");

struct stCD_ActorUknSkillInfo{
	bool			ukn_bool_;		//=1
	p_mem_placeholder(3);
	pt_pcvoid		ukn_ptr_;
};

//�������������ִ���ͷż��ܵ�Ч����
//�����������麯�����ǵ�1����������ͷŵ�this�ڴ档
struct stCD_SkillObj{
	virtual void Destruction(bool delete_self) = 0;

	stCD_ActorUknSkillInfo*			ptr_actor_member_;		//ָ��Actor�����е������Ա����
	stCD_Skill_IdInfo				skill_info_;
	pt_word							skill_id_;
	pt_short						send_use_skill_cnt_;
	p_mem_placeholder(3);
	bool							ukn_bool_;			//=0,$17
	p_mem_placeholder(4);
	pt_dword						update_mouse_pos_;	//$1c
	stCD_VecInt						dst_pos_;
	p_mem_placeholder(g_so_skill_obj_size_ - g_so_skill_obj_dst_pos_ - sizeof(stCD_VecInt));
};
static_assert(g_so_skill_obj_ukn_bool_ == offsetof(stCD_SkillObj, ukn_bool_), "");
static_assert(g_so_skill_obj_update_mouse_pos_ == offsetof(stCD_SkillObj, update_mouse_pos_), "");
static_assert(g_so_skill_obj_dst_pos_ == offsetof(stCD_SkillObj, dst_pos_), "");
static_assert(g_so_skill_obj_size_ == sizeof(stCD_SkillObj), "");

struct stCD_SkillTypeInfo{
	enCD_DownInventoryType		type_;
	stCD_Skill_IdInfo			skill_;
};
static_assert(sizeof(stCD_SkillTypeInfo) == 0xc, "");

struct stCD_InventorySkillItemInfo{
	stCD_Skill_IdInfo			skill_;			//���л����ܺ����������ֵ���
	pt_word						skill_id_;

	void DebugInfo() const;
};

struct stCD_InventorySkillItem{
	p_mem_placeholder(CD_DATA(g_o_get_inventory_skill_item_info_));
	stCD_InventorySkillItemInfo		skill_info_;

	void DebugInfo() const;
};
static_assert(CD_DATA(g_o_get_inventory_skill_item_info_) == offsetof(stCD_InventorySkillItem, skill_info_), "");

struct stCD_InventorySkillMgr{
	p_mem_placeholder(CD_DATA(g_o_inventory_skill_item_array_));
	stCD_InventorySkillItem*	skills_[kSGT_KeyT - kSGT_LeftBt + 1];

	void DebugInfo() const;
};
static_assert(CD_DATA(g_o_inventory_skill_item_array_) == offsetof(stCD_InventorySkillMgr, skills_), "");

//�����inventory������������������Ҳ������Ʒ��
struct stCD_DownInventoryMgr{
	p_mem_placeholder(CD_DATA(g_o_get_inventory_skill_mgr_));
	stCD_InventorySkillMgr*		skill_mgr_;

	stCD_InventorySkillItem* GetSkillItem(enCD_DownInventoryType type) const;
	const stCD_Skill_IdInfo* GetSkillIdInfo(enCD_DownInventoryType type) const;
	void DebugInfo() const;
};
static_assert(CD_DATA(g_o_get_inventory_skill_mgr_) == offsetof(stCD_DownInventoryMgr, skill_mgr_), "");

//������ܺ󣬵������л����ܵ��Ǹ��򣬸ÿ��е�ǰ���м��ܣ����� ���������
struct stCD_UiSelectMySkill : stCD_UiObjBase{
	//��������� Ҳ��stCD_SkillNodeInfo�ṹ������û�м���ID����Ϣ
	typedef stCD_Skill_IdInfo::Fn_TraMySkill Fn_TraMySkill;
	//key�����Ǽ���id�ɣ���ʵ����ν��
	typedef stCD_GameHash_map<pt_dword, stCD_Skill_IdInfo> SkillContT;

	p_mem_placeholder(CD_DATA(g_o_get_my_skills_) - sizeof(stCD_UiObjBase));
	SkillContT			my_skills_;

	int TraMySkill(const Fn_TraMySkill& fn) const;
	void DebugInfo() const;
};
static_assert(CD_DATA(g_o_get_my_skills_) == offsetof(stCD_UiSelectMySkill, my_skills_), "");

struct stCD_MySkillMgrBase{
	stCD_MySkillMgrVtbl*	vtbl_;

	CMN_CAST_TO
};

struct stCD_MySkillMgrEx : stCD_MySkillMgrBase{
	stCD_UiSelectMySkill* GetMySkillMgr() const;
	void DebugInfo() const;
};

struct stCD_SkillEffectInfo{
	enCD_WeaponSkillType		weapon_skill_type_;
	enCD_SkillTypeValue			weapon_skill_value_;
};

struct stCD_ActorSkillMgr{
	typedef GameVector<stCD_MySkillMgrBase*> SkillMgrContT;
	typedef stCD_Skill_IdInfo::Fn_TraMySkill Fn_TraMySkill;
	typedef GameVector<stCD_Skill_IdInfo> SkillContT;

	pt_pcvoid				vtbl_;
	pt_dword				ukn_dw_;
	//�������������������ֵ
	enCD_WeaponSkillType	weapon_skill_type_;		//������Ч��ID�ɣ�����װ���˹���������ı������ֵ����ֻ�������ż��Ķ�������û�м�ʸ����Ч�����ˡ�
	enCD_SkillTypeValue		weapon_skill_value_;	//=30������ı������ֵ���Ͳ������ˣ��������´�������ˢ��״̬��
	SkillContT				my_skills_;		//�Ǹ����飬����ż���id��Ϣ��
	stCD_UknGameVector		ukn_vector_;
	SkillMgrContT			skill_ui_mgr_;

	stCD_ActorSkillMgr(const stCD_ActorSkillMgr&) = delete;
	stCD_ActorSkillMgr& operator=(const stCD_ActorSkillMgr&) = delete;
	stCD_MySkillMgrEx* GetUiSkillMgr() const;
	stCD_UiSelectMySkill* GetUiSelectMySkill() const;
	int TraMySkill(const Fn_TraMySkill& fn) const;
	stCD_SkillInfo* FindSkill(pt_word skill_id) const;
	stCD_SkillObj* CreateSkillObj(pt_word skill_id) const;
	void DebugInfo() const;
};
static_assert(g_so_get_my_skills_cont_ == offsetof(stCD_ActorSkillMgr, my_skills_), "");
static_assert(g_so_my_skill_mgr_array_get_skill_mgr_ == offsetof(stCD_ActorSkillMgr, skill_ui_mgr_), "");
//////////////////////////////////////////////////////////////////////////
//******************�������
struct stCD_QuestInfoBase{
	stCD_QuestInfoVtbl*		vtbl_;
	CMN_CAST_TO
};

struct stCD_CurQuestInfo : stCD_QuestInfoBase{
	stCD_DbMapPins*				db_map_pin_;
	stCD_DbMapConnections*		db_map_connection_;
	pt_pcvoid					vtbl1_;			//�����￪ʼ�������Ǹ����ϳ�Ա����
	stCD_Player*				player_;
	pt_dword					ukn_dw_;		//=1
	pt_dword					ukn_dw1_;		//=1
	stCD_QuestPair				quest_;
	stCD_QuestStatesPair		quest_state_;
	stCD_MapPinsPair			map_pin_;

	void DebugInfo() const;
};
static_assert(g_so_cur_quest_info_quest_state_ == offsetof(stCD_CurQuestInfo, quest_state_), "");
//////////////////////////////////////////////////////////////////////////
struct stCD_AttrDbPlayer : stCD_EntityAttrDbBase{
	p_mem_placeholder(4);
	pt_cwsz			profession_name_;		//ְҵ
	pt_dword		id_;
};

struct stCD_EntityAttrDbActor : stCD_EntityAttrDbBase{
	pt_pcvoid			ukn_ptr_;
	stCD_DbEntity*		act_db_;					//UNICODE "Metadata/Characters/Int/Int.act"
	GameWString			actor_file_path_;			//UNICODE "Metadata/Characters/Int/Int.act"
	pt_dword			ukn_dw_;
	pt_dword			ukn_dw1_;
	stCD_TblItemBloodTypesPair		blood_type_;
	//���ֵһ��Ϊ0x25
	enCD_WeaponSkillType	weapon_skill_type_;		//��������ʱ�򣬾ͻ��ȡ�����ֶΣ������õ�stCD_ActorSkillMgr.weapon_skill_type_��
	enCD_SkillTypeValue		weapon_skill_value_;	//��������ʱ�򣬻������ֶ����õ�stCD_ActorSkillMgr�С�һֱ=0x30
};
static_assert(g_so_actor_info_file_path_ == offsetof(stCD_EntityAttrDbActor, actor_file_path_), "");
static_assert(0x24 == offsetof(stCD_EntityAttrDbActor, ukn_dw_), "");
static_assert(g_so_entity_attr_db_skill_type_ == offsetof(stCD_EntityAttrDbActor, weapon_skill_type_), "");

struct stCD_AttrDbRender : stCD_EntityAttrDbBase{
	p_mem_placeholder(4);		//pt_pcvoid
	pt_dword		ukn_dw_;
	pt_dword		ukn_dw1_;
	GameWString		name_;		//ְҵ����stCD_AttrDbPlayer���ְҵ������һ����
	GameWString		ukn_str_;
	float			ukn_float_[4];
	pt_dword		ukn_dw2_;
	pt_word			ukn_w_;
	p_mem_placeholder(2);

	void DebugInfo() const;
};
static_assert(g_so_player_db_render_name_ == offsetof(stCD_AttrDbRender, name_), "");
static_assert(0x50 == offsetof(stCD_AttrDbRender, ukn_dw2_), "");

//********��Ʒ���db
//Ʒ��
struct stCD_AttrDbQuality : stCD_EntityAttrDbBase{

};

//�ѵ�
struct stCD_AttrDbStack : stCD_EntityAttrDbBase{
	pt_pcvoid			ukn_ptr_;
	p_mem_placeholder(4);
	pt_pcvoid			ukn_price_;				//�۸���ص�
	p_mem_placeholder(4);
	pt_dword			max_stack_cnt_;			//���ѵ�����
	//����ɫ����ʾ�ù�������
	GameWString			function_desc_;			//�������������� ���;��� �ģ�$+18 UNICODE "����һ�����س���Ĵ�����"
	pt_dword			ukn_dw_;

	void DebugInfo() const;
};
static_assert(0xc == offsetof(stCD_AttrDbStack, ukn_price_), "");
static_assert(g_so_attr_db_stack_max_cnt_ == offsetof(stCD_AttrDbStack, max_stack_cnt_), "");

//(char*)(stCD_AttrAttributeRequirements*)attr_requirement + 0x8����ŵ���stCD_AttrDbAttributeRequirementsָ�롣
struct stCD_AttrDbAttributeRequirements : stCD_EntityAttrDbBase{
	pt_pcvoid	ukn_ptr_;
	pt_dword	power_;				//��������
	pt_dword	smart_;				//��������
	pt_dword	brain_;				//�����������ǻ�
	pt_dword	unused_level_;		//����ȼ������Ƕ�=0xf����֪Ϊ�Ρ�����ȼ���������stCD_EntityAttrMods���Ϊ׼��

	void DebugInfo() const;
};
static_assert(g_so_attr_db_AttributeRequirements_power_ == offsetof(stCD_AttrDbAttributeRequirements, power_), "");

struct stCD_AttrDbMods : stCD_EntityAttrDbBase{

};

struct stCD_AttrDbSockets : stCD_EntityAttrDbBase{

};

struct stCD_AttrDbSkillGem : stCD_EntityAttrDbBase{
	pt_pcvoid					ukn_ptr_;
	stCD_GrantedEffectsPairT	granted_effects_pair_;	//$8
	enCD_GemSlotColor			gem_color_;				//��ʯ��ɫ
	stCD_SkillGemsPairT			skill_gem_pair_;		//$14
	pt_dword					ukn_dw1_;
	pt_dword					ukn_dw2_;
	pt_dword					ukn_dw3_;
	pt_dword					ukn_dw4_;
	pt_dword					ukn_dw5_;
	pt_pcvoid					ukn_ptr1_;
	pt_dword					ukn_dw6_;

	//������ؿգ�������������
	stCD_TblItemActiveSkills* GetActiveSkill() const;
	stCD_TblItemGrantedEffectsPerLevel* GetDbPerLevelByLevel(pt_dword lvl) const;
	void DebugInfo() const;
};
static_assert(8 == offsetof(stCD_AttrDbSkillGem, granted_effects_pair_), "");
static_assert(sizeof(stCD_AttrDbSkillGem) == g_so_attr_db_skill_gem_size_, "");

struct stCD_EntityAttrDbChest : stCD_EntityAttrDbBase{
	pt_pcvoid					ukn_ptr_;
	stCD_TblItemChestsPair		db_chest_;
	bool						ukn_b_;
	bool						show_name_;		//Ϊ�����ʾ����
	bool						ukn_b2_;
	bool						ukn_b3_;
	bool						ukn_b4_;
	bool						ukn_b5_;
	bool						ukn_b6_;
	bool						ukn_b7_;
	bool						ukn_b8_;
	bool						ukn_b9_;
	p_mem_placeholder(2);
	pt_dword					ukn_dw_;			//$1c
	pt_pcvoid					ukn_ptr1_;
	stCD_DataChestEffectsPair	chest_effest_;		//$24
	stCD_DataStrongboxesPair	strong_box_;
	pt_dword					ukn_dw2_;

	void DebugInfo() const;
	bool IsQuest() const;
	bool IsIgnore() const;
};
static_assert(0x11 == offsetof(stCD_EntityAttrDbChest, show_name_), "");
static_assert(0x14 == offsetof(stCD_EntityAttrDbChest, ukn_b4_), "");
static_assert(0x1c == offsetof(stCD_EntityAttrDbChest, ukn_dw_), "");
static_assert(0x24 == offsetof(stCD_EntityAttrDbChest, chest_effest_), "");
static_assert(0x34 == offsetof(stCD_EntityAttrDbChest, ukn_dw2_), "");

struct stCD_EntityAttrDbWorldItem : stCD_EntityAttrDbBase{
	pt_pcvoid			ukn_ptr_;
	pt_dword			ukn_dw_;
	stCD_UknGameArray	ukn_array_;
	pt_dword			ukn_dw1_;		//$14
	pt_dword			ukn_dw2_;
	pt_dword			ukn_dw3_;
	pt_dword			ukn_dw4_;		//$20
	stCD_UknGameArray	ukn_array1_;
	pt_dword			ukn_dw5_;
	pt_dword			ukn_dw6_;
	pt_dword			ukn_dw7_;
	pt_dword			ukn_dw8_;
	stCD_DbStats*		db_stats_;			//$3c
	pt_pcvoid			ukn_ptr1_;
	pt_dword			ukn_dw9_;
	pt_dword			ukn_dw10_;
	pt_dword			ukn_dw11_;
	pt_dword			ukn_dw12_;
	stCD_DbStats*		db_stats1_;		//$58
	pt_pcvoid			ukn_ptr2_;

	void DebugInfo() const;
};
static_assert(g_so_entity_db_world_item_size_ == sizeof(stCD_EntityAttrDbWorldItem), "");

struct stCD_EntityAttrDbUsable : stCD_EntityAttrDbBase{
	pt_pcvoid			ukn_ptr_;
	enCD_UsableType		usable_type_;
};
static_assert(g_so_attr_db_usable_type_ == offsetof(stCD_EntityAttrDbUsable, usable_type_), "");

struct stCD_EntityAttrDbCharges : stCD_EntityAttrDbBase{
	pt_pcvoid		ukn_ptr_;
	pt_int			max_charges_;		//������
	pt_int			per_charges_;		//ÿ�γ�������
};

struct stCD_EntityAttrDbFlask : stCD_EntityAttrDbBase{
	struct stFlaskValueInfo{
		stCD_Value		hp_;
		stCD_Value		mp_;
		stCD_Value		time_;
	};
	typedef GameVector<stFlaskValueInfo> FlaskValueContT;

	pt_pcvoid			ukn_ptr_;
	pt_pvoid			vtbl1_;
	FlaskValueContT		flask_values_;
	enCD_FlaskType		flask_type_;
};
static_assert(g_so_attr_db_flask_type_ == offsetof(stCD_EntityAttrDbFlask, flask_type_), "");

struct stCD_EntityAttrDbTargetable : stCD_EntityAttrDbBase{

	void DebugInfo() const;
};

struct stCD_EntityAttrDbMonster : stCD_EntityAttrDbBase{
	pt_pcvoid							ukn_ptr_;		//��ַ������ͬ
	stCD_TblItemMonsterVarietiesPair	variety_;

	stCD_TblItemMonsterTypes* GetMonsterType() const;
	//�Ƿ����ٻ���
	bool IsCalled() const;
	void DebugInfo() const;
};

struct stCD_EntityAttrDbNPC: stCD_EntityAttrDbBase{
};

struct stCD_EntityAttrDbClientNPC : stCD_EntityAttrDbBase{
};

struct stCD_EntityAttrDbInventories : stCD_EntityAttrDbBase{
};

struct stCD_EntityAttrDbTriggerableBlockage : stCD_EntityAttrDbBase{
	pt_pcvoid		ukn_ptr_;
	bool			ukn_b_;
	bool			ukn_b1_;
	bool			ukn_b2_;		//�����Ϊ�٣��Ͳ����д��ͼ���ݣ���Ϊ�ٲŻ��д��ͼ���ݡ�
};

struct stCD_EntityAttrDbAreaTransition : stCD_EntityAttrDbBase{

};
//////////////////////////////////////////////////////////////////////////
struct stCD_Life : stCD_EntityAttrBase{
	typedef GameVector<stCD_BuffInfo*> BuffContT;

	p_mem_placeholder(g_so_life_hp_ - sizeof(stCD_EntityAttrBase));
	stCD_LifeDataHp		hp_;
	stCD_LifeData		mp_;
	stCD_LifeData		shield_;	//��������
	p_mem_placeholder(CD_DATA(g_o_life_get_buff_) - g_so_life_hp_ - sizeof(stCD_LifeData) * 2 - sizeof(stCD_LifeDataHp));
	BuffContT			buff_cont_;

	void DebugInfo() const;
};
static_assert(g_so_life_hp_ == offsetof(stCD_Life, hp_), "");
static_assert(CD_DATA(g_o_life_get_buff_) == offsetof(stCD_Life, buff_cont_), "");

//0x98����ŵ��ǽ�ɫ����
struct stCD_Actor : stCD_EntityAttrBase{
	pt_dword					ukn_dw_;		//=0
	pt_pcvoid					vtbls_[6];		//����vtbl
	stCD_EntityAttrDbActor*		attr_db_;
	pt_pcvoid					ukn_ptr1_;
	pt_pcvoid					ukn_ptr2_;
	//����ʹ�ü��ܺ����������ȴ浽cur_using_skill_���������غ󣬱��ֵ��ŵ�using_skill_timed_�У������ż�ʱ�����ܡ�
	stCD_SkillObj*				using_skill_timed_;		//ʹ�ü���ʱ�������ֶβ���ֵ����ʹ�ü��ܵ�ʱ���������ֶζ���Ϊ0�ġ�
	stCD_SkillObj*				cur_using_skill_;		//$34
	stCD_ActorUknSkillInfo		ukn_skill_info_;
	p_mem_placeholder(g_so_actor_use_skill_left_time_ - g_so_actor_ukn_skill_info_ - sizeof(stCD_ActorUknSkillInfo));
	pt_dword					skill_left_time_;		//����ʩ��ʱ��
	pt_short					use_skill_cnt_;			//ʹ�ü��ܴ���
	pt_short					server_use_skill_cnt_;	//�������������ģ�������һ��Ϊ��
	p_mem_placeholder(CD_DATA(g_o_actor_get_skill_mgr_) - g_so_actor_use_skill_cnt_ - 4);
	stCD_ActorSkillMgr			skill_mgr_;

	//�����Ǵ��м�Ĺֲ��ܶ��Ĺ�
	//$30,�ܶ�ǰ��0�������ǵ�ַ
	//$64���Ǹ�vector����֮ǰ��0����֮�����ֵ
	//$78��$80����ǰ��0������1

	void DebugInfo() const;
	const stCD_ActorSkillMgr& GetMySkillMgr() const;
	bool HandleMsg(const stCD_GameEntityMsg& msg) const;
	bool DummyMsg_OnMove(bool dst_direct, const stCD_VecInt& dst_pos) const;
	//���ʷ���Ч����������ȻҲ���������������һֱû�б����á�
	bool UseSkill(pt_word skill_id, const stCD_VecInt* dst_pos);
	pt_word IncUseSkillCnt();
	bool CanUseSkill() const;
	bool TerminateCurSkill();
};
static_assert(g_so_actor_get_actor_info_ == offsetof(stCD_Actor, attr_db_), "");
static_assert(0x30 == offsetof(stCD_Actor, using_skill_timed_), "");
static_assert(g_so_actor_ukn_skill_info_ == offsetof(stCD_Actor, ukn_skill_info_), "");
static_assert(g_so_actor_use_skill_left_time_ == offsetof(stCD_Actor, skill_left_time_), "");
static_assert(g_so_actor_use_skill_cnt_ == offsetof(stCD_Actor, use_skill_cnt_), "");
static_assert(CD_DATA(g_o_actor_get_skill_mgr_) == offsetof(stCD_Actor, skill_mgr_), "");

struct stCD_Pathfinding : stCD_EntityAttrBase{
	p_mem_placeholder(g_so_pathfinding_is_moving_ - sizeof(stCD_EntityAttrBase));
	bool			is_moving_;
	bool			ukn_[2];
	pt_byte			is_3d_;		//�Ƿ�3D����  >=0��3D����  0xFF��2D����
	stCD_VecInt		dst_pos_;	//Ҫ�ƶ������꣬Ŀ������
	stCD_VecInt*	mouse_dst_pos_;		//���Ŀ������

	//�������ֻ���һ�Σ���ô��Ϸ������������һ�Σ���������ɿ����ţ���ô���������һֱ�����á�
	bool PlayerMove(const stCD_VecInt& dst_pos) const;
	bool PlayerMoveD(const stCD_VecInt& dst_pos, int p1, int p2, int p3, int p4, int p5) const;
	void DebugInfo() const;
};
static_assert(g_so_pathfinding_is_moving_ == offsetof(stCD_Pathfinding, is_moving_), "");

struct stCD_Player : stCD_EntityAttrBaseDb{
	typedef GameVector<stCD_QuestInfoBase*> CurQuestInfoCont;
	typedef std::function<bool(stCD_CurQuestInfo*)> Fn_TraCurQuestInfo;

	GameWString						name_;			//��ɫ����
	p_mem_placeholder(g_so_player_power_ - sizeof(GameWString) - sizeof(stCD_EntityAttrBaseDb));
	pt_dword						power_;			//����
	pt_dword						smart_;			//����
	pt_dword						brain_;			//�������ǻ�
	pt_word							level_;			//�ȼ�,$40
	p_mem_placeholder(2);
#ifndef VER3_
	enCD_kMapDifficulty				difficulty_;	//��ǰ���ڵ�ͼ���Ѷȵȼ�
#endif
	pt_dword						ukn1_;
	pt_dword						ukn2_;
#ifdef VER3_
	BranchStateContT				branch_state_;
#else
	BranchStateContT				branch_state_[kMD_Merciless];
#endif
	p_mem_placeholder(CD_DATA(g_o_cur_quest_info_) - g_so_player_brach_state_ - g_so_brach_quest_state_total_size_);
	CurQuestInfoCont				cur_quest_cont_;

	stCD_AttrDbPlayer* GetAttrDb() const;
	int TraCurQuestInfo(const Fn_TraCurQuestInfo& fn) const;
	stCD_QuestStatesPair* FindQuestState(stCD_QuestStatesPair& out_res, const stCD_QuestPair& quest, enCD_kMapDifficulty difficult) const;
	stCD_QuestStatesPair* FindQuestState(stCD_QuestStatesPair& out_res, const stCD_QuestPair& quest) const;
	void DebugInfo() const;

private:
	stCD_QuestStatesPair* FindQuestStateImpl(stCD_QuestStatesPair& out_res, const stCD_QuestPair& quest, enCD_kMapDifficulty difficult) const;
};
static_assert(g_so_player_power_ == offsetof(stCD_Player, power_), "");
static_assert(g_so_player_brach_state_ == offsetof(stCD_Player, branch_state_), "");
static_assert(CD_DATA(g_o_cur_quest_info_) == offsetof(stCD_Player, cur_quest_cont_), "");

struct stCD_PlayerMe : stCD_Player{
};

struct stCD_Render : stCD_EntityAttrBase{
	pt_pcvoid			vtbl_[10];
	p_mem_placeholder(4);		//=0
	stCD_AttrDbRender*	attr_db_;
	p_mem_placeholder(4 * 8);
	GameWString			name_;
	pt_dword			ukn_dw_;

	void DebugInfo() const;
};
static_assert(0x34 == offsetof(stCD_Render, attr_db_), "");
static_assert(g_so_render_npc_name_ == offsetof(stCD_Render, name_), "");

struct stCD_ItemTipsAttrValue{
	GameWString		value_;
	pt_dword		ukn_dw1_;
	pt_dword		ukn_dw2_;
};
static_assert(0x20 == sizeof(stCD_ItemTipsAttrValue), "");

struct stCD_ItemTipsBaseAttr{
	typedef GameVector<stCD_ItemTipsAttrValue> AttrValueCont;

	pt_dword				ukn_dw_;
	pt_dword				ukn_dw1_;
	GameWString				attr_cn_name_;
	AttrValueCont			attr_values_;
	GameWString				ukn_str_;
	pt_dword				ukn_dw2_;
};
static_assert(0x48 == sizeof(stCD_ItemTipsBaseAttr), "");

//����ṹ������Ҫ��ʾ����Ϣ�������ַ�������ֵ�ȡ��ṹ��ͦ��������0x1e0���ֽڡ�
struct stCD_ItemTipsParams{
	typedef GameVector<stCD_ItemTipsBaseAttr> BaseAttrCont;
	typedef GameVector<GameWString> StringCont;

	stCD_ItemTipsParams() = delete;
	stCD_ItemTipsParams(const stCD_ItemTipsParams&) = delete;
	stCD_ItemTipsParams& operator = (const stCD_ItemTipsParams&) = delete;
	static stCD_ItemTipsParams& GetMe();

	GameWString				item_words_;		//��׺
	GameWString				item_name_;			//��Ʒ��
	pt_dword				name_color_;		//������������ɫ
	BaseAttrCont			base_attrs_;		//�������ԣ����磺���ס��������ܵ�
	BaseAttrCont			require_attrs_;		//��������
	stCD_UknGameVector		ukn_vector_;		//Ϊ��
	stCD_UknGameVector		ukn_vector1_;		//Ϊ��
	StringCont				blue_attrs_;		//������
	StringCont				blue_attrs1_;		//�������һ���ġ�
	p_mem_placeholder(4 * 6);	//�ܿ���Ҳ��vector
	StringCont				add_bule_attrs_;	//����������
	StringCont				add_bule_attrs1_;	//�������һ���ġ�
	stCD_UknGameVector		ukn_vector2_[4];
	p_mem_placeholder(4 * 6);	//�ܿ���Ҳ��vector
	GameWString				desc_suffix_;		//�ٻ�ɫ��˵��
	p_mem_placeholder(CD_DATA(g_o_item_tips_param_item_lvl_) - g_so_item_tips_param_desc_suffix_ - sizeof(GameWString));
	pt_dword				item_lvl_;			//��Ʒ�ȼ�
};
static_assert(0x34 == offsetof(stCD_ItemTipsParams, base_attrs_), "");
static_assert(0x4c == offsetof(stCD_ItemTipsParams, ukn_vector_), "");
static_assert(0x58 == offsetof(stCD_ItemTipsParams, ukn_vector1_), "");
static_assert(0x64 == offsetof(stCD_ItemTipsParams, blue_attrs_), "");
static_assert(0x94 == offsetof(stCD_ItemTipsParams, add_bule_attrs_), "");
static_assert(g_so_item_tips_param_desc_suffix_ == offsetof(stCD_ItemTipsParams, desc_suffix_), "");
static_assert(CD_DATA(g_o_item_tips_param_item_lvl_) == offsetof(stCD_ItemTipsParams, item_lvl_), "");

struct stCD_ModsInfo{};
//$18����ʵ�Ǹ������Ǹ������Ľṹ�壬stCD_ModsInfo����is_identified_��item_color_����Ϣ��stCD_ModsInfo�ĳ�Ա������
struct stCD_EntityAttrMods : stCD_EntityAttrBase{
	typedef GameVector<stCD_ItemWordsInfo> WordsInfoContT;

	p_mem_placeholder(g_so_entity_attr_mods_get_db_ - sizeof(stCD_EntityAttrBase));
	stCD_AttrDbMods*	attr_db_;
	WordsInfoContT		words_info_;		//��׺
	p_mem_placeholder(g_so_entity_attr_mods_is_identified_ - g_so_entity_attr_mods_get_db_ - 4 - sizeof(WordsInfoContT));
	bool				is_identified_;		//�Ƿ��Ѽ���
	p_mem_placeholder(g_so_entity_attr_mods_name_color_ - g_so_entity_attr_mods_is_identified_ - 1);
	enCD_ItemColor		item_color_;		//��Ʒ��ɫ����Ʒ���ֵ���ɫ
	p_mem_placeholder(CD_DATA(g_o_entity_attr_mods_player_lvl_) - g_so_entity_attr_mods_name_color_ - 4);
	pt_dword			player_lvl_;		//����Ľ�ɫ�ȼ�

	stCD_AttrDbMods* GetAttrDb() const;
	void DebugInfo() const;
};
static_assert(g_so_entity_attr_mods_get_db_ == offsetof(stCD_EntityAttrMods, attr_db_), "");
static_assert(g_so_entity_attr_mods_is_identified_ == offsetof(stCD_EntityAttrMods, is_identified_), "");
static_assert(g_so_entity_attr_mods_name_color_ == offsetof(stCD_EntityAttrMods, item_color_), "");
static_assert(CD_DATA(g_o_entity_attr_mods_player_lvl_) == offsetof(stCD_EntityAttrMods, player_lvl_), "");

struct stCD_EntityAttrStack : stCD_EntityAttrBase{
	stCD_AttrDbStack*		attr_db_;
	pt_dword				item_cnt_;		//��Ʒ��������ǰ�ѵ�������

	stCD_AttrDbStack* GetAttrDb() const;
	void DebugInfo() const;
};
static_assert(g_so_attr_stack_get_db_ == offsetof(stCD_EntityAttrStack, attr_db_), "");

//��ʯ���֮���
struct stCD_EntityAttrSockets : stCD_EntityAttrBase{
	typedef std::function<bool(stCD_EntityItemBased*)> Fn_TraInsideGem;

	stCD_AttrDbSockets*		attr_db_;
	stCD_GemSlot			gem_slot_;

	stCD_AttrDbSockets* GetAttrDb() const;
	int TraInsideGem(const Fn_TraInsideGem& fn) const;
	void DebugInfo() const;
};
static_assert(g_so_attr_sockets_get_db_ == offsetof(stCD_EntityAttrSockets, attr_db_), "");

struct stCD_EntityAttrUsable : stCD_EntityAttrBase{
	stCD_EntityAttrDbUsable*		attr_db_;		//$8

	stCD_EntityAttrDbUsable* GetAttrDb() const;
};

//��������
struct stCD_EntityAttrCharges : stCD_EntityAttrBase{
	stCD_EntityAttrDbCharges*		attr_db_;
	pt_int							cur_charges_;		//��ǰ���ܴ���

	stCD_EntityAttrDbCharges* GetAttrDb() const;
};

struct stCD_EntityAttrNPC : stCD_EntityAttrBase{
	pt_dword						ukn_dw_;		//=0
	stCD_EntityAttrDbNPC*			attr_db_;

	p_mem_placeholder(CD_DATA(g_o_entity_attr_npc_is_locked_) - 8 - sizeof(stCD_EntityAttrBase));
	bool		is_locked_;		//��������־ͬʱΪ�٣����ʾNpc�����ƶ���
	bool		is_locked1_;
	p_mem_placeholder(2);		//����

	bool CanMoved() const;
};
static_assert(CD_DATA(g_o_entity_attr_npc_is_locked_) == offsetof(stCD_EntityAttrNPC, is_locked_), "");

struct stCD_EntityAttrClientNpc : stCD_EntityAttrBase{
	pt_pcvoid						vtbl1_;
	pt_pcvoid						vtbl2_;
	pt_pcvoid						ukn_ptr_;
	pt_dword						ukn_dw_;
	pt_dword						ukn_dw1_;
#ifdef VER3_
	p_mem_placeholder(4);
#endif
	stCD_EntityEffectsBased*		entity_effect_;		//������ֵ��Ϊ�գ���ʾ��Ҫ�ӵ�����
	stCD_EntityAttrDbClientNPC*		attr_db_;

	//�Ƿ���Ҫ���ʣ�������NPCͷ�����и�̾��
	bool NeedVisit() const;
};

struct stCD_EntityAttrWorldItem : stCD_EntityAttrBase{
	pt_pcvoid						ukn_ptr_;
	pt_pcvoid						vtbl1_;
	stCD_EntityAttrDbWorldItem*		attr_db_;		//$10
	stCD_EntityItemBased*			item_entity_;

	//���db��û�õ�
	stCD_EntityAttrDbWorldItem* GetAttrDb() const;
	stCD_EntityItemBased* GetItemEntity() const;
	void DebugInfo() const;
};

struct stCD_EntityAttrChest : stCD_EntityAttrBase{
	bool						ukn_b_;
	p_mem_placeholder(3);
	pt_pcvoid					vtbl1_;
	stCD_EntityAttrDbChest*		attr_db_;
	stCD_UknGameVector			ukn_ptr_vector_;		//��ŵ���ָ��
	bool						is_opened_;				//�Ƿ��Ѵ򿪣���Ҫ�������־�ˡ�
	p_mem_placeholder(3);			//����

	void DebugInfo() const;
	stCD_EntityAttrDbChest* GetDbChest() const;
};
static_assert(g_so_get_entity_attr_db_chest_ == offsetof(stCD_EntityAttrChest, attr_db_), "");
static_assert(g_so_chesk_is_opened_ == offsetof(stCD_EntityAttrChest, is_opened_), "");

struct stCD_EntityAttrTargetable : stCD_EntityAttrBase{
	pt_pcvoid						vtbl1_;
	pt_pcvoid						vtbl2_;
	stCD_EntityAttrDbTargetable*	attr_db_;
	bool							targetable_;			//���Ϊfalse���Ͳ���ʾ�ˣ�������Ӧ�κε��
	bool							area_highlight_;		//�����������ʹΪfalseҲ������Ӧ���
	p_mem_placeholder(2);
};
static_assert(0x14 == offsetof(stCD_EntityAttrTargetable, targetable_), "");

struct stCD_EntityAttrMonster : stCD_EntityAttrBase{
	//����������������
	struct stMost{
		pt_pcvoid		vtbl_;
		pt_dword		ukn_dw_;		//=1
		pt_dword		ukn_dw1_;		//=1
	};
	struct stArmoursShields{
		pt_dword					ukn_dw_;
		pt_dword					ukn_dw1_;
		stCD_DbPairArmoursShields	db_model_;
	};
	//ÿ�������Monster��vtbl����һ���ģ������������ȴ�еĲ�һ����
	union AnySubObj{
		stMost				most_;
		stArmoursShields	armour_shield_;
	};
	//////////////////////////////////////////////////////////////////////////
	pt_pcvoid						ukn_ptr_;
	stCD_EntityAttrDbMonster*		attr_db_;
	pt_dword						ukn_;			//���ǵ�ַ
	pt_word							ukn_type_;		//������flag�ɣ�$+14��=88000020
	p_mem_placeholder(2);			//����
	AnySubObj						any_obj_;

	stCD_EntityAttrDbMonster* GetAttrDb() const;
};
static_assert(0x18 == offsetof(stCD_EntityAttrMonster, any_obj_), "");

struct stCD_EntityAttrTransitionable : stCD_EntityAttrBase{
	p_mem_placeholder(CD_DATA(g_o_transitionable_state_) - sizeof(stCD_EntityAttrBase));
	enCD_TransitionableState		state_;
	p_mem_placeholder(3);		//����

	//�Ƿ��Ѵ�
	bool IsOpened() const;
};
static_assert(CD_DATA(g_o_transitionable_state_) == offsetof(stCD_EntityAttrTransitionable, state_), "");

//������������Եģ����ź󣬻���ĵ�ͼ����Ϊ��ͨ����
struct stCD_EntityAttrTriggerableBlockage : stCD_EntityAttrBase{
	pt_pcvoid									vtbl1_;
	pt_pcvoid									vtbl2_;
	pt_pcvoid									vtbl3_;
	stCD_EntityAttrDbTriggerableBlockage*		attr_db_;
	bool										is_blocked_;		//���ź�ͱ��0��
	p_mem_placeholder(3);		//���ܶ���bool
	pt_dword									ukn_dw_;
	stCD_MapDataVector							src_data_;			//���������������д��Ӧ������
	stRectInt									dst_rect_;			//Ҫ��д��Ŀ������
};
static_assert(0x18 == offsetof(stCD_EntityAttrTriggerableBlockage, is_blocked_), "");

struct stCD_ItemPrice{
	stCD_DbEntity*	db_item_;		//UNICODE "Metadata/Items/Currency/CurrencyIdentification"
	pt_dword		item_cnt_;

	stCD_AttrDbItemBase* GetDbItemBase() const;
};
typedef stCD_SafeVector<stCD_ItemPrice> stCD_ItemPriceContT;

struct stCD_EntityAttrItemBase : stCD_EntityAttrBase{
	stCD_AttrDbItemBase*		attr_db_;
	p_mem_placeholder(CD_DATA(g_o_item_base_is_bind_) - sizeof(stCD_EntityAttrBase) - 4);
	bool						is_bind_;
	p_mem_placeholder(3);		//����

	stCD_AttrDbItemBase* GetAttrDb() const;
	//�ɹ��򷵻�����ָ�룬�õ����
	stCD_ItemPriceContT* GetPrice(stCD_ItemPriceContT& price) const;
};
static_assert(CD_DATA(g_o_item_base_is_bind_) == offsetof(stCD_EntityAttrItemBase, is_bind_), "");

struct stCD_AttrInventoryEquip{
	stCD_TblItemItemVisualIdentityPair	visual_identity_;
	p_mem_placeholder(4 * 4);		//һֱ=0
	enCD_AttrInventoryEquipType			equip_type_;
	/*
	left:	0x11,	2
	right:	1b,		8
	�·���	19,		5
	ͷ����	1a,		86
	��		17,		0
	shoe	18,		0
	lring	6,		0
	rring	6,		0
	����		16		28
	*/
	//��װ������ʱ����Ѹ��ֶ����õ�stCD_ActorSkillMgr.skill_type_��
	enCD_WeaponSkillType	weapon_skill_type_;		//�Ǹ�pt_char������Ϊ������Ϸ��ת���ɵ�int��
	pt_int					value2_;		//�Ǹ�pt_char������Ϊ������Ϸ��ת���ɵ�int��
};
static_assert(g_so_attr_inventory_equip_size_ == sizeof(stCD_AttrInventoryEquip), "");

struct stCD_EntityAttrInventories : stCD_EntityAttrBase{
	pt_dword							ukn_dw_;
	stCD_EntityAttrDbInventories*		attr_db_;
	stCD_UknGameVector					ukn_ptr_cont_;
	stCD_AttrInventoryEquip				equips_[kAIET_Max];
};

struct stCD_EntityAttrDiesAfterTime : stCD_EntityAttrBase{
};

struct stCD_EntityAttrSkillGem : stCD_EntityAttrBase{
	pt_dword				ukn_dw_;		//=0
	pt_pcvoid				ukn_ptr_;
	stCD_AttrDbSkillGem*	attr_db_;
	pt_dword				ukn_dw1_;
	pt_dword				cur_lvl_;		//��ǰ���ܱ�ʯ�ĵȼ�

	stCD_AttrDbSkillGem* GetAttrDb() const;
	stCD_TblItemGrantedEffectsPerLevel* GetDbPerLevel() const;
	pt_dword GetRequireLvl() const;
	pt_dword GetRequireAttr(enCD_ItemRequireAttr type) const;
};
static_assert(0x10 == offsetof(stCD_EntityAttrSkillGem, attr_db_), "");
static_assert(0x18 == offsetof(stCD_EntityAttrSkillGem, cur_lvl_), "");

struct stCD_EntityAttrPortal : stCD_EntityAttrBase{
};

struct stCD_EntityAttrAreaTransition : stCD_EntityAttrBase{
	float									ukn_float_;		//=-1
	stCD_EntityAttrDbAreaTransition*		attr_db_;
	p_mem_placeholder(4);			//=-1
};
static_assert(0xc == offsetof(stCD_EntityAttrAreaTransition, attr_db_), "");
//////////////////////////////////////////////////////////////////////////
struct stCD_EntityPlayer : stCD_EntityBaseT<enCD_EntityAttr_Player>{
	stCD_Player* GetPlayer() const;
	stCD_Life* GetLife() const;
	stCD_Actor* GetActor() const;
	void DebugInfo() const;
};

struct stCD_EntityPlayerMe : stCD_EntityPlayer{
	stCD_PlayerMe* GetPlayer() const;
};

struct stCD_EntityNpc : stCD_EntityBaseT<enCD_EntityAttr_Npc>{
	//���ִ����Render����
	stCD_Render* GetRender() const;
	//������Ժ����������йذɣ�����ʹ֮���ֵ���NPC
	stCD_EntityAttrNPC* GetNpc() const;
	//��������Բ���NPC���
	stCD_EntityAttrClientNpc* GetClientNpc() const;
	void DebugInfo() const;
};

struct stCD_EntityWaypoint : stCD_EntityBaseT<enCD_EntityAttr_Waypoint>{
	stCD_Render* GetRender() const;
	void DebugInfo() const;
};

//������
struct stCD_EntityAreaTransition : stCD_EntityBaseT<enCD_EntityAttr_AreaTransition>{
	stCD_Render* GetRender() const;
	stCD_EntityAttrAreaTransition* GetAreaTransition() const;
	void DebugInfo() const;
};

struct stCD_EntityMonster : stCD_EntityBaseT<enCD_EntityAttr_Monster>{
	//���ִ����Render����
	stCD_Render* GetRender() const;
	stCD_Life* GetLife() const;
	stCD_EntityAttrDbMonster* GetDbMonster() const;
	stCD_EntityAttrMonster* GetMonster() const;
	stCD_EntityAttrNPC* GetNpc() const;
	//ͨ��������ж���������Ƿ���ԶԻ�
	stCD_EntityAttrClientNpc* GetClientNpc() const;
	//��Ҫ�ȷ���Npc���и�̾�ŵ�ʱ�򷵻���
	bool NeedVisitNpc() const;
	//�Ƿ���Թ���
	bool CanHit() const;
	//�Ƿ����ٻ���
	bool IsCalled() const;
	void DebugInfo() const;
};

struct stCD_EntityNoHuman : stCD_EntityBaseT<enCD_EntityAttr_NoHuman>{
	//���ִ����Render����
	stCD_Render* GetRender() const;
	void DebugInfo() const;
};

//���ӡ�ľͰ�������ߵ�����
struct stCD_EntityChest : stCD_EntityBaseT<enCD_EntityAttr_Chest>{
	//���ִ����Render����
	stCD_Render* GetRender() const;
	stCD_EntityAttrChest* GetChest() const;
	void DebugInfo() const;
};

//������Ʒ
struct stCD_EntityWorldItem : stCD_EntityBaseT<enCD_EntityAttr_WorldItem>{
	stCD_EntityAttrWorldItem* GetWorldItem() const;
	void DebugInfo() const;
};

//�ɴ��͵Ķ���
struct stCD_EntityTransitionable : stCD_EntityBaseT<enCD_EntityAttr_Transitionable>{
	//���ִ����Render����
	stCD_Render* GetRender() const;
	//�Ƿ��Ѵ򿪣����ѷ���
	bool IsOpened() const;
	void DebugInfo() const;
};
//////////////////////////////////////////////////////////////////////////
struct stCD_TblItemModel{
	p_mem_placeholder(g_so_tbl_item_model_model_path_);
	pt_cwsz				model_path_;
};
static_assert(g_so_tbl_item_model_model_path_ == offsetof(stCD_TblItemModel, model_path_), "");
typedef stCD_DbModelT<stCD_TblItemModel> stCD_DbModel;
typedef stCD_Db_TblItemPair<stCD_TblItemModel, stCD_DbModel> stCD_ModelPair;

struct stCD_MapDataTerrainModel{
	struct stTerrainObjInfo{
		stCD_Positioned*	obj_positioned_;
		char				ukn_byte_;			//ukn_byte_ & 0x7f
		p_mem_placeholder(3);

		void DebugInfo() const;
	};
	typedef GameVector<stTerrainObjInfo> TerrainObjs;

	stCD_ModelPair		model_;
	TerrainObjs			terrain_objs_;
	pt_dword			ukn_dw_;
	stCD_VecShort		pos_;
	pt_word				ukn_w_;
	pt_word				ukn_w1_;

	void DebugInfo(const stCD_VecInt& pos) const;
};
static_assert(g_so_terrain_model_pos_ == offsetof(stCD_MapDataTerrainModel, pos_), "");
static_assert(g_so_terrain_model_size_ == sizeof(stCD_MapDataTerrainModel), "");

struct stCD_MapData{
	struct stUknInfo{
		bool				ukn_b_;
		pt_pcvoid			ukn_ptr_;
		p_mem_placeholder(4);
	};
	static_assert(9 == sizeof(stUknInfo), "");
	struct stTerrainInfo{
		stCD_DbModel*		terrain_;
		bool				ukn_b_;
		bool				ukn_b1_;
		bool				ukn_b2_;
		stUknInfo			ukn_info_[7];
		p_mem_placeholder(2);		//����?
	};
	static_assert(4 + 3 + sizeof(stUknInfo) * 7 + 2 == sizeof(stTerrainInfo), "");
	static_assert(0x48 == sizeof(stTerrainInfo), "");
	typedef GameVector<stTerrainInfo> TerrainInfoCont;
	typedef std::pair<enCD_MapDataFlag*, enCD_MapDataFlag> MapDataAddrInfo;

	pt_pcvoid					vtbl_;
	stCD_World*					world_;
	p_mem_placeholder(g_so_map_data_model_data_ - 8);
	stCD_MapDataTerrainModel*	terrain_models_;		//����ģ������
	TerrainInfoCont				terrain_info_;
	stCD_VecInt					shrink_size_;			//�����ĵ�ͼ�ߴ�
	//��ǰ��Ϸ״̬�µĵ�ͼ����
	stCD_MapDataVector			cur_map_data_;			//��������Ԫ��������һ���ġ�
	//ԭʼ�ĵ�ͼ����
	stCD_MapDataVector			src_map_data_;
	pt_int						shrink_width_;			//������йصĶ����ɣ�shrink_width_*dst_pos.y+dst_pos.x/2=dst_pos�ĵ�ͼ��������
	//����������С��ͼ����Ľ�ɫ���ꡣ������������Ǳ������������ֵҪ��
	stCD_VecInt					little_map_shrink_pos_;	//С��ͼ����
	stCD_VecInt					big_map_shrink_pos_;	//���ͼ����

	static stCD_VecInt Pos2ShrinkPos(const stCD_VecInt& pos);
	static stCD_VecInt ShrinkPos2Pos(const stCD_VecInt& shrink_pos);
	stCD_VecInt GetMapSize() const;
	//���������ֻ���ģ�Ӧ�ÿ����ڲ�����Ϸ���߳���ִ�С�
	enCD_MapDataFlag GetDstMapData(const stCD_VecInt& dst_pos, bool is_src_map_data) const;
	//��������ȡ��ͼ���ݵ��㷨
	MapDataAddrInfo GetDstMapDataAddr(const stCD_VecInt& dst_pos, bool is_src_map_data);
	typedef enCD_MapDataFlag(stCD_MapData::*Fn_GetDstMapData)(const stCD_VecInt& dst_pos, bool is_src_map_data) const;
	static Fn_GetDstMapData GetFn_GetDstMapData();
	stCD_MapDataTerrainModel* TerrainBegin() const;
	stCD_MapDataTerrainModel* TerrainEnd() const;
	stCD_MapDataTerrainModel* GetTerrainFrom(stCD_EntityPosBased* entity, stCD_VecInt& out_pos) const;
	int GetSameModelPathCnt(pt_cwsz model_path) const;
	void ModifyByEntity(stCD_EntityPosBased* entity);
	void DebugInfo() const;
	void DebugModelsInfo(int radius, bool has_obj) const;
	void DbgPlayerPosModel() const;
};
static_assert(g_so_map_data_model_data_ == offsetof(stCD_MapData, terrain_models_), "");
static_assert(g_so_map_data_shrink_size_ == offsetof(stCD_MapData, shrink_size_), "");
static_assert(g_so_map_data_shrink_width_ == offsetof(stCD_MapData, shrink_width_), "");
//////////////////////////////////////////////////////////////////////////
struct stCD_ObjMgr{
	//key��ʵ��id����stCD_EntityPosBased.id_��һ���ġ�
	typedef GameMap<pt_dword, stCD_EntityPosBased*> ObjContT;
	typedef std::function<bool(stCD_EntityPosBased*)> Fn_TraObj;

	pt_pcvoid			vtbl_;
#ifdef VER3_
	p_mem_placeholder(4 * 5);
#else
	p_mem_placeholder(8);			//����dword����0
#endif
	ObjContT			objs_;		//npc/���/��/WorldItem����
	ObjContT			doodad_objs_;	//С���裬һ��Render��û������

	int TraEntityObj(const Fn_TraObj& fn, bool is_obj) const;
};

//world=��ͼ
struct stCD_World{
	pt_pcvoid									vtbl_;
#ifdef VER3_
	p_mem_placeholder(4 * 3);
#endif
	stCD_WorldAreaPairT							world_area_;
	p_mem_placeholder(CD_DATA(g_o_get_entity_component_) - g_so_map_world_area_ - sizeof(stCD_WorldAreaPairT));
	stCD_EntityPlayerMe*						player_entity_;
	p_mem_placeholder(CD_DATA(g_o_map_obj_btree_) - CD_DATA(g_o_get_entity_component_) - 4);
	stCD_ObjMgr									obj_mgr_;
	p_mem_placeholder(g_so_world_environments_info_ - CD_DATA(g_o_map_obj_btree_) - sizeof(stCD_ObjMgr));
	stCD_TblItemEnvironmentsPair				environments_;
	stCD_Db_Metadata_EnvironmentSettings*		db_env_setting_;
	pt_pcvoid									ukn_ptrs_[4];
	stCD_MapData								map_data_;

	//stCD_TblItemEnvironmentsPair		tmp_env_;		//$430���հ���ʱ���Ȱѻ�����ŵ���
	void DebugInfo() const;
};
static_assert(g_so_map_world_area_ == offsetof(stCD_World, world_area_), "");
static_assert(CD_DATA(g_o_get_entity_component_) == offsetof(stCD_World, player_entity_), "");
static_assert(CD_DATA(g_o_map_obj_btree_) == offsetof(stCD_World, obj_mgr_), "");
static_assert(g_so_world_environments_info_ == offsetof(stCD_World, environments_), "");
//static_assert(0x2b8 == offsetof(stCD_World, environments_), "");
static_assert(CD_DATA(g_o_world2map_data_) == offsetof(stCD_World, map_data_), "");
//////////////////////////////////////////////////////////////////////////
//***********************ui���
struct stCD_UknUiBase{
	pt_pcvoid		vtbl_;

	CMN_CAST_TO
};

struct stCD_UknUiMgrBase{
	pt_pcvoid			vtbl_;
	stCD_UknUiBase*		ui_;

	CMN_CAST_TO
};

//û�õ�
struct stCD_DlgUiMgr{
	pt_pcvoid				vtbl_;
};

struct stCD_TmpUiEvent{
	stCD_DlgUiMgr*		tmp_ui_mgr_;
};

struct stCD_WaypointPointItem : stCD_UiObjBase{
	p_mem_placeholder(CD_DATA(g_o_waypoint_item_map_pin_) - sizeof(stCD_UiObjBase));
	stCD_MapPinsPair		map_pin_;

	bool EqualMapName(const std::wstring& map_name) const;
	stCD_TblItemMapPins* GetMapPin() const;
	void DebugInfo(enCD_kMapDifficulty difficult, stCD_DlgWaypointMap* map) const;
};
static_assert(CD_DATA(g_o_waypoint_item_map_pin_) == offsetof(stCD_WaypointPointItem, map_pin_), "");

struct stCD_DlgWaypointMap_UknObj_UknObj{
};

struct stCD_DlgWaypointMap_UknObj{
	pt_pcvoid		vtbl_;
	pt_pcvoid		vtbl1_;
	pt_pcvoid		vtbl2_;
	pt_pcvoid		vtbl3_;
	pt_pcvoid		vtbl4_;
	p_mem_placeholder(CD_DATA(g_o_ui_waypoint_map_ukn_obj_ukn_obj_) - 4 * 5);
	stCD_DlgWaypointMap_UknObj_UknObj	ukn_obj_;
};
static_assert(CD_DATA(g_o_ui_waypoint_map_ukn_obj_ukn_obj_) == offsetof(stCD_DlgWaypointMap_UknObj, ukn_obj_), "");

struct stCD_BtHidePos : stCD_UiObjBase{};

struct stCD_DlgWaypointMap : stCD_UiObjBase{
	typedef std::function<bool(stCD_WaypointPointItem*)> Fn_TraWaypointItem;

	p_mem_placeholder(g_so_dlg_waypoint_map_ukn_obj_ - sizeof(stCD_UiObjBase));
	stCD_DlgWaypointMap_UknObj*	ukn_obj_;
	pt_pcvoid					ukn_ptr_;
	pt_dword					chapter_idx_;		//�½���������1��ʼ
#ifdef VER3_
	p_mem_placeholder(CD_DATA(g_o_ui_waypoint_connections_num_) - g_so_dlg_waypoint_map_ukn_obj_ - 4 * 3);
#else
	enCD_kMapDifficulty			difficulty_;	//��ŵ���MapPins��WorldArea�����ͻ�������
	p_mem_placeholder(CD_DATA(g_o_ui_waypoint_connections_num_) - CD_DATA(g_o_dlg_waypoint_map_area_type_) - 4);
#endif
	pt_dword					connections_num_;			//���ڴ��͵�ķ���
	pt_dword					ukn_dw_;
	/*�����ǰ���Դ��͵��õ�ͼ����Ϊ�գ�����Ϊ��*/
	stCD_WaypointPointItem*		waypoint_item_;				//$0x9dc���������ĳ���������ƶ����õ��ʱ��Ż������ֵ

	stCD_UiObjBase* GetWaypointContainer() const;
	int TraWaypointItem(enCD_TraUiShownFlag show_flag, bool* fn_ret, const Fn_TraWaypointItem& fn) const;
	const stCD_TblItemWorldArea* GetTransferWolrdItem(const stCD_WaypointPointItem& point_item) const;
	//�ж�Ŀ���ͼ�Ƿ��д��͵�
	bool TheMapHasWaypoint(const stCD_WaypointPointItem& point_item) const;
	//�Ƿ��ֹ��õ�ͼ�ˣ�û��ȥ���õ�ͼ�Ļ�����ô��Ӧ�Ĵ��͵ĵ����ʺ�
	bool DiscovedTheMap(const stCD_WaypointPointItem& point_item) const;
	//Ŀ���ͼ�Ĵ��͵��Ƿ��Ѵ򿪣����û�򿪣���ô��Ӧ�Ĵ��͵ĵ��Ǹ��㣬����Ѵ򿪣����Ǹ�������ʵ��
	bool IsTheWaypointOpened(const stCD_WaypointPointItem& point_item) const;
	stCD_WaypointPointItem* FindWaypoint(enCD_TraUiShownFlag show_flag, const std::wstring& map_name) const;
	//����ctrl_pressed==true����ᵯ�� instance manager���
	bool CallChangeMap(const stCD_WaypointPointItem* point_item, bool ctrl_pressed);
	stCD_BtHidePos* GetBtHidePos() const;
	//�Ƿ���Ե��ȥ����
	bool CanPressGotoHidePos() const;
	bool PressGotoHidePos() const;
	void DebugInfo() const;
};
static_assert(g_so_dlg_waypoint_map_ukn_obj_ == offsetof(stCD_DlgWaypointMap, ukn_obj_), "");
//static_assert(0x8bc == g_so_dlg_waypoint_map_ukn_obj_, "");
static_assert(g_so_dlg_waypoint_map_ukn_ptr_ == offsetof(stCD_DlgWaypointMap, ukn_ptr_), "");
#ifndef VER3_
static_assert(CD_DATA(g_o_dlg_waypoint_map_area_type_) == offsetof(stCD_DlgWaypointMap, difficulty_), "");
static_assert(0x8c8 == offsetof(stCD_DlgWaypointMap, difficulty_), "");
#endif
static_assert(CD_DATA(g_o_ui_waypoint_connections_num_) == offsetof(stCD_DlgWaypointMap, connections_num_), "");
//static_assert(0x9dc == offsetof(stCD_DlgWaypointMap, waypoint_item_), "");

struct stCD_StateUiLogic : stCD_UiEventMgr{
	p_mem_placeholder(CD_DATA(g_o_ui_mgr_top2ui_mgr_) - sizeof(stCD_UiEventMgr));
	stCD_UiEventMgr_Ret8		ui_event_mgr_;			//���簴esc�ر�npc�����¼�
	p_mem_placeholder(g_so_ui_logic_top_ui_ - sizeof(stCD_UiEventMgr) - CD_DATA(g_o_ui_mgr_top2ui_mgr_));
	stCD_UiObjBase*				top_ui_;
	p_mem_placeholder(CD_DATA(g_o_ui_mgr_top_get_dlg_ui_mgr_) - 4 - g_so_ui_logic_top_ui_);
	stCD_UiEventMgr_Ret8		tmp_ui_event_mgr_;		//�����������ʱ�ģ������ᱻ��д������㴫�͵㣬Ȼ���ٵ�Ҫȥ�ĵط���ʱ��
};
static_assert(CD_DATA(g_o_ui_mgr_top2ui_mgr_) == offsetof(stCD_StateUiLogic, ui_event_mgr_), "");
static_assert(g_so_ui_logic_top_ui_ == offsetof(stCD_StateUiLogic, top_ui_), "");
static_assert(g_so_ui_logic_top_ui_ == 0xaa4, "");
static_assert(CD_DATA(g_o_ui_mgr_top_get_dlg_ui_mgr_) == offsetof(stCD_StateUiLogic, tmp_ui_event_mgr_), "");

struct stCD_DlgWaypointQuestsScrollBar : stCD_UiObjBase{
};

struct stCD_DlgWaypointQuestItem : stCD_UiObjBase{
	p_mem_placeholder(CD_DATA(g_o_dlg_waypoint_quest_item_db_quest_) - sizeof(stCD_UiObjBase));
	stCD_QuestPair		db_quest_;

	stCD_DlgWaypointChapterContent* GetChapterContent() const;
	stCD_DlgWaypointMap* GetMap() const;
	void DebugInfo() const;
};
static_assert(CD_DATA(g_o_dlg_waypoint_quest_item_db_quest_) == offsetof(stCD_DlgWaypointQuestItem, db_quest_), "");

struct stCD_DlgWaypointQuestsContainer : stCD_UiObjBase{
	typedef std::function<bool(stCD_DlgWaypointQuestItem*)> Fn_TraQuestItem;

	int TraQuestItem(bool* fn_ret, const Fn_TraQuestItem& fn) const;
};

struct stCD_DlgWaypointQuestsPanel : stCD_UiObjBase{
	stCD_DlgWaypointQuestsScrollBar* GetScrollBar() const;
	stCD_DlgWaypointQuestsContainer* GetUiQuests() const;

private:
	stCD_UiObjBase* GetUiQuestsImpl() const;
};

struct stCD_DlgWaypointQuestInfoPanel : stCD_UiObjBase{
};

struct stCD_DlgWaypointChapterContent : stCD_UiObjBase{
	stCD_DlgWaypointMap* GetMap() const;
	stCD_DlgWaypointQuestsPanel* GetQuestsPanel() const;
	stCD_DlgWaypointQuestInfoPanel* GetQuestInfoPanel() const;
};

struct stCD_DlgWaypointTabChapter : stCD_UiObjBase{
	typedef stCD_DlgWaypointMap::Fn_TraWaypointItem Fn_TraWaypointItem;
	typedef stCD_DlgWaypointQuestsContainer::Fn_TraQuestItem Fn_TraQuestItem;

	stCD_DlgWaypointChapterContent* GetContent() const;
	stCD_DlgWaypointMap* GetMap() const;
	stCD_DlgWaypointQuestsContainer* GetUiQuests() const;
	int TraWaypointItem(enCD_TraUiShownFlag show_flag, bool* fn_ret, const Fn_TraWaypointItem& fn) const;
	int TraQuestsItem(bool* fn_ret, const Fn_TraQuestItem& fn) const;
};

struct stCD_DlgWaypointTabDifficulty : stCD_UiObjBase{
	typedef std::function<bool(stCD_DlgWaypointTabChapter*)> Fn_TraTabChapter;

	stCD_UiObjBase* GetChapterContainer() const;
	int TraTabChapter(enCD_TraUiShownFlag show_flag, const Fn_TraTabChapter& fn) const;
};

struct stCD_DlgWaypoint : stCD_UiObjBase{
	typedef std::function<bool(stCD_DlgWaypointTabDifficulty*)> Fn_TraTabDifficulty;
	typedef std::function<bool(enCD_kMapDifficulty, stCD_DlgWaypointMap*, stCD_WaypointPointItem*)> Fn_TraWaypointItem;
	typedef std::function<bool(stCD_DlgWaypointMap*)> Fn_TraMap;
	typedef std::function<bool(enCD_kMapDifficulty, int, stCD_DlgWaypointQuestItem*)> Fn_TraQuestItem;

	struct stWaypointInfo{
		enCD_kMapDifficulty			difficulty_;
		stCD_DlgWaypointMap*		map_;
		stCD_WaypointPointItem*		waypoint_;

		stWaypointInfo();
	};

	stCD_UiObjBase* GetTabDifficultContainer() const;
	int TraTabDifficulty(enCD_TraUiShownFlag show_flag, const Fn_TraTabDifficulty& fn) const;
	int TraWaypointItem(enCD_TraUiShownFlag show_flag, enCD_kMapDifficulty difficulty, const Fn_TraWaypointItem& fn) const;
	int TraMap(enCD_TraUiShownFlag show_flag, const Fn_TraMap& fn) const;
	bool FindWaypoint(enCD_kMapDifficulty difficulty, const std::wstring& map_name, stWaypointInfo& out_res) const;
	//��=kMD_Invalid������������Ѷȣ���chapter < 1������������½�
	int TraQuestItem(enCD_TraUiShownFlag show_flag, enCD_kMapDifficulty difficulty, int chapter, 
		const Fn_TraQuestItem& fn) const;
	void DebugInfo() const;
};

struct stCD_NpcMenuItemInfo{
};

struct stCD_NpcPanelPressEventParam{
	stCD_UiNpcPanelMenuItem*	menu_item_;
	stCD_NpcMenuItemInfo*		item_info_;
	//�ڵ��MenuItem��ʱ����������������û���õ�
	bool						mouse_hover_;		//����ƶ���ȥ��ʱ��Ϊ��
	bool						ukn_true_;			//һֱΪ��
	p_mem_placeholder(2);							//����

	void DebugInfo() const;
};

struct stCD_UiEventParam_Pos{
	bool			handled_;
	p_mem_placeholder(3);
	float			left_top_x_;
	float			left_top_y_;
	float			right_bottom_x_;
	float			right_bottom_y_;
	bool			left_press_;
	p_mem_placeholder(100);		//����

	stCD_UiEventParam_Pos(){
		ZeroMemory(this, sizeof(*this));
		left_press_ = true;
	}
};
static_assert(0x14 == offsetof(stCD_UiEventParam_Pos, left_press_), "");

struct stCD_NpcMenuItemInfoCont{
	typedef stCD_GameDeque<stCD_NpcMenuItemInfo*> ContT;

	pt_pcvoid		ukn_ptr_;
	ContT			cont_;
};

struct stCD_NpcPanelTalkInfo{
	stCD_NPCTalkPair		talk_;
	pt_dword				ukn_flag_;		//һֱ����0x39
};
static_assert(0xc == sizeof(stCD_NpcPanelTalkInfo), "");
typedef GameVector<stCD_NpcPanelTalkInfo> stCD_NpcPanelTalkInfoVector;

struct stCD_UiLabel : stCD_UiObjBase{
	p_mem_placeholder(CD_DATA(g_o_ui_lable_str_info_) - sizeof(stCD_UiObjBase));
	pt_pcvoid				ukn_ptr_;
	pt_pcvoid				ukn_ptr1_;

private:
	GameWString				format_str_;		//��ʽ���ַ��������磺"<fg:argb(255,255,192,119)>{����������}<fg:argb(255,255,"
	stCD_UknGameVector		ukn_values_;
	GameWString				total_str_;			//UNICODE "����������\nǰ�� ����������Ӫ"

public:
	const GameWString& GetFormatStr() const;
	const GameWString& GetTotalStr() const;
	bool EqualLableStr(const std::wstring& lable_str) const;
};
static_assert(CD_DATA(g_o_ui_lable_str_info_) == offsetof(stCD_UiLabel, ukn_ptr_), "");

struct stCD_UiNpcPanelMenuItem : stCD_UiObjBase{
	stCD_UiLabel* GetLabel() const;
	bool EqualLable(const std::wstring& lable) const;
	void DebugInfo() const;
};

struct stCD_UiNpcPanelMenuItems : stCD_UiObjBase{
	typedef std::function<bool(stCD_UiNpcPanelMenuItem*)> Fn_TraMenuItem;
	int TraMenuItem(const Fn_TraMenuItem& fn) const;
};

struct stCD_UiNpcPanelMenuItemsContainer : stCD_UiObjBase{
	typedef GameVector<stCD_NpcPanelPressEventParam> ItemEventInfoContT;
	typedef std::function<bool(const stCD_NpcPanelPressEventParam&)> Fn_TraPressEventParam;

	p_mem_placeholder(CD_DATA(g_o_ui_npc_panel_items_container_items_info_) - sizeof(stCD_UiObjBase));
	ItemEventInfoContT			items_info_cont_;

	stCD_UiNpcPanelMenuItems* GetMenuItems() const;
	int TraPressEventParam(const Fn_TraPressEventParam& fn) const;
	const stCD_NpcPanelPressEventParam* FindPressEventParam(const std::wstring& lable) const;
	bool IsNpcMenuPanel() const;
	bool IsNpcTalkPanel() const;
	void DebugInfo() const;
};
static_assert(CD_DATA(g_o_ui_npc_panel_items_container_items_info_) == offsetof(stCD_UiNpcPanelMenuItemsContainer, items_info_cont_), "");

struct stCD_UiNpcPanel : stCD_UiObjBase{
	typedef stCD_UiNpcPanelMenuItems::Fn_TraMenuItem Fn_TraMenuItem;
	typedef stCD_UiNpcPanelMenuItemsContainer::Fn_TraPressEventParam Fn_TraPressEventParam;

	p_mem_placeholder(CD_DATA(g_o_ui_npc_panel_items_info_) - sizeof(stCD_UiObjBase));
	stCD_NpcMenuItemInfoCont		items_info_;

	stCD_UiObjBase* GetTitleLabelContainer() const;
	stCD_UiLabel* GetUiLabel() const;
	const GameWString* GetTitle() const;
	bool EqualTitleLabel(const std::wstring& title) const;
	stCD_UiNpcPanelMenuItemsContainer* GetMenuItemsContainer(enCD_NpcPanelItemsContainer panel_type) const;
	int TraMenuItem(enCD_NpcPanelItemsContainer panel_type, const Fn_TraMenuItem& fn) const;
	int TraPressEventParam(enCD_NpcPanelItemsContainer panel_type, const Fn_TraPressEventParam& fn) const;
	const stCD_NpcPanelPressEventParam* FindPressEventParam(enCD_NpcPanelItemsContainer panel_type, const std::wstring& lable) const;
	bool PressItem(const stCD_NpcPanelPressEventParam& param) const;
	bool PressItem(enCD_NpcPanelItemsContainer panel_type, const std::wstring& lable) const;
	void DebugInfo() const;
	void DebugAddrInfo() const;
	void DebugMenuItemInfo(int type) const;
};
static_assert(CD_DATA(g_o_ui_npc_panel_items_info_) == offsetof(stCD_UiNpcPanel, items_info_), "");

struct stCD_UiNpcDlgChoice2 : stCD_UiObjBase{
	p_mem_placeholder(CD_DATA(g_o_ui_npc_dlg_choice_help_bt_) - sizeof(stCD_UiObjBase));
	stCD_UiObjBase*		bt_choice_[2];		//0�ǰ������׶٣�1�ǻ��ܿ��׶�

	bool Choose(pt_byte choose_item) const;
};
static_assert(CD_DATA(g_o_ui_npc_dlg_choice_help_bt_) == offsetof(stCD_UiNpcDlgChoice2, bt_choice_), "");

//�������������9����ui��������ʾ����֪�������Ǹ�ɶ��
struct stCD_UiNpcPanelContainer : stCD_UiObjBase{
	stCD_UiNpcPanel* GetNpcPanel(bool must_shown) const;
	//�������׶١����ܿ��׶ٵ��Ǹ��Ի���
	stCD_UiNpcDlgChoice2* GetDlgChoice2() const;
};

//������Ʒ����괦������Ʒͼ��
struct stCD_UiMouseAttachItem : stCD_UiObjBase{
	stCD_EntityItemBased* GetItem() const;
};

struct stCD_UiItemGrid : stCD_UiObjBase{
	p_mem_placeholder(CD_DATA(g_o_ui_item_grid_item_id_) - sizeof(stCD_UiObjBase));
	pt_dword			item_id_;
};
static_assert(CD_DATA(g_o_ui_item_grid_item_id_) == offsetof(stCD_UiItemGrid, item_id_), "");

struct stCD_UiGridPanel : stCD_UiObjBase{
	typedef std::function<bool(stCD_UiItemGrid*)> Tra_ItemGrid;

	p_mem_placeholder(CD_DATA(g_o_ui_grid_panel_inventory_mgr_) - sizeof(stCD_UiObjBase));
	stCD_InventoryMgr*				inventory_mgr_;
	enCD_InventoryType				inventory_type_;
	p_mem_placeholder(CD_DATA(g_o_ui_grid_panel_get_inventory_) - 8 - CD_DATA(g_o_ui_grid_panel_inventory_mgr_));
	stCD_Inventory*					inventory_;
	p_mem_placeholder(g_so_ui_grid_panel_get_mouse_attach_item_ - 4 - CD_DATA(g_o_ui_grid_panel_get_inventory_));
	stCD_UiMouseAttachItem*			mouse_attach_item_;

	stCD_Vtbl_UiGridPanel* Vtbl() const;
	//ͨ�������Ա�����Ʒ
	stCD_Inventory* GetInventory() const;
	bool CanPutIt(const stCD_EntityItemBased* item, int dst_pos_x, int dst_pos_y) const;
	stCD_UiMouseAttachItem* GetMouseAttachItem() const;
	int TraItemGrids(const Tra_ItemGrid& fn) const;
	stCD_UiItemGrid* FindItemGrid(pt_dword item_id) const;
	bool PressGridItem(enCD_PressItemWithKey key_state, pt_dword item_id) const;
	bool PutItemDown(const stCD_VecInt& dst_pos) const;
	bool InsideGem(pt_dword item_id, pt_dword slot_idx) const;
	bool TakeoffGem(pt_dword item_id, pt_dword slot_idx) const;
	bool UseItem(pt_dword item_id, stCD_EntityItemBased* item) const;
	bool MergeItem(pt_dword dst_item_id) const;
};
static_assert(CD_DATA(g_o_ui_grid_panel_inventory_mgr_) == offsetof(stCD_UiGridPanel, inventory_mgr_), "");
//static_assert(0x8bc == offsetof(stCD_UiGridPanel, inventory_type_), "");
static_assert(CD_DATA(g_o_ui_grid_panel_get_inventory_) == offsetof(stCD_UiGridPanel, inventory_), "");
static_assert(g_so_ui_grid_panel_get_mouse_attach_item_ == offsetof(stCD_UiGridPanel, mouse_attach_item_), "");
//static_assert(0x964 == offsetof(stCD_UiGridPanel, mouse_attach_item_), "");

struct stCD_UiRightMostPanel : stCD_UiObjBase{};

//������
//��������UI�ؼ�����1����UiLabel����2���ǲ鿴����״̬���Ǹ���̾�Ű�ť
struct stCD_UiQuestStateQuestItem : stCD_UiObjBase{
	//��������+'\n'+'״̬��Ϣ'���
	stCD_UiLabel* GetUiLabel() const;
	bool GetQuestName(wchar_t* out_buffer, pt_dword buffer_size) const;
	bool GetQuestState(wchar_t* out_buffer, pt_dword buffer_size) const;
	void DebugInfo() const;
};

struct stCD_UiQuestStatePanel : stCD_UiObjBase{
	typedef std::function<bool(stCD_UiQuestStateQuestItem*)> Fn_TraQuestItem;

	int TraQuestItem(const Fn_TraQuestItem& fn) const;
};

struct stCD_UiQuestStatePanelContainer : stCD_UiObjBase{
	stCD_UiQuestStatePanel* GetQuestStatePanel() const;
};

struct stCD_UiLvlUpSkillGemItem : stCD_UiObjBase{
	struct stLvlUpInfo{
		std::wstring		item_name_;
		pt_dword			max_lvl_;
	};
	typedef std::vector<stLvlUpInfo> LvlUpInfo;

	stCD_UiObjBase* GetButton() const;
	bool CanLvlUpSkillGem() const;
	bool PressLvlUp() const;
	void DebugInfo() const;
	static void ClearLvlUpInfo();
	static void AddLvlUpInfo(const std::wstring& item_name, pt_dword max_lvl);

	p_mem_placeholder(CD_DATA(g_o_LvlUpSkillGemItem_item_) - sizeof(stCD_UiObjBase));
	stCD_EntityItemBased*		item_;

	static LvlUpInfo			lvl_up_info_;
};
static_assert(CD_DATA(g_o_LvlUpSkillGemItem_item_) == offsetof(stCD_UiLvlUpSkillGemItem, item_), "");

struct stCD_UiLvlStatePanel : stCD_UiObjBase{
	typedef std::function<bool(stCD_UiLvlUpSkillGemItem*)> Fn_TraLvlUpSkillGemItem;

	void DebugInfo() const;
	int TraLvlUpSkillGemItem(const Fn_TraLvlUpSkillGemItem& fn) const;
};

struct stCD_UiLvlStatePanelContainer : stCD_UiObjBase{
	void DebugInfo() const;
	stCD_UiLvlStatePanel* GetLvlStatePanel() const;
};

struct stCD_UiQuestLvlStatePanel : stCD_UiRightMostPanel{
	typedef stCD_UiQuestStatePanel::Fn_TraQuestItem Fn_TraQuestItem;

	stCD_UiQuestStatePanelContainer* GetQuestStatePanelContainer() const;
	stCD_UiLvlStatePanelContainer* GetLvlStatePanelContianer() const;
	int TraQuestItem(const Fn_TraQuestItem& fn) const;
	int PressAllLvlUpSkillGem() const;
	void DebugInfo() const;
};

struct stCD_UiDiedPanel : stCD_UiObjBase{};

struct stCD_MiniMapBase : stCD_UiObjBase{
};

struct stCD_MiniMap : stCD_MiniMapBase{

};

struct stCD_BigMap : stCD_MiniMapBase{

};

struct stCD_UiMap : stCD_UiObjBase{
	//����tab�������Ͻǳ��ֵ���壬����������Ϣ����ͼ�����Ѷȵȼ�������ȼ�����Ϣ
	stCD_UiObjBase* GetMapInfo() const;
	//С��ͼ�ʹ��ͼ��ʵ��ͬһ�����͵ġ�
	stCD_MiniMap* GetMiniMap() const;
	stCD_BigMap* GetBigMap() const;
};

struct stCD_UiEntityDescContainer : stCD_UiObjBase{
	int TraWorldItems(const Fn_TraSubUiObj& fn) const;
};

struct stCD_UiEntityDescTop : stCD_UiObjBase{
	stCD_UiEntityDescContainer* GetEntityDescContainer() const;

private:
	stCD_UiObjBase* GetSubContainer(int idx) const;
};

struct stCD_UiDlgQuestAward : stCD_UiObjBase{
	stCD_UiGridPanel* GetGridPanel() const;
	stCD_Inventory* GetInventory() const;
};

struct stCD_TabPageItemBase : stCD_UiObjBase{};

struct stCD_TabPageInfo{
	stCD_TabPageItemBase*	page_item_;
	stCD_UiObjBase*			tab_button_;
	GameWString				page_title_;

	stCD_TabPageInfo() = delete;
	stCD_TabPageInfo(const stCD_TabPageInfo&) = delete;
	stCD_TabPageInfo& operator = (const stCD_TabPageInfo&) = delete;
	CMN_CAST_TO
	bool IsValid() const;
	stCD_TabPageItemBase* GetPageItem() const;
	template<typename DerivedT>
	DerivedT* GetPageItemT() const{
		auto page_item = GetPageItem();
		if (!page_item) return nullptr;
		return page_item->CastTo<DerivedT>();
	}
	template<typename DerivedT>
	stCD_UiGridPanel* GetGridPanel() const{
		auto page = GetPageItemT<DerivedT>();
		if (!page) return nullptr;
		return page->GetGridPanel();
	}
};
static_assert(0x20 == sizeof(stCD_TabPageInfo), "");

struct stCD_UiStashGridPanelContainerBase : stCD_UiObjBase{};

struct stCD_UiStashSingleGridPanel : stCD_UiStashGridPanelContainerBase{
	stCD_UiGridPanel* GetGridPanel() const;
};

struct stCD_UiStashMultiGridPanel : stCD_UiStashGridPanelContainerBase{
	typedef std::function<bool(stCD_UiGridPanel*)> Fn_TraGridPanel;

	int TraGridPanel(const Fn_TraGridPanel& fn) const;
	stCD_UiGridPanel* FindGridPanel(int idx) const;
};

struct stCD_UiStashTabPageItem : stCD_TabPageItemBase{
	stCD_UiStashSingleGridPanel* GetSingleContainer() const;
	stCD_UiStashMultiGridPanel* GetMultiContainer(enCD_TraUiShownFlag show_flag) const;
	stCD_UiGridPanel* GetGridPanel() const;
};

struct stCD_UiBuyTabPageItem : stCD_TabPageItemBase{
	stCD_UiGridPanel* GetGridPanel() const;
};

//�ֿ⡢������嶼�������
struct stCD_UiTabPages : stCD_UiObjBase{
	typedef GameVector<stCD_TabPageInfo> PagesContT;
	typedef stCD_TabPageInfo PageInfo;
	typedef std::function<bool(const PageInfo&)> Fn_TraPage;

	int TraPages(const Fn_TraPage& fn) const;
	const PageInfo* GetCurPage() const;
	stCD_UiObjBase* GetPageButtons() const;
	stCD_UiObjBase* GetPagesContainer() const;
	int GetPagesCount() const;
	const PageInfo* FindPageInfo(const stCD_UiObjBase* tab_button) const;
	bool PressSwitchPage(const stCD_UiObjBase* tab_button) const;

	p_mem_placeholder(CD_DATA(g_o_ui_stash_pages_info_) - sizeof(stCD_UiObjBase));
	PagesContT		pages_;
	pt_dword		cur_page_idx_;
};
static_assert(CD_DATA(g_o_ui_stash_pages_info_) == offsetof(stCD_UiTabPages, pages_), "");

struct stCD_UiStashTop : stCD_UiObjBase{
	typedef stCD_UiTabPages UiTabPages;

	stCD_UiObjBase* GetTopContainer() const;
	UiTabPages* GetTabPages() const;
};

struct stCD_DlgStash : stCD_UiObjBase{
	typedef stCD_UiTabPages UiTabPages;
	typedef UiTabPages::PageInfo PageInfo;

	stCD_UiStashTop* GetUiTop() const;
	UiTabPages* GetTabPages() const;
	void DebugInfo() const;
};

struct stCD_UiCheckBox : stCD_UiObjBase{
	stCD_UiLabel* GetUiLabel() const;
	bool Enable(bool enable) const;

	p_mem_placeholder(CD_DATA(g_o_ui_check_box_enable_) - sizeof(stCD_UiObjBase));
	bool				enable_;
};
static_assert(CD_DATA(g_o_ui_check_box_enable_) == offsetof(stCD_UiCheckBox, enable_), "");

struct stCD_DlgBuy : stCD_UiObjBase{
	typedef stCD_UiTabPages UiTabPages;
	typedef UiTabPages::PageInfo PageInfo;

	UiTabPages* GetTabPages() const;
	stCD_UiCheckBox* GetBindCheckBox() const;
	bool EnableUseBind(bool enable);
};

struct stCD_UiSellContainer : stCD_UiObjBase{
	stCD_UiGridPanel* GetMyItemPage() const;
	stCD_UiGridPanel* GetNpcItemPage() const;
	stCD_UiObjBase* GetButtonAccept() const;
	stCD_UiObjBase* GetButtonCancel() const;
	bool PressButton(bool accept) const;
};

struct stCD_DlgSell : stCD_UiObjBase{
	stCD_UiSellContainer* GetTabPagesContainer() const;
	bool PressButton(bool accept) const;
};

struct stCD_DlgPropInventories : stCD_UiObjBase{
	stCD_UiGridPanel* FindGridPanel(enCD_InventoryType inventory_type) const;
};

struct stCD_DlgProp : stCD_UiObjBase{
	stCD_DlgPropInventories* GetUiInventories() const;
	stCD_UiGridPanel* FindGridPanel(enCD_InventoryType inventory_type) const;
};

struct stCD_UiPassiveSkillTop : stCD_UiObjBase{
	p_mem_placeholder(CD_DATA(g_o_passive_skill_graph_mgr_) - sizeof(stCD_UiObjBase));
	stCD_PassiveSkillGraphMgr*		graph_;			//�����츳������ʱ�򣬻��stCD_GameLogic.passive_skill_��������
};
static_assert(CD_DATA(g_o_passive_skill_graph_mgr_) == offsetof(stCD_UiPassiveSkillTop, graph_), "");

struct stCD_DlgPassiveSkill : stCD_UiObjBase{
	stCD_UiPassiveSkillTop* GetUiTop() const;
};

struct stCD_UiBuffNum : stCD_UiObjBase{
	stCD_UiLabel* GetBuffLabel() const;
};

struct stCD_UiBuffItemContainer : stCD_UiObjBase{
	stCD_UiBuffNum* GetUiBuffNum() const;
};

struct stCD_UiBuffItem : stCD_UiObjBase{
	typedef GameVector<pt_dword> EntityIdCont;

	stCD_UiBuffItemContainer* GetContainer() const;
	void DebugInfo() const;

	p_mem_placeholder(CD_DATA(g_o_caller_buff_item2entities_) - sizeof(stCD_UiObjBase));
	EntityIdCont		entity_ids_;			//��ŵ���ʵ��ID
};
static_assert(CD_DATA(g_o_caller_buff_item2entities_) == offsetof(stCD_UiBuffItem, entity_ids_), "");

struct stCD_UiBuffItemsContainer : stCD_UiObjBase{
	typedef std::function<bool(stCD_UiBuffItem*)> Fn_TraUiBuffItem;

	int TraUiBuffItem(const Fn_TraUiBuffItem& fn) const;
};

struct stCD_CallerBuffInfo{
	pt_word				skill_id_;
	p_mem_placeholder(2);		//ռλ��
	stCD_UiBuffItem*	buff_item_;
};
static_assert(8 == sizeof(stCD_CallerBuffInfo), "");

struct stCD_UiCallerBuff : stCD_UiObjBase{
	typedef GameVector<stCD_CallerBuffInfo> BuffItems;

	stCD_UiBuffItemsContainer* GetBuffContainer() const;

	p_mem_placeholder(CD_DATA(g_o_caller_buff_items_) - sizeof(stCD_UiObjBase));
	BuffItems			buff_items_;
};
static_assert(CD_DATA(g_o_caller_buff_items_) == offsetof(stCD_UiCallerBuff, buff_items_), "");

struct stCD_UiBuff : stCD_UiObjBase{
	typedef std::function<bool(stCD_SkillInfo*, stCD_UiBuffItem*)> Fn_TraCallerBuff;

	stCD_UiCallerBuff* GetCallerBuff() const;
	int TraCallerBuff(const Fn_TraCallerBuff& fn) const;
};

struct stCD_DlgMapLocator : stCD_UiObjBase{
	stCD_UiObjBase* GetBtClose() const;
	//������ť
	stCD_UiObjBase* GetBtStart() const;
	//���ͼ����ť
	stCD_UiObjBase* GetBtYiJieTuJian() const;
	stCD_UiGridPanel* GetUiGridPanel() const;
	bool PressStartYiJie() const;
};

struct stCD_MapLocatorMapAttrList : stCD_UiObjBase{
	struct stListItem{
		stCD_UiObjBase*						ui_item_;
		stCD_DataCraftingBenchOptionsPair	data_;

		void DebugInfo() const;
	};
	typedef std::function<bool(stListItem*)> Fn_TraListItem;
	typedef stCD_PairAdjacent<stListItem, void> SmartPtr;
	static_assert(8 == sizeof(SmartPtr), "");
	typedef GameVector<SmartPtr> ListItems;

	p_mem_placeholder(CD_DATA(g_o_map_attr_list_items_) - sizeof(stCD_UiObjBase));
	ListItems						list_items_;
	stCD_MapLocatorMapAttrList*		ptr_this_;
	int								cur_selected_;

	void DebugInfo() const;
	bool Select(const stListItem* item) const;
	int TraListItem(const Fn_TraListItem& fn) const;
};
static_assert(CD_DATA(g_o_map_attr_list_items_) == offsetof(stCD_MapLocatorMapAttrList, list_items_), "");
//static_assert(0xb08 == offsetof(stCD_MapLocatorMapAttrList, cur_selected_), "");

struct stCD_MapLocatorLocator : stCD_UiObjBase{

};

//�����ĵ�ͼ������
struct stCD_DlgSelfMapLocator : stCD_UiObjBase{
	void DebugInfo() const;
	//�����Ǹ����ӵ�ͼ���Ե��б�
	stCD_MapLocatorMapAttrList* GetMapAttrList() const;
	//�����Ǹ����õ�ͼ�����
	stCD_MapLocatorLocator* GetLocator() const;
	stCD_UiGridPanel* GetUiGridPanel() const;
	bool PressStart() const;

	p_mem_placeholder(CD_DATA(g_o_self_map_locator_bt_start_) - sizeof(stCD_UiObjBase));
	stCD_UiObjBase*			bt_start_;
	p_mem_placeholder(4 * 4);			//����UI����
	stCD_UiGridPanel*		grid_panel_;
};
static_assert(CD_DATA(g_o_self_map_locator_bt_start_) == offsetof(stCD_DlgSelfMapLocator, bt_start_), "");
//static_assert(0x8e8 == offsetof(stCD_DlgSelfMapLocator, grid_panel_), "");

struct stCD_UiItemTips : stCD_UiObjBase{
	stCD_ItemTipsParams* FillItemTipsInfo(stCD_EntityItemBased* item) const;
	const GameWString* GenAttrFormatStr(stCD_EntityItemBased* item) const;

	p_mem_placeholder(CD_DATA(g_o_items_tips2item_) - sizeof(stCD_UiObjBase));
	mutable stCD_EntityItemBased*		item_;
#ifdef VER_GJ3_
	p_mem_placeholder(4 * 3);		//==0
#elif VER_GF_
	p_mem_placeholder(4 * 3);		//==0
#endif
	GameWString							tmp_format_attr_str_;
};
static_assert(CD_DATA(g_o_items_tips2item_) == offsetof(stCD_UiItemTips, item_), "");
//static_assert(0x8d8 == offsetof(stCD_UiItemTips, tmp_format_attr_str_), "");

struct stCD_UiItemTipsUp : stCD_UiObjBase{
	stCD_UiItemTips* GetItemTips() const;
};

struct stCD_UiBottomFlask : stCD_UiObjBase{
	stCD_UiItemTipsUp* GetTipsUp() const;
	stCD_UiItemTips* GetTips() const;

	p_mem_placeholder(CD_DATA(g_o_ui_bottom_flask_tips_) - sizeof(stCD_UiObjBase));
	stCD_UiItemTips*		tips_;
	stCD_UiItemTipsUp*		tips_up_;
};
static_assert(CD_DATA(g_o_ui_bottom_flask_tips_) == offsetof(stCD_UiBottomFlask, tips_), "");

struct stCD_UiFlasksMgr : stCD_UiObjBase{
	bool UseFlask(int idx) const;
};

struct stCD_HpMpCircleValue : stCD_UiObjBase{
	p_mem_placeholder(g_so_hp_mp_circle_value_cur_max_value_ - sizeof(stCD_UiObjBase));
	pt_dword				cur_max_value_;
	pt_dword				cur_value_;
	pt_dword				full_max_value_;
	pt_dword				full_value_;
	pt_dword				max_shield_;
	pt_dword				cur_shield_;

	void DebugInfo() const;
};
static_assert(g_so_hp_mp_circle_value_cur_max_value_ == offsetof(stCD_HpMpCircleValue, cur_max_value_), "");

struct stCD_UiHpMpCircle : stCD_UiObjBase{
	void DebugInfo() const;
	stCD_HpMpCircleValue* GetUiValue() const;
};

//����Ѫ������ҩƿ�����ܵ�UI
struct stCD_UiBottom : stCD_UiObjBase{
	void DebugInfo() const;
	stCD_UiObjBase* GetLeftBottomFlasks() const;
	stCD_UiFlasksMgr* GetFlasksMgr() const;
	stCD_UiObjBase* GetFlasks() const;
	stCD_UiBottomFlask* GetFirstFlask() const;
	stCD_UiItemTips* GetFirstTips() const;
	stCD_UiHpMpCircle* GetHpCircle() const;
	stCD_UiHpMpCircle* GetMpCircle() const;
	stCD_UiButton* GetBtSkipAllTutorials() const;
};

//�����Ի�����ȷ����ť�����֣�����ʾ�򾯸�����á�
struct stCD_DlgInteraction : stCD_UiObjBase{
	p_mem_placeholder(CD_DATA(g_o_dlg_interaction_sub_ui_) - sizeof(stCD_UiObjBase));
	stCD_UiObjBase*			ui_container_;			//������ЩUI������
	stCD_UiLabel*			dlg_title_;
	stCD_UiLabel*			dlg_content_;
	stCD_UiObjBase*			bt_cancel_;
	stCD_UiObjBase*			bt_ok_;

	void DebugInfo() const;
	stCD_UiLabel* GetUiTitle() const;
	stCD_UiLabel* GetUiContent() const;
	bool EqualDlgTitle(const std::wstring& title) const;
	bool EqualDlgContent(const std::wstring& content) const;
};
static_assert(CD_DATA(g_o_dlg_interaction_sub_ui_) == offsetof(stCD_DlgInteraction, ui_container_), "");

struct stCD_UiButton : stCD_UiObjBase{
	stCD_UiLabel* GetUiLabel() const;
	bool EqualTitle(const std::wstring& title) const;
};

struct stCD_UiTutorials : stCD_UiObjBase{

};

struct stCD_UiContainerPicInfo{
	struct stPicRenderInfo{
		GameWString			pic_path_;
		stRectInt			pos_;
	};
	struct stPicInfo{
		stPicRenderInfo		pic_back_;		//����ͼƬ��
		stPicRenderInfo		pic_;
	};
	typedef stCD_PairAdjacent<stPicInfo, void> SmartPtr;

	pt_pcvoid			vtbl_;
	SmartPtr			pic_;
};

//vtbl=g_a_ui_dlg_tab_vtbl_
struct stCD_UiContainer : stCD_UiObjBase{
	p_mem_placeholder(CD_DATA(g_o_ui_contianer_pic_info_) - sizeof(stCD_UiObjBase));
	stCD_UiContainerPicInfo		pic_info_;

	const GameWString* GetPicPath() const;
	bool IsTrialComplete() const;
};
static_assert(CD_DATA(g_o_ui_contianer_pic_info_) == offsetof(stCD_UiContainer, pic_info_), "");

struct stCD_UiLabyrinthListItem : stCD_UiObjBase{
	struct stTrialInfo{
		stCD_DataLabyrinthTrialsPair		trial_;
		stCD_UiContainer*					ui_ball_;		//vtbl=g_a_ui_dlg_tab_vtbl_

		bool IsCompleted() const;
	};
	typedef GameVector<stTrialInfo> TrialInfoCont;
	struct stMyTrialInfo{
		stCD_DataLabyrinthTrials*		data_trial_;
		stCD_TblItemWorldArea*			world_area_;
		bool							is_completed_;

		void DebugInfo() const;
	};
	typedef std::vector<stMyTrialInfo> MyTrialInfoCont;

	p_mem_placeholder(CD_DATA(g_o_labyrinth_item2data_labyrinth_) - sizeof(stCD_UiObjBase) - 4);
	p_mem_placeholder(1);		//bool
	pt_bool						is_actived_;
	p_mem_placeholder(2);		//bool
	stCD_DataLabyrinthsPair		data_labyrinths_;
	stCD_UiObjBase*				ukn_ui_;
	TrialInfoCont				trial_info_cont_;

	stCD_UiLabel* GetLabelTitle() const;
	stCD_UiLabel* GetLabelLvl() const;
	stCD_UiLabel* GetLabelCost() const;
	stCD_UiObjBase* GetUiBalls() const;
	bool IsActived() const;
	MyTrialInfoCont GetTrialInfoCont(enCD_GetLabyrinthTrialFlag flag) const;
	void DebugInfo() const;

private:
	stCD_UiLabel* GetUiLabelByIdx(int idx) const;
};
static_assert(CD_DATA(g_o_labyrinth_item2data_labyrinth_) == offsetof(stCD_UiLabyrinthListItem, data_labyrinths_), "");

struct stCD_UiLabyrinthList : stCD_UiObjBase{
	struct stListItem{
		stCD_UiLabyrinthListItem*			ui_item_;
		pt_dword							id_;		//�Թ�id����1��ʼ
	};
	typedef std::function<bool(stListItem*)> Fn_TraListItem;
	typedef stCD_PairAdjacent<stListItem, void> SmartPtr;
	static_assert(8 == sizeof(SmartPtr), "");
	typedef GameVector<SmartPtr> ListItems;
	typedef std::vector<stCD_UiLabyrinthListItem*> ListItemCont;

	p_mem_placeholder(CD_DATA(g_o_labyrinth_list_items_) - sizeof(stCD_UiObjBase));
	ListItems			list_items_;
	pt_pcvoid			ukn_ptr_;
	pt_dword			cur_selected_;			//��ǰѡ����Թ�

	ListItemCont GetListItems(bool must_actived) const;
	bool SelectItem(const stListItem* item);
	void DebugInfo() const;
	int TraListItem(const Fn_TraListItem& fn) const;
};
static_assert(CD_DATA(g_o_labyrinth_list_items_) == offsetof(stCD_UiLabyrinthList, list_items_), "");

struct stCD_DlgLabyrinthSelect : stCD_UiObjBase{
	p_mem_placeholder(CD_DATA(g_o_labyrinth_select_list_) - sizeof(stCD_UiObjBase));
	stCD_UiLabyrinthList*			list_;
	stCD_UiObjBase*					ui_bt_container_;		//vtbl=g_a_ui_dlg_tab_vtbl_
	stCD_UiButton*					bt_active_;

	void DebugInfo() const;
	bool PressActive() const;
};
static_assert(CD_DATA(g_o_labyrinth_select_list_) == offsetof(stCD_DlgLabyrinthSelect, list_), "");

//��3�³����������
struct stCD_DlgTrialPlaque : stCD_UiObjBase{
	typedef GameVector<stCD_UiContainer*> UiContainerCont;
	struct stMyTrialInfo{
		stCD_DataLabyrinthTrials*		data_trial_;
		stCD_TblItemWorldArea*			world_area_;
		bool							is_complete_;

		void DebugInfo() const;
	};
	typedef std::vector<stMyTrialInfo> MyTrialInfoCont;

	p_mem_placeholder(CD_DATA(g_o_TrialPlaque2Labyrinths_) - sizeof(stCD_UiObjBase));
	stCD_DataLabyrinthsPair		data_labyrinth_;
	stCD_UiObjBase*				ukn_ui_obj_;
	UiContainerCont				ui_balls_;

	//��ǰ��������Թ���Ϣ
	stCD_DataLabyrinths* GetDataLabyrinth() const;
	MyTrialInfoCont GetTrialInfoCont() const;
	void DebugInfo() const;
};
static_assert(CD_DATA(g_o_TrialPlaque2Labyrinths_) == offsetof(stCD_DlgTrialPlaque, data_labyrinth_), "");

struct stCD_DlgInstanceMgr : stCD_UiObjBase{
	//-1��ʾ����һ������ʵ��
	bool SelectInstance(int instance_idx) const;
};

struct stCD_UiLabyrinthMapConnectItem : stCD_UiObjBase{

};

struct stCD_DlgLabyrinthMap : stCD_UiObjBase{
	typedef GameVector<stCD_UiLabyrinthMapConnectItem*> MapConnectionUiItems;

	//p_mem_placeholder(CD_DATA(g_o_labyrinth_map_ui_connections_) - sizeof(stCD_UiObjBase));
	MapConnectionUiItems		ui_map_connections_;		//$94c
};
//static_assert(CD_DATA(g_o_labyrinth_map_ui_connections_) == offsetof(stCD_DlgLabyrinthMap, ui_map_connections_), "");

/*
ƫ��$8c4����ŵ���stCD_SceneInGameState*��
*/
struct stCD_InGameMainUi : stCD_UiObjBase{
	p_mem_placeholder(CD_DATA(g_o_main_ui_get_in_game_state_) - sizeof(stCD_UiObjBase));
	stCD_SceneInGameState*		in_game_state_;
	p_mem_placeholder(CD_DATA(g_o_main_ui2ui_dark_panel_) - 4 - CD_DATA(g_o_main_ui_get_in_game_state_));
	stCD_UiObjBase*				ui_dark_panel_;
	p_mem_placeholder(CD_DATA(g_o_main_ui2ui_your_passive_skill_) - 4 - CD_DATA(g_o_main_ui2ui_dark_panel_));
	stCD_DlgInteraction*		dlg_modal_;				//ģ̬�Ի��򣬱��� �츳�����þ��� û���㹻�ĸ���ͨ�� ��
	p_mem_placeholder(CD_DATA(g_o_main_ui_died_panel_) - 4 - CD_DATA(g_o_main_ui2ui_your_passive_skill_));
	stCD_UiObjBase*				ui_died_panel_;			//�˴��ܿ�����������壬ֻ�ǲ²�
	stCD_UiObjBase*				ui_at_city_;
	stCD_UiObjBase*				ui_at_record_;
	stCD_UiObjBase*				ui_at_died_;

	//////////////////////////////////////////////////////////////////////////
	//*********************�����ǻ�öԻ������֮��ĺ���
	//���͵���弴�����ͼ���
	stCD_DlgWaypoint* GetDlgWaypoint() const;
	stCD_UiNpcPanelContainer* GetNpcPanelContainer() const;
	stCD_UiNpcPanel* GetNpcPanel(bool must_shown) const;
	stCD_UiDlgQuestAward* GetDlgQuestAward() const;
	stCD_UiMouseAttachItem* GetMouseAttachItem() const;
	//�ܹ������������Ķ��󡣵�1���� ��������������� ֮���ui����2����֪����ɶ��
	stCD_UiRightMostPanel* GetRightMostPanel(enCD_RightMostPanel idx) const;
	stCD_UiQuestLvlStatePanel* GetQuestLvlStatePanel() const;
	stCD_UiDiedPanel* GetDiedPanel() const;
	//����츳�� ��壬���������֣��������������츳������
	//û���㹻�ĸ���ͨ��
	stCD_DlgInteraction* GetDlgModal() const;
	//�����������ʾ�ŵģ���ô��Ϸ����ͻ��ԵñȽϺڣ�һ����ʾģ̬�Ի����ʱ������������� ����츳�� �Ի��򵯳���ʱ��
	stCD_UiObjBase* GetDarkPanel() const;
	stCD_UiMap* GetUiMap() const;
	//����������Ʒ����Ʒ�������NPC�ȵı���ȡ�
	stCD_UiEntityDescTop* GetEntityDescTop() const;
	//�ֿ�
	stCD_DlgStash* GetDlgStash() const;
	//�������
	stCD_DlgBuy* GetDlgBuy() const;
	//�������
	stCD_DlgSell* GetDlgSell() const;
	//�������
	stCD_DlgProp* GetDlgProp() const;
	//�츳��
	stCD_DlgPassiveSkill* GetDlgPassiveSkill() const;
	//buff
	stCD_UiBuff* GetUiBuff() const;
	//��ͼ������
	stCD_DlgMapLocator* GetDlgMapLocator() const;
	//�����ĵ�ͼ������
	stCD_DlgSelfMapLocator* GetDlgSelfMapLocator() const;
	stCD_UiBottom* GetUiBottom() const;
	stCD_UiTutorials* GetUiTutorials() const;
	//�Թ��Ѷ�ѡ��Ի���
	stCD_DlgLabyrinthSelect* GetDlgLabyrinthSelect() const;
	//��3�³����������
	stCD_DlgTrialPlaque* GetDlgTrialPlaque() const;
	//instance manager,��������
	stCD_DlgInstanceMgr* GetDlgInstanceMgr() const;
	//�Թ���ͼ������ͼ�Ż��������ӵ��Ǹ��Ի���
	stCD_DlgLabyrinthMap* GetDlgLabyrinthMap() const;
	//////////////////////////////////////////////////////////////////////////
	//****************�����ǹ��ܺ���
	int GetDlgCnt(enCD_TraUiShownFlag show_flag) const;
	//�ر�������壬���˷��ؽ�ɫ��壬��Ϊ������EscapeState�еġ�
	//��һ��esc����ر����д򿪵����
	bool EscapePanel() const;
	bool CloseNpcPanel() const;
	//�ڼ�¼�㸴��
	bool Revive(enCD_ReviveAtPosition at_position) const;
	bool CloseDlgModal();
	bool CloseDarkPanel() const;
	void SkipAllTutorials();
	//////////////////////////////////////////////////////////////////////////
	void DebugAddrInfo() const;
};
static_assert(CD_DATA(g_o_main_ui_get_in_game_state_) == offsetof(stCD_InGameMainUi, in_game_state_), "");
static_assert(CD_DATA(g_o_main_ui2ui_dark_panel_) == offsetof(stCD_InGameMainUi, ui_dark_panel_), "");
static_assert(CD_DATA(g_o_main_ui2ui_your_passive_skill_) == offsetof(stCD_InGameMainUi, dlg_modal_), "");
static_assert(CD_DATA(g_o_main_ui_died_panel_) == offsetof(stCD_InGameMainUi, ui_died_panel_), "");

//����ui�Ǹ���������һ����uiһֱû����ui���ڶ�����ui��main UI��main UI�Ǹ��������������ui��һЩ�Ի���֮��ġ�
//����UI���ǣ�g_a_ui_dlg_tab_vtbl_�����͡�
struct stCD_InGameTopUi : stCD_UiObjBase{
	stCD_InGameMainUi* GetMainUi() const;
};

//��Ϸ�ڵ�escape menu
struct stCD_UiEscapeMenuInner : stCD_UiObjBase{};

struct stCD_EscapeMenu : stCD_UiObjBase{
	stCD_UiObjBase* FindButton(enCD_EscapeMenuButton bt_idx) const;
};

struct stCD_EscapeTopUi : stCD_UiObjBase{
	stCD_UiObjBase* GetMenuCotainer() const;
	stCD_EscapeMenu* GetMenu() const;
};
//////////////////////////////////////////////////////////////////////////
struct stCD_CurUsingSkillInfo{
	p_mem_placeholder(4 * 3);
	pt_word			cur_skill_id_;
	p_mem_placeholder(2);
};

struct stCD_MapConnectionInfo{
	stCD_UknGameVector			ukn_vector_;
	p_mem_placeholder(4);
	enCD_EnterMapUknId			ukn_dw_;			//stCDS_EnterMap������Ҫ
	GameWString					connection_key_;	//kMIS_EnterMapConnection������Ҫ
};

//world_���治Զ��������Ŵ��������֣�$+B4  UNICODE "��϶����"
struct stCD_GameLogic{
	p_mem_placeholder(CD_DATA(g_o_game_session_packet_) - 4);
	stCD_World*						world_;		//��send_packet_��������ŵġ�
	stCD_Socket*					send_packet_;
	p_mem_placeholder(4);
	stCD_MapConnectionInfo*			map_connection_info_;		//�л���ͼʱ�Ż���ֵ������Ϊ��
	p_mem_placeholder(4);		//vtbl
	p_mem_placeholder(4);		//pt_pcvoid
	stCD_SocketsMgr					sockets_mgr_;		//�����հ���Ӧ�û���������
	stCD_PassiveSkillGraphMgr		passive_skill_;
	p_mem_placeholder(g_so_cur_using_skill_info_ - CD_DATA(g_o_get_passive_skill_) - sizeof(stCD_PassiveSkillGraphMgr));
	stCD_CurUsingSkillInfo			cur_using_skill_info_;
	p_mem_placeholder(CD_DATA(g_o_logic_get_bag_) - g_so_cur_using_skill_info_ - sizeof(stCD_CurUsingSkillInfo));
	stCD_InventoryMgr				inventory_mgr_;

	void DebugInfo() const;
	//�򿪴��͵� npc �򿪲ֿ� ��ȡ��Ʒ ������
	bool DoTouchTargetObj(enCD_SkillId flag, pt_dword net_id, enCD_TouchTargetSmallFlag small_flag) const;
	//�����������ݻ���Ʒ���ײ�ᷢ����
	//Ӧ���Ǵ����첽��������Ҫ�ȴ����ؽ���Ĳ����İɡ�����ݻ���Ʒ������Ʒ���ȵ����������ȷ�ϣ��Ż���Ĵݻ���Ʒ
	bool OperateCommand(const stCD_SafeGameWString* command) const;
	void TerminateCurUsingSkill() const;
	bool UseItemTo(enCD_InventoryType inventory_src, pt_dword item_id_src, enCD_InventoryType inventory_dst, pt_dword item_id_dst) const;

	static bool is_self_operate_command;
	static bool enable_ignore_operate_command;
};
static_assert(CD_DATA(g_o_game_session_packet_) == offsetof(stCD_GameLogic, send_packet_), "");
static_assert(g_so_sockets_mgr_ == offsetof(stCD_GameLogic, sockets_mgr_), "");
//static_assert(g_so_sockets_mgr_ == 0x3aac, "");
static_assert(CD_DATA(g_o_get_passive_skill_) == offsetof(stCD_GameLogic, passive_skill_), "");
static_assert(g_so_cur_using_skill_info_ == offsetof(stCD_GameLogic, cur_using_skill_info_), "");
static_assert(CD_DATA(g_o_cur_using_skill_id_) == g_so_cur_using_skill_info_ + offsetof(stCD_CurUsingSkillInfo, cur_skill_id_), "");
static_assert(CD_DATA(g_o_logic_get_bag_) == offsetof(stCD_GameLogic, inventory_mgr_), "");

//��Ϸ����
struct stCD_GameArea{
	pt_cwsz			ptr_area_name_;		//ָ��area_name_.c_str()
	pt_dword		name_size_;
	GameWString		area_name_;
	p_mem_placeholder(g_sv_game_area_size_ - 8 - sizeof(GameWString));
};
static_assert(g_sv_game_area_size_ == sizeof(stCD_GameArea), "");
typedef GameVector<stCD_GameArea> stCD_GameAreaCont;
//////////////////////////////////////////////////////////////////////////
struct stCD_GatewayInfo{
	GameWString				short_name_;
	GameWString				name_;
	stCD_UknGameVector		ukn_vector_;
	p_mem_placeholder(4 * 7);

	void DebugInfo() const;
};
static_assert(g_so_login_state_gateway_info_size_ == sizeof(stCD_GatewayInfo), "");

struct stCD_UiLoginGateway : stCD_UiObjBase{
	stCD_UiEdit* GetEditGateway() const;
};
//////////////////////////////////////////////////////////////////////////

//��½�����������б����ص��ˣ����ʷ��в������
//stCD_SceneLoginState�����UI��ʵ��������stCD_ScenePreGameState�ģ�stCD_SceneLoginState�������߼���stCD_ScenePreGameState������Ⱦ��
struct stCD_SceneLoginState : stCD_SceneBase{
	typedef GameVector<stCD_GatewayInfo> GatewayInfoCont;

	p_mem_placeholder(g_so_login_state_bt_login_ - sizeof(stCD_SceneBase));
	stCD_UiObjBase*			bt_login_;
	stCD_UiObjBase*			ukn_obj_;
	stCD_UknGameVector		gateway_ping_info_;				//ASCII "path_of_exile_gateway_ping"
	stCD_UknGameVector		ukn_vector_;
	GatewayInfoCont			gateway_info_;
	stCD_UiLoginGateway*	gateway_;
	pt_bool					is_pop_gateway_panel_;
	p_mem_placeholder(3);
	pt_dword				pop_gateway_tick_count_;		//==GetTickCount() + 0x5dc��ÿ�ε���gateway����ı�һ��
	pt_dword				ukn_dw_;						//=0
	stCD_UiObjBase*			ukn_objs_[4];
	stCD_UiEdit*			edit_pwd_;
	p_mem_placeholder(g_so_login_state_edit_ac_ - g_so_login_state_edit_pwd_ - 4);
	stCD_UiEdit*			edit_ac_;

	stCD_UiEdit* GetEditAc() const;
	stCD_UiEdit* GetEditPwd() const;
	stCD_UiEdit* GetEditGateway() const;
	bool InputLoginInfo(const std::wstring& ac, const std::wstring& pwd, const std::wstring& gateway);
	bool PressBtLogin() const;
	void DebugInfo() const;
};
static_assert(g_so_login_state_bt_login_ == offsetof(stCD_SceneLoginState, bt_login_), "");
static_assert(g_so_login_state_list_gateway_ == offsetof(stCD_SceneLoginState, gateway_), "");
static_assert(g_so_login_state_edit_pwd_ == offsetof(stCD_SceneLoginState, edit_pwd_), "");
static_assert(g_so_login_state_edit_ac_ == offsetof(stCD_SceneLoginState, edit_ac_), "");

//ѡ�������������ɫ��ʱ��Ż�����������
struct stCD_SceneCreateCharacterState : stCD_SceneBase{
	//�����enCD_ProfessionType��ʵ��4���ֽ�
	typedef stCD_GameHash_map<stCD_UiCreateRole_Character*, enCD_ProfessionType> CharacterCont;

	pt_pcvoid						vtbl1_;
	pt_pcvoid						ukn_ptr_;
	//�������ui�����������Ӳ��֣�1.������ɫ��ui��λ�����Ϸ���2.�����·�ѡ������Ҫʹ�õĽ�ɫ.3.���ذ�ť
	stCD_UiObjBase*					ui_select_character_at_bottom_;			//vtbl = g_a_ui_dlg_tab_vtbl_
	p_mem_placeholder(4 * 2);
	stCD_GameAreaCont				game_areas_;
	p_mem_placeholder(g_so_create_role_name_edit_ - sizeof(stCD_GameAreaCont) - 0x34);
	stCD_UiEdit*					name_edit_;
	p_mem_placeholder(CD_DATA(g_o_CreateCharacterState_cancel_bt_) - g_so_create_role_name_edit_ - 4);
	stCD_UiObjBase*					buttons_[kCRBI_Max];
	stCD_UiObjBase*					ui_areas_;			//���������������ߡ�������(ר��)����������
	pt_dword						cur_area_idx_;		//��ǰѡ��Ĵ���
	/*CharacterCont					characters_;
	stCD_UiCreateRole_Character*	cur_character_;		//Ҫ�����Ľ�ɫ/ְҵ*/
	stCD_UiObjBase*					ui_character_profession_type_;			//ѡ��Ҫ������ĳ����ɫ�����������ʾ�ý�ɫ��ְҵ��Ϣ
	stCD_UiObjBase*					ui_character_desc_;						//��ɫ��ϸ˵��������
	stCD_UiObjBase*					ui_character_short_movie_;				//��ɫ����Ƶ
	stCD_CharactersPair				data_cur_characters_;

	stCD_UiEdit* GetNameEdit() const;
	bool SelectGameArea(const stCD_GameArea& game_area);
	bool SelectCharacter(enCD_ProfessionType profession_type) const;
	bool InputRoleName(const std::wstring& role_name);
	bool PressButton(enCD_CreateRoleBtIdx bt_idx) const;
	//�����·�ѡ������Ҫʹ�õĽ�ɫ ����
	bool IsSelectCharacterAtBottom() const;
	void DebugInfo() const;
};
static_assert(0x34 == offsetof(stCD_SceneCreateCharacterState, game_areas_), "");
static_assert(g_so_create_role_name_edit_ == offsetof(stCD_SceneCreateCharacterState, name_edit_), "");
static_assert(CD_DATA(g_o_CreateCharacterState_cancel_bt_) == offsetof(stCD_SceneCreateCharacterState, buttons_), "");
//static_assert(g_so_create_role_cur_area_idx == offsetof(stCD_SceneCreateCharacterState, cur_area_idx_), "");
//static_assert(g_so_create_role_cur_character_ == offsetof(stCD_SceneCreateCharacterState, cur_character_), "");
static_assert(0xa4 == offsetof(stCD_SceneCreateCharacterState, data_cur_characters_), "");

struct stCD_SceneSelectCharacterState : stCD_SceneBase{
	p_mem_placeholder(CD_DATA(g_o_ui_select_role_top_) - sizeof(stCD_SceneBase));
	stCD_UiSelectRoleTop*		select_role_;

	bool PressCreateRole() const;
	stCD_UiSelectRoleTop* GetUiSelectRole() const;
};
static_assert(CD_DATA(g_o_ui_select_role_top_) == offsetof(stCD_SceneSelectCharacterState, select_role_), "");

struct stCD_CharacterCreationInfo{
	stCD_Vtbl_CharacterCreationInfo*		vtbl_;

	bool SelectCharacter(enCD_ProfessionType profession_type) const;
};

struct stCD_ScenePreGameState : stCD_SceneBase{
	stCD_UiObjBase*					modal_dark_panel_;
	stCD_DlgInteraction*			cur_shown_dlg_modal_;		//��ʾ��ʱ��˴�����ֵ
	stCD_LoginLogic*				logic_;
	p_mem_placeholder(4);			//pt_pcvoid
	p_mem_placeholder(4);			//=0,$30
	p_mem_placeholder(4);			//vtbl
	stCD_CharacterCreationInfo*		character_info_;			//$38
#ifndef VER3_
	p_mem_placeholder(4);			//pt_pcvoid
#endif
	stCD_StateUiLogic				ui_logic_;
	p_mem_placeholder(CD_DATA(g_o_pre_in_game_state_dlg_modal_) - g_so_pre_game_state_main_ui_ - sizeof(stCD_StateUiLogic));
	stCD_DlgInteraction*			dlg_modal_;

	stCD_UiPreInGameTop* GetTopUi() const;
	bool CloseDlgModal();
	bool CloseDarkPanel() const;
	stCD_DlgInteraction* GetDlgModal() const;
	stCD_UiObjBase* GetDarkPanel() const;
	bool SelectCharacter(enCD_ProfessionType profession_type) const;
	void DebugInfo() const;
};
static_assert(0x24 == offsetof(stCD_ScenePreGameState, cur_shown_dlg_modal_), "");
static_assert(g_so_character_creation_info_ == offsetof(stCD_ScenePreGameState, character_info_), "");
static_assert(g_so_packet_holder1_send_packet_ == offsetof(stCD_ScenePreGameState, logic_), "");
static_assert(g_so_pre_game_state_main_ui_ == offsetof(stCD_ScenePreGameState, ui_logic_), "");
static_assert(CD_DATA(g_o_pre_in_game_state_dlg_modal_) == offsetof(stCD_ScenePreGameState, dlg_modal_), "");

struct stCD_SceneEscapeState : stCD_SceneBase{
	stCD_StateUiLogic		ui_logic_;

	stCD_EscapeTopUi* GetTopUi() const;
	stCD_EscapeMenu* GetMenu() const;
	stCD_UiObjBase* FindButton(enCD_EscapeMenuButton bt_idx) const;
	bool PressBtItem(enCD_EscapeMenuButton bt_idx) const;
};
static_assert(g_so_escape_state_get_ui_logic_ == offsetof(stCD_SceneEscapeState, ui_logic_), "");

struct stCD_SceneInGameState : stCD_SceneBase{
	p_mem_placeholder(g_so_get_game_session_ - sizeof(stCD_SceneBase) - 4);
	pt_pcvoid				ukn_ptr_;
	stCD_GameLogic*			logic_;
	pt_dword				ukn_dw_;
	stCD_GameLogic*			tmp_logic_;			//��ʼ����ͼ��ʱ���õ�����ʼ��������0��
	p_mem_placeholder(CD_DATA(g_o_in_game_state2ui_mgr_) - g_so_get_game_session_ - 4 * 3);
	stCD_StateUiLogic		ui_logic_;
	p_mem_placeholder(CD_DATA(g_o_get_cur_skill_type_info_) - CD_DATA(g_o_in_game_state2ui_mgr_) - sizeof(stCD_StateUiLogic) - 4);
	stCD_SkillTypeInfo*		using_skill_;				//(int)cur_using_skill_end_ - (int)using_skill_ == sizeof(stCD_SkillTypeInfo)
	stCD_SkillTypeInfo*		cur_using_skill_end_;		//��ǰѡ���
	stCD_SkillTypeInfo*		using_skill_end_;
	p_mem_placeholder(CD_DATA(g_o_get_down_inventory_mgr_) - CD_DATA(g_o_get_cur_skill_type_info_) - 8);
	stCD_DownInventoryMgr*	inventory_mgr_;

	stCD_InGameTopUi* GetTopUi() const;
	//�л���EscapeState���൱�ڴ��˷��ؽ�ɫ���
	bool SwitchToEscapeState() const;
	stCD_SkillTypeInfo* GetLastUsedSkill() const;
	stCD_SkillTypeInfo* GetCurUsingSkill() const;
	void DebugInfo() const;
};
static_assert(g_so_get_game_session_ == offsetof(stCD_SceneInGameState, logic_), "");
static_assert(CD_DATA(g_o_in_game_state2ui_mgr_) == offsetof(stCD_SceneInGameState, ui_logic_), "");
static_assert(CD_DATA(g_o_get_cur_skill_type_info_) == offsetof(stCD_SceneInGameState, cur_using_skill_end_), "");
static_assert(CD_DATA(g_o_get_down_inventory_mgr_) == offsetof(stCD_SceneInGameState, inventory_mgr_), "");
//////////////////////////////////////////////////////////////////////////
struct stCD_UiSelectRole_BtBeginGame : stCD_UiObjBase{};

struct stCD_stCD_UiRoleListItem : stCD_UiObjBase{
	p_mem_placeholder(CD_DATA(g_o_ui_role_list_item_name_) - 4 - sizeof(GameWString) - sizeof(stCD_UiObjBase));
	GameWString		ser_area_;			//����
	pt_dword		ukn_dw_;
	GameWString		role_name_;			//��ɫ��

	std::string GetSerArea() const;
	std::string GetRoleName() const;
	void DebugInfo() const;
};
static_assert(CD_DATA(g_o_ui_role_list_item_name_) == offsetof(stCD_stCD_UiRoleListItem, role_name_), "");

struct stCD_stCD_UiSelectRoleListItems : stCD_UiObjBase{
	typedef std::function<bool(stCD_stCD_UiRoleListItem*)> Fn_TraRoleItem;

	int TraRoleItems(const Fn_TraRoleItem& fn) const;
};

struct stCD_UiSelectRoleList : stCD_UiObjBase{
	typedef stCD_PairAdjacent<stCD_stCD_UiRoleListItem*, pt_void> ItemPair;
	typedef GameVector<ItemPair> ListItemCont;
	typedef stCD_stCD_UiSelectRoleListItems::Fn_TraRoleItem Fn_TraRoleItem;

	int TraRoleItems(const Fn_TraRoleItem& fn) const;
	bool SetCurSelectItem(const stCD_stCD_UiRoleListItem* item);
	stCD_stCD_UiSelectRoleListItems* GetUiListItems() const;
	void DebugInfo() const;

	p_mem_placeholder(CD_DATA(g_o_ui_role_list_items_) - sizeof(stCD_UiObjBase));
	ListItemCont		list_items_;
	pt_pcvoid			ukn_ptr_;
	pt_dword			cur_selected_;
};
static_assert(CD_DATA(g_o_ui_role_list_items_) == offsetof(stCD_UiSelectRoleList, list_items_), "");
//static_assert(0xb08 == offsetof(stCD_UiSelectRoleList, cur_selected_), "");

//������ɾ������ʼ��Ϸ
struct stCD_UiSelectRoleOper : stCD_UiObjBase{
	void DebugInfo() const;
	//������Ҫʵ�ָú���
	stCD_UiSelectRole_BtBeginGame* GetBtBeginGame() const;
};

struct stCD_UiSelectRoleUpContent : stCD_UiObjBase{
	stCD_UiSelectRoleList* GetRoleList() const;
	stCD_UiSelectRoleOper* GetRoleOper() const;

	void DebugInfo() const;
};

struct stCD_UiSelectRoleUpPart : stCD_UiObjBase{
	stCD_UiSelectRoleUpContent* GetContent() const;

	void DebugInfo() const;
};

struct stCD_UiSelectRoleContainer : stCD_UiObjBase{
	stCD_UiSelectRoleUpPart* GetUpPart() const;

	void DebugInfo() const;
};

struct stCD_UiSelectRoleContainerTop : stCD_UiObjBase{
	stCD_UiSelectRoleContainer* GetContainer() const;

	void DebugInfo() const;
};

struct stCD_UiSelectRoleTop : stCD_UiObjBase{
	typedef stCD_UiSelectRoleList::Fn_TraRoleItem Fn_TraRoleItem;

	stCD_UiSelectRoleContainerTop* GetContainerTop() const;
	int TraRoleItems(const Fn_TraRoleItem& fn) const;
	bool EnterGame(const stCD_stCD_UiRoleListItem* item) const;
	void DebugInfo() const;

	p_mem_placeholder(CD_DATA(g_o_ui_bt_begin_game_) - sizeof(stCD_UiObjBase));
	stCD_UiSelectRole_BtBeginGame*		bt_begin_game_;
	p_mem_placeholder(CD_DATA(g_o_role_list_) - CD_DATA(g_o_ui_bt_begin_game_) - 4);		//��Щ����uiָ��
	stCD_UiSelectRoleList*				role_list_;
};
static_assert(CD_DATA(g_o_ui_bt_begin_game_) == offsetof(stCD_UiSelectRoleTop, bt_begin_game_), "");
static_assert(CD_DATA(g_o_role_list_) == offsetof(stCD_UiSelectRoleTop, role_list_), "");

struct stCD_DlgSelectRole : stCD_UiObjBase{
	stCD_UiSelectRoleTop* GetTopUi() const;

	void DebugInfo() const;
};
//////////////////////////////////////////////////////////////////////////
struct stCD_UiSelectAreas : stCD_UiObjBase{

};

//ȡ��/ȷ��
struct stCD_UiSelectAreaOpers : stCD_UiObjBase{
};

struct stCD_UiSelectAreaTop : stCD_UiObjBase{
	stCD_UiSelectAreas* GetUiAreas() const;
	stCD_UiSelectAreaOpers* GetUiOpers() const;
};

struct stCD_EditString{
	pt_pcvoid				vtbl_;
	p_mem_placeholder(CD_DATA(g_o_edit_string2string_) - 4);
	stCD_SafeGameWString	string_;

	bool SetString(const std::wstring& new_str);
};
static_assert(CD_DATA(g_o_edit_string2string_) == offsetof(stCD_EditString, string_), "");

struct stCD_UiEdit : stCD_UiObjBase{
	p_mem_placeholder(CD_DATA(g_o_edit_string_) - sizeof(stCD_UiObjBase));
	stCD_EditString		edit_string_;

	bool SetString(const std::wstring& new_str);
};
static_assert(CD_DATA(g_o_edit_string_) == offsetof(stCD_UiEdit, edit_string_), "");

struct stCD_UiCreateRole_Character : stCD_UiObjBase{

};

struct stCD_UiCreateRoleTop : stCD_UiObjBase{
};

struct stCD_DlgCreateRole : stCD_UiObjBase{
	stCD_UiSelectAreaTop* GetSelectAreaTop() const;
	stCD_UiCreateRoleTop* GetCreateRoleTop() const;
};
//////////////////////////////////////////////////////////////////////////
struct stCD_UiPreInGameTop : stCD_UiObjBase{
	stCD_DlgSelectRole* GetDlgSelectRole() const;
	stCD_DlgCreateRole* GetDlgCreateRole() const;
};
//////////////////////////////////////////////////////////////////////////
struct stCD_ProcessCommandOption{
	GameWString		command_;		//ȫ��
	GameWString		cmd_;			//���
	GameWString		desc_;			//��������
	pt_dword		ukn_dw_;
	pt_dword		ukn_dw1_;

	void DebugInfo(const GameWString& key) const;
};
typedef stCD_PairAdjacent<stCD_ProcessCommandOption, void> stCD_ProcessCommandOptionSmartPtr;
typedef stCD_GameHash_map<GameWString, stCD_ProcessCommandOptionSmartPtr> stCD_ProcessCommandOptionMap;

struct stCD_ProcessCommands{
	p_mem_placeholder(0x1c);
	stCD_ProcessCommandOptionMap	commands_;

	void DebugInfo() const;
};

struct stCD_ProcessInfo{
	p_mem_placeholder(0x18);
	stCD_ProcessCommands*		process_commands_;			//ָ���ջ��ַ

	void DebugInfo() const;
};
//////////////////////////////////////////////////////////////////////////
struct stCD_GameBase{
	typedef GameVector<stCD_UknBase*> GameStateContT;

	p_mem_placeholder(g_so_game_base2ui_obj_);
	GameStateContT		game_state_cont_;	//(char*)begin_ + ���0x20������һ��wchar_t�ַ�������ŵ���dds�ļ������磺"Art/2DArt/SkillIcons/passives/LustforCarnage.dds"

	stCD_GameBase() = delete;
	stCD_GameBase(const stCD_GameBase&) = delete;
	stCD_GameBase& operator = (const stCD_GameBase&) = delete;
	static stCD_GameBase& GetMe();
	stCD_SceneHolder* GetSceneHolder() const;
	stCD_SceneInGameState* GetInGameState() const;
	stCD_GameLogic* GetGameLogic() const;
	stCD_World* GetWorld() const;
	//�õ���ɫ�Լ�
	stCD_EntityPlayerMe* GetPlayerEntity() const;
	stCD_PlayerMe* GetPlayer() const;
};
static_assert(g_so_game_base2ui_obj_ == offsetof(stCD_GameBase, game_state_cont_), "");

struct stCD_GameBaseWndInfo{
	HWND			wnd_handle_;

	stCD_GameBaseWndInfo() = delete;
	stCD_GameBaseWndInfo(const stCD_GameBaseWndInfo&) = delete;
	stCD_GameBaseWndInfo& operator = (const stCD_GameBaseWndInfo&) = delete;
	static stCD_GameBaseWndInfo* GetInstance();
	void DebugInfo() const;
};

struct stCD_GameBaseDb{
	typedef stCD_GameHash_map<pt_cwsz, stCD_Db*, RStd::hash_compare<pt_cwsz, StdEx::LessChar<wchar_t> > > DbHashMap;
	typedef stCD_DbT<stCD_TblItemPassiveSkill> stCD_DbPassiveSkill;
	typedef stCD_DbT<stCD_TblItemQuestStates> stCD_DbQuestStates;
	typedef stCD_DbT<stCD_TblItemQuest> stCD_DbQuest;
	typedef stCD_DbT<stCD_TblItemActiveSkills> stCD_DbActiveSkills;

	DbHashMap		db_hash_map_;

	stCD_GameBaseDb() = delete;
	stCD_GameBaseDb(const stCD_GameBaseDb&) = delete;
	stCD_GameBaseDb& operator = (const stCD_GameBaseDb&) = delete;
	static stCD_GameBaseDb& GetMe();
	//��Ϸ�ѡ���ɫ���뵽��Ϸ��ʱ������FindDb���������Դ����ж���Ϸ�ĳ�ʼ��
	stCD_Db* FindDb(pt_cwsz db_path) const;
	template<typename DbT>
	DbT* FindDbT(pt_cwsz db_path) const{
		static DbT* the_db = nullptr;
		if (the_db) return the_db;
		auto res = FindDb(db_path);
		if (!res)
			return nullptr;
		the_db = res->CastTo<DbT>();
		if (!the_db)
		{
			assert(false);
			return nullptr;
		}
		the_db->lock();
		return the_db;
	}
	//��ò�Ҫ�����������
	stCD_DbEntity* FindDbEntity(pt_cwsz db_path) const;
	stCD_DbPassiveSkill* GetDbPassiveSkill() const;
	stCD_DbQuest* GetDbQuest() const;
	stCD_DbQuestStates* GetDbQuestStates() const;
	stCD_DbActiveSkills* GetDbActiveSkills() const;
	stCD_DbBaseItemTypes* GetDbBaseItemTypes() const;
	stCD_DbItemClasses* GetDbItemClasses() const;
	stCD_DbSkillGems* GetDbSkillGems() const;
	stCD_DbGemTags* GetDbGenTags() const;
	stCD_DbGrantedEffects* GetDbGrantedEffects() const;
	stCD_DbMapConnections* GetDbMapConnections() const;
	stCD_DbWorldArea* GetDbWorldArea() const;
	stCD_DbStats* GetDbStats() const;
	stCD_DbMapPins* GetDbMapPins() const;
	stCD_DbWeaponTypes* GetDbWeaponTypes() const;
	stCD_DbMonsterTypes* GetDbMonsterTypes() const;
	stCD_DbMonsterVarieties* GetDbMonsterVarieties() const;
	stCD_DbClientStrings* GetDbClientStrings() const;
	stCD_DbModelArmoursShields* GetModelArmoursShields() const;
	stCD_DbEnvironments* GetDbEnvironments() const;
	stCD_DbPassiveSkillGraph* GetDbPassiveSkillGraph() const;
	stCD_DbSkillStatDescriptions* GetDbSkillStatDescriptions() const;
	stCD_DbMinionSpellSkillStat* GetDbMinionSpellSkillStat() const;
	stCD_DbChests* GetDbChests() const;
};
//////////////////////////////////////////////////////////////////////////
//*********************anti check
struct stCD_ThrdParam{
	pt_pcvoid		ukn_addr_;
	pt_pcvoid		ThrdRun;
	pt_pcvoid		ukn_ptr_;

	void DebugInfo() const;
};
//////////////////////////////////////////////////////////////////////////
//*******************tmp,��ʱ�ṹ�嶨�崦
//g_c_select_map_locator_attr_��g_c_select_labyrinth_�϶���һ����������
//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)
