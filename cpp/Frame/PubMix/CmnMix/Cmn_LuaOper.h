#pragma once
/*
@author zhp
@date 2016/11/3 19:37
@purpose lua common operate
*/
extern "C"
{
#include <lua/lualib.h>
#include <lua/MyLua.h>
}
#include "../DependSelfLib.h"
#include "_Cmn_LuaOperImpl.hpp"
#include <AssetSys/AS_Node.h>
#include <xtr1common>

//////////////////////////////////////////////////////////////////////////
/*
ƽ����luabind::object��ʱ��һ��ҪС�ģ���ö���object������������luabind::iterator���������Ƚ����õ�luabind::object�����У��ٲ�������
*/
bool LuaObjIsNil(const luabind::object& obj);
bool LuaObjIsBool(const luabind::object& obj);
bool LuaObjIsNumber(const luabind::object& obj);
bool LuaObjIsStr(const luabind::object& obj);
bool LuaObjIsTable(const luabind::object& obj);
bool LuaObjIsFn(const luabind::object& obj);
const char* LuaTypeName(const luabind::object& lua_obj);
//////////////////////////////////////////////////////////////////////////
//*************lua debug
void LuaDP_Top();
//range_min��range_max����Ϊ��������range_maxС��range_min����range_max=lua_gettop(L)
void LuaDP_Var(int range_min, int range_max, int tbl_lvl);
void LuaDP_Var(int stack_idx, int tbl_lvl);
void LuaDP_Var(int stack_idx);	//tbl_lvl=-1����ȼ�������
void LuaDP_Var();				//��������stack������tbl_lvl=-1��
//range_min����Ϊ������range_maxС��range_min�����ʾ������
void LuaDP_UpVar(int range_min, int range_max, int tbl_lvl, int fn_level);
void LuaDP_UpVar(int upvalue_idx, int tbl_lvl, int fn_level);
void LuaDP_UpVar(int upvalue_idx, int tbl_lvl);		//fn_level=0,��ʾ��ǰ����
void LuaDP_UpVar(int upvalue_idx);					//tbl_lvl=-1,fn_level=0
void LuaDP_UpVar();									//����upvalue����������ͬ�ϡ�
//������б���(����upvalue)
void LuaDP_FnInfo(int tbl_lvl, int fn_level);
void LuaDP_FnInfo(int tbl_lvl);			//fn_level=0
void LuaDP_FnInfo();					//tbl_lvl=-1,fn_level=0
void LuaDP_Traceback();
//������б���(����upvalue)
void LuaDP_TracebackEx();
void LuaDP_TracebackEx(int tbl_lvl);
//////////////////////////////////////////////////////////////////////////
struct LuaObjectPair : std::pair<luabind::object, luabind::object>{
	LuaObjectPair();
	explicit LuaObjectPair(const luabind::object& the_first);
	LuaObjectPair(const luabind::object& the_first, const luabind::object& the_second);
	const luabind::object& First() const;
	luabind::object& First();
	const luabind::object& Second() const;
	luabind::object& Second();
	operator bool() const;
	static void RegForLua(lua_State* l);

private:
	const luabind::object& _First_();
	const luabind::object& _Second_();
};
//////////////////////////////////////////////////////////////////////////

template<typename R>
typename ::Detail::EnsureString<R>::type LuaObjCast(const luabind::object& lua_obj, const R& def_value){
	if (!lua_obj.is_valid())
		return def_value;
	const auto& optional_res = luabind::object_cast_nothrow<typename ::Detail::EnsureString<R>::type>(lua_obj);
	if (optional_res)
		return *optional_res;
	return def_value;
}

luabind::object LuaObjGlobal(lua_State* lstate, const char* glo_name);

/*
tag of lua call
example:
//��ָ��tagLC_NoThrowʱ��Ĭ�ϻ��׳��쳣
LuaObjCall<void>(lua_obj, params...)
LuaObjCall<luabind::object>(lua_obj, params...)
//���������Ͳ���int��luabind���׳��쳣����LuaObjCallByDlt�����׳��쳣���᷵��Ĭ��ֵ��
LuaObjCall<int>(lua_obj, params...)
//��LuaObjCallByDlt��˵��tagLC_NoThrow���������֣�����ҪtagLCall��װ����ȻҲ������tagLCall��װһ�£�����Ϊ������������default_valueָ���ˡ�
LuaObjCallByDlt<tagLC_NoThrow>(lua_obj, default_value, params...)
LuaObjCall<tagLCall<void, tagLC_NoThrow> >(lua_obj)
//tagLC_NoThrow�ͷ������͵ĳ���˳������
LuaObjCall<tagLCall<tagLC_NoThrow, double> >(lua_obj)
//��LuaObjCall��˵��tagLC_NoThrowҲ���Ե������֣����޷���ֵ��
LuaObjCall<tagLC_NoThrow>(lua_obj)
*/
template<typename... Args>
struct tagLCall{
	typedef boost::mpl::set<Args...> SetT;
	typedef Detail::tagLC_SetHolder<SetT> SetHolder;
};
//�����׳��쳣
struct tagLC_NoThrow{};

