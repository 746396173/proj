#pragma once
/*
@author zhp
@date 2014-2-18 1:06
@purpose some useful classes
*/
#include "stdafx.h"
#include <cassert>
#include "UsefulFunc.h"
#include <map>
#include <boost/lexical_cast.hpp>
#include <set>
#include "CmnException.h"
#include "../DependSelfLib.h"
#include <CmnMix/Cmn_UsefulClass.h>

//����MFC��ǰ��ģ��ʵ��
//AfxGetResourceHandle();AfxGetInstanceHandle();
//ModuleReplace�����ͷŵ�ʱ�򣬻�ָ�ԭ����
class ModuleReplace{
public:
	//����resource handle��instance handleΪmodule
	ModuleReplace( HMODULE module );
	ModuleReplace( HMODULE new_resource_handle, HMODULE new_instance_handle );
	~ModuleReplace();

private:
	void SetNewHandle( HMODULE new_resource_handle, HMODULE new_instance_handle );

private:
	HMODULE			old_resource_handle_;
	HMODULE			old_instance_handle_;
};

//ָ����ʼ�ַ���������ַ�������λ�ַ���
template<typename CharT>
class FindBetweenString{
public:
	//str_begin==0���ʾ�ӿ�ͷ��str_endָ���Ľ�β
	FindBetweenString( const CharT* str_begin,  const CharT* str_end ){
		str_begin_ = str_begin;
		str_end_ = str_end;
		assert(str_end);
	}

	//first == begin, second == end
	typedef std::pair<const CharT*, const CharT*> RangePtr;
	RangePtr Parse( const CharT* str_dest ){
		if ( !str_dest )
			goto LABLE_RET;
		const CharT* str_begin;
		if ( !str_begin_ )
			str_begin = str_dest;
		else
			str_begin = StdEx::TStrStr(str_dest, str_begin_);
		if ( !str_begin )
			goto LABLE_RET;
		auto str_end = StdEx::TStrStr(str_begin, str_end_);
		if ( !str_end )
			goto LABLE_RET;
		return RangePtr(str_begin, str_end);
LABLE_RET:
/*
#ifdef _DEBUG
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "û�����ҵ�ָ�����ַ�����str_begin:" << str_begin_ << ".str_end:" << str_end_ << ".str_dest:" << str_dest;
#endif*/
		return RangePtr(nullptr, nullptr);
	}

private:
	const CharT*				str_begin_;
	const CharT*				str_end_;
};
typedef FindBetweenString<char> FindBetweenStringA;

//����ʱ���ע��
//runtime class register
class RuntimeClassReg{
public:
	virtual ~RuntimeClassReg();
	//ע��һ��runtime class
	bool RegisterRuntimeClass( size_t runtime_class_id, const CRuntimeClass* runtime_class );
	//�Ƴ�ĳ��runtime class
	void RemoveRuntimeClass( size_t runtime_class_id );
	//ͨ��idѰ��ĳ��runtime class
	CRuntimeClass* FindRuntimeClass( size_t runtime_class_id ) const;

private:
	std::map<size_t, CRuntimeClass*>			map_runtime_;
};

//////////////////////////////////////////////////////////////////////////
//���Ч��
class FrameCheck : public Singleton<FrameCheck, Singleton_Me>{
	FrameCheck();
public:
	inline void Check(){
		auto str_tmp = RandomUniqueStr(_countof(buffer_));
		std::copy(str_tmp.begin(), str_tmp.end(), buffer_);
	}
	void TryCheck();
	inline bool FailedCheck_();

private:
	char					buffer_[256];
	static FrameCheck		only_one_;
};

class SmartCondition{
public:
	typedef FunctionVoid DoFuncT;
	struct AutoResetDo{
		AutoResetDo( SmartCondition& cond );
		bool operator () ();
		bool operator () (pt_dword timeout);
		bool operator () (pt_dword timer_milli_seconds, const DoFuncT& func_do);
		bool operator () (pt_dword timer_milli_seconds, pt_dword timeout, const DoFuncT& func_do);

	private:
		SmartCondition&			cond_;
	};

public:
	SmartCondition();
	void ResetCondition();
	bool CondtionTrue() const;
	void TouchCond();

	bool WaitTouch();
	bool WaitTouch( pt_dword timeout );
	bool TimerDoWaitTouch(pt_dword timer_milli_seconds, const DoFuncT& func_do);
	bool TimerDoWaitTouch(pt_dword timer_milli_seconds, pt_dword timeout, const DoFuncT& func_do);

private:
	bool			cond_true_;
};

