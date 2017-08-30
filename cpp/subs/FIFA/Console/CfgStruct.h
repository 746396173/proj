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
#include <Net/PocoMore.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeParser.h>
#include "GLuaS.h"
#include <Communicate/CG_Defines.h>
#include <Communicate/CGL_Defines.h>
#include <Net/CmnLoginInfo.h>
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
struct stSingletonCfg : CmnLoginInfoMgr<ConnectCntInfo>{
protected:
	stSingletonCfg( const std::string& str_cfg_full_path ) : stored_ip_(kSelfIpStr){
		max_login_ = 15;
		auto_save_ep_ = false;
		run_at_12_ = false;
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
			& BOOST_SERIALIZATION_NVP(ep_file_path_)
			& BOOST_SERIALIZATION_NVP(auto_save_ep_)
			& BOOST_SERIALIZATION_NVP(run_at_12_)
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
		friend bool operator == ( const AccountType& lhs, const AccountType& rhs ){
			return lhs.first == rhs.first && lhs.second == rhs.second && lhs.service_name_ == rhs.service_name_;
		}

		CString					service_name_;
	};
	typedef std::vector<AccountType> AcountContT;

public:
	//Ψһʵ��
	static stSingletonCfg& GetMe();

public:
	void DoCloseTheSession(const BindAcInfoT& the_clr_ac) override;

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
	CString									ep_file_path_;
	bool									auto_save_ep_;
	bool									run_at_12_;						//12���Զ�����
};
BOOST_CLASS_VERSION(stSingletonCfg, 1)

//specific config
//�������ã���������default������
struct stSpecificCfg
{
	//type definitions
public:
	//�ʺű���ֹ��ԭ��
	enum enProhibitReason{
		kPR_Valid = 0,			//û�б���ֹ������Ч
		kPR_51End,				//51������
		kPR_BanAc,				//�ʺű���
		kPR_AcFreeze,			//�ʺű�����
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

public:
	template<class Archive>
	void serialize( Archive & ar, const unsigned int version ){
		ar & BOOST_SERIALIZATION_NVP(script_name_)
			//& BOOST_SERIALIZATION_NVP(game_service_)
			& BOOST_SERIALIZATION_NVP(auto_run_script_)
			& BOOST_SERIALIZATION_NVP(game_ac_type_)
			& BOOST_SERIALIZATION_NVP(ac_pro_state_);
	}
	//����
	void Save( const char* file_name );
	//�ָ�
	void Restore( const char* file_name );
	//�����ʺű���
	void SaveAsAccount( const std::string& ac, int suffix );
	//�����ʺŻָ� 
	void RestoreAsAccount( const std::string& ac, int suffix );

	//�Ƿ���ָ��������
	static bool HasSpecificCfg( const std::string& ac, int suffix );

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
		int					ep_;
	};

	typedef std::vector<stAcIniCfg> ContT;

public:
	const ContT& GetCont() const;
	virtual bool Load( const CPath& full_file_name );
	virtual bool Save( const CPath& full_file_name );
	void Add( const CString& ac, const CString& pwd, const CString& service_name, int ep );

protected:
	ContT			cfg_;
};

//�µĸ�ʽ
class AcIniCfgMgr_New : public AcIniCfgMgr{
public:
	virtual bool Load( const CPath& full_file_name );
	virtual bool Save( const CPath& full_file_name );
};