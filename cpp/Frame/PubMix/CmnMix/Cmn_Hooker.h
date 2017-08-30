#pragma once
/*
@author zhp
@date 2014-1-03
@purpose API/code hook
*/
#include <boost/shared_ptr.hpp>
#include <boost/mpl/int.hpp>
#include <set>
#include "Cmn_LogOut.h"
#include "Cmn_Exception.h"
#include "Cmn_UsefulClass.h"
#include "Cmn_UsefulFunc.h"
#include "../DependSelfLib.h"
#include "../DependExternLib.h"

#pragma warning(push)
#pragma warning(disable:4410)
#pragma warning(disable:4409)

//////////////////////////////////////////////////////////////////////////
//��־�Ĵ�����λ��/λ��
struct stEflags{
	int	carry_ : 1;		//��λ����ִ��һ���ӷ�(�����)���㣬ʹ���λ������λ(���λ)ʱ��CFΪ1������Ϊ0��
	int	unuse1_ : 1;
	int	parity_ : 1;	//��ż����ִ��һ���ӷ�(�����)���㣬ʹ���λ������λ(���λ)ʱ��CFΪ1������Ϊ0��
	int	unuse2_ : 1;
	int auxiliary_ : 1;	//������λ����ִ��һ���ӷ�(�����)���㣬ʹ���λ������λ(���λ)ʱ��CFΪ1������Ϊ0��
	int	unuse3_ : 1;
	int	zero_ : 1;		//���־λ������ǰ��������Ϊ�㣬ZF=1������ZF=0��
	int	sign_ : 1;		//���ű�־λ�����������������λ��ͬ��
	int	trap_ : 1;		//���ٱ�־λ������Ϊ���Գ�����趨���������λ������λ�á�1��ʱ��8086 CPU���ڵ���״̬����ʱCPUÿִ����һ��ָ����Զ�����һ���ڲ��жϡ�����λ��λ��CPU�ָ�����������
	int	interrupt_enable_ : 1;	//�ж������־λ������������8086�Ƿ���������ⲿ�ж�������IF=1��8086����Ӧ�ⲿ�жϣ���֮����Ӧ�ⲿ�жϡ�
	int	direction_ : 1;			//�����־λ��������ָ���ַ�������ʱ�ķ��򣬵���λ�á�1��ʱ���ַ����Եݼ�˳��������ַ�ԴӸߵ���˳��ݼ�����֮�����Ե���˳����
	int	overflow_ : 1;			//�����־λ�����������������ʱ��OF=1������OF=0��	3�����Ʊ�־λ��������CPU�Ĳ�������ָ�������λ�͸�λ��
	int	iopl_ : 2;				//I/O privilege level. I/O��Ȩ��־����λ������λ����ʾ��Ҳ��ΪI/O��Ȩ���ֶΡ����ֶ�ָ����Ҫ��ִ��I/Oָ�����Ȩ���������ǰ����Ȩ��������ֵ��С�ڵ���IOPL��ֵ����ô����I/Oָ���ִ�У����򽫷���һ�������쳣��
	int	nested_task_ : 1;		//Ƕ�������־NT���������жϷ���ָ��IRET��ִ�С�����涨���£�	(1)����NT = 0���ö�ջ�б����ֵ�ָ�EFLAGS��CS��EIP��ִ�г�����жϷ��ز�����(2)����NT = 1��ͨ������ת��ʵ���жϷ��ء�
	int	unuse4_ : 1;
	int	resume_ : 1;			//��������־RF���������Ƿ���ܵ��Թ��ϡ��涨��RF=0ʱ����ʾ"����"���Թ��ϣ�����ܾ�֮���ڳɹ�ִ����һ��ָ��󣬴������RF��Ϊ0�������ܵ�һ���ǵ��Թ���ʱ��������Ͱ�����Ϊ1��
	int	vm_ : 1;	//Virtual-8086 Mode.����ñ�־��ֵΪ1�����ʾ��������������8086��ʽ�µĹ���״̬�����򣬴��������һ�㱣����ʽ�µĹ���״̬��
	int	alignment_check_ : 1;	//
	int	VIF_ : 1;	//virtual interrupt flag
	int VIP_ : 1;	//virtual interrupt pending
	int	id_ : 1;	//ID Flag
	int	unuse5_ : 10;
};
static_assert(sizeof(stEflags) == 4, "");
class IHooker;
//��ת���Լ��Ĵ����ļĴ�������������ṹһ����Ҫ������������
struct JmpHookerAmbient{
	stEflags	efl_;	//״̬�Ĵ���/��־�Ĵ���
	int			edi_;
	int			esi_;
	int			ebp_;
	int			esp_;	//esp����ֱ�ӱ��޸�
	int			ebx_;
	int			edx_;
	int			ecx_;
	int			eax_;

public:
	JmpHookerAmbient();
	JmpHookerAmbient(const JmpHookerAmbient&) = delete;
	JmpHookerAmbient& operator = (const JmpHookerAmbient&) = delete;
	//����esp��ջ�е�Ԫ�ص�Ѱַ
	template<typename T>
	T EspStackValueAs( int delta ) const{
		return *(T*)(void*)(esp_ + delta);
	}
	template<int P_N, typename T>
	T EspParamAs() const{
		static_assert(P_N >= 1 && P_N < 100, "");
		return *(T*)(void*)(esp_ + P_N * 4);
	}
	//�õ��������ص�ַ
	pt_pvoid GetFnRetAddrAsEsp() const{
		return *(pt_pvoid*)(void*)esp_;
	}
	//����ebp��ջ�е�Ԫ�ص�Ѱַ
	template<typename T>
	T EbpStackValueAs(int delta) const{
		return *(T*)(void*)(ebp_ + delta);
	}
	template<int P_N, typename T>
	T EbpParamAs() const{
		static_assert(P_N >= 1 && P_N < 100, "");
		return *(T*)(void*)(ebp_ + P_N * 4 + 4);
	}
	template<typename T>
	void EspModifyStackValue(int delta, const T& v){
		*(T*)(void*)(esp_ + delta) = v;
	}
	template<int P_N, typename T>
	void EspModifyParam(const T& v){
		static_assert(P_N >= 1 && P_N < 100, "");
		*(T*)(void*)(esp_ + P_N * 4) = v;
	}
	template<typename T>
	void EbpModifyStackValue(int delta, const T& v){
		*(T*)(void*)(ebp_ + delta) = v;
	}
	template<int P_N, typename T>
	void EbpModifyParam(const T& v){
		static_assert(P_N >= 1 && P_N < 100, "");
		*(T*)(void*)(ebp_ + P_N * 4 + 4) = v;
	}
	void Cpuid(int eax_param);
	void AssignRegisterABCD(const JmpHookerAmbient& rhs);

private:
	friend class HookerFactory;
};
static_assert(sizeof(JmpHookerAmbient) == 4 + 0x20, "");

