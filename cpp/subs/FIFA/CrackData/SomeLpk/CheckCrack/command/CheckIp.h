#pragma once


// ���÷�����	23.234.25.75��23.234.25.76��23.252.167.25
#define IP_STR			"23.234.25.16"
#define IP_STR1			"23.234.25.9"
#define IP_STR2			"23.234.25.11"
#define IP_STR3			"23.234.25.124"

// 1127���ﲻɾ��������ip
#define IP_STR4			"162.251.95.31"
#define IP_STR5			"162.251.95.31"
#define IP_STR6			"162.251.95.31"


#define XOR_DWORD(a) ((DWORD)a ^ 0x0D8D8AB73)
#define XOR_WORD(a) (WORD)((DWORD)a ^ 0x0D8D8AB73)
#define IP		XOR_DWORD(inet_addr(VMProtectDecryptString(IP_STR)))
#define IP1		XOR_DWORD(inet_addr(VMProtectDecryptString(IP_STR1)))
#define IP2		XOR_DWORD(inet_addr(VMProtectDecryptString(IP_STR2)))
#define IP3		XOR_DWORD(inet_addr(VMProtectDecryptString(IP_STR3)))
#define IP4		XOR_DWORD(inet_addr(VMProtectDecryptString(IP_STR4)))
#define IP5		XOR_DWORD(inet_addr(VMProtectDecryptString(IP_STR5)))
#define IP6		XOR_DWORD(inet_addr(VMProtectDecryptString(IP_STR6)))

// èͷӥ�ķ�����ip
#define MAOTOUYAN_SERVER_IP		XOR_DWORD(inet_addr(VMProtectDecryptString("202.103.226.244")))
#define LOCAL_IP				XOR_DWORD(inet_addr(VMProtectDecryptString("127.0.0.1")))
#define ZEOR_IP					XOR_DWORD(inet_addr(VMProtectDecryptString("0.0.0.0")))


typedef DWORD (WINAPI *PFNGetExtendedTcpTable)(
	__out         PVOID pTcpTable,				//���ز�ѯ�ṹ��ָ��
	_Inout_       PDWORD pdwSize,				//��һ�ε��øò����᷵������Ҫ�Ļ�������С
	__in          BOOL bOrder,					//�Ƿ�����
	__in          ULONG ulAf,					//�� AF_INET����AF_INET6
	__in          TCP_TABLE_CLASS TableClass,	// ��ʾ�ṹ������࣬�˴���Ϊ TCP_TABLE_OWNER_PID_ALL
	__in          ULONG Reserved				//�������ã���Ϊ 0
	);



class CheckIp
{
public:
	CheckIp(void);
	~CheckIp(void);
public:
	bool CheckTcp();
public:
	PFNGetExtendedTcpTable m_pfnGetTcpTable;
	bool Findoledlg(void);
};
