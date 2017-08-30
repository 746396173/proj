#pragma once
/*
@author zhp
@date 2014-3-10 14:59
@purpose for game player info
*/
#include "GameObj.h"
#include <Common/UsefulClass.h>
#include "GSkill.h"
#include "GameObjMgr.h"
#include "GClass.h"
#include "GPacket.h"
#include "GRoom.h"
#include "GTask.h"
#include "GStrMap.h"
#include <luabind/object.hpp>

class GPlayer : public GameObjBase{
public:
	GPlayer();
	 
	//type definition
public:

	//interfaces
public:
	//����ȼ�
	int GetLevel() const;

	//override
public:
	bool Update();

protected:
	GType::stGameVector			direction_;
	int							player_lvl_;
};

class GPlayerSelf : public GPlayer, public Singleton<GPlayerSelf, Singleton_MakeMe>{
public:
	typedef std::shared_ptr<CMDR_OnMailList> MailListPtrT;
	typedef std::shared_ptr<CMDR_OnMyProductList> MyProductListPtrT;
	typedef std::shared_ptr<CMDR_OnCreateNpcByClient> OnCreateNpcByClientT;
	typedef std::queue<std::string> TradeEventQueueT;
	typedef std::shared_ptr<CMDR_OnRequestProductInfo> CurRequestProductInfoT;
	typedef ProduceToDone<CMDR_OnRequestProductList::stProductItem> BuyProductItemsT;
	typedef std::shared_ptr<CMDR_OnRequestProductList> CurRequestProductListT;
	struct stSendMailList{
		GItem			item_;
		std::wstring	receive_role_name_;
	};
	typedef std::vector<stSendMailList> SendMailListContT;

public:
	GPlayerSelf();
	//�õ�ƣ��ֵ
	int GetFatigueData() const;
	GPacket& GetPacket();
	TaskReceivedMgr& GetReceivedTask();
	//�õ���ϸ��ְҵ
	GType::enJobCategory GetJob() const;
	const std::wstring GetSpecifyJobName() const;
	//��ְҵ�����罣��ʿ�������ߡ���ħʦ
	GType::enJobCategory GetMainJob() const;
	const std::wstring& GetChangeMainJobNpcName() const;
	static GType::enJobCategory JobToMainJob( GType::enJobCategory job );
	const GClassInfoTemplate* GetClassInfoTemplate() const;
	const std::wstring& GetCurVillageName() const;

	//�������
public:
	//ʹ�ü���
	bool HitTargets( const GSkillObj& skill_obj, const GameObjMgr::GameObjIterPtr& target_gameobjs );
	bool HitTargetsOneByOne( const GSkillObj& skill_obj, const GameObjMgr::GameObjIterPtr& target_gameobjs );
	//ʹ�ü��ܹ���һ��
	bool HitTarget( const GSkillObj& skill_obj, const GameObjBase::SelfPtrT& target_gameobj );
	//ֻ����һ��
	bool HitToDie( const GSkillObj& skill_obj, const GameObjBase::SelfPtrT& target_gameobj );
	//�������
	bool HitMultiToDie( const GSkillObj& skill_obj, const GameObjMgr::GameObjIterPtr& target_gameobjs );
	GSkillMgr& GetSkillMgr();
	//ѧϰ���ܣ���һ��
	bool LearnSkill( const GSkillObj& skill_obj, int lvl_addition );
	//�Զ���������
	bool AutoLvlUpSkills();
	//�Զ�ѧϰ���������м���
	bool AutoLearnLvlUpSkills();
	//ѧϰ����δѧ���ļ���
	bool LearnAllSkills();
	//ѧϰָ������
	bool LearnTheSkill( const std::string& skill_ch_name );
	bool LearnTheSkillW( const std::wstring& skill_id );
	//ѧϰĳ����֧��δѧ���ļ���
	bool LearnTheSkillBranch( const GClassInfoTemplate::SkillBranch& skill_branch );
	//����Ĭ��������
	bool SendSkillActivityCntAsDlt() const;

