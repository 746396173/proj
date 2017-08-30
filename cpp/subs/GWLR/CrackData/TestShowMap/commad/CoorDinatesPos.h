#pragma once

#include <list>
#include "../commad/MyLock.h"

typedef struct
{
	float	fx;
	float	fy;
	float	fz;

	DWORD	dwMapId;
	DWORD	dwRoomId;
}COORDINATES_POS_DATA,*PCOORDINATES_POS_DATA;

#define SHOW_MAP_ALIGN_X	0	// �ӿ�ʼ������ +10��ʼ��ʾ
#define SHOW_MAP_ALIGN_Y	0

class CoorDinatesPos
{
public:
	CoorDinatesPos(void);
	~CoorDinatesPos(void);
public:
	int	GetRandPosId(){return ++m_nIndex;}
	int GetBigShowCount(){return m_nBigShowCount;}
	DWORD GetPosId(){return m_dwPosId;}

	int GetX(){return m_x*GetBigShowCount();}
	int GetY(){return m_y*GetBigShowCount();}

	int GetOriginalX(){return m_x;}
	int GetOriginalY(){return m_y;}
public:
	int AddPos(PCOORDINATES_POS_DATA pthePosData);
	int AddLuaPos(PCOORDINATES_POS_DATA pthePosData,DWORD dwPosId);
	int InitRole(PCOORDINATES_POS_DATA pthePosData);

public:
	int AddConnectPos(CoorDinatesPos* ptheCoorDinatesPos);
	int DelConnectPos(CoorDinatesPos* ptheCoorDinatesPos);
	CoorDinatesPos* FindConnectPos(DWORD dwPosId);

public:
	static void AddBigShowCount(){m_nBigShowCount++;}
	static void SubBigShowCount(){m_nBigShowCount--;}
	static int  GetStaBigShowCount(){return m_nBigShowCount;};

public:
	void Save();
public:
	float	m_fx;		// ��Ϸ����
	float	m_fy;
	float	m_fz;

	DWORD	m_dwMapId;	// ��ͼģ��id
	DWORD	m_dwRoomId;	// �������
protected:
	int		m_x;		// ��Ӧģ������
	int		m_y;

	DWORD	m_dwPosId;	// �������id

	static int	m_nIndex;		// ��˳�������������id
	static int  m_nBigShowCount;		// �Ŵ���ʾ

public:
	std::list<CoorDinatesPos*>	m_theConnectPosList;		// ��������ӵ����������id
	
};

#include "../commad/MyLine.h"
#include "../commad/MyRect.h"
#include "../commad/MyLineFactory.h"


class CmdCoorDinatesPos
{
public:
	CmdCoorDinatesPos(void);
	~CmdCoorDinatesPos(void);

public:
	void Init(PCOORDINATES_POS_DATA ptheCoorDinatesPosData);
	void ReadLuaInit(PCOORDINATES_POS_DATA ptheCoorDinatesPosData,DWORD dwPosId);
	void AddRoleNode();
	void InitRole(PCOORDINATES_POS_DATA ptheCoorDinatesPosData);
	void Show(int nAlignX = 0,int nAlignY = 0);

	int OnMouseMove(CPoint point);
	int OnLButtonDown(UINT nFlags, CPoint point);

	int GetMinX();
	int GetMinY();

	// ͨ����Ļ����ת��Ϊ�ڴ�����
	float GetFx(float fx){return fx+GetMinX()/CoorDinatesPos::GetStaBigShowCount()-SHOW_MAP_ALIGN_X; };
	float GetFy(float fy){return fy+GetMinY()/CoorDinatesPos::GetStaBigShowCount()-SHOW_MAP_ALIGN_Y; };
	
	int GetPosCount(){return m_CoorDinatesPosList_cmd.size();}

public:
	int AddConnectPos(DWORD dwPosId1, DWORD dwPosId2);
	int DelConnectPos(DWORD dwPosId1, DWORD dwPosId2);
	CoorDinatesPos* GetCoorDinatesPosAddr(DWORD dwPosId);

	int DelPos(DWORD dwPosId);

public:
	void Remove();

public:
	void Save();
	void Read();
public:
	std::list<CoorDinatesPos*>	m_CoorDinatesPosList_cmd;
	CMyLock						m_theCmdLock;

	CMyBaseShape*	m_pTempShape;
	IMyFactory*		m_lpBaseFactory;
	CRect			m_WndRect;
	CClientDC*		m_pdc;

public:
	CoorDinatesPos m_theRoleCoorDinatesPosData;
	
};

extern CmdCoorDinatesPos	theCmdCoorDinatesPos;