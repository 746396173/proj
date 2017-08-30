#pragma once
/*
@author zhp
@date 2014/4/24 16:32
@purpose for table data handle
*/
#include <Net/DbData.h>
#include <vector>
#include "Protocol/P_Defines.h"
#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>
#include <Common/MakeSecret.h>
#include <Common/Database.h>
//////////////////////////////////////////////////////////////////////////
//*******************db_singleton table handlers**************************
//tbl_Account
class DataH_Account : public DataTblBase{
public:
	DataH_Account( DatabaseMgrBase& db_mgr );

	//�ӿ�
public:
	stData_Account* FindUser( const std::string& user_name );
	const stData_Account* FindUser( const std::string& user_name ) const;
	//����û�
	bool AddUser(const std::string& user_name, const std::string& user_pwd, const std::string& str_qq,
		const std::string& str_reg_ip, pt_dword ac_type, std::string& out_info);
	//��½��Ϣ
	bool UpdateLoginInfo(const std::string& user_name, const std::string& login_ip, std::string& cookie, DateTimeLocal& cookie_end_time);
	//֧����ʱ��
	bool Pay( const std::string& user_name, Poco::UInt32 minutes_addition, std::string& out_info );
	//���µ���ʱ��
	bool UpdateEndDayTime( const std::string& user_name, const DateTimeLocal& new_end_day_time, std::string& out_info );
	//ȥ��������
	bool RemoveMachineCode( const std::string& user_name, int minus_minutes );
	//���»�����
	bool UpdateMachineCode( const std::string& user_name, const std::string& new_machine_code );
	//�õ�ʹ������
	bool GetEndDateTime( const std::string& user_name, DateTimeLocal& end_date_time ) const;
	//����cookie
	bool UpdateCookie(const std::string& user_name, std::string& cookie, DateTimeLocal& cookie_end_time);

	IMPL_DATA_OPER(stData_Account);
};

//tbl_Card
class DataH_Card : public DataTblBase{
public:
	DataH_Card( DatabaseMgrBase& db_mgr );

	//type definition
public:
	//����Ϣ��first==card id,second==card pwd
	typedef std::pair<std::string, std::string> CardInfo;
	typedef std::vector<CardInfo> CardsInfoT;

	//interface
public:
	//����ָ���Ŀ�
	stData_Card* FindCard( const std::string& card_id );
	//���ӿ�
	bool AddCard( const std::string& add_user, const std::string& card_id, const std::string& card_pwd,
		Poco::UInt32 card_minutes, Poco::UInt64 grant, pt_dword ac_type, std::string& info);
	//ʹ��
	bool Use( const std::string& user_name, const std::string& card_id, const std::string& card_pwd, Poco::UInt32* card_minutes,
		std::string& out_info );
	void DoItem( const std::function<void(const stData_Card&)>& func ) const;

	IMPL_DATA_OPER(stData_Card);
};

//tbl_AcState
class DataH_AcState : public DataTblBase{
public:
	DataH_AcState(DatabaseMgrBase& db_mgr);

	//interface
public:
	stData_AcState* FindState(const std::string& user_name);
	bool SetState(const std::string& user_name, enAcState state, Poco::UInt32 period);
	bool CanLogin(const std::string& user_name, std::string* out_info);

	IMPL_DATA_OPER(stData_AcState);
};

//tbl_MsgBoard
class DataH_MsgBoard : public DataTblBase{
public:
	DataH_MsgBoard( DatabaseMgrBase& db_mgr );
	//���һ������
	bool AddLeaveMsg( const std::string& msg, const std::string& user_name, std::string& out_info );
	//�õ�ĳ����������
	std::size_t GetUserMsgTotalCnt( const std::string& user_name ) const;
	//�õ�����ĳ����������
	std::size_t GetUserMsgCntToday( const std::string& user_name ) const;

private:
	//�õ�һ��δ��ʹ�õ�id
	Poco::UInt32 GetFreeId() const;

