#include "stdafx.h"
#include <Common/UiCtrls.h>

void CListCtrlStyled::PreSubclassWindow()
{
	__super::PreSubclassWindow();
	//style
	{
		DWORD dwStyle = GetExtendedStyle();
		dwStyle |= LVS_EX_FULLROWSELECT;		//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
		dwStyle |= LVS_EX_GRIDLINES;			//�����ߣ�ֻ������report����listctrl��
		dwStyle |= LVS_EX_CHECKBOXES;			//itemǰ����checkbox�ؼ�
		SetExtendedStyle(dwStyle);				//������չ���
	}
}