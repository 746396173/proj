#pragma once
/*
@author zhp
@date 2014-1-17
@purpose config struct saved to xml
*/
#include "Common/XmlCfg.h"
#include <boost/serialization/version.hpp>
#include <boost/serialization/vector.hpp>
#include "Protocol/P_Defines.h"
#include <atlpath.h>
#include <Socket/PocoMore.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeParser.h>
#include <Communicate/CG_Defines.h>
//////////////////////////////////////////////////////////////////////////
//���ⷽʽ
struct stCrackCaptchaMode{
	enum enCrackCaptchaMode
	{
		kCCM_Local,					//���ش���
		kCCM_DaMaTu,				//������
	};

	stCrackCaptchaMode() : remote_ip_(kSelfIpStr){
		ccm_ = kCCM_Local;
		remote_port_ = P_Port_Game + 10;
	}

	template<class Archive>
	void serialize( Archive & ar, const unsigned int version ){
		ar & BOOST_SERIALIZATION_NVP(account_)
			& BOOST_SERIALIZATION_NVP(password_)
			& BOOST_SERIALIZATION_NVP(ccm_)
			& BOOST_SERIALIZATION_NVP(remote_ip_)
			& BOOST_SERIALIZATION_NVP(remote_port_)
			;
	}

	std::string					account_;			//ĳ���ⷽʽ���ʺ�
	std::string					password_;			//ĳ���ⷽʽ������
	enCrackCaptchaMode			ccm_;				//���ⷽʽ
	std::string					remote_ip_;			//һ��ֻ�����ڱ��ش���
	WORD						remote_port_;		//һ��ֻ�����ڱ��ش���
};
//////////////////////////////////////////////////////////////////////////
//global/singleton xml
//����˼�壬ȫ��Ψһ������
struct stSingletonCfg
{
protected:
	stSingletonCfg( const std::string& str_cfg_full_path ) : stored_ip_(kSelfIpStr){
		max_login_ = 15;
		role_max_cnt_ = 1;
		login_delay_ = 3 * 60;

		XmlCfg::RestoreHelper<stSingletonCfg> restore_helper(this, 
			str_cfg_full_path);
	}

public:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize( Archive & ar, const unsigned int version ){
		ar & BOOST_SERIALIZATION_NVP(game_full_file_path_)
//#ifdef _WG_TEST
#ifdef false
			& BOOST_SERIALIZATION_NVP(test_dll_full_file_path_)
#endif
			& BOOST_SERIALIZATION_NVP(cfg_of_accounts_)
			& BOOST_SERIALIZATION_NVP(authen_account_)
			& BOOST_SERIALIZATION_NVP(authen_password_)
			& BOOST_SERIALIZATION_NVP(crack_captcha_mode_)
			& BOOST_SERIALIZATION_NVP(max_login_)
			& BOOST_SERIALIZATION_NVP(stored_ip_)
			& BOOST_SERIALIZATION_NVP(io_h_)
			& BOOST_SERIALIZATION_NVP(role_max_cnt_)
			& BOOST_SERIALIZATION_NVP(login_delay_)
			;
	}
	//����
	void Save();

	//type definition
public:
	struct AccountType : std::pair<CString, CString>{
		template<class Archive>
		void serialize( Archive & ar, const unsigned int version ){
			ar & BOOST_SERIALIZATION_NVP(first)
				& BOOST_SERIALIZATION_NVP(second)
				& BOOST_SERIALIZATION_NVP(service_name_)
				;
		}

		CString					service_name_;
	};
	typedef std::vector<AccountType> AcountContT;
	struct IoHelper{
		IoHelper() : last_check_roles_(1999, 1, 1){}
		void serialize( boost::archive::xml_oarchive& ar, const unsigned int var ){
			ar << boost::serialization::make_nvp("last_check_roles_", 
				Poco::DateTimeFormatter::format(last_check_roles_, Poco::DateTimeFormat::SORTABLE_FORMAT));
		}
		void serialize( boost::archive::xml_iarchive& ar, const unsigned int var ){
			std::string str_pro_at_time;
			ar & boost::serialization::make_nvp("last_check_roles_", str_pro_at_time);
			int time_zone = 0;
			if ( !Poco::DateTimeParser::tryParse(Poco::DateTimeFormat::SORTABLE_FORMAT, str_pro_at_time, last_check_roles_, time_zone) )
			{
				assert(false);
				last_check_roles_ = Poco::DateTime(1999, 1, 1);
			}
		}

