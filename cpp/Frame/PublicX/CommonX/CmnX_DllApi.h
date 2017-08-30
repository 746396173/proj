#pragma once
/*
@author zhp
@date 2016/3/24 18:48
@purpose for some dll api
*/
#include <Windows.h>
#include <NTSecAPI.h>
#include "../DependSelfLib.h"
//////////////////////////////////////////////////////////////////////////
class LibraryLoader{
public:
	explicit LibraryLoader( const char* str_library );
	HMODULE GetLibrary() const;

public:
	static HMODULE LoadTheLibrary( const char* str_library );
	static HMODULE LoadTheLibrary( const wchar_t* str_library );
	static const LibraryLoader& GetLib_Kernel32();
	static const LibraryLoader& GetLib_User32();
	static const LibraryLoader& GetLib_Ntdll();

private:
	HMODULE		the_library_;
};

//libray functions
class LibFuncLoader{
public:
	LibFuncLoader( const char* str_library, const char* func_name );
	LibFuncLoader( HMODULE hlib, const char* func_name );
	LibFuncLoader( const LibraryLoader& lib_loader, const char* func_name );

public:
	template<typename FuncT_>
	FuncT_ GetFuncT() const{
		return (FuncT_)the_func_addr_;
	}

public:
	static FARPROC GetTheProcAddress( HMODULE hlib, const char* func_name );

private:
	FARPROC		the_func_addr_;
};

template<typename FuncT_>
class LibFuncLoaderX : public LibFuncLoader{
public:
	typedef FuncT_ FuncType;

public:
	LibFuncLoaderX( const char* str_library, const char* func_name ) : LibFuncLoader(str_library, func_name){}
	LibFuncLoaderX( HMODULE hlib, const char* func_name ) : LibFuncLoader(hlib, func_name){}
	LibFuncLoaderX( const LibraryLoader& lib_loader, const char* func_name ) : LibFuncLoader(lib_loader, func_name){}

public:
	FuncType GetFunc() const{
		return GetFuncT<FuncType>();
	}
};
//////////////////////////////////////////////////////////////////////////
typedef BOOL (WINAPI* WriteProcessMemoryT)( _In_   HANDLE hProcess, _In_   LPVOID lpBaseAddress, _In_   LPCVOID lpBuffer, _In_   SIZE_T nSize, _Out_  SIZE_T *lpNumberOfBytesWritten );
WriteProcessMemoryT GetWriteProcessMemory();
BOOL WINAPI WriteProcessMemory_( _In_   HANDLE hProcess, _In_   LPVOID lpBaseAddress, _In_ LPCVOID lpBuffer, _In_   SIZE_T nSize, _Out_  SIZE_T *lpNumberOfBytesWritten );

typedef BOOL (WINAPI* ReadProcessMemoryT)( _In_   HANDLE hProcess, _In_   LPCVOID lpBaseAddress, _Out_  LPVOID lpBuffer, _In_   SIZE_T nSize, _Out_  SIZE_T *lpNumberOfBytesRead );
ReadProcessMemoryT GetReadProcessMemory();
BOOL WINAPI ReadProcessMemory_( _In_   HANDLE hProcess, _In_   LPCVOID lpBaseAddress, _Out_  LPVOID lpBuffer, _In_   SIZE_T nSize, _Out_  SIZE_T *lpNumberOfBytesRead );
bool ReadMemory( const void* base_addr, void* out_buffer, SIZE_T read_size );

typedef int (WINAPI *MessageBoxTimeoutT)( HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId, DWORD dwMilliseconds );
MessageBoxTimeoutT GetMessageBoxTimeout();
int MessageBoxTimeout( HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId, DWORD dwMilliseconds );

typedef LONG NTSTATUS_;
#define NT_SUCCESS(Status) (((NTSTATUS_)(Status)) >= 0)

typedef struct _CLIENT_ID
{
	PVOID UniqueProcess;
	PVOID UniqueThread;
}CLIENT_ID, *PCLIENT_ID;

