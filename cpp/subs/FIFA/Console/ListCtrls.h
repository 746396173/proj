#pragma once
#include "stdafx.h"
#include <stack>
#include "FuncObjS.h"
#include "CfgStruct.h"
#include <list>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <stddef.h>
#include <functional>
#include "Common/UsefulClass.h"
#include <Net/JsonCall.h>
#include <Poco/DateTime.h>
#include <Net/IoTimer.h>
#include <Net/PocoMore.h>

//subitem index
enum enListSubItems{
	kSubitemAccount = 0,
	kSubitemPassword,
	kSubitemService,			//������
	kSubitemRunState,			//����״̬
	kSubitemGameAcType,			//�ŵ�����
	kSubitemAutoRunScript,		//�Զ����нű�
	kSubitemDiscoverGoodPlayer,	//�߼�ֵ��Ա
	kSubitemTrainerName,		//������
	kSubitemTrainerLevel,		//�����ȼ�
	kSubitemMatchCnt,			//��������
	kSubitemCurEP,				//��ǰEP
	kSubitemCurScript,			//��ǰ�ű�
	kSubitemGainedEP,			//��õ�EP
	kSubitemSpid,				//��ԱID
	kSubitemOutRes,				//������
	kSubitemScriptOutputInfo,	//�ű������Ϣ
	kSubitemLastNotifyTime,		//���ͨ��ʱ��
};

//for login
struct LoginHelper{
	int							item_;
	DWORD						login_process_id_;				//��½������id
	bool						is_logining_;					//�Ƿ����ڵ�½
	boost::weak_ptr<Session>	session_login_;					//��½�Ự
	IoTimerPtr					timer_login_;					//��ʼ��½��ʱ��

public:
	//�ͷŵ�½��ʱ
	void FreeLoginTimer();

public:
	LoginHelper();
	struct tagItem{};
	struct tagLoginProcessId{};
	//struct tagSessionLogin{};
};
typedef boost::multi_index_container<
	LoginHelper, boost::multi_index::indexed_by<
	boost::multi_index::ordered_unique<boost::multi_index::tag<LoginHelper::tagItem>, 
	BOOST_MULTI_INDEX_MEMBER(LoginHelper, decltype(LoginHelper::item_), item_) >,
	boost::multi_index::ordered_non_unique<boost::multi_index::tag<LoginHelper::tagLoginProcessId>, 
	BOOST_MULTI_INDEX_MEMBER(LoginHelper, decltype(LoginHelper::login_process_id_), login_process_id_) >/*,
	boost::multi_index::ordered_non_unique<boost::multi_index::tag<LoginHelper::tagSessionLogin>, 
	BOOST_MULTI_INDEX_MEMBER(LoginHelper, decltype(LoginHelper::session_login_), session_login_) >*/
	> > LoginHelperContT;

//��Ϸ������
class GameServiceMgr : public Singleton<GameServiceMgr, Singleton_Instance>{
	//type definition
public:
	typedef std::pair<std::string, DWORD> ServiceInfoT;
	typedef std::vector<ServiceInfoT> ContT;

public:
	GameServiceMgr();
	//�õ�������ID
	DWORD GetServiceId( const std::string& service_name ) const;
	//�õ���Ϸ��������Ϣ
	const ContT& GetServicesInfo() const;
	//�õ�����������
	int GetServiceIdx( const std::string& service_name ) const;

private:
	ContT				services_info_;
};

