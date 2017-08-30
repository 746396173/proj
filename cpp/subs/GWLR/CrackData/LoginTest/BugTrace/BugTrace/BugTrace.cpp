


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ͷ�ļ�
#include <Windows.h>
#include <string>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
#pragma comment(linker, "/EXPORT:CreateUploadBOSDDumpThread=_AheadLib_CreateUploadBOSDDumpThread,@1")
#pragma comment(linker, "/EXPORT:InitializeBugTrace=_AheadLib_InitializeBugTrace,@2")
#pragma comment(linker, "/EXPORT:SetBOSDDumpInfo=_AheadLib_SetBOSDDumpInfo,@3")
#pragma comment(linker, "/EXPORT:UploadBOSDDump=_AheadLib_UploadBOSDDump,@4")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �궨��
#define EXTERNC extern "C"
#define NAKED __declspec(naked)
#define EXPORT __declspec(dllexport)

#define ALCPP EXPORT NAKED
#define ALSTD EXTERNC EXPORT NAKED void __stdcall
#define ALCFAST EXTERNC EXPORT NAKED void __fastcall
#define ALCDECL EXTERNC NAKED void __cdecl
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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
		DWORD dwDoHookAddr = (DWORD)(void*)pfun;
		DWORD dwcAddr = dwDoHookAddr - dwHookAddr - 1 - 4;

		// �жϵ�ǰ��ַ�Ƿ�hook
		unsigned char readcode;
		ReadProcessMemory((void*)-1,(void*)dwHookAddr,&readcode,sizeof(readcode),NULL);

		if( readcode == code )
		{
			DWORD	dwReadAddr = 0;
			ReadProcessMemory((void*)-1,(void*)(dwHookAddr+1),&dwReadAddr,sizeof(dwReadAddr),NULL);

			if( dwReadAddr == dwcAddr )
			{
				return ;
			}
		}

		WriteProcessMemory((void*)-1,(void*)dwHookAddr,&code,1,NULL);

		WriteProcessMemory((void*)-1,(void*)(dwHookAddr+1),&dwcAddr,4,NULL);
	}
	catch (...)
	{
		MessageBoxA(NULL,"������","������",MB_OK);
	}
}


DWORD g_dwSysAllocStringAddr = 0;

void SysAllocStringPrint(wchar_t* pwszLoginStr)
{
	wchar_t wszPrint[1024] = {0};
	swprintf_s(wszPrint,L"[HOOK] %s",pwszLoginStr);
	OutputDebugStringW(wszPrint);
}

_declspec(naked) void HookSysAllocString()
{
	__asm
	{
		pushfd
		pushad

		push [esp+0x28]
		lea eax, SysAllocStringPrint
		call eax
		add esp, 4
	}

	__asm
	{
		popad
		popfd

		mov edi,edi
		push ebp
		mov ebp, esp

		mov eax, g_dwSysAllocStringAddr
		add eax, 5
		jmp eax
	}
}

// ��ȫģ������Ϻ󵽴���봦
void CheckModule()
{
	OutputDebugStringA("[HOOK] ��ȫģ�������!");
	MessageBoxA(NULL,"��ȫģ�������","",MB_OK);
}


DWORD	g_dwHookCheckModuleAddr = 0;
_declspec(naked) void HookCheckModule()
{
	__asm
	{
		pushfd
		pushad

		lea eax, CheckModule
		call eax
	}

	__asm
	{
		popad
		popfd

		XOR EAX,EAX
		POP ESI
		LEAVE
		RETN
	}
}

// ����˺�����״̬���˺Ŷ�����˺��������
void CheckLogin(wchar_t* pwszLoginStr)
{
	wchar_t wszPrint[1024] = {0};
	swprintf_s(wszPrint,L"[HOOK] %s",pwszLoginStr);
	OutputDebugStringW(wszPrint);
}

