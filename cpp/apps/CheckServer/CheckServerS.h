#pragma once
/*
@author zhp
@date 2014/4/21 17:03
@purpose for check server server and session
*/
#include "Net/server.h"
#include "Common/UsefulClass.h"
#include "Net/JsonCall.h"
#include "DataHandlerS.h"
#include "Net/IoTimer.h"
#include <boost/optional.hpp>
#include <set>
#include <functional>
#include <Net/CmnLogin.h>

class Session_CS;
class CheckServer : public Server_Aes_Rsa, public Singleton<CheckServer, Singleton_Instance>{
public:
	CheckServer( DbSingleton::SelfPtr& db_singleton, WORD self_listen_port );
	typedef boost::shared_ptr<CheckServer> SelfPtr;
	typedef std::set<session_ptr> SessionsT;

	//interface
public:
	void DoItem( const std::function<void(Session_CS&)>& func );
	void SessionTimeout();

private:
	bool OnConnected( IoConnectBase* connect );
	void OnDisconnect( IoConnectBase* connect );
	virtual Session* CreateSession();

private:
	DbSingleton::SelfPtr	db_singleton_;
	SessionsT				sessions_;
};

class UserOperS : public BufCall_Socket, public ICmnLoginGrantSink{
public:
	UserOperS( Session_CS& session );
	~UserOperS();

	//�û�����
public:
	//��½
	bool Login(pt_bool is_only_login, const stCheckLoginInfo<pt_csz>& login_info, pt_int ver);
	//���
	bool RemoveBind( pt_csz user_name, pt_csz user_pwd, pt_csz machine_code );
	//ע���û�
	bool RegUser( pt_csz user_name, pt_csz user_pwd, pt_csz str_qq, pt_csz reg_key_id );
	//�û�֧��
	bool UserPay( pt_csz user_name, pt_csz card_id, pt_csz card_pwd );
	//����
	bool LeaveMsg( pt_csz msg );
	//��֤��½
	bool CheckLogin(const CheckLoginInfoContT<pt_csz>& login_infos);

	//Ȩ�޹���
public:
	//���
	bool Grant_RemoveBind( pt_csz user_name_dst );
	//����
	bool Grant_OpenCard(pt_word card_cnt, pt_dword card_minutes, pt_qword grant, pt_dword ac_type);
	//����ע����
	bool Grant_GenRegKey(pt_word reg_key_cnt, pt_dword ac_type);
	//ͨ�����Ų�ѯ�ʺ���Ϣ
	bool Grant_PeerAcByCard( pt_csz card_id, pt_csz card_pwd );
	//ͨ���ʺŲ�ѯ������Ϣ
	bool Grant_PeerCardByAc( pt_csz ac, pt_csz ac_pwd );
	//��ѯ�ʺ���Ϣ
	bool Grant_PeerAcInfo( pt_csz ac, pt_csz ac_pwd );
	//��ѯ������Ϣ
	bool Grant_PeerCardInfo( pt_csz card_id, pt_csz card_pwd );
	//֧���ع�
	bool Grant_RollbackPay( pt_csz card_id, pt_csz card_pwd, bool direction );
	//����addr data
	bool Grant_SetAddrData( pt_int id, pt_dword addr_data );
	//����str data
	bool Grant_SetStrData( pt_int id, pt_csz str_data );
	//�����ʺ�״̬
	bool Grant_SetAcState(pt_csz user_name_dst, enAcState ac_state, Poco::UInt32 period);

private:
	//��Ӧ��½
	bool OnLoginRes(bool res, pt_csz info, pt_csz ac_pwd_machine_mix, pt_csz new_cookie, 
		const TimeT& end_day_time, const TimeT& ser_cur_time, const AddrDatasT& addr_datas, 
		const StrDatasT& str_addr_datas, pt_dword ac_type) override;
	//��Ӧ���
	bool OnRemoveBind( bool res, pt_csz info ) override;
	//��Ӧע��
	bool OnRegUser( bool res, pt_csz info ) override;
	//��Ӧ֧��
	bool OnUserPay( bool res, pt_csz info ) override;
	//��Ӧ����
	bool OnLeaveMsg( bool res, pt_csz info ) override;
	//��Ӧ��֤��½
	bool OnCheckLogin(const CheckLoginResContT& res_info) override;

private:
	bool OnGrant_RemoveBind( bool res, pt_csz info ) override;
	bool OnGrant_OpenCard( bool res, pt_csz info, const CardInfoT& card_info ) override;
	bool OnGrant_GenRegKey( bool res, pt_csz info, const RegKeyInfoT& reg_key ) override;
	bool OnGrant_PeerAcByCard(bool res, pt_csz info, const stData_Account::AcContT& ac_info, const stData_AcState::ContT& ac_state) override;
	bool OnGrant_PeerCardByAc(bool res, pt_csz info, const stData_Card::CardContT& card_info) override;
	bool OnGrant_PeerAcInfo(bool res, pt_csz info, const stData_Account::AcContT& ac_info, const stData_AcState::ContT& ac_state) override;
	bool OnGrant_PeerCardInfo(bool res, pt_csz info, const stData_Card::CardContT& card_info) override;
	bool OnGrant_RollbackPay( bool res, pt_csz info ) override;
	bool OnGrant_SetAddrData( bool res, pt_csz info ) override;
	bool OnGrant_SetStrData( bool res, pt_csz info ) override;
	bool OnGrant_SetAcState(bool res, pt_csz info) override;

private:
	Session_CS&				session_;

	BC_REG_CLS_DECLARE(UserOperS);
};

class Session_CS : public Session_Rsa{
	friend class UserOperS;

public:
	Session_CS( CheckServer& server );
	~Session_CS();

	//interface
public:
	//����single���ݿ�
	void SetSingleDb( DbSingleton::SelfPtr& db_singleton );
	const std::string& GetLoginUserName() const;
	bool IsTimeout( const DateTimeLocal& time_now ) const;

private:
	//��Ծ�Ự
	void ActiveSessionTime();

private:
	bool OnConnected( IoConnectBase* connect );
	void OnDisconnect( IoConnectBase* connect );

private:
	UserOperS				user_oper_;
	DateTimeLocal			active_time_;

private:
	DbSingleton::SelfPtr	db_singleton_;

private:
	std::string				user_name_;			//�û���
};