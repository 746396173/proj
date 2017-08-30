#pragma once
/*
@author zhp
@date 2017/2/5 13:11
@purpose for struct base
*/
#include <string>
#include <ProtocolX/P_DefinesX.h>
#include <CmnMix/Cmn_LogOut.h>
#include "CD_Offset.h"
#include "CD_Const.h"
#include <WgFacility/CmnGameStruct.h>
#include <CmnMix/Cmn_UsefulFunc.h>
#include "CD_Data.h"
#include <CommonX/CmnX_Math.h>
#include <CommonX/CmnX_Allocator.h>
#include <StdEx/XstddefEx.h>

#pragma pack(push)
#pragma pack(1)
struct stCD_Life;
struct stCD_EntityBase;
struct stCD_World;
struct stCD_EntityPlayer;
struct stCD_EntityNpc;
struct stCD_EntityWaypoint;
struct stCD_EntityAreaTransition;
struct stCD_EntityMonster;
struct stCD_AttrDbQuality;
struct stCD_AttrDbAttributeRequirements;
struct stCD_EntityAttrMods;
struct stCD_EntityAttrStack;
struct stCD_EntityAttrSockets;
struct stCD_EntityItemBased;
struct stCD_TblItemBaseItemTypes;
struct stCD_AttrDbSkillGem;
struct stCD_Render;
struct stCD_EntityNoHuman;
struct stCD_TblItemWorldArea;
struct stCD_EntityChest;
struct stCD_EntityWorldItem;
struct stCD_EntityTransitionable;
struct stCD_Actor;
struct stCD_EntityAttrUsable;
struct stCD_EntityAttrCharges;
struct stCD_EntityAttrDbFlask;
struct stCD_EntityAttrItemBase;
struct stCD_EntityAttrNPC;
struct stCD_EntityAttrClientNpc;
struct stCD_EntityAttrMonster;
struct stCD_EntityAttrDiesAfterTime;
struct stCD_EntityAttrSkillGem;
struct stCD_TblItemGrantedEffectsPerLevel;
struct stCD_EntityAttrPortal;
struct stCD_PassiveSkillVertex;
struct stCD_DbTblPassiveSkillGraph;
struct stCD_Pathfinding;
struct stCD_EntityAttrTargetable;
struct stCD_EntityAttrTransitionable;
//////////////////////////////////////////////////////////////////////////
template<typename T>
struct stCD_GameDeque{
	typedef T* pointer_type;

	pointer_type		values_;
	int					buffer_cnt_;
	pt_dword			idx_;
	int					cnt_;
};

template<class _Kty, class _Ty, 
class _Tr = RStd::hash_compare<_Kty, _STD less<_Kty> >,
class _Alloc = _STD allocator<_STD pair<const _Kty, _Ty> > >
using stCD_GameHash_map = GameHash_map<_Kty, _Ty, RStd::enXHashMemberTag::kBucketSizeFirst, _Tr, _Alloc>;
typedef stCD_GameHash_map<void*, void*> stCD_UknGameHash_map;

struct stCD_GameAllocatorImpl{
	static void* Malloc(pt_dword size);
	static void Free(void* ptr);
};
template<typename T>
using stCD_GameAllocator = CmnAllcator<T, stCD_GameAllocatorImpl>;
template<typename _Elem>
using stCD_SafeGameStringT = GameStringT<_Elem, std::char_traits<_Elem>, stCD_GameAllocator<_Elem> >;
typedef stCD_SafeGameStringT<wchar_t> stCD_SafeGameWString;
template<typename T>
using stCD_SafeVector = GameVector<T, stCD_GameAllocator<T> >;

typedef GameArray<void*> stCD_UknGameArray;
typedef GameArrayEx<void*> stCD_UknGameArrayEx;
typedef GameVector<void*> stCD_UknGameVector;
//////////////////////////////////////////////////////////////////////////
template<typename T>
using stCD_Vec2 = stCmnVec2<T>;
typedef stCD_Vec2<int> stCD_VecInt;
typedef stCD_Vec2<float> stCD_VecFloat;
typedef stCD_Vec2<pt_byte> stCD_VecByte;
typedef stCD_Vec2<pt_short> stCD_VecShort;
static_assert(sizeof(stCD_VecByte) == 2, "");
static_assert(sizeof(stCD_VecInt) == 4 * 2, "");
//////////////////////////////////////////////////////////////////////////
template<typename RealObjT, typename AboveT>
struct stCD_PairAdjacent{
	RealObjT*		real_obj_;
	AboveT*			above_part_;
};
typedef stCD_PairAdjacent<void, void> stCD_UknSmartPtr;

struct stCD_StringEnChPair{
	pt_cwsz			en_str_;		
	pt_cwsz			ch_str_;

	friend std::ostream& operator << (std::ostream& ostm, const stCD_StringEnChPair& v);
	void DebugInfo() const;
};

struct stCD_DbTblBase{
	CMN_CAST_TO
};

struct stCD_DbTblVtblBase : stCD_DbTblBase{
	pt_pcvoid					vtbl_;
};

template<typename TblItemT>
struct stCD_DbTblBaseT : stCD_DbTblVtblBase{
	typedef GameVector<TblItemT> TblItemContT;

	TblItemContT	tbl_items_;		//����Ϣ

	void DebugInfo() const{
		LOG_O(Log_debug) << "DbTblAddr:" << this;
		if (tbl_items_.IsValid())
		{
			for (auto& v : tbl_items_)
				v.DebugInfo();
			LOG_O(Log_debug) << "������" << tbl_items_.size();
		}
		else
		{
			assert(false);
		}
	}
	void DebugInfo(int counter) const{
		LOG_O(Log_debug) << "DbTblAddr:" << this;
		if (tbl_items_.IsValid())
		{
			for (auto& v : tbl_items_)
			{
				v.DebugInfo(counter);
				++counter;
			}
			LOG_O(Log_debug) << "������" << tbl_items_.size();
		}
		else
		{
			assert(false);
		}
	}
};

//ģ�ͱ��д�����ݵ�vectorû�ҵ�
template<typename TblItemT>
struct stCD_DbTblModelT : stCD_DbTblVtblBase{
	p_mem_placeholder(10 * 4);
	void DebugInfo() const{
		LOG_O(Log_debug) << "stCD_DbTblModelAddr:" << this;
	}
};

//valueһ������tips�е���ֵ
struct stCD_Value{
	enCD_ValueType		type_;
	pt_int				value_;
};
//////////////////////////////////////////////////////////////////////////
//����ṹ����Ա����ʹ��
struct stCD_ItemGridsIdxInfo{
	//������0��ʼ��
	int		left_x_idx_;		//����߸��ӵ�x����
	int		up_y_idx_;			//���ϱ߸��ӵ�y����
	int		right_x_end_idx_;	//���ұ߸��ӵ�x����+1
	int		down_y_end_idx_;	//���±߸��ӵ�y����+1

	stCD_ItemGridsIdxInfo();
	inline int GetLeftX() const{ return left_x_idx_; }
	inline int GetTopY() const{ return up_y_idx_; }
	inline int GetRightX() const{ return right_x_end_idx_ - 1; }
	inline int GetDownY() const{ return down_y_end_idx_ - 1; }
	//���
	inline int GetWidth() const{ return right_x_end_idx_ - left_x_idx_; }
	//�߶�
	inline int GetHeight() const{ return down_y_end_idx_ - up_y_idx_; }
	//��Ʒ��ռ������
	inline int GetItemGridCnt() const{ return GetWidth() * GetHeight(); }
	//������Ʒ���ӵ�������ÿ�α�������һ��������ֱ������-1
	//������õ���һ����������cursor = 0
	int TraItemGridIdx(int& cursor, int bag_width) const;
	bool IsValid() const;
	void DebugInfo() const;
};

struct stCD_GemSlot{
	typedef GameVector<pt_byte> SlotInfoContT;
	typedef enCD_GemSlotColor GemSlotVecT[CD_kGemSlotMaxCnt];

	GemSlotVecT					slot_;
	stCD_EntityItemBased*		gems_[CD_kGemSlotMaxCnt];		//��ʯ��Ƕ�ڵ�һ�������棬��ʯָ���������0����
	SlotInfoContT				slot_connect_info_;				//���������Ϣ���Ǹ����飬��һ��Ԫ�������3�����ʾǰ3�������������һ��ġ�

	stCD_GemSlot();
	//�õ��������
	int GetSlotCnt() const;
	//�õ����ò������
	int GetUsedSlotCnt() const;
	//������Ƕ�ı�ʯ
	//cursor,�α꣬��Ҫ��ͷ��ʼ��������������=0
	//�����ز�Ϊ�գ����ʱcursor=index + 1��cursor��ʾ��N����ʯ��N����СֵΪ1�����ֵΪCD_kGemSlotMaxCnt
	stCD_EntityItemBased* TraInsideGem(int& cursor) const;
	void DebugInfo() const;
};
//////////////////////////////////////////////////////////////////////////
struct stCD_LifeData{
	pt_pcvoid		vtbl_;
	pt_dword		num1_;
	pt_dword		num2_;
	stCD_Life*		parent_;
	pt_dword		max_value_;
	pt_dword		cur_value_;
	pt_dword		ukn_dw_;
	pt_dword		reserved_;		//��������������˵�����Ǳ�������ֵ��
	pt_dword		ukn_dw1_;

	stCD_LifeData();
	void DebugInfo() const;
	friend std::ostream& operator << (std::ostream& ostm, const stCD_LifeData& v);
};
static_assert(sizeof(stCD_LifeData) == 0x24, "");

#ifdef VER3_
struct stCD_LifeDataHp : stCD_LifeData{
	pt_bool			ukn_bool_;
	p_mem_placeholder(3);
};
#else
typedef stCD_LifeData stCD_LifeDataHp;
#endif

struct stCD_EntityAttrDbBase{
	pt_pcvoid		vtbl_;

	CMN_CAST_TO
};

struct stCD_EntityAttrBase{
	pt_pcvoid				vtbl_;
	stCD_EntityBase*		entity_;
	
	CMN_CAST_TO
};

