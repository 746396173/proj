#include "stdafx.h"
#include "GMap.h"
#include "GAddr.h"
#include "GOffset.h"
#include "../FuncObjC.h"
#include "GStrMap.h"

GMap::GMap()
{
	//is_town_ = true;
	map_lvl_ = GType::kFD_Zero;
	stage_template_ = nullptr;
}

bool GMap::IsTown() const
{
	return GType::kFD_Zero == map_lvl_;
	//return is_town_;
}

struct stSdbStageTemplate{
	DWORD				str_dwVFunAddr;
	DWORD				str_dwStageType;			// ����=1,����=0
	GClass::stGameString		str_theId;					// +8
	GClass::stGameString		str_theStartingSectorId;	// +24
	GClass::stGameString		str_theEnteringWarpGateId;	// +40	10.30��ɾ����������
	GAME_STRING_VF_ID	str_theName;				// +5C
	GAME_STRING_VF_ID	str_theClearConditionDesc;	// +7C
	int					str_dwRecommandLevel[2];
	DWORD				str_dwEnterLevelRange[2];	// +A4	20150316
	DWORD				str_dwRecommandDPS;			// 10.30��ɾ����������
	DWORD				str_dwExperiencedDifficulty;
	XYZ					str_theStartingDirection;	// +AC
	GStageTemplate::GateLinksInfoMgr::stGameTArray		str_theWarpGateLinkInfos;		// +B8  ������������Ϣ
	GClass::BTreeMgrBase::stGBTreeNodes				str_theSectors;					// +CC  ��ǰ��ͼ�ķ���
	GAME_STRUCT_ARRAY_POINT		str_theRandomRoute;				// +D8
	GAME_STRUCT_ARRAY_POINT		str_theUniqueDropListForShowing;
	GAME_STRUCT_ARRAY_POINT		str_theClearBuffListForShowing;	// +F8
	DWORD						str_dwClearExp;						// 
	DWORD						str_dwClearGold;
	GAME_STRING_ID				str_theClearMedal;
	GClass::BTreeMgrBase::stGBTreeNodes					str_theStageObjectNpcs;				// BOOS
	BINARY_TREE_MAP				str_theStageFailObjectNpcs;
	GAME_STRUCT_ARRAY_POINT		str_theClearConditions;
	GAME_STRUCT_ARRAY_POINT		str_theFailConditions;				// 
	FLOAT						str_fStartingPositionX;
	FLOAT						str_fStartingPositionY;
	DWORD						str_dwMinimumLevelToGetLicense;
	DWORD						str_dwGetResurrectionSicknessWhenFailed;
	GAME_STRING_ID_				str_theMinimapPath;
	GAME_STRING_ID_				str_theFishingSiteMinimapPath;		// 1230����
	GAME_STRUCT_ARRAY_POINT		str_theCameraEffectPaths;
	DWORD						str_dwLevel;		// 
	int						str_dwFatigue;		// 
	BYTE						str_bEnableStageFailBuff;
	BYTE						str_bIsRestartable;
	WORD						str_wUnKnow1;
	BINARY_TREE_MAP				str_theMonsterStatusBonus;
	BINARY_TREE_MAP				str_theMonsterStatusBonusByDelta;
	GAME_STRING_ID				str_theBgmCue;
	GAME_STRING_ID				str_theBossBgmCue;
	BINARY_TREE_MAP				str_theAmbientSoundEvents;
	FLOAT						str_fStartingRectangleX;
	FLOAT						str_fStartingRectangleY;
};
static_assert(sizeof(stSdbStageTemplate) == sizeof(SDB_STAGE_INFO), "");

struct stGameMapObj{
	const void*					vtbl_;
	const stSdbStageTemplate*	stage_template_;
	const void*					unknwon_obj_addr_;
	const GClass::stGameString	str_theId;
	const GType::enFbDifficulty	str_dwLevel;		//�����ȼ�������ȼ���Ϊ0
	DWORD			str_dwUnKnow2;
	GClass::BTreeMgrBase::stGBTreeNodes	str_theAlreadyClearSector;		// �Ѿ���������ĸ����������մ��꿪�ź�ķ���
};
static_assert(sizeof(stGameMapObj) == sizeof(MAP_DATA), "");

