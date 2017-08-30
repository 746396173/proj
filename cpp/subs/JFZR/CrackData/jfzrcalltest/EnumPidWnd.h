#pragma once

typedef struct  
{
	HWND	str_hParWnd;						// �����ھ��
	char	str_szExeFile[MAX_ZONE_PATH];		// ��������,���޴�Сд,������д
	char	str_szWndName[MAX_ZONE_PATH];		// ��������
	char	str_szClassName[MAX_ZONE_PATH];		// ��������
	DWORD	str_GWL_STYLE;						// ���ڷ��
	DWORD	str_GWL_EXSTYLE;					// ��չ���ڷ��
	DWORD	str_GCL_STYLE;						// ������ķ��
	DWORD	str_x;								// x
	DWORD	str_y;								// y
}FINDWINDOW,*PFINDWINDOW;

class EnumPidWnd
{
public:
	HWND	m_hWnd;
	DWORD	m_dwPid;
	bool	m_bIsHaveWnd;
	BOOL	m_bIsWindowVisible;
	PFINDWINDOW	m_pWnd;

	DWORD	m_dwWndCount;
public:
	EnumPidWnd(void);
	~EnumPidWnd(void);
	HWND FindWindow(PFINDWINDOW pfindwnd, bool bIsWindowVisible = true);
	unsigned long GetPidByName(LPCSTR pname);
	DWORD GetShowWndCount(char* pszExeFile);
};