	//��Ʒ���
public:
	//ʰȡ��Ʒ
	bool PickUpItem( const GameObjBase::SelfPtrT& drop_item );
	bool PickUpItems( GameObjMgr::GameObjIterPtr& drop_items );
	//վ������ʰȡ��Ʒ
	bool StandAndPickUpItem( const GameObjBase::SelfPtrT& drop_item );
	bool StandAndPickUpItems( GameObjMgr::GameObjIterPtr& drop_items );
	//���������Ѵ�װ��
	bool RepairAllWearEquip();
	//����װ��
	bool EquipItemSync( const GItem& item );
	//�ѵ�װ��
	bool UnEquipItemSync( const GItem& item );
	//������ͨ��������װ��
	bool SellNormalTabAllEquips();
	//����ָ������Ʒ
	bool SellTheItemToShop( GItem& item );
	//�ֽ���Ʒ
	bool DisassemblyTheItem( GItem& item );

	//�ƶ����
public:
	//վ����ĳ������λ��
	bool FbStandToPos( const GType::stGameVector& pos );
	bool VillageStandToPos( const GType::stGameVector& pos );
	//վ����ĳ����Ϸ����
	bool FbStandToGameObj( const GameObjBase::SelfPtrT& gameobj );
	bool VillageStandToGameObj( const GameObjBase::SelfPtrT& gameobj );
	//վ����ĳ����Ϸ�������
	bool FbStandToGameObjSide( const GameObjBase::SelfPtrT& gameobj );
	//�����й�����ƶ�
	bool FbMonsterMove( const GameObjBase::SelfPtrT& gameobj );
	bool FbMonstersMove( const GameObjMgr::GameObjIterPtr& gameobjs );
	//�޸Ľ�ɫ��������
	bool ChangeRoleCurPos( const GType::stGameVector& new_pos );
	//�����ƶ�������������
	bool TouchConditionThatLocalMoveToMonsters();
	void LocalMoveToMonsters();

	//��Խ��ͼ
public:
	//���븱��
	bool EnterCloneMap( const GClass::AllowedVillageCloneMap& clone_map, GType::enFbDifficulty difficulty );
	//Ĭ�ϵȼ�
	bool EnterCloneMapDefault( const GClass::AllowedVillageCloneMap& clone_map );
	//������һ������
	bool EnterAnotherRoom( const GRoomDoor& door );
	//���س���
	bool ReturnCity();
	//�ٴ���ս����
	bool RestartCloneMap();
	//�ı����
	bool ChangeVillage( const std::wstring& village_gate_id );
	//�ƶ���ָ���ĳ���
	bool MoveToTheVillage( const std::string& village_ch_name );
	bool MoveToTheVillageW( const std::wstring& village_dst_id );
	//�ƶ���ָ���ĸ���
	bool MoveToTheCloneMap( const std::string& clone_map_ch_name );
	bool MoveToTheCloneMapW( const std::wstring& clone_map_id );
	bool MoveToTheStage( const std::wstring& stage_id );
	const std::wstring* Fb2Village( const std::wstring& clone_map_id );
	//bool MoveToTheCloneMapW( const std::wstring& clone_map_id );
	//�ƶ���ָ���������ڵĸ���
	//bool MoveToCloneMapOfTheTask( const std::string& quest_ch_name );

