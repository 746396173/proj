// Testdll.h : Testdll DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTestdllApp
// �йش���ʵ�ֵ���Ϣ������� Testdll.cpp
//

class CTestdllApp : public CWinApp
{
public:
	CTestdllApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
