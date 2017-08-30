#include "stdafx.h"
#include "GMatch.h"
#include "FuncObjC.h"
#include "Protocol/P_NormalMsg.h"
#include "GPlayer.h"

//global functions
//������½�
bool PressRightBottomBt()
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
		return false;
	func_obj_normal->GetGLua().LuaObjCall<void>("HandlePressRightBottomBt");
	return true;
}

GMatchMgr::GMatchMgr()
{
	match_mode_ = &match_mode_invalid_;

	match_mode_invalid_.SetParent(this);
	//ע��֧�ֵı���ģʽ
	//������ģʽ
	RegisterRuntimeClass(GType::enMatchMode_Managers, GET_RUNTIME_CLASS(MatchMode_Managers));
	//�Զ���ģʽ
	RegisterRuntimeClass(GType::enMatchMode_Custom, GET_RUNTIME_CLASS(MatchMode_Custom));
}

IGMatchMgr::~IGMatchMgr(){}

IGMatchMgr& IGMatchMgr::GetMe()
{
	static GMatchMgr match_mgr;
	return match_mgr;
}

bool GMatchMgr::ChooseMatch( GType::enMatchMode match_mode )
{
	assert(match_mode_);
	if ( match_mode_->GetMatchMode() == match_mode )
		//�Ѿ���ͬһ����ģʽ��
	{
		return true;
	}
	else
	{
		auto runtime_match = FindRuntimeClass(match_mode);
		if ( !runtime_match )
		{
			//��֧��ָ���ı���ģʽ
			return false;		
		}

		match_mode_ = P_CAST<IMatchMode*>(runtime_match->CreateObject());
		if ( !match_mode_ )
		{
			//��������ģʽ����ʧ��
			SafeDelete();
			return false;
		}

		match_mode_->SetParent(this);
		//�������ı���ģʽ
		//match_mode_->PressSpecifyMatchMode(nullptr);
		return true;
	}
	
	assert(!"����ִ�е�����");
}

bool GMatchMgr::IsSupportMatchMode( GType::enMatchMode match_mode )
{
	return !!FindRuntimeClass(match_mode);
}

GType::enMatchMode GMatchMgr::GetCurMatchMode() const
{
	assert(match_mode_);
	return match_mode_->GetMatchMode();
}

void GMatchMgr::SafeDelete()
{
	if ( match_mode_ != &match_mode_invalid_ )
	{
		SAFE_DELETE(match_mode_);
		assert(!match_mode_);
		match_mode_ = &match_mode_invalid_;
	}
}

GMatchMgr::~GMatchMgr()
{
	SafeDelete();
}

IMatchMode* GMatchMgr::MatchMode() const
{
	assert(match_mode_);
	return match_mode_;
}

void GMatchMgr::PressFriendshipMatch( IoTimer* timer )
{
	if (IsReadyAtSelectedScene())
	{
		auto func_obj_normal = FuncObj_NormalC::GetInstance();
		if ( !func_obj_normal )
			return;
		func_obj_normal->GetGLua().LuaObjCall<void>("HandlePressFriendshipMatch");

		if (IsReadyAtSelectedScene())
		{
			if (timer)
				timer->Continue();
			else
			{
				SetIoTimer(500, boost::bind(&GMatchMgr::PressFriendshipMatch,
					this, _1));
			}
		}
	}
}

void GMatchMgr::PressFriendshipMatch()
{
	PressFriendshipMatch(nullptr);
}

bool GMatchMgr::IsReadyAtSelectedScene()
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if (func_obj_normal)
	{
		return func_obj_normal->IsTrainerSelectedScene();
	}
	return false;
}

