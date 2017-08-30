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
	int GetMaxMp() const;
	inline GClass::stBasePro& GetBasePro(){ return base_pro_; }
	inline pt_dword GetRoleLvl(){ return base_pro_.level_; }
	inline enCD_kMapDifficulty GetDiffLvl() const { return difficulty_; }
	const std::wstring& GetJobName() const{ return job_name_; }
	inline bool IsMoving() const{ return is_moving_; }
	bool IsLockUseFlask() const{ return lock_use_flask_; }
	void LockUseFlask(bool lock);
	int GetAreaId() const override;
	bool Update() override;

	//�ƶ����
public:
	bool EnsureMoveToTheArea(const Fn_GenAreaSteps& fn);
	bool OnTraMapOver();
	bool SmartMove(const stCD_VecInt& dst_pos);
	//�ȴ���ɫ���ƶ�
	bool WaitRoleCanMove(pt_dword timeout);
	GameObjBasePtrT MoveToTheObj(const GA_SmartConsumerT& consumer, const GameObjBasePtrT& obj);
	GameObjBasePtrT MoveToTheObj(const GA_SmartConsumerT& consumer, bool clear_mark_pos, const std::string& obj_name, const GameObjMgrPtr& obj_mgr = nullptr, bool remem_find = true);
	enOpenVisitorRes PreOpenObj(const GameObjBasePtrT& obj);
	enOpenVisitorRes MoveToOpenObj(const GA_SmartConsumerT& consumer, const GameObjBasePtrT& obj);
	enOpenVisitorRes MoveToOpenObj(const GA_SmartConsumerT& consumer, bool clear_mark_pos, const std::string& obj_name, const GameObjMgrPtr& obj_mgr = nullptr, bool remem_find = true);
	bool SmartMoveMap(const std::string& dst_map_name, enCD_kMapDifficulty diff_lvl = kMD_Invalid, bool is_use_item = false);
	bool MoveOtherMapByWayPoint(enCD_kMapDifficulty difficulty, const std::string& dst_map_name);
	bool UseWayReelToMap(const std::string& dst_map_name = kEmptyStr);
	bool MoveHidePosByWayPoint() const;

private:
	bool MoveMapByWaypoint(enCD_kMapDifficulty difficulty, const std::string& dst_map_name);
	bool MoveToHidePosByWayPoint() const;
	bool DoMoveToTheAreaByStep(const AreaVertexPtr& vertex);

	//�������
public:
	bool PreKillMonster();
	//ȫͼɱ��
	bool KillAllMonsters(float tra_map_rate, int remaining);
	//ɱ����Ŀ��
	bool KillToOpenObj(const std::string& dst_name, bool remem_find = true);
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
	//ɱ��ָ��λ��
	bool KillMoveTo(const stCD_VecInt& dst_pos);
	bool KillMoveTo(const std::string& dst_pos_name);
	void OnMonsterDied(pt_dword entity_id);
	//ɱ�Ÿ�����ƶ�����
	bool KillFollowMovement();
	
	//��Ʒ���������
public:
	bool TakeupItem(enCD_InventoryType type, const stCD_VecInt& pos);
	bool PutDownItem( const stCD_VecInt& dst_pos, enCD_InventoryType dst_inventory_type);
	bool TakeoffGem(enCD_InventoryType type, const stCD_VecInt& pos,int index);
	bool InsideGem(enCD_InventoryType type, pt_dword item_id,int index);
	//npc��Ʒ�ŵ��Լ��ı�������繺����Ʒ��ѡ����������
	//bool NpcItemToInventory(const GItemBase& item, const stCD_VecInt& dst_pos, enCD_InventoryType inventory_type);
	bool UseEatFlask(const GItemBase& flask);
	bool MergeItem(const GItemBase& item);
	bool DestroyItem(const GItemBase& item, bool need_takeup);
	bool WaitDstItem(GPackageBase* packet, const GChecksumType& bag_inventories_checksum);

public:
	bool WaitDstHasItem(GPackageBase* packet, const GChecksumType& bag_inventories_checksum);
	//ȡ����ʯ
	bool SendTakeoffGem(const GItemBase& equip, pt_dword slot_idx);
	//��Ƕ��ʯ
	bool SendInsideGem(const GItemBase& equip, pt_dword slot_idx);
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
	GameObjBasePtrT FindNearestObj(enGameObjType obj_type);
	GameObjBasePtrT FindNearestObj(const std::string& obj_name);
	GameObjBasePtrT FindNearestMonsterObj(const std::string& obj_name);

	//�㷨�����Ը���
public:
	void RememberObjs(const GameObjMgrBase& obj_mgr);
	void ClearRememberedObjs();
	const GameObjMgrBase& GetRememberedObjs() const;
	void EraseRememberId(const GameObjBase& obj);

	//for test
public:
	void TestDebug(const std::string& str);
	void TestChangeMap(int difficulty, const std::string& dst_map_name);
	void TestCloseUi(int type);
	void TestTalkToNpc(const std::string& talk_label);
	bool TestPlayerMove(const stCD_VecInt& dst_pos, int p1, int p2, int p3, int p4, int p5);
	
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
	stCD_LifeDataHp			hp_;
	stCD_LifeData			mp_;
	stCD_LifeData			shield_;
	pt_dword				max_mp_;

private:
	GameObjMgrCont			remembered_objs_;
	//int						on_tra_map_over_deep_;
	int						move_to_area_deep_;
	bool					lock_use_flask_;

	//config
public:
	enOpenChestFlag			auto_open_chest_;
	bool					auto_pickup_item_;
	bool					auto_open_waypoint_;
	bool					auto_open_transitionable_;
	bool					auto_lvl_up_skill_gem_by_default_;
	bool					room_open_way_reel_;
};