bool GMap::Update()
{
	using namespace GAddr;
	if ( !g_pCurMapObjAddr )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "��ǰ��ͼ�����ַΪ��";
		assert(false);
		return false;
	}
	bool res = timer_sync_exec_.TimerGWndExecSync([this](){
		return DoUpdateImpl();
	});
	if (IsTown())
	{
		g_through_room_valid_data_x = 0;
		g_through_room_valid_data_y = 0;
		g_through_room_dummy_exist = false;
	}
	return res;
}

GType::enFbDifficulty GMap::GetDifficulty() const
{
	return map_lvl_;
}

const std::wstring& GMap::GetMapId() const
{
	return map_id_;
}

const std::wstring& GMap::GetBossRoomName() const
{
	if ( !stage_template_ )
	{
		assert(false);
		return kEmptyWStr;
	}
	auto boss_sector = stage_template_->GetSectors().GetBossSector();
	if ( !boss_sector )
	{
		assert(false);
		return kEmptyWStr;
	}
	return boss_sector->GetSectorId();
}

const GStageTemplate* GMap::GetStageTemplate() const
{
	return stage_template_;
}

bool GMap::DoUpdateImpl()
{
	using namespace GAddr;
	using namespace GOffset;
	using namespace GClass;
	using namespace GType;
	/*if ( !g_pGameMapObjAddr )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "g_pGameMapObjAddrΪ��";
		assert(false);
		return false;
	}
	if ( !MemOperApplyR(is_town_, (int)g_pGameMapObjAddr, g_o_is_town) )
	{
		assert(false);
		return false;
	}*/
	if ( !g_pCurMapObjAddr )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "��ǰ��ͼ�����ַΪ��";
		assert(false);
		return false;
	}
	auto map_id_old = map_id_;
	//////////////////////////////////////////////////////////////////////////
	const stGameMapObj* game_map = nullptr;
	if ( !MemOperApplyR(game_map, (int)g_pCurMapObjAddr, g_o_map_obj) || !game_map )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "game map obj read error";
		assert(false);
		return false;
	}
	if ( !game_map->stage_template_ )
	{
		assert(false);
		return false;
	}
	if ( !game_map->str_theId.CopyTo(map_id_) )
	{
		assert(false);
		return false;
	}
	if (map_id_.empty())
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_debug) << "map id����Ϊ��";
		assert(false);
		return false;
	}
	/*if (is_town_)
	{
		if ( kFD_Zero != game_map->map_lvl_ )
		{
			assert(false);
			return false;
		}
	}
	else
	{
		if ( game_map->map_lvl_ < kFD_Normal || game_map->map_lvl_ >= kFD_Invalid )
		{
			assert(false);
			return false;
		}
	}*/
	if ( game_map->str_dwLevel < kFD_Zero || game_map->str_dwLevel >= kFD_Invalid )
	{
		assert(false);
		return false;
	}
	map_lvl_ = game_map->str_dwLevel;
	auto& stage_mgr = GStageTemplateMgr::GetMe();
	stage_template_ = stage_mgr.FindStage(map_id_);
	if ( !stage_template_ )
	{
		auto& stage_cont = stage_mgr.GetAllNodes();
		LOG_ENTER_FUNC;
		LOG_O(Log_debug) << "stagetģ�����Ҳ���map id->" << map_id_ << "\t����������stageģ��ID����������->" << stage_cont.size();
		for ( auto& the_stage : stage_cont )
		{
			LOG_O(Log_debug) << the_stage.GetStageId();
		}
		assert(false);
		return false;
	}
	/*if ( !UpdateClearSectors(&game_map->str_theAlreadyClearSector) )
	{
		assert(false);
		return false;
	}*/
	//////////////////////////////////////////////////////////////////////////
	if ( map_id_old != map_id_ && !map_id_.empty() )
	{
		auto funcobj = FuncObj_NormalC::GetInstance();
		if ( !funcobj )
		{
			LOG_ENTER_FUNC;
			LOG_O(Log_error) << "func obj normalC������";
			return false;
		}
		funcobj->GetSessionOper().ThisMemCall(nullptr, "SetCurMapRoomName", &JsonEcho::MakeParams(WideCharToGbk(GetCurMapFbChName())));
	}
	return true;
}

bool GMap::UpdateClearSectors( const GClass::BTreeMgrBase::stGBTreeNodes* the_node )
{
	assert(the_node);
	the_clear_sectors_.SetGameNodes(the_node);
	if ( !the_clear_sectors_.RebuildUpdateAll() )
	{
		assert(false);
		return false;
	}
	return true;
}

