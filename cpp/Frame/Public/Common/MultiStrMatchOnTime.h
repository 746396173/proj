#pragma once
/*
@author zhp
@date 2014-2-28 21:07
@purpose ��ָ����һ��ʱ���ڣ�ƥ��ָ���Ķ���ַ���
*/
#include "stdafx.h"
#include <map>
#include "../DependSelfLib.h"

class MultiStrMatchOnTime{
protected:
	MultiStrMatchOnTime();
	virtual ~MultiStrMatchOnTime();

public:
	//��ʾ����ɾ��template_id����
	static const size_t			kMultiStrLifecycle_Forever = MAXSIZE_T;

	//interfaces
public:
	static MultiStrMatchOnTime& GetMe();
	//��ʼ��ĳ��template_id����
	//template_lifecycle==milliseconds
	//is_order_matched == true:���ճ�ʼ����˳��ƥ��
	//�Ƿ�ƥ��ɹ��󣬸�template_id��ʧЧ
	bool InitTemplateIdObj( int template_id, size_t template_lifecycle, bool is_order_matched );
	//���ӱ�ƥ����ַ���
	bool AddMatchedStr( int template_id, const char* matched_str );
	//��ָ����template_id�����У�ƥ��ָ�����ַ���
	//����true��ʾ��ȫ���ɹ�ƥ��
	bool AllMatchSpecifyStr( int template_id, const char* specify_str );
	//����ƥ��
	void ResetMatch( int template_id );
	//�õ�����ɾ��������
	size_t GetLifecycleForever() const;
	//�Ƿ�ƥ��
	virtual bool IsMatched( const char* str_src, const char* specify_str );

private:
	friend void TimeoutImple( MultiStrMatchOnTime*, size_t, int );
	void Timeout( int template_id );

private:
	std::map<int, void*>								map_impl_;
};

class LuaVM;
//for lua
class MultiStrMatchOnTimeForLua : public MultiStrMatchOnTime{
	MultiStrMatchOnTimeForLua();
public:
	virtual bool IsMatched( const char* str_src, const char* specify_str );

	//register for lua
	static void RegForLua( LuaVM* lua_vm );
	static MultiStrMatchOnTimeForLua& GetMe();

private:
	LuaVM*					lua_vm_;
};