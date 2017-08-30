#pragma once
/*
@author zhp
@date 2016/11/6 17:08
@purpose for io_service
*/
#include <boost/asio/io_service.hpp>
#include <boost/scope_exit.hpp>
#include "../DependSelfLib.h"
#include <boost/atomic/atomic.hpp>


class IoService{
	typedef boost::asio::io_service IoSerT;
	struct WorkImpl_ : boost::asio::io_service::work{
		explicit WorkImpl_(IoService& ios);
		explicit WorkImpl_(boost::asio::io_service::work& ios);
		WorkImpl_(const WorkImpl_& other);
		WorkImpl_(const boost::asio::io_service::work& other);
	};

public:
	IoService();
	IoService(const IoService&) = delete;
	IoService& operator = (const IoService&) = delete;
	
public:
	//IoService::work work(GetIoService());	���Ա�֤work��������ǰ��io_s_��run�����˳���
	typedef WorkImpl_ work;

public:
	IoSerT& GetImpl();
	const IoSerT& GetImpl() const;
	template<typename T>
	void post(const T& f){
		return impl_.post(f);
	}
	void stop(){
		return impl_.stop();
	}
	//Ҫ������ִ�У�����������Run��RunOne��Poll��PollOne�ڲ���������ִ�е�������Ч����ͬpost
	template<typename T>
	void dispatch(const T& f){
		++do_exec_depth_;
		BOOST_SCOPE_EXIT_ALL(&){
			--do_exec_depth_;
			assert(do_exec_depth_ >= 0);
		};
		return impl_.dispatch(f);
	}
	std::size_t PollOne();
	std::size_t Poll();
	std::size_t Run();
	std::size_t RunOne();
	int GetExecDepth() const;

private:
	IoSerT				impl_;
	boost::atomic<int>	do_exec_depth_;			//ִ�����
};