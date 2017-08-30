#pragma once
/*
@author zhp
@date 2013-12-31
@purpose ��Ϸ���ܵ��ã�������Ϸ�ڵĺ���
*/
#include "GTypes.h"
#include <WinDef.h>
#include <string>

namespace GFuncCall{
	extern const WORD kGameHashArray;
	//////////////////////////////////////////////////////////////////////////
	//�õ����ھ��
	HWND GetHwnd();
	//�����ϣֵ
	WORD CalcHash_WORD( const wchar_t* wstr );
	WORD CalcHash_WORD( const std::wstring& wstr );
	DWORD CalcHash_DWORD( const wchar_t* wstr_lhs, const wchar_t* wstr_rhs );
	DWORD CalcHash_DWORD( const std::wstring& wstr_lhs, const std::wstring& wstr_rhs );
	DWORD CalcHash_DWORD( const wchar_t* wstr );
	DWORD CalcHash_DWORD( const std::wstring& wstr );
	//////////////////////////////////////////////////////////////////////////
	//����δ֪����
	//void* GetFbUnknownObjByName( const std::wstring& room_id );
	//////////////////////////////////////////////////////////////////////////
	float GetPreActionPlayTime();
}