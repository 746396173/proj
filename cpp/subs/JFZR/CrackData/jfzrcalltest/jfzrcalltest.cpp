// jfzrcalltest.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "jfzrcalltest.h"
#include "jfzrbase.h"
#include "InjectedWnd.h"
#include <process.h>
#include <mswsock.h>

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

// CjfzrcalltestApp

BEGIN_MESSAGE_MAP(CjfzrcalltestApp, CWinApp)
END_MESSAGE_MAP()


// CjfzrcalltestApp ����

CjfzrcalltestApp::CjfzrcalltestApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CjfzrcalltestApp ����

CjfzrcalltestApp theApp;

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

		//if( readcode == code )
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
		MessageBox(NULL,"������","������",MB_OK);
	}
}


DWORD	g_dwSendObjAddr = 0;
typedef DWORD (*PGetAllmMemorySendObjAddr)();

void InitBase()
{
	g_dwSendObjAddr = (DWORD)((PGetAllmMemorySendObjAddr)GetProcAddress(LoadLibrary("d3d9.dll"),"GetAllmMemorySendObjAddr")());

	assert(g_dwSendObjAddr);
}

BOOL _ReadProcessMemory(DWORD dwReadAddr,void* pReadData,DWORD dwReadlen)
{
	return ::ReadProcessMemory((HANDLE)-1,(LPCVOID)dwReadAddr,pReadData,dwReadlen,0);
}

BOOL _WriteProcessMemory(DWORD dwWriteAddr,void* pWriteData,DWORD dwWritelen)
{
	return ::WriteProcessMemory((HANDLE)-1,(LPVOID)dwWriteAddr,pWriteData,dwWritelen,0);
}


// typedef struct
// {
// 	DWORD	dwAddr1;
// 	DWORD	dwAddr2;
// 	DWORD	dwBufferBeginAddr1;
// 	DWORD	dwBufferEndAddr;
// 	DWORD	dwBufferBeginAddr2;
// }GAME_BUIILD_OBJ,*PGAME_BUIILD_OBJ;

typedef int (*PACKET)(const char* pszSayBufffer, char* pOutszSendBuffer);

// ����
int SayPacket( const char* pszSayBufffer, char* pOutszSendBuffer)
{
	int nLen = strlen(pszSayBufffer)+1;
	*(WORD*)pOutszSendBuffer = nLen+0x1a;		// ��������Ĵ�С
	*(WORD*)(pOutszSendBuffer+2) = 0x55e0;
	*(WORD*)(pOutszSendBuffer+4) = 0x4a94;
	*(DWORD*)(pOutszSendBuffer+6) = 2;
	*(DWORD*)(pOutszSendBuffer+10) = 1;
	*(WORD*)(pOutszSendBuffer+14) = 0x65;
	*(DWORD*)(pOutszSendBuffer+16) = 0x393cb607;
	*(DWORD*)(pOutszSendBuffer+20) = 1;
	*(WORD*)(pOutszSendBuffer+24) = nLen;
	memcpy(pOutszSendBuffer+26, pszSayBufffer,nLen);
	return (int)*(WORD*)pOutszSendBuffer;
}

// ����Ʒ
int BuyPacket( const char* pszSayBufffer, char* pOutszSendBuffer)
{
	int nLen = 14;
	*(WORD*)pOutszSendBuffer = nLen;			// ��������Ĵ�С
	*(WORD*)(pOutszSendBuffer+2) = 0x55e0;		// �̶�����
	*(WORD*)(pOutszSendBuffer+4) = 0x8c00;		// ��Ϊ
	*(DWORD*)(pOutszSendBuffer+6) = 0x5b955f32;	// npc
	*(WORD*)(pOutszSendBuffer+10) = 0x0a57;		// id
	*(WORD*)(pOutszSendBuffer+12) = 1;			// count
	return (int)*(WORD*)pOutszSendBuffer;
}


