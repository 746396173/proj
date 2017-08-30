#include "stdafx.h"
#include "ListCtrls.h"
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeFormat.h>

void ListCtrl_CardInfo::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	const auto kColumnWidth = 140;
	InsertColumn(kCardId, _T("����"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kCardPwd, _T("����"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kCardDays, _T("������"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kUseTime, _T("ʹ��ʱ��"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kAddTime, _T("���ʱ��"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kIsUsed, _T("�Ƿ�ʹ����"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kUserName, _T("ʹ����"), LVCFMT_LEFT, kColumnWidth);
}

void ListCtrl_CardInfo::AddCardInfo(const stData_Card& card_info)
{
	const auto kItemMax = GetItemCount();
	
	InsertItem(kItemMax, CA2CT(card_info.card_id_.c_str()));
	SetItemText(kItemMax, kCardPwd, CA2CT(card_info.card_pwd_.c_str()));
	CString str_tmp;
	str_tmp.Format(_T("%d"), card_info.card_minutes_);
	SetItemText(kItemMax, kCardDays, str_tmp);

	using namespace Poco;
	std::string str_time;
	str_time = DateTimeFormatter::format(card_info.use_time_, DateTimeFormat::SORTABLE_FORMAT);
	SetItemText(kItemMax, kUseTime, CA2CT(str_time.c_str()));
	str_time = DateTimeFormatter::format(card_info.add_time_, DateTimeFormat::SORTABLE_FORMAT);
	SetItemText(kItemMax, kAddTime, CA2CT(str_time.c_str()));
	if (card_info.is_used_)
		str_tmp = _T("��");
	else
		str_tmp = _T("��");
	SetItemText(kItemMax, kIsUsed, str_tmp);
	SetItemText(kItemMax, kUserName, CA2CT(card_info.user_name_.c_str()));
}

void ListCtrl_AcInfo::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	const auto kColumnWidth = 100;
	InsertColumn(kUserName, _T("�ʺ�"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kUserPwd, _T("����"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kIsBindMachine, _T("�Ƿ���˻���"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kLastLoginTime, _T("�ϴε�½ʱ��"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kLastPayTime, _T("�ϴγ�ֵʱ��"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kLastLoginIp, _T("�ϴε�½IP"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kRegTime, _T("ע��ʱ��"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kEndDayTime, _T("����ʱ��"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kQQ, _T("QQ"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kRegIp, _T("ע��ʱ��IP"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kAcState, _T("�ʺ�״̬"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kBanEndTime, _T("��ŵ���ʱ��"), LVCFMT_LEFT, kColumnWidth);
}

void ListCtrl_AcInfo::AddAcInfo(const stData_Account& ac_info)
{
	const auto kItemMax = GetItemCount();

	InsertItem(kItemMax, CA2CT(ac_info.user_name_.c_str()));
	SetItemText(kItemMax, kUserPwd, CA2CT(ac_info.user_pwd_.c_str()));
	CString str_tmp;
	if (ac_info.machine_code_.empty())
		str_tmp = _T("��");
	else
		str_tmp = _T("��");
	SetItemText(kItemMax, kIsBindMachine, str_tmp);
	using namespace Poco;
	std::string str_time;
	str_time = DateTimeFormatter::format(ac_info.last_login_time_, DateTimeFormat::SORTABLE_FORMAT);
	SetItemText(kItemMax, kLastLoginTime, CA2CT(str_time.c_str()));
	str_time = DateTimeFormatter::format(ac_info.last_pay_time_, DateTimeFormat::SORTABLE_FORMAT);
	SetItemText(kItemMax, kLastPayTime, CA2CT(str_time.c_str()));
	SetItemText(kItemMax, kLastLoginIp, CA2CT(ac_info.last_login_ip_.c_str()));
	str_time = DateTimeFormatter::format(ac_info.reg_time_, DateTimeFormat::SORTABLE_FORMAT);
	SetItemText(kItemMax, kRegTime, CA2CT(str_time.c_str()));
	str_time = DateTimeFormatter::format(ac_info.end_day_time_, DateTimeFormat::SORTABLE_FORMAT);
	SetItemText(kItemMax, kEndDayTime, CA2CT(str_time.c_str()));
	SetItemText(kItemMax, kQQ, CA2CT(ac_info.qq_.c_str()));
	SetItemText(kItemMax, kRegIp, CA2CT(ac_info.reg_ip_.c_str()));
}

void ListCtrl_AcInfo::AddAcStateInfo(const stData_AcState& ac_state)
{
	using namespace Poco;
	auto item_max = GetItemCount();
	CString str;
	std::string ac, str_time;
	for (int i = 0; i != item_max;++i)
	{
		str = GetItemText(i, kUserName);
		ac = CT2CA(str);
		if (ac == ac_state.user_name_)
		{
			assert(enAcState::kAS_Normal != ac_state.state_);
			if (enAcState::kAS_Freeze == ac_state.state_)
				SetItemText(i, kAcState, _T("����"));
			else if (enAcState::kAS_Ban == ac_state.state_)
			{
				SetItemText(i, kAcState, _T("���"));
				auto end_time = ac_state.begin_time_ + Poco::Timespan(0, 0, ac_state.period_, 0, 0);
				str_time = DateTimeFormatter::format(end_time, DateTimeFormat::SORTABLE_FORMAT);
				SetItemText(i, kBanEndTime, CA2CT(str_time.c_str()));
			}
		}
	}
}
