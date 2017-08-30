#pragma once
#include "TabPages.h"
#include "LoginS.h"
#include <Poco/Timestamp.h>
#include <Poco/DateTime.h>
#include <Socket/IoTimer.h>
#include "CoordinateS.h"

class CTabOption : public CTabCtrl, public Server, public Singleton<CTabOption, Singleton_Instance>{
public:
	CTabOption();
	~CTabOption();

	//type definition
public:
	//�ؼ�����
	typedef std::vector<DWORD> AddrDatasT;

public:
	PageAccount& GetPageAccount();
	//get succeed
	bool IsLoginSucceed() const;
	//set login succeed
	int SetLoginSucceed( bool succeed );
	//�����û�ʹ������
	void SetUserEndTime( const Poco::Timestamp& timestamp );
	void SetUserEndTime( const Poco::DateTime& end_date_time );
	//��յ�½��Ϣ
	void ClearLoginInfo();
	//�õ�ʹ������
	const Poco::DateTime& GetEndDateTime() const;
	//�õ��ؼ�����
	const AddrDatasT& GetAddrDatas() const;
	//��ӹؼ�����
	void AddAddrData( DWORD addr_data );
	void ClearAddrDatas();
	//����Э������
	void ConnectCoordinate();
	//������״̬
	void CheckDebugger();
	//CRC���
	void CheckCrcValid();
	//������ʱ��֤��½
	void TimerCheckLogin();
	CoorTrans::TrackIterPtrT MakeTransTrackIterPtr();

protected:
	afx_msg void OnSelChange( NMHDR* notify, LRESULT* result );
	afx_msg void OnSelChanging( NMHDR* notify, LRESULT* result );
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	DECLARE_MESSAGE_MAP()

private:
	bool OnConnected( IoConnectBase* connect );
	void OnDisconnect( IoConnectBase* connect );
	virtual Session* CreateSession();

private:
	CoordinateServer					coor_server_;				//Э������
	Poco::DateTime						user_end_time_;				//�û�ʹ������
	LoginServer							login_s_;

private:
	typedef TablePage* TablePagePtr;

	TablePagePtr						table_pages_[stMakeTabPages::kPagesMax];
	bool								login_succeed_;				//��½�Ƿ�ɹ�
	AddrDatasT							addr_datas_;
	IoTimerPtr							timer_check_login_;			//��ʱ��֤��½
	IoConnectIterPtr					io_connects_iter_;
};