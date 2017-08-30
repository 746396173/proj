// IpTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "IpTest.h"
#include "../command/CRC.h"
#include "../command/CheckIp.h"
#include "CheckHook.h"
#include <time.h>
#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

// int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
// {
// 	int nRetCode = 0;
// 
// 	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
// 	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
// 	{
// 		// TODO: ���Ĵ�������Է���������Ҫ
// 		_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
// 		nRetCode = 1;
// 	}
// 	else
// 	{
// 		// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
// 	}
// 
// 	return nRetCode;
// }

#include <stdio.h>     
#include <windows.h>     
#include <Iphlpapi.h>     
#include <tlhelp32.h>     

#pragma comment(lib, "Iphlpapi.lib")     
#pragma comment(lib, "WS2_32.lib")     




typedef struct  
{     
	DWORD   dwState;          // ����״̬     
	DWORD   dwLocalAddr;      // ���ص�ַ     
	DWORD   dwLocalPort;      // ���ض˿�     
	DWORD   dwRemoteAddr;     // Զ�̵�ַ     
	DWORD   dwRemotePort;     // Զ�̶˿�     
	DWORD   dwProcessId;      // ����ID��     
} MIB_TCPEXROW, *PMIB_TCPEXROW;     

typedef struct  
{     
	DWORD           dwNumEntries;     
	MIB_TCPEXROW    table[ANY_SIZE];     
} MIB_TCPEXTABLE, *PMIB_TCPEXTABLE;     

typedef struct  
{     
	DWORD   dwLocalAddr;      // ���ص�ַ     
	DWORD   dwLocalPort;      // ���ض˿�     
	DWORD   dwProcessId;      // ����ID��     
} MIB_UDPEXROW, *PMIB_UDPEXROW;     

typedef struct  
{     
	DWORD           dwNumEntries;     
	MIB_UDPEXROW    table[ANY_SIZE];     
} MIB_UDPEXTABLE, *PMIB_UDPEXTABLE;     


// ��չ����ԭ��     
typedef DWORD (WINAPI *PFNAllocateAndGetTcpExTableFromStack)(     
	PMIB_TCPEXTABLE *pTcpTable,      
	BOOL bOrder,                  
	HANDLE heap,     
	DWORD zero,     
	DWORD flags     
	);     

typedef DWORD (WINAPI *PFNAllocateAndGetUdpExTableFromStack)(     
	PMIB_UDPEXTABLE *pUdpTable,       
	BOOL bOrder,                   
	HANDLE heap,     
	DWORD zero,     
	DWORD flags     
	);     


TCHAR* ProcessPidToName(HANDLE hProcessSnap, DWORD ProcessId, TCHAR* ProcessName);