//�ܶ�ʵ�����Զ������涼��һ��stCD_EntityAttrDbBaseָ�룬�еķ���0xcƫ�ƴ����еķ��ڸ����ƫ�ƴ���
struct stCD_EntityAttrBaseDb : stCD_EntityAttrBase{
	p_mem_placeholder(4);				//����player��˵�����ֵ��1�����ɴ˴���GameArray<stCD_EntityAttrDbBase>
	stCD_EntityAttrDbBase*		attr_db_;
};
//////////////////////////////////////////////////////////////////////////
struct stCD_Positioned : stCD_EntityAttrBase{
	p_mem_placeholder(g_so_positioned_pos_ - sizeof(stCD_EntityAttrBase));
	stCD_VecInt		pos_;
	p_mem_placeholder(4);
	stCD_VecFloat	float_pos_;

	void DebugInfo() const;
};
static_assert(g_so_positioned_pos_ == offsetof(stCD_Positioned, pos_), "");
static_assert(g_so_positioned_float_pos_ == offsetof(stCD_Positioned, float_pos_), "");
//////////////////////////////////////////////////////////////////////////
//���������ʽ�����
struct stCD_EntityAttrInfo{
	pt_dword					array_idx_;		//���Զ������������
};

struct stCD_DbTblEntity : stCD_DbTblVtblBase{
	//ͨ���������õ����������
	typedef stCD_GameHash_map<pt_csz, stCD_EntityAttrInfo> AttrInfoCont;
	typedef GameVector<stCD_EntityAttrDbBase*> AttrDbContT;

	p_mem_placeholder(4);
	AttrDbContT		attr_db_cont_;		//row_info_��С��stCD_EntityBase::entity_cont_һ��
	AttrInfoCont	attr_idx_;

	stCD_EntityAttrInfo* FindAttrIdxInfo(pt_csz name);
	int GetAttrCnt() const;
	void DebugInfo() const;
};
static_assert(g_so_entity_attri_db_cont_ == offsetof(stCD_DbTblEntity, attr_db_cont_), "");
static_assert(g_so_get_entity_attri_info_cont_ == offsetof(stCD_DbTblEntity, attr_idx_), "");

struct stCD_Db{
	pt_pcvoid						vtbl_;
	p_mem_placeholder(4 * 3);
	GameWString						path_;	//"Metadata/Characters/Int/Int"
	pt_dword						ukn_dw_;
	stCD_DbTblBase*					db_tbl_;	//$30
	pt_dword						ukn_dw1_;	//����stCD_Db_TblItemPairʱ�����һ��ȫ�ֱ�����ȡֵ�������ǵ���
	pt_dword						ref_cnt_;	//$38,���ݿ�����ü�����ÿ�β���stCD_Db_TblItemPair����+1

	void DebugInfo() const;
	void lock();
	friend std::ostream& operator << (std::ostream& ostm, const stCD_Db& v);
	CMN_CAST_TO
};
//static_assert(g_so_entity_meta_info_name_ == offsetof(stCD_Db, path_), "");
//static_assert(g_so_get_entity_attri_info_ == offsetof(stCD_Db, db_tbl_), "");
//static_assert(0x38 == offsetof(stCD_Db, ref_cnt_), "");

template<typename TblT>
struct stCD_DbBaseT : stCD_Db{
	typedef TblT DbTblType;

	inline DbTblType* GetDbTbl() const{ assert(!IsUnValidPtr(db_tbl_)); return db_tbl_->CastTo<DbTblType>(); }
	void DebugInfo() const{
		__super::DebugInfo();
		auto tbl = GetDbTbl();
		if (tbl)
			tbl->DebugInfo();
	}
	void DebugInfo(int counter) const{
		__super::DebugInfo();
		auto tbl = GetDbTbl();
		if (tbl)
			tbl->DebugInfo(counter);
	}
};

template<typename TblItemT>
struct stCD_DbT : stCD_DbBaseT<stCD_DbTblBaseT<TblItemT> >{};

template<typename TblItemT>
struct stCD_DbModelT : stCD_DbBaseT<stCD_DbTblModelT<TblItemT> >{};

//�𵽵�λ��������
struct stCD_TblItemUkn{
	void DebugInfo() const;
};
typedef stCD_DbT<stCD_TblItemUkn> stCD_DbUkn;

template<typename TblItemT, typename DbType_ = stCD_DbT<TblItemT> >
struct stCD_Db_TblItemPair{
	typedef DbType_ DbType;
	typedef TblItemT TblItemType;

	stCD_Db_TblItemPair(){
		db_ = nullptr;
		tbl_item_ = nullptr;
	}
	bool IsValid() const{
		if (IsUnValidPtr(db_) || IsUnValidPtr(tbl_item_))
			return false;
		return true;
	}

	DbType*			db_;
	TblItemType*	tbl_item_;
};
typedef stCD_Db_TblItemPair<stCD_TblItemUkn> stCD_UknTblItemPair;

template<typename TblItemT, typename DbType_ = stCD_DbT<TblItemT> >
struct stCD_DbPairT{
	typedef DbType_ DbType;
	typedef TblItemT TblItemType;

	pt_cwsz			db_file_path_;		//�˴����ַ�����stCD_Db.path_����ͬ��
	DbType*			db_;
};

typedef stCD_DbPairT<stCD_TblItemUkn, stCD_DbModelT<stCD_TblItemUkn> > stCD_DbPairModelUkn;
//"Art/Models/Items/Armours/Shields/ShieldInt/ShieldI"
typedef stCD_DbModelT<stCD_TblItemUkn> stCD_DbModelArmoursShields;
typedef stCD_DbPairT<stCD_TblItemUkn, stCD_DbModelArmoursShields> stCD_DbPairArmoursShields;
//UNICODE "Metadata/EnvironmentSettings/1_1_7_3.env"
typedef stCD_DbUkn stCD_Db_Metadata_EnvironmentSettings;
//////////////////////////////////////////////////////////////////////////
struct stCD_TblItemClientStrings{
	pt_cwsz			en_name_;
	pt_cwsz			ch_str_;

	void DebugInfo() const;
	void DebugInfo(int idx) const;
};
static_assert(8 == sizeof(stCD_TblItemClientStrings), "");
typedef stCD_DbT<stCD_TblItemClientStrings> stCD_DbClientStrings;
typedef stCD_Db_TblItemPair<stCD_TblItemClientStrings> stCD_ClientStringPair;

struct stCD_TblItemStats{
	pt_cwsz				en_name_;			//"level"
	pt_dword			ukn_dw_;			//����������boolֵ֮���
	pt_dword			ukn_dw11_;
	pt_cwsz				ch_name_;			//"�ȼ�",$c
	pt_dword			ukn_dw1_;
	pt_dword			ukn_dw2_;			//$14
	pt_word				ukn_w_;				//$18
	pt_byte				ukn_byte_;
	pt_pcvoid			ukn_ptr_;			//$1b
	pt_dword			ukn_dw4_;
	pt_cwsz				slot_en_name_;		//"item_drop_slots"
	pt_cwsz				slot_en_name1_;		//"item_drop_slots"
	pt_dword			ukn_dw5_;			//$2b
	pt_dword			ukn_dw6_;
	pt_cwsz				slot_ch_name_;		//"��Ʒ�����",$33
	pt_dword			ukn_dw7_;
	pt_dword			ukn_dw8_;			//$3b
	p_mem_placeholder(3);
	pt_dword			ukn_dw9_;			//$42
	pt_dword			ukn_dw10_;
	pt_cwsz				next_state_en_name_;	//UNICODE "main_hand_weapon_type",$4a

	void DebugInfo() const;
};
static_assert(g_so_tbl_item_stats_size_ == sizeof(stCD_TblItemStats), "");
typedef stCD_Db_TblItemPair<stCD_TblItemStats> stCD_StatsPair;
typedef stCD_DbT<stCD_TblItemStats> stCD_DbStats;
typedef GameArray<stCD_StatsPair> stCD_StatsArray;

struct stCD_TblItemAchievementItems{
};
typedef stCD_Db_TblItemPair<stCD_TblItemAchievementItems> stCD_AchievementItemsPair;
typedef GameArray<stCD_AchievementItemsPair> stCD_AchievementItemsPairArray;

//��С��0x80
struct stCD_TblItemCharacters{
	pt_cwsz			meta_path_;				//UNICODE "Metadata/Characters/Int/Int"
	pt_cwsz			profession_ch_name_;	//ְҵ��������"Ů��"
	pt_cwsz			meta_ao_path_;			//UNICODE "Metadata/Characters/Int/Int.ao"
	pt_cwsz			meta_act_path_;			//UNICODE "Metadata/Characters/Int/Int.act"
	p_mem_placeholder(4 * 7);
	enCD_ProfessionType		profession_type_;
	p_mem_placeholder(3);					//���룬profession_type_��ʵ��4���ֽڳ���
};
static_assert(0x2c == offsetof(stCD_TblItemCharacters, profession_type_), "");
typedef stCD_Db_TblItemPair<stCD_TblItemCharacters> stCD_CharactersPair;
typedef GameArray<stCD_CharactersPair> stCD_CharactersPairArray;

struct stCD_TblItemPassiveSkill{
	pt_cwsz			en_name_;			//����Ӣ����
	pt_cwsz			dds_file_path_;		//����֮��  $+4 UNICODE "Art/2DArt/SkillIcons/passives/lavalash.dds"
	stCD_StatsArray	stats_;
	pt_dword		delta_value_[4];	//���磺���Ӱٷ�֮20������������ܹ���4��ֵ���京�����������stats���Ӧ�ġ�
	pt_word			skill_id_;			//$20
	pt_word			ukn_w_;
	pt_cwsz						ch_name_;			//����������
	stCD_CharactersPairArray	professions_;		//$28������ְҵ�����Ҳ�Ǹ�stCD_TblItemPassiveSkill��Ҳֻ����㣬����ֶβŲ�Ϊ�ա�
	pt_byte				ukn_b_;
	pt_byte				ukn_b1_;
	pt_pcvoid			ukn_ptr_;		//$32
	pt_byte				ukn_b2_;
	stCD_AchievementItemsPair	achievement_item_;		//$37
	p_mem_placeholder(1);
	p_mem_placeholder(4 * 6);
	pt_cwsz					en_name1_;
	stCD_UknTblItemPair		ukn_array1_;	//$5c
	pt_bool					ukn_bool1_;		//���Ϊ�棬���������츳��
	p_mem_placeholder(4);
	stCD_UknGameArray		ukn_array2_;	//$69
	p_mem_placeholder(4);
	p_mem_placeholder(1);
	p_mem_placeholder(1);
	
