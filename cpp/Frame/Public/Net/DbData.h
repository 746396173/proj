#pragma once
/*
@author zhp
@date 2014/4/22 14:37
@purpose for database data
*/
#include <string>
#include "PocoMore.h"
#include <Protocol/P_Defines.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////
//tbl_Account
struct stData_Account{
	typedef std::vector<stData_Account> AcContT;
	stData_Account(){
		ac_type_ = 0;
	}
	template<class Archive>
	void serialize(Archive & ar){
		ar & user_name_
			& user_pwd_
			& machine_code_
			& last_login_time_
			& last_pay_time_
			& last_login_ip_
			& reg_time_
			& end_day_time_
			& qq_
			& reg_ip_
			& cookie_
			& cookie_end_time_
			& ac_type_;
	}

	std::string				user_name_;					//�û���
	std::string				user_pwd_;					//�û�����
	std::string				machine_code_;				//������
	DateTimeLocal			last_login_time_;			//����½ʱ��
	DateTimeLocal			last_pay_time_;				//���֧��ʱ��
	std::string				last_login_ip_;				//����½ʱ��
	DateTimeLocal			reg_time_;					//ע��ʱ��
	DateTimeLocal			end_day_time_;				//�û���ֹʱ��
	std::string				qq_;						//qq����
	std::string				reg_ip_;					//ע��ʱ��IP
	std::string				cookie_;					//cookie
	DateTimeLocal			cookie_end_time_;			//cookie��ֹʱ��
	Poco::UInt32			ac_type_;					//�ʺ�����
};

//tbl_Card
struct stData_Card{
	typedef std::vector<stData_Card> CardContT;
	stData_Card(){
		card_minutes_ = 0;
		is_used_ = false;
		ac_type_ = 0;
	}
	template<class Archive>
	void serialize(Archive & ar){
		ar & card_id_
			& card_pwd_
			& use_time_
			& add_time_
			& add_user_
			& is_used_
			& user_name_
			& card_minutes_
			& grant_
			& ac_type_;
	}

	std::string				card_id_;					//����
	std::string				card_pwd_;					//������
	DateTimeLocal			use_time_;					//ʹ��ʱ��
	DateTimeLocal			add_time_;					//��ӵ�ʱ��
	std::string				add_user_;					//�����
	bool					is_used_;					//�Ƿ�ʹ��
	std::string				user_name_;					//ʹ����
	Poco::UInt32			card_minutes_;				//�����ӵ�ʱ��,��λ->����
	Poco::UInt64			grant_;						//����Ȩ��
	Poco::UInt32			ac_type_;					//�ʺ�����
};

struct stData_AcState{
	typedef std::vector<stData_AcState> ContT;
	stData_AcState(){
		state_ = enAcState::kAS_Normal;
		last_state_ = state_;
		period_ = 0;
	}
	template<class Archive>
	void serialize(Archive & ar){
		ar & user_name_
			& state_
			& last_state_
			& begin_time_
			& end_time_
			& period_;
	}

	std::string				user_name_;
	enAcState				state_;				//�ʺ�״̬��enAcState
	enAcState				last_state_;		//�ϴ�״̬
	DateTimeLocal			begin_time_;		//��ʼ״̬��ʱ��
	DateTimeLocal			end_time_;			//����״̬��ʱ��
	Poco::UInt32			period_;			//״̬����ʱ�䣬��λ������
};

//tbl_MsgBoard
struct stData_MsgBoard{
	stData_MsgBoard(){
		id_ = 0;
	}
	template<class Archive>
	void serialize(Archive & ar){
		ar & id_
			& msg_
			& user_name_
			& add_time_;
	}

	Poco::UInt32			id_;						//���԰���Ϣ��
	std::string				msg_;						//������Ϣ
	std::string				user_name_;					//������
	DateTimeLocal			add_time_;					//����ʱ��
};

//tbl_UserGrant
struct stData_UserGrant{
	stData_UserGrant(){
		user_grant_ = kUG_No;
	}
	template<class Archive>
	void serialize(Archive & ar){
		ar & user_name_
			& user_grant_;
	}

	//set
	void SetUserGrant( enUserGrant user_grant );
	enUserGrant GetUserGrant() const;
	bool operator < ( const stData_UserGrant& rhs );

	std::string				user_name_;
	enUserGrant				user_grant_;				//�û�Ȩ��,enUserGrant
};

//tbl_RegKey
struct stData_RegKey{
	stData_RegKey(){
		is_used_ = false;
		ac_type_ = 0;
	}
	template<class Archive>
	void serialize(Archive & ar){
		ar & reg_key_id_
			& add_time_
			& add_user_
			& is_used_
			& user_name_
			& use_time_
			& ac_type_;
	}

	std::string				reg_key_id_;
	DateTimeLocal			add_time_;
	std::string				add_user_;
	bool					is_used_;
	std::string				user_name_;
	DateTimeLocal			use_time_;
	Poco::UInt32			ac_type_;					//�ʺ�����
};

//tbl_AddrData
struct stData_AddrData{
	stData_AddrData(){
		id_ = 0;
		addr_data_ = 0;
	}
	template<class Archive>
	void serialize(Archive & ar){
		ar & id_
			& addr_data_;
	}

	Poco::UInt32			id_;						//�ؼ���ַ����id
	Poco::UInt32			addr_data_;					//�ؼ���ַ
};

//tbl_StrData
struct stData_StrData{
	stData_StrData(){
		id_ = 0;
	}
	template<class Archive>
	void serialize(Archive & ar){
		ar & id_
			& str_data_;
	}

	Poco::UInt32			id_;						//�ؼ���ַ����id
	std::string				str_data_;					//�ؼ���ַ
};

//////////////////////////////////////////////////////////////////////////