bool GMap::UpdateClearSectors()
{
	using namespace GAddr;
	using namespace GOffset;
	if ( !g_pCurMapObjAddr )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "��ǰ��ͼ�����ַΪ��";
		assert(false);
		return false;
	}
	const stGameMapObj* game_map = nullptr;
	if ( !MemOperApplyR(game_map, (int)g_pCurMapObjAddr, g_o_map_obj) || !game_map )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "game map obj read error";
		assert(false);
		return false;
	}
	if ( !UpdateClearSectors(&game_map->str_theAlreadyClearSector) )
	{
		assert(false);
		return false;
	}
	return true;
}

bool GMap::UpdateClearSectorsSync()
{
	using namespace GAddr;
	if ( !g_pCurMapObjAddr )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "��ǰ��ͼ�����ַΪ��";
		assert(false);
		return false;
	}
	return GWndExecSync([this](){
		return UpdateClearSectors();
	});
}

bool GMap::ExistTheClearedSector( const std::wstring& sector_id ) const
{
	assert(!sector_id.empty());
	auto& the_cont = the_clear_sectors_.GetAllNodes();
	auto it = std::find_if(the_cont.begin(), the_cont.end(), [&sector_id]( const ClearSector& clear_sector ){
		return clear_sector.GetClearedSector() == sector_id;
	});
	return it != the_cont.end();
}

std::wstring GMap::GetCurMapFbChName() const
{
	if (map_id_.empty())
	{
		assert(false);
		return kEmptyWStr;
	}
	const auto& str_map = GameEn2ChNodeMgr::GetMe();
	GameEn2ChNodeMgr::StrIndexPtr stage_index;
	if (IsTown())
		stage_index = str_map.GetVillageIndex();
	else
		stage_index = str_map.GetStageIndex();
	if ( !stage_index )
	{
		assert(false);
		return kEmptyWStr;
	}
	return stage_index->En2Ch(map_id_);
}

struct stSdbMapInfo : GStageTemplate::GSector::stBTreeNodeBase{
	const GClass::stGameString	room_id_;
	const GClass::stGameStringEx	res_uri_;
};
static_assert(sizeof(stSdbMapInfo) == sizeof(MAP_INFO), "");

struct stSdbBossInfo : GStageTemplate::GameRoomBoss::stBTreeNodeBase{
	const GClass::stGameString_4	boss_name_;
};
static_assert(sizeof(stSdbBossInfo) == sizeof(BOOS_INFO), "");

bool GStageTemplate::GameRoomBoss::Update()
{
	if ( !game_cur_node_ )
	{
		assert(false);
		return false;
	}
	const auto node = (stSdbBossInfo*)game_cur_node_;
	if ( !node->boss_name_.game_str_.CopyTo(boss_name_) )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "boss name read error";
		assert(false);
		return false;
	}
	return true;
}

GStageTemplate::GateLinksInfo::GateLink::stGateInfo::stGateInfo()
{
	enable_ = false;
}

bool GStageTemplate::GateLinksInfo::GateLink::stGateInfo::CopyFrom( const stGameGate& game_gate )
{
	if ( !game_gate.str_theStageId.CopyTo(stage_id_) )
	{
		assert(false);
		return false;
	}
	if ( !game_gate.str_theSectorId.CopyTo(sector_id_) )
	{
		assert(false);
		return false;
	}
	if ( !game_gate.str_theWarpGateId.CopyTo(warp_gate_id_) )
	{
		assert(false);
		return false;
	}
	assert(0 == game_gate.str_bEnable || 1 == game_gate.str_bEnable);
	enable_ = !!game_gate.str_bEnable;
	return true;
}

bool GStageTemplateMgr::UpdateAll()
{
	if ( !btree_.empty() )
		return true;
	return __super::UpdateAll();
}

bool GStageTemplateMgr::RebuildUpdateAll()
{
	using namespace GAddr;
	using namespace GClass;
	if ( !btree_.empty() )
		return true;
	SetGameNodes((const stGBTreeNodes*)g_pStageTemplate);
	if ( !__super::RebuildUpdateAll() )
	{
		assert(false);
		return false;
	}
	assert(!btree_.empty());
	return true;
}

const GStageTemplate* GStageTemplateMgr::FindStage( const std::wstring& stage_id )
{
	if (stage_id.empty())
	{
		assert(false);
		return nullptr;
	}
	for ( const auto& stage : btree_ )
	{
		if ( stage_id == stage.GetStageId() )
			return &stage;
	}
	return nullptr;
}

