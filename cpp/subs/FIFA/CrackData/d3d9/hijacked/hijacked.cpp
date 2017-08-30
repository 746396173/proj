// hijacked.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "hijacked.h"
#include "updates.h"

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

// ChijackedApp

BEGIN_MESSAGE_MAP(ChijackedApp, CWinApp)
END_MESSAGE_MAP()

namespace AheadLib{
	BOOL WINAPI Load();
	VOID WINAPI Free();
}

// ChijackedApp ����

ChijackedApp::ChijackedApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

ChijackedApp::~ChijackedApp()
{
	using namespace AheadLib;
	Free();
}


// Ψһ��һ�� ChijackedApp ����

ChijackedApp theApp;
HANDLE g_hGameThread;

BOOL GetProcessHostFullName(char* pszFullFileName)
{
	DWORD dwResult = 0;
	::ZeroMemory((PBYTE)pszFullFileName, MAX_PATH);
	if (TRUE != ::IsBadReadPtr((PBYTE)pszFullFileName, MAX_PATH))
		dwResult = ::GetModuleFileNameA(
		NULL,                   // handle to module
		pszFullFileName,        // file name of module
		MAX_PATH                // size of buffer
		);

	return (dwResult != 0);
}

BOOL GetProcessHostName(char* pszFullFileName)
{
	BOOL  bResult;
	char  *pdest;

	int   ch = '\\';

	bResult = GetProcessHostFullName(pszFullFileName);
	if (bResult)
	{
		// Search backward 
		pdest = strrchr(pszFullFileName, ch);
		if( pdest != NULL )
			strcpy_s(pszFullFileName, MAX_PATH, &pdest[1]);
	} // if

	return bResult;
}


