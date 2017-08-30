#pragma once
/*
@author zhp
@date 2016/3/24 18:40
@purpose some useful little class
*/
#include "../DependSelfLib.h"
#include <CommonX/CmnX_UsefulClass.h>

class EnumPidWnd{
public:
	struct FindInfo{
		HWND			str_hParWnd;						//�����ھ��
		TCHAR			str_szExeFile[MAX_ZONE_PATH];		//��������,���޴�Сд,������д
		TCHAR			str_szWndName[MAX_ZONE_PATH];		//��������
		TCHAR			str_szClassName[MAX_ZONE_PATH];		//��������
		DWORD			str_GWL_STYLE;						//���ڷ��
		DWORD			str_GWL_EXSTYLE;					//��չ���ڷ��
		DWORD			str_GCL_STYLE;						//������ķ��
		DWORD			str_x;								//���ڿ��
		DWORD			str_y;								//���ڸ߶�
		boost::optional<BOOL>	m_bIsWindowVisible;
		mutable DWORD	pid_;
		DWORD			thrd_id_;

		FindInfo();
		bool IsTheFeature(HWND hWnd) const;
	};
	struct stButInfo{
		HWND		but_wnd_;
		pt_dword	but_thrd_id_;

		stButInfo();
	};

public:
	//EnumWindowsö�ٵ�����Ļ�Ķ��㴰�ڡ�
	HWND FindTheWnd(const FindInfo& find_info);
	HWND FindTheWndBut(const FindInfo& find_info, const stButInfo& but_info);
	static pt_dword GetPidByName(LPCTSTR pname);

private:
	static BOOL CALLBACK EnumProc_IsTheFeature(HWND hWnd, LPARAM lPraram);
	static BOOL CALLBACK EnumProc_IsTheFeatureBut(HWND hWnd, LPARAM lPraram);
	static pt_dword ParsePid(pt_dword the_pid, const FindInfo& find_info);
};