template<typename T>
class UseInitDelay{
public:
	UseInitDelay(){
		is_init_ = false;
	}
	void Construct(){
		if (is_init_)
			return;
		new (buffer_) T();
		is_init_ = true;
	}
	T& get(){
		if (is_init_)
			return *(T*)buffer_;
		new (buffer_) T();
		is_init_ = true;
		return *(T*)buffer_;
	}
	operator T& (){
		return get();
	}

private:
	char	buffer_[sizeof(T)];
	bool	is_init_;
};

class IniProfile{
public:
	IniProfile( const std::string& profile_full_file_name );
	IniProfile();
	void SetProfile( const std::string& profile );
	const std::string& GetProfile() const;
	template<typename Setion_, typename Key_, typename T>
	bool Write(const Setion_& setion, const Key_& key, const T& the_value){
		const auto& the_setion = std::to_string(setion);
		const auto& the_key = std::to_string(key);
		const auto& the_str = std::to_string(the_value);
		auto res = !!::WritePrivateProfileStringA(the_setion.c_str(), the_key.c_str(), the_str.c_str(), profile_name_.c_str());
		assert(res);
		return res;
	}
	template<typename Setion_, typename Key_, typename T>
	bool Read(const Setion_& setion, const Key_& key, T& the_value, const T& def_value){
		const auto& the_setion = std::to_string(setion);
		const auto& the_key = std::to_string(key);
		char szbuffer[MAX_PATH];
		if (GetPrivateProfileStringA(the_setion.c_str(), the_key.c_str(), "", szbuffer, sizeof(szbuffer), profile_name_.c_str()) <= 0)
		{
			the_value = def_value;
			return true;
		}
		try{
			the_value = boost::lexical_cast<T>(szbuffer);
			return true;
		} DO_CATCH_ALL_EXCEPTION({
			assert(false);
			return false;
		})
	}

protected:
	std::string		profile_name_;
};

//������ԭ�����͵��б�����LUA��������
template<typename T>
class AtomicValue{
public:
	typedef T ValueType;

public:
	AtomicValue(){
		value_ = 0;
	}
	explicit AtomicValue( const T& v ) : value_(v){}
	AtomicValue( const AtomicValue& v ) : value_(v.value_){}
	AtomicValue& operator = ( const AtomicValue& v ){
		value_ = v.value_;
		return *this;
	}

public:
	T			value_;
};

//������������/������
template<typename ContT_>
class NameListRef{
public:
	typedef typename ContT_::value_type ValueType;
	typedef ContT_ ContType;
	typedef typename ContType::iterator iterator;
	typedef typename ContType::const_iterator const_iterator;

private:
	static bool NameList_TestValueValid_( const std::string& v ){
		if (v.empty())
		{
			assert(false);
			return false;
		}
		return true;
	}
	template<typename T>
	static bool NameList_TestValueValid_( const T& ){
		return true;
	}
	template<typename T>
	static void AddHelper( std::set<T>& values, const T& v ){
		if ( !NameList_TestValueValid_(v) )
			return;
		values.insert(v);
	}
	template<typename T, typename ContT>
	static void AddHelper( ContT& values, const T& v ){
		if ( !NameList_TestValueValid_(v) )
			return;
		if ( std::find(values.begin(), values.end(), v) != values.end() )
			return;
		values.push_back(v);
	}
	template<typename ContT>
	static bool IsInByMatchHelper( const ContT& values, const std::string& v ){
		if (v.empty())
			return false;
		return std::find_if(values.begin(), values.end(), [&v]( const std::string& the_v ){
			return v.find(the_v) != std::string::npos;
		}) != values.end();
	}
	template<typename T, typename ContT>
	static bool IsInByMatchHelper( const ContT& values, const T& v ){
		assert(false);
		return false;
	}

public:
	explicit NameListRef( ContType& values ) : values_(values){}
	NameListRef& operator = (const NameListRef&) = delete;
	NameListRef(const NameListRef&) = delete;
	void Add( const ValueType& v ){
		AddHelper(values_, v);
	}
	template<typename TheContT_>
	void AddSome( const TheContT_& values ){
		for ( auto& v : values )
			Add(v);
	}
	void Delete( const ValueType& v ){
		auto it = std::find(values_.begin(), values_.end(), v);
		if ( it != values_.end() )
			values_.erase(it);
	}
	void clear(){
		values_.clear();
	}
	bool IsIn( const ValueType& v ) const{
		return std::find(values_.begin(), values_.end(), v) != values_.end();
	}
	//ģ��ƥ��
	bool IsInByMatch( const ValueType& v ) const{
		return IsInByMatchHelper(values_, v);
	}
	template<typename Func_>
	bool IsInBy( const Func_& func ){
		return std::find_if(values_.begin(), values_.end(), func) != values_.end();
	}
	template<typename Func_>
	const ValueType* FindBy( const Func_& func ) const{
		auto it = std::find_if(values_.begin(), values_.end(), func);
		if ( it == values_.end() )
			return nullptr;
		return &*it;
	}
	const ContType& GetValues() const{
		return values_;
	}
	ContType& GetValues(){
		return values_;
	}
	int size() const{
		return (int)values_.size();
	}
	bool empty() const{
		return values_.empty();
	}
	const_iterator begin() const{
		return values_.begin();
	}
	iterator begin(){
		return values_.begin();
	}
	const_iterator end() const{
		return values_.end();
	}
	iterator end(){
		return values_.end();
	}

protected:
	ContType&		values_;
};
template<typename ContT_>
NameListRef<ContT_> MakeNameListRef( ContT_& values ){
	return NameListRef<ContT_>(values);
}