		DateTimeLocal			last_check_roles_;				//��һ����֤��ɫ��ʱ��
	};

public:
	//Ψһʵ��
	static stSingletonCfg& GetMe();

public:
	CString									game_full_file_path_;			//��Ϸ·��
	std::string								test_dll_full_file_path_;		//����DLL��ȫ��Ϸ
	AcountContT								cfg_of_accounts_;				//�ʺŵ�����
	//for authenticate
	CString									authen_account_;				//wg account
	CString									authen_password_;				//wg password
	stCrackCaptchaMode						crack_captcha_mode_;			//����ģʽ
	WORD									max_login_;						//��½�������
	std::string								stored_ip_;						//�ֿ������IP
	IoHelper								io_h_;
	int										role_max_cnt_;
	int										login_delay_;					//��½�ӳ�
};
BOOST_CLASS_VERSION(stSingletonCfg, 1)

//specific config
//�������ã���������default������
struct stSpecificCfg{
	//type definitions
public:
	//�ʺű���ֹ��ԭ��
	enum enProhibitReason{
		kPR_Valid = 0,			//û�б���ֹ������Ч
		kPR_RolesUseOut,		//��ɫˢ��
		kPR_BanAc,				//�ʺű���
		kPR_Restricted,			//������
	};
	//�ʺŽ�ֹ״̬
	struct stAcProState{
		stAcProState(){
			pro_reason_ = kPR_Valid;
		}
		void serialize( boost::archive::xml_oarchive& ar, const unsigned int var ){
			ar << boost::serialization::make_nvp("pro_reason_", pro_reason_)
				<< boost::serialization::make_nvp("pro_at_time_", 
				Poco::DateTimeFormatter::format(pro_at_time_, Poco::DateTimeFormat::SORTABLE_FORMAT));
		}
		void serialize( boost::archive::xml_iarchive& ar, const unsigned int var ){
			std::string str_pro_at_time;
			ar & boost::serialization::make_nvp("pro_reason_", pro_reason_)
				& boost::serialization::make_nvp("pro_at_time_", str_pro_at_time);
			int time_zone = 0;
			if ( !Poco::DateTimeParser::tryParse(Poco::DateTimeFormat::SORTABLE_FORMAT, str_pro_at_time, pro_at_time_, time_zone) )
			{
				assert(false);
				pro_at_time_ = Poco::DateTime(2000, 1, 1);
			}
		}

		enProhibitReason				pro_reason_;			//��ֹԭ��
		DateTimeLocal					pro_at_time_;			//��ֹʱ��
	};
	struct stRoleInfo{
		stRoleInfo(){
			ResetFatigueData();
		}
		stRoleInfo( const std::string& role_name, int fatigule_data );
		stRoleInfo( const std::string& role_name, const std::string& job );
		void serialize( boost::archive::xml_oarchive& ar, const unsigned int var ){
			ar << boost::serialization::make_nvp("role_info_.role_name_", role_info_.role_name_)
				<< boost::serialization::make_nvp("role_info_.role_job_", role_info_.role_job_)
				<< boost::serialization::make_nvp("fatigue_data_", fatigue_data_)
				<< boost::serialization::make_nvp("time", 
				Poco::DateTimeFormatter::format(the_time_, Poco::DateTimeFormat::SORTABLE_FORMAT));
		}
		void serialize( boost::archive::xml_iarchive& ar, const unsigned int var ){
			std::string str_pro_at_time;
			ar & BOOST_SERIALIZATION_NVP(role_info_.role_name_)
				& BOOST_SERIALIZATION_NVP(role_info_.role_job_)
				& BOOST_SERIALIZATION_NVP(fatigue_data_)
				& boost::serialization::make_nvp("time", str_pro_at_time);
			int time_zone = 0;
			if ( !Poco::DateTimeParser::tryParse(Poco::DateTimeFormat::SORTABLE_FORMAT, str_pro_at_time, the_time_, time_zone) )
			{
				assert(false);
				the_time_ = Poco::DateTime(2000, 1, 1);
			}
		}
		void RefreshTime();
		void SetFatigueData( int fatigue_data );
		void ResetFatigueData();