	//�������
public:
	//�����ʼ�,21�����ϲſ��Է��ʼ�
	bool SendMail( const std::wstring& receive_role_name, const std::wstring& mail_title, const std::wstring& mail_content, DWORD gold, const GItem* item );
	bool SendMail( const std::wstring& receive_role_name, const std::wstring& mail_title, const std::wstring& mail_content, DWORD gold, GItemMgr::GameItemIterPtr& item_iter );
	bool SendMailItem( const std::wstring& receive_role_name, const GItem& item );
	bool SendMailItemDelay( const std::wstring& receive_role_name, const GItem& item );
	bool SendMailGold( const std::wstring& receive_role_name, int reverse_gold, int delta_gold );
	bool SendMailImpl( const std::wstring& receive_role_name, int gold, const GItem* item );
	void ClearSendMailList();
	void DoSendMailList();
	void ResetMailList( const MailListPtrT& mail_list );
	void ResetMyProductList( const MyProductListPtrT& product_list );
	const MailListPtrT& GetMailList() const;
	const MyProductListPtrT& GetMyProductList() const;
	const CMDR_OnMyProductList::stMyProduct* FindMyProductByItemId( const std::wstring& item_id ) const;
	int GetTheProductCnt( const std::wstring& item_id ) const;
	/*warning*/int CalcSellingProductCnt( const std::wstring& item_id, int item_quality, int item_level ) const;
	void SucceedToGetAttachments( LONGLONG mail_serial );
	bool ReceiveOneMailAttachments();
	bool RemoveOneRubbishMail();
	//ˢ���ҵ������б�
	bool RefreshMyProductList();
	//������Ʒ
	bool SaleProductAsPrice( GItem& item, double price, int item_cnt, int product_cnt, int ac_type );
	bool SaleProductAsPriceBase( GItem& item, int price_delta, double dlt_price, int item_cnt, int product_cnt, int ac_type );
	//����������Ʒ
	bool BuyOneOtherProduct();
	TradeEventQueueT& GetTradeEventQueue();
	void PushTradeEvent( const std::string& event_name );
	void ClearTradeEventQueue();
	void OnRegisterProductResult( const CMDR_OnRegisterProduct& on_result );
	bool RichToSaleAsPrice( double total_price ) const;
	void ResetCurRequestProductInfo( const CurRequestProductInfoT& cur_info );
	//��ȡĳ�ֺŵ�˽��������Ϣ
	bool GainPriProductInfoByAcType( int ac_type );
	bool GainProductInfoByAcType( int product_ac_type, int ac_type );
	//�����Լ���˽��������Ϣ��ĳ�ֺ�
	bool TellSelfPriProductInfoToAcType( int ac_type );
	bool TellSelfProductInfoToAcType( int product_ac_type, int ac_type );
	bool GenPriProductsInfo( Json::Value& out_json ) const;
	bool GenProductsInfoByAcType( Json::Value& out_json, enGameAcType ac_type ) const;
	GType::RoleProductInfoContT& GetOthersProductInfo();
	void AddOtherProductInfo( const CmnUuid& role_uuid, const GType::stProductInfo& other_product );
	void EraseOtherProductInfo( const CmnUuid& role_uuid, const GType::stProductInfo& other_product );
	//��ѯ�����б�
	bool RequestProductList( const GItemTemplate& item_template );
	//���ɨ������Ŀ
	void ClearBuyProductItems();
	//���ɨ������Ŀ
	bool AddBuyProductItem( const std::string& item_name, int min_price, int item_cnt, int item_cnt_limit );
	void ResetCurRequestProductList( const CurRequestProductListT& cur_product_list );
	//����ɨ����
	void DoBuyProductItem();

	//�������
public:
	//��������
	bool AcceptTask( const std::wstring& quest_id );
	bool SendAcceptTask( const std::wstring& quest_id );
	//�������
	bool CompleteTask( const std::wstring& quest_id, const std::wstring& reward_item_id );
	//�ύ����Ĭ��ѡ����
	bool CommitTask( const std::wstring& quest_id );
	//ѡ��Ĭ�Ͻ���
	const std::wstring& ChooseTaskDftReward( const std::wstring& quest_id );
	const std::wstring& ChooseTaskDftReward( const TaskCurJobTemplate& task_template );
	const TaskCurJobTemplate* GetTaskTemplate( const std::wstring& quest_id );
	//�Զ�����������������
	bool CommitCompleteTasks();
	//�Զ��ύû����ɴ������������
	bool CommitNoCompleteHandlerTasks();
	//��ָ��������
	bool AcceptTheTask( const std::string& quest_ch_name );
	bool AcceptTheTaskW( const std::wstring& quest_id );
	//�Ƿ��ѽ�ָ��������
	bool IsAcceptedTheTask( const std::string& quest_ch_name );
	//�����Ƿ������
	bool TheTaskCompletable( const std::string& quest_ch_name );
	GameEn2ChNodeMgr& GetEn2Ch();
	//��������һ������
	bool AcceptLocalMapAnyTask();
	//�Ƿ��ܽ��ܸ�����
	bool CanAcceptTheTask( const std::wstring& quest_id );
	//����������������(����ͼ��)
	int AcceptLocalMapAnyAllTasks();
	bool PreDoTask();
	//�Զ���һ���ѽ�����
	bool AutoDoneOneAcceptedTask();
	//�Զ����һ�����������
	bool AutoCompleteOneCompletedTask();
	//�Զ�ȥ���������ĳ���ȥ�ύ����
	bool AutoGotoCommitCompletedTask( bool village_move );
	//Ѱ��һ��������ĳ�����������
	static bool FindQuestIdOfVillage( const TaskReceivedMgr::AcceptedTaskIterPtr& task_iter, const std::wstring& village_id, std::wstring& out_stage_id, std::wstring& out_quest_id );
	void ResetTaskBlacklist();
	void AddTaskBlacklist( const std::wstring& quest_id );
	void AddProhibitTask( const std::wstring& quest_ch_name );
	bool TaskBlacklistExistTheQuest( const std::wstring& quest_id );
	//��ս������
	void ClearRecommandVillages();
	//���ɽ������
	void GenRecommandVillages();
	//ִ��һ���������
	bool DoOneRecommandVillage();