GType::stMatchInfo& GMatchMgr::GetMatchInfo()
{
	return match_info_;
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(MatchMode_Managers, CObject)

GType::enMatchMode MatchMode_Managers::GetMatchMode() const
{
	return GType::enMatchMode_Managers;
}

MatchMode_Managers::MatchMode_Managers()
{
	//ע��֧�ֵĶ���ģʽ
	//�������
	RegisterRuntimeClass(GType::enFightMode_Computer, GET_RUNTIME_CLASS(FightMode_Managers_Computer));
	//�������
	RegisterRuntimeClass(GType::enFightMode_Friend, GET_RUNTIME_CLASS(FightMode_Managers_Friend));
}

const char* MatchMode_Managers::GetLuaHandlePressMatchModeFuncName()
{
	return "HandlePressManagersMode";
}

void MatchMode_Managers::EnteredRoom()
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if (func_obj_normal)
	{
		func_obj_normal->SetGameState(GType::enGameState_Managers);
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "���뵽������ģʽ�ķ�����";
	}
}

const char* MatchMode_Managers::GetLuaHandlePressBeginGameFuncName() const
{
	return "HandlePressRightBottomBt";
}

//////////////////////////////////////////////////////////////////////////

IFightMode::~IFightMode()
{

}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(FightMode_Invalid, CObject)
GType::enFightMode FightMode_Invalid::GetFightMode() const
{
	return GType::enFightMode_Invalid;
}

void FightMode_Invalid::EnterWaiting()
{
	LOG_ENTER_FUNC;
	LOG_O(Log_error) << "����ģʽ��Ч";
}

void FightMode_Invalid::EnterChoosePlayer()
{
	LOG_ENTER_FUNC;
	LOG_O(Log_error) << "����ģʽ��Ч";
}

void FightMode_Invalid::EnterMatchReady()
{
	LOG_ENTER_FUNC;
	LOG_O(Log_error) << "����ģʽ��Ч";
}

void FightMode_Invalid::PressSpecifyFightMode( IoTimer* timer )
{
	LOG_ENTER_FUNC;
	LOG_O(Log_error) << "����ģʽ��Ч";
}

void FightMode_Invalid::BeginMatch()
{
	LOG_ENTER_FUNC;
	LOG_O(Log_error) << "����ģʽ��Ч";
}

bool FightMode_Invalid::CanPressChoosePlayer_Begin() const
{
	return false;
}

bool FightMode_Invalid::CanPressReady_Begin() const
{
	return false;
}

void FightMode_Invalid::MatchEnd()
{
	LOG_ENTER_FUNC;
	LOG_O(Log_error) << "����ģʽ��Ч";
}

void FightMode_Invalid::MatchEnd_Prize()
{
	LOG_ENTER_FUNC;
	LOG_O(Log_error) << "����ģʽ��Ч";
}

void FightMode_Invalid::MatchEnd_Back()
{
	LOG_ENTER_FUNC;
	LOG_O(Log_error) << "����ģʽ��Ч";
}

//////////////////////////////////////////////////////////////////////////
bool MatchModeImpl::IsSupportFightMode( GType::enFightMode fight_mode ) const
{
	return !!FindRuntimeClass(fight_mode);
}

bool MatchModeImpl::ChooseFightMode( GType::enFightMode fight_mode )
{
	assert(fight_mode_);
	if ( fight_mode_->GetFightMode() == fight_mode )
	{
		return true;
	}
	else
	{
		auto runtime_fight = FindRuntimeClass(fight_mode);
		if ( !runtime_fight )
		{
			//��֧��ָ���Ķ���ģʽ
			return false;		
		}

		fight_mode_ = P_CAST<FightModeImpl*>(runtime_fight->CreateObject());
		if ( !fight_mode_ )
		{
			//��������ģʽ����ʧ��
			SafeDelte();
			return false;
		}

		fight_mode_->SetParent(this);
		//�������Ķ���ģʽ
		//fight_mode_->PressSpecifyFightMode(nullptr);
		return true;
	}

	assert(!"����ִ�е�����");
}

IFightMode* MatchModeImpl::FightMode() const
{
	assert(fight_mode_);
	return fight_mode_;
}

MatchModeImpl::MatchModeImpl()
{
	fight_mode_ = &fight_mode_invalid_;
	parent_ = nullptr;
	fight_mode_invalid_.SetParent(this);
}