enum THREADINFOCLASS_{
	ThreadBasicInformation,  
	ThreadTimes,  
	ThreadPriority,  
	ThreadBasePriority,  
	ThreadAffinityMask,  
	ThreadImpersonationToken,  
	ThreadDescriptorTableEntry,  
	ThreadEnableAlignmentFaultFixup,  
	ThreadEventPair_Reusable,  
	ThreadQuerySetWin32StartAddress,  
	ThreadZeroTlsCell,  
	ThreadPerformanceCount,  
	ThreadAmILastThread,  
	ThreadIdealProcessor,  
	ThreadPriorityBoost,  
	ThreadSetTlsArrayAddress,   // Obsolete  
	ThreadIsIoPending,  
	ThreadHideFromDebugger,  
	ThreadBreakOnTermination,  
	ThreadSwitchLegacyState,  
	ThreadIsTerminated,  
	ThreadLastSystemCall,  
	ThreadIoPriority,  
	ThreadCycleTime,  
	ThreadPagePriority,  
	ThreadActualBasePriority,  
	ThreadTebInformation,  
	ThreadCSwitchMon,          // Obsolete  
	ThreadCSwitchPmu,  
	ThreadWow64Context,  
	ThreadGroupInformation,  
	ThreadUmsInformation,      // UMS  
	ThreadCounterProfiling,  
	ThreadIdealProcessorEx,  
	MaxThreadInfoClass  
};
typedef NTSTATUS_ (WINAPI *NtQueryInformationThreadT)( HANDLE ThreadHandle, THREADINFOCLASS_ ThreadInformationClass, PVOID ThreadInformation, ULONG ThreadInformationLength, PULONG ReturnLength );
NtQueryInformationThreadT GetNtQueryInformationThread();
typedef struct  
{  
	DWORD ExitStatus;  
	DWORD PebBaseAddress;  
	DWORD AffinityMask;  
	DWORD BasePriority;  
	ULONG UniqueProcessId;  
	ULONG InheritedFromUniqueProcessId;  
}PROCESS_BASIC_INFORMATION;
enum PROCESSINFOCLASS{
	ProcessBasicInformation = 0,
	ProcessDebugPort = 7,
	ProcessWow64Information = 26,
	ProcessImageFileName = 27,
};
typedef NTSTATUS_ (WINAPI* NtQueryInformationProcessT)( IN HANDLE ProcessHandle, //���̾��
													   IN PROCESSINFOCLASS InformationClass, //��Ϣ����
													   OUT PVOID ProcessInformation, //����ָ��
													   IN ULONG ProcessInformationLength, //���ֽ�Ϊ��λ�Ļ����С
													   OUT PULONG ReturnLength OPTIONAL //д�뻺����ֽ���
													   );
NtQueryInformationProcessT GetNtQueryInformationProcess();

BOOL Get_GetVersionExW(LPOSVERSIONINFOW lpVersionInformation );

typedef struct _OBJECT_ATTRIBUTES
{
	ULONG Length;
	PVOID RootDirectory;
	PUNICODE_STRING ObjectName;
	ULONG Attributes;
	PVOID SecurityDescriptor;
	PVOID SecurityQualityOfService;
} OBJECT_ATTRIBUTES, *POBJECT_ATTRIBUTES;
typedef struct _NT_PROC_THREAD_ATTRIBUTE_ENTRY {
	ULONG Attribute;    // PROC_THREAD_ATTRIBUTE_XXX���μ�MSDN��UpdateProcThreadAttribute��˵��
	SIZE_T Size;        // Value�Ĵ�С
	ULONG_PTR Value;    // ����4�ֽ����ݣ�����һ��Handle��������ָ��
	ULONG Unknown;      // ����0�������������������ݸ�������
} PROC_THREAD_ATTRIBUTE_ENTRY, *PPROC_THREAD_ATTRIBUTE_ENTRY;
typedef struct _NT_PROC_THREAD_ATTRIBUTE_LIST {
	ULONG Length;       // �ṹ�ܴ�С
	PROC_THREAD_ATTRIBUTE_ENTRY Entry[1];
} NT_PROC_THREAD_ATTRIBUTE_LIST, *PNT_PROC_THREAD_ATTRIBUTE_LIST;
typedef NTSTATUS_ (WINAPI* NtCreateThreadEx)(
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
	);
