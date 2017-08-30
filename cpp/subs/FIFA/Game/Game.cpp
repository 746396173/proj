// Game.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Facility/GAddr.h"
#include "Facility/GOffset.h"
#include "Protocol/P_Defines.h"
#include "FuncObjC.h"
#include "Facility/GClass.h"
#include "Protocol/P_BaseStruct.h"
#include <set>
#include "Facility/GFuncCall.h"
#include <openssl/ssl.h>
#include "../CrackData/dlgfifacalltest/jfzrcalltest/jfzrbase.h"
#include <CommonX/CmnX_HookerMore.h>
#include "DllApp.h"
//////////////////////////////////////////////////////////////////////////
//API hook
//////////////////////////////////////////////////////////////////////////
bool InitCodeHooker();
extern bool InitGame()
{
	if ( !InitCodeHooker() )
		return false;
	return true;
}

//for gain main wnd handle
void* Hooker_GainMainWndHandle( IHooker& hooker, JmpHookerAmbient& ambient )
{
	LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "ͨ��hook code�õ������ھ��";
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	auto& my_app = GetMyApp();

	if (my_app.game_main_wnd_)
		return hooker.GetCodeOrig();
	my_app.game_main_wnd_ = (HWND)ambient.eax_;
	if (func_obj_normal)
	{
		GetIoService().post([](){
			auto func_obj_normal = FuncObj_NormalC::GetInstance();
			if ( !func_obj_normal )
			{
				assert(false);
				return;
			}
			if (!func_obj_normal->InitInter(GetMyApp().game_main_wnd_))
			{
				LOG_O(Log_fatal) << "��ʼ��func obj interʧ��";
			}
		});		
	}
	return hooker.GetCodeOrig();
}

//http send call
void* Hooker_HttpSendCall( IHooker& hooker, JmpHookerAmbient& ambient )
{
	using namespace GType;
	using namespace GClass;
	
	auto& http_package_send = GClass::HttpPackageSend::GetMe();
	http_package_send.BeginSendHttp();
	//try{
	//////////////////////////////////////////////////////////////////////////
	auto http_send_call_content = ambient.EspStackValueAs<stHttpSendCall_Content*>(4 + offsetof(stHttpSendCall_Content, str_http_content));
	if (http_send_call_content)
	{
		typedef stSpecifyTag_T<DWORD> SelfSendTag;
		static SelfSendTag self_send_tag("&*_+");
		//�ж��Ƿ���ע���̷߳��͵İ�
		if ( self_send_tag == *(SelfSendTag*)(http_send_call_content->str_http_content + http_send_call_content->total_size_http_content + 1) )
		{
			assert(!"�����Ѿ�����������������ˣ��������BUG");
			return hooker.GetCodeOrig();
		}

		if (http_send_call_content->str_http_content)
		{
			auto func_obj_normal = FuncObj_NormalC::GetInstance();
			if ( !func_obj_normal )
			{
				LOG_ENTER_FUNC;
				LOG_O(Log_error) << "��Ϸ���Ѿ���ʼ�����ˣ�FuncObj_NormalC��Ȼ��δ��������";
				return hooker.GetCodeOrig();
			}

			if (func_obj_normal->NeedReplaceSendContent())
			{
				if (func_obj_normal->ReplaceSendContent(*http_send_call_content))
					return hooker.GetCodeOrig();
			}

			auto inject = func_obj_normal->GetInterInject();
			if ( !inject )
			{
				LOG_ENTER_FUNC;
				LOG_O(Log_error) << "inject��δ����";
				return hooker.GetCodeOrig();
			}

			auto http_content_copy = std::make_shared<std::string>(http_send_call_content->str_http_content, http_send_call_content->total_size_http_content);
			inject->AsyncExec([=](){
				HandleSendPackage::GetMe().HandleSendPakcageOfGame(*http_content_copy);
			});
		}
	}
	return hooker.GetCodeOrig();
}

