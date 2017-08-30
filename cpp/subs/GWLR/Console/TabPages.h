#pragma once
/*
@author zhp
@date 2013-12-23
@purpose table pages
*/
#include <string>
#include <FuncObjs/FuncObj.h>
#include <stack>
#include "FuncObjS.h"
#include "ListCtrls.h"
#include "ListCtrl_Players.h"
#include "DlgUnion.h"
//////////////////////////////////////////////////////////////////////////
struct stMakeTabPages{
	LPCTSTR						item_name;
	const CRuntimeClass*		obj_class;

	static const int		kPagesMax = 
#ifdef _WG_TEST
		9
#else
		3
#endif
		;
};

class CTabOption;
class TablePage : public CDialog{
protected:
	TablePage( UINT template_id = -1 );

public:
	bool Create( CWnd* parent_wnd );
	//�õ�CTabOption
	CTabOption& Parent2TabOption();
	//get normal_s
	FuncObj_NormalS* GetNormalS_ByAccount( const CString& str_account );
	FuncObj_NormalS* GetNormalS_ByAccount( const char* str_account );

private:
	virtual void OnCancel();
	DECLARE_DYNCREATE(TablePage)
	//DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

class PageAccount : public TablePage, public Singleton<PageAccount, Singleton_Instance>{
private:
	PageAccount();

public:
	PageAccount_List& GetAccountList();
	//save config
	void SaveConfig();
	//�õ��ֿ�ŷ�������IP
	std::string GetStoredIp() const;
	//ˢ�µ�ǰ�ʺ�֪ͨ��
	void RefreshCurNotifyItem();
	//�õ���ǰ�ʺ�֪ͨ��
	int GetCurNotifyItem() const;
	//���õ�ǰ�ʺ�֪ͨ��
	void SetCurNotifyItem( int cur_item );
	FuncObj_NormalS* GetCurNotifyFuncObj();
	//֪ͨ�Ҽ�����
	void NotifyRightBtHit();
	//12���Զ�����
	void SetRunConsoleAt3Time();
	//֪ͨ��������Ѱ·
	void NotifyOpenVillagePath();

protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	virtual BOOL OnInitDialog();

private:
	//���ýٳ�dll���ñ�
	void SetHijackDllCfg();
	//���Ƕ���
	void CopyMovies( const CPath& movie_path );
	//�Ż��¼�
	void YouHuaSetting();

private:
	afx_msg void OnBtSelectGamePath();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeCrackCaptcha();
	//��������������
	afx_msg void OnBnClickedBtSetMaxLogin();
	//�����ʺ�
	afx_msg void OnBnClickedBtAcAcMgr();
	//�������������˵�
	afx_msg void OnBnShowAllOperMenu();
	//ȷ�ϲֿ��IP
	afx_msg void OnBtOkStoretdIp();
	afx_msg void OnBtRunFirstScript();
	afx_msg void OnSelchangeRoleMaxCnt();
	afx_msg void OnChangeLoginDelay();
	//�����Ҽ�����
	afx_msg void OnBnRightBtHit();
	//3�㶨ʱ����
	afx_msg void OnBnAutoRunConsoleAt3Time();
	//��ž�ֹͣ��½
	afx_msg void OnBtStopLoginAtBanAc();
	//����Ѹ�׼���
	afx_msg void OnBtUseXunLei();
	//�����Ż�
	afx_msg void OnBtUseYouHua();
	//���������ص�
	afx_msg void OnBtLoginAtDisconnectRightNow();
	//��������Ѱ·
	afx_msg void OnBtOpenVillagePath();
	//�����������
	afx_msg void OnBtIgnorePwdErr();
	//�Զ�����
	afx_msg void OnBtAutoDial();
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(PageAccount)

private:
	PageAccount_List				list_ctrl_;
	CComboBox						combo_crack_catpcha_;
	CComboBox						combo_role_max_cnt_;
	CEdit							edit_cur_notify_item_;
	CEdit							edit_login_delay_;
	DlgAutoDial						dlg_auto_dial_;

private:
	DWORD							stored_ip_;				//�ֿ������IP
	int								cur_notify_item_;		//��ǰ�ʺ�֪ͨ��
};

class PageSetting : public TablePage{
private:
	PageSetting();

protected:
	virtual BOOL OnInitDialog();

private:
	afx_msg void OnBtGamePath();
	DECLARE_DYNCREATE(PageSetting)
	DECLARE_MESSAGE_MAP()

protected:
	//���ýٳ�dll���ñ�
	void SetHijackDllCfg();
};

class PageTest : public TablePage, public Singleton<PageTest, Singleton_Instance>{
private:
	PageTest();

public:
	//������Ա��Ϣ����
	void SetPlayersTotalCnt( int cnt );
	//������Ʒ��Ϣ����
	void SetItemsTotalCnt( int cnt );
	FuncObj_NormalS* GetCurNormalS();

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange( CDataExchange* pDX );

private:
	//��һ��Ҫ���ص�DLL�ļ�
	afx_msg void OnBtOpenLib();
	//��ע��dll�������dll
	afx_msg void OnBtLoadLib();
	//ж�����dll
	afx_msg void OnBtUnloadLib();
	//����LuaTest����
	afx_msg void OnBtCallLuaLuaTest();
	//���¼���lua�ļ�
	afx_msg void OnBtReloadLua();
	//����log����ʱ�ļ�
	afx_msg void OnFlushLogToTempFile();
	//ִ�нű�
	afx_msg void OnBtRunScript();
	//��ֹ�ű�
	afx_msg void OnBtTerminateScript();
	//��Ӧ���ѡ���ʺ�
	afx_msg void OnDropdownSelectAccount();
	//ˢ����Ա��Ϣ
	afx_msg void OnBtGetPlayersInfo();
	//�����ɹ���½
	afx_msg void OnBtLoginSucceed();
	//ˢ����Ʒ��Ϣ
	afx_msg void OnBtGetItemsInfo();
	DECLARE_DYNCREATE(PageTest)
	DECLARE_MESSAGE_MAP()

private:
	CComboBox					combo_select_account_;
	CEdit						players_total_;
	CEdit						items_total_;
};

// PageTrade dialog
class PageTrade : public TablePage, public Singleton<PageTrade, Singleton_Instance>{
public:
	PageTrade();
	virtual ~PageTrade();