bool GStageTemplate::Update()
{
	using namespace GOffset;
	typedef GClass::SdbIndex<stSdbStageTemplate> stSdbIndex;
	if ( !game_cur_node_ )
	{
		assert(false);
		return false;
	}
	auto db_index = (const stSdbIndex*)game_cur_node_;
	auto stage_template = db_index->real_obj_;
	if ( !stage_template )
	{
		assert(false);
		return false;
	}
	assert(stage_template->str_dwStageType >= kST_CloneMap && stage_template->str_dwStageType <= kST_PVP);
	stage_type_ = (enStageType)stage_template->str_dwStageType;
	if ( !stage_template->str_theId.CopyTo(stage_id_) )
	{
		assert(false);
		return false;
	}
	if ( !stage_template->str_theStartingSectorId.CopyTo(starting_sector_id_) )
	{
		assert(false);
		return false;
	}
	link_infos_.SetGameTArray(&stage_template->str_theWarpGateLinkInfos);
	if ( !link_infos_.RebuildUpdateAll() )
	{
		assert(false);
		return false;
	}
	sectors_mgr_.SetGameNodes(&stage_template->str_theSectors);
	if ( !sectors_mgr_.RebuildUpdateAll() )
	{
		assert(false);
		return false;
	}
	game_room_boss_mgr_.SetGameNodes(&stage_template->str_theStageObjectNpcs);
	if ( !game_room_boss_mgr_.RebuildUpdateAll() )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "��ͼ������boss�ı���ʧ��";
		assert(false);
		return false;
	}
	fatigue_of_use_ = stage_template->str_dwFatigue;
	assert(fatigue_of_use_ >= 0);
	recommand_lvl_lower_ = (int)stage_template->str_dwRecommandLevel[0];
	assert(recommand_lvl_lower_ >= 0);
	recommand_lvl_upper_ = (int)stage_template->str_dwRecommandLevel[1];
	assert(60 == recommand_lvl_upper_ || recommand_lvl_upper_ >= recommand_lvl_lower_);
	is_arena_stage_ = *((bool*)((char*)stage_template + g_o_is_arena_stage));
	assert(0 == (int)is_arena_stage_ || 1 == (int)is_arena_stage_);
	return true;
}

const GStageTemplate::GateLinksInfoMgr& GStageTemplate::GetGateLinksInfo() const
{
	return link_infos_;
}

GStageTemplate::GStageTemplate()
{
	stage_type_ = kST_PVP;
	fatigue_of_use_ = 0;
	recommand_lvl_lower_ = 0;
	recommand_lvl_upper_ = 0;
	is_arena_stage_ = false;
}

bool GStageTemplate::IsTown() const
{
	return kST_Town == stage_type_;
}

const std::wstring& GStageTemplate::GetStageId() const
{
	return stage_id_;
}

const GStageTemplate::GSectorsMgr& GStageTemplate::GetSectors() const
{
	return sectors_mgr_;
}

const std::wstring& GStageTemplate::GetStartingSectorId() const
{
	return starting_sector_id_;
}

bool GStageTemplate::IsCloneMap() const
{
	return kST_CloneMap == stage_type_;
}

int GStageTemplate::FatigueOfUse() const
{
	return fatigue_of_use_;
}

int GStageTemplate::GetRecommandLvlLower() const
{
	return recommand_lvl_lower_;
}

bool GStageTemplate::IsArenaStage() const
{
	return is_arena_stage_;
}

int GStageTemplate::GetRecommandLvlUpper() const
{
	return recommand_lvl_upper_;
}

bool GStageTemplate::ValidLvlBetweenRecommandLvl( int the_lvl ) const
{
	return the_lvl >= recommand_lvl_lower_ && the_lvl <= recommand_lvl_upper_;
}

bool GStageTemplate::ValidRangeThanRecommandUpperLvl( int the_lvl ) const
{
	auto abs_value = std::abs(the_lvl - recommand_lvl_upper_);
	return abs_value <= 7;
}

bool GStageTemplate::IsNormalRecommandLvlFb() const
{
	auto abs_value = std::abs(recommand_lvl_upper_ - recommand_lvl_lower_);
	return abs_value <= 10;
}

