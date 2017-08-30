#include "StdAfx.h"
#include "EnumPidWnd.h"
#include <tlhelp32.h>

using namespace std;

BOOL    CALLBACK    EnumProc(HWND hWnd,LPARAM lPraram){
	if( NULL==hWnd ){ return FALSE;}

	EnumPidWnd* pEnumPidWnd = (EnumPidWnd*)lPraram;

	// �Ѿ��ҵ����ڣ�����Ҫ�ڱȽ���
	if( pEnumPidWnd->m_bIsHaveWnd == true )
	{
		return true;
	}

	if( ::IsWindow(hWnd) )
	{
		DWORD    pid=0;
		::GetWindowThreadProcessId(hWnd,&pid);

		if( pid == NULL )
		{
			printf("δ��ȡ������ID\r\n");
			return true;
		}

		if( pid==pEnumPidWnd->m_dwPid )
		{
			// �жϴ����Ƿ���ʾ
			BOOL  isS= ::IsWindowVisible(hWnd);

			if( isS == pEnumPidWnd->m_bIsWindowVisible )
			{
				char szWndName[256] = {0};
				::GetWindowTextA(hWnd,szWndName,256);

				// �Աȴ�������
				if( strlen(pEnumPidWnd->m_pWnd->str_szWndName) != 0 )
				{
					printf("�Ƚϴ������� %s ? %s\r\n",pEnumPidWnd->m_pWnd->str_szWndName,szWndName);
					if( strcmp(pEnumPidWnd->m_pWnd->str_szWndName,szWndName) != 0 )
					{
						printf("�Ƚϴ������Ʋ�ƥ��\r\n");
						return true;
					}
				}

				// ���ڷ��
				if( pEnumPidWnd->m_pWnd->str_GWL_STYLE != 0 )
				{
					printf("�Ƚϴ��ڷ��ƥ�� %p ? %p\r\n",pEnumPidWnd->m_pWnd->str_GWL_STYLE,::GetWindowLong(hWnd,GWL_STYLE));
					if( pEnumPidWnd->m_pWnd->str_GWL_STYLE != ::GetWindowLong(hWnd,GWL_STYLE) )
					{
						printf("�Ƚϴ��ڷ��ƥ��\r\n");
						return true;
					}
				}
				
				// ��չ���ڷ��
				if( pEnumPidWnd->m_pWnd->str_GWL_EXSTYLE != 0 )
				{
					printf("�Ƚ���չ���ڷ�� %p ? %p\r\n",pEnumPidWnd->m_pWnd->str_GWL_EXSTYLE,::GetWindowLong(hWnd,GWL_EXSTYLE));
					if( pEnumPidWnd->m_pWnd->str_GWL_EXSTYLE != ::GetWindowLong(hWnd,GWL_EXSTYLE) )
					{
						printf("�Ƚ���չ���ڷ��ƥ��\r\n");
						return true;
					}
				}

				// ָ�����ڵı߿���εĳߴ�
				if( pEnumPidWnd->m_pWnd->str_x != 0 && pEnumPidWnd->m_pWnd->str_y != 0 )
				{
					RECT rRect;
					if( ::GetWindowRect(hWnd,&rRect) )
					{
						if( pEnumPidWnd->m_pWnd->str_x != (rRect.right-rRect.left) || pEnumPidWnd->m_pWnd->str_y != (rRect.bottom-rRect.top) )
						{
							printf("�Ƚϴ��ڵı߿���εĳߴ粻ƥ��\r\n");
							return true;
						}
					}
				}

				// �����������������
				if( strlen(pEnumPidWnd->m_pWnd->str_szClassName) != 0 )
				{
					char szClassName[256] = {0};
					if( ::GetClassName(hWnd,szClassName,sizeof(szClassName)) )
					{
						if( strcmp(pEnumPidWnd->m_pWnd->str_szClassName,szClassName) != 0 )
						{
							printf("�Ƚϴ������������������ƥ��\r\n");
							return true;
						}
					}
				}

				//������ķ��
				if( pEnumPidWnd->m_pWnd->str_GCL_STYLE != 0 )
				{
					printf("�Ƚϴ�����ķ�� %p ? %p\r\n",pEnumPidWnd->m_pWnd->str_GCL_STYLE , ::GetClassLong(hWnd,GCL_STYLE));
					if( pEnumPidWnd->m_pWnd->str_GCL_STYLE != ::GetClassLong(hWnd,GCL_STYLE) )
					{
						printf("�Ƚϴ�����ķ��ƥ��\r\n");
						return true;
					}
				}
				

				//�����ھ��
				if( pEnumPidWnd->m_pWnd->str_hParWnd != NULL )
				{
					if( pEnumPidWnd->m_pWnd->str_hParWnd != ::GetParent(hWnd) )
					{
						printf("�Ƚϸ����ھ����ƥ��\r\n");
						return true;
					}
				}
				
				pEnumPidWnd->m_bIsHaveWnd = true;
				pEnumPidWnd->m_hWnd = hWnd;
				printf("���Ҵ��ڳɹ�\r\n");
			}

			return true;
		}
	}

	return true;
}


