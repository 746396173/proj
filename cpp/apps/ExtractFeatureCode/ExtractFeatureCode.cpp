
// ExtractFeatureCode.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ExtractFeatureCode.h"
#include "ExtractFeatureCodeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CExtractFeatureCodeApp::CExtractFeatureCodeApp()
{
	is_add_main_thred_ = false;
}

CMN_MY_APP_DEFINE(CExtractFeatureCodeApp);

bool CExtractFeatureCodeApp::OnInit_()
{
	if (!__super::OnInit_())
		return false;

	CExtractFeatureCodeDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}
	return FALSE;
}