bool GStageTemplate::GateLinksInfo::Update()
{
	if ( !cur_obj_addr_ )
	{
		assert(false);
		return false;
	}
	auto gate_links = (const stGateLinksInfo*)cur_obj_addr_;
	gate_link_mgr_.SetGameTArray(&gate_links->str_theWarpGeteLinkInfosNode);
	if ( !gate_link_mgr_.RebuildUpdateAll() )
	{
		assert(false);
		return false;
	}
	return true;
}

const GStageTemplate::GateLinksInfo::GateLinkMgr& GStageTemplate::GateLinksInfo::GetGateLinkMgr() const
{
	return gate_link_mgr_;
}

bool GStageTemplate::GateLinksInfo::GateLink::Update()
{
	if ( !cur_obj_addr_ )
	{
		assert(false);
		return false;
	}
	auto game_gate_link = (const stGameGateLink*)cur_obj_addr_;
	if ( !gate_src_.CopyFrom(game_gate_link->gate_src_) )
	{
		assert(false);
		return false;
	}
	if ( !gate_dst_.CopyFrom(game_gate_link->gate_dst_) )
	{
		assert(false);
		return false;
	}
	return true;
}

bool GStageTemplate::GateLinksInfo::GateLinkMgr::RebuildUpdateAll()
{
	if ( !__super::RebuildUpdateAll() )
		return false;
	assert(cont_.empty() || 1 == cont_.size());
	return true;
}

GVillageFbMap GVillageFbMap::map_instance_;

void GVillageFbMap::AddMap( const std::wstring& village_id, const std::wstring& clone_map_id )
{
	assert(false);
	return;
	/*assert(!village_id.empty());
	assert(!clone_map_id.empty());
	assert(!Find_Fb2Village(clone_map_id));
	village_fb_map_.insert(MapT::value_type(village_id, clone_map_id));*/
}

GVillageFbMap::GVillageFbMap()
{
	/*
	//��������
	//����С��
	AddMap(L"Ep01Village01", L"Ep01Stage01");
	//����б��
	AddMap(L"Ep01Village01", L"Ep01Stage02");
	//����Ӫկ
	AddMap(L"Ep01Village01", L"Ep01Stage03");

	//���ز�·
	//����ɭ��
	AddMap(L"Ep02Village02", L"Ep02Stage03");
	//����Ͽ��
	AddMap(L"Ep02Village02", L"Ep02Stage04");

	//ɽ������
	//�ն���Χ
	AddMap(L"Ep02Village01", L"Ep02Stage01");
	//�ն�����ɽ��
	AddMap(L"Ep02Village01", L"Ep02Stage02");
	//�������פ��
	AddMap(L"Ep02Village01", L"Ep02Stage05");
	//������ŷɿ�ͧ��ͷ
	AddMap(L"Ep02Village01", L"Ep02Stage06");

	//�����Ͽ����
	//�����Ͽ����
	AddMap(L"Ep03Village01", L"Ep03Stage01");
	//����Ī˹ʵ����
	AddMap(L"Ep03Village01", L"Ep03Stage02");
	//����Ī˹����Χ��
	AddMap(L"Ep03Village01", L"Ep03Stage03");
	//�Ͽ��
	AddMap(L"Ep03Village01", L"Ep03Stage04");
	//ħ����Ѩ
	AddMap(L"Ep03Village01", L"Ep03Stage0A");
	//Ԫ���׶�
	AddMap(L"Ep03Village01", L"Ep03Stage0B");

	//��Ӱ��
	//����ɽ��
	AddMap(L"Ep04Village01", L"Ep04Stage01");
	//����Ͽ��
	AddMap(L"Ep04Village01", L"Ep04Stage02");
	//��������
	AddMap(L"Ep04Village01", L"Ep04Stage03");
	//��ӡ֮��
	AddMap(L"Ep04Village01", L"Ep04Stage0A");
	//�����ַ�������
	AddMap(L"Ep04Village01", L"Ep04Stage0B");
	//�����ֻҽ�����
	AddMap(L"Ep04Village01", L"Ep04Stage0C");
	//�����ֳ��ؼ�̳
	AddMap(L"Ep04Village01", L"Ep04Stage0D");

	//����³���㳡
	//������ͭ�ݶ�·
	AddMap(L"Ep05Village01", L"Ep05Stage01");
	//�ɿ�ͧ׹��֮��
	AddMap(L"Ep05Village01", L"RgSd_St14");
	//������������ǽ
	AddMap(L"Ep05Village01", L"Ep05Stage02");
	//���¶��䳤��
	AddMap(L"Ep05Village01", L"Ep05Stage06");

	//���º��
	//����������ˮ��
	AddMap(L"Ep05Village02", L"Ep05Stage03");
	//�����ĺ�ɫ�糡
	AddMap(L"Ep05Village02", L"Ep05Stage04");
	//���¶�������ǽ
	AddMap(L"Ep05Village02", L"Ep05Stage05");

	//�������ɸ�
	//������������ͷ
	AddMap(L"Ep06Village01", L"Ep06Stage01");
	//С�󺣵��ų�Ѩ
	AddMap(L"Ep06Village01", L"Ep06Stage02");
	//�����������׳�
	AddMap(L"Ep06Village01", L"Ep06Stage03");
	//���ȵĲر���Ѩ
	AddMap(L"Ep06Village01", L"Ep06Stage04");
	//�Ŵ�������ĹѨ
	AddMap(L"Ep06Village01", L"Ep06Stage05");
	//���ǻƽ���ͷ
	AddMap(L"Ep06Village01", L"Ep06Stage06");

	//�����и����
	//�����³����л����
	AddMap(L"Ep05Village03", L"Ep05Stage0A");
	//���½�����
	AddMap(L"Ep05Village03", L"Ep05Stage0B");
	//���¹���������
	AddMap(L"Ep05Village03", L"Ep05Stage0C");
	*/
}

