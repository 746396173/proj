// CheckCrack.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "CheckCrack.h"
#include "../command/CheckThrad.h"
#include <process.h>
#include "../protect/CheckLpk.h"
#include <CD_CommonFiles/CD_AntiCrack.h>
#include "../command/CRC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CCheckCrackApp

BEGIN_MESSAGE_MAP(CCheckCrackApp, CWinApp)
END_MESSAGE_MAP()


// CCheckCrackApp ����

CCheckCrackApp::CCheckCrackApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	m_hCheckCrackThread = NULL;
}

// Ψһ��һ�� CCheckCrackApp ����

CCheckCrackApp theApp;
bool g_bConnectFlag = true;

// ����ʹ�ã���hookĳһ��ַ�󣬴���hook�ĵ�ַ���洢��ĳ�����У��ڼ���ʱ��ֻ��Ҫ�ٴε��ã����жϷ���ֵ
DWORD	GetHookGoalAddr(DWORD dwHookAddr)
{
	DWORD	dwHookGoalAddr = 0;
	dwHookAddr++;
	__asm
	{
		mov eax, dwHookAddr
		mov ebx, dword ptr [eax]
		mov dwHookGoalAddr, ebx
	}

	// 	char szPrint[256] = {0};
	// 	sprintf_s(szPrint,"[LOG] %p : %p ==> %p call ==> %p",dwHookAddr,dwHookAddr+4,dwHookGoalAddr,dwHookAddr+4+dwHookGoalAddr);
	// 	OutputDebugString(szPrint);
	return dwHookAddr+4+dwHookGoalAddr;
}

HANDLE	g_hBackUpThread = NULL;
DWORD	g_dwBackUpThreadId = 0;
HANDLE	g_hProcess = NULL;
bool    g_bCheckThreadRunFlag = false;

typedef struct
{
	DWORD	dwFunAddr;		// ������ַ
	DWORD	dwHookAddr;		// ����hook�����ת��ַ
}CHECK_HOOK_ADDR,*PCHECK_HOOK_ADDR;

CHECK_HOOK_ADDR	theConnect;

bool g_bConnectCodeCRCflag = false;		// ���ӷ�����ʱ�Կ���̨���� CRC���
DWORD g_dwConnectCodeCRC = 0;

typedef int (WINAPI *PCONNECT)(
								SOCKET s,                          
								const struct sockaddr FAR *name,  
								int namelen                        
								);

PCONNECT	Old_connect;
PCONNECT	Jmp_Old_connect;

// struct sockaddr {
// 	u_short sa_family;              /* address family */
// 	char    sa_data[14];            /* up to 14 bytes of direct address */
// };

