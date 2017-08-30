#ifndef __SCANOPCODE_H__
#define __SCANOPCODE_H__

#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

#include <windows.h>

union Mem
{
	DWORD date32;
	WORD date16[2];
	BYTE data8[4];
};

/************************************************************************/
/* ����˵��������������
/* process: Ҫ���ҵĽ���
/* markCode: �������ַ���,�����пո�
/* distinct���������׵�ַ��Ŀ���ַ�ľ��� ����������������
/* offset: ����Ŀ���ַ
/* size: ���÷�������Ϊ����BYTE 1 2 3 4
/* ordinal: ��������ֵĴ���
/* beginAddr: ��ʼ������ַ
/* endAddr: ������ַ
/* ret:����Ŀ���ַ������
/************************************************************************/
DWORD ScanOpcode(HANDLE process, const char *markCode, 
				  int distinct,
				  LPDWORD offset = NULL,
				  DWORD size = 4,
				  DWORD ordinal = 1,
				  DWORD beginAddr = 0x00400000, DWORD endAddr = 0x7FFFFFFF)
{
	//ÿ�ζ�ȡ��Ϸ�ڴ���Ŀ�Ĵ�С
	const DWORD pageSize = 4096;

	////////////////////////����������/////////////////////
	//�����볤�Ȳ���Ϊ����
	if (strlen(markCode) % 2 != 0) return 0;
	//�����볤��
	int len = strlen(markCode) / 2;
	//��������ת����byte��
	BYTE *m_code = new BYTE[len];
	memset(m_code,0,len);
	for (int i = 0; i < len; i++){
		char c[] = {markCode[i*2], markCode[i*2+1], '\0'};
		m_code[i] = (BYTE)::strtol(c, NULL, 16);
	}

	/////////////////////////����������/////////////////////
	BOOL _break = FALSE;
	//���������ڵڼ�ҳ�еĵڼ����ҵ���������
	int curPage = 0;
	int curIndex = 0;
	//ÿҳ��ȡ4096���ֽ�
	BYTE *page = new BYTE[pageSize+len-1];
	DWORD tmpAddr = beginAddr;
	DWORD ord = 0;
	while (tmpAddr <= endAddr - len){
		if( ::ReadProcessMemory(process, (LPCVOID)tmpAddr, page, pageSize+len-1, 0) )
		{
			//�ڸ�ҳ�в���������
			for (int i = 0; i < pageSize; i++){
				for (int j = 0; j < len; j++){
					//�����??�򲻴���
					if( m_code[j] == 0 )
					{
						continue;
					}
					//ֻҪ��һ�����������Ӧ�������˳�ѭ��
					if (m_code[j] != page[i + j])break;
					//�ҵ��˳�����ѭ��
					if (j == len - 1){
						ord++;
						if(ord != ordinal)
							break;
						_break = TRUE;
						curIndex = i; // ��������׵�ַƫ��
						break;
					}
				}
				if (_break) break;
			}
		}

		if (_break) break;
		curPage++;
		tmpAddr += pageSize;
	}
	// һ��Ҳû�ҵ�
	if(tmpAddr > endAddr - len)
		return 0;
	// ����Ŀ���ַ
	DWORD offsetaddr = curPage * pageSize + curIndex + beginAddr + distinct;
	if(offset != NULL){
		*offset = offsetaddr;
	}
	// ���ص�ַ����
	DWORD base;
	::ReadProcessMemory(process, (LPVOID)offsetaddr, &base, 4, 0);
	delete m_code;
	delete page;
	return base & 0xFFFFFFFF>>(4-size)*8;
}

