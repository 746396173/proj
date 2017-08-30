#pragma once
/*
@author zhp
@date 2016/1/22 8:54
@purpose һЩLPK�����ݷ���ͨ�ýṹ��
*/
#include <ProtocolX/P_BaseTypeX.h>
#include <string>

typedef struct  
{
	WORD	wPacketLen;
	WORD	wMethodType;			// �������ͣ����� http�е� get,post,put,delete
	WORD	wUrlType;				// ����ʵ�ַ�����������
}PACKET_TYPE,*PPACKET_TYPE;

const pt_csz kLpkVersion = "D5CFEE4C-8518-44BF-8198-A6EF06128D69";

struct stLpkData{
	std::string		version_;
	std::string		cry_render_d3d9_;

	pt_dword		hook_dx_press_key_;			// hook dx press key�� �����ж��Ƿ���Ҫȡ���ͻָ��Ż�
	pt_dword		hook_render_;				// ��Ⱦ�߳��Ż�
	pt_dword		black_screen_render_;		// �����Ż��Ļ�ַƫ�Ƶ�ַ  CryRenderD3D11.dll

	pt_dword		sprintf_func_;				// MHOClientBase.dll �е�sprintf���ܣ�ƴ���ַ����������ڶ࿪���ַ���
	pt_dword		tersafe_get_cpuid_;			// tersafe.dll hook GetCpuId���ܺ���
	pt_dword		tersafe_code_crc_hook_;		// tersafe.dll hook ��� crc �Ĵ���

	std::string		snprintf_;					// �࿪ "_snprintf"
	std::string		ZwCreateMutant_;			// "ZwCreateMutant"
	std::string		CreateToolhelp32Snapshot_;	// "CreateToolhelp32Snapshot"
	std::string		EnumProcesses_;
	std::string		ZwQuerySystemInformation_;
	std::string		ZwQueryInformationProcess_;
	std::string		NtCreateFile_;
	std::string		ZwCreateEvent_;
	std::string		FindNextFileA_;
	std::string		DeviceIoControl_;
	std::string		ZwDeviceIoControlFile_;
	std::string		ZwCreateSection_;
	std::string		MemCpy_;					// hook ntdll memcpy
	std::string		CreateThread_;
	std::string		ZwOpenProcess_;

	stLpkData(){
		hook_dx_press_key_ = 0;
		hook_render_ = 0;
		black_screen_render_ = 0;
		sprintf_func_ = 0;
		tersafe_get_cpuid_ = 0;
		tersafe_code_crc_hook_ = 0;
	}
	template<typename T>
	void serialize(T& stm){
		stm & version_
			& cry_render_d3d9_
			& hook_dx_press_key_
			& hook_render_
			& black_screen_render_
			& sprintf_func_
			& tersafe_get_cpuid_
			& tersafe_code_crc_hook_
			& snprintf_
			& ZwCreateMutant_
			& CreateToolhelp32Snapshot_
			& EnumProcesses_
			& ZwQuerySystemInformation_
			& ZwQueryInformationProcess_
			& NtCreateFile_
			& ZwCreateEvent_
			& FindNextFileA_
			& DeviceIoControl_
			& ZwDeviceIoControlFile_
			& ZwCreateSection_
			& MemCpy_
			& CreateThread_
			& ZwOpenProcess_
			;
	}
};