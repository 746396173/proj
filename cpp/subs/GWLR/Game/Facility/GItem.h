#pragma once
/*
@author zhp
@date 2014/7/1 20:40
@purpose for items
*/
#include <Common/GameObjBase.h>
#include "GTypes.h"
#include <list>
#include <Common/UsefulFunc.h>
#include <json/value.h>
#include <map>
#include <functional>
#include <Common/Iterator.h>
#include <Common/RegexMore.h>
#include "GNpc.h"
#include <boost/shared_ptr.hpp>


class ItemInfoBase{
public:
	ItemInfoBase();

protected:
	bool From(const stCD_ItemDb& item_db);

public:
	std::string				item_name_;
	int						item_lvl_;
	int						own_limit_;			//ӵ������
	int						carry_limit_;		//Я������
	int						die_jia_limit_;		//��������
	CD_En_ItemCategory		item_type_;
	CD_En_ItemType			equip_part_type_;
	CD_En_EquipPartSubType_Weapon	equip_part_sub_type_;
	int						player_lvl_;
	CD_En_ItemQuality		item_quality_;
	int						item_id_;
};
class ItemDb : public GGameObjBase, public ItemInfoBase{
public:
	//����װ������
	struct stEquipLvlUpInfo{
		stEquipLvlUpInfo();

		int									dst_item_id_;
		std::vector<stCD_MaterialInfo>		materials_;
	};

public:
	ItemDb();
	const stCD_MaterialInfo* FindLvlUpInfoByMaterialId( int material_item_id ) const;
	void DebugInfo() const override;

private:
	bool UpdateImpl() override;
	void DoUpdateClear() override;

public:
	const stCD_ItemDb*	item_db_;
	std::vector<stEquipLvlUpInfo>		equip_lvl_up_;
};

class ItemDbMgr : public GGameObjMgrBase, public Singleton<ItemDbMgr, Singleton_MakeMe>{
public:
	bool RebuildAll() override;
	const ItemDb* FindById( int item_id ) const;
	const ItemDb* FindByName( const std::string& item_name ) const;
	const ItemDb* FindByMatchName( const std::string& item_name ) const;
	const ItemDb* FindByMaterial(int material_item_id, int dst_item_lvl, CD_En_ItemQuality dst_item_quality) const;
	void DebugInfo() const override;

private:
	bool UpdateAllImpl() override;
	bool RebuildAllImpl() override;
	void DoRebuildUpdateClear() override;

private:
	std::vector<ItemDb>	items_;
};

class GItemMgrBase;
class GItem : public GGameObjBase, public ItemInfoBase{
public:
	GItem();

public:
	GType::enEquipPartIndex ItemIdx2EquipPartIdx() const;
	GType::enEquipPartIndex Equip2EquipPartIdx() const;
	bool IsEquip() const;
	CD_En_EquipPartSubType_Weapon EquipSubType2Weapon() const;
	GType::enEquipPartSubType_Defense EquipSubType2Defense() const;
	GType::enEquipPartSubType_Decorate EquipSubType2Decorate() const;
	pt_dint CalcItemGoodsValue() const;
	bool IsSuCai() const;
	bool CanBeUsed() const;
	bool IsFree() const;

public:
	const ItemDb* GetItemTemplate();

private:
	bool UpdateImpl() override;
	void DoUpdateClear() override;

	//another
public:
	//װ���Ƚ�
	bool EquipLessThan( const GItem& rhs ) const;
	friend bool operator == ( const GItem& lhs, const GItem& rhs );

	//test
public:
	void DebugInfo() const override;

	//static function
public:

public:
	const stCD_Item*		the_item_;
	GItemMgrBase*			item_mgr_ptr_;
	const ItemDb*		item_template_;
	int						item_idx_;			//slot_idx

public:
	pt_dint					item_serial_;
	int						sell_price_;		//���ۼ۸�
	int						item_cnt_;
	CD_En_BindFlag			bind_type_;
};

const GItem kItemInvalid;

class GItemMgrBase : public GGameObjMgrBase{
public:
	typedef std::list<GItem> ContT;
	typedef TraverseTraits<GItem&, GItem&> ItemTraTraits;
	typedef ItemTraTraits::IteratorBase GameItemIterBase;
	typedef ItemTraTraits::IteratorBasePtr GameItemIterPtr;
	typedef ItemTraTraits::DoAnyTraverse DoAnyGameItemFuncT;
	typedef ItemTraTraits::DoEveryTraverse DoEveryGameItemFuncT;
	typedef ItemTraTraits::DoCompFuncT DoCompFuncT;
	typedef std::vector<GItem*> ItemPtrContT;
	typedef GObjFilter<GItem> ItemFilterT;
	typedef ItemFilterT::SelfPtrT ItemFilterPtrT;

	//�ȼ��뱳������֮���ӳ��
	struct stLevel2InventoryMaxCnt{
		typedef std::map<std::pair<int, int>, int> MapT;
		typedef MapT::value_type ValueType;
		//�ɵȼ��õ����������
		int GetInventoryMaxCnt( int lvl ) const;

