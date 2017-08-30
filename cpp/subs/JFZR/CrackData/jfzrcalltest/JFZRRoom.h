#pragma once



typedef struct
{
	char		str_szRoomSerial[64];
	char		str_szRoomWarp[3][64];
	char		str_szFbName[256];		
	wchar_t		str_wszRoomSerialEx[64];		// �������
	wchar_t		str_wszRoomWarpEx[3][64];		// ��
	int			str_i;							// ѡ����
	wchar_t		str_wszFbNameEx[256];			// ��������
	bool		str_bIsClear;					// �Ƿ����
	bool		str_bRoom1Flag;
	bool		str_bRoom2Flag;
	bool		str_bRoom3Flag;
	
	struct
	{
		float		str_fx;
		float		str_fy;
		float		str_fz;
	}str_Coord[3];
}ROOM,*PROOM;


class JFZRRoom
{
public:
	JFZRRoom(void);
	~JFZRRoom(void);
public:
	
public:
	bool UpDataRoom(ROOM* theCurRoom);
	bool UpDataCity(PROOM ptheCurRoom);
public:
	CString	csTxt;
	bool DoFb(wchar_t* wszFbName,DWORD dwLevel,wchar_t* wszBoosSerialEx);
	bool push(PROOM ptheRoom,CList<ROOM*,ROOM*>& theRoomList);
	PROOM pop(CList<ROOM*,ROOM*>& theRoomList);
};
