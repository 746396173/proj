#include "stdafx.h"
#include <CmnAntiCheck/CmnRbuThread.h>
#include <CmnMix/Cmn_Hooker.h>
#include <CD_CommonFiles/Data/CD_PT_Updates.h>
#include <CD_CommonFiles/Data/CD_Structs.h>
#include <CD_CommonFiles/Data/CD_UsefulFns.h>
#include <Common/Toolhelp.h>
#include <Common/UsefulClass.h>
#include <afxmt.h>
#include <CommonX/CmnX_DllApi.h>
#include "FuncObjC.h"

//////////////////////////////////////////////////////////////////////////
//*************�̷߳����ʼ�************************************************
/*
CryGame.dll�ᴴ��2���̣߳�����һ���������ֹ�ˡ�
TenRpcs.dll���̶߳����������Ϸ�����У���ʱ�Ῠ�����������
*/
//////////////////////////////////////////////////////////////////////////
//*********************ntdll*********************
//���Ǹ�crc�̡߳�
pt_dword	g_Ntdll_offset = 0x2233B;
//////////////////////////////////////////////////////////////////////////
//*********************TenSLX*********************
//�����ǷǷ��̡߳��ᴴ��3���̣߳����������̵߳ĵ�ַ��һ���ġ���Ҫȫ���ص���
pt_cdword	g_slx_offset1 = 0x1bf994;	//�������߳�
pt_cdword	g_slx_offset2 = 0x3cdb0;
//////////////////////////////////////////////////////////////////////////
//*********************TerSafe*********************
//TerSafe.dll �ܹ��ᴴ��11���̣߳�����һ���߳�ִ��û���ξ���ֹ�ˣ�ʣ�µ�10���߳��ǻ�Ծ�ġ�����ֻ��һ���̲߳��ܹ�����Sleep��
pt_cdword	g_TerSafe_offset1 = 0x42c0;
pt_cdword	g_TerSafe_offset2 = 0x10440;
pt_cdword	g_TerSafe_offset3 = 0x1c990;
pt_cdword	g_TerSafe_offset4 = 0x260a0;
pt_cdword	g_TerSafe_offset5 = 0x2f8c0;
pt_cdword	g_TerSafe_offset6 = 0x73930;
pt_cdword	g_TerSafe_offset7 = 0x75A90;
pt_cdword	g_TerSafe_offset8 = 0x86E5B;
pt_cdword	g_TerSafe_offset9 = 0x86E69;
/*
g_a_lpka_terSafe_CanNotSleep_,�ɵ�����߳�һ�������������
Ȼ������žͱ��Ӻ������ˣ���������ϵͳ�����Ҳ�ע���κ�DLL��Ҳ���������������
*/
extern pt_cdword g_a_lpka_terSafe_CanNotSleep_;
//����һ������ֹ���߳�
//pt_cdword	g_TerSafe_offset11 = 0x70f90;
//////////////////////////////////////////////////////////////////////////
//*********************MHOClientBase*********************
//�ᴴ��5���̣߳�����һ���߳��ڳ��ڱ���ֹ�ˡ�
//���Ǹ�crc�̡߳�����߳����л���������һ����Ҳ�����߳���ڵ�ַ��ߵ��Ǹ�������߳������ľ���CRC��������OD���ڴ���ʶϵ㣬��ʱ���ϲ�����
extern pt_cdword g_a_lpka_cry_base_crc_;
//�������߳�Ӧ�ò��������⣬��Ϊ��Ϸ���а����ˣ��ڸ�����ֶ��ü����ˣ��������̵߳��л�����һ����2�Σ���һ����4�Ρ�
pt_cdword g_CryBase_thrd1_ = 0x8C9375;		//�������߳�
extern pt_cdword g_a_lpka_cry_base_thrd_;
//////////////////////////////////////////////////////////////////////////
//*********************TCJ*********************
//�ᴴ�������̣߳�����һ���̺߳ܿ������ֹ
//�߳��л������ߵ��Ǹ�
pt_cdword g_TCJ_thrd1 = 0x8C74D;
//////////////////////////////////////////////////////////////////////////
//*********************TenRpcs*********************
//�ᴴ��4���߳�
//�л������ڶ�
//g_TenRpcs_thrd2  g_TenRpcs_thrd3�������߳�ѡ���ɫʱ����У�ѡ���ɫ�����ʱҲ���С�
pt_cdword g_TenRpcs_thrd2 = 0xAFD90;
//�л���������
pt_cdword g_TenRpcs_thrd3 = 0x54A71;
//�����������߳̽�����Ϸ��Ż��У�������Ҫ�ŵ������߳�ȥ����
//�л��������
pt_cdword g_TenRpcs_thrd1 = 0x2957;
//�л���������
pt_cdword g_TenRpcs_thrd4 = 0x1802D;
//////////////////////////////////////////////////////////////////////////
//*********************MHOClient*********************
extern pt_cdword	g_c_lpka_mhoclient_start_thrd_;
extern pt_cdword	g_c_lpka_mhoclient_start_thrd1_;
extern pt_cdword	g_c_lpka_mhoclient_start_thrd2_;
extern pt_cdword	g_c_lpka_mhoclient_start_thrd3_;
extern pt_cdword	g_c_lpka_mhoclient_no_show_npc_;
extern pt_cdword	g_c_lpka_mhoclient_render_thrd_;
//////////////////////////////////////////////////////////////////////////
//*********************CryGame*********************
//����߳��ǿ��Ըɵ���
extern pt_cdword	g_c_lpka_crygame_start_thrd_;
//g_c_lpka_crygame_start_thrd1_�߳�û��þ���ֹ�ˡ�
extern pt_cdword	g_c_lpka_crygame_start_thrd1_;
//һ��ᴴ��9���̣߳�����һ�����ֹ�ˡ�
extern pt_cdword	g_c_lpka_crygame_start_thrd2_;
//�����ڵ�ַֻ��һ���̣߳��ܿ����ֹ������������������g_c_lpka_crygame_start_thrd2_�ġ�
extern pt_cdword	g_c_lpka_crygame_start_thrd3_;
//////////////////////////////////////////////////////////////////////////
//*********************CrossShell*********************
pt_cdword g_CrossShell_terminate_thrd = 0x7640;
//////////////////////////////////////////////////////////////////////////
//*********************SSOPlatform*********************
//ֻ��һ���̴߳���û��ñ���ֹ�ˡ�
pt_cdword g_SSOPlatform_thrd = 0x7CC85;
//////////////////////////////////////////////////////////////////////////
//*********************rasman*********************
//ֻ������һ���̡߳����Ǹ�ϵͳdll�����ܴ��ڼ��������⡣
//pt_cdword g_Rasman_thrd = 0x32FB;
//////////////////////////////////////////////////////////////////////////
//*********************iips*********************
//ֻ������һ���̡߳�
pt_cdword g_Iips_thrd = 0x3BF0;
//////////////////////////////////////////////////////////////////////////
//*********************MMDevApi*********************
//ֻ������һ���̡߳����Ǹ�ϵͳdll�����ܴ��ڼ��������⡣
//pt_cdword g_MMDevApi_thrd = 0x27E1;
//////////////////////////////////////////////////////////////////////////
//*********************netbios*********************
//ֻ������һ���̡߳����Ǹ�ϵͳdll�����ܴ��ڼ��������⡣
//pt_cdword g_netbios_thrd = 0x1C2F;
//////////////////////////////////////////////////////////////////////////
struct ModuleOffsetHandlerHlpBase : ModuleOffsetHandler{
	ModuleOffsetHandlerHlpBase(){
		OffsetsT offsets;
		offsets.insert(stOffsetInfoT(0, -1));
		AddModuleOffset("BugTrack.dll", offsets);
		AddModuleOffset("BugReport.dll", offsets);
		AddModuleOffset("BugTrace.dll", offsets);
		AddModuleOffset("SSOPlatform.dll", offsets);
		AddModuleOffset("TenProxy.dll", offsets);
		AddModuleOffset("iips.dll", offsets);
		AddModuleOffset("ifs2.dll", offsets);
		AddModuleOffset("CrossShell.dll", offsets);
		AddModuleOffset("TASWTLoginHelper.dll", offsets);
		/*offsets.clear();
		offsets.insert(stOffsetInfoT(g_c_lpka_crygame_start_thrd2_, -1));
		offsets.insert(stOffsetInfoT(g_c_lpka_crygame_start_thrd3_, -1));*/
		AddModuleOffset("CryGame.dll", offsets);
	}
};
struct ModuleOffsetHandlerHlp_NtCreateThrd : ModuleOffsetHandlerHlpBase{
};
struct ModuleOffsetHandlerHlp_Msvc : ModuleOffsetHandler{
};
ModuleOffsetHandlerHlp_NtCreateThrd	g_do_pre_create_thrd_nt_;
ModuleOffsetHandlerHlp_Msvc	g_do_pre_create_thrd_msvc_;

class HandleRubThread_ByModuleOffset : public HandleRubThread{
};

