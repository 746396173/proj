#pragma once
/*
@author zhp
@date 2016/4/17 18:38
@purpose ���Դ�һ�������������ú���
*/
#include "BC_Stream.h"
#include "BC_Function.h"
#include "BC_Size.h"
#include <vector>
#include "Detail/BC_Class.h"
#include "../DependSelfLib.h"

//////////////////////////////////////////////////////////////////////////
//��������������
BC_AsStreamW BC_MakeP( pt_csz function_name );
//�������ã���������
template<typename ContT>
BC_Cont<const ContT&> BC_MakeCont( const ContT& cont );
//�������ã����������ַ����Ķ�����
template<typename T>
inline auto BC_MakeArray(const T& v) -> decltype(Detail::BC_MakeArrayImpl<T>::get(v)){
	return Detail::BC_MakeArrayImpl<T>::get(v);
}
//���հ��еĲ�����
template<typename ContT>
struct BC_Cont;
/*
@remark��std::array<T, size>ֻ�ɵ�������ʹ�ã�������Ԫ�ز������ַ�����tuple�ȿɱ䳤�����͡���������ռ�ڴ�������ʱ��ռ�ڴ�һ�¡�
std::array<T, size>Ҳ��һ������������BC_Cont��
BC_Cont�е�Ԫ�ؿ���������ϡ�
tuple�����CMN_ARITY_MAX+1��������ͨ��BC_MakeFunction��ӵĺ��������CMN_ARITY_MAX+1��������
Ĭ��֧��std::vector<T, AllocT>����ʹ��vector��������BC_Cont<std::vector<T, AllocT> >����ʽ��
֧�����б�׼������������vector�������������BC_Cont<ContainerType>����ʽ��װһ�¡�Ҳ֧���Զ���������Ҫ������������value_type������������Ҳ������push_back������
Ĭ��ֱ��֧�ֵĸ���������std::bitset��std::array��std::vector��std::tuple��std::pair��std::basic_string��ATL::CStringT��Json::Value��DateTimeLocal�����顢��/խ�ַ���������
Ĭ��֧�ֵļ�����ΪC++�����ڽ����ͣ�����Ϊ�з������޷��ţ�֧������ö�����͡�
���ڲ����������ó������õ���ʽȥ�������������Լ��ٲ���Ҫ�ĸ��Ʋ�����������vector��
������const char*��const wchar_t*����ʽȥ����std::basic_string��ATL::CStringT����
�������ַ�������������const char[]/const wchar_t[]���ַ�������ʽ���������ͳ��ַ������������뱻���ͳ����飬�����std::array����BC_MakeArray��װһ�¡�
ע����ͳ�Ա������Ҫ�õ��������꣺BC_REG_CLS_DECLARE��BC_REG_CLS_DEFINE��
֧��POD�������ͣ���Ҫͨ��BC_DEFINE_POD������POD�ṹ�塣
֧���Զ������ͣ���������Ҫ�������ĳ�Ա������/ *
template<class Archive>
void serialize(Archive & ar){
	ar
	& member1
	& member2
	& member3;
}
* /
��û��serialize��Ա����������Ҫoperator <<��operator >>��������
֧����֤���ȣ�������꣺BC_CHECK_SIZE��Ҳ֧���Զ�����֤��ȥ�ο�BC_Check_Size��ʵ�֡�
*/
//////////////////////////////////////////////////////////////////////////
#define BC_DEFINE_POD(struct_name)	\
	struct struct_name;	\
	BUFCALL_TYPE_TO_STRING(struct_name);	\
	template<typename Policy>	\
	struct BC_TypeConverter_0<struct_name, Policy> : BC_TypeConverter_POD_Base<struct_name, Policy>{};	\
	struct struct_name
/**/
#define BC_REG_CLS_DECLARE(cls) private:	\
static void _Fn_Reg_##cls##_();	\
static const bufcall::BC_RegClassImpl g_reg_##cls##_
/**/
//ע���Ա����
#define BC_REG_CLS_DEFINE(cls) const bufcall::BC_RegClassImpl cls::g_reg_##cls##_ = &cls::_Fn_Reg_##cls##_;	\
void cls::_Fn_Reg_##cls##_()
/**/
//��֤���ȣ�����֤�����ͣ��ַ�����std::basic_string��ATL::CStringT��std::vector��BC_Cont<ContT>
#define BC_CHECK_SIZE(cls, max_size, min_size)	BC_Check<BC_Check_Size<cls, max_size, min_size> >
/**/

/*���൥���ã���ɵ�������/����ʹ��*/
class BC_BufDecode : public BC_BufClassRuntimeInfo{
public:
	BC_BufDecode();

public:
	bool Decode( BC_AsStreamR& call_info ) const;
	bool Decode( pt_pcvoid buffer, pt_dword buffer_size ) const;

	//��չ��ȥ����
protected:
	//���ܻ��׳��쳣
	virtual bool OnCallImpl( pt_csz function_name, const BC_Function& function, BC_AsStreamR& params_buf, std::string* err_info ) const;

private:
	mutable boost::optional<const bufcall::ClassProxy*>	cls_proxy_;
};

//�����׳��쳣
class BC_BufCallBase : public BC_BufDecode{
public:
	//Զ�̵���
	virtual bool ToCall( const BC_AsStreamW& stm ) = 0;
	//ͬ��Զ�̵���
	virtual bool ToCallSync(const BC_AsStreamW& stm, boost::optional<bool>& oper_res);

protected:
	//�����׳��쳣
	virtual bool OnCallImpl( pt_csz function_name, const BC_Function& function, BC_AsStreamR& params_buf, std::string* err_info ) const override;
};

//���׳��쳣
class BC_BufCallBase_Except : public BC_BufCallBase{
private:
	//���׳��쳣
	bool OnCallImpl( pt_csz function_name, const BC_Function& function, BC_AsStreamR& params_buf, std::string* err_info ) const override;
};