	void DebugInfo() const;
};
static_assert(g_so_tbl_skill_item_id_ == offsetof(stCD_TblItemPassiveSkill, skill_id_), "");
static_assert(g_so_tbl_skill_item_ch_name_ == offsetof(stCD_TblItemPassiveSkill, ch_name_), "");
static_assert(g_v_tbl_item_passive_skill_size_ == sizeof(stCD_TblItemPassiveSkill), "");
typedef stCD_DbT<stCD_TblItemPassiveSkill> stCD_DbPassiveSkill;
typedef stCD_Db_TblItemPair<stCD_TblItemPassiveSkill> stCD_TblItemPassiveSkillPair;
//skill_id��stCD_TblItemPassiveSkillPair��ӳ��
typedef stCD_GameHash_map<pt_word, stCD_TblItemPassiveSkillPair> stCD_PassiveSkillHashMap;


struct stCD_TblItemTags{
	pt_cwsz		en_name_;
};
typedef stCD_Db_TblItemPair<stCD_TblItemTags> stCD_TagsPair;
typedef GameArray<stCD_TagsPair> stCD_TagsPairArray;

struct stCD_TblItemDropPool{
};
typedef stCD_Db_TblItemPair<stCD_TblItemDropPool> stCD_DropPoolPair;
typedef GameArray<stCD_DropPoolPair> stCD_DropPoolPairArray;

struct stCD_TblItemItemClasses{
	pt_cwsz			class_name_;		//Ӣ����
	pt_cwsz			ch_name_;			//������
	pt_cwsz			base_class_name_;	//������

	void DebugInfo() const;
};
typedef stCD_DbT<stCD_TblItemItemClasses> stCD_DbItemClasses;
typedef stCD_Db_TblItemPair<stCD_TblItemItemClasses> stCD_ItemClassesPairT;
typedef GameArrayEx<stCD_ItemClassesPairT> stCD_ItemClassesPairArrayEx;

struct stCD_TblItemModSellPriceTypes{
	/*
	"Low"
	"Medium"
	"High"
	"VeryHigh"
	"Special"
	"UniqueLow"
	"UniqueMedium"
	"UniqueHigh"
	"UniqueVeryHigh"
	"Kingmaker"
	"BreachFire"
	"BreachCold"
	"BreachLightning"
	"BreachPhysical"
	"BreachChaos"
	"BreachFireUnleashed"
	"BreachColdUnleashed"
	"BreachLightningUnleashed"
	"BreachPhysicalUnleashed"
	"BreashChaosUnleashed"
	*/
	pt_cwsz		price_;
};
typedef stCD_Db_TblItemPair<stCD_TblItemModSellPriceTypes> stCD_ModSellPriceTypesPair;
typedef GameArray<stCD_ModSellPriceTypesPair> stCD_ModSellPriceTypesArray;
static_assert(g_so_tbl_item_mod_sell_price_type_size_ == sizeof(stCD_TblItemModSellPriceTypes), "");

struct stCD_TblItemModType{
	pt_cwsz							mod_en_name_;			//UNICODE "IncreasedLife"
	stCD_ModSellPriceTypesArray		mod_sell_price_type_;
};
static_assert(g_so_tbl_item_mod_type_size_ == sizeof(stCD_TblItemModType), "");
typedef stCD_Db_TblItemPair<stCD_TblItemModType> stCD_ModTypePair;

struct stCD_TblItemMods{
	pt_cwsz				attr_en_name_;			//UNICODE "Strength1"
	pt_dword			ukn_dw_;				//����id��
	stCD_ModTypePair	mod_type_;
	stCD_StatsArray		stats_;
};
typedef stCD_Db_TblItemPair<stCD_TblItemMods> stCD_ModsPair;
typedef GameArray<stCD_ModsPair> stCD_ModsPairArray;
typedef GameArrayEx<stCD_ModsPair> stCD_ModsPairArrayEx;

struct stCD_TblItemBaseItemTypes{
	pt_cwsz						meta_path1_;
	stCD_ItemClassesPairT		item_class_pair_;
	pt_dword					grid_width_;	//���ӿ��
	pt_dword					grid_height_;	//���Ӹ߶�
	pt_cwsz						item_name_;		//UNICODE "ĥ��ʯ"
	pt_cwsz						meta_path2_;	//$18
	pt_dword					ukn_dw_;
	stCD_UknTblItemPair			flavour_text_;	//UNICODE "Data/FlavourText.dat"
	stCD_ModsPairArray			mods_;			//$28
	pt_dword					ukn_dw1_;
	stCD_UknTblItemPair			sound_effects_pair_;	//$34,"Data/SoundEffects.dat"
	p_mem_placeholder(g_so_tbl_item_base_item_type_size_ - g_so_tbl_item_base_item_type_db_sound_effects_ - 8);

	void DebugInfo() const;
};
static_assert(g_so_tbl_item_base_item_type_item_name_ == offsetof(stCD_TblItemBaseItemTypes, item_name_), "");
static_assert(g_so_tbl_item_base_item_type_db_sound_effects_ == offsetof(stCD_TblItemBaseItemTypes, sound_effects_pair_), "");
static_assert(g_so_tbl_item_base_item_type_size_ == sizeof(stCD_TblItemBaseItemTypes), "");
typedef stCD_DbT<stCD_TblItemBaseItemTypes> stCD_DbBaseItemTypes;
typedef stCD_Db_TblItemPair<stCD_TblItemBaseItemTypes> stCD_BaseItemTypesPairT;
typedef GameArray<stCD_BaseItemTypesPairT> stCD_BaseItemTypesArray;

struct stCD_TblItemWeaponTypes{
	stCD_BaseItemTypesPairT		item_;
	pt_int						critical_;
	pt_int						speed_;
	pt_int						damage_min_;
	pt_int						damage_max_;
	pt_int						range_max_;		//������Χ
	pt_int						ukn_dw_;

	void DebugInfo() const;
};
static_assert(g_so_tbl_item_weapon_types_size_ == sizeof(stCD_TblItemWeaponTypes), "");
typedef stCD_DbT<stCD_TblItemWeaponTypes> stCD_DbWeaponTypes;

struct stCD_TblItemItemVisualIdentity{
};
typedef stCD_Db_TblItemPair<stCD_TblItemItemVisualIdentity> stCD_TblItemItemVisualIdentityPair;

struct stCD_TblItemNPCShop{
	pt_cwsz					npc_en_name_;
	pt_dword				ukn_dw_;		//40
	stCD_TagsPairArray			tags_;
	stCD_UknGameArray		ukn_array_;
	stCD_DropPoolPairArray		drop_pool_;		//offset=0x18
	stCD_UknGameArray		ukn_id_array_;	
	pt_dword				ukn_dw1_;		//offset=0x28
	stCD_BaseItemTypesArray	items_;
};
typedef stCD_Db_TblItemPair<stCD_TblItemNPCShop> stCD_NPCShopPair;
static_assert(g_so_tbl_item_npc_shop_size_ == sizeof(stCD_TblItemNPCShop), "");

struct stCD_TblItemNPCAudio{
	pt_cwsz			en_name_;
};
typedef stCD_Db_TblItemPair<stCD_TblItemNPCAudio> stCD_NPCAudioPair;

struct stCD_TblItemTextAudio{
	pt_cwsz						en_name_;
	stCD_TblItemCharacters		character_;
	pt_cwsz						say_;				//UNICODE "�����ۿ�����ŵ���������, Ů��. ��Ȼ��ĺڰ����������Ϊ�����ŵ�һ����, Ȼ��, ���û��������"
	pt_cwsz						ogg_path_;			//UNICODE "Audio/Dialogue/NPC/Nessa/Ne01c.ogg"
};
typedef stCD_Db_TblItemPair<stCD_TblItemNPCAudio> stCD_TextAudioPair;
typedef GameArray<stCD_TextAudioPair> stCD_TextAudioArray;

struct stCD_TblItemNPCs{
	pt_cwsz			meta_path_name_;			//"Metadata/NPC/Act1/Tarkleigh"
	pt_cwsz			ch_name_;					//npc������
	pt_cwsz			meta_npc_path_;				//"Metadata/NPC/NPC"
	pt_dword		ukn_dw_;					//0x3e1,offset=0xc
	pt_dword		ukn_dw1_;
	stCD_UknGameArray	ukn_array_;
	pt_dword		ukn_dw2_;					//0x3e1,offset=0x1c
	pt_dword		ukn_dw3_;
	stCD_NPCShopPair	npc_shop_;
	stCD_NPCAudioPair	npc_audio_;				//offset=0x2c
	stCD_NPCAudioPair	npc_audio1_;

	void DebugInfo() const;
};
typedef stCD_Db_TblItemPair<stCD_TblItemNPCs> stCD_NPCsPair;
static_assert(g_so_tbl_item_npcs_size_ == sizeof(stCD_TblItemNPCs), "");

struct stCD_TblItemTopologies{

};
typedef stCD_Db_TblItemPair<stCD_TblItemTopologies> stCD_TopologiesPair;
typedef GameArray<stCD_TopologiesPair> TopologiesPairArray;

struct stCD_TblItemSoundEffects{

};
typedef stCD_Db_TblItemPair<stCD_TblItemSoundEffects> stCD_SoundEffectsPair;
typedef GameArray<stCD_SoundEffectsPair> SoundEffectsPairArray;

