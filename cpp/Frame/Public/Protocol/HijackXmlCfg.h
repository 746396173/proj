#pragma once
/*
@author zhp
@date 2014-3-9 21:59
@purpose for hijack dll xml config
*/
#include "stdafx.h"
#include "Common/XmlCfg.h"
#include <boost/serialization/version.hpp>
#include "Common/UsefulClass.h"
#include "../DependSelfLib.h"

//�ٳ�DLLʹ��
struct stHijackDllCfg
{
	stHijackDllCfg();
	//�����ļ���
	static LPCTSTR GetCfgFileName();

	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive & ar, const unsigned int version ){
		ar & BOOST_SERIALIZATION_NVP(injected_game_name_)
			& BOOST_SERIALIZATION_NVP(inject_dll_full_path_);
	}

	CString			injected_game_name_;			//��ע�����Ϸ��ģ����
	CString			inject_dll_full_path_;			//ע��DLL��ȫ·��
};
BOOST_CLASS_VERSION(stHijackDllCfg, 1)

class stHijackProfile : public IniProfile{
public:
	bool Load();
	bool Save();
	//�����ļ���
	static LPCTSTR GetCfgFileName();

public:
	std::string		injected_game_name_;
	std::string		inject_dll_full_path_;

public:
	static const char* const kMainSetion;
};