	//for lua
public:
	//ɱ�����еĹ���
	bool KillAllMonster();
	//�ƻ����й�̬��Ʒ
	bool DestroyAllMisc();
	//ʰȡ������Ʒ
	bool PickUpAllItems();
	//ʰȡ���н�Ǯ
	bool PickUpAllGold();
	//�������з���
	bool FightThroughAllRooms( const luabind::object& func );
	bool FightThroughAllRooms_( const std::function<void()>& func );
	//ȫͼ�򸱱�
	bool FightAllGraph( const luabind::object& func );
	bool FightAllGraph_( const std::function<void()>& func );
	bool DoTheFb( const std::wstring& fb_id );
	bool DoTheFbA( const std::string& fb_ch_name );
	void DoWhenAtRoom();
	//���ֱ������
	void HitUntilClearCurSector( const std::wstring& cur_sector );

	//other
public:
	//BOSS����ѡ����
	bool FbBossRoomReward();
	//תְ
	bool ChangeJob( int sub_job_idx );
	//Ĭ��תְ
	bool ChangeJobAsDlt();
	bool NeedChangeJob() const;
	CmnUuid GetMyRoleUuid() const;
	void ResetOnCreateNpcByClient( const OnCreateNpcByClientT& the_msg );
	//��ɫ������
	void PlayerDied();
	//�����������سǸ���
	void ResetNoRetCityAtDie();
	//����������سǸ���
	void AddNoRetCityAtDie( const std::wstring& fb_ch_name );

	//test
public:
	void Test();
	void Test1();
	//�������п��Խ�ȥ�ĸ������ͼ��Ϣ
	void TestAllowedV_CM();
	void TestEnterCloneMap();

	//static
public:
	
	//override
public:
	bool Update();
	bool UpdateFatigueData();

private:
	//ѧ��ĳ�����ܵ�SP
	bool UseOutSkillSp( GSkillObj& skill_obj );

private:
	bool TryUpdateImpl();
	bool DoUpdateImpl();

private:
	GSkillMgr				skill_mgr_;
	int						fatigue_data_;			//ƣ��ֵ
	GPacket					packet_;				//����
	std::wstring			village_name_;			//��ǰ���ڳ�������
	TaskReceivedMgr			received_tasks_;		//�ѽ�����
	int						left_sp_;				//ʣ�༼�ܵ�
	std::wstring			channel_id_;
	GType::enJobCategory	job_;
	std::wstring			role_class_type_;
	int						gold_;
	GClass::TimerSyncExec	timer_sync_exec_;
	const GClassInfoTemplate*	job_branch_skill_template_;
	MailListPtrT			mail_list_;
	MyProductListPtrT		my_product_list_;
	TradeEventQueueT		trade_event_queue_;
	CurRequestProductInfoT	cur_request_product_info_;
	GType::RoleProductInfoContT	others_product_info_;
	std::set<std::wstring>	task_blacklist_;
	std::set<std::wstring>	task_prohibited_ch_name_;
	int						buy_other_min_gold_;
	BuyProductItemsT		buy_product_items_;		//ɨ����
	CurRequestProductListT	cur_product_list_;
	std::queue<std::wstring>	recommand_villages_;
	OnCreateNpcByClientT		on_create_npc_by_client_;
	SendMailListContT			send_mail_list_;
	bool						player_died_;
	std::set<std::wstring>		no_ret_city_at_die_;			//�������سǸ���
};