class HandleRubThread_OnlyDoSleep : public HandleRubThread, public Singleton<HandleRubThread_OnlyDoSleep, Singleton_MakeMe>{
};

#ifdef _DEBUG
struct stRubThrdCntMgr{
	HandleRubThread		mhoclient_start_;
	HandleRubThread		mhoclient_render_;
};
#endif

//HandleMsvcrThrd ���������Ҳ��Щƫ����Ҫ��ע
bool DoTraCheckThread(){
	/*
	GetProcAddress(LoadLibraryA("ntdll.dll"),"memcpy") - 5 == 0x20233B + LoadLibraryA("ntdll.dll");
	$ ==>    7783233B                      90              NOP
	$+1      7783233C                      90              NOP
	$+2      7783233D                      90              NOP
	$+3      7783233E                      90              NOP
	$+4      7783233F                      90              NOP
	$+5      77832340 ntdll.memcpy       - E9 66674392     JMP game.09C68AAB                        ; memcpy
	$+A      77832345                      8B75 0C         MOV ESI, DWORD PTR SS:[EBP+C]
	$+D      77832348                      8B4D 10         MOV ECX, DWORD PTR SS:[EBP+10]
	*/
	auto h_ntdll = LoadLibraryA("ntdll.dll");
	if (!h_ntdll)
	{
		assert(false);
		return false;
	}
	auto fn_memcpy = GetProcAddress(h_ntdll, "memcpy");
	if (!fn_memcpy)
	{
		assert(false);
		return false;
	}
	g_Ntdll_offset = (pt_cdword)fn_memcpy - 5 - (pt_cdword)h_ntdll;
	//////////////////////////////////////////////////////////////////////////
	ModuleOffsetHolder module_offset;
	ModuleOffsetHolder::OffsetsT offsets;

	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_a_lpka_cry_base_crc_, 1));
	//offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_CryBase_thrd1_, 2));
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_a_lpka_cry_base_thrd_, 1));
	module_offset.AddModuleOffset("MHOClientBase.dll", offsets);

	offsets.clear();
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_slx_offset1, 2));
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_slx_offset2, 1));
	module_offset.AddModuleOffset("TenSLX.dll", offsets);

	offsets.clear();
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_TerSafe_offset1, 1));
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_TerSafe_offset2, 1));
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_TerSafe_offset3, 1));
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_TerSafe_offset4, 1));
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_TerSafe_offset5, 1));
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_TerSafe_offset6, 1));
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_TerSafe_offset7, 1));
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_TerSafe_offset8, 1));
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_TerSafe_offset9, 1));
	//offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_a_lpka_terSafe_CanNotSleep_, 1));
	module_offset.AddModuleOffset("TerSafe.dll", offsets);

	offsets.clear();
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_Ntdll_offset, 1));
	module_offset.AddModuleOffset("ntdll.dll", offsets);

	offsets.clear();
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_TCJ_thrd1, 1));
	module_offset.AddModuleOffset("TCJ.dll", offsets);

	offsets.clear();
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_TenRpcs_thrd2, 1));
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_TenRpcs_thrd3, 1));
	//��ʱע�͵�
	//module_offset.AddModuleOffset("TenRpcs.dll", offsets);

	offsets.clear();
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_Iips_thrd, 1));
	//module_offset.AddModuleOffset("iips.dll", offsets);

	//�����ϵͳ�̣߳�Ӧ���������ġ�
	/*offsets.clear();
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_Rasman_thrd, 1));
	module_offset.AddModuleOffset("rasman.dll", offsets);*/

	//�����ϵͳ�̣߳�Ӧ���������ġ�
	/*offsets.clear();
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_MMDevApi_thrd, 1));
	module_offset.AddModuleOffset("MMDevApi.dll", offsets);*/

	//����ÿ̨��������������̵߳ġ�
	/*offsets.clear();
	offsets.insert(ModuleOffsetHolder::stOffsetInfoT(g_netbios_thrd, 1));
	module_offset.AddModuleOffset("netbios.dll", offsets);*/
	//////////////////////////////////////////////////////////////////////////
	LOG_O(Log_debug) << "��ʼ�������������߳�";
	HandleRubThread_ByModuleOffset rub_thrd;
	auto res = rub_thrd.DoAllThrdSleepByOffset(1000 * 60 * 3, module_offset, DummySleep);
	rub_thrd.ClrAll();
	LOG_O(Log_debug) << "���������̴߳�����:" << res;
	return res;
	//////////////////////////////////////////////////////////////////////////
}

CEvent*	g_event_handle_rub_thrd_ = nullptr;
bool g_handle_rub_thrd_end_ = false;
#ifdef _DEBUG
stRubThrdCntMgr	g_rub_thrd_cnt_mgr_;
#endif

void BeginHandleRubThrd(){
	if (!g_event_handle_rub_thrd_)
	{
		assert(false);
		return;
	}
	g_event_handle_rub_thrd_->SetEvent();
}
void HandleSleepRubThrd(CEvent* the_event){
	assert(the_event);
	the_event->Lock();
	the_event->Unlock();
	LOG_O(Log_trace) << "��ʼ������Щ�����������߳�";
	auto& rub_thrd = HandleRubThread_OnlyDoSleep::GetMe();
	assert(4 == g_rub_thrd_cnt_mgr_.mhoclient_render_.GetThrdTotalCnt());

	auto cnt = rub_thrd.GetThrdTotalCnt();
	int succeed_cnt = 0;
	auto res = TimerDo_Sleep(100, 1000 * 60, [&rub_thrd, &succeed_cnt](){
		succeed_cnt += rub_thrd.DoThrdSleep();
		return rub_thrd.GetUnhandledThrdCnt() <= 0;
	});
	if (res)
		LOG_O(Log_trace) << "��Щ�����������̴߳�����ϣ��ܸ�����" << cnt << " �ɹ�������" << succeed_cnt;
	else
	{
		LOG_O(Log_debug) << "��Щ�����������߳�δ�ܴ���ɹ�";
		assert(false);
		GetIoService().post([](){
			throw CmnTerminateProcessException();
		});
	}

	HandleRubThread_ByModuleOffset the_rub_thrd;
	ModuleOffsetHolder the_module_offset;
	ModuleOffsetHolder::OffsetsT the_offsets;
	//�����̸߳��ɵ���MHOClient.exeֻ��һ���̣߳��������̣߳������̶߳�����_beginthread�����ġ�
	the_offsets.insert(ModuleOffsetHolder::stOffsetInfoT(0, -1));
	the_module_offset.AddModuleOffset("MHOClient.exe", the_offsets);

	LOG_O(Log_debug) << "��ʼ����ʣ�µ������߳�";
	auto the_res = the_rub_thrd.DoAllThrdSleepByOffset(1000 * 60 * 2, the_module_offset, ::Sleep);
	//�ж�������߳���MHOClient.exeģ�����Ƿ�Ψһ
	if (the_res)
	{
		/*if (!TimerDo_Sleep(500, 5000, [&](){
			if (the_rub_thrd.DoAllThrdSleepByOffset(1000, the_module_offset, ::Sleep))
				return false;
			return true;
		}))*/
		if (the_rub_thrd.DoAllThrdSleepByOffset(1000, the_module_offset, ::Sleep))
			assert(!"ʣ�µ������߳̾�Ȼ����");
	}
	the_rub_thrd.ClrAll();
	if (the_res)
	{
		LOG_O(Log_debug) << "ʣ�µ������̴߳���ɹ�";
	}
	else
	{
		LOG_O(Log_debug) << "ʣ�µ������߳�δ�ܴ���ɹ�";
		assert(false);
		GetIoService().post([](){
			throw CmnTerminateProcessException();
		});
	}

	while (true)
	{
		rub_thrd.DoThrdSleep();
		::Sleep(3000);
	}

	rub_thrd.ClrAll();
}

void HandleAddRubThrdSleep(DWORD thrd_id, void* start_addr, pt_csz modue_name){
	if (g_handle_rub_thrd_end_)
	{
		assert(false);
		return;
	}
	LOG_O(Log_trace) << "HandleAddRubThrdSleep���߳�ID��" << std::dec << thrd_id << " start_addr:" << start_addr << " ģ������" << modue_name;
	auto& rub_thrd = HandleRubThread_OnlyDoSleep::GetMe();
	rub_thrd.AddThrdId(thrd_id);
}