	//interfaces
public:
	FuncObj_NormalS* GetCurNormalS();
	//���õ�ǰͨ����
	void SetCurNotifyItem( int item );
	//�����ҵĳ����б�����
	void SetMyOfferListCnt( int cnt );
	//���������ŵ�����
	void SetOtherOfferItemsCnt( int cnt );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	BOOL OnInitDialog();

	afx_msg void OnBtGetMyOfferList();
	afx_msg void OnBtGetOtherOfferItems();
	DECLARE_DYNCREATE(PageTrade)
	DECLARE_MESSAGE_MAP()

private:
	CList_MyOfferList				my_offer_list_;			//�ҵĳ����б�
	CList_OtherOffers				other_offer_items_;		//�����ŵĳ�����
	CEdit							my_offer_total_;
	CEdit							other_offer_total_;
	CButton							bt_refresh_my_list_;
	CButton							bt_refresh_other_list_;
	int								cur_notify_item_;		//��ǰͨ����
};

//������Ϣ
class PageSkill : public TablePage, public Singleton<PageSkill, Singleton_Instance>{
public:
	PageSkill();
	//���ü�������
	void SetSkillTotalCnt( int cnt );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_DYNCREATE(PageSkill)
	//ˢ�¼���
	afx_msg void OnBtRefreshSkillInfo();
	DECLARE_MESSAGE_MAP()

private:
	CEdit							edit_skill_total_cnt_;
};

//��Ϸ������Ϣ
class PageGameObjs : public TablePage, public Singleton<PageGameObjs, Singleton_Instance>{
public:
	PageGameObjs();
	//������Ϸ��������
	void SetGameObjTotalCnt( int cnt );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_DYNCREATE(PageGameObjs)
	//ˢ����Ϸ����
	afx_msg void OnBtRefreshGameObjs();
	DECLARE_MESSAGE_MAP()

private:
	CEdit							edit_gameobj_total_cnt_;
};

//��Ʒ��Ϣ
class PageItems : public TablePage, public Singleton<PageItems, Singleton_Instance>{
public:
	PageItems();
	void SetItemsTotalCnt( int cnt );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_DYNCREATE(PageItems)
	afx_msg void OnBtRefreshPageItems();
	DECLARE_MESSAGE_MAP()

private:
	CEdit						edit_item_total_cnt_;
};

//������Ϣ
class PageRoom : public TablePage, public Singleton<PageRoom, Singleton_Instance>{
public:
	PageRoom();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_DYNCREATE(PageRoom)
	afx_msg void OnBtRefreshRoomInfo();
	DECLARE_MESSAGE_MAP()

private:
};

//����
class PageTask : public TablePage, public Singleton<PageTask, Singleton_Instance>{
public:
	PageTask();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_DYNCREATE(PageTask)
	DECLARE_MESSAGE_MAP()

private:
};

//ע������
class PageRemark : public TablePage, public Singleton<PageRemark, Singleton_Instance>{
public:
	PageRemark();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_DYNCREATE(PageRemark)
	DECLARE_MESSAGE_MAP()
	BOOL OnInitDialog();

private:
	CEdit			static_remark_;
};