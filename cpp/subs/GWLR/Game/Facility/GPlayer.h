#pragma once
/*
@author zhp
@date 2014-3-10 14:59
@purpose for game player info
*/
#include "GTypes.h"
#include "GameObj.h"
#include "GVillage.h"
#include "GItem.h"
#include "GTask.h"
#include "GCloneMap.h"
#include "../GloFuncs.h"
#include "GProtocolR.h"
#include "GMapPath.h"

class GPlayer : public GameObjBase{
public:
	GPlayer();
};

typedef std::pair<GType::stGameVector3, GType::stGameVector3> GameObjDirT;
class GPlayerMe : public GPlayer, public Singleton<GPlayerMe, Singleton_MakeMe>{
	friend class GClass::GHitMonsterMode_Mouse;
	friend class GClass::GHitMonsterMode_UsePacketItem;
public:
	typedef GSP_StagePosPath::StepsT PosQueueT;
	typedef std::shared_ptr<CMDR_OnEnterFb> MsgOnEnterFbT;
	typedef std::shared_ptr<CMDR_OnEnterFbError> MsgOnEnterFbErrT;
	typedef std::shared_ptr<CMDR_OnFbInfo> MsgOnFbInfoT;
	typedef boost::optional<MsgOnFbInfoT> MsgOnFbInfoOptionalT;
	typedef std::shared_ptr<CMDR_OnRefreshMySellList> MsgMySellListT;
	typedef std::shared_ptr<CMDR_OnGainAuctionPageInfo> MsgAuctionPageInfoT;
	typedef std::vector<MsgAuctionPageInfoT> AuctionPagesInfoT;
	typedef std::shared_ptr<CMDR_OnSafeTime> MsgOnLeftTimeT;
	typedef std::shared_ptr<CMDR_OnBuyAuction> MsgOnBuyAuctionT;
	typedef std::list<stAuctionItemInfo> AuctionItemsContT;
	typedef std::shared_ptr<CMDR_OnAcceptMail> MsgOnAcceptMailT;
	typedef std::shared_ptr<CMDR_OnOpenNpc> MsgOnOpenNpcT;
	typedef std::shared_ptr<CMDR_OnSoldAuction> MsgOnSoldAuctionT;
	typedef std::shared_ptr<CMDR_OnSoldItemToShop> MsgOnSoldToShopT;
	typedef std::shared_ptr<CMDR_OnCommitTaskFailed> MsgCommitTaskFailedT;
	typedef std::shared_ptr<CMDR_OnDoNpcChat> MsgOnDoNpcChatT;
	typedef std::shared_ptr<CMDR_OnSendMail> MsgOnSendMailT;
	typedef std::shared_ptr<CMDR_OnSendMail2> MsgOnSendMail2T;
	typedef std::shared_ptr<CMDR_OnUseItemRet1> MsgOnUseItemRet1T;
	typedef std::shared_ptr<CMDR_OnUseItemRet2> MsgOnUseItemRet2T;
	typedef std::shared_ptr<CMDR_OnBuyItem> MsgOnBuyItemT;
	typedef std::shared_ptr<CMDR_OnCollectRet> MsgOnCollectRetT;
	typedef std::shared_ptr<CMDR_OnArrangeItemsRet> MsgOnArrangeItemsRetT;
	typedef std::shared_ptr<CMDR_OnSendMoveRoomRet> MsgOnSendMoveRoomRetT;
	typedef std::shared_ptr<CMDR_OnAcceptTaskRet> MsgOnAcceptTaskRetT;
	typedef std::shared_ptr<CMDR_OnGiveupTaskRet> MsgOnGiveupTaskRetT;
	typedef std::shared_ptr<CMDR_OnRequestDeal>	MsgOnRequestDealT;
	typedef std::shared_ptr<CMDR_OnRequestDealFail> MsgOnRequestDealFailT;
	typedef std::shared_ptr<CMDR_OnRecvQuestDeal> MsgOnRecvQuestDealT;
	typedef std::shared_ptr<CMDR_OnCancelDeal> MsgOnCancelDealT;
	typedef std::shared_ptr<CMDR_OnDealFail> MsgOnDealFailT;
	typedef std::shared_ptr<CMDR_OnMoveItemToDealTab> MsgOnMoveItemToDealTabT;
	typedef std::shared_ptr<CMDR_OnMoveDealGold> MsgOnMoveDealGoldT;
	typedef std::shared_ptr<CMDR_OnRecvDealStatus> MsgOnRecvDealStatusT;
	typedef std::shared_ptr<CMDR_OnRecvDealEnd> MsgOnRecvDealEndT;
	typedef std::shared_ptr<CMDR_OnGetMailItemsInfo> MsgOnGetMailItemsInfoT;
	typedef NameList<std::string> NameList_StrT;
	typedef std::pair<std::string, std::string> WearWhiteListPairT;
	typedef NameList<WearWhiteListPairT, std::vector<WearWhiteListPairT> > WearWhiteListT;
	struct stShangJinNameListItem{
		std::string				task_sub_name_;
		CD_En_FbDifficulty		fb_diff_;
		bool					is_king_fb_;