NtCreateThreadEx GetNtCreateThreadEx();

typedef struct _INITIAL_TEB {
	PVOID                StackBase;
	PVOID                StackLimit;
	PVOID                StackCommit;
	PVOID                StackCommitMax;
	PVOID                StackReserved;
} INITIAL_TEB, *PINITIAL_TEB;
typedef NTSTATUS_(WINAPI* NtCreateThread)(                     // <��ز���˵��>
	__out PHANDLE ThreadHandle,     //���ش����̵߳ľ��
	__in ACCESS_MASK DesiredAccess, //�����̵߳ķ���Ȩ��
	__in_opt POBJECT_ATTRIBUTES ObjectAttributes, //ָ�����̶߳��������
	__in HANDLE ProcessHandle,      //���̾��
	__out PCLIENT_ID ClientId,      //�������̵߳�ClientId �ṹ
	__in PCONTEXT ThreadContext,    //���̵߳�ִ�л���
	__in PINITIAL_TEB InitialTeb,   //�ṩ���̵߳�TEB��ʼֵ
	__in BOOLEAN CreateSuspended    //�´������߳��Ƿ�Ҫ�ȱ�����
	);

typedef enum _OBJECT_INFORMATION_CLASS {
	ObjectBasicInformation,
	ObjectNameInformation,
	ObjectTypeInformation,
	ObjectAllInformation,
	ObjectDataInformation
} OBJECT_INFORMATION_CLASS, *POBJECT_INFORMATION_CLASS;
typedef NTSTATUS_(WINAPI*NtQueryObject)(
IN HANDLE               ObjectHandle,
IN OBJECT_INFORMATION_CLASS ObjectInformationClass,
OUT PVOID               ObjectInformation,
IN ULONG                Length,
OUT PULONG              ResultLength);
NtQueryObject GetNtQueryObject();
/*һ���ں˶�����������������һ���Ǿ������������Ǹ��û�̬�õģ���һ����ָ�������Ҳ�����ü�������Ϊ����̬Ҳ�����õ��ں˶���
Ϊ�˷��㣬�ں���̬�Ĵ�����ָ��ֱ�ӷ��ʶ�������Object   Managerά�������ָ�����ü�����
ֻ���ھ�����������ü�����Ϊ0ʱ������ű��ͷš�һ����ԣ�ָ�����ü���ֵ�Ⱦ������ֵ��*/
typedef struct _OBJECT_BASIC_INFORMATION {
	ULONG                   Attributes;
	ACCESS_MASK             DesiredAccess;
	ULONG                   HandleCount;	 //������� 
	ULONG                   ReferenceCount;	//ָ�����ü��� 
	ULONG                   PagedPoolUsage;
	ULONG                   NonPagedPoolUsage;
	ULONG                   Reserved[3];
	ULONG                   NameInformationLength;
	ULONG                   TypeInformationLength;
	ULONG                   SecurityDescriptorLength;
	LARGE_INTEGER           CreationTime;
} OBJECT_BASIC_INFORMATION, *POBJECT_BASIC_INFORMATION;
ULONG GetNtObjectHandleCount(HANDLE ObjectHandle);

typedef NTSTATUS_(WINAPI* ZwOpenProcess)(
	_Out_     PHANDLE ProcessHandle,
	_In_      ACCESS_MASK DesiredAccess,
	_In_      POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_  PCLIENT_ID ClientId
	);

