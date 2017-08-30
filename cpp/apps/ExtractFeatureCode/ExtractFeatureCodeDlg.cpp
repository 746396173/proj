
// ExtractFeatureCodeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ExtractFeatureCode.h"
#include "ExtractFeatureCodeDlg.h"
#include "afxdialogex.h"
#include <CmnMix/Cmn_Disasm.h>
#include <CmnMix/Cmn_UsefulFunc.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CExtractFeatureCodeDlg �Ի���



CExtractFeatureCodeDlg::CExtractFeatureCodeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CExtractFeatureCodeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIconW(IDR_MAINFRAME);
}

void CExtractFeatureCodeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ASM_INPUT, edit_asm_input_);
	DDX_Control(pDX, IDC_EDIT_RESULT, edit_result_);
}

BEGIN_MESSAGE_MAP(CExtractFeatureCodeDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BT_EXTRACT, &CExtractFeatureCodeDlg::OnBtExtract)
	ON_BN_CLICKED(IDC_BT_COPY, &CExtractFeatureCodeDlg::OnBtCopy)
END_MESSAGE_MAP()


// CExtractFeatureCodeDlg ��Ϣ�������

BOOL CExtractFeatureCodeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CExtractFeatureCodeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CExtractFeatureCodeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CExtractFeatureCodeDlg::PreTranslateMessage( MSG* pMsg )
{
	if (pMsg)
	{
		if ( WM_KEYDOWN == pMsg->message )
		{
			if ( VK_ESCAPE == pMsg->wParam || VK_RETURN == pMsg->wParam )
				return TRUE;
		}
	}
	return __super::PreTranslateMessage(pMsg);
}

void CExtractFeatureCodeDlg::OnBtExtract()
{
	CString str_code;
	edit_asm_input_.GetWindowText(str_code);
	CStringA str_code_a = CT2CA(str_code);

	Cmn_Disasm disasm;
	auto str_hex = Str2Hex(str_code_a, str_code_a.GetLength());
	disasm.SetInputBuffer((const unsigned char*)str_hex.c_str(), str_hex.size());

	const auto& str_res = disasm.GenFeatureCode();

	CString str_res_t = CA2CT(str_res.c_str());
	edit_result_.SetWindowText(str_res_t);
}

void CExtractFeatureCodeDlg::OnBtCopy()
{
	CString str_res;
	edit_result_.GetWindowText(str_res);
	CopyTextToClipboard(CT2CA(str_res), str_res.GetLength());
}