		friend bool operator == ( const stShangJinNameListItem& lhs, const stShangJinNameListItem& rhs ){
			return lhs.is_king_fb_ == rhs.is_king_fb_ && lhs.fb_diff_ == rhs.fb_diff_ && lhs.task_sub_name_ == rhs.task_sub_name_;
		}
	};
	typedef NameList<stShangJinNameListItem, std::vector<stShangJinNameListItem> > ShangJinWhiteListT;
	typedef NameList<int> NameList_IntT;
	struct stShangJinTaskInfo{
		const GTaskDb*		task_template_;
		GMapDb				fb_info_;
		bool				test_fb_diff_lvl_;
		stShangJinTaskInfo();
	};
	typedef std::vector<stShangJinTaskInfo> ShanJinTaskInfoT;
	struct stSendMailItem : GClass::stItemInfo{
		bool	reach_cnt_;		//�ﵽָ�������Ż��ʼ�
	};
	typedef std::vector<stSendMailItem> SendMailContT;
	struct stLastSendMoveRoomInfo{
		std::string		cmd_;
		int				dst_room_num_;
	};
	struct stNeedMaterialInfo{
		int			material_item_id_;		//��Ҫ�Ĳ���ID
		int			total_item_cnt_;		//��Ҫ�Ĳ�������
		int			need_cnt_;				//��Ҫ�Ĳ�����
	};
	enum enSendMail{
		kSM_Error = -2,
		kSM_Again = -1,
		kSM_Empty = 0,
		kSM_Succeed = 1,
	};

public:
	GPlayerMe();
	void ResetAllUpdateData();
	void ResetPassRoomData();
	void OnRoleDead();

public:
	int GetHitHp() const;
	void SetHitHp( DWORD package_id, int hit_hp );
	int GetFeebHp() const;
	void SetFeebHp( DWORD package_id, int feeb_hp );
	int GetCurHp() const;
	const std::string& GetCurMapName() const;
	int GetCurTemplateMapId() const;
	int GetCurMapId() const;
	const std::string& GetCurTemplateMapName() const;
	void ResetNofityDatas();
	void OnCrossMap();
	//ÿ�ν�ɫ������Ϸ��Ҫִ��
	void ExecAtEveryRoleEnterGame();
	GReceivedTaskMgr& GetReceivedTaskMgr();
	GAcceptableTasks& GetAcceptableTasks();
	GEnterableFbMgr& GetEnterableFbMgr();
	GItemMgr_Package& GetGridPackage();
	GItemMgr_Store& GetStorePackage();
	GItemMgr_SuCai& GetGridSuCai();
	GItemMgr_Equip& GetEquipPackage();
	GItemMgr_Task& GetGridsTask();
	GItemMgrBase* GetItemMgr(CD_En_TabCategory tab_category);
	GClass::CurFarmFieldInfo& GetCaoYaoTianInfo();
	const MsgOnEnterFbT& GetMsg_OnEnterFb() const;
	int GetRoleLvl() const;
	int GetLeftShouLieQuanCnt() const;
	int GetCurGold() const;
	int GetCurSilver() const;
	void SetOnEnterFb( const MsgOnEnterFbT& msg );
	void SetOnFbInfo( const MsgOnFbInfoOptionalT& fb_info );
	void SetOnRefreshMySellList( const MsgMySellListT& msg );
	void SetOnGainAuctionPageInfo( const MsgAuctionPageInfoT& msg );
	void SetOnLeftTime( const MsgOnLeftTimeT& msg );
	void SetOnBuyAuction( const MsgOnBuyAuctionT& msg );
	void SetOnAcceptMail( const MsgOnAcceptMailT& msg );
	void SetOnOpenNpc( const MsgOnOpenNpcT& msg );
	void SetOnSoldAuction( const MsgOnSoldAuctionT& msg );
	void SetOnSoldToShop( const MsgOnSoldToShopT& msg );
	void SetCommitTaskFailed( const MsgCommitTaskFailedT& msg );
	void SetOnDoNpcChat( const MsgOnDoNpcChatT& msg );
	void SetOnSendMail( const MsgOnSendMailT& msg );
	void SetOnSendMail2( const MsgOnSendMail2T& msg );
	void SetOnUseItemRet1( const MsgOnUseItemRet1T& msg );
	void SetOnUseItemRet2( const MsgOnUseItemRet2T& msg );
	void OnBuyItem( const MsgOnBuyItemT& msg );
	void OnCollectRet( const MsgOnCollectRetT& msg );
	MsgOnCollectRetT& GetCollectRet();
	void OnArrangeItemsRet( const MsgOnArrangeItemsRetT& msg );
	bool SetLianQiCao();
	void SetRightBtHit( bool is_right_hit );
	void SetMonsterMaxHigh( float high );
	void ResetSendRoomTime();
	int GetLeftSingleExp() const;
	int GetLeftDoubleExp() const;
	void HitRaii();

