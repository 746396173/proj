#pragma once
/*
@author zhp
@date 2017/2/5 22:38
@purpose for game player info
*/
#include "GameObj.h"
#include "GSkill.h"
#include <Common/UsefulClass.h>
#include "GClass.h"
#include "GameObjMgr.h"

//////////////////////////////////////////////////////////////////////////
class GPlayer : public GameObjBase{
public:
	GPlayer();
};

class GPlayerMe : public GPlayer, public Singleton<GPlayerMe, Singleton_MakeMe>{
	typedef NameList<std::string>  NameList_StrT;

public:
	GPlayerMe();
	int GetCurHp() const override;
	int GetCurMp() const override;
	inline int GetMaxHp() const { return hp_.max_value_; }
	inline int GetMaxMp() const { return mp_.max_value_; }
	inline GClass::stBasePro& GetBasePro(){ return base_pro_; }
	inline pt_dword GetRoleLvl(){ return base_pro_.level_; }
	inline enCD_kMapDifficulty GetDiffLvl() const { return difficulty_; }
	const std::wstring& GetJobName() const{ return job_name_; }
	inline int GetCurAvoidSkillDeep() const{ return avoid_skill_deep_; }
	stCD_VecInt GetCurMovingDstPos();
	inline bool IsMoving() const{ return is_moving_; }
	GAutoUseSkill& GetAutoUseSkill(){ return auto_use_skill_; }

	//�ƶ����
public:
	bool DoMoveToTheAreaByStep(const stAreaVertex& vertex);
	bool OnTraMapOver();
	bool SmartMove(const stCD_VecInt& dst_pos);
	//�ȴ���ɫ���ƶ�
	bool WaitRoleCanMove(pt_dword timeout);
	GameObjBasePtrT MoveToTheObj(const GA_SmartConsumerT& consumer, bool clear_mark_pos, const GameObjBasePtrT& obj);
	GameObjBasePtrT MoveToTheObj(const GA_SmartConsumerT& consumer, bool clear_mark_pos, const std::string& obj_name, const GameObjMgrPtr& obj_mgr = nullptr);
	enOpenVisitorRes PreOpenObj(const GameObjBasePtrT& obj);
	enOpenVisitorRes MoveToOpenObj(const GA_SmartConsumerT& consumer, bool clear_mark_pos, const GameObjBasePtrT& obj);
	enOpenVisitorRes MoveToOpenObj(const GA_SmartConsumerT& consumer, bool clear_mark_pos, const std::string& obj_name, const GameObjMgrPtr& obj_mgr = nullptr);
	bool SmartMoveMap(const std::string& dst_map_name, enCD_kMapDifficulty diff_lvl = kMD_Invalid, bool is_use_item = false);
	bool MoveOtherMapByWayPoint(enCD_kMapDifficulty difficulty, const std::string& dst_map_name);
	bool UseWayToTown();

private:
	bool MoveMapByWaypoint(enCD_kMapDifficulty difficulty, const std::string& dst_map_name);

	//�������
public:
	bool PreKillMonster();
	//ȫͼɱ��
	bool KillAllMonsters();
	//ɱ����Ŀ��
	bool KillToOpenObj( const std::string& dst_name);
	bool KillToOpenObj(const GameObjBasePtrT& dst_obj);
	//ɱ��ɱ��Ŀ��
	bool KillToKillTheObj(const std::string& dst_name);
	bool KillToKillTheObj(const GameObjBasePtrT& dst_obj);		//�������ǣ�ɱ�������
	//ɱ��Ŀ��
	bool KillToTheObj(const std::string& dst_name);
	bool KillToTheObj(const GameObjBasePtrT& dst_obj);
	//ɱ������
	bool KillToTheRoom(const std::string& dst_name);
	//ɱ��ɱ��NPC��
	bool KillToKillNpc(const std::string& dst_name);
	bool UseSkill(const GSkillObj& skill, const stCD_VecInt& dst_pos);
	bool UseSkill(const std::string& skill_name, const stCD_VecInt& dst_pos);
	void OnMonsterDied(pt_dword entity_id);
	