void HandleBeginThrd_MhoClient_Start(stCD_Common_ThrdStart* thrd_obj, DWORD thrd_id)
{
	if (IsUnValidPtr(thrd_obj->vtbl_))
	{
		assert(false);
		return;
	}
	auto the_run_fn = (pt_cdword)thrd_obj->vtbl_->fn_run_thrd_;
	
	if (g_c_lpka_mhoclient_no_show_npc_ == the_run_fn)
	{
		//�ܹ�������10���̣߳���Щ�̶߳����Ըɵ��������ڳ��������ֻ����ʾ���ֺͳƺţ��ڸ����е�NPCֻ��ͷ����ʾ�������������ġ�
		//����ȫ��������� �ε���� ������� �������� �򲻵�����������������BOSSҲ�򲻵���
		//return HandleAddRubThrdSleep(thrd_id, (pt_pvoid)the_run_fn, "MHOClient.exe_run0");
	}
#ifdef _DEBUG
	else if (g_c_lpka_mhoclient_render_thrd_ == the_run_fn)
	{
		//�ܹ�������4���̣߳�ȫ�����˾ͻ����������Ӧ������Ⱦ�̣߳�4��ͬʱ��Ⱦ��ֻҪ��һ��������û�¡�����Ϊ��3��û�£���ʵ��Ȼ��ֻ��3��������Ϸ��ֱ�Ӻ�����
		g_rub_thrd_cnt_mgr_.mhoclient_render_.AddThrdId(thrd_id);
		auto cnt = g_rub_thrd_cnt_mgr_.mhoclient_render_.GetThrdTotalCnt();
		assert(cnt <= 4);
		//return HandleAddRubThrdSleep(thrd_id, (pt_pvoid)the_run_fn, "MHOClient.exe_run1");
	}
#endif
	//else if (0x0045E120 == the_run_fn)
	{
		//ֻ�ᴴ��һ���̣߳�����̻߳����ܸ㣬������������������������ص�ͼ��ʱ�������⣬��ƽ��û���⡣
		//return HandleAddRubThrdSleep(thrd_id, (pt_pvoid)the_run_fn, "MHOClient.exe_run2");
	}
	//else if (0x00504920 == the_run_fn)
	{
		//�ܹ�������3���̣߳�ȫ�����ܸ㣬�����������ͼ��ʱ��Ҳ������������߳��е��κ�һ�����㣬���������
		//return HandleAddRubThrdSleep(thrd_id, (pt_pvoid)the_run_fn, "MHOClient.exe_run3");
	}
	//else if (0x00504600 == the_run_fn)
	{
		//�ܹ�������2���̣߳�������Ҳ���ܸ㣬��Ȼ��ɫ����û���⣬���ǽ�����Ϸ��ʱ����������ͼ��ʱ��Ҳ������������߳��е��κ�һ�����㣬���������
		//return HandleAddRubThrdSleep(thrd_id, (pt_pvoid)the_run_fn, "MHOClient.exe_run4");
	}
	//else if (0x0089BFB0 == the_run_fn)
	{
		//�ܹ�������һ���̣߳����ܸ������Ȼѡ���ɫ����û���⣬��������Ϸʱ���Ῠ��loading�ĵط���
		//return HandleAddRubThrdSleep(thrd_id, (pt_pvoid)the_run_fn, "MHOClient.exe_run5");
	}
	//else if (0x00874910 == the_run_fn)
	{
		//�ܹ�������һ���̣߳����ܸ������Ȼѡ���ɫ����û���⣬��������Ϸʱ���Ῠ��loading�ĵط���
		//return HandleAddRubThrdSleep(thrd_id, (pt_pvoid)the_run_fn, "MHOClient.exe_run6");
	}

	LOG_O(Log_trace) << "HandleBeginThrd_MhoClient_Start:" << thrd_obj << " thrd_id:" << std::dec << thrd_id
		<< std::hex
		<< " vtbl:" << thrd_obj->vtbl_ << " run_fn:" << thrd_obj->vtbl_->fn_run_thrd_ <<
		" on_exit:" << thrd_obj->vtbl_->fn_on_exit_thrd_;
}

void HandleBeginThrd_CryGame_Start(stCD_CryGame_ThrdStart* thrd_obj, void* start_addr, DWORD thrd_id)
{
	LOG_O(Log_trace) << "HandleBeginThrd_CryGame_Start:" << thrd_obj << " thrd_id:" << std::dec << thrd_id
		<< std::hex
		<< " start_addr:" << start_addr
		<< " vtbl:" << thrd_obj->vtbl_ << " run_fn:" << thrd_obj->vtbl_->fn_run_thrd_;
}

void HandleBeginThrd_CryGame_Start1(stCD_Common_ThrdStart* thrd_obj, void* start_addr, DWORD thrd_id)
{
	LOG_O(Log_trace) << "HandleBeginThrd_CryGame_Start1:" << thrd_obj << " thrd_id:" << std::dec << thrd_id
		<< std::hex
		<< " start_addr:" << start_addr
		<< " vtbl:" << thrd_obj->vtbl_ << " run_fn:" << thrd_obj->vtbl_->fn_run_thrd_ <<
		" on_exit:" << thrd_obj->vtbl_->fn_on_exit_thrd_;
}

/*
Cmnx_Mutex_CriticalSection g_cri_section_thrd_id_;
NameList<int, std::vector<int> > g_the_thrd_ids_;*/
void HandleMsvcrThrd(void* start_addr, DWORD thrd_id, unsigned stack_size, void* arg_list,
	boost::optional<void*> security, boost::optional<unsigned> init_flag, boost::optional<unsigned*> ptr_thrd_id)
{
	auto hmodule = ModuleFromAddress(start_addr);
	if (!hmodule)
	{
		assert(false);
		return;
	}
	char buffer[MAX_PATH];
	if (!GetModuleName(hmodule, buffer, sizeof(buffer)))
		return;

	const auto addr_offset = (pt_cdword)start_addr - (pt_cdword)hmodule;

	/*BOOST_SCOPE_EXIT_ALL(thrd_id){
		Cmnx_Lockable lock(g_cri_section_thrd_id_);
		auto old_size = g_the_thrd_ids_.Size();
		g_the_thrd_ids_.Add(thrd_id);
		auto new_size = g_the_thrd_ids_.Size();
		if (old_size == new_size)
		{
			LOG_O(Log_debug) << "�Ѿ����ڸ��߳�ID�ˣ�" << std::dec << thrd_id;
		}
		else
		{
			LOG_O(Log_trace) << "���ڵ��߳�����Ϊ��" << std::dec << new_size;
		}
	};*/

	if (0 == _stricmp(buffer, "MHOClient.exe"))
	{
		if (!IsUnValidPtr(arg_list))
		{
			if (g_c_lpka_mhoclient_start_thrd_ == (pt_cdword)start_addr)
				return HandleBeginThrd_MhoClient_Start((stCD_Common_ThrdStart*)arg_list, thrd_id);
			else if (g_c_lpka_mhoclient_start_thrd1_ == (pt_cdword)start_addr)
			{
				//�����ڴ����������̣߳��������̺߳��񶼲���Ծ��������Ϸ�����ˣ�Ҳû���й���
				//return HandleBeginThrd_MhoClient_Start1((stCD_MhoClient_ThrdStart1*)arg_list, thrd_id);
				return HandleAddRubThrdSleep(thrd_id, start_addr, "MHOClient.exe_start_thrd1");
			}
			else if (g_c_lpka_mhoclient_start_thrd2_ == (pt_cdword)start_addr)
			{
				//�����ڴ������߸��̣߳���ѡ���ɫ����ʱ���߸��߳̾��Ѿ�ȫ�����ˡ�
				//return HandleBeginThrd_MhoClient_Start2((stCD_MhoClient_ThrdStart2*)arg_list, thrd_id);
				return HandleAddRubThrdSleep(thrd_id, start_addr, "MHOClient.exe_start_thrd2");
			}
			else if (g_c_lpka_mhoclient_start_thrd3_ == (pt_cdword)start_addr)
			{
				//������ֻ������һ���̣߳�����̺߳��񲻻�Ծ��������Ϸ�����ˣ�Ҳû���й���
				//return HandleBeginThrd_MhoClient_Start3((stCD_MhoClient_ThrdStart3*)arg_list, thrd_id);
				return HandleAddRubThrdSleep(thrd_id, start_addr, "MHOClient.exe_start_thrd3");
			}
			assert(false);
		}
		else
		{
			//ֻ��һ���̣߳���ں�����Զ�����У�"������ڴ�С��2G����������Ϸ�����������������Ҫ���Ƿ����������Ϸ��"��
			//����̲߳��ܸ㣬������������������Ⱦ�̡߳�
			//����߳̾��������NtQueryInformationProcess(ProcessBasicInformation)����������̲߳�ֻ���𵽴����̵߳����á�
			//return HandleAddRubThrdSleep(thrd_id, start_addr, "MHOClient.exe_start_thrd_else");
		}
#ifdef _DEBUG
		g_rub_thrd_cnt_mgr_.mhoclient_start_.AddThrdId(thrd_id);
		assert(g_rub_thrd_cnt_mgr_.mhoclient_start_.GetThrdTotalCnt() <= 12 + 1);
#endif
	}
	else if (0 == _stricmp(buffer, "CryGame.dll"))
	{
		//�ܹ��ᴴ�������̡߳�
		assert((pt_cdword)hmodule == CDF_GetCryGameBaseAddr());
		//g_c_lpka_crygame_start_thrd1_�߳�û��þ���ֹ�ˡ�
		if (g_c_lpka_crygame_start_thrd1_ != addr_offset)
		{
			return HandleAddRubThrdSleep(thrd_id, start_addr, "CryGame.dll");
		}
		/*else if (g_c_lpka_crygame_start_thrd1_ == addr_offset)
		{
			return HandleBeginThrd_CryGame_Start1((stCD_Common_ThrdStart*)arg_list, start_addr, thrd_id);
		}
		else if (g_c_lpka_crygame_start_thrd_ == addr_offset)
		{
			return HandleBeginThrd_CryGame_Start((stCD_CryGame_ThrdStart*)arg_list, start_addr, thrd_id);
			return HandleAddRubThrdSleep(thrd_id, start_addr, "CryGame.dll");
		}*/
	}
	else if (0 == _stricmp(buffer, "iips.dll"))
	{
		return HandleAddRubThrdSleep(thrd_id, start_addr, "iips.dll");
	}
	else if (0 == _stricmp(buffer, "CrossShell.dll"))
	{
		if (g_CrossShell_terminate_thrd != addr_offset)
			return HandleAddRubThrdSleep(thrd_id, start_addr, "CrossShell.dll");
	}
	else if (0 == _stricmp(buffer, "CryAction.dll"))
	{
		return HandleAddRubThrdSleep(thrd_id, start_addr, "CryAction.dll");
	}

	if (security)
	{
		LOG_O(Log_debug) << "��Ϸ�������̣߳�start_addr:" << start_addr << " thrd_id:" << std::dec << thrd_id << " ģ�飺" << buffer
			<< " stack_size:" << stack_size << " arg_list:" << arg_list <<
			" security:" << *security << " init_flag:" << *init_flag << " ptr_thrd_id:" << *ptr_thrd_id;
	}
	else
	{
		LOG_O(Log_debug) << "��Ϸ�������̣߳�start_addr:" << start_addr << " thrd_id:" << std::dec << thrd_id << " ģ�飺" << buffer
			<< " stack_size:" << stack_size << " arg_list:" << arg_list;
	}
}