	//�ƶ�/��·���
public:
	//������·���
	bool SendWalk( const GType::stGameVector3& dst_pos, const GType::stDirection2d& dir );
	bool DoWalk( const GType::stGameVector3& dst_pos );
	bool DeltaWalk( const GType::stGameVector3& delta_pos );
	bool SetPosInfoAsAnotherObj( const GameObjBase& obj );
	//�������ﳯ��
	bool SetRoleForward( const GameObjBase& obj );
	bool SetRoleForwardByPos( const GType::stGameVector3& pos_src, const GType::stGameVector3& pos_dst );
	//�ƶ�
	bool MoveForward( int steps = 1 );
	//��������
	bool SendToSerThePos( const GType::stGameVector3& the_pos, bool send_force );
	//�������굽��Ϸ���󱳺�
	bool SetRoleToBackDirect( const GameObjBase& obj, int steps = 1 );
	bool TestTheMonsterPosZ( const GType::stGameVector3& the_pos );
	bool IsTestTheMonsterPosZ( GameObjBase& obj );
	OptinalBool SetRoleToBackIndirect( GameObjBase& obj, GNormalGameObjMgrBase* obj_mgr, int obj_room_num, int role_room_num, bool is_any_direction, int steps );
	bool SetPosEnsureSync( const GType::stGameVector3& pos );
	typedef std::function<bool()> SetRolePosCallBackT;
	OptinalBool SetRoleToPosIndirect( const GType::stGameVector3& dst_pos, int obj_room_num, int role_room_num, 
		int target_room_num, const SetRolePosCallBackT* call_back, bool is_test_dst_pos_z, bool is_pass_room = false );
	bool TestObjPosInfoAtFindingPath( DWORD obj_packet_id, GNormalGameObjMgrBase* obj_mgr, int obj_room_num, const GType::stGameVector3& pos_tmp );
	bool TestObjBodyPartPosInfoAtFindingPath( DWORD obj_packet_id, GNormalGameObjMgrBase* obj_mgr, int obj_room_num, const GType::stGameVector3& pos_tmp );
	//����
	bool AttrackGameObj( GameObjBase& obj );
	//��������
	bool StepVillageDoor( const stCrossDoorPosInfo& door_pos_info );
	//�ƶ���ָ���Ĵ�ׯ
	OptinalBool MoveToTheVillage( const std::string& dst_village_name, int room_num );
	bool SendMoveVillage( const std::string& gate_name );
	//�ƶ���ָ���ĸ���
	OptinalBool MoveToTheFb( const std::string& fb_name );
	OptinalBool MoveToTheFbById( int fb_id );
	OptinalBool MoveToTheFbImpl( const GMapDb& fb_info );
	OptinalBool SendMoveToTheFb( const GMapDb& fb_info, GType::enFbConsumeMode fb_mode );
	bool DoSendMoveToFbErr();
	//�����ؿ�
	bool GiveUpFb();
	bool SendGiveUpFb();
	//�˳�����ѵ��
	bool GiveUpXinShouXunLian();
	bool SendGiveUpXinShouXunLian();
	//��������ѵ��
	bool EnterXinShou();
	//�ƶ���ָ���ķ���
	OptinalBool SendMoveToTheRoom( const std::string& move_cmd, const GType::stGameVector3& door_pos, int target_room_num, bool force_send );
	//����ֱ��������
	bool PressKeyUntilSendMoveRoom( DWORD v_k, const GType::stGameVector3& door_pos );
	void OnGameSendMoveRoom( const CMDR_Hook_SendMoveRoom& msg );
	bool MoveToTheRoom( int room_num );
	bool MoveToTheRoomOfObj( GameObjBase& obj );
	//����ÿ�ƶ�һ�εľ���
	void SetMoveStepDist( float step_dist );
	//����ÿ������
	int StepOverObjs( const GameObjsContT& game_objs );
	//����ָ�����ֵľ�ֹ����
	int StepOverTheStaticObjs( const std::string& obj_name );
	//Ѱ��һ�����ʵĸ���
	const GMapDb* FindSuitableFbInfo();
	//���ý��븱����Ĵ���
	bool SetAfterEnteredFb( const luabind::object& func );

	//����/�������
public:
	bool UseSkill(CD_En_SkillId skill_category, WORD hit_times = 1);
	bool HitByLeftBt( WORD hit_times = 1 );
	bool HitByRightBt( WORD hit_times = 1 );
	bool PressKeyZ();
	bool SwitchKnife();
	//�յ�
	bool TakeInKnife();
	//�ȴ�������״̬
	bool WaitToFree( int wait_time );
	//�ȴ���doing״̬
	bool WaitToDoingStatus( int wait_time );
	//���ù�����ʱ��һ��Ҫ���ǽ�ɫ�������������Ҫ���������λ������
	OptinalBool HitMonster( GameObjBase& obj, GNormalGameObjMgrBase* obj_mgr, int obj_room_num, int role_room_num, bool is_any_direction );
	OptinalBool HitMonsterByPacketId( DWORD packet_id, GNormalGameObjMgrBase* obj_mgr, bool is_any_direction );
	//�������ָ���Ĺ���ֱ������
	int HitTheMonsterToDie( DWORD packet_id, GNormalGameObjMgrBase* obj_mgr, int sleep_time, bool is_any_direction );
	//���ʱ�Ĵ���
	void HandleAtHitting();
	//���ù�����λ��Ϣ
	void SetHitBodyPart( int body_part_idx, int hit_cnt, DWORD cur_packet_id );
	//���ô˴ι���ģʽ
	void SetCurHitMode(GClass::GHitMonsterMode_Mouse::enHitMode hit_mide);
	//���ù���ģʽ_ʹ�ñ�����Ʒ
	bool SetHitMode_UsePacketItem( const std::string& item_name, int steps );
	//������״̬
	bool IsHotStatus();
	//�ں���״̬
	bool IsColdStatus();
	//���ж�״̬
	bool IsPoisoningStatus();
	//���ڰ������
	bool HasAoYiJueXing();
	//������״̬
	bool IsNiRenStatus();
	//�Ƿ����ָ����buff
	bool IsTheCurStatus( const std::string& buff_name );
	//ȼ��״̬
	bool IsRanShaoStatus();
	//����״̬
	bool IsErChouStatus();
	//ѩ��״̬
	bool IsSnowManStatus();
	//����״̬
	bool IsChanRaoStatus();