		MapT				map_;
	};

public:
	GItemMgrBase();
	void SetTabCategory(CD_En_TabCategory tab_category);
	CD_En_TabCategory GetTabCategory() const;
	ContT& GetItems();
	const ContT& GetItems() const;
	//�õ�����
	virtual int GetFreeSlotIndex() const;
	//�õ���������
	int GetGridMaxCnt() const;
	//�õ�������
	int GetFreeCnt() const;
	//������Ʒ���ǽ����ŵ�
	bool AllItemNextTo() const;
	//��������
	bool PacketBeFulled() const;
	GItem* FindByName( const std::string& item_name, bool is_bind = true );
	GItem* FindByName_Cnt( const std::string& item_name, bool is_bind = true, int item_cnt = 1 );
	GItem* FindByMatchName( const std::string& item_name, bool is_bind = true );
	GItem* FindById( int item_id );
	int GetTheItemTotalCnt( int item_id );
	int GetTheItemTotalCnt( const std::string& item_name );
	template<typename T>
	void AppendItems(T& the_items){
		std::copy(items_.begin(), items_.end(), std::back_inserter(the_items));
	}

	//�����Ͳ���
public:
	//��������
	GameItemIterPtr TraverseIf( const DoAnyGameItemFuncT& func );
	//֧��ģ��ƥ��
	GameItemIterPtr TraverseByMatchName( const std::string& item_name );
	GameItemIterPtr TraverseByMatchName_Cnt( const std::string& item_name, int cnt );
	GameItemIterPtr TraverseByName( const std::string& item_name );
	GameItemIterPtr TraverseByItemId( int item_id );
	//���ҵ�һ��
	GItem* FindIf( const DoAnyGameItemFuncT& func );
	GItem* FindBySlotIndex( int slot_index );
	GItem* FindByName_Lvl( const std::string& item_name, int item_lvl );
	GItem* FindBySerial( const LONGLONG& item_serial );

	//��Ʒ����
public:

protected:
	bool UpdateAllImpl() override;
	bool RebuildAllImpl() override;
	void DoRebuildUpdateClear() override;

	//test
public:
	void DebugInfo() const override;

protected:
	CD_En_TabCategory		tab_category_;
	ContT					items_;	
	ItemFilterPtrT			trade_filter_;

protected:
	int						grids_max_cnt_;

protected:
	stCD_GridsMgr*			grids_mgr_;
};

//������Ʒ
class GItemMgr_Package : public GItemMgrBase{
public:
	GItemMgr_Package();
	//�õ�����Ӵ���С
	int GetFreeSlotIndex() const;

private:
	bool RebuildAllImpl() override;
};

//װ����Ʒ
class GItemMgr_Equip : public GItemMgrBase{
public:
	GItemMgr_Equip();

private:
	bool RebuildAllImpl() override;
};

//�ֿ���Ʒ
class GItemMgr_Store : public GItemMgrBase{
public:
	GItemMgr_Store();

private:
	bool RebuildAllImpl() override;
};

//�زĲֿ�
class GItemMgr_SuCai : public GItemMgrBase{
public:
	GItemMgr_SuCai();

private:
	bool RebuildAllImpl() override;
};

class GItemMgr_Task : public GItemMgrBase{
public:
	GItemMgr_Task();

private:
	bool RebuildAllImpl() override;
};

//�ʼ�
class GMailItem : public GGameObjBase{
public:
	struct stItem{
		int		item_id_;
		int		item_cnt_;
	};

public:
	GMailItem();

private:
	bool UpdateImpl() override;
	void DoUpdateClear() override;

public:
	stCD_MailInfo*		mail_;

public:
	std::string			mail_title_;
	pt_dint				mail_serial_;
	std::vector<stItem>	items_;
	int					gold_;
};

class GMailMgr : public GGameObjMgrBase, public Singleton<GMailMgr, Singleton_MakeMe>{
public:
	const GMailItem* FindBySerial( const pt_dint& mail_serial );
	const std::vector<GMailItem>& GetMails() const;

private:
	bool RebuildAllImpl() override;
	bool UpdateAllImpl() override;

private:
	std::vector<GMailItem>		mails_;
};

//����
class GManufactureDbMgr : public GGameObjBase, public Singleton<GManufactureDbMgr, Singleton_MakeMe>{
public:
	typedef std::vector<stCD_MaterialInfo> MaterialContT;
	struct stItemFactureDb{
		int				facture_id_;		//����ID
		int				dst_item_id_;
		std::string		dst_item_name_;
		MaterialContT	materials_;
	};
	typedef std::vector<stItemFactureDb> ItemsFactureContT;

public:
	bool Update() override;
	const stItemFactureDb* FindByMaterial(int material_item_id, int dst_item_lvl, CD_En_ItemQuality dst_item_quality) const;
	const stItemFactureDb* FindByDstItemName( const std::string& dst_item_name ) const;
	void DebugInfo() const override;

private:
	bool UpdateImpl() override;
	void DoUpdateClear() override;

public:
	ItemsFactureContT		items_facture_info_;
};

//������
class GSupplyBox : public GGameObjBase, public Singleton<GSupplyBox, Singleton_MakeMe>{
public:
	struct stSupplyItemInfo{
		int		slot_key_;
		int		item_id_;
		int		item_cnt_;
	};
	typedef std::vector<stSupplyItemInfo> ItemsInfoContT;

public:
	void DebugInfo() const override;

private:
	bool UpdateImpl() override;
	void DoUpdateClear() override;

public:
	ItemsInfoContT		items_info_;
};

//���
class GGiftItem : public GClass::BTreeBase{
public:
	GGiftItem();
	void DebugInfo() const override;
	bool CanGain() const;

private:
	bool UpdateImpl() override;
	void DoUpdateClear() override;

public:
	int				gift_bag_id_;
	int				flag_;
	std::string		gifg_name_;
};

class GGiftItemMgr : public GClass::BTreeMgr_SkipRoot<GGiftItem>, public Singleton<GGiftItemMgr, Singleton_MakeMe>{
public:
	void DebugInfo() const override;
	const GGiftItem* FindGift( int id ) const;

private:
	bool RebuildAllImpl() override;
};