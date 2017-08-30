#pragma once
/*
@author zhp
@date 2017/1/4 23:00
@purpose lua vm
*/
#include <CmnMix/Cmn_LuaOper.h>

class CmnGameLuaThrdData : public LuaThrdData{
public:
	explicit CmnGameLuaThrdData(lua_State* lstate);

protected:
	void BindGlobalFn() override;
	//�˺����󶨵������ռ���scmd
	virtual void BindScriptCommand(luabind::module_& mod);

	//�ű�����
public:
	static bool CopyAssetFile(const char* file_name, const char* new_file_path);

protected:
	const char*		cmd_namespace_;
};

class GameDllLuaThrdData : public CmnGameLuaThrdData{
public:
	explicit GameDllLuaThrdData(lua_State* lstate);

protected:
	void BindGlobalFn() override;
	void BindClass() override;
	virtual void BindTest();
};