	//����
public:
	//����������
	bool SendAcceptTask( int task_id );
	bool AcceptTask( int task_id );
	//��������
	bool GiveUpTask( int task_id );
	//����������
	bool SendCommitTask( int task_id );
	bool CommitTask( int task_id );
	//���жԻ�
	bool DoNpcChat( int task_id );
	bool SendDoNpcChat( int task_id );
	//���ܹ���ί��
	bool AcceptSociatyTask( const std::string& task_lvl, const std::string& task_name );
	bool SendAcceptSociatyTask( GType::enSociatyTaskLvl sociaty_task_lvl, DWORD task_fb_id );
	//�Զ�ȥ��ָ���Ĺ���ί�У������������ϵ��GainTheFbInfo���ǿ��Բ����ṩ����ȼ������ģ��Ժ�����������ǧ������ʱ��ȥ����
	bool AutoToDoTheSociatyTask( const std::string& task_lvl, const std::string& task_name, const luabind::object& do_func );
	//��ѯ������Ϣ
	bool SendGainFbInfo(CD_En_FbType fb_type);
	bool GainTheFbInfo(CD_En_FbType fb_type);
	//��������
	bool ZuoReQiQiu();
	//����ͽ����������
	void AddShangJinWhiteList(const std::string& task_name, CD_En_FbDifficulty fb_diff, bool is_king_fb);
	//����ͽ����������
	void ClrShangJinWhiteList();
	const GTaskDb* FilterShangJinWhiteList(const ShanJinTaskInfoT& shang_jin_task_info, int& the_fb_id) const;
	//����ͽ�Ŀ�긱��������
	void AddShangJinDstFbBlackList( int fb_id );
	//����ͽ�Ŀ�긱��������
	void ClrShangJinDstFbBlackList();
	bool IsInShangJinDstFbBlackList( int fb_id ) const;
	//�����������������
	void AddFbBlackList_Cat( int fb_id );
	//�����������������
	void ClrFbBlackList_Cat();
	//����������������
	bool IsInFbBlackList_Cat( int fb_id ) const;
	//��Ӹ���������
	void AddFbBlackList( int fb_id );
	//��ո���������
	void ClrFbBlackList();
	//�ڸ���������
	bool IsInFbBlackList( int fb_id ) const;
	//����ͽ�Ŀ�긱���̶�������
	void AddShangJinDstFbStableBlackList( int fb_id );
	//����ͽ�Ŀ�긱���̶�������
	void ClrShangJinDstFbStableBlackList();
	bool IsInShangJinDstFbStableBlackList( int fb_id ) const;
	//��Ӳɼ�������
	void AddCollectBlackList( const std::string& collect_name );
	//��ղɼ�������
	void ClrCollectBlackList();
	bool IsInCollectBlackList( const std::string& collect_full_name ) const;

	//npc���
public:
	bool SendOpenNpc( DWORD npc_packet_id, GType::enNpcOpenType open_type );
	bool OpenNpc( const GameObjBase& npc, GType::enNpcOpenType open_type = GType::kNOT_Normal );

