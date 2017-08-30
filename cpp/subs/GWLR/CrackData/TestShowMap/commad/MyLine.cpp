// MyLine.cpp: implementation of the CMyLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CMyLine, CObject, 0)

CMyLine::CMyLine()
{
	m_theName = "����";
}

CMyLine::~CMyLine()
{

}

CMyLine::CMyLine(CPoint& ptBegin,CPoint& ptEnd)
:m_theBegin(ptBegin),m_theEnd(ptEnd)
{
	m_theName = "����";
}

void CMyLine::OnDraw(CDC *lpDc)
{	
	m_thePen.m_crColor = RGB(54,109,201);
	//���¶����滻��ǰ����ͬ���͵Ķ���,���ؾɶ��������
	HGDIOBJ hOldPen = lpDc->SelectObject(m_thePen);

	BYTE r = GetRValue(m_thePen.m_crColor);
	BYTE g = GetGValue(m_thePen.m_crColor);
	BYTE b = GetBValue(m_thePen.m_crColor);

 	lpDc->MoveTo(m_theBegin);
	lpDc->LineTo(m_theEnd);	

	lpDc->SelectObject(hOldPen);
}


void CMyLine::OnMouseMove(UINT nFlags, CPoint point) 
{
	//���ֻ��һ������ÿ���ƶ������������ĵ�������
	//	m_theBegin = point;
	m_theEnd = point;
}

void CMyLine::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_theName = "����";
	m_theBegin = point;
}


CMyBaseShape* CMyLine::CreateShape()
{
	return new CMyLine;
}