//hook recv call
void* Hooker_RecvCall( IHooker& hooker, JmpHookerAmbient& ambient )
{
	//�ж��Ƿ�http��ͷ
	typedef stSpecifyTag_N<9> SpecifyTag;
	static SpecifyTag http_tag("HTTP/1.1 ");

	//http�ַ��������esp��ƫ��
	/*const int kEspOffset_HttpStr = 0x18;
	auto http_str_ptr = ambient.EspStackValueAs<const char*>(kEspOffset_HttpStr);*/
	auto http_str_ptr = (pt_csz)ambient.edi_;
	if ( !http_str_ptr )
		goto LABEL_RET;
	
	auto& Handle_recv = GClass::HandleRecvPackage::GetMe();
	//����հ����ܳ���
	//const int kPackageLength = ambient.EspStackValueAs<size_t>(kEspOffset_HttpStr + 4);
	const int kPackageLength = ambient.eax_;
	if (kPackageLength <= 0)
		goto LABEL_RET;
	/*LOG_O(Log_error).operator<< ("�հ�,���ȣ�").operator << (kPackageLength).operator<<(" ���ݣ�").write(http_str_ptr, kPackageLength);
	goto LABEL_RET;*/

	if ( http_tag == *(SpecifyTag*)http_str_ptr )
	{
		Handle_recv.RecvHttpPackage(http_str_ptr, kPackageLength);
	}
	else
	{
		Handle_recv.HandleFollowPackage(http_str_ptr, kPackageLength);
	}
LABEL_RET:
	return hooker.GetCodeOrig();
}

bool g_is_open_you_hua = true;

//dx GetDeviceState�������ú����һ��ָ��ĵ�ַ
void* Hooker_AfterGetDeviceState( IHooker& hooker, JmpHookerAmbient& ambient )
{
	auto normal_c = FuncObj_NormalC::GetInstance();
	if ( !normal_c )
		return hooker.GetCodeOrig();
	auto& press_key_ptr = normal_c->GetDI_PressKeyPtr();
	if ( !press_key_ptr )
		return hooker.GetCodeOrig();

	auto key_state_buffer = (char*)(DI_KeyStateBuffer)(ambient.ebp_ - FIFA_REVERSAL_HOOK_AFTER_GET_DEVICE_STATE_BUFF_OFFSET___);
	if ( !key_state_buffer )
		return hooker.GetCodeOrig();

	if ( key_state_buffer[DIK_F3] & 0x80 )
	{
		g_is_open_you_hua = true;
	}
	else if ( key_state_buffer[DIK_F4] & 0x80 )
	{
		g_is_open_you_hua = false;
	}

	if (press_key_ptr->first.empty())
		return hooker.GetCodeOrig();

	{
		WriteLock write_lock(press_key_ptr->second);
		auto& di_key = press_key_ptr->first.front();
		if (di_key.is_down_)
		{
			key_state_buffer[di_key.di_key_] |= 0x80;
			di_key.is_down_ = false;
		}
		else
		{
			//assert((*key_state_buffer)[di_key.di_key_] & 0x80);
			key_state_buffer[di_key.di_key_] = 0;
			press_key_ptr->first.pop();
		}
	}
	return hooker.GetCodeOrig();
}

//�Ƿ����ڱ���
bool g_isBeginingMatch = false;
//��ʼ�����ĵ�һ������
const char* const kBeginMatchAnimate = "ApplyScreenHUDSetting";
//����������Ķ���
const char* const kMatchEndAnimate = "StartPostMatch";
//���һ�������Ŀ�ʼ
const char* const kSendMatchEnd = "SendMatchEnd";