	//item
public:
	//��ȡ��������Ʒ
	int GainSupplyItem( const std::string& item_name );
	bool SendGainSupplyItem( int item_id, int item_cnt, int slot_idx );
	bool UseItem(CD_En_ItemPackageCategory ipc, int item_slot_idx);
	bool UseItemByName( const std::string& item_name );
	int UseSomeItems( const std::string& item_name, int use_cnt );
	//ʹ��������Ʒ
	bool UseTaskItem( const std::string& item_name );
	//����
	bool DoCraft( const std::string& item_name );
	bool DoCraftByDstEquipItemId( const GClass::CraftDbMgr::stCraftDb& craft_item );
	//����
	bool DoBuy( const std::string& shop_category_name, const std::string& item_name, int buy_cnt, const std::string& village_name, const std::string& npc_name );
	//����װ��(ֻ�������������ϵ�װ��)
	bool LvlUpEquip( const std::string& equip_name, int lvl_up_equip_idx );
	bool LvlUpTheEquip( GItem& the_equip, int lvl_up_equip_idx, bool is_log );
	//�Զ�����װ��������
	void AddAutoLvlUpEquipBlackList( const std::string& item_name );
	//����Զ�����װ��������
	void ClrAutoLvlUpEquipBlackList();
	bool IsInAutoLvlUpEquipBlackList( const GItem& the_item ) const;
	const ItemDb::stEquipLvlUpInfo* GetTheEquipLvlUpInfo( const ItemDb& the_equip, int lvl_up_equip_idx );
	//��ȡ�������������Ϣ
	void GainWeaponNeedLvlUpInfo( std::vector<stNeedMaterialInfo>& out_info );
	bool SendLvlUpEquip( const GItem& item, const ItemDb::stEquipLvlUpInfo& lvl_up_info );
	//////////////////////////////////////////////////////////////////////////
	//****************�ƶ���Ʒ*************************
	//�����ƶ���Ʒ�����Ŀ��λ��û����Ʒ���������ƶ������������Ʒ��ָ��ƶ���
	bool SmartMoveItem(GItem& item_src, CD_En_TabCategory tbl_category_dst, int slot_idx_dst);
	//�ƶ�������Ʒ
	bool MoveTotalItem(GItem& item_src, CD_En_TabCategory tbl_category_dst, int slot_idx_dst);
	//�ϲ��ƶ���Ʒ
	bool MoveMergeItem( GItem& item_src, const GItem& item_dst );
	//�ָ��ƶ���Ʒ
	bool MoveSplitItem(GItem& item_src, CD_En_TabCategory tbl_category_dst, int slot_idx_dst);
	bool SendMoveItem(const LONGLONG& item_serial, CD_En_TabCategory tbl_category_src, int slot_idx_src, CD_En_TabCategory tbl_category_dst, int slot_idx_dst);
	bool SendMoveMergeItem(const GItem& item, CD_En_TabCategory tbl_category_src, int slot_idx_src, CD_En_TabCategory tbl_category_dst, int slot_idx_dst, const LONGLONG& item_serial_dst);
	bool SendMoveSplitItem(const GItem& item, CD_En_TabCategory tbl_category_src, int slot_idx_src, CD_En_TabCategory tbl_category_dst, int slot_idx_dst);
	//////////////////////////////////////////////////////////////////////////
	//�����̵�
	bool SendSellToShop( const GItem& item );
	int SellItemsToShop( const GItemMgrBase::ContT& items, const std::string& village_name, const std::string& npc_name );
	//������
	bool SendOpenMail();
	//ɾ������
	bool SendDeleteMail( const LONGLONG& mail_serial );
	//��ȡ�ʼ�
	bool SendGainMailItem( const LONGLONG& mail_serial );
	//�ʼ�
	enSendMail SendMail(const SendMailContT* items, int item_reach_cnt, 
		int gold, const std::string& target_role_name, const std::string& village_name, const std::string& npc_name);
	bool SendMailHelper( int& send_item_cnt, std::deque<GItem>& send_items, GItemMgrBase::GameItemIterPtr& tra_it );
	bool BuildSendMailMsg(std::deque<GItem>& send_items, stCD_Msg_SendMail& msg);
	//�Ӳֿ�ͱ����в���
	boost::optional<GItem> FindItemFromPacketAndStore( const std::string& item_name, bool is_bind = true, int item_cnt = 1 );
	//�Զ������Ʒ���ֿ�
	void AutoStoreItemsToStored();
	//////////////////////////////////////////////////////////////////////////
	//***************************��Ʒ������***********************************
	//��ʼ����Ʒ�������Ͱ�����
	void InitItemBlackWhiteList();
	//�����Ʒ�������Ͱ�����
	void AfterRunScript();
	void PreRunScript();
	//�����ֿ�ͱ�����������Ʒ
	int SellStored_PacketRubbishItems( int packet_reserve_cnt, int stored_reserve_cnt, const std::string& village_name, const std::string& npc_name );
	void SellStored_PacketRubbishItemsImpl( int reserve_cnt, const GItemMgrBase::ContT& items, GItemMgrBase::ContT& black_list, luabind::object* filter_white_ptr, luabind::object* filter_black_ptr );
	//������Ʒ���˺�����
	void SetItemFilterBlackList( const luabind::object& item_func );
	//������Ʒ���˰�����
	void SetItemFilterWhiteList( const luabind::object& item_func );
	//������̵���Ʒ��������
	void AddItemNameBlackList( const std::string& item_name );
	//������̵���Ʒ��������
	void ClrItemNameBlackList();
	//������̵���Ʒ��������
	void AddItemNameWhiteList( const std::string& item_name );
	//������̵���Ʒ��������
	void ClrItemNameWhiteList();
	//������Ʒ��Ϣ������
	void SetItemInfoWhiteList( int item_lvl, int item_quality );
	//���ö�����Ʒ������
	void SetCraftItemWhiteList( int item_lvl, int item_quality );
	//��������װ��������
	void SetLvlUpEquipWhiteList( int item_lvl, int item_quality );
	//���õ��Ͱ�����
	void SetFactureWhiteList( int item_lvl, int item_quality );
	//////////////////////////////////////////////////////////////////////////
	//��Ӵ�ֿ���Ʒ������
	void AddStoreWhiteList( const std::string& item_name );
	//��մ�ֿ���Ʒ������
	void ClrStoreWhiteList();
	bool InStoreWhiteList( const GItem& item );
	//�Ӳֿ����ƶ�����������Щ��������Ʒ
	int StoreToPackageTheWhileList();
	//////////////////////////////////////////////////////////////////////////
	//������Ʒ
	bool ArrangeItems(CD_En_TabCategory tab_cate);
	//Ѱ����Ʒ
	GItem FindTotalItem( int item_id );
	GItem FindTotalItemByName( const std::string& item_name );
	GItem FindTotalItemByMatchName( const std::string& item_name );
	GItem FindTotalItem_TaskByMatchName( const std::string& item_name );
	GItem FindTotalItemFromPackeAndStoreByMatchName( const std::string& item_name );
	GItem FindTotalItemFromPackeAndStoreNormalByMatchName( const std::string& item_name );
	//��ȡ���
	bool GainGiftBag( int gift_bag_id );
	//�Զ���ȡ���
	int AutoGainGiftBag();
	//��ȡ������ȯ
	bool GainWeekShouLieQuan();
	//����Զ�����װ��������
	void AddAutoWearBlackList( const std::string& item_name );
	//����Զ�����װ��������
	void ClrAutoWearBlackList();
	bool IsInAutoWearBlackList( const GItem& item ) const;
	//���Զ���װ������
	const WearWhiteListPairT* FindAutoWearWhiteListItem( const std::string& equip_name );
	void AddAutoWearWhiteList( const std::string& item_name, const std::string& item_type );
	//����������Ӣ����
	bool UnlockKingCream(int fb_id, const std::string& unlock_item_name);