// ����Ʒ
int SellPacket( const char* pszSayBufffer, char* pOutszSendBuffer)
{
	int nLen = 0x16;
	*(WORD*)pOutszSendBuffer = nLen;			// �������
	*(WORD*)(pOutszSendBuffer+2) = 0x55e0;		// �̶�����
	*(WORD*)(pOutszSendBuffer+4) = 0x0dba3;		// ��Ϊ
	*(DWORD*)(pOutszSendBuffer+6) = 0x5b955f32;	// npc
	*(DWORD*)(pOutszSendBuffer+10) = 1;			// ����Ʒ����
	*(DWORD*)(pOutszSendBuffer+14) = 6;			// ��Ʒ���ڱ����ڼ���
	*(DWORD*)(pOutszSendBuffer+18) = 1;			// count
	return (int)*(WORD*)pOutszSendBuffer;
}

// ����װ��
int FixPacket( const char* pszSayBufffer, char* pOutszSendBuffer)
{
	int nLen = 7;
	*(WORD*)pOutszSendBuffer = nLen;			// �������
	*(WORD*)(pOutszSendBuffer+2) = 0x55e0;		// �̶�����
	*(WORD*)(pOutszSendBuffer+4) = 0x177e;		// ��Ϊ
	*(BYTE*)(pOutszSendBuffer+6) = 1;
	return (int)*(WORD*)pOutszSendBuffer;
}

// 0E 00                 
// E0 55 
// A1 CA 
// 00 00 00 00 
// 02 00 00 00
// �ֽ���Ʒ
int ResolvePacket( const char* pszSayBufffer, char* pOutszSendBuffer)
{
	int nLen = 0x0e;
	*(WORD*)pOutszSendBuffer = nLen;			// �������
	*(WORD*)(pOutszSendBuffer+2) = 0x55e0;		// �̶�����
	*(WORD*)(pOutszSendBuffer+4) = 0x0caa1;		// ��Ϊ
	*(DWORD*)(pOutszSendBuffer+6) = 0;			// ��ͨ����
	*(DWORD*)(pOutszSendBuffer+10) = 0;			// ��Ʒ���ڱ����ڼ���
	return (int)*(WORD*)pOutszSendBuffer;
}

int UserSkill1( const char* pszSayBufffer, char* pOutszSendBuffer)
{
	int nLen = 0x14;
	*(WORD*)pOutszSendBuffer = nLen;
	*(WORD*)(pOutszSendBuffer+2) = 0x55e0;
	*(WORD*)(pOutszSendBuffer+4) = 0xfa66;				// ʹ�ü���
	*(DWORD*)(pOutszSendBuffer+6) = 0xfd70b9b4;			// ����id
	*(WORD*)(pOutszSendBuffer+10) = 0xc7ef;				// Param
	*(WORD*)(pOutszSendBuffer+12) = 0xce8e;				// associative_array
	*(DWORD*)(pOutszSendBuffer+14) = 0;
	*(WORD*)(pOutszSendBuffer+18) = 0;
	return (int)*(WORD*)pOutszSendBuffer;
}

void UserSkillAdd()
{
	__asm
	{
		MOV ECX,0x018CDAB4
		MOV EAX,0x1
		LOCK XADD DWORD PTR DS:[ECX],EAX
		INC EAX
	}
}

