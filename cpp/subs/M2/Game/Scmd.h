#pragma once
/*
@author zhp
@date 2017/2/5	22:33
@purpose for script command
*/
#include <Common/UsefulClass.h>
#include <luabind/object.hpp>
#include <AppMix/WgLuaVm.h>
#include "Facility/GItem.h"
#include "Facility/GType.h"
#include "Facility/GPackageItemFilter.h"
#include "Facility/GActions.h"

class MyLuaThrdData : public GameDllLuaThrdData{
public:
	explicit MyLuaThrdData(lua_State* lstate);
	typedef std::vector<std::string> StrCont;
	typedef std::map<std::string, en_NpcMonster> NpcMonsterT;

protected:
	void BindGlobalFn() override;
	void BindClass() override;
	void BindScriptCommand(luabind::module_& mod) override;
	void BindConst() override;
	void BindTest() override;

	//����
public:
	static void EnableAutoOpenChest(bool enable);
	static void EnableAutoPickupItem(bool enable);
	static void EnableAutoOpenWaypoint(bool enable);
	static void EnableAutoOpenTransitionable(bool enable);
	static void EnableAutoLvlUpSkillGemByDef(bool enable);
	static void EnableAutoWearEquip(bool enble);
	//�����츳��
	static void SetPassiveSkillTree(const luabind::object& job_skill_nodes);
	//����Ĭ�ϴ�����ɫ��ְҵ
	static void SetDefCreateProfessionType(const std::string& profession_name);
	//����Ĭ�ϴ�����ɫ����
	static void SetDefCreateGameArea(const std::string& game_area);

	//��Ʒ����
public:
	//������Ϲ���
	static GFilterItemPtr CreateGroupFilter(const luabind::object& tbl);
	//�������˶���
	static GFilterItemPtr CreateFilterObj(en_ItemFilterType filter_type, const luabind::object& tbl);
	//���ʰȡ����
	static void AddPickUpFilter(GFilterItemPtr filter_ptr);
	//��Ӵ�ֹ���		
	static void AddStoreFilter(GFilterItemPtr filter_ptr);
	//��ӳ��۹���
	static void AddSellFilter(GFilterItemPtr filter_ptrl);
	//�����Զ�ʹ��ҩ��
	static void SetAutoUseFlask(float hp_rate, float mp_rate);
	//���ñ������ӿ�������
	static void SetMainBagMinFree(int wight, int hight);
	//���ñ�ʯ����
	static bool SetGemLink(const std::string& main_gem, const luabind::object& tbl);
	//���ô�����������
	static void SetWearWeaponType(enWeaponCompositeCate type);
	//�������б�ʯ����
	static void ClearAllGemLink();
	//��������
	static void SetItemScore(en_GradeValue score_type, const luabind::object& tbl);
	//����ҩƷ����
	static void SetBagFlaskCnt(const luabind::object& tbl);
	//����������
	static void SetYiJieFilter(en_ItemFilterType filter_type, const luabind::object& tbl);
	//������װ����
	static void SetEmboitementCnt(int cnt);
	//�����Ʒ���Խ���
	static void ClearItemAttrParser();
	//��Ʒ���Խ���
	static CSV_NodePtr CreateItemAttrParser(const luabind::object& fn);

	//����
public:
	//ȫͼɱ��
	static bool KillAllMonster(bool clear_mark_pos_first);
	//ɱ����Ŀ��
	static bool KillToOpenObj(const std::string& dst_name);
	//ɱ��ɱ��Ŀ��
	static bool KillToKillTheObj(const std::string& dst_name);
	static bool KillToKillTheObj_(const GameObjBasePtrT& obj);
	//ɱ��ָ����ͼ
	static bool KillToTheMap(const std::string& dst_map_name, int diff_lvl, bool use_way);
	//ɱ��Ŀ��
	static bool KillToTheObj(const std::string& dst_name);
	//ɱ��ɱ��NPC��
	static bool KillToKillNpc(const std::string& dst_name);
	//�ƶ���Ŀ��
	static bool MoveToTheObj(const std::string& obj_name);
	static bool MoveToTheObj_(const GameObjBasePtrT& obj);
	//ɱ������
	static bool KillToTheRoom(const std::string& dst_name);
	//�ȴ���ɫ���ƶ�
	static bool WaitRoleCanMove(pt_dword timeout);
	//�ƶ���ָ���ĸ��������֣��Ѷȵȼ���
	static bool SmartMoveMap(const std::string& fb_name, int diff);
	//���ͻس�
	static bool UseWayToTown();

	//�������
public:
	//�򿪶���
	static bool OpenObj(const std::string& item_name);
	static bool OpenObj_(const GameObjBasePtrT& obj);
	static GameObjBasePtrT FindNearestObj(GameObjType obj_type);
	static GameObjBasePtrT FindNearestObj_(const std::string& obj_name);
	static GameObjBasePtrT FindNearestMonsterObj(const std::string& mon_name);
	//��ý�ɫ�ȼ�
	static DWORD GetRoleLvl();
	//�Ի�Npc(npc����ϵ�����Ϊ����)
	static bool TalkToNpc(const std::string& talk_content);
	//������Ʒ����ȡ����
	static bool TakeNpcItem(const std::string& item_name);
	static bool TakeNpcItem_(int index);