	//�ɼ�
public:
	//�����ɼ�
	//bool SendCollect( DWORD );
	//�ɼ�һ��ָ���Ŀɲɼ�����
	bool CollectTheCollectableObj( GameObjBase& obj, GNormalGameObjMgrBase* obj_mgr, int collect_time );
	bool CollectTheCollectableObjById( DWORD packet_id, GNormalGameObjMgrBase* obj_mgr, int collect_time );
	bool CollectTheCollectableObjImpl( GameObjBase& obj, GNormalGameObjMgrBase* obj_mgr, int collect_time );
	//��Ƥ
	bool CutSkin( GameObjBase& obj, GNormalGameObjMgrBase* obj_mgr, int wait_time );
	bool CutSkinById( DWORD packet_id, GNormalGameObjMgrBase* obj_mgr, int wait_time );
	bool CutSkinImpl( GameObjBase& obj, GNormalGameObjMgrBase* obj_mgr, int wait_time );
	//����ׯ԰�ɼ�
	int LvlUpCollectOfFarm(CD_En_FarmFacilityIdx idx, int lvl_limit, bool is_open_npc);
	bool IsFreeTimeToCollectOfFarm(CD_En_FarmFacilityIdx idx);
	//�����Լ���ׯ԰
	bool EnterSelfFarm();
	//�뿪ׯ԰
	bool LeaveFarm();
	//���һ�����е�������
	std::string GetExistFarmSeedName();
	//��ֲ����
	bool PlantFarmSeed( const std::string& seed_name, const std::string& land_name );
	//�����´�ׯ԰�ɼ���ʱ��
	bool CalcNextCollectFarmTime();
	//����ׯ԰�ɼ���ʱ��
	bool IsTimeToCollectFarm( const std::string& collect_name );

	//�������
public:
	//������
	bool SendSellToAuction( const GItem& item, int begin_price, int smart_price );
	bool SellToAuction( const std::string& item_name, int item_cnt, int begin_price, int smart_price, bool private_sell, 
		const boost::optional<int>& relative_smart_price, const boost::optional<int>& min_smart_price, const boost::optional<int>& average_cnt, bool begin_price_direct );
	//ˢ���ҵ�����
	bool SendRefreshMySellList( bool force_fresh );
	bool RefreshMySellList( bool force_fresh = false );
	//�Է�����ɫ��ʱ�򣬻����һ����ɫ�����Ķ�������ɾ����
	void ClrMySellList();
	//ͨ���ҵ������б����ݵı仯���Զ�֪ͨ�Է���Ӫ
	void NotifyOtherSideByMySellListChanged();
	//��ѯ��������Ŀ��
	int QuerySoldCnt( const std::string& item_name );
	//һ�ڼ۹���
	bool SendSmartBuy( const stAuctionItemInfo& item );
	bool CanSmartBuy( const stAuctionItemInfo& item );
	int SmartBuy( const std::string& item_name, int seach_page_cnt, const std::string& seller, int price_limit, int buy_cnt );
	//����һЩ�Է���Ӫ��������Ʒ
	int SmartBuyOtherSide();
	const stAuctionItemInfo* FindOtherSideItem( const stAuctionItemInfo& item_info );
	void AddOtherSideItem( const stAuctionItemInfo& item_info );
	void EraseOtherSideItem( const stAuctionItemInfo& item_info );
	void EraseMySellItem( const stAuctionItemInfo& item_info );
	bool AddOtherSideItemsFromJson( const Json::Value& j_value );
	void EraseOtherSideItemsFromJson( const Json::Value& j_value );
	void GenPrivateToJson( Json::Value& j_value );
	void GenMySellListToJson( Json::Value& j_value );
	void GenOthersSellToJson( Json::Value& j_value );
	const stAuctionItemInfo* SmartBuyOneImpl( const std::string& seller, int price_limit );
	//��ѯ������Ϣ
	bool SendGainAuctionInfo( const ItemDb& item_template );
	//��Ѱָ��ҳ���������Ϣ
	bool SendGainAuctionThePageInfo( int page_idx );
	//�Ƿ���˽������
	static bool IsPrivateSell( int price );
	static int MakePrivateSellPrice( int price );
	static int MakePublicSellPrice( int price );
	//////////////////////////////////////////////////////////////////////////
	//*******************���潻��*********************************************
	//������
	bool RequestDeal( const GPlayer& other );
	//����һ����������
	bool AcceptOneDealRequest();
	//�ƶ���Ʒ��������
	bool MoveItemToDealTab( const GItem& item, int dst_slot_idx );
	//����������
	bool LockDealTab();
	//ȷ�Ͻ���
	bool EnterDeal();
	//���׽��
	bool DealGold( int gold );
	//////////////////////////////////////////////////////////////////////////

	//����
public:
	//����������Ʒ
	bool ManuFactureItem( const std::string& item_name );
	
	//math
public:
	//����������
	GameObjDirT TwoPos2Dir( const GType::stGameVector3& vec_src, const GType::stGameVector3& vec_dst ) const;
	GameObjDirT Vec2Dir( const GType::stGameVector3& vec_dir ) const;
	//��������
	GType::stGameVector3 Dir2Vec( const GType::stGameVector3& dir_lhs, const GType::stGameVector3& dir_rhs ) const;
	//distance2steps
	bool Dist2Steps( const GType::stGameVector3& pos_src, const GType::stGameVector3& pos_dst, PosQueueT& pos_steps );
	//��pos info�еõ�2D��������Ҫ�����޸ķ���
	bool PosInfo2Dir2d(const stCD_PosDirInfo& pos_info_src, const stCD_BodyPartInfo& body_part_info, GType::stDirection2d& out_dir);
	//���ݲ�λ��Ϣ�õ���ɫӦ�ƶ�����������Ϣ
	bool BodyPartInfo2RolePos(const stCD_PosDirInfo& pos_info_src, const stCD_BodyPartInfo& body_part_info, GType::stGameVector3& out_pos, GameObjDirT& out_dir);

