#pragma once

// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

//0x501==XP, 0x0600==win7
#ifndef _WIN32_WINNT
#error _WIN32_WINNT �����Ѷ���
#endif

//������Ԥ���������涨��
//#define _WIN32_WINNT 0x502
#define _AFX_NO_MFC_CONTROLS_IN_DIALOGS         // remove support for MFC controls in dialogs
#define WINDOWS_ENABLE_CPLUSPLUS
#define STRSAFE_NO_DEPRECATE

#define _WINSOCK_DEPRECATED_NO_WARNINGS		//error C4996: 'WSAAddressToStringA': Use WSAAddressToStringW() instead or define _WINSOCK_DEPRECATED_NO_WARNINGS to disable deprecated API warnings

/*Ӱ��std::tuple��ģ��Ĳ�������*/
#if defined(_VARIADIC_MAX)
#  error _VARIADIC_MAX ����Լ�������
#  undef _VARIADIC_MAX
#endif /* !defined(_VARIADIC_MAX) */
#define _VARIADIC_MAX 10
/*��������������*/
#define CMN_ARITY_MAX 15

#ifdef _DEBUG
#define _WG_TEST
#else
//vmp����
//#define __VMP__
/**/
#ifdef __RELEASE_LOG_INFO_
#define _LOG_OUT_BY_LEVEL Log_info
#endif
/**/
#endif

#include <SDKDDKVer.h>

//luaʹ��jsonʱҪ����˺�
#define _LUA_USE_JSON
//luaʹ��poco����http�ַ���ʱҪ����˺�
#define _LUA_USE_POCO_PARSE_HTTP_STR
//luaʹ�ö��ַ���ƥ��Ҫ����˺�
#define _LUA_USE_MULTI_STR_MATCH
//version of dx input
#define DIRECTINPUT_VERSION 0x0800

//ʹ��windows API����ΪPoco���и�unwindows.h�ļ�����windows API����undef��
#define POCO_NO_UNWINDOWS
//diable some warnings
#define _SCL_SECURE_NO_WARNINGS
/**/
#ifdef POD_TO_CLASS
#define POD_TO_CLASS_UNWIND(code) code
#define POD_TO_CLASS_COMMA ,
#else
#define POD_TO_CLASS_UNWIND(code)
#define POD_TO_CLASS_COMMA
#endif
#define POD_TO_CLASS_VIRTUAL POD_TO_CLASS_UNWIND(virtual)
/**/
#ifndef _WIN32_DCOM
#define _WIN32_DCOM
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
//////////////////////////////////////////////////////////////////////////
//************************������****************************************
//�������������ľ��棺warning LNK4099: PDB 'lib.pdb' was not found with
//#pragma warning(disable:4099)
//////////////////////////////////////////////////////////////////////////
//************wxLua
#include <luabind_wx/wxlua_config.h>
//////////////////////////////////////////////////////////////////////////
