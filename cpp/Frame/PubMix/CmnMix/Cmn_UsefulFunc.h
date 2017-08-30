#pragma once
/*
@author zhp
@date 2016/3/24 18:41
@purpose useful functions
*/
#include "../DependSelfLib.h"
#include <cstddef>
#include <string>
#include <functional>
#include <boost/uuid/uuid.hpp>
#include <CommonX/CmnX_UsefulFunc.h>
#include <vector>
#include <ProtocolX/P_DefinesX.h>
#include <RStd/RString.h>
#include <AppBase/Cmn_Thrd.h>
//////////////////////////////////////////////////////////////////////////
//******************extern***********************************************
extern bool GWndExecSync( const FunctionBool& func );
extern void __stdcall DummySleep(unsigned long milli_seconds);
//////////////////////////////////////////////////////////////////////////

//�õ�ģ��·��
bool GetModulePath( LPCTSTR module_name, LPTSTR path_buffer, pt_dword buffer_size );
bool GetModulePath( LPTSTR path_buffer, pt_dword buffer_size, HMODULE module );
CString GetModulePath( LPCTSTR module_name );
//��ȫ·���еõ�·��
CString GetPathFromFullFilePath( const CString& full_file_path );
//��ȫ·���еõ��ļ���
CString GetFileNameFromFullFilePath( const CString& full_file_path );
bool GetModuleName(HMODULE module, pt_sz buffer, pt_dword buffer_size);
bool GetAddressModuleName(pt_pcvoid address, pt_sz buffer, pt_dword buffer_size);

//�ַ�ת��
//utf-8 convert to gbk
std::string Utf8ToGbk( const char* str_utf8 );
//gbk convert to utf-8
std::string GbkToUtf8( const char* str_gbk );
//gbk convert to wide char
std::wstring GbkToWideChar( const char* str_gbk );
std::wstring GbkToWideChar( const std::string& str_gbk );
//wide char convert to gbk
std::string WideCharToGbk( const std::wstring& str_wide );
std::string WideCharToGbk(const RStd::wstring& str_wide);
std::string WideCharToGbk(const wchar_t* str_wide);
//str to hex
std::string Str2Hex( const char* buffer, unsigned int buf_size );
//hex to str
std::string Hex2str( const char* buffer, unsigned int buf_size );
//�Ƿ���16�����ַ�
bool IsHexadecimal( char c );
//�ָ��ַ���
void SeparateString(const std::string& full_str, const std::string& sep_char, std::vector<std::string>& out_str);
//�������ָ�����ȵ�Ψһ���ַ���
std::string RandomUniqueStr(pt_dword str_size = kUuidStrLen);
std::string RandomUniqueStrEx(pt_dword str_size = kUuidStrLenEx);
//uuidת��Ϊ�ַ���
std::string Uuid2String(boost::uuids::uuid const& u);


//�����ı���������
bool CopyTextToClipboard( const char* str, size_t str_size );
//�Ӽ������ȡ�ı�
std::string GetTextFromClipboard();

//����崻�,return EXCEPTION_CONTINUE_SEARCH�Ⱥ�
//::SetUnhandledExceptionFilter(HandleCrash)
LONG WINAPI HandleCrashImpl(LONG ret_value /*= EXCEPTION_CONTINUE_SEARCH*/, PEXCEPTION_POINTERS pExceptPtrs);
#define HandleCrash(ret_value) HandleCrashImpl(ret_value, GetExceptionInformation())

//load rcdata resource
std::pair<void*, pt_dword> 
	LoadRcdataRes( LPCTSTR module_name, LPCTSTR res_name );
std::pair<void*, pt_dword> 
	LoadRcdataRes( HMODULE module, LPCTSTR res_name );

//��Perl����Ԫ�ַ�ʧȥ����
std::wstring UnsensePerlMetachar( const std::wstring& str_src );
std::string UnsensePerlMetacharA( const std::string& str_src );

HMODULE ModuleFromAddress(pt_pcvoid pv);

//�õ�ʱ����tzd
int GetTzd();

boost::uuids::uuid GenUuidFromBuff(const void* buffer, pt_dword buffer_size);

void XorBufferData(void* out_buffer, const void* buffer_src, pt_dword buffer_size, unsigned char xor_data);

bool CheckOptionalBoolRes(const OptionalBool& res);
//////////////////////////////////////////////////////////////////////////
// Returns the HMODULE that contains the specified memory address
void* GetThreadStartAddr(DWORD thread_id);
void* GetThreadStartAddr(HANDLE handle_thread);
//////////////////////////////////////////////////////////////////////////
void TerminateTheProcess(DWORD process_id);
void TerminateSelfProcess();
//�ö�����
void ForegroundWnd(HWND hWnd);
std::pair<bool, char> Ascii2VK(char c);
//�����¼�
void InputKeybdEventChar(char c);
void InputKeybdEvent(const std::string& str);
//////////////////////////////////////////////////////////////////////////
Cmn_Threadable::ThrdIoService& GetIoService();
void __stdcall DummySleep(unsigned long milli_seconds);
//////////////////////////////////////////////////////////////////////////