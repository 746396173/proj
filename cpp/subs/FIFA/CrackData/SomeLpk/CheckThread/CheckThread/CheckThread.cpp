// CheckThread.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "CheckThread.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include <stdio.h>
#include <windows.h>
#include <winbase.h>
#include <ntsecapi.h>
#include <time.h>
#include <afxsock.h>

//#define UNICODE
#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)
#define STATUS_SUCCESS              ((NTSTATUS) 0x00000000)
#define STATUS_INFO_LENGTH_MISMATCH ((NTSTATUS) 0xC0000004)
#define SystemProcessesAndThreadsInformation    5
#define NTAPI    __stdcall

typedef enum _THREAD_STATE
{
    StateInitialized,
    StateReady,
    StateRunning,
    StateStandby,
    StateTerminated,
    StateWait,
    StateTransition,
    StateUnknown
}THREAD_STATE;

typedef enum _KWAIT_REASON
{
    Executive,
    FreePage,
    PageIn,
    PoolAllocation,
    DelayExecution,
    Suspended,
    UserRequest,
    WrExecutive,
    WrFreePage,
    WrPageIn,
    WrPoolAllocation,
    WrDelayExecution,
    WrSuspended,
    WrUserRequest,
    WrEventPair,
    WrQueue,
    WrLpcReceive,
    WrLpcReply,
    WrVirtualMemory,
    WrPageOut,
    WrRendezvous,
    Spare2,
    Spare3,
    Spare4,
    Spare5,
    Spare6,
    WrKernel,
    MaximumWaitReason
}KWAIT_REASON;

typedef NTSTATUS (WINAPI *PNTRAISE)(NTSTATUS,
                                    ULONG,
                                    ULONG,
                                    PULONG,
                                    UINT,
                                    PULONG);    


typedef LONG NTSTATUS;
typedef LONG    KPRIORITY;

typedef struct _CLIENT_ID {
    DWORD        UniqueProcess;
    DWORD        UniqueThread;
} CLIENT_ID, * PCLIENT_ID;


typedef struct _VM_COUNTERS {
    SIZE_T        PeakVirtualSize;
    SIZE_T        VirtualSize;
    ULONG        PageFaultCount;
    SIZE_T        PeakWorkingSetSize;
    SIZE_T        WorkingSetSize;
    SIZE_T        QuotaPeakPagedPoolUsage;
    SIZE_T        QuotaPagedPoolUsage;
    SIZE_T        QuotaPeakNonPagedPoolUsage;
    SIZE_T        QuotaNonPagedPoolUsage;
    SIZE_T        PagefileUsage;
    SIZE_T        PeakPagefileUsage;
} VM_COUNTERS;


typedef struct _SYSTEM_THREAD_INFORMATION {
    LARGE_INTEGER   KernelTime;
    LARGE_INTEGER   UserTime;
    LARGE_INTEGER   CreateTime;
    ULONG            WaitTime;
    PVOID            StartAddress;
    CLIENT_ID        ClientId;
    KPRIORITY        Priority;
    KPRIORITY        BasePriority;
    ULONG            ContextSwitchCount;
    LONG            State;
    LONG            WaitReason;
} SYSTEM_THREAD_INFORMATION, * PSYSTEM_THREAD_INFORMATION;



typedef struct _SYSTEM_PROCESS_INFORMATION {
    ULONG            NextEntryDelta;
    ULONG            ThreadCount;
    ULONG            Reserved1[6];
    LARGE_INTEGER   CreateTime;
    LARGE_INTEGER   UserTime;
    LARGE_INTEGER   KernelTime;
    UNICODE_STRING ProcessName;
    KPRIORITY        BasePriority;
    ULONG            ProcessId;
    ULONG            InheritedFromProcessId;
    ULONG            HandleCount;
    ULONG            Reserved2[2];
    VM_COUNTERS        VmCounters;
    IO_COUNTERS        IoCounters;
    SYSTEM_THREAD_INFORMATION Threads[5];
} SYSTEM_PROCESS_INFORMATION, * PSYSTEM_PROCESS_INFORMATION;



typedef DWORD (WINAPI* PQUERYSYSTEM)(UINT, PVOID, DWORD,PDWORD);

/************************************************************************/
/* ����˵����
   ������dwThreadID �����߳�ID ,������Ҫ����֤�̵߳�ID
             szProcessName,��ʾ�߳����ڵĽ�����

����ֵ��
       true�� ��ʾ�̱߳�����
       false�� ��ʾ�߳�������

*/
/************************************************************************/