MatchModeImpl::~MatchModeImpl()
{
	SafeDelte();
}

void MatchModeImpl::SafeDelte()
{
	if ( fight_mode_ != &fight_mode_invalid_ )
	{
		SAFE_DELETE(fight_mode_);
		assert(!fight_mode_);
		fight_mode_ = &fight_mode_invalid_;
	}
}

void MatchModeImpl::PressSpecifyMatchMode( IoTimer* timer )
{
	if (IsCanPressMatchMode())
	{
		auto func_obj_normal = FuncObj_NormalC::GetInstance();
		if ( !func_obj_normal )
			return;
		func_obj_normal->GetGLua().LuaObjCall<void>(GetLuaHandlePressMatchModeFuncName());

		if (IsCanPressMatchMode())
		{
			if (timer)
				timer->Continue();
			else
			{
				SetIoTimer(500, boost::bind(&MatchModeImpl::PressSpecifyMatchMode,
					this, _1));
			}
		}
	}
}

bool MatchModeImpl::IsCanPressMatchMode() const
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if (func_obj_normal)
	{
		return func_obj_normal->IsTrainerSelectedScene();
	}
	return false;
}

const char* MatchModeImpl::GetLuaHandlePressMatchModeFuncName()
{
	return "LuaDoNothing";
}

void MatchModeImpl::EnteredRoom()
{

}

IGMatchMgr* MatchModeImpl::GetParent() const
{
	assert(parent_);
	return parent_;
}

void MatchModeImpl::SetParent( IGMatchMgr* parent )
{
	assert(parent);
	assert(!parent_);
	parent_ = P_CAST<GMatchMgr*>(parent);
	assert(parent_);
}

const char* MatchModeImpl::GetLuaHandlePressBeginGameFuncName() const
{
	return "LuaDoNothing";
}

void MatchModeImpl::EnterWaitingImpl( IoTimer* timer )
{
	//�����Զ��ȴ�����˵���Ӧ�������뵽choose player״̬
	//����do nothing
}

void MatchModeImpl::EnterChoosePlayerImpl( IoTimer* timer )
{
	if (fight_mode_->CanPressChoosePlayer_Begin())
	{
		if ( !PressRightBottomBt() )
			return;

		if (fight_mode_->CanPressChoosePlayer_Begin())
		{
			if (timer)
				timer->Continue();
			else
			{
				SetIoTimer(1000, boost::bind(&MatchModeImpl::EnterChoosePlayerImpl,
					this, _1));
			}
		}
	}
}

void MatchModeImpl::EnterMatchReadyImpl( IoTimer* timer )
{
	if (fight_mode_->CanPressReady_Begin())
	{
		if ( !PressRightBottomBt() )
			return;

		if (fight_mode_->CanPressReady_Begin())
		{
			if (timer)
				timer->Continue();
			else
			{
				SetIoTimer(1000, boost::bind(&MatchModeImpl::EnterMatchReadyImpl,
					this, _1));
			}
		}
	}
}

GType::stMatchInfo& MatchModeImpl::GetMatchInfo()
{
	return parent_->GetMatchInfo();
}

void MatchModeImpl::MatchRoom_CloseContractDlg()
{
	ImplMatchRoomCloseContractDlg(nullptr);
}

bool MatchModeImpl::IsMatchRoomContractDlgClosed() const
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
		return false;
	const auto game_state = func_obj_normal->GetGameState();
	return game_state < GType::enGameState_Managers || game_state >= GType::enGameState_Match_Wait;
}