int WINAPI CHECKconnect(
			SOCKET s,                          
			const struct sockaddr FAR *name,  
			int namelen                        
			)
{
	// ����CRC
	PIMAGE_DOS_HEADER	    pDosHeader=NULL;
	PIMAGE_NT_HEADERS       pNtHeader=NULL;
	PIMAGE_SECTION_HEADER   pSecHeader=NULL;
	DWORD					ImageBase;
	DWORD					dwCodeCrc = 0;
	unsigned char*			pCheckCodeBaseAddr = NULL;
	IMAGE_OPTIONAL_HEADER32* pImageOptionalHeader32 = NULL;
	IMAGE_SECTION_HEADER*	pImageSectionHeader = NULL;

	try
	{
		ImageBase=(DWORD)GetModuleHandle(NULL);//ȡ��ַ����ʵ����Ҳ��ֱ����0x4000000���ֵ

		pDosHeader=(PIMAGE_DOS_HEADER)ImageBase;	 	 
		pNtHeader=(PIMAGE_NT_HEADERS32)((DWORD)pDosHeader+pDosHeader->e_lfanew);
		pSecHeader=IMAGE_FIRST_SECTION(pNtHeader);   //�õ���һ���������ʼ��ַ  
		pImageOptionalHeader32 = (IMAGE_OPTIONAL_HEADER32*)((DWORD)pDosHeader+pDosHeader->e_lfanew+sizeof(IMAGE_FILE_HEADER)+sizeof(DWORD));
		pImageSectionHeader = (IMAGE_SECTION_HEADER*)((DWORD)pDosHeader+pDosHeader->e_lfanew+sizeof(IMAGE_FILE_HEADER)+sizeof(DWORD)+sizeof(IMAGE_OPTIONAL_HEADER32));
		pCheckCodeBaseAddr = (unsigned char*)(ImageBase+pSecHeader->VirtualAddress);

		CRC32_INLINE(pCheckCodeBaseAddr,pImageSectionHeader->Misc.PhysicalAddress,dwCodeCrc);
	}
	catch (...)
	{
		assert(false);
	}

	VMP_BEGIN_EX;

	try
	{
		// ���￪ʼ ���� ����
		DWORD dwCodeCrcTemp = 0;
		for (int i=0;i<1000; i++)
		{
			dwCodeCrcTemp += dwCodeCrc;
		}

		if( dwCodeCrcTemp == 0 )
		{
			g_dwConnectCodeCRC = dwCodeCrcTemp;
		}
		// ���� ���ŷ���
	}
	catch (...)
	{
		assert(false);
	}

	try
	{
		sockaddr_in* pname = (sockaddr_in*)name;

		if( IP == XOR_DWORD(*(DWORD*)&pname->sin_addr) ||
			IP1 == XOR_DWORD(*(DWORD*)&pname->sin_addr) ||
			IP2 == XOR_DWORD(*(DWORD*)&pname->sin_addr) ||
			IP3 == XOR_DWORD(*(DWORD*)&pname->sin_addr) ||
			IP4 == XOR_DWORD(*(DWORD*)&pname->sin_addr) ||
			IP5 == XOR_DWORD(*(DWORD*)&pname->sin_addr) ||
			IP6 == XOR_DWORD(*(DWORD*)&pname->sin_addr) )
		{
			g_bConnectFlag = true;			// ������ڰ�������ip�����ñ�־Ϊtrue
			DEBUG_PRINT("hook connect server");

#ifdef	_OPEN_CRC_

			// ��ȡlpkд���crc
			static DWORD dwLpkCRC = *(DWORD*)(pCheckCodeBaseAddr+pImageSectionHeader->Misc.PhysicalAddress);

#ifdef _DEBUG_LOG_
			char szPrint[256];
			sprintf_s(szPrint,"[LOG] CHECKconnect code addr = 0x%p size = 0x%p lpk crc = 0x%p crc = 0x%p ip = %d.%d.%d.%d",
				ImageBase+pSecHeader->VirtualAddress,pImageSectionHeader->Misc.PhysicalAddress,dwLpkCRC,dwCodeCrc,
				pname->sin_addr.S_un.S_un_b.s_b1,
				pname->sin_addr.S_un.S_un_b.s_b2,
				pname->sin_addr.S_un.S_un_b.s_b3,
				pname->sin_addr.S_un.S_un_b.s_b4);
			OutputDebugStringA(szPrint);
#endif

			if( dwLpkCRC != dwCodeCrc )
			{
#ifdef _DEBUG_LOG_
				OutputDebugStringA("[LOG] connect crc error!");
#endif
				g_bConnectFlag = false;	// ����ʧ��
				return WSAEADDRNOTAVAIL;
			}
#endif

		}
	}
	catch (...)
	{
		assert(false);
	}

	VMP_END;

	return Jmp_Old_connect(s,name,namelen);
}