//��������
void* Hooker_AnimationFeature( IHooker& hooker, JmpHookerAmbient& ambient )
{
	using namespace GType;
	auto norc = FuncObj_NormalC::GetInstance();
	if (!norc)
		return hooker.GetCodeOrig();
	/*auto game_state = norc->GetGameState();
	if (game_state <= enGameState_Managers_Random || game_state > enGameState_MatchEnd_Back)
	{
		if (g_isBeginingMatch)
		{
			GetIoService().post([](){
				g_isBeginingMatch = false;
			});
		}
		return hooker.GetCodeOrig();
	}*/

	if (IsUnValidPtr(ambient.esp_))
		return hooker.GetCodeOrig();
	auto animation_feature = ambient.EspStackValueAs<const char*>(4);
	if (IsUnValidPtr(animation_feature))
		return hooker.GetCodeOrig();
	/*LOG_O(Log_fatal) << "���" << animation_feature;
	return hooker.GetCodeOrig();*/

	struct PlayingHelper{
		std::set<std::string>			strs_;
		PlayingHelper(){
			strs_.insert(kBeginMatchAnimate);
			strs_.insert("exitPlayState");
			strs_.insert(kSendMatchEnd);
		}
	};
	struct StopHelper{
		std::set<std::string>			strs_;
		StopHelper(){
			strs_.insert("enterPlayState");
			strs_.insert(kMatchEndAnimate);
		}
	};
	//�����Ƿ����ڲ���
	static bool animation_playing = false;
	static const PlayingHelper playing_helper;
	static const StopHelper stop_helper;
	static IoTimerPtr timer_press;
	if ( playing_helper.strs_.find(animation_feature) != playing_helper.strs_.end() )
		//��ʼ����
	{
		/*if (animation_playing)
			return hooker.GetCodeOrig();*/
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "��ʼ����, animation_feature:" << animation_feature;
		bool* ptr_animation_playing = &animation_playing;
		GetIoService().post([ptr_animation_playing](){
			assert(ptr_animation_playing);
			if (!*ptr_animation_playing)
				*ptr_animation_playing = true;

			if (timer_press)
			{
				if (timer_press->IsClocking())
					return;
				timer_press->Continue();
				return;
			}			
			timer_press = CreateIoTimer(500, true, [ptr_animation_playing](const IoTimerPtr& timer){
				if (!timer)
				{
					assert(false);
					return;
				}
				auto norc = FuncObj_NormalC::GetInstance();
				if (!norc)
					return;
				auto game_state = norc->GetGameState();
				if (enGameState_Match_BeginFirtAnimate != game_state && enGameState_MatchEnd != game_state)
				{
					return;
				}
				assert(ptr_animation_playing);
				if (!*ptr_animation_playing)
				{
					LOG_ENTER_FUNC;
					LOG_O(Log_debug) << "������־��ȡ��������������";
					return;
				}
				LOG_ENTER_FUNC;
				LOG_O(Log_trace) << "��������";
				timer->Continue();
				norc->PressDxinputKey(DIK_ESCAPE);
			});
		});

		if (0 == strcmp(kBeginMatchAnimate, animation_feature))
		{
			SetIoTimer(1000 * 4, [](IoTimer*){
				//assert(!g_isBeginingMatch);
				LOG_O(Log_debug) << "g_isBeginingMatch�Ѿ�Ϊ����";
				g_isBeginingMatch = true;
			});
		}
		/*if (!g_isBeginingMatch)
		{
			GetIoService().post([](){
				g_isBeginingMatch = true;
			});
		}*/		
		/*else if (0 == strcmp(kSendMatchEnd, animation_feature))
		{
			GetIoService().post([](){
				g_isBeginingMatch = false;
			});
			if (timer_press)
				timer_press->Cancel();
		}*/
	}
	else if ( stop_helper.strs_.find(animation_feature) != stop_helper.strs_.end() )
		//��������
	{
		if (g_isBeginingMatch && 0 == strcmp(kMatchEndAnimate, animation_feature))
		{
			GetIoService().post([](){
				g_isBeginingMatch = false;
			});
			if (timer_press)
				timer_press->Cancel();
		}
		if (!animation_playing)
			return hooker.GetCodeOrig();
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "��������, animation_feature:" << animation_feature;
		bool* ptr_animation_playing = &animation_playing;
		GetIoService().post([ptr_animation_playing](){
			*ptr_animation_playing = false;
		});
	}
	return hooker.GetCodeOrig();
}

//Ϊ�˽�����Ⱦ�̵߳�CPU
void* Hooker_RenderThd_Sleep( IHooker& hooker, JmpHookerAmbient& ambient )
{
	using namespace GType;
	if ( !g_is_open_you_hua )
		return hooker.GetCodeOrig();
	auto norc = FuncObj_NormalC::GetInstance();
	if ( !norc )
		return hooker.GetCodeOrig();
	auto game_state = norc->GetGameState();

	/*if (game_state >= enGameState_Managers_Computer && game_state <= enGameState_Match_Ready 
		|| game_state >= enGameState_MatchEnd && game_state <= enGameState_MatchEnd_Prize 
		|| enGameState_Match_BeginFirtAnimate == game_state && g_isBeginingMatch)*/
	if (game_state >= enGameState_Managers_Computer && game_state <= enGameState_Managers_Friend
		|| game_state >= enGameState_Match_Wait && game_state <= enGameState_Match_Ready
		|| game_state >= enGameState_MatchEnd && game_state <= enGameState_MatchEnd_Prize
		|| enGameState_Match_BeginFirtAnimate == game_state && g_isBeginingMatch)
	{
		static int tick_count = 0;
		if ( tick_count++ % 20 != 0 )
		{
			::Sleep(50);
			void* the_addr;
			_asm mov the_addr, offset LABEL_YOU_HA
			return the_addr;
		}
	}
	return hooker.GetCodeOrig();
LABEL_YOU_HA:
	_asm{
		retn
	}
}

