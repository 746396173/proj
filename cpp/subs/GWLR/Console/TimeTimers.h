#pragma once
/*
@author zhp
@date 2016/1/15 19:43
@purpose �����з�ɢ�ļ�ʱ��ʹ�ü��ϵ���С�ļ�����
*/
#include <Common/UsefulClass.h>

class HandleTimeTimers : public Singleton<HandleTimeTimers, Singleton_MakeMe>{
public:
	//std::priority_queue<TimeElapse, std::vector

public:
	bool Init();
	void OnTimer_1Seconds();
	void OnTimer_2Seconds();
	void OnTimer_5Seconds();
	void OnTimer_10Seconds();
	void OnTimer_30Seconds();
	void OnTimer_1Minutes();
	void OnTimer_2Minutes();
	void OnTimer_5Minutes();
	void OnTimer_10Minutes();
	void OnTimer_30Minutes();

private:
	//TimeElapse		te_1se
};