	//update some data
public:
	bool Update() override;
	bool UpdateRolePos();
	bool UpdateRolePosSync();
	bool UpdatePacketId() override;
	bool UpdatePacketIdSync();
	bool UpdateCurMapInfo();
	bool UpdateCurMapInfo_Notify();
	bool UpdateGrids();
	bool UpdateReceivedTasks();
	bool UpdateAcceptableTasks();
	bool UpdateEnterableFb();
	bool UpdateRoleLvl();
	bool UpdateRoleLvl_Notify();
	bool UpdateExp();
	bool UpdateExp_Notify();
	bool UpdateHp();
	bool UpdateHpSync();
	bool UpdateGold();
	bool UpdateGold_Notify();
	bool UpdateLianQiCao();
	bool UpdateLianQiCaoSync();
	bool UpdateZhanWeiZhi();
	bool UpdateZhanWeiZhiSync();
	bool RefreshZhanWeiZhiMax();
	bool UpdatePoisoningState();
	bool UpdatePoisoningStateSync();
	bool UpdateShouLieQuanCnt();
	bool UpdateLeftShouLieQuanCnt_Notify();
	bool UpdateJingSuanDian();
	bool UpdateJingSuanDianSync();
	bool UpdateCurFarmFacilityInfo();
	bool UpdateOwnerRoomNum() override;

private:
	bool UpdateImpl() override;
	void DoUpdateClear() override;

	//another
public:
	bool IsInVillage() const;
	bool IsInFb() const;
	bool IsInSelfFarm() const;
	//�ȴ���ɫ����
	bool WaitRoleAlive();
	//��ͨ�����Ѿ�����
	//bool IsNormalFbOver() const;
	//�ȴ���ȫʱ��
	void WaitSafeTime();
	bool IsSafeTime();
	//����ƣ��ֵ
	void TellFatigueData( pt_qword fatigue_data );
	//����ƣ��ֵ
	unsigned __int64 CalcFatigueData();
	//��Ҫĥ��
	bool NeedMoDao();
	//�Ƿ��ڸ߶Ⱥ�������
	bool IsInMonsterHighBlackList( const std::string& boss_name ) const;
	//��Ӻ���
	bool AddNewFriend( const std::string& role_name );
	//�õ���ǰ��Ч��������ģʽ
	GType::enFbConsumeMode GetCurFbValidConsumeMode();

	//test
public:
	void Test( int param );
	void Test1( const luabind::object& func );
	bool SendSay( const std::string& say_msg );
	void DebugInfo() const override;
	void SetDeltaAngle( float delta_angle );
	void DebugGridsInfo() const;
	void DebugReceivedTaskInfo() const;
	void DebugAcceptableTasksInfo() const;
	void DebugEnterableFb() const;
	void DebugObjStatus() const;
	void DebugMySellList() const;
	void DebugGainAuctionPagesInfo() const;
	void DebugCurFarmFacilityInfo() const;

private:
	const char*				actor_obj_addr_;
	stCD_NetObj_Role*		cur_role_;
	stCD_SkillObj*			game_skill_;
	stCD_MapDb*			cur_map_db_;

private:
	GItemMgr_Package		grids_package_;			//����
	GItemMgr_Equip			grids_equip_;			//װ��
	GItemMgr_Store			grids_store_;			//�ֿ�
	GItemMgr_SuCai			grids_su_cai_;			//�ز�
	GItemMgr_Task			grids_task_;			//����
	GReceivedTaskMgr		received_task_mgr_;
	GAcceptableTasks		acceptable_tasks_;
	GEnterableFbMgr			enterable_fb_;
	GClass::CurFarmFacilityInfo	cur_farm_facility_info_;
	GClass::CurFarmFieldInfo	cao_yao_tian_info_;

	//��Ϸ����
private:
	int						cur_hp_;
	int						last_update_hit_hp_;
	int						feeb_hp_;
	int						role_lvl_;
	int						left_single_exp_;
	int						left_double_exp_;
	int						left_shou_lie_quan_cnt_;	//ʣ������ȯ
	int						gold_;		//���
	int						silver_;	//����
	int						wait_safe_time_cnt_;
	int						lian_qi_cao_;
	int						zhan_wei_zhi_;
	int						zhan_wei_zhi_max_;
	CD_En_PoisonStatus		poisoning_state_;
	int						jing_suan_dian_;
	std::string				cur_map_name_;			//��ǰ���ڵ�ͼ������
	int						cur_map_id_;
	int						cur_template_map_id_;
	std::string				cur_map_db_info_name_;