int UserSkill2( const char* pszSayBufffer, char* pOutszSendBuffer)
{
	DWORD dwTemp = 0;
	int nLen = 0x3F;
	*(WORD*)pOutszSendBuffer = nLen;
	*(WORD*)(pOutszSendBuffer+2) = 0x55e0;
	*(WORD*)(pOutszSendBuffer+4) = 0xd671;			// �����ж�
	 __asm
	 {
		 mov eax, 0x018CCB60
		 add eax, 0x1C
		 mov eax, dword ptr[eax]
		 mov dwTemp, eax
	 }
	*(DWORD*)(pOutszSendBuffer+6) = dwTemp;			// ���

	DWORD dwSerial = 0;
	UserSkillAdd();
	__asm
	{
		mov eax, 0x018CDAB4
		mov eax, dword ptr[eax]
		mov dwSerial, eax
	}
	*(DWORD*)(pOutszSendBuffer+10) = dwSerial;		// �ж����
	UserSkillAdd();

	*(DWORD*)(pOutszSendBuffer+14) = 0x0FD17221E;	// �ж�hash
	*(BYTE*)(pOutszSendBuffer+18) = 0;				// ExistParams

	FLOAT x;
	FLOAT y;
	FLOAT z;
	__asm
	{
		mov eax, 0x018CC8F0
		mov eax, dword ptr[eax]
		mov x, eax
	}
	*(FLOAT*)(pOutszSendBuffer+19) = x+5.0f;		// X
	__asm
	{
		mov eax, 0x018CC8F4
		mov eax, dword ptr[eax]
		mov z, eax
	}
	*(FLOAT*)(pOutszSendBuffer+23) = z+1.0f;		// Z
	__asm
	{
		mov eax, 0x018CC8F8
		mov eax, dword ptr[eax]
		mov y, eax
	}	
	*(FLOAT*)(pOutszSendBuffer+27) = y+5.0f;		// Y


	*(WORD*)(pOutszSendBuffer+31) = 0x0BB89;		// DirectionX
	*(WORD*)(pOutszSendBuffer+33) = 0x355D;			// DirectionY
	*(WORD*)(pOutszSendBuffer+35) = 0x0;			// MovingDirectionX
	*(WORD*)(pOutszSendBuffer+37) = 0x0;			// MovingDirectionY

	DWORD dwTime = 0;
	__asm
	{
		MOV EDX,0x7FFE0000
		MOV EAX,DWORD PTR DS:[EDX]
		MUL DWORD PTR DS:[EDX+0x4]
		SHRD EAX,EDX,0x18
		mov dwTime, eax
	}

	*(FLOAT*)(pOutszSendBuffer+39) = (FLOAT)dwTime;		// ClientAbsoluteTime

	__asm
	{
		mov eax, 0x00CC1920
		call eax
		mov dwTemp, eax
	}
	*(DWORD*)(pOutszSendBuffer+43) = dwTemp;		// RandomSeed

	dwSerial -= 2;
	*(DWORD*)(pOutszSendBuffer+47) = dwSerial;		// PrevActionSerial

	*(DWORD*)(pOutszSendBuffer+51) = dwTime-5000;	// PrevActionPlayTime
	*(BYTE*)(pOutszSendBuffer+55) = 0;				// SkipValidation

	*(DWORD*)(pOutszSendBuffer+56) = 0x0FD70B9B4;	// SkillId
	*(WORD*)(pOutszSendBuffer+60) = 0x0d0;			// SkillLevel
	*(BYTE*)(pOutszSendBuffer+63) = 0;				// SkipValidation


	return (int)*(WORD*)pOutszSendBuffer;
}


