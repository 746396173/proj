#pragma once
/*
@author zhp
@date 2014-2-24 13:43
@purpose for game lua
*/
#include <FuncObjs/FuncObj.h>
#include <Script/lua_base.h>
#include <Script/LuaScript.h>

class GLuaC : public LuaVM{
public:
	GLuaC();

	//����
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
	bool InitThrdData() override;
};