class IHooker{
public:
	IHooker() = default;
	IHooker(const IHooker&) = delete;
	IHooker& operator = (const IHooker&) = delete;
	operator void*(){
		return GetCodeOrig();
	}
	virtual ~IHooker();
	//get hooked API origin
	virtual PROC GetApiOrig();
	//code hooker,hooked code addr
	virtual void* GetHookedCodeAddr();
	//code hooker,next execute code addr
	//origin code addr
	//��hookס��ָ��ᵽ���ص�ַ����
	virtual void* GetCodeOrig();
	//�Ƿ���Ч
	virtual bool IsValid() = 0;
	//�����Ƿ�ָ�ԭ���Ĵ���
	virtual void SetResume(bool is_resume) = 0;
};
typedef boost::shared_ptr<IHooker> HookerPtr;

//////////////////////////////////////////////////////////////////////////
#define _HOOKER_COMMON_PRE_DEF_1	\
	static IHooker* hooker = nullptr;	\
	static auto g_call_back = call_back;	\
	void* label_addr;	\
	_asm mov label_addr, offset LABLE_DETOUR;	\
/**/
#define _HOOKER_COMMON_PRE_DEF_2	\
	static auto g_call_back = call_back;	\
	void* label_addr;	\
	_asm mov label_addr, offset LABLE_DETOUR;	\
/**/
#define _HOOKER_COMMON_ASM_CODE_PRE	\
		goto LABLE_RET;		\
	LABLE_DETOUR:		\
		/*��һ��ָ��ֻ����_asm pushad���м�*/	\
		__asm	\
		{	\
			__asm pushad	\
			__asm pushfd	\
			/*����*/		\
			__asm push eax	\
			/*ѹ����ĸ�����*/	\
			__asm mov eax, esp	\
			__asm add eax, 4	\
			__asm push eax	\
		}	\