//��Ϸ���̵߳���SSL_read���յ�һ��������HTTP����ִ�еĵط�
void* Hooker_AfterReadFullHttpPackage( IHooker& hooker, JmpHookerAmbient& ambient )
{
	auto& http_package_send = GClass::HttpPackageSend::GetMe();
	http_package_send.EndRecvHttp();
	return hooker.GetCodeOrig();
}

//��Ϸ���̵߳���SSL_read���յ�һ��������HTTP���������ִ�еĵط�
void* Hooker_AfterReadFullHttpPackageByError( IHooker& hooker, JmpHookerAmbient& ambient )
{
	assert(false);
	if ( SSL_ERROR_WANT_READ != (int)(ambient.eax_) )
	{
		auto& http_package_send = GClass::HttpPackageSend::GetMe();
		http_package_send.EndRecvHttp();
	}
	
	return hooker.GetCodeOrig();
}

void* Hooker_ModifyMatchTime( IHooker& hooker, JmpHookerAmbient& ambient )
{
	using namespace GAddr;
	if (IsUnValidPtr(ambient.edi_))
	{
		assert(false);
		return hooker.GetCodeOrig();
	}
	if ( g_pSetMatchTimeAddr != ambient.edi_ )
	{
		if ( !IsUnValidPtr(g_pSetMatchTimeAddr) )
		{
			LOG_O(Log_debug) << "���ñ�������ʱ��֮�����ַ��һ����֮ǰ��" << g_pSetMatchTimeAddr << " ֮��" << ambient.edi_;
		}

		g_pSetMatchTimeAddr = ambient.edi_;
	}
	return hooker.GetCodeOrig();
}

void Hook( const char* hooker_name, DWORD dwHookAddr,LPVOID pfun)
{
	try
	{
		if ( !CmnX_AntiHookCheck::GetRealMe().AddHookCodeInfo(hooker_name, (const char*)dwHookAddr) )
		{
			assert(false);
			return;
		}
		unsigned char oldcode;
		ReadProcessMemory((void*)-1,(void*)dwHookAddr,&oldcode,1,NULL);
		unsigned char code = 0xe9;

		if( oldcode == code )
		{
			return ;
		}
		WriteProcessMemory((void*)-1,(void*)dwHookAddr,&code,1,NULL);

		DWORD dwDoHookAddr = (DWORD)(void*)pfun;

		DWORD dwcAddr = dwDoHookAddr - dwHookAddr - 1 - 4;

		WriteProcessMemory((void*)-1,(void*)(dwHookAddr+1),&dwcAddr,4,NULL);
	}
	catch (...)
	{
		MessageBoxA(NULL,"������","������",MB_OK);
	}
}

//////////////////////////////////////////////////////////////////////////
void* Hooker_GainSslHandle( IHooker& hooker, JmpHookerAmbient& ambient )
{
	/*if (IsUnValidPtr(ambient.edx_))
	{
		assert(false);
		return hooker.GetCodeOrig();
	}
	//LOG_ENTER_FUNC;
	//LOG_O(Log_trace) << "sll handle��֮ǰ��" << GAddr::g_hSslHandle << " ֮��" << ambient->edx_;
	GAddr::g_hSslHandle = ambient.edx_;*/
	GAddr::g_hSslHandle = *(int*)ambient.esp_;
	return hooker.GetCodeOrig();
}
//////////////////////////////////////////////////////////////////////////

