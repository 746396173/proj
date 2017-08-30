#pragma once
/*
@author zhp
@date 2014-3-7 17:42
@purpose for more POCO library
*/
#include <boost/asio.hpp>			//����ļ�������ʹ��Poco֮ǰ��������������ͻ��б������
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Common/JsonMore.h>
#include <Poco/DateTime.h>
#include <CmnMix/Cmn_PocoMore.h>
#include "../DependSelfLib.h"
#include <ProtocolX/P_DefinesX.h>

//http package read from buffer
class HttpPackageReadFromBuffer{
public:
	HttpPackageReadFromBuffer();

public:
	//read from buffer
	bool ReadFromBuffer( const std::string& buffer );
	//void ReadFromBuffer( const char* buffer );
	bool ReadFromBuffer( const char* buffer, pt_dword buff_size );
	//�õ���Ϣ����
	const std::string& GetRealMsg() const;
	//��������Ϣ����
	static const char* RetrieveRealMsg( const char* buffer );
	//����real msg
	void SetContent( const std::string& msg );
	//////////////////////////////////////////////////////////////////////////
	//decode content as gzip
	bool DeContentAsGzip( std::string& str_out ) const;
	//decode gzip content to json
	bool DeGzipContentToJson( Json::Value& root ) const;
	//decode content to json
	bool DeContentToJson( Json::Value& root ) const;
	//encode content as gzip
	bool EnContentAsGzip( const std::string& content_src );
	//encode Json content as gzip
	bool EnJsonContentAsGzip( const Json::Value& root );
	//////////////////////////////////////////////////////////////////////////

protected:
	//ִ�ж�
	virtual void ReadImpl( std::istream& istr ) = 0;
	virtual void SetContentImpl( const std::string& msg ) = 0;

protected:
	std::string				real_msg_;
};

//http response more of read from buffer
class HTTPResponse_RFB : public Poco::Net::HTTPResponse, public HttpPackageReadFromBuffer{
public:
	//�����Ƿ���json
	bool ContentTypeIsJson() const;
	//�����Ƿ���gzip
	bool ContentTypeIsGzip() const;
	//������Ϣ����
	bool AddContent( const char* buffer, pt_dword buffer_size );
	//������Ϣ����
	void SwapContent( std::string& content );

public:
	void write( std::ostream& ostr ) const;
	void read( std::istream& istr );

protected:
	//ִ�ж�
	virtual void ReadImpl( std::istream& istr );
	virtual void SetContentImpl( const std::string& msg );
};

//http request more of read from buffer
class HTTPRequest_RFB : public Poco::Net::HTTPRequest, public HttpPackageReadFromBuffer{	
public:
	void write( std::ostream& ostr ) const;
	void read( std::istream& istr );

protected:
	//ִ�ж�
	virtual void ReadImpl( std::istream& istr );
	virtual void SetContentImpl( const std::string& msg );
};

class LuaVM;
//poco register for lua
class RegPocoForLua{
public:
	//ע��http�ַ���������
	static void RegHttpStrHandlers( LuaVM* lua_vm );
};
//////////////////////////////////////////////////////////////////////////
class TimeDuration{
public:
	typedef FunctionVoid DoFuncT;
	typedef FunctionBool DoFuncSyncT;
	typedef std::function<bool(pt_dword)> WaitFuncT;

public:
	TimeDuration(pt_dword time_duration);
	bool IsTimeout() const;
	bool IsTimeout(pt_dword time_duration) const;
	pt_dword CalcLeftDuration() const;
	pt_dword CalcLeftDuration(pt_dword time_duration) const;
	bool DoTimeout();
	bool DoTimeout(pt_dword time_duration);
	void UpdateTime();
	void Wait() const;
	void WaitUpdate();
	void SetDuration(pt_dword time_duration);
	pt_dword GetDuration() const;
	const DateTimeLocal& GetLastTime() const;
	bool TimeToDo(const DoFuncT& func, pt_dword time_duration);
	bool TimeToDo(const DoFuncT& func);
	bool TimeToDoSync(const DoFuncSyncT& func, pt_dword time_duration);
	bool TimeToDoSync(const DoFuncSyncT& func);
	bool TimeToDoSync(const DoFuncSyncT& func, pt_dword time_duration, const WaitFuncT& fn_wait);
	//���û��ָ���ļ������ô��run oneһ��
	bool WaitWithRunOne();

public:
	static TimeDuration FromNow(pt_dword time_duration);

private:
	TimeDuration();

private:
	DateTimeLocal			last_time_;
	pt_dword				time_duration_;
};
//////////////////////////////////////////////////////////////////////////
class TimeElapse{
public:
	//Ĭ�ϵ�һ�η���
	TimeElapse();
	//Ĭ�ϵ�һ�η���
	TimeElapse( pt_dword time_dist, bool let_fist_time_pass = true );
	void SetTimeDist( pt_dword time_dist );
	void SetTimerStart( bool start );
	pt_dword GetTimeDist() const;
	void SetLetFirstTimePass( bool let_first_time_pass );
	bool IsTimeout() const;
	void RefreshCurTime();
	bool DoTimeout();
	void ResetLastTime();

private:
	mutable DateTimeLocal	last_time_;
	pt_dword				time_dist_;					//��λ����
	bool					let_first_time_pass_;		//�Ƿ��һ�η���
	mutable bool			is_first_time_;
	bool					is_start_;
};
//////////////////////////////////////////////////////////////////////////