template<typename ValueT_, typename ContT_ = std::set<ValueT_> >
class NameList : public NameListRef<ContT_>{
public:
	NameList() : NameListRef<ContT_>(values_holder_){}
	NameList(const NameList& rhs) : NameListRef(values_holder_), values_holder_(rhs.values_holder_){}
	NameList& operator = (const NameList& rhs){
		values_holder_ = rhs.values_holder_;
		return *this;
	}

protected:
	ContType		values_holder_;
};

//����ָ�����ַ���������
class RandomCombineStr{
public:
	typedef NameList<std::string, std::vector<std::string> > StrT;
	typedef boost::optional<const std::string&> OptionalString;

public:
	RandomCombineStr();
	pt_dword GetMaxLen() const{ return max_len_; }
	pt_dword GetMinLen() const{ return min_len_; }
	static void RegForLua(lua_State* l);
	static RandomCombineStr& GetDefMe();

	//setting
public:
	//������Ϻ�����ַ������С����
	void SetTotalLen_MinMax( int min_len, int max_len );
	//����ǰ׺�ַ����ּ���
	void SetOccurRate_Pre( double rate_pre );
	//���ü���ַ����ּ���
	void SetOccurRate_Middle( double rate_middle );
	//���ú�׺�ַ����ּ���
	void SetOccurRate_Suffix( double rate_suffix );

	//���
public:
	//���ǰ׺�ַ�
	void AddStr_Pre( const std::string& str_pre );
	void AddSomeStr_Pre( const std::string& str_some_pre );
	//��Ӽ���ַ�
	void AddStr_Middle( const std::string& str_middle );
	void AddSomeStr_Middle( const std::string& str_some_middle );
	//��Ӻ�׺�ַ�
	void AddStr_Suffix( const std::string& str_suffix );
	void AddSomeStr_Suffix( const std::string& str_some_suffix );
	//�������ַ�
	void AddRandomStr( const std::string& str_random );
	void AddSomeRandomStr( const std::string& str_some_random );
	//����������ݣ������������ַ�������
	void ClearAllData();

	//����
public:
	//��һ���ַ����Ļ������������һ���������Ҫ����ȫ�µģ�str_baseΪ�ռ���
	std::string GenRandomStr( const std::string& str_base ) const;

private:
	static std::vector<std::string> SeparateTheStr( const std::string& the_str );
	static const std::string& GetRandomOneStrBy( const StrT& strs );
	static std::string GetRandomSomeStrBy(const StrT& strs, OptionalString str_middle, pt_dword max_char_size);
	static std::string FilterValidStr( const std::string& str );

private:
	StrT			strs_pre_;
	StrT			strs_middle_;
	StrT			strs_suffix_;
	StrT			strs_random_;

private:
	pt_dword		max_len_;
	pt_dword		min_len_;
	double			occur_rate_pre_;
	double			occur_rate_middle_;
	double			occur_rate_suffix_;
};

class CookieHelper : public Singleton<CookieHelper, Singleton_MakeMe>{
public:
	//���������
	CookieHelper() = delete;
	const std::string& GetCookie( const std::string& whose );
	bool UpdateCookie( const std::string& whose, const std::string& new_cookie );

private:
	std::map<std::string, std::string>		cookies_;
};

class LocalInfo{
public:
	//������
	static std::string GetTheMachineCode();
	//�õ�cookieֵ
	static std::string GetTheCookie(const std::string& whose);
	//����cookie
	static void SetNewCookie(const std::string& whose, const std::string& str_cookie);

private:
	static const std::string& GetMachineCodeSysFileInfo();

private:
	static const wchar_t*const kCookieFileName;
};
