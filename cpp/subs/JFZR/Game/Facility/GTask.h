#pragma once
/*
@author zhp
@date 2014/8/7 12:24
@purpose for task
*/
#include "GClass.h"
#include <boost/optional.hpp>
#include "GAddr.h"

//��ǰְҵ������
class TaskCurJobTemplate : public GClass::BTreeBase{
public:
	typedef std::shared_ptr<TaskCurJobTemplate> SharedPtrT;
	
	class NpcCondition : public GClass::GGameTypeBase{
	public:
		class ApprovedStage : public GClass::GGameTypeBase{
		public:
			typedef GClass::stGameString GameType;

		public:
			bool Update();
			const std::wstring& GetCloneMapId() const;

		private:
			std::wstring			clone_map_id_;
		};
		typedef GClass::GGameTArray<std::vector<ApprovedStage> > ApprovedStagesTArray;
		//��ɱ����
		struct stNpcCondition{
			void*								vtbl_;
			DWORD								str_dwNpcConditionType;
			GClass::stGameString				npc_obj_id_;						//NPC id
			int									need_kill_cnt_;						//��Ҫ��ɱ������
			DWORD								str_dwBackAttackCount;
			DWORD								str_dwSpecialAttackUseCount;
			DWORD								str_dwDeadlySkillUseCount;
			GClass::GGameTArrayPlaceholder		str_theSkillUsageCounts;
			ApprovedStagesTArray::stGameTArray	approved_stages_;					//�������ڸ�����ͼ
			GClass::BTreeMgrBase::stGBTreeNodes	str_theNpcKillBySkill;
		};
		static_assert(sizeof(stNpcCondition) == sizeof(NPC_CONDITION), "");
		typedef stNpcCondition GameType;

	public:
		NpcCondition();
		bool Update();
		const std::wstring& GetMonsterId() const;
		int GetNeedKillCnt() const;
		const ApprovedStagesTArray& GetApprovedCloneMap() const;
		std::size_t GetApprovedSize() const;
		const ApprovedStage* GetFirstApproved() const;

	private:
		std::wstring			monster_id_;
		int						need_kill_cnt_;
		ApprovedStagesTArray	approved_clone_map_;			//�������ڸ���
	};
	typedef GClass::GGameTArray<std::vector<NpcCondition> > NpcConditionTArray;
	class CollectItem : public GClass::BTreeBase{
	public:
		struct stSdbCollectItem : stBTreeNodeBase{
			GClass::stGameString		item_name_id_;		//��Ҫ�ռ���Ʒ������id
			int							item_cnt_;			//��Ҫ�ռ���Ʒ������
		};
		static_assert(sizeof(stSdbCollectItem) == sizeof(COLLECT_ITEM), "");

	public:
		CollectItem();
		bool Update();
		const std::wstring& GetCollectItemId() const;
		int GetCollectItemCnt() const;

	private:
		std::wstring			item_name_id_;
		int						item_cnt_;
	};
	class CollectItemsMgr : public GClass::BTreeMgr_SkipRoot<CollectItem>{};
	class QuestRewardItem : public GClass::BTreeBase{
	public:
		typedef CollectItem::stSdbCollectItem stQuestRewardItem;

	public:
		QuestRewardItem();
		bool Update();
		const std::wstring& GetRewardItemId() const;
		int GetRewardItemCnt() const;

	private:
		std::wstring			reward_item_name_id_;
		int						reward_item_cnt_;
	};
	class QuestRewardItemsMgr : public GClass::BTreeMgr_SkipRoot<QuestRewardItem>{};
		
	struct stTeleportLocation{
		GClass::stGameStringEx		village_id_;
		GType::stGameVector			village_pos_;
		GType::stGameVector			village_direction_;
	};
	static_assert(sizeof(stTeleportLocation) == sizeof(TELEPORTLOCATION), "");
	struct TelePortLocation{
		std::wstring			village_id_;
		GType::stGameVector		village_pos_;
		GType::stGameVector		village_direction_;

		bool From( const stTeleportLocation& gtele );
	};

public:
	TaskCurJobTemplate();
	bool Update();

	//get
public:
	DWORD GetTaskId() const;
	const std::wstring& GetStrTaskId() const;
	const std::wstring& GetCloneMapId() const;
	const std::wstring& GetMainTitle() const;
	GType::enTaskCategory GetTaskCategory() const;
	int GetTaskLevel() const;
	const std::wstring& GetAcceptTaskNpc() const;
	const std::wstring& GetCompleteTaskNpc() const;
	const NpcConditionTArray& GetNpcCondition() const;
	const CollectItemsMgr& GetCollectItemCondition() const;
	const QuestRewardItemsMgr& GetRewardItems() const;
	bool IsAcceptable() const;

private:
	DWORD						task_id_;
	std::wstring				str_task_id_;
	std::wstring				clone_map_id_;				//����������ڸ���
	std::wstring				task_main_title_;			//��������
	GType::enTaskCategory		task_category_;
	int							task_level_;				//����ȼ�
	std::wstring				accept_task_npc_;			//������npc
	std::wstring				complete_task_npc_;			//�������npc

	//accept condition
private:

	//teleport location,����վ
private:
	boost::optional<TelePortLocation>		teleport_location_;		//Ŀ�괫��վ