void* Hooker_beginthread(IHooker& hooker, JmpHookerAmbient& ambient)
{
	auto start_addr = ambient.EspParamAs<1, void*>();
	if (IsUnValidPtr(start_addr))
	{
		assert(false);
		return hooker.GetCodeOrig();
	}
	typedef void(*StartFn)(void*);
	typedef uintptr_t (__cdecl *Fn_beginthread)(_In_ void(__cdecl* _StartAddress) (void *), _In_ unsigned _StackSize, _In_opt_ void * _ArgList);
	auto the_fn = (Fn_beginthread)hooker.GetCodeOrig();
	auto stack_size = ambient.EspParamAs<2, unsigned>();
	auto arg_list = ambient.EspParamAs<3, void*>();
	char module_name[MAX_PATH];
	auto pre_res = g_do_pre_create_thrd_msvc_.DoPreCreateThrd_Cdecl((StartFn&)start_addr, arg_list, nullptr, module_name, MAX_PATH);
	auto res = the_fn((StartFn)start_addr, stack_size, arg_list);
	ambient.eax_ = res;

	if (!pre_res)
	{
		if (res)
			HandleMsvcrThrd(start_addr, GetThreadId((HANDLE)res), stack_size, arg_list,
			boost::optional<void*>(), boost::optional<unsigned>(), boost::optional<unsigned*>());
		else
			HandleMsvcrThrd(start_addr, 0, stack_size, arg_list,
			boost::optional<void*>(), boost::optional<unsigned>(), boost::optional<unsigned*>());
	}
	return NakedRetP0;
}

void* Hooker_beginthreadex(IHooker& hooker, JmpHookerAmbient& ambient)
{
	auto start_addr = ambient.EspParamAs<3, void*>();
	if (IsUnValidPtr(start_addr))
	{
		assert(false);
		return hooker.GetCodeOrig();
	}
	typedef unsigned(__stdcall* StartFn) (void *);
	typedef uintptr_t(__cdecl *Fn_beginthread)(_In_opt_ void * _Security, _In_ unsigned _StackSize,
		_In_ unsigned(__stdcall * _StartAddress) (void *), _In_opt_ void * _ArgList,
		_In_ unsigned _InitFlag, _Out_opt_ unsigned * _ThrdAddr);
	auto the_fn = (Fn_beginthread)hooker.GetCodeOrig();
	unsigned thrd_id = 0;
	auto security = ambient.EspParamAs<1, void*>();
	auto stack_size = ambient.EspParamAs<2, unsigned>();
	auto arg_list = ambient.EspParamAs<4, void*>();
	auto init_flag = ambient.EspParamAs<5, unsigned>();
	char module_name[MAX_PATH];
	auto pre_res = g_do_pre_create_thrd_msvc_.DoPreCreateThrd_Std((StartFn&)start_addr, arg_list, nullptr, module_name, MAX_PATH);
	auto res = the_fn(security, stack_size, (StartFn)start_addr, arg_list, init_flag, &thrd_id);
	auto ptr_thrd_id = ambient.EspParamAs<6, unsigned*>();
	if (ptr_thrd_id)
		*ptr_thrd_id = thrd_id;
	ambient.eax_ = res;

	if (!pre_res)
	{
		if (res)
			HandleMsvcrThrd(start_addr, thrd_id, stack_size, arg_list, security, init_flag, ptr_thrd_id);
		else
			HandleMsvcrThrd(start_addr, 0, stack_size, arg_list, security, init_flag, ptr_thrd_id);
	}
	return NakedRetP0;
}

void HandleNtCreateThread(char module_name[MAX_PATH], HMODULE the_module, void* start_addr, DWORD thrd_id){
	if (0 == _stricmp(module_name, "TenRpcs.dll"))
	{
		auto addr_offset = (pt_cdword)start_addr - (pt_cdword)the_module;
		if (g_TenRpcs_thrd4 == addr_offset)
		{
			HandleAddRubThrdSleep(thrd_id, start_addr, "TenRpcs.dll g_TenRpcs_thrd4");
		}
		else if (g_TenRpcs_thrd1 == addr_offset)
		{
			HandleAddRubThrdSleep(thrd_id, start_addr, "TenRpcs.dll g_TenRpcs_thrd1");
		}
	}
}

stDetourHooker<NtCreateThread> hooker_info_NtCreateThread_;
NTSTATUS_ WINAPI Hooker_NtCreateThread(                     // <��ز���˵��>
	__out PHANDLE ThreadHandle,     //���ش����̵߳ľ��
	__in ACCESS_MASK DesiredAccess, //�����̵߳ķ���Ȩ��
	__in_opt POBJECT_ATTRIBUTES ObjectAttributes, //ָ�����̶߳��������
	__in HANDLE ProcessHandle,      //���̾��
	__out PCLIENT_ID ClientId,      //�������̵߳�ClientId �ṹ
	__in PCONTEXT ThreadContext,    //���̵߳�ִ�л���
	__in PINITIAL_TEB InitialTeb,   //�ṩ���̵߳�TEB��ʼֵ
	__in BOOLEAN CreateSuspended    //�´������߳��Ƿ�Ҫ�ȱ�����
	){
	assert(false);
	HANDLE thrd_handle = INVALID_HANDLE_VALUE;
	//auto pre_res = HandlePreCreateThread(buffer, the_module, (void*&)StartRoutine, (pt_dword&)StartContext);
	auto res = hooker_info_NtCreateThread_.code_orig_(&thrd_handle, DesiredAccess, ObjectAttributes, ProcessHandle, ClientId, ThreadContext, InitialTeb, CreateSuspended);
	if (ThreadHandle)
		*ThreadHandle = thrd_handle;
	if (ThreadContext)
	{
		auto the_module = ModuleFromAddress((void*)ThreadContext->Eax);
		char buffer[MAX_PATH];
		buffer[0] = 0;
		GetModuleName(the_module, buffer, MAX_PATH);
		HandleNtCreateThread(buffer, the_module, (void*)ThreadContext->Eax, GetThreadId(thrd_handle));
	}
	return res;
}

stDetourHooker<NtCreateThreadEx> hooker_info_NtCreateThreadEx_;
NTSTATUS_ WINAPI Hooker_NtCreateThreadEx(
	OUT PHANDLE ThreadHandle,
	IN ACCESS_MASK DesiredAccess,
	IN POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL,
	IN HANDLE ProcessHandle,
	IN PTHREAD_START_ROUTINE StartRoutine,
	IN PVOID StartContext,
	IN ULONG CreateThreadFlags,
	IN ULONG ZeroBits OPTIONAL,
	IN ULONG StackSize OPTIONAL,
	IN ULONG MaximumStackSize OPTIONAL,
	IN PNT_PROC_THREAD_ATTRIBUTE_LIST AttributeList
	){
	HANDLE thrd_handle = INVALID_HANDLE_VALUE;
	HMODULE the_module = nullptr;
	char the_module_name[MAX_PATH];
	auto pre_res = g_do_pre_create_thrd_nt_.DoPreCreateThrd_Std((ModuleOffsetHandler::StartFn_Std&)StartRoutine, (void*&)StartContext, 
		&the_module, the_module_name, MAX_PATH);
	auto res = hooker_info_NtCreateThreadEx_.code_orig_(&thrd_handle, DesiredAccess, ObjectAttributes, ProcessHandle, 
		StartRoutine, StartContext, CreateThreadFlags,
		ZeroBits, StackSize, MaximumStackSize, AttributeList);
	if (ThreadHandle)
		*ThreadHandle = thrd_handle;
	if (StartRoutine && !pre_res)
		HandleNtCreateThread(the_module_name, the_module, StartRoutine, GetThreadId(thrd_handle));

#ifdef _DEBUG
	if (!pre_res)
	{
		if (0 != _stricmp(the_module_name, "MSVCR90.dll") && 0 != _stricmp(the_module_name, "MSVCR80.dll") && 0 != _stricmp(the_module_name, "msvcrt.dll")
			&& the_module != GlobalSetter::GetMe().GetSelfModuleHandle())
			LOG_O(Log_trace) << "Hooker_NtCreateThreadEx�����̣߳���ڵ�ַ��" << (void*)StartRoutine << " ģ������" << the_module_name;
	}
#endif
	return res;
}