struct stCD_TblItemDifficulties{
	pt_cwsz			en_name_;			//UNICODE "Normal"
	pt_dword		ukn_dw_;
	pt_dword		ukn_dw1_;
	pt_cwsz			ch_name_;			//$+C UNICODE "һ��"�������������Ϊ׼
	pt_cwsz			ch_name1_;			//$+10 UNICODE "һ��"
	enCD_kMapDifficulty GetDifficulty() const;
};
static_assert(0x14 == sizeof(stCD_TblItemDifficulties), "");
typedef stCD_Db_TblItemPair<stCD_TblItemDifficulties> stCD_TblItemDifficultiesPair;

struct stCD_TblItemWorldArea{
	typedef GameArray<stCD_TblItemWorldArea*> AreaContT;

	pt_cwsz			en_area_name_;		//Ӣ������������ͬ�������ĵ�ͼ���ɲ�ͬ��WorldArea��ɵģ��������Ӣ������Ψһ��
	pt_cwsz			ch_map_name_;		//$4,���ĵ�ͼ��
	pt_dword		chapter_;			//$8,�������½�id����1����1����2����2
	bool			is_town_;			//$c
	bool			ukn_bool_;			//$d
	AreaContT		next_area_;			//$e, ͨ�����һ����ͨ������һ����ͼ,offset=0xe
#ifndef VER3_
	pt_byte			ukn_byte_;			//$16
	pt_dword		ukn_dw1_;			//$17
#endif
	pt_dword		ukn_dw2_;			//$1b
	pt_dword		world_area_id_;			//$1a,id�����͵㷢����ʱ���õõ�
	pt_dword		ukn_dw3_;			//�����ƫ���������
	pt_dword		ukn_dw5_;			//$23
	pt_cwsz			loading_image_path_;		//"Art/Textures/Interface/LoadingImages/Act1.dds",$26
	pt_dword		ukn_dw6_;
	stCD_UknGameArray	ukn_id_array_;
	pt_dword		ukn_dw7_;
	TopologiesPairArray		topologies_;		//$3a
	stCD_TblItemWorldArea*				belong_town_;		//��������,$42
#ifndef VER3_
	stCD_TblItemDifficultiesPair		difficult_;
#endif
	p_mem_placeholder(4 * 3);
	stCD_UknGameArray	ukn_array_;			//$52
	stCD_UknGameArray	ukn_array1_;
	stCD_UknGameArray	ukn_array2_;
	stCD_UknGameArray	ukn_array3_;
	pt_byte			ukn_byte1_;				//$72
	stCD_UknGameArray	ukn_array4_;		//$73
	p_mem_placeholder(4 * 4);				//$7b
	stCD_UknGameArray	ukn_array5_;			//$8b
	p_mem_placeholder(4 * 2);
	stCD_UknGameArray	ukn_array6_;			//$9b
	p_mem_placeholder(4 * 3);
	stCD_UknGameArray	ukn_id_array1_;			//$af
	pt_byte				ukn_byte2_;				//$b7
	p_mem_placeholder(4 * 2);
	stCD_UknGameArray	ukn_array8_;			//$c0
	pt_dword			ukn_dw23_;		//$c8
	pt_byte				ukn_byte3_;		//$cc
	pt_dword			ukn_dw24_;			//$cd
	pt_bool				ukn_bool1_;			//$d1,����Ʒ��ʱ����ж�����ֶ�
	p_mem_placeholder(4 * 3);			//$d2
	stCD_UknGameArray	ukn_array9_;			//offset=0xeb
	pt_dword			ukn_dw28_;
	pt_dword			ukn_dw29_;
	pt_dword			ukn_dw30_;
	stCD_UknGameArray	ukn_array10_;			//offset=0xff
	p_mem_placeholder(4 * 9 + 3);
	stCD_UknGameArray	ukn_array11_;		//$12e
	p_mem_placeholder(4 * 5);
	stCD_UknGameArray	ukn_array12_;		//$14a
	p_mem_placeholder(4 * 2 + 2);
	stCD_UknGameArray	ukn_array13_;		//$15c
	p_mem_placeholder(4 * 2);
	stCD_SoundEffectsPair	sound_effects_;		//$16c
	pt_pcvoid				ukn_ptr_;
	p_mem_placeholder(8);
/*
#ifdef VER_GJ_
	p_mem_placeholder(0xc);
#endif*/
#ifdef VER3_
	p_mem_placeholder(0xc);
	p_mem_placeholder(4 * 2);
#endif
#ifdef VER3_
	p_mem_placeholder(8);
#endif
	enCD_kMapDifficulty GetDiffLvl() const;
	void DebugInfo() const;		//0x180
};
static_assert(g_so_world_area_area_id_ == offsetof(stCD_TblItemWorldArea, world_area_id_), "");
#ifndef VER3_
static_assert(g_so_tbl_item_world_area_ukn_ == offsetof(stCD_TblItemWorldArea, ukn_array5_), "");
#endif
static_assert(g_so_tbl_item_world_area_size_ == sizeof(stCD_TblItemWorldArea), "");
typedef stCD_DbT<stCD_TblItemWorldArea> stCD_DbWorldArea;
typedef stCD_Db_TblItemPair<stCD_TblItemWorldArea> stCD_WorldAreaPairT;
typedef GameArray<stCD_WorldAreaPairT> stCD_WorldAreaPairArray;

struct stCD_TblItemMusic{
};
typedef stCD_Db_TblItemPair<stCD_TblItemMusic> stCD_TblItemMusicPair;
typedef GameArray<stCD_TblItemMusicPair> stCD_TblItemMusicPairArray;

struct stCD_TblItemEnvironments{
	pt_cwsz						en_name_;						//UNICODE "1_1"
	pt_cwsz						path_audio_sound_effects_;		//$+4 UNICODE "Audio/Sound Effects/Ambient/1_1_1_The_Twilight_Str"
	stCD_TblItemMusicPairArray	musics_;
	pt_cwsz						meta_env_setting_;				//$+10 UNICODE "Metadata/EnvironmentSettings/1_1_1.env"
	pt_pcvoid					ukn_ptr_;
	pt_dword					ukn_dw_;
	pt_pcvoid					ukn_ptrs_[3];
};
static_assert(0x28 == sizeof(stCD_TblItemEnvironments), "");
typedef stCD_DbT<stCD_TblItemEnvironments> stCD_DbEnvironments;
typedef stCD_Db_TblItemPair<stCD_TblItemEnvironments> stCD_TblItemEnvironmentsPair;

struct stCD_TblItemCurrencyItems{

};
typedef stCD_Db_TblItemPair<stCD_TblItemCurrencyItems> stCD_CurrencyItemsPair;
typedef GameArray<stCD_CurrencyItemsPair> stCD_CurrencyItemsPairArray;

struct stCD_TblItemNPCMaster{
	pt_cwsz			en_name_;		//UNICODE "DexIntMaster"
	pt_cwsz			meta_path_;		//UNICODE "Metadata/NPC/Missions/Hideout/DexInt"
	pt_word			ukn_w_;
	stCD_ModsPair	mods_;			//offset=0xa
	pt_byte			ukn_byte_;
	pt_cwsz			meta_path1_;	//UNICODE "Metadata/NPC/Missions/Hideout/DexIntDemo", offset=13
	stCD_WorldAreaPairArray			world_areas_;
	pt_dword						item_cnt_;				//�²��ǽ�������Ʒ����
	stCD_AchievementItemsPair		achievement_items_;
	stCD_TagsPairArray				tags_;				//offset=0x2b
	stCD_UknGameArray				ukn_id_array_;
	stCD_DropPoolPairArray			drop_pool_;			//offset=0x3b
	stCD_UknGameArray				ukn_id_array1_;
	stCD_CurrencyItemsPair			currency_items_;
	stCD_AchievementItemsPair		achievement_items1_;
	stCD_AchievementItemsPairArray	achievement_items_array_;
};
static_assert(g_so_tbl_item_npc_master_size_ == sizeof(stCD_TblItemNPCMaster), "");

struct stCD_TblItemNPCMasterExperiencePerLevel{

};

typedef GameArray<pt_dword> stCD_QuestIdArrayT;
struct stCD_TblItemNPCTalk{
	stCD_NPCsPair			npc_;
	pt_dword				npc_panel_menu_item_idx_;		//��0��ʼ��
	pt_cwsz					npc_panel_menu_item_name_;		//"���μ���"
	stCD_QuestIdArrayT		ukn_id_array_;
	stCD_QuestIdArrayT		branch_id_;		//offset=0x18����QuestState�����brach_id����һ����
	stCD_QuestIdArrayT		ukn_id_array1_;
	pt_pcvoid				ukn_ptr_;		//�������array�����ָ������Ǹ�vector
	pt_dword				ukn_dw1_;		//offset=0x2c
	pt_dword				talk_state_;		//$30��npc�����ݸ�ֵ���ж��Ƿ���ʾ��talk
	pt_dword				ukn_dw3_;
	pt_dword				ukn_dw4_;
	pt_dword				ukn_dw5_;
	stCD_UknGameArray		ukn_array_;		//offset=0x40
	stCD_TextAudioArray		text_audio_;
	pt_pcvoid				ukn_ptr1_;		//����������ֶεĻ�����������ַ
	pt_dword				ukn_dw6_;
	pt_word					ukn_w_;
	pt_pcword				item_ch_name_;		//offset=0x5a��UNICODE "ҽҩ��"
	pt_dword				ukn_dw7_;
	pt_pcword				item_ch_name1_;
	pt_dword				ukn_dw8_;
	pt_dword				ukn_dw9_;
	pt_dword				ukn_dw10_;
	pt_dword				ukn_dw11_;
	pt_pcword				item_ch_name2_;		//offset=0x7a
	pt_dword				ukn_dw12_;
	pt_dword				ukn_dw13_;
	pt_byte					ukn_byte_;
	pt_pcword				item_ch_name3_;		//offset=0x83
};
typedef stCD_Db_TblItemPair<stCD_TblItemNPCTalk> stCD_NPCTalkPair;
static_assert(g_so_tbl_item_npc_talk_size_ == sizeof(stCD_TblItemNPCTalk), "");

//���ܴ���˴����š����͵㴫�͵ĵط�
struct stCD_TblItemMapPins{
	typedef GameArray<stCD_WorldAreaPairT>	WorldAreaCont;

