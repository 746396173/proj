#pragma once

#define LPK_CHECK_EVENT			"FFDFFF9A-5EDC-40a5-96E4-C5395B2CFFE7"
#define LPK_CHEKC_FILEMAPPING	"E750A151-1227-4c88-92BF-F0EEFCFD2A69"
#define LPK_CHECK_VIEWOFFILE	"{0A46BE53-0E77-49eb-A4BC-7AAEDF68118A}{3C7BB159-A43D-4822-9B40-33CAD4D3BDC6}"
#define LPK_CHEKC_FILEMAPPING1	"97B57C9B-79FF-4b29-BD18-9C3E3E3AF7A0"
#define LPK_CHECK_VIEWOFFILE1	"5E4DC4A9-91F5-4f7c-BF89-AA28A83413D6"

class CheckLpk
{
private:
	HANDLE	m_hEvent;
	HANDLE	m_hMapFile;
	PVOID	m_pView;
public:
	CheckLpk(void);
	~CheckLpk(void);
public:
	// �����¼�����	����һ��Ҫ�������¼����������
	bool LpkCreateEvent(const char* pszObjEvent);
	void LpkCloseEvent();

	// ���¼����� ����һ���Ѿ��������¼����������
	bool LpkOpenEvent(const char* pszObjEvent);

	// �����ڴ湲����� ����һ��Ҫ�����������ڴ���������
	bool LpkCreateFileMapping(const char* pszFileMappingObj);

	// д�����ݵ������ڴ� ����һ��Ҫ��д�������
	bool LpkFlushViewOfFile( const char* pszData, int str_len );

	// ���ڴ湲����� ����һ���Ѿ����������ڴ湲���������� ����������ȡ���ݵĲ���
	bool LpkOpenFileMapping(const char* pszFileMapping, OUT char* pszOutData);
	PVOID LpkOpenConsoleFileMapping(const char* pszFileMapping);

	// ������
	bool xor(const char* pszData, char* pszOutData);

};

extern CheckLpk	g_theCheckLpk;;


///////////////////////////////////////////////////////////////////////////////////////
// �������ܣ�	����LPK��֤�ӿ�
// ������		Ԥ���ӿڣ���ʱ����,�� NULL ����
// ����ֵ��		true ��ʾ�ɹ��� false ��ʾʧ��
///////////////////////////////////////////////////////////////////////////////////////
extern bool OpenCheckLpk(LPVOID lpParameter);