stDetourHooker<NtQueryInformationProcessT> g_hooker_NtQueryInformationProcess_;
NTSTATUS_ WINAPI Hooker_NtQueryInformationProcess(IN HANDLE ProcessHandle, //���̾��
	IN PROCESSINFOCLASS InformationClass, //��Ϣ����
	OUT PVOID ProcessInformation, //����ָ��
	IN ULONG ProcessInformationLength, //���ֽ�Ϊ��λ�Ļ����С
	OUT PULONG ReturnLength OPTIONAL //д�뻺����ֽ���
	){
	//������NtQueryInformationProcess����Ϸ����·�����������������Ե��е㿨�ˣ�����CPU��δ���ߡ�
	//ProcessBasicInformation == InformationClass ȥ���󣬾Ͳ�����
	if (/*ProcessBasicInformation == InformationClass ||*/ ProcessDebugPort == InformationClass)
	{
		auto thrd_id = GetCurrentThreadId();
		auto the_module = ModuleFromAddress(GetThreadStartAddr(thrd_id));
		if (GlobalSetter::GetMe().GetSelfModuleHandle() != the_module)
		{
#ifdef _DEBUG
			if (ProcessDebugPort == InformationClass)
			{
				LOG_O(Log_debug) << "Hooker_NtQueryInformationProcess����ʧ�ܣ�ProcessDebugPort �߳�ID��" << thrd_id;
				return -1;
			}
			DWORD gwnd_thrd_id = 0;
			auto nor = FuncObj_NormalC::GetInstance();
			if (nor)
			{
				auto gwnd = nor->GetInterGWnd();
				if (gwnd)
					gwnd_thrd_id = gwnd->GetWndThrdId();
			}			
			if (gwnd_thrd_id != thrd_id || ProcessBasicInformation != InformationClass)
				LOG_O(Log_debug) << "Hooker_NtQueryInformationProcess����ʧ�ܣ�InformationClass:" << InformationClass << " �߳�ID��" << thrd_id;
#endif
			return -1;
		}
	}
	else if (ProcessImageFileName == InformationClass)
	{
		auto thrd_id = GetCurrentThreadId();
		auto the_module = ModuleFromAddress(GetThreadStartAddr(thrd_id));
		if (GlobalSetter::GetMe().GetSelfModuleHandle() != the_module)
		{
			ULONG ret_length = 0;
			auto res = g_hooker_NtQueryInformationProcess_.code_orig_(ProcessHandle, InformationClass, ProcessInformation, ProcessInformationLength, &ret_length);
			if (NT_SUCCESS(res))
			{
				if (Cmnx_Stristr((wchar_t*)ProcessInformation, L"Console.exe"))
				{
					LOG_O(Log_debug) << "Hooker_NtQueryInformationProcess����ʧ�ܣ���Ϊ��������Console.exe �߳�ID��" << thrd_id;
					if (ReturnLength)
						*ReturnLength = 0;
					return -1;
				}
			}
			if (ReturnLength)
				*ReturnLength = ret_length;
			return res;
		}
	}
	return g_hooker_NtQueryInformationProcess_.code_orig_(ProcessHandle, InformationClass, ProcessInformation, ProcessInformationLength, ReturnLength);
}

void* Hooker_Sprintf(IHooker& hooker, JmpHookerAmbient& ambient)
{
	static bool exec_once = false;
	if (exec_once)
		return hooker.GetCodeOrig();
	//JFZRBASE_SPRINTF
	struct TheSprintfP{
		char*	pScrCur;
		int		nRemainBufLen;
		char*	pScrBuf;
	};
	if (IsUnValidPtr(ambient.edi_))
	{
		//assert(false);
		return hooker.GetCodeOrig();
	}
	auto the_param = (TheSprintfP*)ambient.edi_;
	//LOG_O(Log_trace) << "Hooker_Sprintf, the_str:" << std::string(the_param->pScrBuf, 10);
	if (strstr(the_param->pScrBuf, "Global-Event-") != 0)
	{
		/*
		ԭ���ǣ�\Sessions\1\BaseNamedObjects\Global-Event-0000002E0systemevent
		�޸ĺ�\Sessions\1\BaseNamedObjects\Global-Event-0000183C0000002E0systemevent
		*/
		exec_once = true;
		char szProcessId[256] = { 0 };
		sprintf_s(szProcessId, "%p", GetCurrentProcessId());

		int nLen = strlen(szProcessId);
		memcpy(the_param->pScrCur, szProcessId, nLen);
		the_param->nRemainBufLen -= nLen;
		the_param->pScrCur += nLen;
	}
	return hooker.GetCodeOrig();
}

void* Hooker_CpuId(IHooker& hooker, JmpHookerAmbient& ambient)
{
	LOG_O(Log_trace) << "Hooker_CpuId, eax:" << ambient.eax_;
	assert(false);
	return hooker.GetCodeOrig();
}

void* Hooker_GetUserDefaultLCID(IHooker& hooker, JmpHookerAmbient& ambient)
{
	auto the_call_addr = ambient.EspStackValueAs<void*>(0);
	if (IsUnValidPtr(the_call_addr))
	{
		assert(false);
		return hooker.GetCodeOrig();
	}
	auto thrd_id = GetCurrentThreadId();
	auto the_module = ModuleFromAddress(GetThreadStartAddr(thrd_id));
	if (GlobalSetter::GetMe().GetSelfModuleHandle() == the_module)
		return hooker.GetCodeOrig();

	MEMORY_BASIC_INFORMATION memory_basic = { 0 };
	VirtualQueryEx(INVALID_HANDLE_VALUE, the_call_addr, &memory_basic, sizeof(memory_basic));
	if (PAGE_READWRITE != memory_basic.AllocationProtect)
		return hooker.GetCodeOrig();
	LOG_O(Log_trace) << "Hooker_GetUserDefaultLCID��Ѻ�̣߳��߳�ID:" << std::dec << GetCurrentThreadId() << " ���ص�ַ��" << the_call_addr;
	while (true)
	{
		Sleep(1000 * 60 * 5);
	}
	return hooker.GetCodeOrig();
}

void* Hooker_TimeGetTime(IHooker& hooker, JmpHookerAmbient& ambient)
{
	return hooker.GetCodeOrig();
}

void* Hooker_ZwOpenProcess(IHooker& hooker, JmpHookerAmbient& ambient)
{
	auto ProcessHandle = ambient.EspParamAs<1, PHANDLE>();
	auto DesiredAccess = ambient.EspParamAs<2, ACCESS_MASK>();
	auto ObjectAttributes = ambient.EspParamAs<3, POBJECT_ATTRIBUTES>();
	auto ClientId = ambient.EspParamAs<4, PCLIENT_ID>();
	auto real_fn = (ZwOpenProcess)hooker.GetCodeOrig();
	if (IsUnValidPtr(ClientId))
	{
		assert(false);
		return hooker.GetCodeOrig();
	}
	auto thrd_id = GetCurrentThreadId();
	auto the_module = ModuleFromAddress(GetThreadStartAddr(thrd_id));
	if (GlobalSetter::GetMe().GetSelfModuleHandle() == the_module)
		return hooker.GetCodeOrig();
	//////////////////////////////////////////////////////////////////////////
	CLIENT_ID theClientId;
	theClientId.UniqueProcess = ClientId->UniqueProcess;
	theClientId.UniqueThread = ClientId->UniqueThread;

	PVOID pProcessId = (PVOID)0;
	if (ClientId->UniqueProcess == pProcessId)
	{
		theClientId.UniqueProcess = (PVOID)(8);
		theClientId.UniqueThread = 0;

#ifdef _DEBUG
		char buffer[MAX_PATH];
		if (GetModuleName(the_module, buffer, sizeof(buffer)))
		{
			LOG_O(Log_debug) << "Hooker_ZwOpenProcess��Ѻ�̣߳��߳�ID��" << std::dec << thrd_id << " ģ������" << buffer;
		}
#endif

		while (true)
		{
			Sleep(1000 * 60 * 10);
		}
	}
	auto res = real_fn(ProcessHandle, DesiredAccess, ObjectAttributes, &theClientId);
	ambient.eax_ = res;
	//////////////////////////////////////////////////////////////////////////
	return NakedRetP4;
}

