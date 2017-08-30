#pragma once
/*
@author zhp
@date 2014/5/11 13:49
@purpose for test, players info
*/
#include "stdafx.h"
#include <Common/UsefulClass.h>

class CListCtrlStyled : public CListCtrl{
protected:
	virtual void PreSubclassWindow();
};

//�ҵĳ����б�
class CList_MyOfferList : public CListCtrlStyled, public Singleton<CList_MyOfferList, Singleton_Instance>{
	//type definitions
public:
	enum enColumns{
		kPrice = 0,			//��Ǯ
#ifdef _DEBUG
		kPlayerId,
		kId,
		kSpid,
#endif
		kSoldState,					
		kIssuedAt,			//����ʱ��
		kGrade,				//ǿ���ȼ�
	};

protected:
	virtual void PreSubclassWindow();
};

//�����ŵĳ�����
class CList_OtherOffers : public CListCtrlStyled, public Singleton<CList_OtherOffers, Singleton_Instance>{
	//type definitions
public:
	enum enColumns{
		kPrice = 0,			//��Ǯ
#ifdef _DEBUG
		kId,
		kSpid,
#endif
		kIssuedAt,			//����ʱ��
		kGrade,				//ǿ���ȼ�
	};

protected:
	virtual void PreSubclassWindow();
};