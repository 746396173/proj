#pragma once
/*
@author zhp
@date 2013-12-31
@purpose ��Ϸ���ܵ��ã�������Ϸ�ڵĺ���
*/
#include "GTypes.h"

//GFuncCall->GFC_
//�����½�
//const ZHANG_TASK_FB_INFO* FindChapterInfo( int fb_id );
//���������
bool IsTheFbIdJuQingDone( int fb_id );
//�Ƿ����ھ�������
bool IsTheFbIdJuQingTask( int fb_id );
int GFC_GetShangJinCompleteCount();
int GFC_GetShangJinTotalCount();
// �ж��ͽ������״̬  ״̬=1 ��ʾ�ѽ�  ״̬=10 ��ʾ�Ѿ����
int GFC_GetShangJinTaskStatus(DWORD dwShangJinTaskId);
int GFC_GetMsgRoleCityRoomIndex();
void GFC_TidyInventoryItem(CD_En_TabCategory nTabSoltIndex);
LONGLONG GFC_GetSynCoorDinatesRandom();
//////////////////////////////////////////////////////////////////////////
void GFC_EnableWuDi( bool enable_wu_di );
//////////////////////////////////////////////////////////////////////////
//**********************UI************************************************
stCD_UiCtrl* GFC_Ui_TraUi(const char* cls_name);
bool GFC_Ui_ClickButton( const char* cls_name );
bool GFC_Ui_PutString( const char* cls_name, const wchar_t* the_str );
//////////////////////////////////////////////////////////////////////////