class ListNormal : public CListCtrl{
//type definitions
public:
	//��ֹ��,��Ϸ�ʺţ���Ϸ����ԭ��
	struct stProhibitAc : public std::pair<std::string, std::string>{
		stSpecificCfg::enProhibitReason				prohibit_reason_;				//�ʺű���ֹ��ԭ��
	};
	typedef std::set<stProhibitAc> ProhibitT;

public:
	ListNormal();

public:
	void StartItemScript( int item );
	void StopItemScript( int item );
	void Delete_Item( int item );
	//ɾ�������ʺ�
	void DeleteAllItems();
	void Insert_Item( LPCTSTR account, LPCTSTR password, LPCTSTR service_name );
	//�ر���Ϸ����
	bool CloseGameProcess( int item );
	//�õ�һ�����е���Ч��
	int GetFreeItem();
	//���÷�����
	bool SetItemService( int item, LPCTSTR service_name );
	//do item
	bool DoItem( const std::function<bool(int, const ListNormal&)>& func );
	//do item func obj
	void DoItemFuncObj( const std::function<void(FuncObj_NormalS&)>& func );

public:
	int FindItemByAccount( LPCTSTR account, LPCTSTR service_name ) const;
	int FindItemByAccount( const std::string& game_ac, const std::string& game_ser_name ) const;
	//����item func obj
	void SetItemFuncObj( int item, FuncObj_NormalS* func_obj );
	//�õ�item func obj
	FuncObj* GetItemFuncObj( int item );
	FuncObj_NormalS* GetNormalS( LPCTSTR account );
	FuncObj_NormalS* GetNormalS( LPCTSTR ac, LPCTSTR service_name );
	FuncObj_NormalS* GetNormalS( int item );
	FuncObj_NormalS* GetNormalS( const std::string& game_ac, int ser_idx );
	void FreeItemByFuncObj( FuncObj& func_obj, const CString& str_run_state );
	int FindItemByFuncObj( FuncObj& func_obj );
	CString GetItemAccount( int item ) const;
	//�õ���������
	CString GetItemServiceName( int item ) const;
	//�õ���������
	int GetItemServiceIdx( int item ) const;
	int GetItemServiceIdx( const std::string& ac, const std::string& service_name ) const;
	//game ac type
	enGameAcType GetItemGameAcType( int item );
	//��������
	int AcceptSession( DWORD client_proccess_id );
	//�����Ƿ��Զ����нű�
	void SetAutoRunScript( int item, bool auto_run_script );
	//����ָ���ĵ�½����
	LoginHelper* FindLoginHelperBySession( Session* login_session );
	LoginHelper* FindLoginHelperByPid( DWORD pid );
	//ɾ��ָ���ĵ�½����
	void EraseLoginHelperBySession( Session* login_session );
	void EraseLoginHelper( LoginHelper* login_hlp );
	//�õ�δ����ֹ��item��
	int GetNoProhibitItem( const std::string& user_ac, const std::string& service_name );
	//���ӽ�ֹ��½��
	void AddProhibitItem( const std::string& user_ac, const std::string& service_name, stSpecificCfg::enProhibitReason reason );
	//ɾ����ֹ��½��
	void RemoveProhibitItem( const std::string& user_ac, const std::string& game_service );
	void RemoveProhibitItem( int item );
	//����һ����ֹ��
	ProhibitT::iterator FindProhibitIter( const std::string& user_ac, const std::string& game_service );
	//���51����ֹ��
	void ClearProhibit_51();
	//Ч��֤����
	bool CheckSamePwd( LPCTSTR ac, LPCTSTR pwd );

public:
	const stSpecificCfg& GetAccountCfg( const std::string& ac, const std::string& service_name );
	stSpecificCfg* FindSpecificCfg( const std::string& ac, const std::string& service_name );
	void SaveCfgByAccount( const std::string& ac, const std::string& service_name );
	void SaveAllSpecificCfg();
	//��������ĳ�ʺŵ��������ã�������ɸ���
	stSpecificCfg* GenSpecificCfg( const std::string& ac, const std::string& service_name );

	//��½���
public:
	//��ʼ��½��Ϸ
	bool BeginLogin( int item );
	//ִ�е�½һ���ʺ�
	bool DoLoginOne();
	//�õ����ڵ�½�����ߵ�����
	DWORD GetLoginingCnt() const;

