
// ExtractFeatureCode.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include <AppBase/CmnCWinApp.h>


// CExtractFeatureCodeApp:
// �йش����ʵ�֣������ ExtractFeatureCode.cpp

class CExtractFeatureCodeApp : public Cmn_CWinApp{
public:
	CExtractFeatureCodeApp();

private:
	bool OnInit_() override;
};
CMN_MY_APP_DECLARE(CExtractFeatureCodeApp);