void* Hooker_ZwQuerySystemInformation(IHooker& hooker, JmpHookerAmbient& ambient)
{
	auto real_fn = (ZwQuerySystemInformation)hooker.GetCodeOrig();
	auto SystemInformationClass = ambient.EspParamAs<1, SYSTEM_INFORMATION_CLASS>();
	auto SystemInformation = ambient.EspParamAs<2, PVOID>();
	if (IsUnValidPtr(SystemInformation))
		return hooker.GetCodeOrig();
	auto SystemInformationLength = ambient.EspParamAs<3, ULONG>();
	auto ReturnLength = ambient.EspParamAs<4, PULONG>();

	auto status = real_fn(SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength);
	ambient.eax_ = status;
	auto pInfo = (PSYSTEM_PROCESSES)SystemInformation;

	if (SystemModuleInformation == SystemInformationClass)
	{
		auto thrd_id = GetCurrentThreadId();
		auto the_module = ModuleFromAddress(GetThreadStartAddr(thrd_id));
		if (GlobalSetter::GetMe().GetSelfModuleHandle() != the_module)
		{
			LOG_O(Log_debug) << "Hooker_ZwQuerySystemInformation����ģ��" << " thrd_id:" << GetCurrentThreadId();
			PSYSTEM_MODULE_INFORMATION pModle = (PSYSTEM_MODULE_INFORMATION)SystemInformation;
			if (pModle != nullptr)
			{
				pModle->ModulesCount = 1;
				SystemInformation = nullptr;
			}
			else
			{
				//OutputDebugString("[LOG] ����ģ�� SystemInformation = NULL");
			}
		}
	}
	else if (SystemProcessInformation == SystemInformationClass && status != 0x0C0000004)
	{
		while (true)
		{
			if (pInfo->NextEntryDelta == 0)
			{
				break;
			}

			pInfo = (PSYSTEM_PROCESSES)(((PUCHAR)pInfo) + pInfo->NextEntryDelta);

			wchar_t* pszProcessName = ((wchar_t*)(&pInfo->ProcessName) + 2);

			if (Cmnx_Stristr((wchar_t*)*(DWORD*)pszProcessName, L"Console.exe"))
			{
				auto thrd_id = GetCurrentThreadId();
				auto the_module = ModuleFromAddress(GetThreadStartAddr(thrd_id));
				if (GlobalSetter::GetMe().GetSelfModuleHandle() != the_module)
				{
					//pInfo->NextEntryDelta = 0;
					pInfo->ProcessId = 0;
					__asm
					{
						lea eax, pszProcessName
						mov eax, dword ptr[eax]
						mov dword ptr[eax], 0
					}
					/*char buffer[MAX_PATH];
					auto thrd_id = GetCurrentThreadId();
					if (GetAddressModuleName(GetThreadStartAddr(thrd_id), buffer, sizeof(buffer)))
					{
					LOG_O(Log_debug) << "Hooker_ZwQuerySystemInformation�ɹ��ĸɵ���һ�μ����̣��߳�ID��" << std::dec << thrd_id << " ģ������" << buffer;
					}*/
				}
			}
		}
	}
	/*else if (SystemProcessInformation == SystemInformationClass)
	{
	}
	else if( SystemBasicInformation == SystemInformationClass )
	{
		OutputDebugString("[LOG] ��ȡϵͳ��Ϣ");
		PSYSTEM_BASIC_INFORMATION pBasic = (PSYSTEM_BASIC_INFORMATION)SystemInformation;
		pBasic->NumberProcessors = 4;
	}*/
	return NakedRetP4;
}

stDetourHooker<NtCreateFile> g_hooker_NtCreateFile;
LONG NTAPI Hooker_NtCreateFile(
	OUT PHANDLE             FileHandle,
	IN ACCESS_MASK          DesiredAccess,
	IN POBJECT_ATTRIBUTES   ObjectAttributes,
	OUT PIO_STATUS_BLOCK    IoStatusBlock,
	IN PLARGE_INTEGER       AllocationSize OPTIONAL,
	IN ULONG                FileAttributes,
	IN ULONG                ShareAccess,
	IN ULONG                CreateDisposition,
	IN ULONG                CreateOptions,
	IN PVOID                EaBuffer OPTIONAL,
	IN ULONG                EaLength){
	if (ObjectAttributes->ObjectName->Buffer != NULL && ObjectAttributes->ObjectName->MaximumLength > 0)
	{
		auto pwszPatch = Cmnx_Stristr(ObjectAttributes->ObjectName->Buffer, L"Console.exe");
		if (pwszPatch)
		{
			auto thrd_id = GetCurrentThreadId();
			auto the_module = ModuleFromAddress(GetThreadStartAddr(thrd_id));
			if (GlobalSetter::GetMe().GetSelfModuleHandle() != the_module)
			{
#ifdef _DEBUG
				char buffer[MAX_PATH];
				if (GetModuleName(the_module, buffer, sizeof(buffer)))
				{
					LOG_O(Log_debug) << "Hooker_NtCreateFile���ּ�����̨" << " �߳�ID��" << thrd_id << " ģ������" << buffer;
				}
#endif
				*(wchar_t*)pwszPatch = L'D';
				LONG lRet = g_hooker_NtCreateFile.code_orig_(FileHandle, DesiredAccess, ObjectAttributes,
					IoStatusBlock, AllocationSize, FileAttributes, ShareAccess, CreateDisposition, CreateOptions, EaBuffer, EaLength);
				*(wchar_t*)pwszPatch = L'C';
				return lRet;
			}			
		}
	}

	return g_hooker_NtCreateFile.code_orig_(FileHandle, DesiredAccess, ObjectAttributes, 
		IoStatusBlock, AllocationSize, FileAttributes, ShareAccess, CreateDisposition, CreateOptions, EaBuffer, EaLength);
}

stDetourHooker<RtlQueryProcessDebugInformation> g_hooker_RtlQueryProcessDebugInformation;
HANDLE WINAPI Hooker_RtlQueryProcessDebugInformation(DWORD th32ProcessID, DWORD dwFlags, LPVOID Buffer)
{
	//CreateToolhelp32Snapshot�ײ�����RtlQueryProcessDebugInformation
	if (dwFlags != 4)
	{
		auto thrd_id = GetCurrentThreadId();
		auto the_module = ModuleFromAddress(GetThreadStartAddr(thrd_id));
		if (GlobalSetter::GetMe().GetSelfModuleHandle() != the_module)
		{
			LOG_O(Log_debug) << "Hooker_RtlQueryProcessDebugInformation ���̱߳�����ֱ�ӷ���ʧ�ܣ��߳�ID��" << std::dec << thrd_id;
			return INVALID_HANDLE_VALUE;
		}
	}
	return g_hooker_RtlQueryProcessDebugInformation.code_orig_(th32ProcessID, dwFlags, Buffer);
}

stDetourHooker<decltype(CreateToolhelp32Snapshot)*> g_hooker_CreateToolhelp32Snapshot_;
HANDLE WINAPI Hooker_CreateToolhelp32Snapshot(DWORD dwFlags, DWORD th32ProcessID){
	auto thrd_id = GetCurrentThreadId();
	auto the_module = ModuleFromAddress(GetThreadStartAddr(thrd_id));
	if (GlobalSetter::GetMe().GetSelfModuleHandle() != the_module)
	{
		LOG_O(Log_debug) << "Hooker_CreateToolhelp32Snapshot ֱ�ӷ���ʧ�ܣ��߳�ID��" << std::dec << thrd_id;
		return INVALID_HANDLE_VALUE;
	}
	return g_hooker_CreateToolhelp32Snapshot_.code_orig_(dwFlags, th32ProcessID);
}

typedef BOOL (WINAPI* EnumProcessesFnT)(_Out_  DWORD *pProcessIds, _In_   DWORD cb, _Out_  DWORD *pBytesReturned);
stDetourHooker<EnumProcessesFnT> g_hooker_EnumProcesses_;
BOOL WINAPI Hooker_EnumProcesses(_Out_  DWORD *pProcessIds, _In_   DWORD cb, _Out_  DWORD *pBytesReturned){
	auto thrd_id = GetCurrentThreadId();
	auto the_module = ModuleFromAddress(GetThreadStartAddr(thrd_id));
	if (GlobalSetter::GetMe().GetSelfModuleHandle() != the_module)
	{
		LOG_O(Log_debug) << "Hooker_EnumProcesses ֱ�ӷ���ʧ�ܣ��߳�ID��" << std::dec << thrd_id;
		return FALSE;
	}
	return g_hooker_EnumProcesses_.code_orig_(pProcessIds, cb, pBytesReturned);
}