reversalsock	theSocket;
// CCheckCrackApp ��ʼ��
unsigned int __stdcall CheckCrackThreadProc(
									LPVOID lpParameter)
{
	CheckIp theCheckIp;
	try
	{
		CheckLpk theCheckLpk;

#if _DEBUG
		pthePacket = new FIFAPacket;
		if( pthePacket == NULL )
		{
			assert(false);
			return 0;
		}
		ptheDBConnectionManager	= new FIFADBConnectionManager;
		if( ptheDBConnectionManager == NULL )
		{
			assert(false);
			return 0;
		}
		if( false == theSocket.bind("lpkb_fifa",&theSocket.m_hsocket.m_theScrSocket) )
		{
			assert(false);
			return 0;
		}

		while( g_bCheckThreadRunFlag )
		{
			if( theCheckIp.CheckTcp() == false )
			{
				DEBUG_PRINT("CheckCrackThreadProc local host error1!");
				return false;
			}
		}

		if( pthePacket != NULL )
		{
			delete pthePacket;
			pthePacket = NULL;
		}
#else
		const BYTE* pszConsoleVersion = (BYTE*)theCheckLpk.LpkOpenConsoleFileMapping(VMProtectDecryptString(kCheckFileMapName));

		if( pszConsoleVersion != NULL )
		{
			BYTE bCheckConsoleVersionKey = (BYTE)(pszConsoleVersion[kKeyValueOffset]^GetCurrentProcessId());

			if( bCheckConsoleVersionKey == kXorConstValue )
			{
				pthePacket = new FIFAPacket;
				if( pthePacket == NULL )
				{
					assert(false);
					return 0;
				}
				ptheDBConnectionManager	= new FIFADBConnectionManager;
				if( ptheDBConnectionManager == NULL )
				{
					assert(false);
					return 0;
				}
				if( false == theSocket.bind("lpkb_fifa",&theSocket.m_hsocket.m_theScrSocket) )
				{
					assert(false);
					return 0;
				}

				while( g_bCheckThreadRunFlag )
				{
					if( theCheckIp.CheckTcp() == false )
					{
						DEBUG_PRINT("CheckCrackThreadProc local host error1!");
						return false;
					}
				}

				if( pthePacket != NULL )
				{
					delete pthePacket;
					pthePacket = NULL;
				}
			}
		}
#endif

		
	}
	catch (...)
	{
		VERIFY(false);
	}

	return 0;
}

BOOL CCheckCrackApp::InitInstance()
{
	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	VMP_BEGIN_EX;

	g_hProcess = (HANDLE)XOR_DWORD(GetCurrentProcessId());


	unsigned int dwThreadId = 0;
	m_hCheckCrackThread = (HANDLE)_beginthreadex(NULL,0,CheckCrackThreadProc,NULL,0,&dwThreadId);

	g_hBackUpThread = (HANDLE)XOR_DWORD(m_hCheckCrackThread);
	g_dwBackUpThreadId = XOR_DWORD(dwThreadId);

	if( m_hCheckCrackThread == NULL )
	{
		DEBUG_PRINT("m_hCheckCrackThread error");
		assert(false);
		return FALSE;
	}

	g_bCheckThreadRunFlag = true;
	//by zhp, 2016/12/19 16:59ȥ��CRC���
	/*Old_connect = (PCONNECT)GetProcAddress(GetModuleHandleA("Ws2_32.dll"), VMProtectDecryptString("connect"));
	if( Old_connect != NULL )
	{
		HOOKEX(Old_connect,CHECKconnect,Jmp_Old_connect);
		theConnect.dwFunAddr = (DWORD)Old_connect;
		theConnect.dwHookAddr = GetHookGoalAddr(theConnect.dwFunAddr);
		assert(theConnect.dwHookAddr);
		DEBUG_PRINT("hook connect success");

		g_bCheckThreadRunFlag = true;
	}*/

	DEBUG_PRINT("Init success!");
	VMP_END;
	return TRUE;
}

int CCheckCrackApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���

	g_bCheckThreadRunFlag = false;

	if( m_hCheckCrackThread != NULL )
	{
		CloseHandle(m_hCheckCrackThread);
		m_hCheckCrackThread = NULL;
		
	}
	return CWinApp::ExitInstance();
}