BOOL    CALLBACK    EnumProcCount(HWND hWnd,LPARAM lPraram){
	if( NULL==hWnd ){ return FALSE;}

	EnumPidWnd* pEnumPidWnd = (EnumPidWnd*)lPraram;

	if( ::IsWindow(hWnd) )
	{
		DWORD    pid=0;
		::GetWindowThreadProcessId(hWnd,&pid);
		if( pid==pEnumPidWnd->m_dwPid )
		{
			// �жϴ����Ƿ���ʾ
			BOOL  isS= ::IsWindowVisible(hWnd);

			if( isS == pEnumPidWnd->m_bIsWindowVisible )
			{
				pEnumPidWnd->m_dwWndCount++;
			}

			return TRUE;
		}
	}

	return TRUE;
}

EnumPidWnd::EnumPidWnd(void)
{
	m_dwPid = 0;
	m_bIsHaveWnd = false;
}

EnumPidWnd::~EnumPidWnd(void)
{
}

HWND EnumPidWnd::FindWindow(PFINDWINDOW pfindwnd, bool bIsWindowVisible)
{
	if( strlen(pfindwnd->str_szExeFile) == 0 )
	{
		return false;
	}

	m_bIsHaveWnd = false;
	m_bIsWindowVisible = bIsWindowVisible;
	m_pWnd = pfindwnd;

	if( strcmp(pfindwnd->str_szExeFile,"jfzr.exe") == 0 || strcmp(pfindwnd->str_szExeFile,"JFZR.exe") == 0 )
	{
		m_dwPid=GetCurrentProcessId();
	}
	else
	{
		m_dwPid=GetPidByName(pfindwnd->str_szExeFile);
	}
	
	if(0!=m_dwPid)
	{
		::EnumWindows(EnumProc,(LPARAM)this);
	}
	else
	{
		//printf("GetPidByName ���� NULL\r\n");
	}

	if( m_bIsHaveWnd )
	{
		return m_hWnd;
	}

	return NULL;
}

unsigned long EnumPidWnd::GetPidByName(LPCSTR pname)
{
	unsigned long    pid=0;
	
	char name[256] = {0};
	strcpy_s(name,256,pname);

	::CharLowerA(name);

	PROCESSENTRY32    lp;
	HANDLE            lh=NULL;
	memset(&lp,0,sizeof(lp));
	lp.dwSize    =    sizeof(lp);

	lh            =    ::CreateToolhelp32Snapshot(    TH32CS_SNAPPROCESS, 0 );
	BOOL ok        =   ::Process32First( lh,&lp);

	while(ok)
	{
		char* dname    =    new char[(int)((strlen(lp.szExeFile)+1)*sizeof(wchar_t))];
		strcpy_s(dname,(int)((strlen(lp.szExeFile)+1)*sizeof(wchar_t)),lp.szExeFile);
		dname = ::CharLowerA(dname);
		if ( strcmp(name,dname) == 0 )
		{
			pid    =    lp.th32ProcessID;        
			delete [] dname;dname=NULL;
			break;
		}
		delete [] dname;dname=NULL;
		ok = ::Process32Next(lh,&lp);
	}
	return pid;
}

DWORD EnumPidWnd::GetShowWndCount(char* pszExeFile)
{
	m_dwWndCount = 0;
	m_dwPid = GetPidByName(pszExeFile);

	if(0!=m_dwPid)
	{
		::EnumWindows(EnumProcCount,(LPARAM)this);
	}

	return m_dwWndCount;
}