	//complete condition
private:
	NpcConditionTArray			ac_npc_condition_;			//�������
	CollectItemsMgr				collect_items_mgr_;			//�ռ���Ʒ����
	QuestRewardItemsMgr			reward_items_mgr_;			//������Ʒ
};
//��ǰְҵ����������
class TaskCurJobTemplateMgr : public GClass::BTreeMgr_SkipRoot<GClass::BTreeBasePtrWrapper<TaskCurJobTemplate> >, public Singleton<TaskCurJobTemplateMgr, Singleton_MakeMe>{
public:
	bool RebuildUpdateAll();
	bool UpdateAll();

private:
	bool UpdateImpl();

	//����������
public:
	const TaskCurJobTemplate* FindByTaskId( const std::wstring& task_id ) const;
	TaskCurJobTemplate::SharedPtrT FindTaskPtrById ( const std::wstring& task_id ) const;
};

//�ѽ�����
class TaskReceived : public GClass::BTreeBase{
public:
	class RemainNpc : public GClass::GGameTypeBase{
	public:
		typedef GClass::GGameTArray<std::vector<GClass::GGameTypePlaceholder<GClass::stGameString> > > StageTArray;
		//��ɱ����
		struct stRemainNpcConditions{
			DWORD				str_dwVFunAddr;
			GAME_STRING_ID		str_theType;
			GAME_STRING_ID		str_theKey;						// ������Ҫ����NPC������id
			int					str_dwValue;					// ��Ҫ����NPC����ĸ���
			DWORD				str_dwBackAttackCount;						// ���󹥻�����
			DWORD				str_dwSpecialAttackUseCount;				// ���⹥��ʹ����
			DWORD				str_dwDeadlySkillUseCount;					// �����ļ���ʹ����
			GAME_STRUCT_ARRAY_POINT			str_theSkillUsageCounts;		// ���ܵ�ʹ������
			StageTArray::stGameTArray			str_theStages;					// ����׶Σ���������ͼ
			BINARY_TREE_MAP					str_theNpcKillBySkill;			// ʹ�ü���ɱ������
		};
		static_assert(sizeof(stRemainNpcConditions) == sizeof(REMAIN_NPC_CONDITION), "");
		typedef stRemainNpcConditions GameType;
		

	public:
		RemainNpc();
		bool Update();

		std::wstring	stage_id_;				//Ҫȥ�ĸ���
		int				remaint_cnt_;			//ʣ����������
	};
	typedef GClass::GGameTArray<std::vector<RemainNpc> > ActiveNpcTArray;

public:
	TaskReceived();
	bool Update();
	const std::wstring& GetStrTaskId() const;
	bool TaskCompletable() const;
	bool CanDoTheAcceptedTask() const;
	const TaskCurJobTemplate* GetTaskTemplate();
	const std::wstring& GetCompleteStageId();
	const ActiveNpcTArray& GetRemainActiveNpcInfo() const;

private:
	std::wstring					task_id_;
	bool							completable_;			//�Ƿ������
	TaskCurJobTemplate::SharedPtrT	task_template_;
	ActiveNpcTArray					remain_active_npc_;
};

//�����ѽ�����
class TaskReceivedMgr : public GClass::BTreeMgr_SkipRoot<TaskReceived>{
public:
	typedef TraverseTraits<TaskReceived&, const TaskReceived&> TraTraits;
	typedef TraTraits::IteratorBase AcceptedTaskIterBase;
	typedef TraTraits::IteratorBasePtr AcceptedTaskIterPtr;

public:
	bool RebuildUpdateAll();
	TaskReceived* FindTask( const std::wstring& quest_id );
	bool IsFulled() const;
	//��������δ�������
	AcceptedTaskIterPtr TraverseUncompleteTasks();
	AcceptedTaskIterPtr TraverseCompleteTasks();
};

//npc����
class TaskNpc : public GClass::BTreeBase{
public:
	class TaskNode : public GClass::BTreeBase{
	public:
		bool Update();
		const std::wstring& GetTaskId() const;
		const TaskCurJobTemplate::SharedPtrT& GetTaskTemplate();

	private:
		std::wstring					task_id_;
		TaskCurJobTemplate::SharedPtrT	task_template_;
	};
	class TaskMgr : public GClass::BTreeMgr_SkipRoot<TaskNode>{
	public:
		typedef TraverseTraits<const TaskNode&, const TaskNode&> TraTraits;
		typedef TraTraits::IteratorBase TaskNodeIterBase;
		typedef TraTraits::IteratorBasePtr TaskNodeIterPtr;

	public:
		TaskNodeIterPtr TraverseAllTask();
	};

public:
	bool Update();
	TaskMgr& GetAcceptableMgr();
	const std::wstring& GetNpcId() const;

private:
	std::wstring	npc_id_;
	TaskMgr			acceptable_task_;			//�ɽ��ܵ�����
	TaskMgr			complete_task_;				//�Ѿ���ɵ�����
};

class TaskNpcMgr : public GClass::BTreeMgr_SkipRoot<TaskNpc>, public Singleton<TaskNpcMgr, Singleton_MakeMe>{
public:
	typedef TraverseTraits<TaskNpc&, TaskNpc&> TraTraits;
	typedef TraTraits::IteratorBase NpcTaskIterBase;
	typedef TraTraits::IteratorBasePtr NpcTaskIterPtr;

public:
	bool RebuildUpdateAll();
	//�������Խ��������NPC
	NpcTaskIterPtr TraverseAcceptableNpc();
	//��������ͼ���Խ��������NPC
	NpcTaskIterPtr TraverseLocalMapAcceptableNpc();

private:
	bool DoUpdateImpl();

private:
	GClass::TimerSyncExec	timer_sync_exec_;
};