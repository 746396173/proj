#pragma once
/*
@author zhp
@date 2014-2-24 13:49
@purpose for game lua
*/
#include "FuncObjs/FuncObj.h"
//#include "Script/lua_base.h"
#include <Script/LuaScript.h>
#include <Common/CmnPriLuaData.h>

class GLuaS : public GLua{
public:
	GLuaS( FuncObj* parent );
};

class FuncObj_NormalS;
class LuaScriptS : public LuasScriptEchoS{
public:
	LuaScriptS( LuaVM& lua_vm, FuncObj_NormalS& func_obj );
	bool OutputScriptInfo( const std::string& script_info );

private:
	FuncObj_NormalS&			func_obj_;
};

class GLuaVM_S : public LuaVM{
	GLuaVM_S();

public:
	static GLuaVM_S& GetMe();
	static void ReleaseMe();
	static GLuaVM_S* GetInstance();
	bool InitScript( HMODULE module_name, LPCTSTR main_lua_file_name );
	CmnPriLuaData* GetLoginData() const;

protected:
	//ȫ�ֺ���
	virtual void BindGlobalFn();
	//�ṹ��
	virtual void BindStruct();
	//��
	virtual void BindClass();
	//������ö�����͵�
	virtual void BindConst();
	//����
	virtual void BindOther();
	virtual bool DoPrivateLuaFileByFile();

private:
	static GLuaVM_S*			lua_vm_;
	std::shared_ptr<CmnPriLuaData>			login_data_;
};