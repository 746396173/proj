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