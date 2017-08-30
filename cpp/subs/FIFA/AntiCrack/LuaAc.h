#pragma once
/*
@author zhp
@date 2014/6/24 2:07
@purpose for anti crack lua
*/
#include <Script/lua_base.h>
#include <Common/UsefulClass.h>

class Lua_Ac : public LuaVM, public Singleton<Lua_Ac, Singleton_MakeMe>{
public:
	Lua_Ac();

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
	virtual bool DoMainLuaFileByFile();
};