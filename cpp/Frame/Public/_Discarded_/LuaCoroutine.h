#pragma once
/*
@author zhp
@date 2016/4/10 20:48
@purpose luaЭ�̣����Ѳ����ˡ��Ѿɴ��뵥���Ƶ����ļ��С�
*/
#include <boost/enable_shared_from_this.hpp>
#include <CmnMix/Cmn_LuaOper.h>
#include <Script/lua_base.h>
#include <CmnMix/Cmn_RegexMore.h>

class ILuaCoroutine : public boost::enable_shared_from_this<ILuaCoroutine>{
public:
	enum CoState{
		kState_Invalid,
		kState_Free,
		kState_Running,
	};

public:
	ILuaCoroutine( LuaVM* lua_vm );
	typedef boost::shared_ptr<ILuaCoroutine> PtrType;
	virtual ~ILuaCoroutine();
	//resume thread
	virtual void ResumeT() = 0;
	//terminate thread
	virtual void TerminateT() = 0;
	//�Ƿ���Ч
	virtual bool IsValid() const;
	//�Ƿ����״̬
	virtual bool IsFree() const;
	//�Ƿ�������״̬
	virtual bool IsRunning() const;
	//���´�ͷ��ʼִ��
	virtual void Restart() = 0;
	//�ӳ�
	virtual bool Delay( size_t millisecond );
	//�ó�һ�ο���ʱ��(ֻ����postһ��resume��Ϣ����)
	virtual bool YieldOneFree();
	//�Ƿ���ֹ�ű��е�ѭ��
	virtual bool IsTerminateScriptRun();
	//�Ƿ���ֹ�ű�
	bool IsTerminateScript() const;
	//ǿ����ֹrun
	virtual void ForceTerminateScriptRun( bool is_terminate );
	//ǿ����ֹ�ű�
	void ForceTerminateScript( bool is_terminate );
	//ִ��ĳ���ű�
	bool RunLuaScript( const char* lua_file_name, bool is_force );
	//set coroutine state
	void SetCoState( CoState co_state );
	//get the run script file name
	const char* GetScriptFileNameForRun();
	//����ִ̨�йرսű�
	void TerminateScriptByConsole();

protected:
	//�Ƿ���Ҫ�ٴ�ִ��run
	virtual bool IsExecNextRun();
	//run������
	virtual void RunToEnd();
	//�ٴ�ִ��һ��run֮ǰ�Ķ���
	virtual void PreRun();

private:
	//register for lua
	void RegForLua();

protected:
	std::string				lua_file_name_;
	LuaVM*const				lua_vm_;

private:
	bool					force_terminate_script_run_;
	bool					force_terminate_script_;
	CoState					state_;
};

//lua coroutine
class LuaCoroutine : public ILuaCoroutine{
protected:
	LuaCoroutine( LuaVM* lua_vm );

public:
	~LuaCoroutine();
	//resume thread
	virtual void ResumeT();
	//yield thread
	//coroutine.yield��coroutine.resume�ĵ��ò�֮�䲻�ܴ���C++�ĺ�������
	virtual void YieldT();
	//terminate thread
	virtual void TerminateT();
	//�Ƿ���Ч
	virtual bool IsValid() const;
	//���´�ͷ��ʼִ��
	virtual void Restart();
	//�ӳ�
	virtual bool Delay( size_t millisecond );
	//�ó�һ�ο���ʱ��(ֻ����postһ��resume��Ϣ����)
	virtual bool YieldOneFree();
	//�Ƿ���ֹrun
	virtual bool IsTerminateScriptRun();

protected:
	//run of the new thread
	virtual void Run() = 0;
	virtual bool IsExecNextRun();

private:
	//register for lua
	void RegForLua();
	//main function of the new thread
	static void MainFunc( LuaCoroutine* lua_co );

protected:
	lua_State*				lua_state_new_;
};

//lua coroutine script
class LuaCoScript : public LuaCoroutine{
protected:
	LuaCoScript( LuaVM* lua_vm );

protected:
	virtual void Run();

private:
	void RegForLua();
};

//luaִ��coroutine
class LuaRunCo : public ILuaCoroutine{
public:
	LuaRunCo( LuaVM* lua_vm, const char* co_name, const char* co_run_func_name );
	LuaRunCo( LuaVM* lua_vm );

	virtual void ResumeT();
	virtual void TerminateT();
	virtual void Restart();

public:
	//�Ƿ��������Ľű�����
	bool IsEnableForChinese() const;
	//ע��ؼ���
	bool RegKeywordForChinese( const char* str_word_src, const char* str_word_chinese );
	//ת����lua
	std::string ConvertToLua();
	std::string ConvertToLua( const char* script_file_name );

private:
	void RegForLua();
	void Init( const char* co_name, const char* co_run_func_name );

private:
	std::string				co_name_;
	std::string				co_run_func_name_;
	RegexWordReplace		replace_from_chinese_;			//������ת����lua
};