	//�ᱻԶ�̵���
public:
	//����EP
	void SetEP( FuncObj_NormalS& func_obj_normal );
	//��������
	void SetMatchCnt( FuncObj_NormalS& func_obj_normal );
	//��������״̬
	void SetRunState( FuncObj_NormalS& func_obj_normal );
	//���ý�����
	void SetTrainerName( FuncObj_NormalS& func_obj_normal );
	//���ý����ȼ�
	void SetTrainerLevel( FuncObj_NormalS& func_obj_normal );
	//���ýű������Ϣ
	void SetScriptOutputInfo( FuncObj_NormalS& func_obj_normal, const char* output_info );
	//��ʼ�ű�
	void StartRunScript( FuncObj_NormalS& func_obj_normal );
	//����ĳ����Ϸ����
	void OnGameState( FuncObj_NormalS& func_obj_normal );
	//���ֺõ���Ա
	void DiscoverGoodPlayer( FuncObj_NormalS& func_obj_normal );
	
protected:
	virtual void PreSubclassWindow();

public:
	//��Ӧ�Ҽ�down
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//��ʼ�ű�
	afx_msg void OnMenuItemStartItemScript();
	//ֹͣ�ű�
	afx_msg void OnMenuItemStopScript();
	//����ʺ�
	afx_msg void OnMenuAddAccount();
	//ɾ���ʺ�
	afx_msg void OnMenuDeleteAccount();
	//��ʾ��Ϸ����
	afx_msg void OnMenuListShowGameWindow();
	//���ýű�
	afx_msg void OnMenuListSetScript();
	//��ʾͳ����Ϣ
	afx_msg void OnMenuShowAccountInfo();
	//��ʼ���нű�
	afx_msg void OnMenuStartAllScript();
	//ֹͣ���нű�
	afx_msg void OnMenuStopAllScript();
	//��ʾ����ͳ����Ϣ
	afx_msg void OnMenuShowAllAccountInfo();
	//�ر���Ϸ����
	afx_msg void OnMenuCloseProcess();
	//�ر�������Ϸ����
	afx_msg void OnCloseAllProcess();
	//��ʼ��½��Ϸ
	afx_msg void OnMenuBeginLogin();
	//ѡ�������
	afx_msg void OnMenuSelectService();
	//�����Ϻ�
	afx_msg void OnMenuLoginSomeGame();
	//�Զ����нű�
	afx_msg void OnMenuAutoRunScript();
	//�����Զ����нű�
	afx_msg void OnMenuAllAutoRunScript();
	//ֹͣ�����Ϻ�
	afx_msg void OnMenuStopLoginAll();
	//���ú�����
	afx_msg void OnMenuSelectGameAcType();
	//�鿴�˺ŵĽ�����Ϣ
	afx_msg void OnMenuAsNotifyObj();
	//ȡ����ֹ��½��
	afx_msg void OnMenuCancelprohibit();
	//�鿴�˺���Ʒ��Ϣ
	afx_msg void OnMenuLookItemInfo();
	//�鿴�˺���Ա��Ϣ
	afx_msg void OnMenuLookPlayerInfo();
	DECLARE_MESSAGE_MAP()

private:
	//�������ͨ�ŵ�ʱ��
	void UpdateLastNotifyTime( int item );

protected:
	//first == �ʺţ�second == ��������
	typedef std::pair<std::string, std::string> SpecificCfgKeyT;
	typedef std::map<SpecificCfgKeyT, stSpecificCfg> SpecificCfgT;

	struct stGameInfo{
		int						cur_ep_;
		int						gain_total_ep_;				//��õ���EP
		int						match_cnt_;					//��������
		int						trainer_level_;				//�����ȼ�
		CString					running_state_;				//����״̬
		CString					trainer_name_;				//������
		GType::enGameState		game_state_;				//��Ϸ״̬

		stGameInfo();
	};
	
protected:
	//std::stack<int>							start_items_;	
	SpecificCfgT							specific_cfgs_;
	LoginHelperContT						login_helper_;
	ProhibitT								prohibit_login_;			//��ֹ������
	GameServiceMgr							game_service_mgr_;
};

class PageAccount_List : public ListNormal{
private:
	PageAccount_List();
	~PageAccount_List();
	friend class PageAccount;

public:
	void SaveAllAccountCfg();
	//����EP��ָ�����ļ�
	void SaveEpToTheFile();
	int CalcConnectionsCnt();

	//Э��ͨ�����
public:
	//��Ϸ�ŵĵ���
	FuncObj_NormalS::IteratorPtr CreateIterByGameAcType( enGameAcType game_ac_type, int service_idx );

public:
	static PageAccount_List* GetInstance();

protected:
	virtual void PreSubclassWindow();

private:
	//ÿ���ڶ����0�����ս�ֹ��
	void Timer_ClrProhibitAtMidnight( const boost::system::error_code& error );

private:
	static PageAccount_List*		this_;
	//boost::asio::deadline_timer		timer_clr_prohibit_;		//ÿ��0����ս�ֹ��
	DateTimeLocal					time_start_;				//����ʱ��
};