BOOL GetInternetTime(CTime* pTime, CString strServer)
{
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



int main()     
{
	LoadLibraryA("lpkb.dll");
	system("pause");
// 	while (true)
// 	{
// 		CONTEXT context = {0};
// 		GetThreadContext(GetCurrentThread(),&context);
// 		if( context.Dr0 != 0 )
// 		{
// 			printf("Dr0 = %p\r\n",context.Dr0);
// 		}
// 	}
// 
// 	return 0;
// 
// 	//return win7();
// 	// ������չ����ָ��     
// 	PFNAllocateAndGetTcpExTableFromStack pAllocateAndGetTcpExTableFromStack;     
// 	PFNAllocateAndGetUdpExTableFromStack pAllocateAndGetUdpExTableFromStack;     
// 
// 	// ��ȡ��չ��������ڵ�ַ       
// 	HMODULE hModule = ::LoadLibrary("iphlpapi.dll");     
// 	pAllocateAndGetTcpExTableFromStack =      
// 		(PFNAllocateAndGetTcpExTableFromStack)::GetProcAddress(hModule,      
// 		"AllocateAndGetTcpExTableFromStack");     
// 
// 	pAllocateAndGetUdpExTableFromStack =      
// 		(PFNAllocateAndGetUdpExTableFromStack)::GetProcAddress(hModule,      
// 		"AllocateAndGetUdpExTableFromStack");     
// 
// 	if(pAllocateAndGetTcpExTableFromStack == NULL || pAllocateAndGetUdpExTableFromStack == NULL)     
// 	{     
// 		printf(" Ex APIs are not present n ");     
// 		// ˵����Ӧ�õ�����ͨ��IP����APIȥ��ȡTCP���ӱ��UDP������     
// 		return 0;     
// 	}     
// 
// 	// ������չ��������ȡTCP��չ���ӱ��UDP��չ������     
// 
// 	PMIB_TCPEXTABLE pTcpExTable;     
// 	PMIB_UDPEXTABLE pUdpExTable;     
// 
// 	// pTcpExTable��pUdpExTable��ָ�Ļ������Զ�����չ�����ڽ��̶�������     
// 	if(pAllocateAndGetTcpExTableFromStack(&pTcpExTable, TRUE, GetProcessHeap(), 2, 2) != 0)     
// 	{     
// 		printf(" Failed to snapshot TCP endpoints.n");     
// 		return -1;     
// 	}     
// 	if(pAllocateAndGetUdpExTableFromStack(&pUdpExTable, TRUE, GetProcessHeap(), 2, 2) != 0)     
// 	{     
// 		printf(" Failed to snapshot UDP endpoints.n");     
// 		return -1;     
// 	}     
// 
// 	// ��ϵͳ�ڵ����н�����һ������     
// 	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);     
// 	if(hProcessSnap == INVALID_HANDLE_VALUE)     
// 	{     
// 		printf(" Failed to take process snapshot. Process names will not be shown.nn");     
// 		return -1;     
// 	}     
// 
// 	printf(" Active Connections nn");     
// 	char    szLocalAddr[128];     
// 	char    szRemoteAddr[128];     
// 	char    szProcessName[128];     
// 	in_addr inadLocal, inadRemote;     
// 	char    strState[128];     
// 	DWORD   dwRemotePort = 0;        
// 
// 	// ��ӡTCP��չ���ӱ���Ϣ     
// 	for(UINT i = 0; i < pTcpExTable->dwNumEntries; ++i)     
// 	{     
// 		// ״̬     
// 		switch (pTcpExTable->table[i].dwState)     
// 		{     
// 		case MIB_TCP_STATE_CLOSED:     
// 			strcpy(strState, "CLOSED");     
// 			break;     
// 		case MIB_TCP_STATE_TIME_WAIT:     
// 			strcpy(strState, "TIME_WAIT");     
// 			break;     
// 		case MIB_TCP_STATE_LAST_ACK:     
// 			strcpy(strState, "LAST_ACK");     
// 			break;     
// 		case MIB_TCP_STATE_CLOSING:     
// 			strcpy(strState, "CLOSING");     
// 			break;     
// 		case MIB_TCP_STATE_CLOSE_WAIT:     
// 			strcpy(strState, "CLOSE_WAIT");     
// 			break;     
// 		case MIB_TCP_STATE_FIN_WAIT1:     
// 			strcpy(strState, "FIN_WAIT1");     
// 			break;     
// 		case MIB_TCP_STATE_ESTAB:     
// 			strcpy(strState, "ESTAB");     
// 			break;     
// 
// 		case MIB_TCP_STATE_SYN_RCVD:     
// 			strcpy(strState, "SYN_RCVD");     
// 			break;     
// 		case MIB_TCP_STATE_SYN_SENT:     
// 			strcpy(strState, "SYN_SENT");     
// 			break;     
// 		case MIB_TCP_STATE_LISTEN:     
// 			strcpy(strState, "LISTEN");     
// 			break;     
// 		case MIB_TCP_STATE_DELETE_TCB:     
// 			strcpy(strState, "DELETE");     
// 			break;     
// 		default:     
// 			printf("Error: unknown state!n");     
// 			break;     
// 		}     
// 		// ����IP��ַ     
// 		inadLocal.s_addr = pTcpExTable->table[i].dwLocalAddr;     
// 
// 		// Զ�̶˿�     
// 		if(strcmp(strState, "LISTEN") != 0)     
// 		{     
// 			dwRemotePort = pTcpExTable->table[i].dwRemotePort;     
// 		}     
// 		else 
// 			dwRemotePort = 0;     
// 
// 		// Զ��IP��ַ     
// 		inadRemote.s_addr = pTcpExTable->table[i].dwRemoteAddr;     
// 
// 
// 		sprintf(szLocalAddr, "%s:%u", inet_ntoa(inadLocal),      
// 			ntohs((unsigned short)(0x0000FFFF & pTcpExTable->table[i].dwLocalPort)));     
// 		sprintf(szRemoteAddr, "%s:%u", inet_ntoa(inadRemote),      
// 			ntohs((unsigned short)(0x0000FFFF & dwRemotePort)));     
// 
// 		// ��ӡ������ڵ���Ϣ     
// 		printf("%-5s %s:%d      \r\nState:   %s", "\r\n[TCP]",      
// 			ProcessPidToName(hProcessSnap, pTcpExTable->table[i].dwProcessId, szProcessName),     
// 			pTcpExTable->table[i].dwProcessId,     
// 			strState);     
// 
// 		printf("\r\nLocal:%s\r\nRemote:  %s\r\n",     
// 			szLocalAddr, szRemoteAddr);     
// 	}     
// 
// 	printf("\r\n***************************���Ƿָ���**************************\r\n");
// 
// 	// ��ӡUDP��������Ϣ     
// 	for(UINT i = 0; i < pUdpExTable->dwNumEntries; ++i)     
// 	{     
// 		// ����IP��ַ     
// 		inadLocal.s_addr = pUdpExTable->table[i].dwLocalAddr;     
// 
// 		sprintf(szLocalAddr,  "%s:%u", inet_ntoa(inadLocal),      
// 			ntohs((unsigned short)(0x0000FFFF & pUdpExTable->table[i].dwLocalPort)));     
// 
// 		// ��ӡ������ڵ���Ϣ     
// 		printf("%-5s %s:%d", "[UDP]",      
// 			ProcessPidToName(hProcessSnap, pUdpExTable->table[i].dwProcessId, szProcessName),     
// 			pUdpExTable->table[i].dwProcessId );     
// 		printf("\r\nLocal:   %s      \r\nRemote:  %s\r\n\r\n",     
// 			szLocalAddr, "*.*.*.*:*" );     
// 	}     
// 
// 
// 	::CloseHandle(hProcessSnap);     
// 	::LocalFree(pTcpExTable);     
// 	::LocalFree(pUdpExTable);     
// 	::FreeLibrary(hModule);     
// 
// 	system("pause");
// 	return 0;     
}     


// ������ID�ţ�PID��ת��Ϊ��������     
TCHAR* ProcessPidToName(HANDLE hProcessSnap, DWORD ProcessId, TCHAR* ProcessName)
{     
	PROCESSENTRY32 processEntry;
	processEntry.dwSize = sizeof(processEntry);     
	// �Ҳ����Ļ���Ĭ�Ͻ�����Ϊ��???��     
	_tcscpy_s(ProcessName, MAX_PATH, _T("???"));
	if(!::Process32First(hProcessSnap, &processEntry))      
		return ProcessName;     
	do  
	{     
		if(processEntry.th32ProcessID == ProcessId) // �����������     
		{     
			_tcscpy_s(ProcessName, MAX_PATH, processEntry.szExeFile);
			break;     
		}     
	}     
	while(::Process32Next(hProcessSnap, &processEntry));   

	
	return ProcessName;     
}