/**/
#define _HOOKER_COMMON_ASM_CODE_END	\
		__asm	\
		{	\
			/*�������ĸ�����*/		\
			__asm pop ebx	\
			/*������ת��ַ��������*/		\
			__asm mov [esp], eax		\
			/*�ͷű���*/		\
			__asm add esp, 4	\
			__asm popfd		\
			__asm popad		\
			/*���ͷŵı�������ת*/		\
			__asm jmp [esp - 28h]		\
		}	\
		assert(!"����ִ�е�����");	\
/**/
//////////////////////////////////////////////////////////////////////////
//����hook api
void SetDetourHook_(const char* hooker_name, void* hooked_addr, const void* detour_addr, void** code_orig);
template<typename T>
void SetDetourHook(const char* hooker_name, T hooked_addr, const T detour_addr, T* code_orig){
	SetDetourHook_(hooker_name, (void*)hooked_addr, (void*)detour_addr, (void**)(void*)code_orig);
}
template<typename T>
struct stDetourHooker{
	T			hooked_addr_;
	T			detour_addr_;
	T			code_orig_;

	stDetourHooker(T hooked_addr = nullptr, T detour_addr = nullptr){
		hooked_addr_ = hooked_addr;
		detour_addr_ = detour_addr;
		code_orig_ = nullptr;
	}
};
template<typename T>
bool SetDetourHook(const char* hooker_name, stDetourHooker<T>& hooker_info){
	SetDetourHook<T>(hooker_name, hooker_info.hooked_addr_, hooker_info.detour_addr_, &hooker_info.code_orig_);
	if (!hooker_info.code_orig_)
	{
		assert(false);
		return false;
	}
	return true;
}
//////////////////////////////////////////////////////////////////////////
#define HOOKER_CreateCodeHooker(hooker_name, hooked_addr, call_back) \
	struct stHookerTag_ ## hooker_name{};	\
	HookerFactory::GetMe().CreateCodeHooker<stHookerTag_ ## hooker_name>(#hooker_name, (void*)(hooked_addr), call_back)
/**/
#define HOOKER_SetCodeHooker(hooker_name, hooked_addr, call_back) \
	struct stHookerTag_ ## hooker_name{};	\
	HookerFactory::GetMe().SetCodeHooker<stHookerTag_ ## hooker_name>(#hooker_name, (void*)(hooked_addr), call_back)
