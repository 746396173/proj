#pragma once
/*
@author zhp
@date 2014/8/31 3:30
@JsonCall->BufCall:  2016/12/26 21:26
@purpose for chinese lua script
*/
#include <Net/Bufcall_Socket.h>
#include <Common/UsefulClass.h>
#include <Net/IoTimer.h>
#include "../DependSelfLib.h"
#include <CmnMix/Cmn_RegexMore.h>
#include <WgFacility/CmnSceneHandler.h>
#include <vector>
#include <luabind/luabind.hpp>


class LuaScriptEchoBase : public BufCall_SocketExcept{
protected:
	LuaScriptEchoBase(FuncObj& parent);
	enum enOperResult{
		kBeginRun,	//��ʼ����
		kStopped,	//��ֹͣ
	};

public:
	//ִ��ĳ���ű�
	virtual bool RunLuaScript(const std::string& lua_file_name, const std::string& lua_serialize) = 0;
	//��ֹ�ű�
	virtual bool TerminateScript() = 0;
	//����ű���Ϣ
	virtual bool OutputScriptInfo( const std::string& script_info ) = 0;
	//�������
	virtual bool OperResult(enOperResult result) = 0;

private:
	BC_REG_CLS_DECLARE(LuaScriptEchoBase);
};

class ScriptRunRAII{
public:
	virtual ~ScriptRunRAII();
	virtual bool PreRun();
	virtual void AfterRun();
};

class LuasScriptEchoC : public LuaScriptEchoBase, public Singleton<LuasScriptEchoC, Singleton_Instance>{
	struct stLevel0ScriptInfo{
		std::string			level0_script_name_;
		luabind::object		fn_get_script_name_;
	};
	typedef std::vector<stLevel0ScriptInfo> Level0Scripts;

public:
	struct stEvents{
		std::vector<std::string>		event_names_;
	};
	typedef std::vector<const stEvents*> EventsCont;

public:
	LuasScriptEchoC(FuncObj& parent);
	~LuasScriptEchoC();
	static void RegForLua(lua_State* l);
	static bool IsRunning();

public:
	bool TerminateScript() override;
	bool OutputScriptInfo(const std::string& script_info) override;	
	//ת����lua
	std::string ConvertToLua(const std::string& script_file_name);
	luabind::object LoadScriptFile(const std::string& script_file_name, const luabind::object& script_param, bool is_new_env);

	//���ܻ��ű����
public:
	//�Զ�ѡ�����нű�
	static luabind::object AutoChooseRunScript(const CSH_HandlerPtr& scene_handler, const luabind::object& fn_get_script_name);
	//�ı����еĽű������top_n=0���򵯳������Ľű�;top_n=1���򵯳���������һ��ű�����������;top_n=-1���򵯳���ǰ���еĶ���ű����������ơ�
	static void ChangeRunningScript(int top_n = 0, bool is_rerun = false);

	//�¼����
public:
	//ִ�в��ȴ��¼�
	//fn_event_handler���Ƿ����棬��ʾ�¼�����ɹ���������һ��ִ��fn_run��������˳� ִ�в��ȴ��¼��������¼��������Ľ������֮��
	static luabind::object RunWaitEvent(const luabind::object& fn_run, const luabind::object& fn_event_handler, const std::string& event_name);
	//event_names�Ǹ�����ʾһϵ�е��¼�
	static luabind::object RunWaitEvent_(const luabind::object& fn_run, const luabind::object& fn_event_handler, const luabind::object& event_names);
	//�����¼�
	static void TriggerEvent(const std::string& event_name);

private:
	static luabind::object RunWaitEventImpl_(const luabind::object& fn_run, const luabind::object& fn_event_handler, const stEvents& events);

protected:
	bool RunLuaScript(const std::string& lua_file_name, const std::string& lua_serialize) override;
	bool OperResult(enOperResult result) override;
	virtual void RunScriptImpl(const std::string& lua_file_name);
	virtual ScriptRunRAII* CreateRunRAII();
	virtual void PreCallScriptFn(const luabind::object& lua_file_func);
	virtual luabind::object GetConsoleCfg() const;

private:
	void CatchRunScript(const std::string& lua_file_name);
	void TerminateScriptImpl();
	//ע��ؼ���
	bool RegKeywordForChinese(const char* str_word_src, const char* str_word_chinese);
	static bool OutputScriptInfo_(const std::string& script_info);

private:
	bool				running_;
	RegexWordReplace	replace_from_chinese_;		//������ת����lua
	IoTimerPtr			timer_to_run_script_;
	Level0Scripts		level0_scripts_;			//��ǰ���еĶ����ű���
	EventsCont			cur_events_;				//��ǰ�¼�

protected:
	ScriptRunRAII*		script_raii_;

	BC_REG_CLS_DECLARE(LuasScriptEchoC);
};

class LuasScriptEchoS : public LuaScriptEchoBase{
public:
	LuasScriptEchoS(FuncObj& parent);
	bool RunLuaScript(const std::string& lua_file_name, const std::string& lua_serialize = kEmptyStr) override;
	bool TerminateScript() override;

protected:
	bool OperResult(enOperResult result) override;

	BC_REG_CLS_DECLARE(LuasScriptEchoS);
};