	//msg
public:
	MsgOnEnterFbT			msg_on_enter_fb_;
	MsgOnEnterFbErrT		msg_on_enter_fb_err_;
	MsgOnFbInfoOptionalT	msg_last_fb_info_;
	//MsgOnFbInfoT			msg_fb_info_sociaty_;
	//MsgOnFbInfoT			msg_fb_info_miao_miao_;
	//MsgOnFbInfoT			msg_fb_info_qian_shou_;
	MsgMySellListT			msg_my_sell_list_old_;
	TimeElapse				time_to_refresh_my_sell_list_;
	MsgMySellListT			msg_on_my_sell_list_;
	MsgAuctionPageInfoT		msg_last_page_info_;
	AuctionPagesInfoT		msg_auction_pages_info_;
	MsgOnLeftTimeT			msg_left_time_;
	MsgOnBuyAuctionT		msg_on_buy_auction_;
	AuctionItemsContT		other_side_items_;
	MsgOnAcceptMailT		msg_on_accept_mail_;
	MsgOnOpenNpcT			msg_on_open_npc_;
	MsgOnSoldAuctionT		msg_on_sold_auction_;
	MsgOnSoldToShopT		msg_on_sold_to_shop_;
	MsgCommitTaskFailedT	msg_commit_task_failed_;
	MsgOnDoNpcChatT			msg_on_do_npc_chat_;
	MsgOnSendMailT			msg_on_send_mail_;
	MsgOnSendMail2T			msg_on_send_mail2_;
	MsgOnUseItemRet1T		msg_on_use_item_ret1_;
	MsgOnUseItemRet2T		msg_on_use_item_ret2_;
	MsgOnBuyItemT			msg_on_buy_item_;
	MsgOnCollectRetT		msg_on_collect_ret_;
	MsgOnArrangeItemsRetT	msg_on_arrange_items_ret_;
	MsgOnSendMoveRoomRetT	msg_on_send_move_ret_;
	MsgOnAcceptTaskRetT		msg_on_accept_task_;
	MsgOnGiveupTaskRetT		msg_on_giveup_task_;
	MsgOnRequestDealT		msg_on_request_deal_;
	MsgOnRequestDealFailT	msg_on_request_deal_fail_;
	MsgOnRecvQuestDealT		msg_on_recv_quest_deal_;
	MsgOnCancelDealT		msg_on_cancel_deal_;
	MsgOnDealFailT			msg_on_deal_fail_;
	MsgOnMoveItemToDealTabT	msg_on_move_item_deal_tab_;
	MsgOnMoveDealGoldT		msg_on_move_deal_gold_;
	MsgOnRecvDealStatusT	msg_on_recv_deal_status_;
	MsgOnRecvDealStatusT	msg_on_deal_status_self_;
	MsgOnRecvDealStatusT	msg_on_deal_status_other_;
	MsgOnRecvDealEndT		msg_on_recv_deal_end_;
	MsgOnGetMailItemsInfoT	msg_on_get_mail_items_info_;

	//��������
public:
	float					delta_angle_;			//��������ϵ����������ϵ֮��ļн�
	float					move_step_dist_;
	CMDR_Hook_SendMoveRoom	msg_on_hook_move_room_;
	//SharedMutex				mutex_msg_on_hook_move_room_;
	volatile bool			is_send_move_room_;
	int						last_room_id_for_send_room_;
	//boost::optional<GType::stGameVector3>		last_send_role_pos_;
	bool					is_active_cross_map_;		//�Ƿ�������ͼ
	bool					is_hitting_monster_;
	bool					is_throw_data_error_;
	int						min_gold_to_keep_buy_;				//���ϵĽ�Ҵ�����������Ż�ȥ���ֹ���
	int						min_silver_to_keep_buy_;			//���ϵĽ�Ҵ�����������Ż�ȥ���ֹ���
	bool					is_open_village_path_;
	int						fb_server_full_cnt_;					//��������������
	bool					is_dealing_handle_;
	bool					handle_can_not_move_state_;
	GType::enFbConsumeMode	fb_consume_mode_;
	int						fb_consume_mode_min_silver_;
	bool					move_fb_strict_;

	bool					is_right_bt_hit_;
	boost::optional<stLastSendMoveRoomInfo>	last_send_move_cmd_;
	std::pair<GType::stGameVector3, int>	last_valid_pos_;

	//��Ʒ�������Ͱ�����
private:
	std::shared_ptr<CmnPriLuaData>	item_black_white_list_;
	NameList_StrT						item_name_black_list_;
	NameList_StrT						item_name_white_list_;
	int							white_list_item_lvl_;			
	CD_En_ItemQuality		white_list_item_quality_;
	int							white_list_craft_item_lvl_;			//��������Ʒ�ĵȼ�
	CD_En_ItemQuality		white_list_craft_item_quality_;
	int							white_list_lvl_up_equip_lvl_;
	CD_En_ItemQuality		white_list_lvl_up_equip_quality_;
	int							white_list_facture_lvl_;
	CD_En_ItemQuality		white_list_facture_quality_;

	NameList_StrT					auto_lvl_up_equip_black_list_;
	NameList_StrT					store_white_name_list_;

	ShangJinWhiteListT			shang_jin_white_list_;
	NameList_IntT				shang_jin_dst_fb_black_list_;
	NameList_IntT				shang_jin_dst_fb_stable_black_list_;
	NameList_IntT				cat_fb_black_list_;
	NameList_IntT				fb_black_list_;					//����������

	NameList_StrT					collect_black_list_;			//�ɼ�������
	NameList_StrT					auto_wear_black_list_;			//�Զ�����װ������

public:
	WearWhiteListT					auto_wear_white_list_;

public:
	GClass::GHitMonsterModeBase*	cur_hit_mode_;
	GClass::GHitMonsterMode_Mouse	hit_mode_mouse_;
	GClass::GHitMonsterMode_UsePacketItem	hit_mode_use_packet_item_;
	CMDR_OnFbInfo::FbIdsT					fb_info_cat_;			//�հ��õ�����������
};