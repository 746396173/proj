#pragma once
/*
@author zhp
@date 2017/5/17 13:25
@purpose for rtti
*/
#include <ProtocolX/P_BaseTypeX.h>
#include <typeinfo.h>
#include <functional>
#include <string>
#include "../DependSelfLib.h"

namespace StdEx{
	class RttiEx{
	public:
		typedef std::function<bool(const std::type_info&)> Fn_TraClassHierarchy;

	public:
		static const std::type_info* TypeId(pt_pcvoid obj_addr);
		static const std::type_info* VtblTypeId(pt_pcvoid vtbl);
		static pt_csz TypeName(pt_pcvoid obj_addr);
		static pt_csz VtblTypeName(pt_pcvoid vtbl);
		static pt_csz TypeFullName(pt_pcvoid obj_addr);
		static pt_csz VtblTypeFullName(pt_pcvoid vtbl);
		static pt_csz TypeRawName(pt_pcvoid obj_addr);
		static pt_csz VtblTypeRawName(pt_pcvoid vtbl);
		static int TraBaseClass(pt_pcvoid obj_addr, const Fn_TraClassHierarchy& fn);
		static int VtblTraBaseClass(pt_pcvoid vtbl, const Fn_TraClassHierarchy& fn);
		static pt_csz Name2ShortName(pt_csz full_name);
		static std::string UnDName(pt_csz symbol_name);

	private:
		struct PMD{
			//��������ݿ�ʼλ������ڶ���ʼλ�õ�ƫ�ơ��ݹ۲죬�����Ĵ��ֶ�һ��Ϊ0���������������ֶο�ȡ��׼ȷ��ƫ�ơ����������ô��ֶ�ȡƫ�ơ�
			int				mdisp;		//member displacement
			//����������ڶ���ʼλ�õ�ƫ�ơ�����û�в�������̳У������Ķ���Ҳû��ָ�������������ָ�룬��ʱ��pdispһ��Ϊ-1��
			int				pdisp;		//vbtable displacement
			/*
			��pdispΪ�Ǹ�����˵���������������������¼��ÿһ����������������ڶ���ʼλ�õ�ƫ�ơ�
			vdisp���¼����һ��������Ӧ���������һ���ֵΪһ���������������ʼλ�õ�ƫ�ơ�
			����ͨ���������ʼλ�ú�pdsip�ҵ��������λ�ã���ͨ����������ʼλ�ú�vdisp�ҵ��û�������ݵ�λ�á�
			*/
			int				vdisp;		//displacement inside vbtable
		};
		struct TypeDescriptor{
			const std::type_info& AsTypeInfo() const;

			pt_dword		ptrToVTable;
			pt_dword		spare;
			char			name[1];
		};
		static_assert(sizeof(TypeDescriptor) == sizeof(type_info), "");
		struct RTTIBaseClassDescriptor{
			// ָ��type_info����
			TypeDescriptor*							pTypeDescriptor;		//type descriptor of the class
			// �û����������������ĸ���
			pt_dword								numContainedBases;		//number of nested classes following in the Base Class Array
			// �����û���ĳ�Ա�ڶ����е�λ�� 
			PMD										where;					//pointer-to-member displacement info
			// ����
			pt_dword								attributes;				//flags, usually 0
			struct RTTIClassHierarchyDescriptor*	pClassDescriptor;		//���ϵ������о�Ȼû������ֶΣ���
		};
		struct RTTIBaseClassArray{
			RTTIBaseClassDescriptor* arrayOfBaseClassDescriptors[1];
		};
		struct RTTIClassHierarchyDescriptor{
			pt_dword				signature;					//always zero?
			// ���ԣ���λ�� 
			pt_dword				attributes;					//bit 0 set = multiple inheritance, bit 1 set = virtual inheritance
			// ����ĸ���
			pt_dword				numBaseClasses;				//number of classes in pBaseClassArray
			// ָ���������ṹ���ʵ��
			RTTIBaseClassArray*		pBaseClassArray;
		};
		struct RTTICompleteObjectLocator{
			// ���ʵ���˼��ǩ������ʵ�����ƺ�����Ϊ0 
			pt_dword						signature;			//always zero ?
			// ����������ڶ���ʼ��ƫ����(һ������ȡ���������ָ��)
			pt_dword						offset;				//offset of this vtable in the complete class
			/*
			 cdOffset��Ҫ����ʹ��������ʱ�򡣵�������д���������麯��ʱ������һ��������������������
			 �������ڹ��������ڴ沼��ʱ��Ϊÿһ������ಿ�ֶ�����һ������vtordisp�ĳ�Ա����ô���vtordisp�Ǹ�ʲô���أ�
			 vtordisp������һ��ƫ�ƣ�ͨ����������ݵ���ʼ��ַ��offsetȡ�������ʼ��ַ�󣬻���Ҫ��vtordisp��ֵ��������ȷ�Ķ�����ʼ��ַ��
			 cdOffsetָ���˴������������ʼ��ַ��ǰ��ע����������ǰ��ƫ�ƶ���λ����ȡ��vtordisp����cdOffsetΪ0����û�����������������ʱ�Ͳ����ټ���vtordisp��
			 ��������ֶ����ײ�������������������⣬�����ں�������������Ƕ�û����vtordisp��cdOffset����0��
			 */
			pt_dword						cdOffset;			//constructor displacement offset
			// ָ��һ��type_info����
			TypeDescriptor*					pTypeDescriptor;	//TypeDescriptor of the complete class
			// ������ļ̳���Ϣ
			RTTIClassHierarchyDescriptor*	pClassDescriptor;	//describes inheritance hierarchy
		};

	private:
		static void* RTCastToVoid(void* inptr);
		static void* RTtypeid(void* inptr);
		static void* RTDynamicCast(void* inptr, long VfDelta, void* SrcType, void* TargetType, bool isReference);

	private:
		static const RTTICompleteObjectLocator* GetCompleteObjectLocator(pt_pcvoid vtbl);
	};
}