//luabind::unpack_call������֧��unpack table��unpack vector��
//���Ƿ���luabind::object����ʾֻ����һ�������Ҳ���Է��ض�������lua�У���ô����lua_pushvalue֮��ĺ���
template<typename UnionR, typename... Args>
typename Detail::stLuaTagHlp<UnionR>::ResType
LuaObjCall(const luabind::object& lua_func, const Args&... args){
	typedef typename Detail::stLuaTagHlp<UnionR>::ResType ResType;
	typedef typename Detail::stLuaTagHlp<UnionR>::NoThrow NoThrow;
	if (!LuaObjIsFn(lua_func))
		return ResType();
	return NoThrow::Call<ResType>(lua_func, args...);
}
//���Ƿ���luabind::object����ʾֻ����һ�������Ҳ���Է��ض�������lua�У���ô����lua_pushvalue֮��ĺ���
template<typename UnionR, typename... Args>
typename Detail::stLuaTagHlp<UnionR>::ResType
LuaObjCall(lua_State* lstate, const char* glo_name, const Args&... args){
	typedef typename Detail::stLuaTagHlp<UnionR>::ResType ResType;
	typedef typename Detail::stLuaTagHlp<UnionR>::NoThrow NoThrow;
	auto lua_func = LuaObjGlobal(lstate, glo_name);
	if (!LuaObjIsFn(lua_func))
		return ResType();
	return NoThrow::Call<ResType>(lua_func, args...);
}
/**/
//by default
template<typename UnionR = tagLCall<>, typename R, typename... Args>
typename Detail::EnsureString<R>::type LuaObjCallByDlt(const luabind::object& lua_func, const R& def_value, const Args&... args){
	typedef typename Detail::stLuaTagHlp<UnionR>::SetT OrgSetT;
	typedef typename boost::mpl::insert<OrgSetT, luabind::object>::type NewSetT;
	luabind::object lua_res = LuaObjCall<Detail::tagLC_SetHolder<NewSetT> >(lua_func, args...);
	return LuaObjCast(lua_res, def_value);
}
template<typename UnionR = tagLCall<>, typename R, typename... Args>
typename Detail::EnsureString<R>::type 
LuaObjCallByDlt(lua_State* lstate, const char* glo_name, const R& def_value, const Args&... args){
	typedef typename Detail::stLuaTagHlp<UnionR>::SetT OrgSetT;
	typedef typename boost::mpl::insert<OrgSetT, luabind::object>::type NewSetT;
	auto lua_func = LuaObjGlobal(lstate, glo_name);
	luabind::object lua_res = LuaObjCall<Detail::tagLC_SetHolder<NewSetT> >(lua_func, args...);
	return LuaObjCast(lua_res, def_value);
}
/**/
//////////////////////////////////////////////////////////////////////////
//�µĺ�������
class LuaNewFEnv{
public:
	explicit LuaNewFEnv(const luabind::object& the_func);
	LuaNewFEnv(const luabind::object& the_func, const luabind::object& new_env);
	~LuaNewFEnv();

private:
	void Init(const luabind::object& the_func, const luabind::object& new_env);

public:
	luabind::object	fn_;
	luabind::object new_fenv_;
	luabind::object	old_fenv_;
};
/**/
//////////////////////////////////////////////////////////////////////////
//lua ���л�
class LuaSerialize{
public:
	static std::string PlutoPersist(const luabind::object& permanents, const luabind::object& root_obj);
	static luabind::object PlutoUnpersist(const luabind::object& permanents, const std::string& buffer);
	static std::string ToString(const luabind::object& lua_obj);
	static std::string ToString(const luabind::object& lua_obj, int tbl_lvl);
	static void ToString(std::ostream& ostm, const luabind::object& lua_obj, int tbl_lvl);
	static bool Key2String(const luabind::object& key, std::string& buffer);
	static std::string Key2String(const luabind::object& key);
	static std::string ToPointerString(const luabind::object& lua_obj);

public:
	template<typename... Args>
	static std::string ToLuaString(const char* separator, const Args&... args){
		std::string res;
		::Detail::ToLuaString(res, separator, args...);
		return res;
	}
	template<typename... Args>
	static std::string ToLuaStringCall(const char* str_fn, const Args&... args){
		std::string res;
		if (str_fn)
			res.append(str_fn);
		res.append(1, '(');
		::Detail::ToLuaString(res, ",", args...);
		res.append(1, ')');
		return res;
	}

private:
	//luabind::object��ò�Ҫ��std::set��������Ϊ���õ���<����������vector֮��������õ���==��������
	typedef std::vector<luabind::object> LuaObjContT;
	static bool _ToStringImpl_(LuaObjContT& unique_tbl, std::ostream& buffer, const luabind::object& lua_obj, int tab_num, bool new_line, int tbl_lvl);
};