void MatchModeImpl::ImplMatchRoomCloseContractDlg( IoTimer* timer )
{
	if ( !IsMatchRoomContractDlgClosed() )
	{
		auto func_obj_normal = FuncObj_NormalC::GetInstance();
		if ( !func_obj_normal )
			return;

		func_obj_normal->GetGLua().LuaObjCall<void>("HandlePressDlg_Contract");
		func_obj_normal->GetGLua().LuaObjCall<void>("HandlePressDlg_DoneContract");

		if ( !IsMatchRoomContractDlgClosed() )
		{
			if (timer)
				timer->Continue();
			else
			{
				SetIoTimer(500, boost::bind(&MatchModeImpl::ImplMatchRoomCloseContractDlg,
					this, _1));
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(MatchModel_Invalid, CObject)
GType::enMatchMode MatchModel_Invalid::GetMatchMode() const
{
	return GType::enMatchMode_Invalid;
}

//////////////////////////////////////////////////////////////////////////
IMatchMode::~IMatchMode()
{

}
//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(MatchMode_Custom, CObject)
GType::enMatchMode MatchMode_Custom::GetMatchMode() const
{
	return GType::enMatchMode_Custom;
}

MatchMode_Custom::MatchMode_Custom()
{
	//ע��֧�ֵĶ���ģʽ
	//�������
	RegisterRuntimeClass(GType::enFightMode_Computer, GET_RUNTIME_CLASS(FightMode_Computer));
	//�������
	RegisterRuntimeClass(GType::enFightMode_Friend, GET_RUNTIME_CLASS(FightMode_Friend));
}

void MatchMode_Custom::EnteredRoom()
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if (func_obj_normal)
	{
		func_obj_normal->SetGameState(GType::enGameState_Custom);
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "���뵽�Զ���ģʽ�ķ�����";
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(FightMode_Computer, CObject)

GType::enFightMode FightMode_Computer::GetFightMode() const
{
	return GType::enFightMode_Computer;
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(FightMode_Friend, CObject)

GType::enFightMode FightMode_Friend::GetFightMode() const
{
	return GType::enFightMode_Friend;
}

//////////////////////////////////////////////////////////////////////////

bool FightModeImpl::IsCanPressFightMode() const
{
	return false;
}

const char* FightModeImpl::GetLuaHandlePressFightModeFuncName() const
{
	return "LuaDoNothing";
}

void FightModeImpl::PressSpecifyFightMode( IoTimer* timer )
{
	if (IsCanPressFightMode())
	{
		auto func_obj_normal = FuncObj_NormalC::GetInstance();
		if ( !func_obj_normal )
			return;
		func_obj_normal->GetGLua().LuaObjCall<void>(GetLuaHandlePressFightModeFuncName());

		if (IsCanPressFightMode())
		{
			if (timer)
				timer->Continue();
			else
			{
				SetIoTimer(1000, boost::bind(&FightModeImpl::PressSpecifyFightMode,
					this, _1));
			}
		}
	}
}

FightModeImpl::FightModeImpl()
{
	parent_ = nullptr;
	match_cnt_ = 0;
	time_match_begin_ = 0;
}

IMatchMode* FightModeImpl::GetParent() const
{
	assert(parent_);
	return parent_;
}

void FightModeImpl::SetParent( IMatchMode* parent )
{
	assert(!parent_);
	parent_ = P_CAST<MatchModeImpl*>(parent);
	assert(parent_);
}

void FightModeImpl::BeginMatch()
{
	//BeginGame(nullptr);
}

void FightModeImpl::BeginMatch( IoTimer* timer )
{
	if (IsCanBegin())
	{
		auto func_obj_normal = FuncObj_NormalC::GetInstance();
		if ( !func_obj_normal )
			return;
		func_obj_normal->GetGLua().LuaObjCall<void>(GetParent()->GetLuaHandlePressBeginGameFuncName());

		if (IsCanBegin())
		{
			if (timer)
				timer->Continue();
			else
			{
				SetIoTimer(1000, boost::bind(&FightModeImpl::BeginMatch,
					this, _1));
			}
		}
	}
}

bool FightModeImpl::IsCanBegin() const
{
	return false;
}

void FightModeImpl::EnterWaiting()
{
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "���뵽�ȴ������״̬";
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
	{
		LOG_O(Log_error) << "func_obj_normal��δ����";
		return;
	}
	func_obj_normal->SetGameState(GType::enGameState_Match_Wait);
	assert(parent_);
	parent_->EnterWaitingImpl();

	time_match_begin_ = time(nullptr);
	auto& the_timer = func_obj_normal->GetSetMatchTimer();
	the_timer.SetTimerStart(true);
	the_timer.RefreshCurTime();
	the_timer.IsTimeout();
	++match_cnt_;
}

void FightModeImpl::EnterChoosePlayer()
{
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "���뵽ѡ����Ա��״̬";
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
	{
		LOG_O(Log_error) << "func_obj_normal��δ����";
		return;
	}
	func_obj_normal->SetGameState(GType::enGameState_Match_Choose_Player);
	assert(parent_);
	//parent_->EnterChoosePlayerImpl();
}

void FightModeImpl::EnterMatchReady()
{
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "���뵽ѡ���������״̬";
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
	{
		LOG_O(Log_error) << "func_obj_normal��δ����";
		return;
	}
	func_obj_normal->SetGameState(GType::enGameState_Match_Ready);
	assert(parent_);
	//parent_->EnterMatchReadyImpl();
}

bool FightModeImpl::CanPressChoosePlayer_Begin() const
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
		return false;
	return GType::enGameState_Match_Choose_Player == func_obj_normal->GetGameState();
}

bool FightModeImpl::CanPressReady_Begin() const
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
		return false;
	return GType::enGameState_Match_Ready == func_obj_normal->GetGameState();
}

void FightModeImpl::EnterMatchAllReady()
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "func_obj_normal��δ����";
		return;
	}
	if ( GType::enGameState_Match_Ready != func_obj_normal->GetGameState() )
		return;
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "���뵽�����˶��Ѿ�����״̬";
	func_obj_normal->SetGameState(GType::enGameState_Match_BeginFirtAnimate);
}

void FightModeImpl::MatchEnd()
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "func_obj_normal��δ����";
		return;
	}

	//�������μ�һ
	/*GType::enPlayerPosition positions[] = {
		GType::enPlayerPosition_First, GType::enPlayerPosition_Second
	};
	auto players_iter = GPlayer::GetMe().CreatePlayerIterByPosition(positions, _countof(positions));
	if ( !players_iter )
	{
		assert(false);
		LOG_O(Log_error) << "����������Ȼ��ò����׷����油�ĵ�������";
		return;
	}
	for ( players_iter->First(); !players_iter->IsDone(); players_iter->Next() )
	{
		auto player = players_iter->CurItem();
		assert(player);
		if (player)
		{
			const auto player_life = player->GetLife();
			if ( player_life > 0 )
			{
				player->SetLife(player_life - 1);
			}
			else
			{
				assert(false);
				(void*)0;
			}
		}
	}*/

	if ( GType::enGameState_Match_BeginFirtAnimate > func_obj_normal->GetGameState() )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "��Ϸ״̬�жϲ�ͨ����" << func_obj_normal->GetGameState();
		return;
	}
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "���������ӣ����Ͼ�Ҫ�����������";
	func_obj_normal->SetGameState(GType::enGameState_MatchEnd);

	//PressMatchEnd_Result(nullptr);
	auto& the_timer = func_obj_normal->GetSetMatchTimer();
	the_timer.SetTimerStart(false);

	P_Exec_MatchInfo match_info;
	match_info.time_match_end = time(nullptr);
	match_info.time_match_begin = time_match_begin_;
	match_info.match_cnt = match_cnt_;
	func_obj_normal->UserMsg(P_Exec_MatchInfo::value, &match_info, sizeof(match_info));

	if (func_obj_normal)
	{
		func_obj_normal->GetSessionOper().ToCall(BC_MakeP("SetMatchCnt")<<match_cnt_);
		if ( match_cnt_ >= GPlayer::GetMe().GetMatchLimitCnt() )
		{
			LOG_O(Log_warning) << "���������Ѵ�����->" << match_cnt_;

			func_obj_normal->GetSessionOper().ToCall(BC_MakeP("MatchLimitCnt"));
		}
	}
}