	//��Ʒ���������
public:
	bool TakeupItem(enCD_InventoryType type, const stCD_VecInt& pos);
	bool PutDownItem( const stCD_VecInt& dst_pos, enCD_InventoryType dst_inventory_type);
	bool TakeoffGem(enCD_InventoryType type, const stCD_VecInt& pos,int index);
	bool InsideGem(enCD_InventoryType type, pt_dword item_id,int index);
	//npc��Ʒ�ŵ��Լ��ı�������繺����Ʒ��ѡ����������
	bool NpcItemToInventory(const GItemBase& item, const stCD_VecInt& dst_pos, enCD_InventoryType inventory_type);
	//ʹ����Ʒ
	bool UseItem(const GItemBase& item);
	bool UseItem(const GItemBase& item_src, const GItemBase& item_dst);
	bool UseEatFlask(const GItemBase& flask);
	bool MergeItem(const GItemBase& item);
	bool DestroyItem(const GItemBase& item, bool need_takeup);

private:
	bool SendTakeupItem(const GItemBase& item);
	bool SendPutDownItem( const stCD_VecInt& dst_pos, enCD_InventoryType inventory_type);
	bool WaitDstHasItem(GPackageBase& packet, const stCD_VecInt& dst_pos);
	//ȡ����ʯ
	bool SendTakeoffGem(const GItemBase& equip, pt_dword slot_idx);
	//��Ƕ��ʯ
	bool SendInsideGem(const GItemBase& equip, pt_dword slot_idx);
	//ʹ��ҩ��
	bool SendUseFlask(const GItemBase& flask);
	//ʹ����Ʒ
	bool SendUseItem(const GItemBase& item);
	//ʹ����Ʒ��������һ����Ʒ���������������װ����
	bool SendUseItemTo(const GItemBase& item_src, const GItemBase& item_dst);
	//�ϲ���Ʒ
	bool SendMergeItem(const GItemBase& dst_item);
	//�ݻ���Ʒ
	bool SendDestroy(const GItemBase& dst_item);

	//�������
public:
	bool AcceptAnyQuest();

	//npc���
public:

	//ui���
public:
	//�ر�������壬����Npc��塢���ؽ�ɫ���
	//������Ҫ�ر����Ĺ��ܣ������ر�npc��EscapeMenu������ͳһ���������
	bool CloseAllPanel(bool close_npc_panel = true);
	//��EscapeMenu�����򿪷��ؽ�ɫ���
	bool OpenEscapeMenu();
	//press EscapeMenu�İ����������Ҫ�ж�����Ϸ��״̬
	bool PressEscapeMenuItem(enCD_EscapeMenuButton bt_idx);
	//�Ի�Npc
	bool TalkToNpc(const std::string& talk_label);
	//�ر�npc
	bool CloseNpcPanel();

private:
	bool PressEscOnceToClosePanel(int* cur_dlg_cnt);
	//�ر�EscapeMenu
	bool CloseEscapeMenu();
	//EscapeMenu�Ƿ��Ѵ�
	bool EscapeMenuOpened() const;

	//�������
public:
	GameObjBasePtrT FindNearestObj(GameObjType obj_type);
	GameObjBasePtrT FindNearestObj(const std::string& obj_name);
	GameObjBasePtrT FindNearestMonsterObj(const std::string& obj_name);

	//�㷨�����Ը���
public:
	void RememberObjs(const GameObjMgrBase& obj_mgr);
	void ClearRememberedObjs();
	const GameObjMgrBase& GetRememberedObjs() const;

	//for test
public:
	void TestDebug(const std::string& str);
	void TestChangeMap(int difficulty, const std::string& dst_map_name);
	void TestCloseUi(int type);
	void TestTalkToNpc(const std::string& talk_label);
	void TestAvoidPos(bool enable);
	bool TestPlayerMove(const stCD_VecInt& dst_pos);

private:
	bool SendUseSkill(pt_word skill_id, const stCD_VecInt& dst_pos);
	
private:
	bool UpdateImpl() override;
	void DebugInfo() const override;

public:
	bool SmartMoveTest(const stCD_VecInt* dst_pos);

private:
	bool					is_moving_;
	bool					is_openning_;

	GClass::stBasePro		base_pro_;
	pt_dword				job_id_;		//ְҵid
	enCD_kMapDifficulty		difficulty_;	//��ǰ���ڵ�ͼ�����ѵȼ�	
	
	std::wstring			job_name_;		//ְҵ����
	stCD_LifeData			hp_;
	stCD_LifeData			mp_;
	stCD_LifeData			shield_;

private:
	GameObjMgrCont			remembered_objs_;
	SharedMutex				moving_dst_pos_mutex_;
	const stCD_VecInt*		moving_dst_pos_;
	int						avoid_skill_deep_;
	int						on_tra_map_over_deep_;

	//config
public:
	GAutoUseSkill			auto_use_skill_;
	bool					auto_open_chest_;
	bool					auto_pickup_item_;
	bool					auto_open_waypoint_;
	bool					auto_open_transitionable_;
	bool					auto_lvl_up_skill_gem_by_default_;
};