/**/
//////////////////////////////////////////////////////////////////////////
class HookerFactory{
	HookerFactory();
	HookerFactory& operator = ( const HookerFactory& );
public:
	//singleton
	static HookerFactory& GetMe();
	//API hooker
	HookerPtr CreateApiHooker(PCSTR pszCalleeModName, PCSTR pszFuncName, 
		PROC pfnHook, bool is_resume = true);
	//code hooker
	HookerPtr CreateCodeHooker(const char* hooker_name, void* hooked_addr, void* detour_addr, bool is_resume = true);
	//code hooker,����һ��jmp�ĵ�ַ
	template<void* hooked_addr, typename FnT>
	HookerPtr CreateCodeHooker(const char* hooker_name, const FnT& call_back, bool is_resume = true){
		_HOOKER_COMMON_PRE_DEF_1
		auto hook_ptr = CreateCodeHooker(hooker_name, hooked_addr, label_addr, is_resume);
		if (hook_ptr)
			hooker = hook_ptr.get();
		_HOOKER_COMMON_ASM_CODE_PRE
			SafeExec(g_call_back, *hooker, 0);
		_HOOKER_COMMON_ASM_CODE_END
LABLE_RET:
		return hook_ptr;
	}
	template<typename Tag, typename FnT>
	HookerPtr CreateCodeHooker(const char* hooker_name, void* hooked_addr, const FnT& call_back, bool is_resume = true){
		_HOOKER_COMMON_PRE_DEF_1
		auto hook_ptr = CreateCodeHooker(hooker_name, hooked_addr, label_addr, is_resume);
		if (hook_ptr)
			hooker = hook_ptr.get();
		_HOOKER_COMMON_ASM_CODE_PRE
			SafeExec(g_call_back, *hooker, 0);
		_HOOKER_COMMON_ASM_CODE_END
LABLE_RET:
		return hook_ptr;
	}
	//hooker���ͷſ����û�����
	//hooker�������������deattach dll
	//����ִ��һ�ξ��ͷ�code hook���ɵ���HookerPtr::reset
	template<void* hooked_addr, typename FnT>
	void SetCodeHooker(const char* hooker_name, const FnT& call_back, bool is_resume = true){
		_HOOKER_COMMON_PRE_DEF_2
		static auto hook_ptr(CreateCodeHooker(hooker_name, hooked_addr, label_addr, is_resume));
		_HOOKER_COMMON_ASM_CODE_PRE
			SafeExec(g_call_back, *hook_ptr, 0);
		_HOOKER_COMMON_ASM_CODE_END
LABLE_RET:
		return;
	}
	template<typename Tag, typename FnT>
	void SetCodeHooker(const char* hooker_name, void* hooked_addr, const FnT& call_back, bool is_resume = true){
		_HOOKER_COMMON_PRE_DEF_2
		static auto hook_ptr(CreateCodeHooker(hooker_name, hooked_addr, label_addr, is_resume));
		_HOOKER_COMMON_ASM_CODE_PRE
			SafeExec(g_call_back, *hook_ptr, 0);
		_HOOKER_COMMON_ASM_CODE_END
LABLE_RET:
		return;
	}

private:
	static void* GetTheHookCodeOrig(IHooker& the_hook){
		return the_hook.GetCodeOrig();
	}
	static void* GetTheHookCodeOrig(HookerPtr& the_hook){
		assert(the_hook);
		return the_hook->GetCodeOrig();
	}
	template<typename T, typename U>
	static void* SafeExecImpl(const T& the_call, U& the_hook, JmpHookerAmbient& ambient){
		try{
			return the_call(the_hook, ambient);
		}
		DO_CATCH_ALL_EXCEPTION({
			LOG_ENTER_FUNC;
			LOG_O(Log_fatal) << "hkept1";
			assert(false);
			return GetTheHookCodeOrig(the_hook);
		})
	}
	//�������������ã��м�
	template<typename T, typename U>
	static void* __stdcall SafeExec(const T& the_call, U& the_hook, int dummy_value, ...){
		va_list ap;
		va_start(ap, dummy_value);
		auto ambient_dummy_ptr = (JmpHookerAmbient*)((char*)(void*)va_arg(ap, int));
		__try{
			return SafeExecImpl(the_call, the_hook, *ambient_dummy_ptr);
		}
		__except (HandleCrash(EXCEPTION_EXECUTE_HANDLER)){
			auto f = [](){
				LOG_O(Log_debug) << "SafeExec֮������C++δ�ܲ����SEH�쳣";
			};
			f();
			assert(false);
		}
		return GetTheHookCodeOrig(the_hook);
	}
};

class HookerPtrStored{
public:
	void StoreHook(const HookerPtr& hook_ptr);
	void Clear();

	std::set<HookerPtr>		hooks_;
};

//////////////////////////////////////////////////////////////////////////
class HookSomeThing{
public:
	enum enAntiCpuidRes{
		kACR_RetNormal,
		kACR_RetPassCpuid,
	};

public:
	HookSomeThing() = default;
	HookSomeThing(const HookSomeThing&) = delete;
	HookSomeThing& operator = (const HookSomeThing&) = delete;
	static HookSomeThing& GetMe();
	void SetMachineCodeBased(const std::string& machine_code_based);
	template<int tagHook>
	void AntiCpuid(pt_pcvoid cpuid_addr) const{
		assert(cpuid_addr);
		//0xa20f==cpuid
		assert(*(unsigned short*)cpuid_addr == 0xa20f);		
		HookerFactory::GetMe().SetCodeHooker<boost::mpl::int_<tagHook> >("_Hooker_ForAntiCpuid_", (void*)(cpuid_addr), _Hooker_ForAntiCpuid_);
	}
	template<int tagHook>
	void AntiCpuid(pt_dword cpuid_addr) const{
		return AntiCpuid<tagHook>((pt_pcvoid)cpuid_addr);
	}

public:
	enAntiCpuidRes DoAntiCpuid(JmpHookerAmbient& ambient);

private:
	static void* _Hooker_ForAntiCpuid_(IHooker& hooker, JmpHookerAmbient& ambient);

private:
	pt_dword GetDummyCpuid(pt_dword cpuid, int idx) const;

private:
	std::string		machine_code_based_;
};
//////////////////////////////////////////////////////////////////////////

#undef _HOOKER_COMMON_PRE_DEF_1
#undef _HOOKER_COMMON_PRE_DEF_2
#undef _HOOKER_COMMON_ASM_CODE_PRE
#undef _HOOKER_COMMON_ASM_CODE_END

#pragma warning(pop)