class LuaSerializable{
public:
	virtual ~LuaSerializable();
	virtual bool SerializeR(const luabind::object& lua_obj) = 0;
	virtual bool SerializeW(luabind::object& lua_obj) const = 0;
};
//////////////////////////////////////////////////////////////////////////
/**/
//LuaParamHolder�������ã�����lua_pcall֮��ĺ����ģ��;��������ǡ�
class LuaParamHolder{
public:
	//����
	explicit LuaParamHolder(lua_State* lstate);
	//�ָ�
	~LuaParamHolder();

private:
	luabind::object	params;
	lua_State*		lstate_;
};
/**/
//�����ջ
class LuaStackPack{
public:
	explicit LuaStackPack(lua_State* lstate);
	luabind::object PackToTable(int stack_idx_begin, int stack_idx_end, bool is_remove) const;
	bool UnpackToStack(const luabind::object& tbl) const;

private:
	lua_State*		lstate_;
};
/**/
//////////////////////////////////////////////////////////////////////////
class LStateWrapper{
protected:
	LStateWrapper();

public:
	LStateWrapper(lua_State* lstate);
	virtual ~LStateWrapper(){}
	lua_State* lua() const{ return lstate_; }
	
public:
	//���Ƿ���luabind::object����ʾֻ����һ�������Ҳ���Է��ض�������lua�У���ô����lua_pushvalue֮��ĺ���
	luabind::object LuaObjGlobal(const char* glo_name) const;
	template<typename UnionR, typename... Args>
	typename Detail::stLuaTagHlp<UnionR>::ResType
		LuaObjCall(const char* glo_name, const Args&... args) const{
		return ::LuaObjCall<UnionR>(lstate_, glo_name, args...);
	}
	template<typename UnionR = tagLCall<>, typename R, typename... Args>
	typename Detail::EnsureString<R>::type
		LuaObjCallByDlt(const char* glo_name, const R& def_value, const Args&... args) const{
		return ::LuaObjCallByDlt<UnionR>(lstate_, glo_name, def_value, args...);
	}

	//only load, not execute
public:
	//�൱��lua�е�loadfile
	virtual luabind::object LoadFile(const char* file_name) const;
	luabind::object LoadString(const char* str) const;
	luabind::object LoadBuffer(const char* buffer, size_t size, const char* buff_name = nullptr) const;

	//load and execute
public:
	//���Ƿ���luabind::object����ʾֻ����һ�������Ҳ���Է��ض�������lua�У���ô����lua_pushvalue֮��ĺ���
	luabind::object DoFile(const char* file_name) const;
	luabind::object DoString(const char* str) const;
	luabind::object DoBuffer(const char* buffer, size_t size, const char* buff_name = nullptr) const;
	luabind::object Require(const char* modname) const;

	//debug
	//DP->debug print
public:
	void DP_Top() const;
	//range_min��range_max����Ϊ��������range_maxС��range_min����range_max=lua_gettop(L)
	void DP_Var(int range_min, int range_max, int tbl_lvl) const;
	//range_min����Ϊ������range_maxС��range_min�����ʾ������
	void DP_UpVar(int range_min, int range_max, int tbl_lvl, int fn_level) const;
	//������б���(����upvalue)
	void DP_FnInfo(int tbl_lvl, int fn_level) const;
	void DP_Traceback() const;
	//������б���
	void DP_TracebackEx(int tbl_lvl) const;
	bool D_GetFnInfo(int fn_level, std::ostream& out, int tbl_lvl) const;
	//�õ������ߺ�����
	static int LuaD_GetLevelFnName(lua_State* L);

