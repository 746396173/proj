#pragma once
/*
@author zhp
@date 2014-3-24 21:59
@purpose for regex
*/
#include <string>
#include <map>
#include <boost/optional.hpp>
#include <sstream>
#include <vector>
#include "../DependSelfLib.h"
#include <ProtocolX/P_DefinesX.h>

//regex word replace
class RegexWordReplace{
public:
	//����ԭ�ַ������滻�ַ�����ӳ��
	bool AddMap_Src2Dst_A( const char* str_word_src, const char* str_word_dest );
	bool AddMap_Src2Dst_A( const std::string& str_word_src, const std::string& str_word_dest );
	//ɾ��ԭ�ַ�����ӳ��
	void EraseMap_Src_A( const char* str_word_src );
	void EraseMap_Src_A( const std::string& str_word_src );
	//�����滻
	std::string Replace_A( const char* str_replaced );
	std::string Replace_A( const std::string& str_replaced );
	//find dest string
	const std::wstring* FindDestStr_W( const wchar_t* str_word_src );
	const std::wstring* FindDestStr_W( const std::wstring& str_word_src );
	//�Ƿ�Ϊ��
	bool empty() const;

private:
	//make one regex word
	std::wstring MakeOneRegexWord_W( const std::wstring& str_word_src ) const;

private:
	std::map<std::wstring, std::wstring>			words_map_;
	boost::optional<std::wstring>					str_regex_;
};

//ģʽƥ���ʽ
class MatchPatternFormatter{
public:
	virtual ~MatchPatternFormatter();
	//�����ģʽ��ʽ,��ʶ��ϵ
	virtual void AddSubFormatter( MatchPatternFormatter* sub_formatter );
	//�õ�ģʽ�ַ���
	virtual std::wstring PatternString() const = 0;
	//�����std::ostringstream
	virtual void PatternToOstm( std::wostringstream& ostm ) const = 0;
};

//��ʽ���
class MatchPatternF_Composite : public MatchPatternFormatter{
public:
	virtual void AddSubFormatter( MatchPatternFormatter* sub_formatter );
	virtual std::wstring PatternString() const;
	virtual void PatternToOstm( std::wostringstream& ostm ) const;

private:
	std::vector<MatchPatternFormatter*>				sub_formatters_;
};

//ģʽ�ַ�����ʽ
class MatchPattern_String : public MatchPatternFormatter{
public:
	MatchPattern_String( const std::wstring& pattern_str );
	virtual std::wstring PatternString() const;
	virtual void PatternToOstm( std::wostringstream& ostm ) const;

private:
	std::wstring			pattern_string_;
};

class MatchPattern_RefString : public MatchPatternFormatter{
public:
	MatchPattern_RefString( const std::wstring& pattern_str );
	virtual std::wstring PatternString() const;
	virtual void PatternToOstm( std::wostringstream& ostm ) const;

private:
	const std::wstring&			pattern_string_;
};

//����ȵ����ָ�ʽ
class MatchPattern_Digital : public MatchPatternFormatter{
public:
	MatchPattern_Digital( int digital, pt_dword width = 1, wchar_t fill_char = L' ' );
	virtual std::wstring PatternString() const;
	virtual void PatternToOstm( std::wostringstream& ostm ) const;

private:
	pt_dword				width_;
	wchar_t					fill_char_;
	int						digital_;
};

//��������
class MatchPattern_AnyDigital : public MatchPatternFormatter{
public:
	virtual std::wstring PatternString() const;
	virtual void PatternToOstm( std::wostringstream& ostm ) const;
};