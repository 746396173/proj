#pragma once
/*
@author zhp
@date 2016/11/4 15:29
@purpose Asset System Mgr
*/
#include "AS_Node.h"
#include <typeinfo>
#include <map>
#include "./DependSelfLib.h"
#include <boost/preprocessor/cat.hpp>


class AS_Sys{
	AS_Sys();
	AS_Sys(const AS_Sys&) = delete;
	AS_Sys& operator = (const AS_Sys&) = delete;

public:
	//sys_dirΪ�ձ�ʾ����Ҫϵͳ·����ϵͳ·��һ��Ϊexe��dll����·��
	//assf�ļ�������std::ios_base::binary����ʽ�򿪣��Զ����Ƶ���ʽ��д����AS_Node��Serializeϵ�к������޴����ơ�
	static void SetMe(std::istream& istm, const std::string& sys_dir = std::string());
	static AS_Sys& GetMe();
	AS_NodePtr GetRoot() const;
	bool HasTheFile(const luabind::object& tbl, const char* file_name) const;
	bool AddFileToTbl(luabind::object& tbl, const AS_NodePtr& node_root, const AS_NodePtr& file_node) const;
	bool AddFilesByTbl(const luabind::object& tbl, AS_NodePtr& node_root) const;

	static void RegForLua(lua_State* l);

private:
	AS_NodePtr		root_;
	static AS_Sys	me_;
};

class AS_Factory{
	friend class AS_Sys;
	AS_Factory();
	AS_Factory(const AS_Factory&) = delete;
	AS_Factory& operator = (const AS_Factory&) = delete;
	typedef std::map<const char*, AS_NodePtr> MapT;

public:
	typedef IteratorTraits<const char*, IterContTag_ByCopy> AS_FactoryTraits;
	typedef IteratorTraits<MapT::value_type, IterContTag_ByRef, IterFilterTag_Custom> AS_NodeTraits;
	typedef AS_FactoryTraits::iterator IteratorT;
	typedef AS_FactoryTraits::iterator_pointer IteratorPtr;

public:
	template<typename T>
	struct RegHelper{
		RegHelper(){
			AS_Factory::GetMe().RegCls(new T);
		}
	};
#define AS_FACTORY_REG(cls_name)	AS_Factory::RegHelper<cls_name> BOOST_PP_CAT(_as_auto_reg_, __LINE__);

public:
	static AS_Factory& GetMe();
	AS_NodePtr RegCls(AS_Node* node);
	AS_NodePtr CreateNode(const char* cls_name) const;
	IteratorPtr Iterator() const;
	IteratorPtr ValidClsNmae(const AS_NodePtr& parent) const;

public:
	//assf�ļ�������std::ios_base::binary����ʽ�򿪣��Զ����Ƶ���ʽ��д��
	AS_NodePtr CreateWithSerialize(std::istream& istm) const;
	bool WriteToSerialize(const AS_NodePtr& node, std::ostream& ostm) const;
	AS_NodePtr CreateWithSerialize_Zlib(std::istream& istm) const;
	bool WriteToSerialize_Zlib(const AS_NodePtr& node, std::ostream& ostm) const;
	AS_NodePtr ReadFromFile(const std::string& file_name) const;
	bool WriteToFile(const AS_NodePtr& node, const std::string& file_name) const;

private:
	AS_NodePtr DoCreateByName_(std::istream& istm, AS_StrSizeT cnt) const;
	MapT::const_iterator Find(const char* name) const;
	static void RegForLua(lua_State* l);

private:
	MapT					holder_;
};
