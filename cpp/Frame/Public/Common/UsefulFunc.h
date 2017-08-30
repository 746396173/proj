#pragma once
/*
@author zhp
@date 2013-12-29
@purpose utilities policy
*/
#include "stdafx.h"
#include <boost/asio/io_service.hpp>
#include <Poco/Types.h>
#include <atlpath.h>
#include <boost/filesystem.hpp>
#include <random>
#include <boost/uuid/uuid.hpp>
#include <Net/PocoMore.h>
#include <Protocol/P_Defines.h>
#include <Net/IoService.h>
#include <CommonX/CmnX_UsefulFunc.h>
#include <CmnMix/Cmn_UsefulFunc.h>
#include "../DependSelfLib.h"
#include <AppBase/Cmn_Thrd.h>

//////////////////////////////////////////////////////////////////////////
//******************extern***********************************************
extern TimeDuration& GetGlobalTimeDuration();
//////////////////////////////////////////////////////////////////////////

//������˵�ǰ�߳�֮����߳�
void WINAPI SupendProcess( bool is_suspend );

#ifdef UNICODE
#define InjectLib InjectLibW
#define EjectLib  EjectLibW
#else
#define InjectLib InjectLibA
#define EjectLib  EjectLibA
#endif
BOOL WINAPI InjectLibW(DWORD dwProcessId, PCWSTR pszLibFile);
BOOL WINAPI InjectLibA(DWORD dwProcessId, PCSTR pszLibFile);
BOOL WINAPI EjectLibW(DWORD dwProcessId, PCWSTR pszLibFile);
BOOL WINAPI EjectLibA(DWORD dwProcessId, PCSTR pszLibFile);

//DetourCreateProcessWithDll �������̵�ʱ�����������ע��dll
bool LoadLib( const char* lib_name );
bool FreeLib( const char* lib_name );

//������ǰ���̵�Ȩ��
bool AdjustProcessTokenPrivilege();
//////////////////////////////////////////////////////////////////////////
//ѡ���ļ��У������Ŀ¼
CString GetBrowseFolder( HWND pParent );

//load rcdata resource
//������Դ���ļ���
bool SaveRcdataAsFile( HMODULE module, LPCTSTR res_name, const CPathW& full_file_name );
bool SaveRcdataAsFile(LPCTSTR module_name, LPCTSTR res_name, const CPathW& full_file_name);
bool SaveRcdataAsFile(HMODULE module, LPCTSTR res_name, const CPathA& full_file_name);
bool SaveRcdataAsFile(LPCTSTR module_name, LPCTSTR res_name, const CPathA& full_file_name);
//�ļ��б仯�ĲŻᱣ��
bool CopyUnsameFile( const std::string& file_src, const std::string& file_dst );

std::random_device& GetDltRandomDevice();
//ĳ����ֵ����������,����[0, 100]
int RandomNum( int min_num, int max_num );
//���ݳ��ָ����ж��Ƿ����
bool IsOccuredByOccurRate( double occur_rate );
//�������ָ�����ȷ�Χ����ĸ�����ֵ����,[cnt_min, cnt_max]
std::string Random_Str( size_t cnt_min, size_t cnt_max );
std::wstring Random_StrW( size_t cnt_min, size_t cnt_max );
//ֻ������ĸ������������
std::string Random_LetterStr(size_t cnt_min, size_t cnt_max);
//��һ���ַ�������һ���̶���uuid�ַ���
std::string GenUuidStr( const std::string& str_src );
std::string GenUuidStr( const void* buffer, pt_dword buffer_size );
std::string GenUuidStr( std::istream& istm );
std::string GenUuidStrOfFile( const std::string& full_file_name );
//����һ������������һ���̶���uuid�ַ���
std::string GenUuidStrFromGenerator( const std::string& str_src, const std::string& str_generator );
//����һ���µ�RSA�����ļ�
bool GenNewRsaKeyFile( const std::string& str_out_to_pub_file, const std::string& str_out_to_pri_file, const std::string& str_private_key );

//////////////////////////////////////////////////////////////////////////
//sleep,���ڲ���Ȼ�ᴦ����Ϣ
bool WaitUntil(const FunctionBool& func_until);
bool WaitUntil(pt_dword timeout, const FunctionBool& func_until);
bool DoWaitUntil(pt_dword timeout, const FunctionBool& func_until, const FunctionVoid& func_do);
bool TimerDoWaitUntil(pt_dword timer_time, pt_dword timeout, const FunctionBool& func_until, const FunctionVoid& func_do);
namespace Details{
	template<>
	struct stTimerDoByPolicy<tagTimerDoDummySleep>{
		static bool TimerDoImpl(pt_dword every_sleep, pt_dword time_out, const FunctionBool& func_do);
	};
};
//////////////////////////////////////////////////////////////////////////

//��ֵƴ��
unsigned __int64 MakeInt64( Poco::UInt32 lower, Poco::UInt32 upper );
//��ֵ�ָ�,first==lower,second==upper
std::pair<Poco::UInt32, Poco::UInt32> SplitInt64( Poco::UInt64 big_value );

