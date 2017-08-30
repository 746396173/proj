#pragma once
/*
@author zhp
@date 2014-3-1 16:49
@purpose for match
*/
#include "MatchInterface.h"
#include "Common/UsefulClass.h"

class MatchModeImpl;
//һ���Ե�ʵ��
class FightModeImpl : public IFightMode{
protected:
	FightModeImpl();

public:
	virtual void PressSpecifyFightMode( IoTimer* timer );
	virtual IMatchMode* GetParent() const;
	virtual void SetParent( IMatchMode* parent );
	virtual void BeginMatch();
	virtual void EnterWaiting();
	virtual void EnterChoosePlayer();
	virtual void EnterMatchReady();
	virtual void EnterMatchAllReady();
	virtual void MatchEnd();
	virtual void MatchEnd_Prize();
	virtual void MatchEnd_Back();

public:
	//�Ƿ���Ե��ѡ����Ա֮��ʼ
	virtual bool CanPressChoosePlayer_Begin() const;
	//�Ƿ���Ե������֮��ʼ
	virtual bool CanPressReady_Begin() const;

protected:
	//�Ƿ���Ե��ѡ�����ģʽ��
	virtual bool IsCanPressFightMode() const;
	//lua�д������������ģʽ�ĺ�����
	virtual const char* GetLuaHandlePressFightModeFuncName() const;
	//�Ƿ���Կ�ʼ������
	virtual bool IsCanBegin() const;
	//��ʼ����
	void BeginMatch( IoTimer* timer );
	//�Ƿ���Ե����������֮�������
	bool CanPressMatchEnd_Result() const;
	//�����������֮�������
	void PressMatchEnd_Result( IoTimer* timer );
	//�Ƿ���Ե����������֮��������
	bool CanPressMatchEnd_Prize() const;
	//�����������֮��������
	void PressMatchEnd_Prize( IoTimer* timer );

protected:
	MatchModeImpl*				parent_;
	int							match_cnt_;					//��������
	time_t						time_match_begin_;			//��ʼ����ʱ��
};

//fight mode invalid
class FightMode_Invalid : public FightModeImpl{
public:
	virtual GType::enFightMode GetFightMode() const;
	virtual void PressSpecifyFightMode( IoTimer* timer );
	virtual void BeginMatch();
	virtual void EnterWaiting();
	virtual void EnterChoosePlayer();
	virtual void EnterMatchReady();
	virtual bool CanPressChoosePlayer_Begin() const;
	virtual bool CanPressReady_Begin() const;
	virtual void MatchEnd();
	virtual void MatchEnd_Prize();
	virtual void MatchEnd_Back();

	DECLARE_DYNCREATE(FightMode_Invalid)
};

class GMatchMgr;
//һ���Ե�ʵ��
class MatchModeImpl : public IMatchMode, public RuntimeClassReg{
protected:
	MatchModeImpl();
	~MatchModeImpl();

public:
	virtual bool IsSupportFightMode( GType::enFightMode fight_mode ) const;
	virtual bool ChooseFightMode( GType::enFightMode fight_mode );
	virtual IFightMode* FightMode() const;
	virtual void SafeDelte();
	virtual void PressSpecifyMatchMode( IoTimer* timer );
	virtual void EnteredRoom();
	virtual IGMatchMgr* GetParent() const;
	virtual void SetParent( IGMatchMgr* parent );
	virtual const char* GetLuaHandlePressBeginGameFuncName() const;
	virtual GType::stMatchInfo& GetMatchInfo();
	virtual void MatchRoom_CloseContractDlg();

public:
	void EnterWaitingImpl( IoTimer* timer = nullptr );
	void EnterChoosePlayerImpl( IoTimer* timer = nullptr );
	void EnterMatchReadyImpl( IoTimer* timer = nullptr );

protected:	
	//�Ƿ���Ե��ѡ�����ģʽ��
	bool IsCanPressMatchMode() const;
	//lua�д������������ģʽ�ĺ�����
	virtual const char* GetLuaHandlePressMatchModeFuncName();
	//��������֮��Լ�Ի����Ƿ�ر���
	bool IsMatchRoomContractDlgClosed() const;
	//ִ�б�������֮�ر���Լ�Ի���
	void ImplMatchRoomCloseContractDlg( IoTimer* timer );
	
protected:
	FightModeImpl*				fight_mode_;
	GMatchMgr*					parent_;

private:
	FightMode_Invalid			fight_mode_invalid_;
};