BOOL IsThreadSuspend(DWORD dwThreadID,wchar_t *szProcessName)
{
    ULONG cbBuffer = 0x5000;
    
    BOOL bRet = FALSE;

    LPVOID pBuffer = NULL;
    NTSTATUS Status;


    DWORD b=0;

    PQUERYSYSTEM NtQuerySystemInformation;
    PSYSTEM_PROCESS_INFORMATION pInfo ;

    NtQuerySystemInformation = (PQUERYSYSTEM) GetProcAddress(
        LoadLibraryA( "ntdll.dll" ),
        "NtQuerySystemInformation" );

    do
    {
        pBuffer = malloc(cbBuffer);
        if (pBuffer == NULL)
        {
            break;
        }

        Status = NtQuerySystemInformation(
            SystemProcessesAndThreadsInformation,
            pBuffer, cbBuffer, NULL);

        if (Status == STATUS_INFO_LENGTH_MISMATCH)
        {
            free(pBuffer);
            cbBuffer *= 2;
        }
        else if (!NT_SUCCESS(Status))
        {
            free(pBuffer);
        }

    }   while (Status == STATUS_INFO_LENGTH_MISMATCH);


    pInfo = (PSYSTEM_PROCESS_INFORMATION)pBuffer;

    for (;;)
    {


        if (pInfo->NextEntryDelta == 0)
		{
            break;
		}

		wprintf(L"%s\r\n",pInfo->ProcessName.Buffer);

        if(pInfo->ProcessName.Buffer!=NULL &&
            !_wcsicmp(pInfo->ProcessName.Buffer,szProcessName))
        {

            for(b=0;b<pInfo->ThreadCount ;b++)
            {
                if(pInfo->Threads[b].ClientId.UniqueThread == dwThreadID ) //�ҵ��߳�               
                {

                    if(pInfo->Threads[b].State == StateWait && pInfo->Threads[b].WaitReason == Suspended) //�̱߳�����
                    {
                        bRet = TRUE;
                        break;
                    }
                }
            }
            break;
        
        }
        pInfo = (PSYSTEM_PROCESS_INFORMATION)(((PUCHAR)pInfo) +    pInfo->NextEntryDelta);
    }

    free(pBuffer);
    return bRet;
}    


/**************************************************************/
/*�ж��߳��Ƿ���ֹ , �����ֹ����FALSE,��������ŷ���TRUE
/**************************************************************/

BOOL IsThreadAlive(DWORD dwThreadID)
{
    BOOL bRet = FALSE;
    DWORD ExitCode = 0;

    HANDLE hThread = OpenThread(THREAD_QUERY_INFORMATION,FALSE,dwThreadID);
    if(hThread != NULL)
    {
        if(GetExitCodeThread(hThread,&ExitCode))
        {
            if( ExitCode == STILL_ACTIVE)
                bRet = TRUE;
        }

        CloseHandle(hThread);
    }

    return bRet;
}

// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;


BOOL GetInternetTime(CTime* pTime, CString strServer)
{
	AfxSocketInit();

	CSocket sockClient;
	sockClient.Create();			//����socket

	sockClient.Connect((LPCTSTR)strServer, 37); // strServer��ʱ���������ַ�� 37���˿ں�


	DWORD dwTime = 0;				//������ŷ����������ı�׼ʱ������
	unsigned char nTime[8];			//��ʱ��������
	memset(nTime, 0, sizeof(nTime));

	sockClient.Receive(nTime, sizeof(nTime));	//���շ�������������4���ֽڵ�����
	sockClient.Close();				//�ر�socket


	dwTime += nTime[0] << 24;		//��������	
	dwTime += nTime[1] << 16;
	dwTime += nTime[2] << 8;
	dwTime += nTime[3];		

	if(0 == dwTime)	return FALSE;


	//�������������������Դ�1900������������
	//ȡ�� 1900~1970 ��ʱ���(����������) ������dwSpan����
	COleDateTime t00( 1900, 1, 1, 0, 0, 0 ); // 1900.1.1 00:00:00 
	COleDateTime t70( 1970, 1, 1, 0, 0, 0 ); // 1970.1.1 00:00:00 

	COleDateTimeSpan ts70to00 = t70 - t00; 
	DWORD dwSpan = 0x83AA7E80;(DWORD)ts70to00.GetTotalSeconds(); 
	ASSERT( dwSpan == 2208988800L ); 

	//��ʱ���Ϊ����1970��ģ�������CTime����
	dwTime -= dwSpan;		

	//���쵱ǰʱ���CTime����
	CTime timeNow(dwTime); //  = (CTime)dwTime;

	CString s = timeNow.Format("%Y.%m.%d  %H:%M:%S \r\n");

	return TRUE;
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	CTime tm(1990, 1, 1, 0, 0, 0);
	CString strServer("time.ien.it");

	if(GetInternetTime(&tm, strServer))
	{

	}

// 	BOOL bRET =IsThreadSuspend(2380,L"notepad.EXE");
// 
// 	if(bRET)
// 	{
// 		printf(" 2320�̱߳������ˣ�");
// 	}
	return 0;
}