//���������
//��û�����
bool GetHWID( char* out_buffer, pt_dword buffer_size );
//�õ������Ļ�����
bool GetMixHWID( char* out_buffer, pt_dword buffer_size );
//Ӳ�̵��������к�
bool GetPhyHardDiskId( std::string& str_buffer );
//�õ�CPU id
bool GetCpuId( std::string& str_buffer );
//�õ�����mac
bool GetMac( std::string& str_buffer );
//�õ������߼����к�
bool GetAllDiskSubareaSN( std::string& str_buffer );
//�õ�Ӳ�̷���������
bool GetAllDiskSubareaSize( std::string& str_buffer );
//�õ�����ϵͳ�汾��
bool GetOsVersionStr( std::string& str_buffer );
//�õ�ָ��Ӳ�������к�
bool GetTheSerialNumber( const char* const class_name, std::string& out_str );
//�õ�bios���
bool GetBiosNumber( std::string& str_buffer );
//�õ�������
bool GetBaseBoardNumber( std::string& str_buffer );
//�õ�Ӳ�̱��
bool GetPhysicalMediaNumber( std::string& str_buffer );

//��ʾһ������ʽ�˵�
void ShowPopupMenu( UINT resource_id, CWnd* parent );

//��֤Ψһʵ��
bool CheckSingletonHandle( const std::string& str_handle_name );

//�����ļ�
bool DoFileItem( const std::string& path_file, const std::function<void( const boost::filesystem::directory_iterator& )>& func );
bool DoExtensionFileItem( const std::string& path_file, const std::string& file_extension, const std::function<void( const boost::filesystem::directory_iterator& )>& func );
//�����༶�ļ���
int CreateDepthDirectory( const CPath& dir_path );
void CopyAllFilesOfDirectory( const boost::filesystem::path &src, const boost::filesystem::path &dst, const std::function<bool( const boost::filesystem::directory_iterator& )>* but_func );
std::string GetSystemFolderPath(int folder);
std::string GetMyDocumentsFolderPath();

//��������
std::string Domain2Ip( const std::string& domain, unsigned short int port = 0 );
//////////////////////////////////////////////////////////////////////////
//*******************algorithm extern*************************************
//���׼���unique��ͬ������������ظ�Ԫ�ص�����
template<class _FwdIt> inline
	_FwdIt Unique(_FwdIt _First, _FwdIt _Last)
{
	if (_First != _Last)
		for (_FwdIt _Firstb; (_Firstb = _First), ++_First != _Last; )
			if (*_Firstb == *_First)
			{	// copy down
				for (; ++_First != _Last; )
					if (!(*_Firstb == *_First))
					{
						++_Firstb;
						std::swap(*_Firstb, *_First);
					}
					return (++_Firstb);
			}
	return (_Last);
}
//////////////////////////////////////////////////////////////////////////
//ע������
void AutoRegLpk();
//�������г���
void AutoRunAtSystemBegin( const std::string& reg_value, const std::string& run_param );
void DeleteAutoRunAtSystemBegin( const std::string& reg_value );
//////////////////////////////////////////////////////////////////////////
//����ϵͳ
void RestartSystem();
//////////////////////////////////////////////////////////////////////////
boost::optional<std::wstring> Regex_SearchFirstSubStr( const std::wstring& full_str, const std::wstring& str_pattern );
std::vector<std::wstring> Regex_FindAllTheStr( const std::wstring& full_str, const std::wstring& str_pattern );
OptionalBool Regex_MatchAllSubStr( const std::wstring& full_str, const std::wstring& str_pattern, const std::wstring& matched_str );
std::wstring Regex_ReplaceSubStr( const std::wstring& full_str, const std::wstring& str_pattern, const std::wstring& str_fmt );
boost::optional<std::wstring> Regex_ReplaceUnsameSubStr( const std::wstring& full_str, const std::wstring& str_pattern, const std::wstring& str_fmt );
bool Regex_ModifySubStrOfFile( const std::string& full_file_name, const std::string& str_pattern, const std::string& str_fmt );
bool Regex_ModifySubStrOfFileByStrTag( const std::string& full_file_name, const std::string& str_tag, const std::string& new_str );
bool Regex_ModifySubStrOfFileByStrTagIncInt( const std::string& full_file_name, const std::string& str_tag );
//////////////////////////////////////////////////////////////////////////
//���ſ���Ƿ�����
bool IsDialBroadbandConnecting();
//�Ͽ����ſ������
int CloseDialBroadband();
//�������ſ��
bool ReDialBroadband();
//////////////////////////////////////////////////////////////////////////
DateTimeLocal G_GetSerCurTime();
void G_SetCurTime(const std::time_t& time);
//////////////////////////////////////////////////////////////////////////
void WriteQqLoginRecord(const std::string& qq_num, pt_dword service_id, const std::string& full_file_name_path);