	//ui���
public:
	//�ر��������
	static bool CloseAllPanel(bool close_npc_panel);
	//��EscapenMenu(��ESC�� �����ĶԻ���)
	static bool OpenEscapenMenu();
	//ѡ��EscapenMenu
	static bool SelectEscapenMenu(int index);

	//��Ʒ���
public:
	//�Զ���Ƕ��ʯ
	static int AutoWearSomeGem();
	//�Զ�����װ��
	static void AutoWearSomeEquips();
	//�Զ���ҩ
	static void AutoUseFlack(stCDR_OnHpMp::enValueType value_type);
	//�Զ�ʹ��ˮӡҩ��
	static void AutoUseUtilityFlask();
	//���ұ�����Ʒ
	static GItemBasePtr FindPakcetItem(const std::string& item_name);
	//���һЩ��Ʒ���ֿ�
	static bool AutoStoreBagItemToStore();
	//�Զ�����Ʒ   //�ں�������ֱ���������ڰ������ʹ��ڵ�����������ֵ�Ĳ���
	static bool AutoSellBagItem();
	//ʹ����Ʒ
	static bool UseItem(const std::string& item_name);
	//ʹ����Ʒ��Ŀ��(�����ڵ�ʹ��)
	static bool UseItemToDst(const std::string& src_name, const std::string& dst_name);
	//��Ʒ����
	static int GetItemCnt(const std::string& item_name);
	//�������ͻ����Ʒ����
	static int GetItemCntByType(enCD_ItemType type);
	//�������
	static bool HasTheQuestByName(const std::string& quest_name);
	//������Ʒ
	static bool BuyItemByNpc(const std::string npc_name, const std::string& item_name);
	//�Ƿ��ڳ���
	static bool InTown();
	//ʰȡ������Ʒ
	static bool PickUpQuestItem();
	//��õ�ǰ�Ѷȵȼ�
	static int GetCurDiffLvl();
	//�Ӳֿ�ȡ��ͼ(ֻ�����ȡ��ͼʹ�ã������˵�ͼ����)
	static int TakeOutYiJieMapFromStorage(int cnt);
	//�Ӳֿ���ȡ��Ʒ
	static int TakeOutItemByName(const std::string& item_name, int cnt);
	//�����ȡ��װ
	static bool CheckStoreEmboitementToBag();


	//����
public:
	//����ȫ��Σ�վ���
	static void SetGlobalDangerDistance(float screen_rate);
	//��������
	static CA_ActionPtr MakeSkill(const std::string& skill_name);
	//����ʬ�弼��
	static CA_ActionPtr MakeCorpseSkill(const std::string& skill_name);
	//��Ӽ���
	static void AddSkill(GA_SkillBase& skill);
	//��ռ���
	static void ClearSkills();

	//����
public:
	//��ǰ��ͼ���͵��Ƿ���
	static bool IsOpenWayPointByMap(const std::string& map_name);
	//ѡ�������Ϸ
	static bool SelectEnterGame(const std::string& role_name);
	//�������װ��
	static bool OpenMapDevice();
	//�������Ҵ�����(��Ҫ���ڲ�����翪���Ĵ�����)
	static GameObjBasePtrT FindYiJieTransitonable();
	//��õ�ǰ��ͼ
	static const std::string& GetCurMapName();

	//ע�ᵽlua�е�˽�ú���
public:
	static void AddMapRoomRate(const std::string& map_name, int zoom_rate);
	static void UpdateCurMap();
	static void SetMapAreaInfo(const std::string& map_name, const luabind::object& areas);
	//static StrCont& GetAllNpcMon();

public:
	inline static enWeaponCompositeCate GetWearWeaponType(){ return wear_weapon_type_; }
	inline static GFilterItemContPickUp& GetPickUpFilter() { return pick_up_filter_; }
	inline static GFilterItemContSmart& GetSaveStoreFilter(){ return save_Store_filter_; }
	inline static GFilterItemContSmart& GetSellItemFilter(){ return sell_item_filter_; }
	inline static bool GetAutoWearEquip(){ return auto_wear_equip_; }

private:
	static void AutoWearSomeEquipsImpl();
	static enCD_InventoryType IndexToPackType(int index);
	static bool InStoreWhiteList(const GItemBase& item);
	static GItemBasePtr FindPacketItemByName(enCD_InventoryType type, const std::string& item_name);
	static bool SetItemColor(int item_color, enCD_ItemColor out_item_color);
	static bool AutoIdentifiedItem();
	static bool UseFlack(int index);
	static bool AutoWearLinkGem();

	//test
public:
	static int TestAutoLvlUpPassiveSkills(int type);
	static void TestCreateSelectRole(const std::string& area_name, int profession_type, const std::string& role_name);

	//debug
public:
	static void DbgObjs(bool is_alive, const luabind::object& tbl);
	static void DbgSortedObjs(bool is_alive, const luabind::object& tbl);
	static void DbgPakcageItems(int package_type);
	static void DbgGSP_Resolver(bool is_vertex);

private:
	static GFilterItemContSmart							sell_item_filter_;
	static GFilterItemContSmart							save_Store_filter_;
	static GFilterItemContPickUp						pick_up_filter_;
	static GFilterItemCont								yi_jie_map_filter_;
	
	static GAutoEatHpMp									auto_eat_hp_mp_;
	static GAutoUpDateGem								auto_update_gem_;
	static enWeaponCompositeCate						wear_weapon_type_;
	static bool											auto_wear_equip_;
};