void FightModeImpl::MatchEnd_Prize()
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "func_obj_normal��δ����";
		return;
	}
	if ( GType::enGameState_MatchEnd > func_obj_normal->GetGameState() )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "��Ϸ״̬�жϲ�ͨ����" << func_obj_normal->GetGameState();
		return;
	}
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "��������֮��������";
	func_obj_normal->SetGameState(GType::enGameState_MatchEnd_Prize);

	//PressMatchEnd_Prize(nullptr);
}

void FightModeImpl::MatchEnd_Back()
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "func_obj_normal��δ����";
		return;
	}
	if ( func_obj_normal->GetGameState() < GType::enGameState_MatchEnd )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "��Ϸ״̬�жϲ�ͨ����" << func_obj_normal->GetGameState();
		return;
	}
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "��������֮���ر�������";
	func_obj_normal->SetGameState(GType::enGameState_MatchEnd_Back);
}

bool FightModeImpl::CanPressMatchEnd_Prize() const
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
		return false;
	return GType::enGameState_MatchEnd_Prize == func_obj_normal->GetGameState();
}

void FightModeImpl::PressMatchEnd_Prize( IoTimer* timer )
{
	if (CanPressMatchEnd_Prize())
	{
		auto func_obj_normal = FuncObj_NormalC::GetInstance();
		if ( !func_obj_normal )
			return;
		if ( !PressRightBottomBt() )
			return;

		if (CanPressMatchEnd_Prize())
		{
			if (timer)
				timer->Continue();
			else
			{
				SetIoTimer(1000, boost::bind(&FightModeImpl::PressMatchEnd_Prize,
					this, _1));
			}
		}
	}
}