	pt_cwsz					en_map_name_;
	int						pos_x_;		//������С��ͼ�ĳߴ�֮��İ�
	int						pos_y_;
	//���͵���������
	stCD_WorldAreaPairT		waypoint_world_area_;		//����ĳ��ͼ�пɱ����͹�ȥ�����ֵ��Ϊ�գ�����Ϊ0
	WorldAreaCont			world_areas_;
	pt_cwsz					map_ch_name_;
	pt_cwsz					format_desc_;			//offset=0x20
	stCD_UknGameArray		ukn_array_;
	pt_dword				ukn_dw_;				//offset=0x2c
	WorldAreaCont			world_areas1_;
	WorldAreaCont			world_areas2_;
	stCD_WorldAreaPairT		world_area_1_;			//offset=0x40
	stCD_WorldAreaPairT		world_area_2_;
	pt_cwsz					en_map_name1_;			//��en_map_name_���ַ���ͬ�����ǵ�ַ��ֵ����ͬ,offset=0x50
	pt_dword				ukn_dw1_;
	WorldAreaCont			world_ares3_;
	stCD_UknGameArray		ukn_ids_;

	void DebugInfo() const;
	//gj3.0
	stCD_WorldAreaPairT GetTransferWorldItemPair() const;
};
static_assert(g_so_tbl_item_map_pins_size_ == sizeof(stCD_TblItemMapPins), "");
typedef stCD_DbT<stCD_TblItemMapPins> stCD_DbMapPins;
struct stCD_MapPinsPair : stCD_Db_TblItemPair<stCD_TblItemMapPins>{
	const stCD_TblItemWorldArea* GetTransferWorldItem(enCD_kMapDifficulty area_type) const;
	const stCD_TblItemWorldArea* GetTransferWorldItem() const;
	stCD_WorldAreaPairT GetTransferWorldItemPair(enCD_kMapDifficulty area_type) const;
	stCD_WorldAreaPairT GetTransferWorldItemPair() const;
};

//�⼸��dwordӦ���Ǳ�־
struct stCD_TblItemMapConnections{
	stCD_MapPinsPair		map_dst_;
	stCD_MapPinsPair		map_src_;
	pt_dword				ukn_dw_;		//==1,3e1
	pt_cwsz					dst_map_condition_;		//$+14 "�������������񡾴��ſڵĵ��ˡ�. "
	pt_dword				ukn_dw1_;		//==2,3e1
	pt_dword				ukn_dw2_;		//0x3e1
	pt_dword				ukn_dw3_;		//0x3e1,offset=0x20

	void DebugInfo() const;
};
typedef stCD_DbT<stCD_TblItemMapConnections> stCD_DbMapConnections;
typedef stCD_Db_TblItemPair<stCD_TblItemMapConnections> stCD_MapConnectionsPair;
static_assert(g_so_tbl_item_map_connections_size_ == sizeof(stCD_TblItemMapConnections), "");

struct stCD_TblItemQuest{
	pt_cwsz		en_name_;				//2291D700 UNICODE "a1q1"
	pt_dword	chapter_id_;				//�ڼ��£��е���������ڶ���½���
	pt_cwsz		ch_name_;				//2291D708 UNICODE "���ſڵĵ���"
	pt_dword	flag_;					//Ӧ���Ǳ�־
	pt_cwsz		dds_file_path_;			//2291D710 UNICODE "Art/2DArt/QuestIcons/hillock.dds"
	pt_dword	sub_id_;				//�½��ڵ�����id����ͬ����������sub_id��ͬ
	bool		is_branch_line_;		//�Ƿ���֧��
	p_mem_placeholder(3);
	pt_dword	ukn4_;
	pt_dword	ukn5_;					//����ֶο�����������word��ɵ�

	void DebugInfo() const;
};
static_assert(sizeof(stCD_TblItemQuest) == g_so_tbl_item_quest_size_, "");
typedef stCD_Db_TblItemPair<stCD_TblItemQuest> stCD_QuestPair;
typedef stCD_DbT<stCD_TblItemQuest> stCD_DbQuest;

struct stCD_TblItemQuestStates{
	typedef stCD_Db_TblItemPair<stCD_TblItemQuest> QuestPairT;
	typedef GameArray<stCD_MapPinsPair> MapPinsCont;
	typedef GameArray<pt_cwsz> QuestPromptCont;

	QuestPairT				quest_pair_;
	pt_dword				quest_state_;		//����״̬�����״̬��0���ӿ�ʼ��ĳ�����񣬵����״̬����ֵ�����μ�1�ġ�
	stCD_QuestIdArrayT		branch_ids_;		//���飬����˷�֧����id
	stCD_UknGameArray		ukn_array_;			//һֱ=0,$14
	//�������ͼ��壬������ʾ��������ϸ������Ϣ
	pt_cwsz					state_desc_;		//$+1C����ϸ���������� "������� - ���Ѿ������������˶��Ҵ�����������ȡ��������. "
	bool					is_complete_state_;	//�Ƿ����״̬,$20
	//�����������ʾ��
	pt_cwsz					simple_prompt_;		//$21,״̬�ļ�Ҫ��ʾ������"�������"��"���ܺ���.Īޱ��"��"����ɯ��̸"��"�ص�����"
	MapPinsCont				map_pins_;			//offset=0x25
	pt_dword				ukn_dw1_;			//offset=0x2d
	//״̬��ʾ����ʾ���ұߵ��Ǹ�����е�
	QuestPromptCont			quest_prompt_;
	MapPinsCont				map_pins1_;			//$39
	stCD_UknGameArrayEx		ukn_arrayex_;		//$41,������鶼��Ϊ�յ�
	pt_byte					ukn_byte_;			//$4d
	stCD_UknGameArray		ukn_ids_;

	void DebugInfo() const;
};
static_assert(g_so_tbl_item_quest_states_desc_ == offsetof(stCD_TblItemQuestStates, state_desc_), "");
static_assert(g_so_tbl_item_quest_states_size_ == sizeof(stCD_TblItemQuestStates), "");
typedef stCD_Db_TblItemPair<stCD_TblItemQuestStates> stCD_QuestStatesPair;

//����û��id�ֶΣ�id���ܾ��������������
struct stCD_TblItemActiveSkills{
	typedef GameArray<pt_dword> ValueContT;
	typedef GameArray<pt_pcvoid> PtrContT;

	pt_cwsz			en_name_;			//UNICODE "double_strike"
	pt_cwsz			ch_name_;			//UNICODE "˫�ش��"
	pt_cwsz			use_desc_;			//����ʹ�õ�����	 UNICODE "ʹ��������ֽ�ս��������Ŀ��������ο��ٵĹ���."
	pt_cwsz			en_name1_;			//$c,UNICODE "DoubleStrike"
	pt_cwsz			dds_file_path_;		//UNICODE "Art/2DArt/SkillIcons/icondoubleswing.dds"
	ValueContT		ukn_ids1_;
	ValueContT		ukn_ids2_;
	stCD_ItemClassesPairArrayEx		item_classes_;			//$24������Ҫ�����������
	pt_cwsz			http_image_path_;	//UNICODE "http://s3.amazonaws.com/pathofexile/image/skills/s"
	pt_byte			ukn_byte1_;			
	pt_cwsz			en_name2_;			//$35
	pt_byte			ukn_byte2_;			//$39
	pt_dword		ukn_dw1_;		//1,$3a
	pt_byte			ukn_byte3_;		//1,$3e
	stCD_StatsArray		status1_;		//3,$3f
	stCD_StatsArray		status2_;
	stCD_UknGameArray	ukn_array_;

	void DebugInfo() const;
};
static_assert(g_so_tbl_item_active_skill_dds_file_path_ == offsetof(stCD_TblItemActiveSkills, dds_file_path_), "");
static_assert(g_so_tbl_item_active_skill_size_ == sizeof(stCD_TblItemActiveSkills), "");
typedef stCD_Db_TblItemPair<stCD_TblItemActiveSkills> stCD_ActiveSkillPairT;

typedef stCD_StringEnChPair stCD_TblItemGemTags;
typedef stCD_DbT<stCD_TblItemGemTags> stCD_DbGemTags;

struct stCD_TblItemGrantedEffects{
	typedef GameVector<pt_byte> ByteContT;

	pt_cwsz						en_name_;
	pt_dword					ukn_dw_;
	pt_byte						ukn_byte_;
	pt_pcvoid					ukn_ptr_;		//$9,������ָ�����
	pt_pcvoid					ukn_ptr1_;		//$d
	pt_dword					ukn_dw1_;		//$11
	pt_dword					ukn_dw2_;		//$15
#ifdef VER3_
	p_mem_placeholder(4 * 2);
#endif
	pt_cwsz						en_name1_;			//$19,UNICODE "MonsterFireball"
	pt_dword					ukn_dw3_;
	pt_cwsz						en_name2_;			//UNICODE "MonsterFireball"
	pt_pcvoid					ukn_ptr2_;
	pt_dword					ukn_dw4_;
	pt_pcvoid					ukn_ptr3_;
	pt_word						ukn_w_;
	pt_dword					ukn_dw6_;
	pt_dword					ukn_dw5_;
	stCD_ActiveSkillPairT		active_skill_pair_;
	pt_byte						ukn_byte1_;
#ifdef VER3_
	p_mem_placeholder(1);
#endif

	//������ؿգ�������������
	inline stCD_TblItemActiveSkills* GetActiveSkill() const{ if (IsUnValidPtr(active_skill_pair_.tbl_item_)) return nullptr; return active_skill_pair_.tbl_item_; }
	void DebugInfo() const;
};
static_assert(g_so_tbl_item_granted_effects_active_skill_pair_ == offsetof(stCD_TblItemGrantedEffects, active_skill_pair_), "");
static_assert(sizeof(stCD_TblItemGrantedEffects) == g_so_tbl_item_granted_effects_size_, "");
typedef stCD_DbT<stCD_TblItemGrantedEffects> stCD_DbGrantedEffects;
typedef GameArray<stCD_TblItemGrantedEffects> stCD_TblItemGrantedEffectsArray;
typedef GameArrayEx<stCD_TblItemGrantedEffects> stCD_TblItemGrantedEffectsArrayEx;
struct stCD_GrantedEffectsPairT : stCD_Db_TblItemPair<stCD_TblItemGrantedEffects>{
	stCD_TblItemGrantedEffectsPerLevel* FindDbPerLevelBySkillGemLvl(pt_dword lvl) const;
};

