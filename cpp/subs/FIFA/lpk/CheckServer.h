#pragma once

class CheckServer
{
public:
	bool	m_bRunExeFlag;
	char	m_szReleaseResExeFile[260];

public:
	CheckServer(void);
	~CheckServer(void);

public:
	// ���м�����
	bool Check();

	// �ָ�ִ���ļ�
	bool UnTenioDL(void);

	bool Close();
};

extern CheckServer g_theCheckServer;