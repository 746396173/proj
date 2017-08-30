#pragma once
/*
@author zhp
@date 2014/4/28 0:08
@purpose for check and login
*/
#include "Script/JsonCall.h"
#include "socket/client.h"
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <Poco/Types.h>

class CheckLoginC;
class CheckLoginOperC : public JsonEchoVmp{
public:
	CheckLoginOperC( CheckLoginC& check_login );

	//�û�����
public:
	//��½
	void Login( const std::string& user_name, const std::string& user_pwd );
	//���
	void RemoveBind( const std::string& user_name, const std::string& user_pwd, const std::string& machine_code );
	//ע��
	void RegUser( const std::string& user_name, const std::string& user_pwd, const std::string& str_qq, const std::string& reg_key_id );
	//��ֵ
	void Pay( const std::string& user_name, const std::string& card_id, const std::string& card_pwd );
	//�õ��ؼ�����
	void GetAddrDatas();
	//��֤��½
	static void CheckLogin( const std::string& user_name, const std::string& user_pwd );
	//����
	std::string LeaveMsg( const std::string& msg );
	//�õ�������
	static std::string GetMachineCode();

	//�û��������
public:
	//��Ӧ��½
	void OnLoginAcInfo( const std::string& ac_pwd );
	//��Ӧ���
	void OnRemoveBind( bool succeed );
	//��Ӧע��
	void OnRegUser( bool succeed );
	//��Ӧ֧��
	void OnUserPay( bool succeed );
	//CheckLogin result
	void OnCheckLoginResult( int res_reson );

	//������Ϣ
public:
	//��½��Ϣ
	void OnLoginInfo( const std::string& info );
	//�����Ϣ
	void OnRemoveBindInfo( const std::string& info );
	//ע����Ϣ
	void OnRegUserInfo( const std::string& info );
	//֧����Ϣ
	void OnUserPayInfo( const std::string& info );
	//���չؼ�����
	void OnRecvAddrDatas( const std::string& str_key, const Json::Value& addr_datas );

	//��������
public:
	//��ֹʱ��
	void OnUserEndTime( Poco::UInt32 timestamp_lower, Poco::UInt32 timestamp_upper );

protected:
	virtual bool OnThisMemCall( const stThisCallHelper& helper );

private:
	CheckLoginC&				check_login_;
};

class CheckLoginC : public Con_Aes_Rsa{
	friend class CheckLoginOperC;
public:
	typedef boost::shared_ptr<CheckLoginC> SelfPtr;
	typedef boost::weak_ptr<CheckLoginC> WeakPtr;

public:
	CheckLoginC( const std::string& check_server_ip, const CryptoStrCompose::SubCryptoT& stm_pub, 
		const CryptoStrCompose::SubCryptoT& stm_pri );
	//��½�ɹ���������
	static bool AfterLoginSucced( const std::function<void( SelfPtr& conne_self )>& func );

	//interface
public:
	CheckLoginOperC& GetUserOper();
	static SelfPtr GetSelfPtr();
	void OnDisconnect( IoConnectBase* connect );
	
protected:
	bool OnConnected( IoConnectBase* connect );
	virtual void OnConnectFailed();

private:
	CheckLoginOperC				check_server_oper_;

private:
	boost::optional<bool>		login_res_;
	boost::optional<bool>		remove_bind_;
	boost::optional<bool>		reg_user_;
	boost::optional<bool>		user_pay_;
};