// MyRect.cpp: implementation of the CMyRect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyRect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

IMPLEMENT_SERIAL(CMyRect, CObject, 0)

CMyRect::CMyRect()
{
	m_theName = "����";
}

CMyRect::CMyRect(CPoint& ptBegin,CPoint& ptEnd)
:m_theBegin(ptBegin),m_theEnd(ptEnd)
{
	m_theName = "����";
}

CMyRect::~CMyRect()
{

}

void CMyRect::OnDraw(CDC *lpDc)
{	
	//CPen( int nPenStyle������ʽ, int nWidth���ʿ��, COLORREF crColor������ɫ );
	HGDIOBJ hOldPen = lpDc->SelectObject(m_thePen);

	lpDc->SelectObject(m_RectBrush);
	if( lpDc != NULL )
	{
		lpDc->Rectangle(CRect(m_theBegin,m_theEnd));
	}

//	lpDc->SelectObject(hOldPen);
}

void CMyRect::OnMouseMove(UINT nFlags, CPoint point) 
{
	//���ֻ��һ������ÿ���ƶ������������ĵ�������
	//	m_theBegin = point;
	m_theEnd = point;
}

void CMyRect::OnLButtonDown(UINT nFlags, CPoint point) 
{
	m_theBegin = point;
	m_theName = "����";
}

CMyBaseShape* CMyRect::CreateShape()
{
	return new CMyRect;
}