	IMPL_DATA_OPER(stData_MsgBoard);
};

//tbl_UserGrant
class DataH_UserGrant : public DataTblBase{
public:
	DataH_UserGrant( DatabaseMgrBase& db_mgr );
	//�Ƿ����ĳ��Ȩ��
	bool HasTheGrant( const std::string& user_ac, enUserGrant user_grant );
	//�õ��û�Ȩ��
	enUserGrant GetUserGrant( const std::string& user_ac );
	stData_UserGrant* FindUserGrant( const std::string& user_ac );
	//Ȩ�ޱȽϣ�С��
	bool LessGrant( const std::string& lhs, const std::string& rhs );
	//Ȩ�ޱȽϣ�С�ڵ���
	bool LessEqGrant( const std::string& lhs, const std::string& rhs );
	//���Ȩ��
	bool AddGrant( const std::string& user_ac, enUserGrant grant );

	IMPL_DATA_OPER(stData_UserGrant);
};

//tbl_RegKey
class DataH_RegKey : public DataTblBase{
public:
	typedef std::vector<std::string> RegKeysInfoT;

public:
	DataH_RegKey( DatabaseMgrBase& db_mgr );
	stData_RegKey* FindRegKey( const std::string& reg_key_id );
	//����ע����
	bool AddRegKey(const std::string& add_user, const std::string& reg_key_id, pt_dword ac_type);
	//ʹ��ע����
	bool TryUse(const std::string& reg_key_id, pt_dword& ac_type, std::string& out_info);
	bool Use( const std::string& user_name, const std::string& reg_key_id, std::string& out_info );

	IMPL_DATA_OPER(stData_RegKey);
};
//////////////////////////////////////////////////////////////////////////
//tbl_AddrData
class DataH_AddrData : public DataTblBase{
	//type definition
public:
	typedef std::vector<std::string> EncryptAddrDataT;

public:
	DataH_AddrData( DatabaseMgrBase& db_mgr );

public:
	//�õ���������
	bool GetEncrytAddrData( ISecretMaker* secret_maker, EncryptAddrDataT& encrypt_data );
	//��������
	void OrderById();
	bool SetAddrData( Poco::UInt32 id, Poco::UInt32 addr_data );

	IMPL_DATA_OPER(stData_AddrData);

	DataType* FindById( Poco::UInt32 id );
};

//tbl_StrData
class DataH_StrData : public DataTblBase{
	//type definition
public:

public:
	DataH_StrData( DatabaseMgrBase& db_mgr );

public:
	bool GetAllStrData( std::vector<std::string>& all_datas );
	//��������
	void OrderById();
	bool SetStrData( Poco::UInt32 id, std::string str_data );

	IMPL_DATA_OPER(stData_StrData);

	DataType* FindById( Poco::UInt32 id );
};
//////////////////////////////////////////////////////////////////////////

//db_singleton
class DbSingleton : public DatabaseMgrBase{
	//type definition
public:
	typedef boost::shared_ptr<DbSingleton> SelfPtr;

public:
	DbSingleton( const std::string& server_ip, WORD ip_port, const std::string& db_name );

	//����
public:
	//��½
	bool Login(const std::string& user_name, const std::string& user_pwd, const std::string& machine_code, 
		pt_csz str_mix_p, const std::string& str_cookie, std::string* new_cookie, const std::string* login_ip, 
		std::string* out_info, pt_dword& ac_type);
	//���
	bool RemoveBind( const std::string& user_name, const std::string& user_pwd, const std::string& machine_code, int minus_minutes,
		std::string& out_info );
	//ע���û�
	bool RegUser( const std::string& user_name, const std::string& user_pwd, const std::string& str_qq,
		const std::string& str_reg_ip, const std::string& reg_key_id, std::string& out_info );
	//�û�֧��
	bool UserPay( const std::string& user_name, const std::string& card_id, const std::string& card_pwd, std::string& out_info );
	//�û�����
	bool UserLeaveMsg( const std::string& msg, const std::string& user_name, std::string& out_info );

