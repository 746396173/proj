#pragma once
/*
@author zhp
@date 2013-12-31
@purpose ��Ϸ���ܵ��ã�������Ϸ�ڵĺ���
*/
#include "GTypes.h"
namespace GFuncCall{
	//////////////////////////////////////////////////////////////////////////
	//�õ����ھ��
	HWND GetHwnd();
	//�رչ���dlg
	void CloseNoticeDlg();
	//�Ƿ���ڽ���
	bool IsExistTrainer();
	//�Ƿ������Ч����
	bool IsExistValidTrainer();
	
	//�Ƿ��ǽ���ѡ������
	bool IsTrainerSelectedScene();
	//malloc of game
	void* MallocOfGame( size_t size );
	//calloc of game
	void* CallocOfGame( size_t n, size_t size );
	//free of game
	void FreeOfGame( void* p );
	//SSL_read���õ�ssl handle
	void* GetSllReadHandle();
	//////////////////////////////////////////////////////////////////////////
	//����
	void PressKeyImpl( DWORD v_k, UINT msg );
	//������
	void LeftBtClickImpl( int x, int y );
	//////////////////////////////////////////////////////////////////////////
}