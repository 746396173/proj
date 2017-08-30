
// MainFrm.h : interface of the CMainFrame class
//

#pragma once
#include "ChildView.h"
#include "DlgUnion.h"
#include <Common/UsefulClass.h>
#include "MultiLogin.h"

class CMainFrame : public CFrameWnd, public Singleton<CMainFrame, Singleton_Instance>
{	
public:
	CMainFrame();

protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Operations
public:
	//��ʼ����ʺ����Ƿ���ȷ
	void BeginCheckAcValid();
	//������֤������֤ͨ�����ʺź�����
	void SetValidAcInfo( const std::string& ac_pwd );
#ifdef _MULTI_LOGIN_
	DlgMultiLogin&
#else
	DlgLogin& 
#endif
		GetDlgLogin();

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CChildView    m_wndView;

public:
	afx_msg void OnMenuLogin();

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnMenuRemoveBind();
	afx_msg void OnMenuReg();
	afx_msg void OnMenuPay();
	DECLARE_MESSAGE_MAP()

private:
	IoTimerPtr					timer_ac_check_;
#ifdef _MULTI_LOGIN_
	DlgMultiLogin				dlg_multi_login_;
#else
	DlgLogin					dlg_login_;
#endif
	DlgRemoveBind				dlg_remove_bind_;
	DlgReg						dlg_reg_;
	DlgPay						dlg_pay_;
	std::string					ac_pwd_;
};