//CD_kFileDbPath_GrantedEffectsPerLevel
struct stCD_TblItemGrantedEffectsPerLevel{
	stCD_GrantedEffectsPairT			granted_effects_;
	pt_dword							ukn_dw_;
	stCD_StatsArray						stats_;		//$c
	p_mem_placeholder(g_so_GrantedEffectsPerLevel_require_lvl_ - 0xc - sizeof(stCD_StatsArray));
	pt_dword							require_lvl_;		//����ȼ�,$3c
	pt_dword							ukn_dw1_;			//��ֵ��require_lvl_һ��
	stCD_StatsArray						stats1_;	//$44
	stCD_UknGameArray					ukn_ids_;	//$4c
	p_mem_placeholder(6 * 4);		//������ֵ
	stCD_StatsArray						stats2_;	//$6c
	p_mem_placeholder(8 * 4);	//������ֵ
	pt_byte								ukn_b_;		//$94
};
static_assert(g_so_GrantedEffectsPerLevel_require_lvl_ == offsetof(stCD_TblItemGrantedEffectsPerLevel, require_lvl_), "");
#ifndef VER3_
static_assert(g_so_tbl_item_granted_effects_per_level_size_ == sizeof(stCD_TblItemGrantedEffectsPerLevel), "");
#endif
typedef stCD_DbT<stCD_TblItemGrantedEffectsPerLevel> stCD_DbGrantedEffectsPerLevel;
typedef stCD_Db_TblItemPair<stCD_TblItemGrantedEffectsPerLevel> stCD_GrantedEffectsPerLevelPairT;

//��ʯ�����ָ����ܵ�������һ���ģ�����������Ʒ���Ϳ��Եõ���Ӧ�ļ����ˡ�
struct stCD_TblItemSkillGems{
	typedef stCD_Db_TblItemPair<stCD_TblItemGemTags> GemTagPairT;
	typedef GameArray<GemTagPairT> GemTagInfoT;

	stCD_BaseItemTypesPairT			item_pair_;
	stCD_GrantedEffectsPairT		granted_effects_pair_;
	pt_dword						ukn_dw1_;
	pt_dword						ukn_dw2_;
	pt_dword						ukn_dw3_;
	GemTagInfoT						gem_tag_info_;				//��ʯ��������Ļ�ɫ���壬Ͷ�����������˪��
	stCD_BaseItemTypesPairT			item_pair1_;				//�е����������Ч���е��������Ϊ��
	pt_byte							ukn_byte_;

	void DebugInfo() const;
};
static_assert(g_so_tbl_item_skill_gems_gem_tag_ == offsetof(stCD_TblItemSkillGems, gem_tag_info_), "");
static_assert(sizeof(stCD_TblItemSkillGems) == g_so_tbl_item_skill_gems_size_, "");
typedef stCD_Db_TblItemPair<stCD_TblItemSkillGems> stCD_SkillGemsPairT;

struct stCD_DbSkillGems : stCD_DbT<stCD_TblItemSkillGems>{
	stCD_TblItemSkillGems* FindByBaseItemType(stCD_TblItemBaseItemTypes* base_item_ptr) const;
};

struct stCD_TblItemChests{
	pt_cwsz				meta_path_;		//UNICODE "Metadata/Chests/ProdWounded1"
	bool				ukn_bool_;
	pt_dword			type_;			//$5,�²�������
	pt_cwsz				ch_name_;		//UNICODE "�����ߵ�����"
	pt_cwsz				meta_so_path_;	//UNICODE "Metadata/Chests/DeadPlayerProds/ProdWounded1.ao"
	bool				ukn_b_;			//$11
	bool				ukn_b1_;		//�����������־
	bool				ukn_b2_;		//$13������������
	bool				ukn_b3_;
	pt_word				ukn_w1_;
	pt_word				ukn_w_;
	pt_dword			ukn_dw2_;		//$19
	stCD_UknGameArray	ukn_array_;		//$1d
	stCD_UknGameArray	ukn_array1_;
	pt_dword			ukn_dw3_;
	pt_dword			ukn_dw4_;
	bool				ukn_bool1_;		//$35
	stCD_UknGameArray	ukn_array2_;	//$36
	stCD_UknGameArray	ukn_array3_;
	pt_dword			ukn_dw5_;
	pt_dword			ukn_dw6_;
	stCD_UknGameArray	ukn_array4_;	//$4e
	pt_dword			ukn_dw7_;
	pt_dword			ukn_dw8_;
	pt_dword			ukn_dw9_;
	pt_dword			ukn_dw10_;
	pt_dword			ukn_dw11_;
	pt_dword			ukn_dw12_;
	pt_cwsz				next_chest_meta_path_;		//UNICODE "Metadata/Chests/ProdWounded2"
	pt_dword			ukn_dw13_;
	pt_dword			ukn_dw14_;

	void DebugInfo() const;
};
static_assert(g_so_tbl_item_chests_size_ == sizeof(stCD_TblItemChests), "");
typedef stCD_Db_TblItemPair<stCD_TblItemChests> stCD_TblItemChestsPair;
typedef stCD_DbT<stCD_TblItemChests> stCD_DbChests;

struct stCD_TblItemBloodTypes{

};
typedef stCD_Db_TblItemPair<stCD_TblItemBloodTypes> stCD_TblItemBloodTypesPair;

struct stCD_TblItemMonsterResistances{

};
typedef stCD_Db_TblItemPair<stCD_TblItemMonsterResistances> stCD_TblItemMonsterResistancesPair;

struct stCD_TblItemMonsterTypes{
	pt_cwsz				en_name_;		//"BloodMonkey"
	pt_dword			ukn_dw_;
	bool				is_called_;			//$8���Ƿ����ٻ���
	pt_dword			ukn_dw1_;
	pt_dword			ukn_dw2_;
	pt_dword			ukn_dw3_;
	pt_dword			ukn_dw4_;		//$15
	stCD_TagsPairArray	tags_;			//$19
	stCD_TblItemMonsterResistancesPair		resistance_;	//$21

	void DebugInfo() const;
};
static_assert(g_so_tbl_item_monster_types_size_ == sizeof(stCD_TblItemMonsterTypes), "");
typedef stCD_Db_TblItemPair<stCD_TblItemMonsterTypes> stCD_TblItemMonsterTypesPair;
typedef stCD_DbT<stCD_TblItemMonsterTypes> stCD_DbMonsterTypes;

//����Ʒ��
struct stCD_TblItemMonsterVarieties{
	pt_cwsz							meta_path_;			//"Metadata/Monsters/Bandits/BanditBossHeavyStrike_"
	stCD_TblItemMonsterTypesPair	monster_type_;
	pt_dword			ukn_dw1_;
	pt_dword			ukn_dw2_;
	pt_dword			ukn_dw3_;
	pt_dword			ukn_dw4_;
	pt_cwsz				meta_act_path_;				//$1c
	pt_cwsz				meta_ao_path_;
	pt_cwsz				meta_path1_;
	stCD_UknGameArray	ukn_array_;					//$28
	stCD_UknGameArrayEx	ukn_array1_;
	pt_dword			ukn_dw5_;			//$3c
	pt_dword			ukn_dw6_;
	pt_dword			ukn_dw7_;
	pt_dword			ukn_dw8_;
	pt_dword			ukn_dw9_;
	pt_dword			ukn_dw10_;			//$50
	stCD_TagsPairArray	tags_;				//$54
	pt_dword			ukn_dw11_;
	pt_dword			ukn_dw12_;
	pt_pcvoid			ukn_ptr_;			//$64
	pt_dword			ukn_dw13_;
	pt_dword			ukn_dw14_;
	pt_dword			ukn_dw15_;
	pt_dword			ukn_dw16_;
	pt_dword			ukn_dw17_;			//$78
	stCD_TblItemGrantedEffectsArrayEx		granted_effects_;
	stCD_ModsPairArrayEx	mods_;
	stCD_TblItemBloodTypesPair		blood_type_;		//$94
	pt_cwsz					ch_name_;		//$9c,"��­�߿�����"
	p_mem_placeholder(4 * 3);
	stCD_UknGameArray	ukn_array2_;		//$ac,"Data/ItemVisualIdentity.dat"
	stCD_UknGameArray	ukn_array3_;		//$ac,"Data/ItemVisualIdentity.dat"
	p_mem_placeholder(4 * 2);
	stCD_ItemClassesPairT	item_classes_;	//$c4
	stCD_ItemClassesPairT	item_classes1_;
	p_mem_placeholder(4 * 5);
	stCD_AchievementItemsPairArray	achievement_items_;		//$e8
	stCD_UknGameArray				ukn_array4_;
	stCD_UknGameArray				ukn_array5_;
	pt_byte							ukn_b_;				//$100
	p_mem_placeholder(4 * 6);		//$101
	pt_byte			ukn_;		//$119
	pt_dword		ukn_dw18_;		//$11a
	pt_pcvoid		ukn_ptr1_;
	stCD_UknGameArray				ukn_array6_;
	stCD_UknGameArray				ukn_array7_;
	stCD_UknGameArray				ukn_array8_;
	p_mem_placeholder(4 * 2);		//$13a
	stCD_UknTblItemPair				monster_segments_;		//"Data/MonsterSegments.dat"
	stCD_UknTblItemPair				monster_armours_;		//"Data/MonsterArmours.dat"
	p_mem_placeholder(4 * 2);		//$152
	stCD_UknGameArray				ukn_array9_;			//$15a
	stCD_UknGameArray				ukn_array10_;
	stCD_UknGameArray				ukn_array11_;
	stCD_UknGameArray				ukn_array12_;
	stCD_UknGameArray				ukn_array13_;
	stCD_UknGameArray				ukn_array14_;
	stCD_UknGameArray				ukn_array15_;
	p_mem_placeholder(4 * 2);		//$192
	stCD_UknGameArray				ukn_array16_;