int UserSkill3( const char* pszSayBufffer, char* pOutszSendBuffer)
{
	DWORD dwTemp = 0;
	int nLen = 0x38;
	*(WORD*)pOutszSendBuffer = nLen;
	*(WORD*)(pOutszSendBuffer+2) = 0x55e0;
	*(WORD*)(pOutszSendBuffer+4) = 0x15fa;			// �����ж�
	__asm
	{
		mov eax, 0x018CCB60
		add eax, 0x1C
		mov eax, dword ptr[eax]
		mov dwTemp, eax
	}
	*(DWORD*)(pOutszSendBuffer+6) = dwTemp;			// ���

	DWORD dwSerial = 0;

	__asm
	{
		mov eax, 0x018CDAB4
		mov eax, dword ptr[eax]
		mov dwSerial, eax
	}
	*(DWORD*)(pOutszSendBuffer+10) = dwSerial;		// �ж����

	*(DWORD*)(pOutszSendBuffer+14) = 0x24611BA0;	// �ж�hash
	*(BYTE*)(pOutszSendBuffer+18) = 0;				// ExistParams

	FLOAT x;
	FLOAT y;
	FLOAT z;
	__asm
	{
		mov eax, 0x018CC8F0
		mov eax, dword ptr[eax]
		mov x, eax
	}
	*(FLOAT*)(pOutszSendBuffer+19) = x+5.0f;		// X
	__asm
	{
		mov eax, 0x018CC8F4
		mov eax, dword ptr[eax]
		mov z, eax
	}
	*(FLOAT*)(pOutszSendBuffer+23) = z+1.0f;		// Z
	__asm
	{
		mov eax, 0x018CC8F8
		mov eax, dword ptr[eax]
		mov y, eax
	}	
	*(FLOAT*)(pOutszSendBuffer+27) = y+5.0f;		// Y

	*(WORD*)(pOutszSendBuffer+31) = 0x0BB89;		// DirectionX
	*(WORD*)(pOutszSendBuffer+33) = 0x355D;			// DirectionY
	*(WORD*)(pOutszSendBuffer+35) = 0x0;			// MovingDirectionX
	*(WORD*)(pOutszSendBuffer+37) = 0x0;			// MovingDirectionY


	*(FLOAT*)(pOutszSendBuffer+39) = (FLOAT)GetTickCount();		// ClientAbsoluteTime

	__asm
	{
		mov eax, 0x00CC1920
		call eax
		mov dwTemp, eax
	}
	*(DWORD*)(pOutszSendBuffer+43) = dwTemp;		// RandomSeed

	dwSerial -= 2;
	*(DWORD*)(pOutszSendBuffer+47) = dwSerial;		// PrevActionSerial

	*(FLOAT*)(pOutszSendBuffer+51) = (FLOAT)GetTickCount()-50.f;	// PrevActionPlayTime
	*(BYTE*)(pOutszSendBuffer+55) = 1;				// SkipValidation


	return (int)*(WORD*)pOutszSendBuffer;
}

// typedef struct
// {
// 	DWORD dwArgc3;
// 	DWORD dwArgc4;
// }SEND_CALL_ARGC;
/*++
		[[1765a10]+0]
--*/
void JFZR_Send(char* szSayBuffer,PACKET pFun)
{
	DWORD	dwArgc1 = 0;
	// ��ȡ����һ��ֵ
	_ReadProcessMemory(JFZR_REVERSAL_SEND_PACKET_SOCKET_ADDR,&dwArgc1,sizeof(dwArgc1));
	_ReadProcessMemory(dwArgc1+JFZR_REVERSAL_SEND_PACKET_SOCKET_OFFSET___,&dwArgc1,sizeof(dwArgc1));

	// �齨����,��������Ϸ�ڲ��������뻺����
	GAME_BUIILD_OBJ theBuildObj;
	__asm
	{
		push 0
		lea ecx, theBuildObj
		mov eax, JFZR_REVERSAL_SEND_ALLOC_OBJ_CALL
		call eax
	}
	//MessageBox(NULL,"","",MB_OK);

	theBuildObj.dwBufferEndAddr = pFun(szSayBuffer,(char*)theBuildObj.dwBufferBeginAddr1) + (DWORD)theBuildObj.dwBufferBeginAddr1;

	SEND_CALL_ARGC theArgc;

	// ��ַδ��ȡ�������������
	DWORD	dwEcx = g_dwSendObjAddr+JFZR_REVERSAL_SEND_PACKET_OFFSET;

	_ReadProcessMemory(dwEcx+JFZR_REVERSAL_SEND_PACKET_JIAMI_OBJ_OFFSET,&theArgc.dwArgc3,sizeof(theArgc.dwArgc3));
	_ReadProcessMemory(dwEcx+JFZR_REVERSAL_SEND_PACKET_TASK_OBJ_OFFSET,&theArgc.dwArgc4,sizeof(theArgc.dwArgc4));

	__asm
	{
// 		push 0x180F7424
// 		push 0x1BEA1264
		sub esp, 8
		mov ecx, esp
		lea edx, theArgc		// ���ܶ���,�����������
		push edx
		mov dword ptr [ecx], 0
		mov dword ptr [ecx+4], 0
		mov eax, JFZR_REVERSAL_SEND_PUSH_ARGC3_ARGC4_CALL
		call eax
		
		lea eax, theBuildObj	// ��������
		push eax				
		push dwArgc1			// socket ����
		mov eax, JFZR_REVERSAL_SEND_ADDR_CALL
		call eax
		add esp, 0x10
	}

	// �ͷ��齨����ʱ������ڴ�
	__asm
	{
		lea ecx, theBuildObj
		mov eax, JFZR_REVERSAL_SEND_FREE_OBJ_CALL
		call eax
	}
}


