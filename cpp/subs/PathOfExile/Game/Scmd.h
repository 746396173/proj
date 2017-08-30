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

protected:
	void BindGlobalFn() override;
	void BindClass() override;
	void BindScriptCommand(luabind::module_& mod) override;
	void BindConst() override;
	void BindTest() override;

	//����
public:
	static void EnableAutoOpenChest(enOpenChestFlag flag);
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
	//�������õ�ͼ
	static void SetResetMap(bool reset);
	//���������Թ������ȼ�
	static void SetLabyrinthLevel(pt_int level);

	//��Ʒ����
public:
	//������Ϲ���
	static GFilterItemPtr CreateGroupFilter(const luabind::object& tbl);
	//�������˶���
	static GFilterItemPtr CreateFilterObj(enItemFilterType filter_type, const luabind::object& tbl);
	//���ʰȡ����
	static void AddPickUpFilter(GFilterItemPtr filter_ptr);
	//��Ӵ�ֹ���		
	static void AddStoreFilter(GFilterItemPtr filter_ptr);
	//��ӳ��۹���
	static void AddSellFilter(GFilterItemPtr filter_ptrl);
	//���ϴ������
	static void AddAginRinseFilter(GFilterItemPtr filter_ptr);
	//�����Զ�ʹ��ҩ��
	static void SetAutoUseFlask(float hp_rate, float mp_rate);
	//���ñ������ӿ�������
	static void SetMainBagMinFree(int wight, int hight);
	//���ñ�ʯ����
	static bool SetGemLink(pt_dword min_lvl, pt_dword max_lvl, const std::string& main_gem, const luabind::object& tbl);
	//���ô�����������
	static void SetWearWeaponType(enWeaponCompositeCate type);
	//�������б�ʯ����
	static void ClearAllGemLink();
	//��������
	static void SetItemScore(enGradeValue score_type, const luabind::object& tbl);
	//����ҩƷ����
	static void SetBagFlaskCnt(const luabind::object& tbl);
	//����������
	static void SetYiJieFilter(enItemFilterType filter_type, const luabind::object& tbl);
	//������װ����
	static void SetEmboitementCnt(int cnt);
	//���ý��뷿�俪������
	static void SetJoinRoomOpenWayReel(bool open);
	//�����Ʒ���Խ���
	static void ClearItemAttrParser();
	//��Ʒ���Խ���
	static CSV_NodePtr CreateItemAttrParser(const std::string& pro_name);
	//�������
	static void ClearFilter(int filter_type);
	//����ϴ��װ��
	static GItemAgainRinsePtr CreateItemTypeRinse(enCD_ItemType item_type, pt_dword min_lvl, pt_dword max_lvl);

	//����
public:
	//�ƶ���ָ��λ��
	static bool SmartMoveTo(const stCD_VecInt& dst_pos);
	//ȫͼɱ��
	static bool KillAllMonster(bool clear_mark_pos_first, float tra_map_rate, int remaining);
	//ɱ����Ŀ��
	static bool KillToOpenObj(const std::string& dst_name, bool remem_find = true);
	//ɱ��ɱ��Ŀ��
	static bool KillToKillTheObj(const std::string& dst_name);
	static bool KillToKillTheObj_(const GameObjBasePtrT& obj);
	//ɱ��ָ����ͼ
	static bool KillToTheMap(const std::string& dst_map_name, int diff_lvl, bool use_way, bool use_near_way);
	//ɱ��Ŀ��
	static bool KillToTheObj(const std::string& dst_name);
	//ɱ��ɱ��NPC��
	static bool KillToKillNpc(const std::string& dst_name);
	//�ƶ���Ŀ��
	static bool MoveToTheObj(const std::string& obj_name);
	static bool MoveToTheObj_(const GameObjBasePtrT& obj);
	//ɱ������
	static bool KillToTheRoom(const std::string& dst_name);
	//�ȴ����ƶ�
	static bool WaitRoleCanMove(pt_dword timeout);
	//�ƶ���ָ����ͼ
	static bool SmartMoveMap(const std::string& fb_name, int diff);
	//ʹ�ô��;��ᵽ��ͼ
	static bool UseWayReelToMap(const std::string& dst_map_name);
	//ɱ��ָ��λ��
	static bool KillMoveTo(const std::string& name);
	static bool KillMoveTo_(const stCD_VecInt& dst_pos);
	//ɱ���ı�״̬
	static bool KillChangeState();
	//ɱ�Ÿ�����ƶ�����
	static bool KillFollowMovement();

	//�������
public:
	//��Ŀ��
	static bool OpenObj(const std::string& item_name);
	static bool OpenObj_(const GameObjBasePtrT& obj);
	static GameObjBasePtrT FindNearestObj(enGameObjType obj_type);
	static GameObjBasePtrT FindNearestObj_(const std::string& obj_name);
	static GameObjBasePtrT FindNearestMonsterObj(const std::string& mon_name);
	//��ý�ɫ�ȼ�
	static DWORD GetRoleLvl();
	//�Ի�Npc(npc����ϵ�����Ϊ����)
	static bool TalkToNpc(const std::string& talk_content);
	//������Ʒ����ȡ����
	static bool TakeNpcItem(const std::string& item_name);
	static bool TakeNpcItem_(int index);
	//�򿪸�������
	static bool CheckNearestObjAndOpen(const std::string& obj_name);

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
	//�Զ�ϴ��
	static void AutoAgainRinseEquip();
	//���ұ�����Ʒ
	static GItemBasePtr FindPakcetItem(const std::string& item_name);
	//�Զ����
	static bool AutoStoreBagItemToStore();
	//�Զ�����Ʒ  
	static bool AutoSellBagItem(const std::string& npc_name);
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
	static int BuyItemByNpc(const std::string npc_name, const std::string& item_name,int cnt);
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
	//���������Ʒ����
	static void PrintBagItemWeight();
	//���������Ʒtips��Ϣ
	static void PrintBagItemTipsInfo();
	//�����Ʒ��ȡ��ʽ
	static bool AddItemPathway(const std::string& item_name, const std::string& town_name, const std::string& npc_name);
	//���ֹ�����Ʒ
	static int KeepBuyItem(const std::string& item_name, int item_cnt);
	//�Զ������ֿ��ͼ
	static bool UpLevelStashMap(const luabind::object& lua_obj);
	//�����Զ�����ʣ�౦ʯ�ȼ�
	static void SetAutoWearSurplusGem(pt_dword max_level);
	//���ֿⱦʯ��װ������
	static bool CheckStoreGemTotalQualityToBag(pt_dword total_quality);
	//������
	static bool AdjustPack();

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
	//��ռ��ܱ�ʯ������Ϣ
	static void ClearSkillGemLvlUpInfo();
	//��Ӽ��ܱ�ʯ������Ϣ
	static void AddSkillGemLvlUpInfo(const std::string& skill_gem_name, int max_lvl);

	//����
public:
	//��ǰ��ͼ���͵��Ƿ���
	static bool IsOpenWayPointByMap(const std::string& map_name);
	//ѡ�������Ϸ
	static bool SelectEnterGame(const std::string& role_name);
	//�������װ��
	static bool OpenMapDevice(const std::string& map_name);
	//�������Ҵ�����(��Ҫ���ڲ�����翪���Ĵ�����)
	static GameObjBasePtrT FindYiJieTransitonable();
	//��õ�ǰ��ͼ
	static const std::string& GetCurMapName();
	//��õ�ǰ���е�����ͼ
	static const std::string& GetCurYiJieMapName();
	//�����ƽ���ͼ��
	static bool OpenHideoutMapDeviceByCarft(const std::string& craft_name);
	//�Զ���½�ʺ�
	static bool AutoLoginAccount();
	//�ȴ��ٻ�������
	static bool WaitCalledDie(bool wait_called);
	//�����Թ�װ��
	static bool OpenLabyrinthDevice(pt_int select_level);
	//���δ�������
	static luabind::object GetUndoneLabyrinthMap();
	//��õ�ǰ�½�
	static int GetCurChapter();

	//ע�ᵽlua�е�˽�ú���
public:
	static void AddMapRoomRate(const std::string& map_name, int zoom_rate);
	static void UpdateCurMap();
	static void UpdateSelfArea();
	static void SetMapAreaInfo(const std::string& map_name, const luabind::object& areas);