stDetourHooker<EnumProcessesFnT> g_hooker_EnumProcesses1_;
BOOL WINAPI Hooker_EnumProcesses1(_Out_  DWORD *pProcessIds, _In_   DWORD cb, _Out_  DWORD *pBytesReturned){
	auto thrd_id = GetCurrentThreadId();
	auto the_module = ModuleFromAddress(GetThreadStartAddr(thrd_id));
	if (GlobalSetter::GetMe().GetSelfModuleHandle() != the_module)
	{
		LOG_O(Log_debug) << "Hooker_EnumProcesses1 ֱ�ӷ���ʧ�ܣ��߳�ID��" << std::dec << thrd_id;
		return FALSE;
	}
	return g_hooker_EnumProcesses1_.code_orig_(pProcessIds, cb, pBytesReturned);
}

typedef BOOL(WINAPI* EnumWindowsFnT)(WNDENUMPROC lpEnumFunc, LPARAM lParam);
stDetourHooker<EnumWindowsFnT> g_hooker_EnumWindows_;
BOOL WINAPI Hooker_EnumWindows(WNDENUMPROC lpEnumFunc, LPARAM lParam){
	auto thrd_id = GetCurrentThreadId();
	auto the_module = ModuleFromAddress(GetThreadStartAddr(thrd_id));
	if (GlobalSetter::GetMe().GetSelfModuleHandle() != the_module)
	{
		LOG_O(Log_debug) << "Hooker_EnumWindows ֱ�ӷ���ʧ�ܣ��߳�ID��" << std::dec << thrd_id;
		return FALSE;
	}
	return g_hooker_EnumWindows_.code_orig_(lpEnumFunc, lParam);
}

stDetourHooker<decltype(FindWindowExW)*> g_hooker_FindWindowEx_;
HWND WINAPI Hooker_FindWindowExW(__in_opt HWND hWndParent, __in_opt HWND hWndChildAfter, __in_opt LPCWSTR lpszClass, __in_opt LPCWSTR lpszWindow){
	auto thrd_id = GetCurrentThreadId();
	auto the_module = ModuleFromAddress(GetThreadStartAddr(thrd_id));
	if (GlobalSetter::GetMe().GetSelfModuleHandle() != the_module)
	{
		LOG_O(Log_debug) << "Hooker_FindWindowExW ֱ�ӷ���ʧ�ܣ��߳�ID��" << thrd_id;
		return nullptr;
	}
	return g_hooker_FindWindowEx_.code_orig_(hWndParent, hWndChildAfter, lpszClass, lpszWindow);
}

stDetourHooker<decltype(FindWindowW)*> g_hooker_FindWindowW_;
HWND WINAPI Hooker_FindWindowW(__in_opt LPCWSTR lpClassName, __in_opt LPCWSTR lpWindowName){
	auto thrd_id = GetCurrentThreadId();
	auto the_module = ModuleFromAddress(GetThreadStartAddr(thrd_id));
	if (GlobalSetter::GetMe().GetSelfModuleHandle() != the_module)
	{
		if (lpWindowName)
		{
			if (Cmnx_Stristr(lpWindowName, L"��������Online��¼����"))
			{
				auto wnd_handle = g_hooker_FindWindowW_.code_orig_(lpClassName, lpWindowName);
				if (wnd_handle)
				{
					DWORD process_id = 0;
					GetWindowThreadProcessId(wnd_handle, &process_id);
					if (0 != process_id)
					{
						TerminateTheProcess(process_id);
					}
				}
				return nullptr;
			}
		}		
#ifdef _DEBUG
		std::string cls_name;
		if (lpClassName)
			cls_name = CW2A(lpClassName);
		std::string wnd_name;
		if (lpWindowName)
		wnd_name = CW2A(lpWindowName);
		LOG_O(Log_debug) << "Hooker_FindWindowW ֱ�ӷ���ʧ�ܣ��߳�ID��" << thrd_id << " cls_name:" << cls_name << " wnd_name:" << wnd_name;
#endif
		return nullptr;
	}
	return g_hooker_FindWindowW_.code_orig_(lpClassName, lpWindowName);
}

void AntiCheckThrd_ClientBase(HookerPtrStored& hooks){
	HMODULE h_client_base = GetModuleHandleA("MHOClientBase.dll");
	while (!h_client_base)
	{
		::Sleep(1);
		h_client_base = GetModuleHandleA("MHOClientBase.dll");
	}
	auto& hooker_factory = HookerFactory::GetMe();
	//�࿪	
	struct tagSprintf{};
	//�����ᱻ��
	/*hooks.StoreHook(hooker_factory.HOOKER_CreateCodeHooker(tagSprintf, (char*)h_client_base + g_h_lpkb_sprintf_,
		Hooker_Sprintf, true));*/

	LOG_O(Log_trace) << "AntiCheckThrd_ClientBase��hook�ɹ�";
}

void AntiCheckThrd_TerSafe(HookerPtrStored& hooks){
	HMODULE h_tersafe = GetModuleHandleA("terSafe.dll");
	while (!h_tersafe)
	{
		::Sleep(1);
		h_tersafe = GetModuleHandleA("terSafe.dll");
	}
	auto& hooker_factory = HookerFactory::GetMe();
	//�õ�������
	struct tagCpuId{};
	hooks.StoreHook(hooker_factory.HOOKER_CreateCodeHooker(tagCpuId, (char*)h_tersafe + g_h_lpkb_tersafe_get_cpuid_,
		Hooker_CpuId, true));

	LOG_O(Log_trace) << "AntiCheckThrd_TerSafe��hook�ɹ�";
}

void AntiCheckThrd_vcr80(HookerPtrStored& hooks){
	auto h_module = GetModuleHandleA("MSVCR80.dll");
	while (!h_module)
	{
		::Sleep(1);
		h_module = GetModuleHandleA("MSVCR80.dll");
		if (h_module)
			break;
		CToolhelp th(TH32CS_SNAPMODULE, GetCurrentProcessId());
		MODULEENTRY32 m_entry;
		m_entry.dwSize = sizeof(m_entry);
		if (th.ModuleFind(_T("MSVCR80.dll"), &m_entry))
			h_module = m_entry.hModule;
	}
	LOG_O(Log_trace) << "AntiCheckThrd_vcr80 �ҵ���ģ��";
	auto& hooker_factory = HookerFactory::GetMe();
	auto the_addr = (void*)GetProcAddress(h_module, "_beginthread");
	if (!the_addr)
	{
		assert(false);
		return;
	}
	struct tagBeginThread80{};
	hooks.StoreHook(hooker_factory.HOOKER_CreateCodeHooker(tagBeginThread80, the_addr,
		Hooker_beginthread, true));

	the_addr = (void*)GetProcAddress(h_module, "_beginthreadex");
	if (!the_addr)
	{
		assert(false);
		return;
	}
	struct tagBeginThreadEx80{};
	hooks.StoreHook(hooker_factory.HOOKER_CreateCodeHooker(tagBeginThreadEx80, the_addr,
		Hooker_beginthreadex, true));

	LOG_O(Log_trace) << "AntiCheckThrd_vcr80��hook�ɹ�";
}