typedef struct  
{
	DWORD	st_dwAddr0;
	DWORD	st_dwAddr4;
	DWORD	st_dwAddr8;
	DWORD	st_dwAddrC;
	DWORD	st_dwAddr10;
	DWORD	st_dwAddr14;
	DWORD	st_dwAddr18;
	DWORD	st_dwAddr1C;
	DWORD	st_dwAddr20;
	DWORD	st_dwAddr24;
	DWORD	st_dwAddr28;
	DWORD	st_dwAddr2C;
	DWORD	st_dwAddr30;
	DWORD	st_dwAddr34;
	DWORD	st_dwAddr38;
	DWORD	st_dwAddr3C;
	DWORD	st_dwAddr40;
	DWORD	st_dwAddr44;
	DWORD	st_dwAddr48;
}GAME_DIRECTION,*PGAME_DIRECTION;

typedef struct
{
	float x;
	float y;
	float z;
}D3D_DIRECTION,*PD3D_DIRECTION;

typedef struct
{
	DWORD	st_dwAddr0;
	DWORD	st_dwAddr4;
	DWORD	st_dwAddr8;
	DWORD	st_dwAddrC;
	DWORD	st_dwAddr10;
}GAME_ARGC_DIRECTION,*PGAME_ARGC_DIRECTION;

DWORD AllmMemory_Alloc(int nsize)
{
	__asm
	{
		push nsize
		mov eax, JFZR_REVERSAL_ALLMMEMORY_ALLOC_ADDR
		call eax
		add esp, 4
	}
}

typedef struct
{
	DWORD	st_dwLen;
	DWORD	st_dwAddr1;
	DWORD	st_dwAddr2;
	DWORD	st_dwAddr3;
	DWORD	st_dwAddr4;
}GAME_TEST,*PGAME_TEST;

// ��Ϸ�ڲ����ַ�����ֵ������������ڴ�
void GameMemcpy(LPVOID lpAddr, WCHAR* pszStr)
{
	int nLen = wcslen(pszStr);
	__asm
	{
		push nLen
		push pszStr
		mov ecx, lpAddr
		mov eax, JFZR_REVERSAL_GAME_MEMCPY_CALL
		call eax
	}
}

void JFZR_CMD(WCHAR* pszCmd)
{
	GAME_TEST theGameTestArgc1 = {0};
	theGameTestArgc1.st_dwLen = 9;
	theGameTestArgc1.st_dwAddr1 = AllmMemory_Alloc(0x80);
	GameMemcpy((LPVOID)theGameTestArgc1.st_dwAddr1,pszCmd);

	// ��·
	*(DWORD*)(theGameTestArgc1.st_dwAddr1+0x3c) = 1;
	*(DWORD*)(theGameTestArgc1.st_dwAddr1+0x40) = 0x00700055;
	*(DWORD*)(theGameTestArgc1.st_dwAddr1+0x50) = 2;
	*(DWORD*)(theGameTestArgc1.st_dwAddr1+0x54) = 7;
	*(DWORD*)(theGameTestArgc1.st_dwAddr1+0x7c) = 1;

	// ����1
// 	*(DWORD*)(theGameTestArgc1.st_dwAddr1+0x3c) = 1;
// 	*(DWORD*)(theGameTestArgc1.st_dwAddr1+0x40) = 0x31;
// 	*(DWORD*)(theGameTestArgc1.st_dwAddr1+0x50) = 1;
// 	*(DWORD*)(theGameTestArgc1.st_dwAddr1+0x54) = 7;
// 	*(DWORD*)(theGameTestArgc1.st_dwAddr1+0x7c) = 1;

	GAME_TEST theGameTestArgc2 = {0};

	theGameTestArgc2.st_dwLen = theGameTestArgc1.st_dwAddr1;

	theGameTestArgc2.st_dwAddr1 = theGameTestArgc1.st_dwAddr1+0x84;
	theGameTestArgc2.st_dwAddr2 = theGameTestArgc1.st_dwAddr1+0x84;

	theGameTestArgc2.st_dwAddr3 = AllmMemory_Alloc(0x20);

	WCHAR szCmd[] = L"ActionCommand";
	memcpy((char*)theGameTestArgc2.st_dwAddr3,szCmd,sizeof(szCmd));

	__asm
	{
		lea eax, theGameTestArgc2
		push eax
		lea eax, theGameTestArgc1
		push eax
		mov ecx, 0x1B1859A4
		mov eax, JFZR_REVERSAL_ZOULU_CALL
		call eax
	}

}