		CG_RoleInfo			role_info_;
		int					fatigue_data_;
		DateTimeLocal		the_time_;
	};
	typedef std::vector<stRoleInfo> RoleInfoContT;

public:
	template<class Archive>
	void serialize( Archive & ar, const unsigned int version ){
		ar & BOOST_SERIALIZATION_NVP(script_name_)
			//& BOOST_SERIALIZATION_NVP(game_service_)
			& BOOST_SERIALIZATION_NVP(auto_run_script_)
			& BOOST_SERIALIZATION_NVP(game_ac_type_)
			& BOOST_SERIALIZATION_NVP(ac_pro_state_)
			& BOOST_SERIALIZATION_NVP(roles_info_);
	}
	//����
	void Save( const char* file_name );
	//�ָ�
	void Restore( const char* file_name );
	//�����ʺű���
	void SaveAsAccount( const std::string& ac, int server_id );
	//�����ʺŻָ� 
	void RestoreAsAccount( const std::string& ac, int server_id );

	void SetRolesInfo( const CG_RoleInfo::RoleInfoContT& roles_info );
	void SetRoleFatigueData( const std::string& role_name, int fatigue_data );
	void SetRoleInfo( const std::string& role_name, const std::string& job );
	const stRoleInfo* FindRoleInfoByName( const std::string& role_name ) const;
	stRoleInfo* FindRoleInfoByName( const std::string& role_name );
	const stRoleInfo* FindFirstFatigueValidRole();
	int RoleInfo2Index( const stRoleInfo* role_info ) const;
	void ResetAllFatigueData();
	bool CanCreateNewRole() const;
	//�Ƿ���ָ��������
	static bool HasSpecificCfg( const std::string& ac, int server_id );

private:
	static int ServerIdx2Suffix( int server_id );

public:
	enum{
		Version = 1
	};

public:
	std::string				script_name_;			//Ĭ�Ͻű���
	//std::string				game_service_;			//��Ϸ������
	bool					auto_run_script_;		//��½�����Ƿ��Զ����нű�
	enGameAcType			game_ac_type_;			//��Ϸ�ŵ�����
	stAcProState			ac_pro_state_;			//��Ϸ�ʺŵĽ�ֹ״̬
	RoleInfoContT			roles_info_;			//��ɫ��Ϣ
};
BOOST_CLASS_VERSION(stSpecificCfg, stSpecificCfg::Version)

//default.xml
struct stDefaultCfg : public stSpecificCfg
{
private:
	stDefaultCfg();
	using stSpecificCfg::Restore;

public:
	//Ψһʵ��
	static stDefaultCfg& GetMe();
	//����
	void Save();
};
BOOST_CLASS_VERSION(stDefaultCfg, stDefaultCfg::Version)

class AcIniCfgMgr{
public:
	//�ʺ�.ini�ļ�
	struct stAcIniCfg{
		stAcIniCfg();
		bool Read( std::size_t setion_idx, LPCTSTR full_file_name );
		bool Write( std::size_t setion_idx, LPCTSTR full_file_name ) const;
		bool ReadLine( const std::string& str_line );
		bool WriteLine( std::string& str_line ) const;

		CString				ac_;
		CString				pwd_;
		CString				service_name_;
	};

	typedef std::vector<stAcIniCfg> ContT;

public:
	const ContT& GetCont() const;
	virtual bool Load( const CPath& full_file_name );
	virtual bool Save( const CPath& full_file_name );
	void Add( const CString& ac, const CString& pwd, const CString& service_name );

protected:
	ContT			cfg_;
};

//�µĸ�ʽ
class AcIniCfgMgr_New : public AcIniCfgMgr{
public:
	virtual bool Load( const CPath& full_file_name );
	virtual bool Save( const CPath& full_file_name );
};