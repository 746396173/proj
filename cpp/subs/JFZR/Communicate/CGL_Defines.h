#pragma once
/*
@author zhp
@date 2014/6/15 15:12
@purpose console.exe/game.dll/login.dll֮��Ľ���
*/

//�汾�ַ���
#ifdef __PROJ_JFZR_
//�汾��
const unsigned short kAssistVersion = 0x001;
const char* const kAssistVersionUuidGenerator =
	"6D7AF229-1FF7-432B-9154-79AB2A5EF988";
//�汾uuid�����
const unsigned char kAssistVersionXor = 0xd1;
//��������
const unsigned int kGameConnectionMaxCnt = 99999;
#elif defined(__PROJ_JFZR_SM_)
//�汾��
const unsigned short kAssistVersion = 0x001;
const char* const kAssistVersionUuidGenerator =
	"9E3AC972-718F-4C00-913B-9594386B10ED";
//�汾uuid�����
const unsigned char kAssistVersionXor = 0xa3;
//��������
const unsigned int kGameConnectionMaxCnt = 1;
#elif defined(__PROJ_JFZR_TWO_)
//�汾��
const unsigned short kAssistVersion = 0x001;
const char* const kAssistVersionUuidGenerator =
	"E8DC12A9-09C1-443F-1F17-3A74463BECC4";
//�汾uuid�����
const unsigned char kAssistVersionXor = 0x3f;
//��������
const unsigned int kGameConnectionMaxCnt = 2;
#endif

//�汾�¼�������
const char* const kAssistVersionEventObj = "_ComAtlStUads_";

//�����汾У��
bool CreateCheck_AssistVersion();
//���а汾У��
bool CheckAssistVersion();

//��Ϸģ������
#define P_INJECTED_GAME_NAME _T("JFZR.exe")