	//mylua
public:
	static bool My_TableSort(const luabind::object& tbl);
	static std::string My_ToString(const luabind::object& obj);
	static int My_DbgTracebackToStr(lua_State *L);

	//another
public:
	template<typename T>
	luabind::object CreateMultiIdxFn(const T& cont){
		if (cont.empty())
		{
			assert(false);
			return luabind::object();
		}
		auto new_tbl = luabind::newtable(lstate_);
		int idx = 1;
		for (auto& v : cont)
		{
			new_tbl[idx] = v;
			++idx;
		}
		return LuaObjCall<luabind::object>("CreateMultiIdxFn", new_tbl);
	}
	template<typename T, typename F>
	luabind::object CreateMultiIdxFn(const T& cont, const F& f){
		if (cont.empty())
		{
			assert(false);
			return luabind::object();
		}
		auto new_tbl = luabind::newtable(lstate_);
		int idx = 1;
		for (auto& v : cont)
		{
			new_tbl[idx] = f(v);
			++idx;
		}
		return LuaObjCall<luabind::object>("CreateMultiIdxFn", new_tbl);
	}
	static bool ObjectEqual(const luabind::object& lhs, const luabind::object& rhs);
	//���Ǳ�
	static bool DeepCoverTbl(const luabind::object& src, const luabind::object& dst);
	//���Ʊ�
	static bool CopyTbl(const luabind::object& src, const luabind::object& dst, bool copy_metatable);
	//���Ŀ���Ѵ��ڣ��򲻸���
	static bool OptionalCopy(const luabind::object& src, const luabind::object& dst);

public:
	lua_State*		lstate_;
};

class LStateWrapperAS : public LStateWrapper{
protected:
	LStateWrapperAS();

public:
	LStateWrapperAS(lua_State* lstate, const char* as_path = nullptr);
	void SetLuaPath(const char* as_path);
	luabind::object LoadFile(const char* file_name) const override;
	AS_NodePtr GetRootPath() const;
	static AS_NodePtr FindAS_LuaFile(const AS_NodePtr& lua_dir, const char* file_name);

protected:
	AS_NodePtr		lua_path_root_;
};

class Cmn_LuaCfgResolver;
class Cmn_LuaCfgFileBase_;
class LuaThrdData : public LStateWrapperAS{
	LuaThrdData(const LuaThrdData&) = delete;
	LuaThrdData& operator = (const LuaThrdData&) = delete;
	typedef boost::shared_ptr<Cmn_LuaCfgResolver> LuaCfgResolverPtrT;

public:
	LuaThrdData(lua_State* lstate = nullptr, const char* as_path = "lua");
	~LuaThrdData();
	//SetMe��GetMe������lua�̵߳���
	static void SetMe(LuaThrdData* thrd_data);
	//��ͬ���̲߳�ͬ��ʵ����Ҫ������SetMe
	static LuaThrdData& GetMe();
	void SetMainLuaName(const char* main);
	const char* GetMainLuaName() const;
	void SetScriptDirName(const char* script_dir);
	void SetMustHasLuaRoot(bool must_has_lua_root);
	static void RegLuabind(lua_State* lstate);
	template<typename T>
	static T* AsPtr(){
		return static_cast<T*>(&LuaThrdData::GetMe());
	}
	template<typename T>
	static T& AsRef(){
		typedef typename std::remove_cv<T>::type UnCvT;
		typedef std::remove_reference<UnCvT>::type OrgT;
		return *static_cast<OrgT*>(&LuaThrdData::GetMe());
	}
	static const char* GetRequireLuaFilesName();

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

protected:
	//Init��SetMe����
	virtual bool InitThrdData();

private:
	void AddRequireFiles(const char* lua_file, const AS_NodePtr& node);
	static int Require_PreLoad_(lua_State *L);

private:
	AS_NodePtr					require_luafiles_node_;
	LuaCfgResolverPtrT			require_cfg_resolver_;
	Cmn_LuaCfgFileBase_*		require_cfg_file_;
	bool						self_lstate_;
	const char*					main_lua_name_;
	const char*					script_dir_name_;
	bool						must_has_lua_root_;
	static const char* const	kRequireLuaFilesName_;
};
//////////////////////////////////////////////////////////////////////////