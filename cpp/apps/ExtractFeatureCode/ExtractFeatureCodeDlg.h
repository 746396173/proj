
// ExtractFeatureCodeDlg.h : ͷ�ļ�
//

#pragma once


// CExtractFeatureCodeDlg �Ի���
class CExtractFeatureCodeDlg : public CDialog
{
// ����
public:
	CExtractFeatureCodeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EXTRACTFEATURECODE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtExtract();
	afx_msg void OnBtCopy();
	DECLARE_MESSAGE_MAP()

private:
	CEdit			edit_asm_input_;
	CEdit			edit_result_;
};
