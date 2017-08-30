#include "stdafx.h"
#include "ListCtrl_Players.h"

void CListCtrlStyled::PreSubclassWindow()
{
	__super::PreSubclassWindow();
	//style
	{
		DWORD dwStyle = GetExtendedStyle();
		dwStyle |= LVS_EX_FULLROWSELECT;		//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
		dwStyle |= LVS_EX_GRIDLINES;			//�����ߣ�ֻ������report����listctrl��
		dwStyle |= LVS_EX_CHECKBOXES;			//itemǰ����checkbox�ؼ�
		SetExtendedStyle(dwStyle);				//������չ���
	}
}
void CList_MyOfferList::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	const auto kColumnWidth = 175;
	InsertColumn(kPrice, _T("��Ǯ"), LVCFMT_LEFT, kColumnWidth);
#ifdef _DEBUG
	InsertColumn(kPlayerId, _T("��ԱID"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kId, _T("������ID"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kSpid, _T("spid"), LVCFMT_LEFT, kColumnWidth);
#endif
	InsertColumn(kSoldState, _T("����״̬"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kIssuedAt, _T("����ʱ��"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kGrade, _T("ǿ���ȼ�"), LVCFMT_LEFT, kColumnWidth);
}

void CList_OtherOffers::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	const auto kColumnWidth = 225;
	InsertColumn(kPrice, _T("��Ǯ"), LVCFMT_LEFT, kColumnWidth);
#ifdef _DEBUG
	InsertColumn(kId, _T("������ID"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kSpid, _T("spid"), LVCFMT_LEFT, kColumnWidth);
#endif
	InsertColumn(kIssuedAt, _T("����ʱ��"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kGrade, _T("ǿ���ȼ�"), LVCFMT_LEFT, kColumnWidth);
}

void CList_Skills::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	const auto kColumnWidth = 225;
	InsertColumn(kSkillName, _T("����"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kSkillLvl, _T("�ȼ�"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kSkillId, _T("id"), LVCFMT_LEFT, kColumnWidth);
}

void CList_Skills::AddSkillInfo( const stSkillInfo& skill_info )
{
	const auto kItemMax = GetItemCount();
	InsertItem(kItemMax, CW2CT(skill_info.skill_name_.c_str()));
	CString str_tmp;
	str_tmp.Format(_T("%u"), skill_info.skill_lvl_);
	SetItemText(kItemMax, kSkillLvl, str_tmp);
	str_tmp.Format(_T("%u"), skill_info.skill_id_);
	SetItemText(kItemMax, kSkillId, str_tmp);
}

void CList_GameObjs::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	const auto kColumnWidth = 150;
	InsertColumn(kObjType, _T("����"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kSerial, _T("���"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kJobName, _T("ְҵ��"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kObjName, _T("������"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kObjTypeNameInGame, _T("��Ϸ������"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kCurHp, _T("HP"), LVCFMT_LEFT, kColumnWidth);
}

void CList_GameObjs::AddGameObjInfo( const stGameObjInfo& gameobj_info )
{
	const auto kItemMax = GetItemCount();
	CString str_tmp;
	switch (gameobj_info.obj_type_)
	{
	case kGOT_Invalid:
		str_tmp = _T("��Ч");
		break;
	case kGOT_MISC:
		str_tmp = _T("MISC");
		break;
	case kGOT_Npc:
		str_tmp = _T("NPC");
		break;
	case kGOT_Player:
		str_tmp = _T("���");
		break;
	case kGOT_Unknown:
		str_tmp = _T("������Ʒ");
		break;
	case kGOT_Monster:
		str_tmp = _T("����");
		break;
	case kGOT_ParseObjType:
		str_tmp = _T("���ڽ���");
		break;
	default:
		str_tmp = _T("δ֪");
		break;
	}
	InsertItem(kItemMax, str_tmp);
	str_tmp.Format(_T("%u"), gameobj_info.obj_serial_);
	SetItemText(kItemMax, kSerial, str_tmp);
	SetItemText(kItemMax, kJobName, CW2CT(gameobj_info.obj_job_name_.c_str()));
	SetItemText(kItemMax, kObjName, CW2CT(gameobj_info.obj_name_.c_str()));
	SetItemText(kItemMax, kObjTypeNameInGame, CW2CT(gameobj_info.game_obj_type_name_.c_str()));
	str_tmp.Format(_T("%u"), gameobj_info.cur_hp_);
	SetItemText(kItemMax, kCurHp, str_tmp);
}

CList_GameObjs::stGameObjInfo::stGameObjInfo() : GameObjBase(kGOT_Invalid)
{

}

void CList_Items::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	const auto kColumnWidth = 125;
	InsertColumn(kItemName, _T("����"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kItemQuality, _T("Ʒ��"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kItemDurable, _T("�;ö�"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kItemCnt, _T("����"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kIsSeal, _T("�Ƿ��ӡ"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kNeedIdentification, _T("��Ҫ����"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kTabCategory, _T("table"), LVCFMT_LEFT, kColumnWidth);
}

void CList_Items::AddItem( const stItem& gitem, GType::enTabCategory tab_category )
{
	/*
	const auto kItemMax = GetItemCount();
	InsertItem(kItemMax, CW2CT(gitem.item_id_.c_str()));
	CString str_tmp;
	str_tmp.Format(_T("%u"), gitem.item_quality_);
	SetItemText(kItemMax, kItemQuality, str_tmp);
	str_tmp.Format(_T("%u"), gitem.item_durable_);
	SetItemText(kItemMax, kItemDurable, str_tmp);
	str_tmp.Format(_T("%u"), gitem.item_cnt_);
	SetItemText(kItemMax, kItemCnt, str_tmp);
	if (gitem.is_sealed_)
		str_tmp = _T("��");
	else
		str_tmp = _T("��");
	SetItemText(kItemMax, kIsSeal, str_tmp);
	if (gitem.unidentified_)
		str_tmp = _T("��");
	else
		str_tmp = _T("��");
	SetItemText(kItemMax, kNeedIdentification, str_tmp);
	str_tmp.Format(_T("%u"), gitem.game_item_addr_);
	SetItemText(kItemMax, kTabCategory, str_tmp);
	*/
}

void CList_Room::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	const auto kColumnWidth = 150;
	InsertColumn(kRoomName, _T("��������"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kRoomId, _T("����ID"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kDoorName, _T("������"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kDoorPos, _T("������"), LVCFMT_LEFT, kColumnWidth);
}

void CList_Room::SetRoomInfo( const stRoomInfo& room_info )
{
	/*const auto kItemMax = GetItemCount();
	InsertItem(kItemMax, CW2CT(room_info.room_name_.c_str()));
	SetItemText(kItemMax, kRoomId, CW2CT(room_info.room_id_.c_str()));
	for ( auto i = 0; i != _countof(room_info.doors_); ++i )
	{
		AddDoorInfo(*(stDoorInfo*)&room_info.doors_[i]);
	}*/
}

void CList_Room::AddDoorInfo( const stDoorInfo& door_info )
{
	/*const auto kItemMax = GetItemCount();
	InsertItem(kItemMax, _T(""));
	SetItemText(kItemMax, kDoorName, CW2CT(door_info.door_name_.c_str()));
	CString str_tmp;
	str_tmp.Format(_T("%f,%f,%f"), door_info.door_pos_.x_, door_info.door_pos_.y_, door_info.door_pos_.z_);
	SetItemText(kItemMax, kDoorPos, str_tmp);*/
}

void CList_Task::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	/*const auto kColumnWidth = 125;
	InsertColumn(kItemName, _T("����"), LVCFMT_LEFT, kColumnWidth);*/
}
