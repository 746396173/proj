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
//��½����ѡ��������Ĵ�������
const LPCTSTR kLoginSelectServiceWndClsName = _T("e649e249_0000442e_00004f2d_0018c024");
//��½���������������
const LPCTSTR kLoginMainWndName = _T("��������Online��¼����");
//��½���������·��
const LPCTSTR kRelativeClient = _T("TCLS\\");
//��½��������
const LPCTSTR kLoginClientName = _T("Client.exe");

//��֤�����Ϊ��Ŀ������
const LPCTSTR kCaptchaPicNewName = _T("NewCaptcha.png");

//����̨����gameģ��һ���̶����ַ���
#ifdef __PROJ_GWLR_MB_
const char* const kStableStr_ConsoleToLogin = 
	/*kStableStr_ConsoleToLogin_mb*/"5635ee5f-4d4d-41e1-8543-8e952b00aa79";
#elif (__PROJ_GWLR_XE_)
const char* const kStableStr_ConsoleToLogin = 
	/*kStableStr_ConsoleToLogin_xe*/"aca51561-5dce-4f12-b1f9-2e8244d566a8";
#elif (__PROJ_GWLR_MBP_)
const char* const kStableStr_ConsoleToLogin = 
	/*kStableStr_ConsoleToLogin_mbp*/"44d68105-4f81-4671-8104-cf4d411318c2";
#endif
//login operator
const P_ObjId kObjId_LoginOper = DEF_THE_CUSTOM_TEMPLATE_OBJ_ID_(1);