	//Ȩ�޹���
public:
	//���
	bool Grant_RemoveBind( const std::string& user_name_src, const std::string& user_name_dst, int minus_minutes,
		std::string& out_info );
	//����
	bool Grant_OpenCard(const std::string& add_user, Poco::UInt16 card_cnt, Poco::UInt32 card_minutes, pt_dword ac_type,
		DataH_Card::CardsInfoT* cards_info, Poco::UInt64 grant, std::string& out_info);
	//����ע����
	bool Grant_GenRegKey(const std::string& add_user, Poco::UInt16 reg_key_cnt, 
		pt_dword ac_type, DataH_RegKey::RegKeysInfoT* reg_keys, std::string& out_info);
	//���ݿ��Ų�ѯ�ʺ���Ϣ
	bool Grant_PeerAcByCard( const std::string& user_name, const std::string& card_id, const std::string& card_pwd, stData_Account::AcContT& ac_cont, std::string& out_info );
	//�����ʺŲ�ѯ������Ϣ
	bool Grant_PeerCardByAc( const std::string& user_name, const std::string& ac, const std::string& ac_pwd, stData_Card::CardContT& card_cont, std::string& out_info );
	//��ѯ�ʺ���Ϣ
	bool Grant_PeerAcInfo( const std::string& user_name, const std::string& ac, const std::string& ac_pwd, stData_Account::AcContT& ac_cont, std::string& out_info );
	//��ѯ������Ϣ
	bool Grant_PeerCardInfo( const std::string& user_name, const std::string& card_id, const std::string& card_pwd, stData_Card::CardContT& card_cont, std::string& out_info );
	//֧���ع�
	bool Grant_RollbackPay( const std::string& user_name, const std::string& card_id, const std::string& card_pwd, bool direction, std::string& out_info );
	//����addr data
	bool Grant_SetAddrData(Poco::UInt32 id, Poco::UInt32 addr_data, std::string& info);
	//����str data
	bool Grant_SetStrData(Poco::UInt32 id, const std::string& str_data, std::string& info);
	//�����ʺ�״̬
	bool Grant_SetAcState(const std::string& user_name_src, const std::string& user_name_dst, enAcState ac_state, Poco::UInt32 period, std::string& out_info);

	//another
public:
	//addr data,�������ݵ�
	bool GetAddrDatas(std::string& str_key, DataH_AddrData::EncryptAddrDataT& out_data);
	//string data,�ַ������ݵ�
	bool GetStrDatas(std::vector<std::string>& the_data);
	//�õ��ʺ�״̬
	bool GetAcStates(const stData_Account::AcContT& ac_cont, stData_AcState::ContT& ac_states);

public:
	//�ָ����еı�
	bool SelectAllTblData();
	void OnReconnected() override;

	//get tables
public:
	const DataH_Account& GetTbl_Account() const;
	const DataH_Card& GetTbl_Card() const;
	DataH_UserGrant& GetTbl_UserGrant();
	const DataH_RegKey& GetTbl_RegKey() const;

	//���ߺ���
private:
	//���ɿ���Ϣ
	void GenCardInfo( std::string& card_id, std::string& card_pwd );
	//����ע������Ϣ
	void GenRegKeyInfo( std::string& reg_key );

	//tables
private:
	DataH_Account				tbl_account_;
	DataH_Card					tbl_card_;
	DataH_UserGrant				tbl_user_grant_;
	DataH_RegKey				tbl_reg_key_;
	DataH_MsgBoard				tbl_msg_board_;
	DataH_AddrData				tbl_addr_data_;
	DataH_StrData				tbl_str_data_;
	DataH_AcState				tbl_ac_state_;

private:
	static const Poco::Timespan cookie_time_span;
};
