// hijacked.h : hijacked DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// ChijackedApp
// �йش���ʵ�ֵ���Ϣ������� hijacked.cpp
//

class ChijackedApp : public CWinApp
{
public:
	ChijackedApp();
	~ChijackedApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