DWORD	g_dwCheckLoginAddr = 0;
_declspec(naked) void HookCheckLogin()
{
	__asm
	{
		pushfd
		pushad
		
		push [esp+0x28]
		lea eax, CheckLogin
		call eax
		add esp, 4
	}

	__asm
	{
		popad
		popfd

		mov edi,edi
		push ebp
		mov ebp, esp

		mov eax, g_dwCheckLoginAddr
		add eax, 5
		jmp eax
	}
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AheadLib �����ռ�
namespace AheadLib
{
	HMODULE m_hModule = NULL;	// ԭʼģ����
	DWORD m_dwReturn[4] = {0};	// ԭʼ�������ص�ַ


	// ����ԭʼģ��
	inline BOOL WINAPI Load()
	{
		char tzPath[MAX_PATH];
		char tzTemp[MAX_PATH * 2];

// 		GetSystemDirectory(tzPath, MAX_PATH);
// 		lstrcat(tzPath, TEXT("\\BugTrace"));
		m_hModule = LoadLibraryA(/*tzPath*/"BugTrace_2.dll");
		if (m_hModule == NULL)
		{
			sprintf_s(tzTemp, "�޷����� %s�������޷��������С�", tzPath);
			MessageBoxA(NULL, tzTemp, "AheadLib", MB_ICONSTOP);
		}

		char szProcessName[1024] = {0};
		GetProcessHostName(szProcessName);

		//#ifdef _DEBUG
		char szPrint[256] = {0};
		sprintf_s(szPrint,"[HOOK] ����:%s !!!",szProcessName);
		OutputDebugStringA(szPrint);
		//#endif

		if( strcmp(szProcessName,"TASLogin.exe") == 0 )
		{
			g_dwHookCheckModuleAddr = (DWORD)LoadLibraryA("SecureCheck.dll");
			if( g_dwHookCheckModuleAddr != 0 )
			{
				/*
				38023883 |8B4E 04 MOV ECX,DWORD PTR DS:[ESI+0x4]
				38023886 |83C4 0C ADD ESP,0xC
				38023889 |8D85 E0FBFFFF LEA EAX,DWORD PTR SS:[EBP-0x420]
				3802388F |50 PUSH EAX
				38023890 |E8 0EFFFFFF CALL SecureCh.380237A3
				38023895 |5F POP EDI
				38023896 \33C0 XOR EAX,EAX           ; HOOK   ƫ�� 0x23896
				38023898 5E POP ESI
				38023899 C9 LEAVE
				3802389A C3 RETN

				8B4E??83C4??8D85????????50E8????????5F33C0
				--*/
				g_dwHookCheckModuleAddr += 0x2500E; // 0x23896;
				Hook(g_dwHookCheckModuleAddr,HookCheckModule);
			}

			
			g_dwCheckLoginAddr = (DWORD)GetProcAddress(LoadLibraryA("oleaut32.dll"),"SysAllocStringLen");
			if( g_dwCheckLoginAddr != NULL )
			{
				Hook(g_dwCheckLoginAddr,HookCheckLogin);
			}

			
			g_dwSysAllocStringAddr = (DWORD)GetProcAddress(LoadLibraryA("oleaut32.dll"),"SysAllocString");

			if( g_dwSysAllocStringAddr != NULL )
			{
				Hook(g_dwSysAllocStringAddr,HookSysAllocString);
			}
		}


		return (m_hModule != NULL);	
	}
		
	// �ͷ�ԭʼģ��
	inline VOID WINAPI Free()
	{
		if (m_hModule)
		{
			FreeLibrary(m_hModule);
		}
	}

	// ��ȡԭʼ������ַ
	FARPROC WINAPI GetAddress(PCSTR pszProcName)
	{
		FARPROC fpAddress;
		CHAR szProcName[16];
		char tzTemp[MAX_PATH];

		fpAddress = GetProcAddress(m_hModule, pszProcName);
		if (fpAddress == NULL)
		{
			if (HIWORD(pszProcName) == 0)
			{
				sprintf_s(szProcName, "%d", pszProcName);
				pszProcName = szProcName;
			}

			sprintf_s(tzTemp, "�޷��ҵ����� %hs�������޷��������С�", pszProcName);
			MessageBoxA(NULL, tzTemp, "AheadLib", MB_ICONSTOP);
			ExitProcess(-2);
		}

		return fpAddress;
	}
}
using namespace AheadLib;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��ں���
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		return Load();
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		Free();
	}

	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL AheadLib_CreateUploadBOSDDumpThread(void)
{
	GetAddress("CreateUploadBOSDDumpThread");
	__asm JMP EAX;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL AheadLib_InitializeBugTrace(void)
{
	GetAddress("InitializeBugTrace");
	__asm JMP EAX;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL AheadLib_SetBOSDDumpInfo(void)
{
	GetAddress("SetBOSDDumpInfo");
	__asm JMP EAX;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL AheadLib_UploadBOSDDump(void)
{
	GetAddress("UploadBOSDDump");
	__asm JMP EAX;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