public:
	inline static enWeaponCompositeCate GetWearWeaponType(){ return wear_weapon_type_; }
	inline static GFilterItemContPickUp& GetPickUpFilter() { return pick_up_filter_; }
	inline static GFilterItemContSmart& GetSaveStoreFilter(){ return save_Store_filter_; }
	inline static GFilterItemContSmart& GetSellItemFilter(){ return sell_item_filter_; }
	inline static GFilterItemContSmart& GetAgainRinseFilter(){ return again_Rinse_filter_; }
	inline static bool GetAutoWearEquip(){ return auto_wear_equip_; }
	inline static bool GetResetMap(){ return auto_reset_map_; }
	inline static pt_int GetOpenLabyrinthLvl(){ return open_labyrinth_Lvl_; }

private:
	static void AutoWearSomeEquipsImpl();
	static bool InStoreWhiteList(const GItemBase& item);
	static GItemBasePtr FindPacketItemByName(enCD_InventoryType type, const std::string& item_name);
	static bool SetItemColor(int item_color, enCD_ItemColor out_item_color);
	static bool AutoIdentifiedItem(bool all_indentified = false);
	static bool UseFlack(int index);
	static bool AutoWearLinkGem();
	static bool CheckHidePosMap(const std::string& dst_map, enCD_kMapDifficulty diff_lvl);

	//test
public:
	static int TestAutoLvlUpPassiveSkills(int type);
	static void TestCreateSelectRole(const std::string& area_name, int profession_type, const std::string& role_name);
	//���ƶ���Ŀ�꣬Ȼ���ж�Ŀ��λ�õ�ģ���Ƿ���Ψһ���Σ��������
	static void TestAutoDetectTerrainObjs(const luabind::object& obj_names);
	//���ݵ�ǰ��ɫ��λ�ã������radiusΪ�뾶�ĸ���������Ϣ��Ҫ��õ�����������ͼ�г��ֵĴ�����಻����max_cnt�Ρ���max_cnt==1ʱ�����ʾ���Ψһ���Ρ�
	static void TestDetectUniqueTerrain(int radius, int max_cnt);
	//���ݵ�����������λһ�����Σ�������������ݰ�����һ����������һ������֮��ľ���
	//���������ж�λ���ĵ�һ�����μ�ΪҪ��λ�ĵ���
	//terrain_cnt���Ϊ2��Ϊ3�Ļ������ܻ����
	//��ǰ��ɫ���ڵĵ������ڵ��������еĵ�һ�����Σ�Ҳ��������Ҫ��λ�򲶻�ĵ���
	//�ú�������ϸ��������¸����εľ������Ϣ����Ҫ�ɾ������Ϣ��λ��������
	//terrain_cnt==2��ʾ���������������Ϣ
	static void TestDetectOneTerrainArea(int radius, int terrain_cnt);
	//����һϵ�����������λһ����������
	static void TestDetectUniqueTerrainByPos(const luabind::object& positions);
	//������ǰ��ͼ������ָ���ĵ���
	static void TestTerrainSameInfo(const std::string& terrain_path);
	static void TestLoginAccount(const std::string& ac, const std::string& pwd, const std::string& gateway);
	static void TestActorUseSkill(const std::string& skill_name, const stCD_VecInt& dst_pos);
	static void TestTerminateCurSkill();
	static void TestGetInGameMainUiDlgCnt(int flag);

	//debug
public:
	static void DbgObjs(bool is_alive, const luabind::object& tbl);
	static void DbgSortedObjs(bool is_alive, const luabind::object& tbl);
	static void DbgPakcageItems(int package_type);
	static void DbgGSP_Resolver(bool is_vertex);
	static void DbgTestPrint(int value);
	
private:
	static GFilterItemContSmart							sell_item_filter_;
	static GFilterItemContSmart							save_Store_filter_;
	static GFilterItemContPickUp						pick_up_filter_;
	static GFilterItemCont								yi_jie_map_filter_;
	static GFilterItemContSmart							again_Rinse_filter_;

	static GAutoEatHpMp									auto_eat_hp_mp_;
	//static GAutoUpDateGem								auto_update_gem_;
	static enWeaponCompositeCate						wear_weapon_type_;
	static std::string									cur_yi_jie_map_;
	static pt_int										open_labyrinth_Lvl_;
	static bool											auto_reset_map_;
	static bool											auto_wear_equip_;
};