void JFZR_CMD2(WCHAR* pszCmd)
{
	try
	{

		GAME_TEST theGameTestArgc1;
		theGameTestArgc1.st_dwAddr4 = 0;
		GAME_TEST theGameTestArgc2 = {0};

		theGameTestArgc2.st_dwLen = AllmMemory_Alloc(0x40);
		GameMemcpy((LPVOID)theGameTestArgc2.st_dwLen,pszCmd);
		*(DWORD*)(theGameTestArgc2.st_dwLen+0x3c) = 1;

		theGameTestArgc2.st_dwAddr1 = theGameTestArgc2.st_dwLen+0x40;
		theGameTestArgc2.st_dwAddr2 = theGameTestArgc2.st_dwLen+0x40;

		theGameTestArgc2.st_dwAddr3 = AllmMemory_Alloc(0x20);

		WCHAR szCmd[] = L"ActionCommand";
		memcpy((char*)theGameTestArgc2.st_dwAddr3,szCmd,sizeof(szCmd));

		__asm
		{
			lea eax, theGameTestArgc2
			push eax
			lea eax, theGameTestArgc1
			push eax
			mov ecx, 0x116AAA54
			mov eax, 0x00AB4AB0
			call eax

			// 		pop eax
			// 		pop eax
		}
	}
	catch (...)
	{
		OutputDebugString("[JFZR] JFZR_CMD2 error!!");
	}
}


// 
// DWORD	g_dwSendPacketCallAddr = 0;
// char szSendPacketData[2048] = {0};
// char szPrint[2096] = {0};
// 
// // HOOK ����������İ���Ϣ
// void PrintSendPacket(const BYTE* pszSendPacket)
// {
// 	DWORD dwlen = *(WORD*)pszSendPacket;
// 
// 	for (DWORD i = 0 ; i < dwlen ; i++)
// 	{
// 		if( pszSendPacket[i] > 0x0f )
// 			wsprintfA(szSendPacketData+i*3,"%2X ",pszSendPacket[i]);
// 		else
// 			wsprintfA(szSendPacketData+i*3,"0%1X ",pszSendPacket[i]);
// 	}
// 
// 	szSendPacketData[dwlen*3] = 0;
// 	
// 	wsprintfA(szPrint,"[JFZR] len = %p %s",dwlen,szSendPacketData);
// 	OutputDebugStringA(szPrint);
// }
// 
// DWORD dwLen = 0;
// 
// _declspec(naked) void HookSendPacket()
// {
// 	__asm
// 	{
// 		pushfd
// 		pushad
// 	}
// 
// 	__asm
// 	{
// 		mov eax, dword ptr[esp+0x2C]
// 		mov eax, dword ptr[eax+0x8]
// 		push eax
// 		mov eax, dword ptr[eax]
// 		mov dwLen, eax
// 		lea eax, PrintSendPacket
// 		call eax
// 		add esp, 4
// 	}
// 
// 	dwLen = (WORD)dwLen;
// 	if( dwLen == 0x12 )
// 	{
// 		__asm
// 		{
// 			popad
// 			popfd
// 			retn 
// 		}
// 	}
// 
// 	__asm
// 	{
// 		popad
// 		popfd
// 
// 		PUSH EBP
// 		MOV EBP,ESP
// 		PUSH -0x1
// 		mov eax, g_dwSendPacketCallAddr
// 		add eax, 5
// 		jmp eax
// 	}
// }