bool FightModeImpl::CanPressMatchEnd_Result() const
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
		return false;
	return GType::enGameState_MatchEnd == func_obj_normal->GetGameState();
}

void FightModeImpl::PressMatchEnd_Result( IoTimer* timer )
{
	if (CanPressMatchEnd_Result())
	{
		auto func_obj_normal = FuncObj_NormalC::GetInstance();
		if ( !func_obj_normal )
			return;
		if ( !PressRightBottomBt() )
			return;

		if (CanPressMatchEnd_Result())
		{
			if (timer)
				timer->Continue();
			else
			{
				SetIoTimer(1000, boost::bind(&FightModeImpl::PressMatchEnd_Result,
					this, _1));
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(FightMode_Managers_Computer, CObject)

bool FightMode_Managers_Computer::IsCanPressFightMode() const
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
		return false;
	
	const auto kGameState = func_obj_normal->GetGameState();
	if ( kGameState < GType::enGameState_Managers )
		return false;
	return kGameState != GType::enGameState_Managers_Computer;
}

const char* FightMode_Managers_Computer::GetLuaHandlePressFightModeFuncName() const
{
	assert(false);
	return "HandlePressMangers_Computer";
}

bool FightMode_Managers_Computer::IsCanBegin() const
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
		return false;

	return GType::enGameState_Managers_Computer == func_obj_normal->GetGameState();
}

void FightMode_Managers_Computer::BeginMatch()
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if (func_obj_normal)
		func_obj_normal->SetGameState(GType::enGameState_Managers_Computer);
	__super::BeginMatch();
}

//////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(FightMode_Managers_Friend, CObject)

bool FightMode_Managers_Friend::IsCanPressFightMode() const
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
		return false;

	const auto kGameState = func_obj_normal->GetGameState();
	if ( kGameState < GType::enGameState_Managers )
		return false;
	return kGameState != GType::enGameState_Managers_Friend;
}

const char* FightMode_Managers_Friend::GetLuaHandlePressFightModeFuncName() const
{
	return "HandlePressMangers_Friend";
}

bool FightMode_Managers_Friend::IsCanBegin() const
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
		return false;

	return GType::enGameState_Managers_Friend == func_obj_normal->GetGameState();
}

void FightMode_Managers_Friend::BeginMatch()
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if (func_obj_normal)
		func_obj_normal->SetGameState(GType::enGameState_Managers_Friend);
	__super::BeginMatch();
}

//////////////////////////////////////////////////////////////////////////
