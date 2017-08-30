#pragma once
/*
@author zhp
@date 2014-1-16
@purpose ȫ�����ú;�������
*/
#include <fstream>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include "LogOut.h"
#include <Common/CmnException.h>
#include "../DependSelfLib.h"

class XmlCfg{
	XmlCfg();
public:
	//����
	template<typename T>
	static void Save( const T& obj, const char* full_file_name ){
		try{
			std::ofstream ofs(full_file_name);
			assert(ofs.good());
			boost::archive::xml_oarchive oa(ofs);
			oa << BOOST_SERIALIZATION_NVP(obj);
			//LOG_O(Log_trace) << "������ļ����ǣ�" << full_file_name;
		}
		DO_CATCH_THE_EXCEPTION( const std::exception& e, {
			LOG_O(Log_debug) << e.what();
		})
	}
	template<typename T>
	static void Save( const T& obj, std::ostream& ofs ){
		try{
			assert(ofs.good());
			boost::archive::xml_oarchive oa(ofs);
			oa << BOOST_SERIALIZATION_NVP(obj);
			//LOG_O(Log_trace) << "�������ݵ���";
		}
		DO_CATCH_THE_EXCEPTION( const std::exception& e, {
			LOG_O(Log_debug) << e.what();
		})
	}
	template<typename T>
	static void Save( const T& obj, const std::string& full_file_name ){
		Save(obj, full_file_name.c_str());
	}
	//��ȡ
	template<typename T>
	static void Restore( T& obj, const char* full_file_name ){
		try{
			std::ifstream ifs(full_file_name);
			assert(ifs.good());
			//LOG_O(Log_trace) << "��ȡ���ļ����ǣ�" << full_file_name;
			boost::archive::xml_iarchive ia(ifs);
			// restore the schedule from the archive
			ia >> BOOST_SERIALIZATION_NVP(obj);
		}
		DO_CATCH_THE_EXCEPTION( const std::exception& e, {
			LOG_O(Log_debug) << e.what();
		})
	}
	template<typename T>
	static void Restore( T& obj, std::istream& ifs ){
		try{
			assert(ifs.good());
			boost::archive::xml_iarchive ia(ifs);
			// restore the schedule from the archive
			ia >> BOOST_SERIALIZATION_NVP(obj);
			//LOG_O(Log_trace) << "�����лָ�����";
		}
		DO_CATCH_THE_EXCEPTION( const std::exception& e, {
			LOG_O(Log_debug) << e.what();
		})
	}
	template<typename T>
	static void Restore( T& obj, const std::string& full_file_name ){
		Restore(obj, full_file_name.c_str());
	}
	//restore helper
	template<typename T>
	struct RestoreHelper{
		RestoreHelper( T* obj_ptr, const std::string& full_file_name ){
			Init(obj_ptr, full_file_name.c_str());
		}
		RestoreHelper( T* obj_ptr, const char* full_file_name ){
			Init(obj_ptr, full_file_name);
		}
		~RestoreHelper(){
			if ( !full_file_name_.empty() && PathFileExistsA(full_file_name_.c_str()) )
				Restore<T>(*obj_ptr_, full_file_name_);
		}
	private:
		void Init( T* obj_ptr, const char* full_file_name ){
			obj_ptr_ = obj_ptr;
			if (full_file_name)
				full_file_name_ = full_file_name;
		}
		T*				obj_ptr_;
		std::string		full_file_name_;
	};
	//�õ�����Ŀ¼
	static const std::string& GetCfgPath();
	//�����ļ���
	static std::string GenFileNameBy( const char* account );
	//�õ�ȫ·����
	static std::string MakeFullFileName( const char* account );
	//�õ�Ĭ�������ļ���
	static const char* GetFileName_DefaultCfg();
	//�õ�ȫ��Ψһ�����ļ���
	static const std::string& GetFullFileName_SingletonCfg();
};

namespace boost{
namespace serialization{
	void serialize( boost::archive::xml_oarchive& ar, CString& str, const unsigned int var );
	void serialize( boost::archive::xml_iarchive& ar, CString& str, const unsigned int var );
}
}