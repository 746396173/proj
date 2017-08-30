// SyncTimeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SyncTime.h"
#include "SyncTimeDlg.h"

#include <time.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSyncTimeDlg dialog

CSyncTimeDlg::CSyncTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSyncTimeDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSyncTimeDlg)
	m_info = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSyncTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSyncTimeDlg)
	DDX_Control(pDX, IDC_COMBO1, m_cmbServer);
	DDX_Text(pDX, IDC_EDIT1, m_info);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSyncTimeDlg, CDialog)
	//{{AFX_MSG_MAP(CSyncTimeDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SYNC, OnSync)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSyncTimeDlg message handlers

BOOL CSyncTimeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//���ʱ�����������
	m_cmbServer.AddString("time-a.timefreq.bldrdoc.gov");
	m_cmbServer.AddString("utcnist.colorado.edu");
	m_cmbServer.AddString("time-nw.nist.gov");
	m_cmbServer.AddString("time.ien.it");

	m_cmbServer.SetCurSel(0);
	/*
	//��Щ������

	"time-a.timefreq.bldrdoc.gov"
    "time-b.timefreq.bldrdoc.gov"
    "time-c.timefreq.bldrdoc.gov"
    "utcnist.colorado.edu"
    "time-nw.nist.gov"
    "nist1.nyc.certifiedtime.com"
    "nist1.dc.certifiedtime.com"
    "nist1.sjc.certifiedtime.com"
    "nist1.datum.com"
    "ntp2.cmc.ec.gc.ca"
    "ntps1-0.uni-erlangen.de"
    "ntps1-1.uni-erlangen.de"
    "ntps1-2.uni-erlangen.de"
    "ntps1-0.cs.tu-berlin.de"
    "time.ien.it"
    "ptbtime1.ptb.de"
    "ptbtime2.ptb.de"

	*/
	dwDely = 0;

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSyncTimeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSyncTimeDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSyncTimeDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSyncTimeDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CSyncTimeDlg::OnSync() 
{
	m_info = "";
	UpdateData(FALSE);

	//����������ʱ
	dwDely = 0;
	KillTimer(0);

	SetTimer(0, 1000, NULL);	//������ʱ��
	
	// �õ��û�ѡ��ķ�����
	CString strServer("");
	m_cmbServer.GetWindowText(strServer);

	//��ȡinternetʱ��
	CTime tm(1990, 1, 1, 0, 0, 0);
	if(GetInternetTime(&tm, strServer))
	{
		//SyncSystemClock(tm);
	}

//	SyncSystemClock((CTime)dwTime);
	
}

BOOL CSyncTimeDlg::GetInternetTime(CTime* pTime, CString strServer)
{
	CSocket sockClient;
	sockClient.Create();			//����socket

	//for debug
	m_info += "Connect server: " + strServer + "...\r\n";
	UpdateData(FALSE);
	//for debug

	sockClient.Connect((LPCTSTR)strServer, 37); // strServer��ʱ���������ַ�� 37���˿ں�

	DWORD dwTime = 0;				//������ŷ����������ı�׼ʱ������
	unsigned char nTime[8];			//��ʱ��������
	memset(nTime, 0, sizeof(nTime));

	sockClient.Receive(nTime, sizeof(nTime));	//���շ�������������4���ֽڵ�����
	sockClient.Close();				//�ر�socket
	
	//for debug
	m_info += "Connect shut down.\r\n";
	UpdateData(FALSE);
	//for debug

	dwTime += nTime[0] << 24;		//��������	
	dwTime += nTime[1] << 16;
	dwTime += nTime[2] << 8;
	dwTime += nTime[3];		

	if(0 == dwTime)	return FALSE;

	//for debug
	CString strSec("");
	strSec.Format("Receive value : %u\r\n", dwTime);
	m_info += strSec;
	UpdateData(FALSE);
	//for debug

	//�������������������Դ�1900������������
	//ȡ�� 1900~1970 ��ʱ���(����������) ������dwSpan����
	COleDateTime t00( 1900, 1, 1, 0, 0, 0 ); // 1900.1.1 00:00:00 
	COleDateTime t70( 1970, 1, 1, 0, 0, 0 ); // 1970.1.1 00:00:00 

	COleDateTimeSpan ts70to00 = t70 - t00; 
	DWORD dwSpan = 0x83AA7E80;		//(DWORD)ts70to00.GetTotalSeconds();   XP�������win7������ȷ������д��
	ASSERT( dwSpan == 2208988800L ); 

	CString	s;
	s.Format("%p\r\n",dwSpan);

	m_info += s;
	
	//��ʱ���Ϊ����1970��ģ�������CTime����
	dwTime -= dwSpan;		
	//���������ӳ�����
	dwTime += dwDely;
	//���쵱ǰʱ���CTime����
	CTime timeNow(dwTime); //  = (CTime)dwTime;

	//for debug
	m_info += timeNow.Format("%Y.%m.%d  %H:%M:%S \r\n");
	UpdateData(FALSE);
	//for debug

	*pTime = timeNow;		

	return TRUE;
}

BOOL CSyncTimeDlg::SyncSystemClock(CTime tmServer)
{
	//�������XP�£������������̵�Ȩ��
	OSVERSIONINFO osv;
	osv.dwOSVersionInfoSize=sizeof OSVERSIONINFO;
	GetVersionEx(&osv);
	if(osv.dwPlatformId==VER_PLATFORM_WIN32_NT)
	{
	   HANDLE hToken; 
	   TOKEN_PRIVILEGES tkp; 

	   // Get a token for this process. 

	   if (!OpenProcessToken(GetCurrentProcess(), 
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) 
		  return( FALSE ); 

	   // Get the LUID for the shutdown privilege. 

	   LookupPrivilegeValue(NULL, SE_SYSTEMTIME_NAME, 
			&tkp.Privileges[0].Luid); 

	   tkp.PrivilegeCount = 1;  // one privilege to set    
	   tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 

	   // Get the shutdown privilege for this process. 

	   AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, 
			(PTOKEN_PRIVILEGES)NULL, 0); 

	   if (GetLastError() != ERROR_SUCCESS) 
		  return FALSE; 
	}

	//����ϵͳʱ��
	SYSTEMTIME systm;
	systm.wYear = tmServer.GetYear();
	systm.wMonth = tmServer.GetMonth();
	systm.wDay = tmServer.GetDay();
	systm.wHour = tmServer.GetHour();
	systm.wMinute = tmServer.GetMinute();
	systm.wSecond = tmServer.GetSecond();
	systm.wMilliseconds = 0;


	if(0 != ::SetLocalTime(&systm))
	{
		m_info += "Set Time OK.\r\n";
		UpdateData(FALSE);
		return TRUE;
	}
	else
	{
		m_info += "Set Time Failure.\r\n";
		UpdateData(FALSE);
		return FALSE;
	}



}

void CSyncTimeDlg::OnTimer(UINT nIDEvent) 
{
	//�����ӳټ�����һ
	dwDely++;

	CDialog::OnTimer(nIDEvent);
}
