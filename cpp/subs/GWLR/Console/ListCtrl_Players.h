#pragma once
/*
@author zhp
@date 2014/5/11 13:49
@purpose for test, players info
*/
#include "stdafx.h"
#include <Common/UsefulClass.h>
#include <Communicate/CG_Defines.h>

class CListCtrlStyled : public CListCtrl{
public:
	enum enColumns{
		kItemName = 0,
		kItemCnt,
		kSeller,
		kPriceBegin,
		kPriceSmart,				
		kPriceJingPai,
	};
	void AddOfferItem( const stAuctionItemInfoEx& offer_item );

protected:
	virtual void PreSubclassWindow();
};

//�ҵĳ����б�
class CList_MyOfferList : public CListCtrlStyled, public Singleton<CList_MyOfferList, Singleton_Instance>{
	//type definitions
public:
};

//�����ŵĳ�����
class CList_OtherOffers : public CListCtrlStyled, public Singleton<CList_OtherOffers, Singleton_Instance>{
	//type definitions
public:
};