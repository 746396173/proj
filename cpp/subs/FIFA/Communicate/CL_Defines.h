#pragma once
/*
@author zhp
@date 2014/6/15 15:15
@purpose console.exe/login.dll֮��Ľ���
*/
#include <WTypes.h>
#include <Protocol/P_Defines.h>

//��½���������������
const LPCTSTR kLoginMainClsName = _T("TWINCONTROL");
//��½���������������
const LPCTSTR kLoginMainWndName = _T("FIFA Online 3��¼����");
//��½���������·��
const LPCTSTR kRelativeClient = _T("TCLS\\");
//��½��������
const LPCTSTR kLoginClientName = _T("Client.exe");

//��֤�����Ϊ��Ŀ������
const LPCTSTR kCaptchaPicNewName = _T("NewCaptcha.png");

//����̨����gameģ��һ���̶����ַ���
const char* const kStableStr_ConsoleToLogin = 
	"572BF63C-69618-4215-3hE9-0841E231244fa";

//login operator
const P_ObjId kObjId_LoginOper = DEF_THE_CUSTOM_TEMPLATE_OBJ_ID_(1);