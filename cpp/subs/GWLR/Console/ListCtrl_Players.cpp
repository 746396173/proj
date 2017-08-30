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

	const auto kColumnWidth = 175;
	InsertColumn(kItemName, _T("��Ʒ"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kItemCnt, _T("��Ʒ����"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kSeller, _T("������"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kPriceBegin, _T("���ļ�"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kPriceSmart, _T("һ�ڼ�"), LVCFMT_LEFT, kColumnWidth);
	InsertColumn(kPriceJingPai, _T("���ļ�"), LVCFMT_LEFT, kColumnWidth);
}

void CListCtrlStyled::AddOfferItem( const stAuctionItemInfoEx& offer_item )
{
	const auto kItemMax = GetItemCount();
	InsertItem(kItemMax, CA2CT(offer_item.item_name_.c_str()));
	
	CString str_tmp;
	str_tmp.Format(_T("%d"), offer_item.item_cnt_);
	SetItemText(kItemMax, kItemCnt, str_tmp);	
	SetItemText(kItemMax, kSeller, CA2CT(offer_item.req_item_by_player_name_.c_str()));
	str_tmp.Format(_T("%d"), offer_item.begin_price_);
	SetItemText(kItemMax, kPriceBegin, str_tmp);
	str_tmp.Format(_T("%d"), offer_item.smart_price_);
	SetItemText(kItemMax, kPriceSmart, str_tmp);
	str_tmp.Format(_T("%d"), offer_item.jing_pai_price_);
	SetItemText(kItemMax, kPriceJingPai, str_tmp);
}
