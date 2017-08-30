#define __in_out

//4. ZwQuerySystemInformation

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
}SYSTEM_BASIC_INFORMATION,*PSYSTEM_BASIC_INFORMATION;

//
// System Information Classes.
//
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

typedef struct _CLIENT_ID
{
	PVOID UniqueProcess;
	PVOID UniqueThread;
} CLIENT_ID, *PCLIENT_ID;
typedef LONG       KPRIORITY;

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
}VM_COUNTERS,*PVM_COUNTERS;

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
} SYSTEM_THREAD_INFORMATION,*PSYSTEM_THREADS;

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


//  typedef struct _SYSTEM_PROCESS_INFORMATION
//  {
//      ULONG NextEntryOffset;
//      ULONG NumberOfThreads;
//      LARGE_INTEGER WorkingSetPrivateSize; // since VISTA
//      ULONG HardFaultCount; // since WIN7
//      ULONG NumberOfThreadsHighWatermark; // since WIN7
//      ULONGLONG CycleTime; // since WIN7
//      LARGE_INTEGER CreateTime;
//      LARGE_INTEGER UserTime;
//      LARGE_INTEGER KernelTime;
//      UNICODE_STRING ImageName;
//      KPRIORITY BasePriority;
//      HANDLE UniqueProcessId;
//      HANDLE InheritedFromUniqueProcessId;
//      ULONG HandleCount;
//      ULONG SessionId;
//      ULONG_PTR UniqueProcessKey; // since VISTA (requires SystemExtendedProcessInformation)
//      SIZE_T PeakVirtualSize;
//      SIZE_T VirtualSize;
//      ULONG PageFaultCount;
//      SIZE_T PeakWorkingSetSize;
//      SIZE_T WorkingSetSize;
//      SIZE_T QuotaPeakPagedPoolUsage;
//      SIZE_T QuotaPagedPoolUsage;
//      SIZE_T QuotaPeakNonPagedPoolUsage;
//      SIZE_T QuotaNonPagedPoolUsage;
//      SIZE_T PagefileUsage;
//      SIZE_T PeakPagefileUsage;
//      SIZE_T PrivatePageCount;
//      LARGE_INTEGER ReadOperationCount;
//      LARGE_INTEGER WriteOperationCount;
//      LARGE_INTEGER OtherOperationCount;
//      LARGE_INTEGER ReadTransferCount;
//      LARGE_INTEGER WriteTransferCount;
//      LARGE_INTEGER OtherTransferCount;
//      SYSTEM_THREAD_INFORMATION Threads[1];
// } SYSTEM_PROCESS_INFORMATION, *PSYSTEM_PROCESS_INFORMATION;

typedef struct _IO_STATUS_BLOCK
{
	LONG Status;
	ULONG_PTR Information;
}IO_STATUS_BLOCK, *PIO_STATUS_BLOCK;


#define STATUS_SUCCESS                          ((NTSTATUS)0x00000000L) // ntsubauth

