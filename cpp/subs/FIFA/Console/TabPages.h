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
//////////////////////////////////////////////////////////////////////////
struct stMakeTabPages{
	LPCTSTR						item_name;
	const CRuntimeClass*		obj_class;

	static const int		kPagesMax = 
#ifdef _WG_TEST
		5
#else
		4
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
	void SetTabIdx( int tab_idx );
	int GetTabIdx() const;

private:
	virtual void OnCancel();
	DECLARE_DYNCREATE(TablePage)
	//DECLARE_MESSAGE_MAP()

protected:
	int		tab_idx_;
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
	//12���Զ�����
	void SetRunConsoleAt12Time();

protected:
	virtual void DoDataExchange( CDataExchange* pDX );
	virtual BOOL OnInitDialog();

private:
	//���ýٳ�dll���ñ�
	void SetHijackDllCfg();

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
	//����EP
	afx_msg void OnBnSaveEp();
	//����ep�ļ�Ŀ¼
	afx_msg void OnBnSetEpFilePath();
	//12�㶨ʱ����
	afx_msg void OnBnAutoRunConsoleAt12Time();
	DECLARE_MESSAGE_MAP()
	DECLARE_DYNCREATE(PageAccount)

private:
	PageAccount_List				list_ctrl_;
	CComboBox						combo_crack_catpcha_;
	DWORD							stored_ip_;				//�ֿ������IP
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
	CList_ItemsSingle& GetCtrlItem();

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange( CDataExchange* pDX );

protected:
	FuncObj_NormalS* GetItemNormal( int item );

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
	CList_PlayersSingle			list_players_;
	CList_ItemsSingle			list_items_;
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

	afx_msg void OnBtGetMyOfferList();
	afx_msg void OnBtGetOtherOfferItems();
	DECLARE_DYNCREATE(PageTrade)
	DECLARE_MESSAGE_MAP()

private:
	CList_MyOfferList				my_offer_list_;			//�ҵĳ����б�
	CList_OtherOffers				other_offer_items_;		//�����ŵĳ�����
	CEdit							my_offer_total_;
	CEdit							other_offer_total_;
	int								cur_notify_item_;		//��ǰͨ����
};

class PageItemInfo : public TablePage, public Singleton<PageItemInfo, Singleton_Instance>{
public:
	PageItemInfo();
	CList_ItemsSingle& GetCtrlItem();
	void SetItemsTotalCnt( int cnt );
	void SetNofityItem( int notify_item );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_DYNCREATE(PageItemInfo)
	//ˢ����Ʒ��Ϣ
	afx_msg void OnBtGetItemsInfo();
	DECLARE_MESSAGE_MAP()

private:
	CList_ItemsSingle			list_items_;
	CEdit						items_total_;
	CEdit						edit_notify_item_;

private:
	int							notify_item_;
};

class PagePlayerInfo : public TablePage, public Singleton<PagePlayerInfo, Singleton_Instance>{
public:
	PagePlayerInfo();
	CList_PlayersSingle& GetCtrlPlayer();
	void SetItemsTotalCnt( int cnt );
	void SetNofityItem( int notify_item );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_DYNCREATE(PagePlayerInfo)
	//ˢ����Ա��Ϣ
	afx_msg void OnBtGetPlayersInfo();
	DECLARE_MESSAGE_MAP()

private:
	CList_PlayersSingle			list_players_;
	CEdit						players_total_;
	CEdit						edit_notify_item_;

private:
	int							notify_item_;
};