CInjectedWnd m_theDlgUnModel;


#define MFC_DLL_MSG_API

MFC_DLL_MSG_API int __stdcall YAANIPCLIB_Init(IN int nType)
{
	try
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
	}
	catch (...)
	{
		assert(false);
	}

	return 0;
}

MFC_DLL_MSG_API int __stdcall YAANIPCLIB_UnInit(void)
{
	try
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
	}
	catch (...)
	{
		assert(false);
	}
	return 0;
}

MFC_DLL_MSG_API long __stdcall YAANIPCLIB_CreateInstance(IN const int nFlag)
{
	try
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		CInjectedWnd   *  pDlg = new CInjectedWnd;
		if (pDlg == NULL)
		{
			return -1;
		}
		if (FALSE == pDlg->Create(IDD_DIALOG1))
		{
			return -2;
		}

		pDlg->ShowWindow(SW_SHOW);

		return (long)pDlg;
	}
	catch (...)
	{
		assert(false);
	}


	return 0;
}

MFC_DLL_MSG_API int __stdcall YAANIPCLIB_DestroyInstance(IN long lInstace)
{
	try
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		CInjectedWnd   *  pDlg = (CInjectedWnd*)lInstace;
		if (pDlg)
		{
			pDlg->DestroyWindow();
			delete pDlg;
			pDlg = NULL;
		}
	}
	catch (...)
	{
		assert(false);
	}

	return 0;
}

HANDLE	g_hDlgThread;
long	g_lInstance = 0;
bool	g_bWndRunFlag = false;

uintptr_t __stdcall ThreadFunc( void* param )
{
	try
	{
		g_bWndRunFlag = true;
		g_lInstance = YAANIPCLIB_CreateInstance(0);//��������
	}
	catch (...)
	{
		assert(false);
	}

	while (true)
	{
		try
		{
			MSG msg;	
			while(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				// ת��������Ϣ
				::TranslateMessage(&msg);
				// ����Ϣ���͵���Ӧ�Ĵ��ں���
				::DispatchMessage(&msg);
			}

		}
		catch (...)
		{
			assert(false);
		}

		if( g_bWndRunFlag == false )
		{
			break;
		}
	}

	return 0;
}


// CjfzrcalltestApp ��ʼ��
BOOL CjfzrcalltestApp::InitInstance()
{
	CWinApp::InitInstance();

// 	g_dwSendPacketCallAddr = JFZR_REVERSAL_SEND_ADDR_CALL;
// 	Hook(g_dwSendPacketCallAddr,HookSendPacket);

// 	MessageBox(NULL,"","",MB_OK);
 	InitBase();
// 	//JFZR_Send("1234567",SayPacket);
//  	JFZR_Send("1234567",UserSkill1);
//  	JFZR_Send("1234567",UserSkill2);
// 
//  	JFZR_Send("1234567",UserSkill3);

	//direction2();
	//JFZR_CMD(L"PressMove");
	//JFZR_CMD(L"ReleaseMove");

// 	JFZR_CMD(L"Command");
// 	JFZR_CMD(L"CommandRelease");
//	JFZR_CMD2(L"Jump");
	

// 	LPWSANETWORKEVENTS 
// 	FD_READ_BIT
// 	WSAENETDOWN
// 	WSAEINPROGRESS

	try
	{
		int nRet = 0;
		nRet = YAANIPCLIB_Init(0);
		g_hDlgThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, NULL, 0, 0);
	}
	catch (...)
	{
		assert(false);
	}
	return TRUE;
}

int CjfzrcalltestApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	try
	{
		g_bWndRunFlag = false;
		if( g_hDlgThread )
		{
			::CloseHandle(g_hDlgThread);
			//TerminateThread(g_hDlgThread,0);
			g_hDlgThread = NULL;
		}

		YAANIPCLIB_UnInit();
	}
	catch (...)
	{
		assert(false);
	}
	return CWinApp::ExitInstance();
}