bool DoAntiCheck(HookerPtrStored& hooks){
	//////////////////////////////////////////////////////////////////////////
	auto& hooker_factory = HookerFactory::GetMe();

	auto h_msvcr = GetModuleHandleA("MSVCR90.dll");
	if (!h_msvcr)
	{
		assert(false);
		return false;
	}
	auto the_addr = (void*)GetProcAddress(h_msvcr, "_beginthread");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	struct tagBeginThread90{};
	hooks.StoreHook(hooker_factory.HOOKER_CreateCodeHooker(tagBeginThread90, the_addr,
		Hooker_beginthread, true));

	the_addr = (void*)GetProcAddress(h_msvcr, "_beginthreadex");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	struct tagBeginThreadEx90{};
	hooks.StoreHook(hooker_factory.HOOKER_CreateCodeHooker(tagBeginThreadEx90, the_addr,
		Hooker_beginthreadex, true));

	h_msvcr = GetModuleHandleA("msvcrt.dll");
	if (!h_msvcr)
	{
		assert(false);
		return false;
	}
	the_addr = (void*)GetProcAddress(h_msvcr, "_beginthread");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	struct tagBeginThread_Crt{};
	hooks.StoreHook(hooker_factory.HOOKER_CreateCodeHooker(tagBeginThread_Crt, the_addr,
		Hooker_beginthread, true));

	the_addr = (void*)GetProcAddress(h_msvcr, "_beginthreadex");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	struct tagBeginThreadEx_Crt{};
	hooks.StoreHook(hooker_factory.HOOKER_CreateCodeHooker(tagBeginThreadEx_Crt, the_addr,
		Hooker_beginthreadex, true));

	h_msvcr = GetModuleHandleA("msvcr80.dll");
	if (!h_msvcr)
	{
		CToolhelp th(TH32CS_SNAPMODULE, GetCurrentProcessId());
		MODULEENTRY32 m_entry;
		m_entry.dwSize = sizeof(m_entry);
		if (th.ModuleFind(_T("msvcr80.dll"), &m_entry))
		{
			h_msvcr = m_entry.hModule;
			LOG_O(Log_trace) << "�ҵ���msvcr80";
		}
		else
		{
			LOG_O(Log_debug) << "û�ҵ�msvcr80";
		}
	}
	else
	{
		LOG_O(Log_trace) << "1�ҵ���msvcr80";
	}

	if (h_msvcr)
	{
		the_addr = (void*)GetProcAddress(h_msvcr, "_beginthread");
		if (!the_addr)
		{
			assert(false);
			return false;
		}
		struct tagBeginThread80{};
		hooks.StoreHook(hooker_factory.HOOKER_CreateCodeHooker(tagBeginThread80, the_addr,
			Hooker_beginthread, true));

		the_addr = (void*)GetProcAddress(h_msvcr, "_beginthreadex");
		if (!the_addr)
		{
			assert(false);
			return false;
		}
		struct tagBeginThreadEx80{};
		hooks.StoreHook(hooker_factory.HOOKER_CreateCodeHooker(tagBeginThreadEx80, the_addr,
			Hooker_beginthreadex, true));
	}
	else
	{
		boost::thread t_msvcr80([&hooks](){
			AntiCheckThrd_vcr80(hooks);
		});
	}
	//////////////////////////////////////////////////////////////////////////
	boost::thread t_handle_sleep_thrd([](){
		CEvent event_handle;
		g_event_handle_rub_thrd_ = &event_handle;
		BOOST_SCOPE_EXIT_ALL(&){
			g_event_handle_rub_thrd_ = nullptr;
			g_handle_rub_thrd_end_ = true;
		};
		HandleSleepRubThrd(&event_handle);
	});
	//////////////////////////////////////////////////////////////////////////
	auto h_inst = GetModuleHandleA("Kernel32.dll");
	if (!h_inst)
	{
		assert(false);
		return false;
	}
	the_addr = GetProcAddress(h_inst, "GetUserDefaultLCID");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	struct tagGetUserDefaultLCID{};
	hooks.StoreHook(hooker_factory.HOOKER_CreateCodeHooker(tagGetUserDefaultLCID, (char*)the_addr,
		Hooker_GetUserDefaultLCID, true));

	the_addr = GetProcAddress(h_inst, "CreateToolhelp32Snapshot");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	g_hooker_CreateToolhelp32Snapshot_.hooked_addr_ = (decltype(CreateToolhelp32Snapshot)*)the_addr;
	g_hooker_CreateToolhelp32Snapshot_.detour_addr_ = Hooker_CreateToolhelp32Snapshot;
	if (!SetDetourHook("Hooker_CreateToolhelp32Snapshot", g_hooker_CreateToolhelp32Snapshot_))
	{
		assert(false);
		return false;
	}

	h_inst = GetModuleHandleA("winmm.dll");
	if (!h_inst)
	{
		assert(false);
		return false;
	}
	the_addr = GetProcAddress(h_inst, "timeGetTime");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	struct tagtimeGetTime{};
	hooks.StoreHook(hooker_factory.HOOKER_CreateCodeHooker(tagtimeGetTime, (char*)the_addr,
		Hooker_TimeGetTime, true));

	h_inst = GetModuleHandleA("ntdll.dll");
	if (!h_inst)
	{
		assert(false);
		return false;
	}
	the_addr = GetProcAddress(h_inst, "ZwOpenProcess");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	struct tagZwOpenProcess{};
	hooks.StoreHook(hooker_factory.HOOKER_CreateCodeHooker(tagZwOpenProcess, (char*)the_addr,
		Hooker_ZwOpenProcess, true));

	the_addr = GetProcAddress(h_inst, "ZwQuerySystemInformation");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	struct tagZwQuerySystemInformation{};
	hooks.StoreHook(hooker_factory.HOOKER_CreateCodeHooker(tagZwQuerySystemInformation, (char*)the_addr,
		Hooker_ZwQuerySystemInformation, true));

	the_addr = GetProcAddress(h_inst, "NtCreateFile");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	g_hooker_NtCreateFile.hooked_addr_ = (NtCreateFile)the_addr;
	g_hooker_NtCreateFile.detour_addr_ = Hooker_NtCreateFile;
	if (!SetDetourHook("Hooker_NtCreateFile", g_hooker_NtCreateFile))
	{
		assert(false);
		return false;
	}
	
	//CreateToolhelp32Snapshot�ײ�����RtlQueryProcessDebugInformation
	the_addr = GetProcAddress(h_inst, "RtlQueryProcessDebugInformation");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	g_hooker_RtlQueryProcessDebugInformation.hooked_addr_ = (RtlQueryProcessDebugInformation)the_addr;
	g_hooker_RtlQueryProcessDebugInformation.detour_addr_ = Hooker_RtlQueryProcessDebugInformation;
	if (!SetDetourHook("Hooker_RtlQueryProcessDebugInformation", g_hooker_RtlQueryProcessDebugInformation))
	{
		assert(false);
		return false;
	}

	the_addr = GetProcAddress(h_inst, "ZwCreateThread");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	hooker_info_NtCreateThread_.hooked_addr_ = (NtCreateThread)the_addr;
	hooker_info_NtCreateThread_.detour_addr_ = Hooker_NtCreateThread;
	if (!SetDetourHook("Hooker_NtCreateThread", hooker_info_NtCreateThread_))
	{
		assert(false);
		return false;
	}

	the_addr = GetProcAddress(h_inst, "ZwCreateThreadEx");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	hooker_info_NtCreateThreadEx_.hooked_addr_ = (NtCreateThreadEx)the_addr;
	hooker_info_NtCreateThreadEx_.detour_addr_ = Hooker_NtCreateThreadEx;
	if (!SetDetourHook("Hooker_NtCreateThreadEx", hooker_info_NtCreateThreadEx_))
	{
		assert(false);
		return false;
	}

	g_hooker_NtQueryInformationProcess_.hooked_addr_ = GetNtQueryInformationProcess();
	if (!g_hooker_NtQueryInformationProcess_.hooked_addr_)
	{
		assert(false);
		return false;
	}
	g_hooker_NtQueryInformationProcess_.detour_addr_ = Hooker_NtQueryInformationProcess;
	if (!SetDetourHook("Hooker_NtQueryInformationProcess", g_hooker_NtQueryInformationProcess_))
	{
		assert(false);
		return false;
	}
	//////////////////////////////////////////////////////////////////////////
	h_inst = GetModuleHandleA("PSAPI.dll");
	if (h_inst)
	{
		the_addr = GetProcAddress(h_inst, "EnumProcesses");
		if (the_addr)
		{
			g_hooker_EnumProcesses_.hooked_addr_ = (EnumProcessesFnT)the_addr;
			g_hooker_EnumProcesses_.detour_addr_ = Hooker_EnumProcesses;
			if (!SetDetourHook("Hooker_EnumProcesses", g_hooker_EnumProcesses_))
			{
				assert(false);
				return false;
			}
		}
	}
	h_inst = GetModuleHandleA("Kernel32.dll");
	if (!h_inst)
	{
		assert(false);
		return false;
	}
	the_addr = GetProcAddress(h_inst, "K32EnumProcesses");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	g_hooker_EnumProcesses1_.hooked_addr_ = (EnumProcessesFnT)the_addr;
	g_hooker_EnumProcesses1_.detour_addr_ = Hooker_EnumProcesses1;
	if (!SetDetourHook("Hooker_EnumProcesses1", g_hooker_EnumProcesses1_))
	{
		assert(false);
		return false;
	}
	//////////////////////////////////////////////////////////////////////////
	h_inst = GetModuleHandleA("user32.dll");
	if (!h_inst)
	{
		assert(false);
		return false;
	}
	the_addr = GetProcAddress(h_inst, "EnumWindows");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	g_hooker_EnumWindows_.hooked_addr_ = (EnumWindowsFnT)the_addr;
	g_hooker_EnumWindows_.detour_addr_ = Hooker_EnumWindows;
	if (!SetDetourHook("Hooker_EnumWindows", g_hooker_EnumWindows_))
	{
		assert(false);
		return false;
	}

	the_addr = GetProcAddress(h_inst, "FindWindowW");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	g_hooker_FindWindowW_.hooked_addr_ = (decltype(g_hooker_FindWindowW_.hooked_addr_))the_addr;
	g_hooker_FindWindowW_.detour_addr_ = Hooker_FindWindowW;
	if (!SetDetourHook("Hooker_FindWindowW", g_hooker_FindWindowW_))
	{
		assert(false);
		return false;
	}

	the_addr = GetProcAddress(h_inst, "FindWindowExW");
	if (!the_addr)
	{
		assert(false);
		return false;
	}
	g_hooker_FindWindowEx_.hooked_addr_ = (decltype(g_hooker_FindWindowEx_.hooked_addr_))the_addr;
	g_hooker_FindWindowEx_.detour_addr_ = Hooker_FindWindowExW;
	if (!SetDetourHook("Hooker_FindWindowExW", g_hooker_FindWindowEx_))
	{
		assert(false);
		return false;
	}
	//////////////////////////////////////////////////////////////////////////
	/*boost::thread t_1([&hooks](){
	AntiCheckThrd_ClientBase(hooks);
	});*/

	/*boost::thread t_2([&hooks](){
		AntiCheckThrd_TerSafe(hooks);
	});*/
	return true;
}