typedef enum _SYSTEM_INFORMATION_CLASS {
	SystemBasicInformation,
	SystemProcessorInformation,             // obsolete...delete
	SystemPerformanceInformation,
	SystemTimeOfDayInformation,
	SystemPathInformation,
	SystemProcessInformation,
	SystemCallCountInformation,
	SystemDeviceInformation,
	SystemProcessorPerformanceInformation,
	SystemFlagsInformation,
	SystemCallTimeInformation,
	SystemModuleInformation,
	SystemLocksInformation,
	SystemStackTraceInformation,
	SystemPagedPoolInformation,
	SystemNonPagedPoolInformation,
	SystemHandleInformation,
	SystemObjectInformation,
	SystemPageFileInformation,
	SystemVdmInstemulInformation,
	SystemVdmBopInformation,
	SystemFileCacheInformation,
	SystemPoolTagInformation,
	SystemInterruptInformation,
	SystemDpcBehaviorInformation,
	SystemFullMemoryInformation,
	SystemLoadGdiDriverInformation,
	SystemUnloadGdiDriverInformation,
	SystemTimeAdjustmentInformation,
	SystemSummaryMemoryInformation,
	SystemMirrorMemoryInformation,
	SystemPerformanceTraceInformation,
	SystemObsolete0,
	SystemExceptionInformation,
	SystemCrashDumpStateInformation,
	SystemKernelDebuggerInformation,
	SystemContextSwitchInformation,
	SystemRegistryQuotaInformation,
	SystemExtendServiceTableInformation,
	SystemPrioritySeperation,
	SystemVerifierAddDriverInformation,
	SystemVerifierRemoveDriverInformation,
	SystemProcessorIdleInformation,
	SystemLegacyDriverInformation,
	SystemCurrentTimeZoneInformation,
	SystemLookasideInformation,
	SystemTimeSlipNotification,
	SystemSessionCreate,
	SystemSessionDetach,
	SystemSessionInformation,
	SystemRangeStartInformation,
	SystemVerifierInformation,
	SystemVerifierThunkExtend,
	SystemSessionProcessInformation,
	SystemLoadGdiDriverInSystemSpace,
	SystemNumaProcessorMap,
	SystemPrefetcherInformation,
	SystemExtendedProcessInformation,
	SystemRecommendedSharedDataAlignment,
	SystemComPlusPackage,
	SystemNumaAvailableMemory,
	SystemProcessorPowerInformation,
	SystemEmulationBasicInformation,
	SystemEmulationProcessorInformation,
	SystemExtendedHandleInformation,
	SystemLostDelayedWriteInformation,
	SystemBigPoolInformation,
	SystemSessionPoolTagInformation,
	SystemSessionMappedViewInformation,
	SystemHotpatchInformation,
	SystemObjectSecurityMode,
	SystemWatchdogTimerHandler,
	SystemWatchdogTimerInformation,
	SystemLogicalProcessorInformation,
	SystemWow64SharedInformation,
	SystemRegisterFirmwareTableInformationHandler,
	SystemFirmwareTableInformation,
	SystemModuleInformationEx,
	SystemVerifierTriageInformation,
	SystemSuperfetchInformation,
	SystemMemoryListInformation,
	SystemFileCacheInformationEx,
	MaxSystemInfoClass  // MaxSystemInfoClass should always be the last enum
} SYSTEM_INFORMATION_CLASS;