const std::wstring* GVillageFbMap::Find_Fb2Village( const std::wstring& clone_map_id ) const
{
	auto sub_stage = GRegionStageMapTemplateMgr::GetMe().Fb2Village(clone_map_id);
	if ( !sub_stage )
		return nullptr;
	return &sub_stage->GetSubStageId();
	/*auto it_end = village_fb_map_.end();
	for ( auto it = village_fb_map_.begin(); it != it_end; ++it )
	{
		if ( it->second == clone_map_id )
			return &it->first;
	}
	return nullptr;*/
}

struct stSdbSector{
	NODE				str_theNode;
	GAME_STRING_ID		str_theId_;
	DWORD				str_dwVFunAddr;
	GAME_STRING_ID_		str_theSectorPath;
	GClass::stGameString		str_theId;
	DWORD				str_dwSectorResetType;				// ������������
	GAME_STRUCT_ARRAY_POINT		str_theSectorLimitPoints;
	GAME_STRUCT_ARRAY_POINT		str_theRestrictions;
	GAME_STRUCT_ARRAY_POINT		str_theLocations;
	bool						str_bIsBossSector;			// �Ƿ�ΪBOOS����
	DWORD						str_dwMinimapOffset[2];
	DWORD						str_dwMinimapSize[2];
	BINARY_TREE_MAP				str_theWarpGates;			// +88 ���䴫����	
	GAME_STRUCT_ARRAY_POINT		str_theStageStartWarpGates;	// stage��ʼ������
	GAME_STRUCT_ARRAY_POINT		str_thePopInfos;
	GStageTemplate::GSector::GFixedNpcTArray::stGameTArray		str_theFixedNpcs;			// ����NPC
	GAME_STRUCT_ARRAY_POINT		str_theInteractiveNpcs;		
	GAME_STRUCT_ARRAY_POINT		str_theFixedNpcsByQuest;
	GAME_STRUCT_ARRAY_POINT		str_theBuffFloors;
	GAME_STRUCT_ARRAY_POINT		str_theStartingRedWall;
	GAME_STRUCT_ARRAY_POINT		str_theStartingBlueWall;
	GAME_STRUCT_ARRAY_POINT		str_theAdditionalNpcPopInfos;
	GAME_STRING_ID				str_theReverbPreset;
	struct  
	{
		DWORD					str_dwVFunAddr;
		GAME_STRING_ID			str_theCinematicDialogId;
		GAME_STRUCT_ARRAY_POINT	str_theCreateItems;
	}theClearEventInfo;		// +144
	struct  
	{
		DWORD					str_dwVFunAddr;
		GAME_STRING_ID			str_theWarpGateId;
		DWORD					str_dwDelayTime;
	}theAutoWarpGateAfterSectorClearInfo;		// +174
	struct  
	{
		DWORD					str_dwVFunAddr;
		GAME_STRING_ID			str_theUnknow1;
	}theUnKnow1;
	XYZ							str_theSectorCenterPosition;
	XYZ							str_theSectorRebirthPosition;
	XYZ							str_theSectorRebirthDirection;
	XYZ							str_theSectorEscortPosition;
	struct  
	{
		DWORD					str_dwVFunAddr;
		struct  
		{
			DWORD				str_dwVFunAddr;
			GAME_STRING_ID		str_theEnterMessage;
		}theEnterMessage;
		struct  
		{
			DWORD				str_dwVFunAddr;
			GAME_STRING_ID		str_theClearMessage;
		}theClearMessage;
		GAME_STRUCT_ARRAY_POINT		str_theTimeMessage;
		GAME_STRUCT_ARRAY_POINT		str_theMonsterMessage;
	}theSectorMessageInfo;
};
static_assert(sizeof(stSdbSector) == sizeof(SDB_SECTOR), "SDB_SECTOR");