	void DebugInfo() const;
};
static_assert(0x78 == offsetof(stCD_TblItemMonsterVarieties, ukn_dw17_), "");
static_assert(g_so_tbl_item_monster_varieties_size_ == sizeof(stCD_TblItemMonsterVarieties), "");
typedef stCD_Db_TblItemPair<stCD_TblItemMonsterVarieties> stCD_TblItemMonsterVarietiesPair;
typedef stCD_DbT<stCD_TblItemMonsterVarieties> stCD_DbMonsterVarieties;

struct stCD_TblItemBuffDefinitions{
	pt_cwsz				en_name_;
	pt_cwsz				ch_desc_;			//�������������� �������翹��
	pt_word				ukn_w_;
	pt_cwsz				ch_name_;			//$a
	stCD_StatsArray		stats_;

	void DebugInfo() const;
};
typedef stCD_Db_TblItemPair<stCD_TblItemBuffDefinitions> stCD_TblItemBuffDefinitionsPair;

struct stCD_DataCraftingBenchOptions{
	typedef GameArray<pt_dword> RequireItemCnt;

	p_mem_placeholder(4 * 2);
	pt_dword					ukn_dw_;				//$8
	stCD_ModsPair				mods_;
	stCD_BaseItemTypesArray		require_item_type_;		//$14
	RequireItemCnt				require_item_cnt_;		//$1c
	pt_dword					ukn_dw1_;
	pt_cwsz						title_;					//$28

	void DebugInfo() const;
};
static_assert(0x14 == offsetof(stCD_DataCraftingBenchOptions, require_item_type_), "");
static_assert(0x1c == offsetof(stCD_DataCraftingBenchOptions, require_item_cnt_), "");
static_assert(0x28 == offsetof(stCD_DataCraftingBenchOptions, title_), "");
typedef stCD_Db_TblItemPair<stCD_DataCraftingBenchOptions> stCD_DataCraftingBenchOptionsPair;

struct stCD_DataChestEffects{
};
typedef stCD_Db_TblItemPair<stCD_DataChestEffects> stCD_DataChestEffectsPair;

struct stCD_DataStrongboxes{
};
typedef stCD_Db_TblItemPair<stCD_DataStrongboxes> stCD_DataStrongboxesPair;

struct stCD_DataWords{

};
typedef stCD_Db_TblItemPair<stCD_DataWords> stCD_DataWordsPair;

struct stCD_DataNPCTextAudio{

};
typedef stCD_Db_TblItemPair<stCD_DataNPCTextAudio> stCD_DataNPCTextAudioPair;

//����
struct stCD_DataLabyrinthTrials{
	stCD_WorldAreaPairT			world_area_;
	p_mem_placeholder(4 * 3);		//pt_dword
	stCD_DataNPCTextAudioPair	npc_text_audio_;
	pt_cwsz						direction_str1_;
	pt_cwsz						direction_str2_;
};
static_assert(0x24 == sizeof(stCD_DataLabyrinthTrials), "");
typedef stCD_Db_TblItemPair<stCD_DataLabyrinthTrials> stCD_DataLabyrinthTrialsPair;
typedef GameArray<stCD_DataLabyrinthTrialsPair> stCD_DataLabyrinthTrialsArray;

struct stCD_DataLabyrinths{
	pt_dword						id_;
	pt_cwsz							title_;			//$+4      4DE67A7C   505F9330  �f��  UNICODE "The Normal Labyrinth"
	stCD_BaseItemTypesPairT			cost_item_;
	p_mem_placeholder(4);
	stCD_DataLabyrinthTrialsArray	trials_;
	pt_dword						lvl_;			//�����ɫ�ȼ�
	p_mem_placeholder(4);		//pt_dword
	stCD_DataWordsPair				data_words_;
	stCD_UknGameArray				ukn_ids_;
	stCD_UknGameArray				ukn_ids1_;
};
static_assert(0x3c == sizeof(stCD_DataLabyrinths), "");
typedef stCD_Db_TblItemPair<stCD_DataLabyrinths> stCD_DataLabyrinthsPair;
//////////////////////////////////////////////////////////////////////////
struct stCD_BuffInfo{
	pt_pcvoid							vtbl_;

private:
	stCD_TblItemBuffDefinitionsPair*	db_buff_definition_;

public:
	pt_cwsz GetBuffCnName() const;
	pt_cwsz GetBuffEnName() const;
	pt_cwsz	GetBuffDesc() const;
	void DebugInfo() const;
};
//////////////////////////////////////////////////////////////////////////
struct stCD_AttrDbItemBase : stCD_EntityAttrDbBase{
	pt_pcvoid						ukn_;
	pt_dword						grid_width_;	//��������ҩ�� ����1
	pt_dword						grid_height_;	//��������ҩ�� ����2
	GameWString						name_;			//��Ʒ��
	pt_dword						ukn_dw_;
	GameWString						desc_;			//��Ʒ����
	pt_dword						ukn_dw1_;
	stCD_BaseItemTypesPairT			base_item_type_pair_;

	void DebugInfo() const;
};
static_assert(g_so_attr_db_item_base_name_ == offsetof(stCD_AttrDbItemBase, name_), "");
static_assert(g_so_attr_db_item_base_item_type_pair_ == offsetof(stCD_AttrDbItemBase, base_item_type_pair_), "");
//////////////////////////////////////////////////////////////////////////
struct stCD_DbEntity : stCD_Db{
	inline stCD_DbTblEntity* GetDbTbl() const{ 
		if (IsUnValidPtr(db_tbl_))
		{
			assert(false);
			return nullptr;
		}
		return db_tbl_->CastTo<stCD_DbTblEntity>();
	}
	stCD_EntityAttrInfo* FindAttrInfo(pt_csz name) const;
	stCD_EntityAttrDbBase* FindAttrDb(pt_csz name) const;
	template<typename T>
	T* FindAttrDb(pt_csz name) const{
		auto res = FindAttrDb(name);
		if (!res) return nullptr;
		return res->CastTo<T>();
	}
	void DebugInfo() const;
};

struct stCD_EntityBase{
	typedef GameVector<stCD_EntityAttrBase*> AttrContT;

	stCD_DbEntity*	db_;		//ͬ�����͵Ķ�����õ�ַ��һ���ģ������ɫ(�����Լ�)����ֵ����һ���ġ������Ǹ���ɫdb�����ֵ����һ�������������������Ҳ��һ���ġ�
	AttrContT		entity_cont_;

	stCD_DbTblEntity* GetDbTbl() const;
	const GameWString* GetDbPath() const;
	stCD_EntityAttrDbBase* FindAttrDb(pt_csz name) const;
	template<typename T>
	T* FindAttrDb(pt_csz name) const{
		if (IsUnValidPtr(db_))
		{
			assert(false);
			return nullptr;
		}
		return db_->FindAttrDb<T>(name);
	}
	stCD_EntityAttrInfo* FindAttrInfo(pt_csz name) const;
	stCD_EntityAttrBase* FindAttrComponent(pt_csz name) const;
	template<typename T>
	T* FindAttrComponent(pt_csz name) const{
		auto res = FindAttrComponent(name);
		if (!res) return nullptr;
		return res->CastTo<T>();
	}
	//////////////////////////////////////////////////////////////////////////
	//����IsNpc��CastToNpc�Ⱥ���ǰ���ȵ���IsValid�ж�һ�¡�
	bool IsValid() const;
	//////////////////////////////////////////////////////////////////////////
	//std::ostream����ڼ䣬�����ٴ�LOG_O(Log_debug)�����������˳��Ļ��ҡ�
	friend std::ostream& operator << (std::ostream& ostm, const stCD_EntityBase& v);
	void DebugInfo() const;
	CMN_CAST_TO
};

//���������ʵ�壬Ҳ���Ǹ�ʵ�����������ԣ����磺��ҡ�NPC��������͵��
struct stCD_EntityPosBased : stCD_EntityBase{
	typedef bool(stCD_EntityPosBased::*Fn_EntityIf)() const;
	typedef void(stCD_EntityPosBased::*Fn_EntityDebugInfo)() const;

#ifdef VER3_
	p_mem_placeholder(4 * 3);
#endif
	stCD_World*				world_;
	pt_dword				id_;			//����id������id�������ڷ���
	p_mem_placeholder(g_so_entity_base_pos_attr_ - g_so_entity_id_ - 4);
	stCD_Positioned*		attr_pos_;

