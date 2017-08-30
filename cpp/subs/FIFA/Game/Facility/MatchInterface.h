#pragma once
/*
@author zhp
@date 2014-3-1 20:33
@purpose for match facility interface
*/
#include "stdafx.h"
#include "GTypes.h"
#include "Net/IoTimer.h"

class IMatchMode;
//fight mode interface
class IFightMode : public CObject{
public:
	virtual ~IFightMode();
	//�õ�����ģʽ
	virtual GType::enFightMode GetFightMode() const = 0;
	//�������Ķ���ģʽ
	virtual void PressSpecifyFightMode( IoTimer* timer ) = 0;
	//get parent
	virtual IMatchMode* GetParent() const = 0;
	//set parent
	virtual void SetParent( IMatchMode* parent ) = 0;
	//��ʼ����
	virtual void BeginMatch() = 0;
	//�����˵ȴ�״̬
	virtual void EnterWaiting() = 0;
	//������ѡ����Ա
	virtual void EnterChoosePlayer() = 0;
	//�����˱�������״̬
	virtual void EnterMatchReady() = 0;
	//�����˶��Ѿ���������ʼ�����Ķ���״̬
	virtual void EnterMatchAllReady() = 0;
	//��������
	virtual void MatchEnd() = 0;
	//��������֮��������
	virtual void MatchEnd_Prize() = 0;
	//��������֮���ر�������
	virtual void MatchEnd_Back() = 0;
};

class IGMatchMgr;
//match mode interface
class IMatchMode : public CObject{
public:
	virtual ~IMatchMode();
	//�����Ƿ�֧��ָ���Ķ���ģʽ
	virtual bool IsSupportFightMode( GType::enFightMode fight_mode ) const = 0;
	//ѡ��ָ���Ķ���ģʽ
	virtual bool ChooseFightMode( GType::enFightMode fight_mode ) = 0;
	//�õ�����ģʽ
	virtual GType::enMatchMode GetMatchMode() const = 0;
	//�õ���ǰ��սģʽ
	virtual IFightMode* FightMode() const = 0;
	//��ȫ�ͷ�
	virtual void SafeDelte() = 0;
	//�������ı���ģʽ
	virtual void PressSpecifyMatchMode( IoTimer* timer ) = 0;
	//�Ѿ����뷿����
	virtual void EnteredRoom() = 0;
	//get parent
	virtual IGMatchMgr* GetParent() const = 0;
	//set parent
	virtual void SetParent( IGMatchMgr* parent ) = 0;
	//lua�д�������ʼ����ģʽ�ĺ�����
	virtual const char* GetLuaHandlePressBeginGameFuncName() const = 0;
	//�õ�match info
	virtual GType::stMatchInfo& GetMatchInfo() = 0;
	//�رձ�������֮��Լ�Ի���
	virtual void MatchRoom_CloseContractDlg() = 0;
};

//interface game manager
class IGMatchMgr{
public:
	static IGMatchMgr& GetMe();
	virtual ~IGMatchMgr();
	//�Ƿ�֧��ָ���ı���ģʽ
	virtual bool IsSupportMatchMode( GType::enMatchMode match_mode ) = 0;
	//ѡ�����ģʽ�����ģʽ
	virtual bool ChooseMatch( GType::enMatchMode match_mode ) = 0;
	//�õ���ǰ����ģʽ
	virtual GType::enMatchMode GetCurMatchMode() const = 0;
	//��ȫ�ͷ�
	virtual void SafeDelete() = 0;
	//�õ�����ģʽ����
	virtual IMatchMode* MatchMode() const = 0;
	//���������
	virtual void PressFriendshipMatch() = 0;
	//�õ�������Ϣ
	virtual GType::stMatchInfo& GetMatchInfo() = 0;
};