bool GStageTemplate::GSector::Update()
{
	if ( !game_cur_node_ )
	{
		assert(false);
		return false;
	}
	auto game_sector = (const stSdbSector*)game_cur_node_;
	if ( !game_sector->str_theId.CopyTo(sector_id_) )
	{
		assert(false);
		return false;
	}
	assert(1 == (int)game_sector->str_bIsBossSector || 0 == (int)game_sector->str_bIsBossSector);
	boss_room_ = game_sector->str_bIsBossSector;
	fixed_npcs_.SetGameTArray(&game_sector->str_theFixedNpcs);
	if ( !fixed_npcs_.RebuildUpdateAll() )
	{
		assert(false);
		return false;
	}
	return true;
}

GStageTemplate::GSector::GSector()
{
	boss_room_ = false;
}

const std::wstring& GStageTemplate::GSector::GetSectorId() const
{
	return sector_id_;
}

bool GStageTemplate::GSector::IsBossRoom() const
{
	return boss_room_;
}

bool GStageTemplate::GSector::GFixedNpc::Update()
{
	if ( !cur_obj_addr_ )
	{
		assert(false);
		return false;
	}
	auto fixed_npc = (const stFixedNpc*)cur_obj_addr_;
	if ( !fixed_npc->str_theId.CopyTo(fixed_npc_id_) )
	{
		assert(false);
		return false;
	}
	return true;
}

const GStageTemplate::GSector* GStageTemplate::GSectorsMgr::GetBossSector() const
{
	for ( const auto& sector : btree_ )
	{
		if (sector.IsBossRoom())
			return &sector;
	}
	return nullptr;
}

bool GRegionStageMapTemplateMgr::RebuildUpdateAll()
{
	using namespace GClass;
	using namespace GAddr;
	using namespace GOffset;
	const auto nodes = (const BTreeMgrBase::stGBTreeNodes*)g_pRegionStageMapTemplate;
	if ( nodes->node_cnt_ == btree_.size() )
		return true;
	SetGameNodes(nodes);
	if ( !__super::RebuildUpdateAll() )
	{
		assert(false);
		return false;
	}
	assert(!btree_.empty());
	//assert(nodes->node_cnt_ == btree_.size());
	return true;
}

bool GRegionStageMapTemplateMgr::UpdateAll()
{
	if ( !btree_.empty() )
		return true;
	return __super::UpdateAll();
}

const GRegionStageMapTemplate* GRegionStageMapTemplateMgr::FindByStageId( const std::wstring& stage_id ) const
{
	for ( const auto& v : btree_ )
	{
		if (v.GetSubStages().ExistTheStageId(stage_id))
			return &v;
	}
	assert(false);
	return nullptr;
}

const GRegionStageMapTemplate::SubStage* GRegionStageMapTemplateMgr::Fb2Village( const std::wstring& fb_id ) const
{
	for ( const auto& v : btree_ )
	{
		auto sub_stage = v.GetSubStages().Fb2Vaillage(fb_id);
		if (sub_stage)
			return sub_stage;
	}
	return nullptr;
}

struct stSdbRegionTemplate{
	DWORD					str_dwVFunAddr;
	GClass::stGameString			str_theId;
	GClass::stGameStringEx		str_theName;
	GAME_STRING_ID_			str_theWorldMapImagePath;
	GAME_STRING_ID_			str_theStageSelectBackgroundImagePath;
	GRegionStageMapTemplate::SubStageTArray::stGameTArray		str_theStageIds;					// �����ͳ���ӳ��
	GAME_STRUCT_ARRAY_POINT		str_theStageGroups;
	DWORD						str_dwMinLevelToEnter;
};
static_assert(sizeof(stSdbRegionTemplate) == sizeof(SDB_REGION_INFO), "SDB_REGION_INFO");