//�жϵ�ַ�Ƿ���Ч
bool IsValidAddr(DWORD dwCodeAddr)
{
	static DWORD hModuleHandle = (DWORD)GetModuleHandleA("MHOClient.exe");
	static DWORD hModuleCryGameHandle = (DWORD)GetModuleHandleA("CryGame.dll");
	static DWORD hModuleCryActionHandle = (DWORD)GetModuleHandleA("CryAction.dll");
	static DWORD hModuleMhoClientBaseHandle = (DWORD)GetModuleHandleA("MHOClientBase.dll");
	static DWORD hModuleTersafeHandle = (DWORD)GetModuleHandleA("tersafe.dll");
	if( hModuleHandle != 0 && hModuleCryGameHandle != 0 && hModuleCryActionHandle != 0 && hModuleTersafeHandle != NULL )
	{
		if( dwCodeAddr >= hModuleHandle && dwCodeAddr <= (hModuleHandle+0x01C27000) )
		{
			return true;
		}
		else if( dwCodeAddr >= hModuleCryGameHandle && dwCodeAddr <= (hModuleCryGameHandle+0x01A34000) )
		{
			return true;
		}
		else if( dwCodeAddr >= hModuleCryActionHandle && dwCodeAddr <= (hModuleCryActionHandle+0x011EA000) )
		{
			return true;
		}
		else if( dwCodeAddr >= hModuleMhoClientBaseHandle && dwCodeAddr <= (hModuleMhoClientBaseHandle+0x00C9A000 ) )
		{
			return true;
		}
		else if( dwCodeAddr >= hModuleTersafeHandle && dwCodeAddr <= (hModuleTersafeHandle+0x00841000 ) )
		{
			return true;
		}
	}

	OutputDebugStringA("[LOG] ����ĵ�ַ��Ч!");
	return false;
}

// �����ڴ��ַ
DWORD ScanAddr(HANDLE process, const char *markCode,
			   int distinct,
			   DWORD size = 4,
			   DWORD ordinal = 1,
			   DWORD beginAddr = 0x00400000, DWORD endAddr = 0x7FFFFFFF)
{
	DWORD addr = NULL;
	ScanOpcode(process, markCode, distinct, &addr, size, ordinal, beginAddr, endAddr);
	if( IsValidAddr(addr) )
		return addr;
	return 0;
}

// ����������
DWORD ScanImme(HANDLE process, const char *markCode,
			   int distinct,
			   DWORD size = 4,
			   DWORD ordinal = 1,
			   DWORD beginAddr = 0x00400000, DWORD endAddr = 0x7FFFFFFF)
{
	return ScanOpcode(process, markCode, distinct, NULL, size, ordinal, beginAddr, endAddr);
}

// ���ҵ�ַcall
DWORD ScanCall(HANDLE process, const char *markCode,
			   int distinct,
			   DWORD size = 4,
			   DWORD ordinal = 1,
			   DWORD beginAddr = 0x00400000, DWORD endAddr = 0x7FFFFFFF)
{
	DWORD addr = NULL;
	DWORD cont = ScanOpcode(process, markCode, distinct, &addr, size, ordinal, beginAddr, endAddr);

	DWORD addrret = addr - 1 + 5 + cont;

	if( IsValidAddr(addrret) )
		return addrret;
	return 0;
}

bool IsCryRenderD3D9ValidAddr(DWORD dwCodeAddr)
{
	static DWORD hModuleHandle = (DWORD)GetModuleHandleA("CryRenderD3D9.dll");
	if( hModuleHandle == 0 )
	{
		OutputDebugStringA("[LOG] ��ȡCryRenderD3D9ģ���ַʧ��!");
		return false;
	}

	char szPrint[256];
	sprintf_s(szPrint,"[LOG] 0x%p >= 0x%p && 0x%p <= 0x%p",dwCodeAddr,hModuleHandle,dwCodeAddr,hModuleHandle+0x0062C000);
	OutputDebugStringA(szPrint);

	if( dwCodeAddr >= hModuleHandle && dwCodeAddr <= (hModuleHandle+0x0062C000))
	{
		return true;
	}
	return false;
}

DWORD ScanCryRenderD3D9Addr(HANDLE process, const char *markCode,
			   int distinct,
			   DWORD size = 4,
			   DWORD ordinal = 1,
			   DWORD beginAddr = 0x00400000, DWORD endAddr = 0x7FFFFFFF)
{
	DWORD addr = NULL;
	ScanOpcode(process, markCode, distinct, &addr, size, ordinal, beginAddr, endAddr);
	if( IsCryRenderD3D9ValidAddr(addr) )
		return addr;
	return 0;
}


#endif // __SCANOPCODE_H__