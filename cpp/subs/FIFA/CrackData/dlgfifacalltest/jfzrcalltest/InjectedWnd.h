#pragma once


// CInjectedWnd �Ի���

class CInjectedWnd : public CDialog
{
	DECLARE_DYNAMIC(CInjectedWnd)

public:
	CInjectedWnd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInjectedWnd();

// �Ի�������
	enum { IDD = IDD_DLG_INJECTED_WND };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
};