void Hook(DWORD dwHookAddr,LPVOID pfun)
{
	try
	{
		unsigned char code = 0xe9;
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

///////////////////////////////////////////////////////////////////////////////////////////
// HOOK   6D185163		SetCooperativeLevel
DWORD	g_dwSetCooperativeLevelAddr = 0;
#define DISCL_EXCLUSIVE     0x00000001
#define DISCL_NONEXCLUSIVE  0x00000002
#define DISCL_FOREGROUND    0x00000004
#define DISCL_BACKGROUND    0x00000008		//��̨ģʽ��һ������������DISCL_NONEXCLUSIVE���Ƕ�ռģʽ�����ʹ��
#define DISCL_NOWINKEY      0x00000010

void DoSetCooperativeLevel(HWND hWnd,DWORD dwFlags)
{
	char szPrint[256] = {0};
	sprintf_s(szPrint,"[LOG] hWnd = 0x%p  dwFlags = 0x%p",hWnd,dwFlags);
	OutputDebugStringA(szPrint);
}

__declspec(naked) void DoHookSetCooperativeLevel()
{
	MessageBoxA(NULL,"","",MB_OK);
	__asm
	{
		pushfd
		pushad
	}

// 	__asm
// 	{
// 		mov eax, DISCL_BACKGROUND
// 		or eax, DISCL_NONEXCLUSIVE
// 		mov dword ptr [esp+0x30], eax
// 
// 		mov eax, dword ptr [esp+0x30]
// 		mov ebx, dword ptr [esp+0x2c]
// 		push eax
// 		push ebx
// 		lea eax, DoSetCooperativeLevel
// 		call eax
// 		add esp, 8
// 	}

	__asm
	{
		popad
		popfd
		mov     edi, edi
		push    ebp
		mov     ebp, esp
		mov eax, g_dwSetCooperativeLevelAddr
		add eax, 5
		Jmp eax
	}
}



///////////////////////////////////////////////////////////////////////////////////////////
// HOOK GetDeviceState
DWORD	g_pFunGetDeviceStateAddr;

BOOL	g_bKeyBoardFlag = false;


bool g_IsSleepTime = false;		// �����Ż��õı�־�����������͹ر��Ż�
void PrintKeyBoard(int i)
{
	char szPrint[256] = {0};
	switch(i)
	{
	case DIK_ESCAPE:
		{
			sprintf_s(szPrint,"[LOG] ������ESC");
		}
		break;
	case DIK_A:
		{
			sprintf_s(szPrint,"[LOG] ������A");
		}
		break;
	case DIK_S:
		{
			sprintf_s(szPrint,"[LOG] ������S");
		}
		break;
	case DIK_D:
		{
			sprintf_s(szPrint,"[LOG] ������D");
		}
		break;
	case DIK_W:
		{
			sprintf_s(szPrint,"[LOG] ������W");
		}
		break;
	case DIK_Q:
		{
			sprintf_s(szPrint,"[LOG] ������Q");
		}
		break;
	case DIK_F3:
		{
			sprintf_s(szPrint,"[LOG] ������F3 �����Ż�");
			g_IsSleepTime = true;
		}
		break;
	case DIK_F4:
		{
			sprintf_s(szPrint,"[LOG] ������F4 �ر��Ż�");
			g_IsSleepTime = false;
		}
		break;
	default:
		{

		}
	}

	OutputDebugStringA(szPrint);
}

void DoGetDeviceState(byte* pKeyBuffer,int nlen)
{
	if( nlen == 0x100 )
	{
		for(int i = 0; i < 256; i++ ) 
		{
			if( pKeyBuffer[i] & 0x80 ) 
			{
				PrintKeyBoard(i);
			}
			else
			{
				continue;
				if( DIK_ESCAPE == i )
				{
					if( g_bKeyBoardFlag == FALSE )
					{
						pKeyBuffer[DIK_ESCAPE] = 0x80;
						PrintKeyBoard(i);
						g_bKeyBoardFlag = TRUE;
					}
					else if( g_bKeyBoardFlag == TRUE )
					{
						g_bKeyBoardFlag = FALSE;
					}
				}
			}
			
		}
	}
}

__declspec(naked) void DoHookGetDeviceState()
{
	__asm
	{
		pushfd
		pushad
	}

	__asm
	{
		mov eax, dword ptr [esp+0x30]
		mov ebx, dword ptr [esp+0x2c]
		push ebx
		push eax
		lea eax, DoGetDeviceState
		call eax
		add esp, 8
	}

	__asm
	{
		popad
		popfd
		retn 0x0c
	}
}


//////////////////////////////////////////////////////////////////////////////////////////
// HOOK ��Ϸ��յ��� GetDeviceState
DWORD	g_pFunGameGetDeviceStateAddr = 0x00B829D6;
#define	GAME_GETDEVICESTATE_JNZ		0x00B82D23
// $+2      01167F02          85C0            test    eax, eax
// $+4      01167F04          0F85 17030000   jnz     fifazf.01168221			01168221 - 0x01167F02 = 0x31f
// $+A      01167F0A          3943 08         cmp     dword ptr ds:[ebx+8], eax	01167F0A - 0x01167F02 = 8

__declspec(naked) void DoHookGameGetDeviceState()
{
	__asm
	{
		pushfd
		pushad
	}

	__asm
	{
		push 0x100
		lea eax, [EBP-0x104]
		push eax
		lea eax, DoGetDeviceState
		call eax
		add esp, 8
	}

	__asm
	{
		popad
		popfd
	}

	__asm
	{
		test    eax, eax
		jnz     GAME_GETDEVICESTATE_JNZ
		mov		ecx, g_pFunGameGetDeviceStateAddr
		add		ecx, 0x8
		jmp		ecx
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//	�޸���Ϸ���,��dinput��Ϊ��̨ģʽor����ģʽ  01167354 6A 06 PUSH 0x6			
#define GAME_SETCOOPERATIVELEVEL	0x01167354

void DoGameSetCooperativeLevel()
{
 	unsigned char code = 0x0a;
 	WriteProcessMemory((HANDLE)-1,(void*)(GAME_SETCOOPERATIVELEVEL+1),&code,1,NULL);
}



int SleepTime(int nTime)
{
	if( g_IsSleepTime )
	{
		static int nCount = 0;

		if( nCount++ > 20 )
		{
			OutputDebugStringA("[LOG] ˢ��һ��!");
			nCount = 0;
			return 0;
		}

		Sleep(nTime);
		return 1;	// ����1 �����Ż�ģʽ
	}

	return 0;		// ����0 �����κ�����
}

_declspec(naked) void SleepMainThread()
{
	__asm
	{
		pushfd
		pushad

		push 50
		lea eax, SleepTime
		call eax
		add esp, 4

		test eax, eax
		jnz FIFA_RENDER_RETURN

		popad
		popfd

		PUSH EBX
		PUSH ESI
		PUSH EDI
		MOV EDI,ECX

		mov ecx, UPDATES_FIFA_REVERSAL_STOP_RENDER_AND_SLEEP_HOOK  
		add ecx, 5
		jmp ecx
FIFA_RENDER_RETURN:

		popad
		popfd
		retn
	}
}

// ChijackedApp ��ʼ��

BOOL ChijackedApp::InitInstance()
{
	CWinApp::InitInstance();

	char szProcessName[MAX_PATH] = {0};
	GetProcessHostName(szProcessName);

#ifdef _DEBUG
	char szPrint[256] = {0};
	sprintf_s(szPrint,"[HIJACKED] ����:%s !!!",szProcessName);
	OutputDebugStringA(szPrint);
#endif

	if( strcmp(szProcessName,"fifazf.exe") == 0 || strcmp(szProcessName,"keyboard.exe") == 0 )
	{
		
		// ��������Ҫ�Ķ���
		HMODULE hdll = LoadLibraryA("dinput8.dll");
		if( hdll )
		{
// 			DoGameSetCooperativeLevel();
 			Hook(g_pFunGameGetDeviceStateAddr,DoHookGameGetDeviceState);		// hook dx

			Hook(UPDATES_FIFA_REVERSAL_STOP_RENDER_AND_SLEEP_HOOK,SleepMainThread);	// hook render �Ż�

			g_pFunGetDeviceStateAddr = (DWORD)hdll + 0x80A7;
			//Hook(g_pFunGetDeviceStateAddr+0x0BE,DoHookGetDeviceState);

			g_dwSetCooperativeLevelAddr = (DWORD)hdll + 0x477F;//0x5163;
			//Hook(g_dwSetCooperativeLevelAddr,DoHookSetCooperativeLevel);

// 			g_dwSetCooperativeLevelAddr = 0x0119C0C6;
// 			byte bCode[] = {0x6a,0x0a,0x90,0x90};
// 			WriteProcessMemory( (HANDLE)-1,(void*)g_dwSetCooperativeLevelAddr,bCode,4,NULL);
		}
		
		using namespace AheadLib;
		return Load();
	}

	if( strcmp(szProcessName,"fifalauncher.exe") == 0 || strcmp(szProcessName,"Client.exe") == 0 )
	{
		using namespace AheadLib;
		return Load();
	}

	return FALSE;

}
