#include "stdafx.h"
#include "GLuaC.h"
#include "FuncObjC.h"

GLuaC::GLuaC()
{

}

bool GLuaC::InitThrdData()
{
	/*if (lua_script_)
	{
		assert(!"�Ѿ�������");
		return false;
	}*/

	if (!__super::InitThrdData())
		return false;
	LuasScriptEchoC::RegForLua(lua());
	return true;
}