	//////////////////////////////////////////////////////////////////////////
	/*�����ߵ�������NPC*/
	bool IsNpc() const;
	bool IsPlayer() const;
	bool IsMonster() const;
	bool IsWaypoint() const;
	bool IsAreaTransition() const;
	//�ֿ�
	bool IsStash() const;
	//��ʾ��
	bool IsNoticeBoard() const;
	//���ʾ��
	bool IsNoticeBoardPvP() const;
	//���ӡ�ľͰ�������ߵ�����
	bool IsChest() const;
	//������Ʒ
	bool IsWorldItem() const;
	//���ƶ�����
	bool IsMovement() const;
	//�ɴ��͵Ķ���
	bool IsTransitionable() const;
	stCD_EntityNpc* CastToNpc() const;
	//�����Ȳ����ж�player����Ϊ�õ�������ǳ���
	stCD_EntityPlayer* CastToPlayer() const;
	stCD_EntityMonster* CastToMonster() const;
	stCD_EntityWaypoint* CastToWaypoint() const;
	stCD_EntityAreaTransition* CastToAreaTransition() const;
	stCD_EntityNoHuman* CastToStash() const;
	stCD_EntityNoHuman* CastToNoticeBoard() const;
	stCD_EntityNoHuman* CastToNoticeBoardPvP() const;
	stCD_EntityChest* CastToChest() const;
	stCD_EntityWorldItem* CastToWorldItem() const;
	stCD_EntityTransitionable* CastToTransitionable() const;
	void DebugInfoAsNpc() const;
	void DebugInfoAsPlayer() const;
	void DebugInfoAsMonster() const;
	void DebugInfoAsWaypoint() const;
	void DebugInfoAsAreaTransition() const;
	void DebugInfoNoHuman() const;
	void DebugInfoChest() const;
	void DebugInfoWorldItem() const;
	void DebugInfoTransitionable() const;
	void DebugMonsterSkillInfo() const;
	//////////////////////////////////////////////////////////////////////////
	stCD_Positioned* GetPositioned() const;
	stCD_Render* GetRender() const;
	stCD_Actor* GetActor() const;
	//������Ժ����������йذɣ�����ʹ֮���ֵ���NPC
	stCD_EntityAttrNPC* GetNpc() const;
	//��������Բ���NPC���
	stCD_EntityAttrClientNpc* GetClientNpc() const;
	stCD_EntityAttrMonster* GetMonster() const;
	//��Ҫ�������Ĺ�һ�����������
	stCD_EntityAttrDiesAfterTime* GetDiesAfterTime() const;
	//ʹ�ô��;������ֵĴ����Ų����������
	stCD_EntityAttrPortal* GetPortal() const;
	stCD_Pathfinding* GetPathfinding() const;
	stCD_EntityAttrTargetable* GetTargetable() const;
	stCD_EntityAttrTransitionable* GetTransitionable() const;
	void DebugInfo() const;

private:
	bool IsNoHumain(pt_cwsz meta_name) const;
	stCD_EntityNoHuman* CastToNoHuman(pt_cwsz meta_name) const;
};
static_assert(g_so_entity_id_ == offsetof(stCD_EntityPosBased, id_), "");
static_assert(g_so_entity_base_pos_attr_ == offsetof(stCD_EntityPosBased, attr_pos_), "");

//��Ʒʵ�����
struct stCD_EntityItemBased : stCD_EntityBase{
	//////////////////////////////////////////////////////////////////////////
	//**********��������ĺ���֮ǰ�������˵���IsValid�ж�һ�¡�
	enCD_ItemType GetItemType() const;
	//������Ʒ������������Ƿ��ؿգ���ʾ�����Ʒ������
	stCD_AttrDbItemBase* GetAttrDbBase() const;
	stCD_TblItemBaseItemTypes* GetBaseItemType() const;
	//Ʒ���ò��ϣ����ع�����
	stCD_AttrDbQuality* GetAttrDbQuality() const;
	stCD_AttrDbAttributeRequirements* GetAttrDbAttributeRequirements() const;
	stCD_AttrDbSkillGem* GetAttrDbSkillGem() const;
	stCD_EntityAttrDbFlask* GetAttrDbFlask() const;
	stCD_EntityAttrItemBase* GetAttrBase() const;
	stCD_EntityAttrMods* GetAttrMods() const;
	stCD_EntityAttrStack* GetAttrStack() const;
	stCD_EntityAttrSockets* GetAttrSockets() const;
	stCD_EntityAttrUsable* GetAttrUsable() const;
	stCD_EntityAttrCharges* GetAttrCharges() const;
	stCD_EntityAttrSkillGem* GetAttrSkillGem() const;
	//////////////////////////////////////////////////////////////////////////
	//�·�����
	bool IsArmour() const;
	//���ܱ�ʯ
	bool IsSkillGem() const;
	//////////////////////////////////////////////////////////////////////////
	void DebugInfo() const;
};

//UNICODE "Metadata/Effects/PermanentEffect"
struct stCD_EntityEffectsBased : stCD_EntityBase{};

template<typename TypeT, typename EntityBaseT = stCD_EntityPosBased>
struct stCD_EntityBaseT : EntityBaseT{};

template<typename TypeT>
struct stCD_EntityItemBasedT : stCD_EntityBaseT<TypeT, stCD_EntityItemBased>{};

//////////////////////////////////////////////////////////////////////////
typedef GameVector<stCD_PassiveSkillVertex*> stCD_PassiveSkillVertexCont;
struct stCD_PassiveSkillVertices{
	p_mem_placeholder(4 * 2);
	pt_dword						ukn_dw_;
	pt_dword						ukn_dw1_;
	stCD_PassiveSkillVertexCont		vertices_;			//���澹ȻҲ������stCD_PassiveSkillVertex����ָ��
	p_mem_placeholder(4 * 2);							//�������ֶ��п��ܲ���������ṹ��
};
typedef stCD_PairAdjacent<stCD_PassiveSkillVertices, void> stCD_PassiveSkillVerticesSmartPtr;

struct stCD_PassiveSkillEdge{
	stCD_PassiveSkillVertex*	from_;
	stCD_PassiveSkillVertex*	to_;

	friend std::ostream& operator << (std::ostream& ostm, const stCD_PassiveSkillEdge& v);
};
typedef GameVector<stCD_PassiveSkillEdge*> stCD_PassiveSkillEdgeCont;

struct stCD_PassiveSkillVertex{
	pt_dword							ukn_dw_;				//=0
	stCD_TblItemPassiveSkillPair		passive_skill_;
	p_mem_placeholder(4 * 3);				//������ֵ
	stCD_PassiveSkillVerticesSmartPtr	vertices_;				//$18,�����Ǹ�����ָ��
	stCD_DbTblPassiveSkillGraph*		db_tbl_graph_;
	stCD_PassiveSkillEdgeCont			edges_in_;				//$24�����
	stCD_PassiveSkillEdgeCont			edges_out_;				//$30������

	void DebugInfo() const;
};
static_assert(0x30 == offsetof(stCD_PassiveSkillVertex, edges_out_), "");
typedef stCD_GameHash_map<stCD_TblItemPassiveSkillPair, stCD_PassiveSkillVertex*> stCD_PassiveSkillVertexHashMap;

struct stCD_DbTblPassiveSkillGraph : stCD_DbTblBase{
	stCD_UknGameVector				ukn_vector_;
	stCD_PassiveSkillVertexHashMap	vertices_;					//$c
	stCD_UknGameVector				ukn_vector1_;				//$2c
	GameWString						graph_file_path_;			//$38,"Metadata/PassiveSkillGraph.psg"
	pt_dword						ukn_dw_;
	stCD_DbPassiveSkill*			db_passive_skill_;			//$54
	stCD_PassiveSkillHashMap		hash_passive_skills_;		//$58
	stCD_UknGameHash_map			ukn_hash1_;					//$78
	stCD_UknGameVector				ukn_vector2_;				//$98

	void DebugInfo() const;
};
static_assert(0 == offsetof(stCD_DbTblPassiveSkillGraph, ukn_vector_), "");
static_assert(0x54 == offsetof(stCD_DbTblPassiveSkillGraph, db_passive_skill_), "");
static_assert(0x98 == offsetof(stCD_DbTblPassiveSkillGraph, ukn_vector2_), "");
typedef stCD_DbBaseT<stCD_DbTblPassiveSkillGraph> stCD_DbPassiveSkillGraph;
//////////////////////////////////////////////////////////////////////////
typedef stCD_SafeVector<stCD_SafeGameWString> stCD_SkillAttrNameCont;
struct stCD_TblItemSkillStatDescriptions{
	stCD_SkillAttrNameCont			skill_attr_names_;
	stCD_UknGameVector				ukn_vector_;
};
typedef std::vector<std::wstring> stCD_MySkillAttrNameCont;

struct stCD_DbTblSkillStatDescriptions : stCD_DbTblBase{
	//��������������Ϣ��ӳ��
	typedef stCD_GameHash_map<stCD_SafeGameWString, stCD_TblItemSkillStatDescriptions> SkillStatDescHashMap;

	stCD_UknGameHash_map			ukn_hash_map_;
	GameWString						self_file_path_;		//"Metadata/StatDescriptions/skill_stat_descriptions."
	SkillStatDescHashMap			skill_stat_desc_map_;
};
static_assert(0x38 == offsetof(stCD_DbTblSkillStatDescriptions, skill_stat_desc_map_), "");
struct stCD_DbSkillStatDescriptions : stCD_DbBaseT<stCD_DbTblSkillStatDescriptions>{
	struct stAttrNameInfo{
		std::wstring				skill_name_;
		stCD_MySkillAttrNameCont	attr_name_cont_;
	};
	typedef std::hash_map<pt_cwsz, stAttrNameInfo, RStd::hash_compare<pt_cwsz, StdEx::LessChar<wchar_t> > > MyHashMap;

	static const stCD_MySkillAttrNameCont* FindSkillAttr(pt_cwsz skill_en_name);
	bool ResolveMyHashMap();

private:
	static MyHashMap		my_hash_map_;
};

struct stCD_SkillTipsRow{
	stCD_SafeGameWString		str_tips_row_;			//ÿ����ʾ���ַ���
	stCD_SafeGameWString		ukn_str_;				//һ�㶼Ϊ��
};
static_assert(0x30 == sizeof(stCD_SkillTipsRow), "");
typedef stCD_SafeVector<stCD_SkillTipsRow> stCD_SkillTipsRowCont;

struct stCD_SkillAttr{
	typedef GameVector<pt_dword> AttrValueIdCont;

	pt_pcvoid			vtbl_;
	pt_dword			ukn_dw_;
	stCD_UknGameVector	ukn_vec1_;
	AttrValueIdCont		attr_value_ids_;
};
static_assert(0x14 == offsetof(stCD_SkillAttr, attr_value_ids_), "");
typedef stCD_PairAdjacent<stCD_SkillAttr, void> stCD_SkillAttrSmartPtr;
//���������������Ե�ӳ�䡣
typedef stCD_GameHash_map<stCD_SafeGameWString, stCD_SkillAttrSmartPtr> stCD_SkillAttrHashMap;

struct stCD_DbTblMinionSpellSkillStat : stCD_DbTblBase{
	stCD_SkillAttrHashMap		skill_attr_hash_map_;

	stCD_SkillAttr* FindSkillAttr(pt_cwsz attr_name) const;
};
typedef stCD_DbBaseT<stCD_DbTblMinionSpellSkillStat> stCD_DbMinionSpellSkillStat;
//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)
