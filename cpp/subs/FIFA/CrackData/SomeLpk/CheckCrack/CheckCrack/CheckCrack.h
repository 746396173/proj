// CheckCrack.h : CheckCrack DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCheckCrackApp
// �йش���ʵ�ֵ���Ϣ������� CheckCrack.cpp
//

class CCheckCrackApp : public CWinApp
{
public:
	HANDLE		m_hCheckCrackThread;
public:
	CCheckCrackApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
