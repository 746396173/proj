#pragma once
/*
@author zhp
@date 2013-12-31
@purpose ��ź�����ַ��ȫ�ֱ����ĵ�ַ
*/
#include "Common/MemOper.h"
#include <CD_CommonFiles/CD_Updates.h>
//g_f_s_->stdcall function
//g_f_c_->cdecl function
//g_f_t_->thiscall function
//g_f_a_->��������Լ���ĺ���
//g_v_->�麯����
//g_sa_->���ֽ��ַ���
//g_sw_->���ֽ��ַ���
namespace GAddr{
	/*
	����http��
	@1:�����ַ
	@2:ָ��������(ASCII�ַ���)
	@3:�����Ч���ݳ���
	*/
	//SSL_read-->int 	SSL_read(SSL *ssl,void *buf,int num);
	typedef MemOper<Oper_Cdecl> MO_SslRead;
	//extern MO_SslRead						g_pSSL_read;
	const MO_SslRead								g_pSSL_read(UPDATES_FIFA_REVERSAL_SSL_READ);
	//SSL_write->int SSL_write(SSL *ssl, const void *buf, int num);
	typedef MemOper<Oper_Cdecl> MO_SslWrite;
	//extern MO_SslWrite								g_pSSL_write;
	const MO_SslWrite								g_pSSL_write(UPDATES_FIFA_REVERSAL_SSL_WRITE);
	//////////////////////////////////////////////////////////////////////////
	//SSL_get_error, int SSL_get_error(SSL *ssl, int ret)
	const MemOper<Oper_Cdecl>				g_pSSL_get_error(UPDATES_FIFA_REVERSAL_SSL_GET_ERROR);
	const unsigned int						g_pHttpSendCall_ = UPDATES_FIFA_REVERSAL_HTTP_SEND_CALL;		// ����CALL
	//hook����call
	//const MemOper<Oper_Cdecl>				g_pHttpSendCall(g_pHttpSendCall_);
	/*
	�����õ������ھ��
	hook Call CreateWindowEx����һ��ָ��
	*/
	const unsigned int						g_pHookForGainMainWndHandle_ = UPDATES_FIFA_REVERSAL_HOOK_FOR_GAIN_MAIN_WND_HANDLE;	// ���ھ��
	//malloc of game
	const MemOper<Oper_Cdecl, MemOper_RetrieveAddr> g_pGMalloc(UPDATES_FIFA_REVERSAL_MEMOPER_G_MALLOC);	
	//calloc of game
	const MemOper<Oper_Cdecl, MemOper_RetrieveAddr> g_pGCalloc(UPDATES_FIFA_REVERSAL_MEMOPER_G_CALLOC);
	//free of game
	const MemOper<Oper_Cdecl, MemOper_RetrieveAddr> g_pGFree(UPDATES_FIFA_REVERSAL_MEMOPER_G_FREE);
	//���ͼ��̡������Ϣ����ȡ�����ַcall
	const MemOper<Oper_Cdecl>					g_pGetMouseKeyEventHandler(UPDATES_FIFA_REVERSAL_MEMOPER_GET_MOUSE_KEY_EVENT_HANDLER);
	//�հ�call(-4)
	/*const unsigned int							g_pHookRecvCallAddr_ = UPDATES_FIFA_REVERSAL_HOOK_RECV_CALL_ADDR;
	const unsigned int							g_pHookRecvCallAddr1_ = UPDATES_FIFA_REVERSAL_HOOK_RECV_CALL_1;
	const unsigned int							g_pHookRecvCallAddr2_ = UPDATES_FIFA_REVERSAL_HOOK_RECV_CALL_2;
	const unsigned int							g_pHookRecvCallAddr3_ = UPDATES_FIFA_REVERSAL_HOOK_RECV_CALL_3;*/
	const unsigned int							g_pHookRecvCallAddr_ = UPDATES_FIFA_REVERSAL_HOOK_RECV_CALL_ADDR_ZHP;
	//dx GetDeviceState�������ú����һ��ָ��ĵ�ַ
	const unsigned int							g_pHookAfterGetDeviceState_ = UPDATES_FIFA_REVERSAL_HOOK_AFTER_GET_DEVICE_STATE;
	//hook��������
	const unsigned int							g_pHookAnimationFeature_ = UPDATES_FIFA_REVERSAL_HOOK_ANIMATION_FEATURE;
	//���������
	pt_cdword									g_pHookTopCmdFn = UPDATES_FIFA_REVERSAL_HOOK_TOP_COMMAND_FN;
	//hook�����Ĵ���DX input�ı�־����̨�빲��ģʽ
	const unsigned int							g_pHookDxInputModel = UPDATES_FIFA_REVERSAL_HOOK_DX_INPUT_MODEL;
	//hook��Ⱦ�̣߳�sleep�����ڽ���CPU
	const unsigned int							g_pHookRenderThd_Sleep = UPDATES_FIFA_REVERSAL_STOP_RENDER_AND_SLEEP_HOOK;
	//��Ϸ���̵߳���SSL_read���յ�һ��������HTTP����ִ�еĵط�
	const unsigned int							g_pHookAfterGameReadFullHttpPackage = UPDATES_FIFA_REVERSAL_HOOK_AFTER_GAME_READ_FULL_HTTP_PACKAGE;
	//��Ϸ���̵߳���SSL_read��ִ�д����ִ�еĵط�
	//const unsigned int							g_pHookAfterGameReadFullHttpPackage_ByError = 0x00F2A24F;
	//match time hook
	extern int				g_pSetMatchTimeAddr;
	//////////////////////////////////////////////////////////////////////////
	const unsigned int							g_pHookGainSslHandle = UPDATES_FIFA_REVERSAL_SSL_READ_AND_WRITE_SOCKET_ADDR_HOOK;
	extern volatile int							g_hSslHandle;
	//////////////////////////////////////////////////////////////////////////
}