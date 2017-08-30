// jfzrcalltest.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "jfzrcalltest.h"
#include "jfzrbase.h"
#include "InjectedWnd.h"
#include <process.h>

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


DWORD	g_dwSendObjAddr = 0;
typedef DWORD (*PGetAllmMemorySendObjAddr)();

void InitBase()
{
	g_dwSendObjAddr = (DWORD)((PGetAllmMemorySendObjAddr)GetProcAddress(LoadLibraryA("d3d9.dll"),"GetAllmMemorySendObjAddr")());
}

BOOL _ReadProcessMemory(DWORD dwReadAddr,void* pReadData,DWORD dwReadlen)
{
	return ::ReadProcessMemory((HANDLE)-1,(LPCVOID)dwReadAddr,pReadData,dwReadlen,0);
}

BOOL _WriteProcessMemory(DWORD dwWriteAddr,void* pWriteData,DWORD dwWritelen)
{
	return ::WriteProcessMemory((HANDLE)-1,(LPVOID)dwWriteAddr,pWriteData,dwWritelen,0);
}


CInjectedWnd m_theDlgUnModel;


#define MFC_DLL_MSG_API

MFC_DLL_MSG_API int __stdcall YAANIPCLIB_Init(IN int nType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return 0;
}

MFC_DLL_MSG_API int __stdcall YAANIPCLIB_UnInit(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return 0;
}

MFC_DLL_MSG_API long __stdcall YAANIPCLIB_CreateInstance(IN const int nFlag)
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

MFC_DLL_MSG_API int __stdcall YAANIPCLIB_DestroyInstance(IN long lInstace)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CInjectedWnd   *  pDlg = (CInjectedWnd*)lInstace;
	if (pDlg)
	{
		pDlg->DestroyWindow();
		delete pDlg;
		pDlg = NULL;
	}
	return 0;
}

HANDLE	g_hDlgThread;
long	g_lInstance = 0;
bool	g_bWndRunFlag = false;

uintptr_t __stdcall ThreadFunc( void* param )
{
	g_bWndRunFlag = true;
	g_lInstance = YAANIPCLIB_CreateInstance(0);//��������

	while (true)
	{
		MSG msg;	
		while(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// ת��������Ϣ
			::TranslateMessage(&msg);
			// ����Ϣ���͵���Ӧ�Ĵ��ں���
			::DispatchMessage(&msg);
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
// 	InitBase();
// 	//JFZR_Send("1234567",SayPacket);
// 	JFZR_Send("1234567",UserSkill1);
// 	JFZR_Send("1234567",UserSkill2);
// 	Sleep(300);
// 	JFZR_Send("1234567",UserSkill3);

	//direction2();
	//JFZR_CMD(L"PressMove");
	//JFZR_CMD(L"ReleaseMove");

// 	JFZR_CMD(L"Command");
// 	JFZR_CMD(L"CommandRelease");
//	JFZR_CMD2(L"Jump");
	



	int nRet = 0;
	nRet = YAANIPCLIB_Init(0);
	g_hDlgThread = (HANDLE)_beginthreadex(NULL, 0, ThreadFunc, NULL, 0, 0);
	
	return TRUE;
}

int CjfzrcalltestApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	g_bWndRunFlag = false;
	if( g_hDlgThread )
	{
		::CloseHandle(g_hDlgThread);
		//TerminateThread(g_hDlgThread,0);
		g_hDlgThread = NULL;
	}
	
	YAANIPCLIB_UnInit();
	return CWinApp::ExitInstance();
}