//Init code hooker
bool InitCodeHooker()
{
	//return true;
	using namespace GAddr;
	auto& hooker_factory = HookerFactory::GetMe();
	//game main wnd
	static auto hooker_gain_main_wnd_handle = hooker_factory.CreateCodeHooker<
		(void*)(int)g_pHookForGainMainWndHandle_>("g_pHookForGainMainWndHandle_",
		Hooker_GainMainWndHandle, false);
	//http send call
	static auto hooker_http_send_call = hooker_factory.CreateCodeHooker<
		(void*)(int)g_pHttpSendCall_>("g_pHttpSendCall_",
		Hooker_HttpSendCall, false);
	//recv call
	static auto hooker_recv_call = hooker_factory.CreateCodeHooker<
		(void*)(int)g_pHookRecvCallAddr_>("g_pHookRecvCallAddr_",
		Hooker_RecvCall, false);
	/*static auto hooker_recv_call = hooker_factory.CreateCodeHooker<
		(void*)(int)g_pHookRecvCallAddr_>("g_pHookRecvCallAddr_",
		Hooker_RecvCall, false);
	static auto hooker_recv_call1 = hooker_factory.CreateCodeHooker<
		(void*)(int)g_pHookRecvCallAddr1_>("g_pHookRecvCallAddr1_",
		Hooker_RecvCall, false);
	static auto hooker_recv_call2 = hooker_factory.CreateCodeHooker<
		(void*)(int)g_pHookRecvCallAddr2_>("g_pHookRecvCallAddr2_",
		Hooker_RecvCall, false);
	static auto hooker_recv_call3 = hooker_factory.CreateCodeHooker<
		(void*)(int)g_pHookRecvCallAddr3_>("g_pHookRecvCallAddr3_",
		Hooker_RecvCall, false);*/
	//after GetDeviceState
	static auto hooker_after_GetDeviceState = hooker_factory.CreateCodeHooker<
		(void*)(int)g_pHookAfterGetDeviceState_>("g_pHookAfterGetDeviceState_",
		Hooker_AfterGetDeviceState, false);
	//������������������ʱȡ��������Ϊ�����˹��������ӱ������ص�ѡ�������Խ����ʱ��������
	static auto hooker_animation_feature = hooker_factory.CreateCodeHooker<
		(void*)(int)g_pHookAnimationFeature_>("g_pHookAnimationFeature_",
		Hooker_AnimationFeature, false);
	static auto hooker_top_cmd_fn = hooker_factory.CreateCodeHooker<
		(void*)(int)g_pHookTopCmdFn>("g_pHookTopCmdFn",
		Hooker_AnimationFeature, false);

	//��dinput��Ϊ��̨ģʽ�͹���ģʽ
	{
		//BYTE model = DISCL_NONEXCLUSIVE | DISCL_BACKGROUND;
		BYTE bCode[] = {0x6a,0x0a,0x90,0x90};
		static_assert(sizeof(bCode) == 4, "");
		WriteMemory_AntiCrc("g_pHookDxInputModel", (void*)g_pHookDxInputModel, bCode, sizeof(bCode));
	}

	//hook��Ⱦ�̣߳�����CPU
	static auto hooker_render_thr_sleep = hooker_factory.CreateCodeHooker<
		(void*)(int)g_pHookRenderThd_Sleep>("g_pHookRenderThd_Sleep",
		Hooker_RenderThd_Sleep, false);

	//��Ϸ���̵߳���SSL_read���յ�һ��������HTTP����ִ�еĵط�
	static auto hooker_after_read_full_http_package = hooker_factory.CreateCodeHooker<
		(void*)(int)g_pHookAfterGameReadFullHttpPackage>("g_pHookAfterGameReadFullHttpPackage",
		Hooker_AfterReadFullHttpPackage, false);
	//�����ʱ��ִ��
	/*static auto hooker_after_read_full_http_package_by_error = hooker_factory.CreateCodeHooker<
		(void*)(int)g_pHookAfterGameReadFullHttpPackage_ByError>(
		Hooker_AfterReadFullHttpPackageByError, false);*/
	//////////////////////////////////////////////////////////////////////////
	static auto hooker_gain_ssl_handle = hooker_factory.CreateCodeHooker<
		(void*)(int)g_pHookGainSslHandle>("g_pHookGainSslHandle",
		Hooker_GainSslHandle, false);
	//////////////////////////////////////////////////////////////////////////
	return true;
}