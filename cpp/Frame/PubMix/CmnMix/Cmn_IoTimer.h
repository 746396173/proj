#pragma once
/*
@author zhp
@date 2017/5/15 18:46
@purpose for timer
*/
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include "../DependSelfLib.h"
#include <ProtocolX/P_DefinesX.h>

class IoTimer{
public:
	struct lock_guard{
		lock_guard();
		~lock_guard();

	private:
		bool		old_locked_;
	};

public:
	virtual ~IoTimer();
	//������ʱ
	virtual void Continue() = 0;
	//ȡ����ʱ������ȡ����ʱ�������¼�ʱ��
	virtual void Cancel() = 0;
	//���ü�ʱ���
	virtual void SetDuration(pt_dword milli_seconds) = 0;
	//�Ƿ����ڼ�ʱ
	virtual bool IsClocking() const = 0;
};
typedef boost::shared_ptr<IoTimer> IoTimerPtr;

//��ʱ���ص�����
//����ΪIoTimerPtr
//set timer, no call times
void SetIoTimer(pt_dword milli_seconds, const std::function<void(IoTimer*)>& call_back);
void SetIoTimer1(pt_dword milli_seconds, const std::function<void(IoTimer&)>& call_back);
//����Ϊ�ص��Ĵ���
//set timer, with call times,��0��ʼ����
void SetIoTimer(pt_dword milli_seconds, pt_dword times, const std::function<void(pt_dword)>& call_back);
//������ʱ��
IoTimerPtr CreateIoTimer(pt_dword milli_seconds, bool start_timer, const std::function<void(IoTimerPtr&)>& call_back);
//��������ʱ��
IoTimerPtr LockableIoTimer(pt_dword milli_seconds, bool start_timer, const std::function<void(IoTimerPtr&)>& call_back);