//match model invalid
class MatchModel_Invalid : public MatchModeImpl{
public:
	virtual GType::enMatchMode GetMatchMode() const;

	DECLARE_DYNCREATE(MatchModel_Invalid)
};

//game match manage
class GMatchMgr : public IGMatchMgr, public RuntimeClassReg{
	GMatchMgr();
	friend IGMatchMgr& IGMatchMgr::GetMe();

public:
	~GMatchMgr();

public:
	//�Ƿ�֧��ָ���ı���ģʽ
	virtual bool IsSupportMatchMode( GType::enMatchMode match_mode );
	//ѡ�����ģʽ�����ģʽ
	virtual bool ChooseMatch( GType::enMatchMode match_mode );
	//�õ���ǰ����ģʽ
	virtual GType::enMatchMode GetCurMatchMode() const;
	//��ȫ�ͷ�
	virtual void SafeDelete();
	//�õ�����ģʽ����
	virtual IMatchMode* MatchMode() const;
	virtual void PressFriendshipMatch();
	//������Ϣ
	GType::stMatchInfo& GetMatchInfo();

	//implement
private:
	//ѡ�������£��Ƿ����
	bool IsReadyAtSelectedScene();
	//���������
	void PressFriendshipMatch( IoTimer* timer );

private:
	IMatchMode*					match_mode_;
	MatchModel_Invalid			match_mode_invalid_;
	GType::stMatchInfo			match_info_;
};

//������ģʽ
class MatchMode_Managers : public MatchModeImpl{
public:
	MatchMode_Managers();

public:
	virtual GType::enMatchMode GetMatchMode() const;
	virtual void EnteredRoom();
	virtual const char* GetLuaHandlePressBeginGameFuncName() const;

protected:
	virtual const char* GetLuaHandlePressMatchModeFuncName();

	DECLARE_DYNCREATE(MatchMode_Managers)
};

//�Զ���ģʽ
class MatchMode_Custom : public MatchModeImpl{
public:
	MatchMode_Custom();

public:
	virtual GType::enMatchMode GetMatchMode() const;
	virtual void EnteredRoom();

	DECLARE_DYNCREATE(MatchMode_Custom)
};

//�������
class FightMode_Computer : virtual public FightModeImpl{
public:
	virtual GType::enFightMode GetFightMode() const;

	DECLARE_DYNCREATE(FightMode_Computer)
};

//�������
class FightMode_Friend : virtual public FightModeImpl{
public:
	virtual GType::enFightMode GetFightMode() const;

	DECLARE_DYNCREATE(FightMode_Friend)
};

//������ģʽ֮�������
class FightMode_Managers_Computer : public FightMode_Computer{
public:

protected:
	virtual bool IsCanPressFightMode() const;
	virtual const char* GetLuaHandlePressFightModeFuncName() const;
	virtual bool IsCanBegin() const;
	virtual void BeginMatch();

	DECLARE_DYNCREATE(FightMode_Managers_Computer)
};

//������ģʽ֮�������
class FightMode_Managers_Friend : public FightMode_Friend{
public:

protected:
	virtual bool IsCanPressFightMode() const;
	virtual const char* GetLuaHandlePressFightModeFuncName() const;
	virtual bool IsCanBegin() const;
	virtual void BeginMatch();

	DECLARE_DYNCREATE(FightMode_Managers_Friend)
};
//�����������
//�����Ȳ�֧��
/*
class FightMode_Random : public FightModeImpl{
public:
	virtual GType::enFightMode GetFightMode() const;

	DECLARE_DYNCREATE(FightMode_Random)
};*/