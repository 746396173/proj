#pragma once
/*
@author zhp
@date 2017/1/23 20:59
@purpose for plugin test
*/
#include "CmnWxDllApp.h"


class CmnPluginTest : public Cmn_DllRunApp{
protected:
	//bool OnRun_() override;		//�����������������ʵ����ʾ�Ի���ȹ���
	void BindFrame(lua_State* l) override;
	void LuaVmSetting(LuaThrdData* lua_vm) const override;

private:
	void RunWithMsgBox(const luabind::object& fn, const std::string& msg);
};