#pragma once
/*
@author zhp
@date 2014/1/20
@purpose use lua
*/
#include <CmnMix/Cmn_LuaOper.h>

//LuaVM������ѻ��������ˣ���������Ŀ
class LuaVM : public LuaThrdData{
public:

	//forע�ắ�����ࡢ�ṹ��
protected:
	//ȫ�ֺ���
	void BindGlobalFn() override;
	//��
	void BindClass() override;
};