bool GRegionStageMapTemplate::Update()
{
	typedef GClass::SdbIndex<stSdbRegionTemplate> stSdbIndex;
	if ( !game_cur_node_ )
	{
		assert(false);
		return false;
	}
	auto region_ptr = ((const stSdbIndex*)game_cur_node_)->real_obj_;
	if ( !region_ptr )
	{
		assert(false);
		return false;
	}
	if ( !region_ptr->str_theId.CopyTo(region_id_) )
	{
		assert(false);
		return false;
	}
	if ( !region_ptr->str_theName.game_str_.CopyTo(region_name_) )
	{
		assert(false);
		return false;
	}
	sub_stages_.SetGameTArray(&region_ptr->str_theStageIds);
	if ( !sub_stages_.RebuildUpdateAll() )
	{
		assert(false);
		return false;
	}
	return true;
}

const GRegionStageMapTemplate::SubStageTArray& GRegionStageMapTemplate::GetSubStages() const
{
	return sub_stages_;
}

bool GRegionStageMapTemplate::ObjValid()
{
	typedef GClass::SdbIndex<stSdbRegionTemplate> stSdbIndex;
	if ( !game_cur_node_ )
	{
		assert(false);
		return false;
	}
	auto region_ptr = ((const stSdbIndex*)game_cur_node_)->real_obj_;
	if ( !region_ptr )
	{
		assert(false);
		return false;
	}
	if ( !region_ptr->str_theId.CopyTo(region_id_) )
	{
		assert(false);
		return false;
	}
	if (region_id_.empty())
	{
		assert(false);
		return false;
	}
	if ( !region_ptr->str_theName.game_str_.CopyTo(region_name_) )
	{
		assert(false);
		return false;
	}
	auto& str_mgr = GameEn2ChNodeMgr::GetMe();
	const auto& the_cn_name = str_mgr.FindChByFullPath(region_name_);
	if (the_cn_name.empty())
	{
		assert(false);
		return false;
	}
	static const wchar_t* kTheChNames[] = {
		L"��������", L"���ز�·", L"ɽ������", L"�����Ͽ����", L"�����и����",
		L"����³���㳡", L"���º��", L"��Ӱ��", L"���»ƽ�Ϧ����", L"�������ɸ�"
	};
	auto it_cn_name = std::find(kTheChNames, kTheChNames + _countof(kTheChNames), the_cn_name);
	if ( it_cn_name == kTheChNames + _countof(kTheChNames) )
		return false;
	LOG_O(Log_trace) << "the region id :" << region_id_ << "\tregion name->" << region_name_ << "\tcn name->" << the_cn_name;
	return true;
}

bool GRegionStageMapTemplate::SubStage::Update()
{
	if ( !cur_obj_addr_ )
	{
		assert(false);
		return false;
	}
	auto stage_id = (const GameType*)cur_obj_addr_;
	if ( !stage_id->CopyTo(stage_id_) )
	{
		assert(false);
		return false;
	}
	return true;
}

const std::wstring& GRegionStageMapTemplate::SubStage::GetSubStageId() const
{
	return stage_id_;
}

bool GRegionStageMapTemplate::SubStageTArray::ExistTheStageId( const std::wstring& stage_id ) const
{
	for ( const auto& v : cont_ )
	{
		if ( v.GetSubStageId() == stage_id )
			return true;
	}
	return false;
}

const GRegionStageMapTemplate::SubStage* GRegionStageMapTemplate::SubStageTArray::Fb2Vaillage( const std::wstring& fb_id ) const
{
	const auto kSize = cont_.size();
	for ( int i = 1; i < kSize; ++i )
	{
		if ( cont_[i].GetSubStageId() == fb_id )
		{
			return &cont_[0];
		}
	}
	return nullptr;
}

const std::wstring& GMap::ClearSector::GetClearedSector() const
{
	return cleard_sector_;
}

struct stClearedSector
{
	NODE					str_theNode;
	GClass::stGameString	str_theId;
};
static_assert(sizeof(CLEAR_SECTOR) == sizeof(stClearedSector), "");

bool GMap::ClearSector::Update()
{
	if ( !game_cur_node_ )
	{
		assert(false);
		return false;
	}
	auto the_sector = (const stClearedSector*)game_cur_node_;
	if ( !the_sector->str_theId.CopyTo(cleard_sector_) )
	{
		assert(false);
		return false;
	}
	return true;
}