typedef LONG       KPRIORITY;
typedef struct _SYSTEM_THREADS{
	LARGE_INTEGER KernelTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER CreateTime;
	ULONG WaitTime;
	PVOID StartAddress;
	CLIENT_ID ClientId;
	KPRIORITY Priority;
	LONG BasePriority;
	ULONG ContextSwitches;
	ULONG ThreadState;
	ULONG WaitReason;
	ULONG Reversed;//add by achillis
} SYSTEM_THREAD_INFORMATION, *PSYSTEM_THREADS;
typedef struct _VM_COUNTERS
{
	ULONG PeakVirtualSize; //����洢��ֵ��С��
	ULONG VirtualSize; //����洢��С��
	ULONG PageFaultCount; //ҳ������Ŀ��
	ULONG PeakWorkingSetSize; //��������ֵ��С��
	ULONG WorkingSetSize; //��������С��
	ULONG QuotaPeakPagedPoolUsage; //��ҳ��ʹ������ֵ��
	ULONG QuotaPagedPoolUsage; //��ҳ��ʹ����
	ULONG QuotaPeakNonPagedPoolUsage;//�Ƿ�ҳ��ʹ������ֵ��
	ULONG QuotaNonPagedPoolUsage;//�Ƿ�ҳ��ʹ����
	ULONG PagefileUsage;//ҳ�ļ�ʹ�������
	ULONG PeakPagefileUsage;//ҳ�ļ�ʹ�÷�ֵ��
}VM_COUNTERS, *PVM_COUNTERS;
typedef struct _SYSTEM_PROCESSES{
	ULONG NextEntryDelta;
	ULONG ThreadCount;
	LARGE_INTEGER Reserved1[3];
	LARGE_INTEGER CreateTime;
	LARGE_INTEGER UserTime;
	LARGE_INTEGER KernelTime;
	UNICODE_STRING ProcessName;
	KPRIORITY BasePriority;
	ULONG ProcessId;
	ULONG InheritedFromProcessId;
	ULONG HandleCount;
	ULONG SessionId;
	ULONG_PTR PageDirectoryBase;
	VM_COUNTERS VmCounters;
	ULONG PrivatePageCount;// add by achillis
	IO_COUNTERS IoCounters;
	_SYSTEM_THREADS Threads[1];
} SYSTEM_PROCESSES, *PSYSTEM_PROCESSES;

#define MAXIMUM_FILENAME_LENGTH 256
typedef struct _SYSTEM_MODULE {
	ULONG                Reserved1;
	ULONG                Reserved2;
	PVOID                ImageBaseAddress;
	ULONG                ImageSize;
	ULONG                Flags;
	WORD                 Id;
	WORD                 Rank;
	WORD                 w018;
	WORD                 NameOffset;
	BYTE                 Name[MAXIMUM_FILENAME_LENGTH];
} SYSTEM_MODULE, *PSYSTEM_MODULE;

#pragma warning(push)
#pragma warning(disable:4200)
typedef struct _SYSTEM_MODULE_INFORMATION {
	ULONG                ModulesCount;
	SYSTEM_MODULE        Modules[0];
} SYSTEM_MODULE_INFORMATION, *PSYSTEM_MODULE_INFORMATION;
#pragma warning(pop)

typedef struct
{
	ULONG Unknown; //Always contains zero
	ULONG MaximumIncrement; //һ��ʱ�ӵļ�����λ
	ULONG PhysicalPageSize; //һ���ڴ�ҳ�Ĵ�С
	ULONG NumberOfPhysicalPages; //ϵͳ�����Ŷ��ٸ�ҳ
	ULONG LowestPhysicalPage; //�Ͷ��ڴ�ҳ
	ULONG HighestPhysicalPage; //�߶��ڴ�ҳ
	ULONG AllocationGranularity;
	ULONG LowestUserAddress; //�ض��û���ַ
	ULONG HighestUserAddress; //�߶��û���ַ
	ULONG ActiveProcessors; //����Ĵ�����
	UCHAR NumberProcessors; //�ж��ٸ�������
}SYSTEM_BASIC_INFORMATION, *PSYSTEM_BASIC_INFORMATION;

typedef LONG(WINAPI* ZwQuerySystemInformation)(
	__in        SYSTEM_INFORMATION_CLASS SystemInformationClass,
	__inout     PVOID SystemInformation,
	__in          ULONG SystemInformationLength,
	__out_opt    PULONG ReturnLength
	);

typedef struct _IO_STATUS_BLOCK
{
	LONG Status;
	ULONG_PTR Information;
}
IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;
typedef LONG (NTAPI* NtCreateFile)(
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
	IN ULONG                EaLength);

typedef HANDLE (WINAPI* RtlQueryProcessDebugInformation)(DWORD th32ProcessID, DWORD dwFlags, LPVOID Buffer);
//////////////////////////////////////////////////////////////////////////