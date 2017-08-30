#pragma once
/*
@author zhp
@date 2014/5/11 13:49
@purpose for test, players info
*/
#include "stdafx.h"
#include "Facility/GPlayer.h"
#include <Common/UsefulClass.h>
#include <Common/UiCtrls.h>

//��Ա�б�
enum enListPlayers_SubItems{
	kLPSI_Id = 0,			//��ԱID
	kLPSI_PlayerName,		//��Ա��
	kLPSI_Grade,			//��Ա�ȼ�
	kLPSI_Price,			//��Ա��ֵ
	kLPSI_Life,				//ʣ�ೡ��
	kLPSI_Pos,				//��Աְλ
	kLPSI_Spid,				//��Աspid
};
//��Ʒ�б�
enum enListItems_SubItems{
	kLISI_Id = 0,			//��Ʒid
	//kLISI_ItemId,			//��Ʒitem_id
	kLISI_Remains,			//��Ʒ����
	kLISI_Expired,			//�Ƿ���
};

//��Ա��Ϣ
class PlayerInfoS : public GPlayer::stPlayer{
public:
	bool ParseFromJsonObj( const Json::Value& player_obj );

public:
	std::string				name_;
};

//��Ʒ��Ϣ
class ItemInfoS : public GPlayer::stItem{
public:
	bool ParseFromJsonObj( const Json::Value& item_obj );
};

class CList_Players : public CListCtrlStyled{
protected:
	virtual void PreSubclassWindow();
};

class CList_PlayersSingle : public CList_Players{
public:
	//���һ����Ա
	void AddPlayer( const PlayerInfoS& player );
};

class CList_Items : public CListCtrlStyled{
protected:
	virtual void PreSubclassWindow();
};

class CList_ItemsSingle : public CList_Items{
public:
	//���һ����Ʒ��Ϣ
	void AddItemInfo( const ItemInfoS& item_info );
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
	struct stSelfOfferItem : public GPlayer::stSelfOfferItem{
		bool ParseFromJsonObj( const Json::Value& sold_player );
	};

public:
	void AddOfferItem( const stSelfOfferItem& offer_item );

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
	struct stOtherOfferItem : public GPlayer::stOfferItem{
		bool ParseFromJsonObj( const Json::Value& sold_player );
	};

public:
	void AddOfferItem( const stOtherOfferItem& offer_item );

protected:
	virtual void PreSubclassWindow();
};