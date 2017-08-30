#pragma once
/*
@author zhp
@date 2017/1/24 17:22
*/
#include <ProtocolX/P_DefinesX.h>
#include <cstddef>
#include "CD_Serialize.hpp"

#pragma pack(push)
#pragma pack(1)

//////////////////////////////////////////////////////////////////////////
enum CD_enMsgIdR : pt_word{
	kMIR_Invalid = 0,			//��Ч��ϢID����ռλ��������
#ifdef VER_GJ3_
	kMIR_PromptInfo = 0xb,
	kMIR_PreGamePromptInfo = 0xd,
	kMIR_OnNpcPanelInfo = 0x43,
	kMIR_OnItem = 0x69,
	kMIR_OnMove = 0xdb,
	kMIR_UseSkillEffectAtPos = 0xdc,
	kMIR_SkillUsing = 0xdd,
	kMIR_UseSkillEnd = 0xde,
	kMIR_EffectToEntity = 0xdf,
	kMIR_NormalHitted = 0xe0,
	kMIR_OnHpMp = 0xe1,
#elif VER_GJ_
	kMIR_PromptInfo = 0xa,
	kMIR_PreGamePromptInfo = 0xd,
	kMIR_OnNpcPanelInfo = 0x41,
	kMIR_OnItem = 0x67,
	kMIR_OnMove = 0xd8,
	kMIR_UseSkillEffectAtPos = 0xd9,
	kMIR_SkillUsing = 0xda,
	kMIR_UseSkillEnd = 0xdb,
	kMIR_EffectToEntity = 0xdc,
	kMIR_NormalHitted = 0xdd,
	kMIR_OnHpMp = 0xde,
#else
	kMIR_PreGamePromptInfo = 0xd,
	kMIR_PromptInfo = 0xf,
	kMIR_OnNpcPanelInfo = 0x47,
	kMIR_OnHpMp = 0xe5,
	kMIR_OnItem = 0x6d,

	//���ظ���
	kMIR_OnMove = 0xda,
	kMIR_UseSkillEffectAtPos = 0xdb,
	kMIR_SkillUsing = 0xdc,
	kMIR_UseSkillEnd = 0xdd,
	kMIR_EffectToEntity = 0xde,
	kMIR_NormalHitted = 0xdf,
#endif
};
//////////////////////////////////////////////////////////////////////////
struct stCDGR_PromptInfo : stCD_GameMsgBase{
	typedef GameVector<int> VecValues;

	pt_word			prompt_id_;
	p_mem_placeholder(2);		//short,=-1
	p_mem_placeholder(1);		//byte
	p_mem_placeholder(3);
	p_mem_placeholder(4 * 4);
	VecValues		values_;
	
	//ʣ���������
	int GetRemaining() const;
};
static_assert(0x20 == offsetof(stCDGR_PromptInfo, values_), "");

struct stCDR_PromptInfo : stCDR_MsgBase<kMIR_PromptInfo, false>{
	enum enPromptId : pt_word{
#ifdef VER_GJ3_
		kNameUsed = 0xd,						//�˽�ɫ�����ѱ�ʹ�ã�����̫����������ʹ�õ�ID��һ����
		kNameTooShort = 0xd,					//���ƹ���
		kMIR_YouEntered = 0x76,					//���ѽ��룺xxx
		kNotIdentified = 0x84,					//Ŀ����Ʒ��δ������δ����
		kRemaining = 0x98,						//ʣ���������
		kRoleDie = 0xb1,						//��ɫ����
		kItemDestroyed = 0xcf,					//�����ѡȡ����Ʒ�ݻ�
		kCannotUseItemAtTown = 0x112,			//�ڳ����޷�ʹ�ô���Ʒ
		kLeaveModeClose = 0x16a,				//����ģʽ�رգ�δ����
		kNameMinGan = 0x17f,					//����������ݰ������дʻ㣬δ����
#elif VER_GJ_
		kNameUsed = 0xd,						//�˽�ɫ�����ѱ�ʹ�ã�����̫����������ʹ�õ�ID��һ����
		kNameTooShort = 0xd,					//���ƹ���
		kMIR_YouEntered = 0x76,					//���ѽ��룺xxx
		kNotIdentified = 0x84,					//Ŀ����Ʒ��δ������δ����
		kRoleDie = 0xb3,						//��ɫ����
		kItemDestroyed = 0xe3,					//�����ѡȡ����Ʒ�ݻ�
		kCannotUseItemAtTown = 0x112,			//�ڳ����޷�ʹ�ô���Ʒ
		kLeaveModeClose = 0x16a,				//����ģʽ�رգ�δ����
		kNameMinGan = 0x17f,					//����������ݰ������дʻ㣬δ����
#else
		kNameUsed = 0x15,						//�˽�ɫ�����ѱ�ʹ��
		kNameTooShort = 0x17,					//���ƹ���
		kMIR_YouEntered = 0x76,					//���ѽ��룺xxx
		kNotIdentified = 0x84,					//Ŀ����Ʒ��δ����
		kRemaining = 0x98,						//ʣ���������
		kRoleDie = 0xb1,						//��ɫ����
		kItemDestroyed = 0xcf,					//�����ѡȡ����Ʒ�ݻ�
		kCannotUseItemAtTown = 0x112,			//�ڳ����޷�ʹ�ô���Ʒ
		kLeaveModeClose = 0x16a,				//����ģʽ�ر�
		kNameMinGan = 0x17f,					//����������ݰ������дʻ�
#endif
	};
	stCDR_PromptInfo();
	template<class Archive>
	void serialize(Archive& ar){
		ar & prompt_id_;
	}

	enPromptId		prompt_id_;
	short			ukn_s_;			//-1
	pt_byte			ukn_flag_;		//kCannotUseItemAtTownʱ=2
	pt_dword		ukn_dw_;		//kCannotUseItemAtTownʱ=0
};

struct stCDR_PreGamePromptInfo : stCDR_MsgBase<kMIR_PreGamePromptInfo, true>{
	enum enPromptId : pt_word{
		kNameUsed = 0x15,						//�˽�ɫ�����ѱ�ʹ��
		kNameMinGan = 0x16,						//����������ݰ�����Ч�ַ�
		kNameTooShort = 0x17,					//���ƹ���
	};
	stCDR_PreGamePromptInfo();
	template<class Archive>
	void serialize(Archive& ar){
		ar & prompt_id_ & flag_;
	}

	enPromptId		prompt_id_;
	pt_byte			flag_;			//��½����0������Ϸ����-1
};

//������Ʒ�������յ����������İ�����С�ǲ�һ����
//������Ʒ�������յ����������İ�����С�ǲ�һ����
//������Ʒ���յ�һ�������İ�����С89
struct stCDR_OnItem : stCDR_MsgBase<kMIR_OnItem, false>{
	template<class Archive>
	void serialize(Archive& ar){}
};

//npc�����Ϣ�������NPC������ٻᡢ������������ĳ��MenuItem��
struct stCDR_NpcPanelInfo : stCDR_MsgBase<kMIR_OnNpcPanelInfo, false>{
	template<class Archive>
	void serialize(Archive& ar){}
};

//////////////////////////////////////////////////////////////////////////
//���۹���Լ�������������ҡ����缼��Ҳ�ᷢ����������������Ҳ�ᷢ�����
//����������ƶ�����Ҳ��ʹ�ü��ܵİ�����Ϊ�ƶ�Ҳ�Ǽ��ܵ�һ�֡�
struct stCDR_OnMove : stCDR_MsgBase<kMIR_OnMove, false>{
	stCD_EntityMsgInfo				entity_msg_;
	enCD_TouchTargetSmallFlag		flag_;		//=8�����<=0�Ļ������ٶ��ȡ�����ֶΣ�һ�㶼�Ǵ���0�ģ�û������С�ڵ���0�������
	pt_dword						ukn_;		//=0x148,�������ܵ�
	pt_dword						ukn2_;		//=0x17f,�������ܵ�
	pt_dword						ukn3_;		//=0x164,�������ܵ�
	pt_dword						ukn4_;		//=0x18b,�������ܵ�
	pt_word							skill_id_;	//0x4000
	pt_word							skill_entity_id_;		//=0x82a2���²��Ǹ������йص�һ��id��
};

struct stCDGR_OnMove : stCD_GameEntityMsg{
	stCDGR_OnMove();

	pt_dword			ukn_zero_;				//ֱ�Ӿͳ�ʼ��Ϊ0�ˣ�������ͨ����ȡ������0�ġ�
	stCD_VecInt			pos_dst_;				//$18
	stCD_VecInt			pos_src_;				//$20
	pt_word				skill_id_;				//$28����·ʱ����2909������·�ļ���id
	pt_word				ukn_;					//���������ʹ�ü��ܵĴ�����ÿʹ�ôμ��ܼ�1
	enCD_TouchTargetSmallFlag		flag_;		//=8��$2c,���<=0��һ����-8���Ļ������ٶ��ȡ�����ֶΣ�һ�㶼�Ǵ���0�ģ�û������С�ڵ���0�������
	p_mem_placeholder(0x50);					//������δȻ
};
static_assert(0x18 == offsetof(stCDGR_OnMove, pos_dst_), "");
static_assert(0x28 == offsetof(stCDGR_OnMove, skill_id_), "");
static_assert(0x2c == offsetof(stCDGR_OnMove, flag_), "");

//ʹ��һ�μ��ܣ�ֻ�ᷢһ�Σ��������Ƿ��ż����š�ÿ�����ܶ��ᷢ��������0xe0���ġ�
//�����ƶ�Ҳ�����������С10
//ʹ�ü��ܵ�ĳ���ط�ʱ���������Զ��������һ������ľ��룬�Ա�ʩ�Ÿü��ܡ�
//ʩ�ŵļ��ܣ�ֻ����ʾʩ�ŵ�Ч��/��Ч
//�����Է�ʱ����ͨ��stCDR_OnMove�ƶ����Է���Ȼ���յ��ð���ʾʩ�Ŵ˼���
//�����Ҳ����ֹ���ܵ����ã���Ϊ����������Ļ�����һֱ������ʩ�ż��ܵ�Ч����
struct stCDR_UseSkillEffectAtPos : stCDR_MsgBase<kMIR_UseSkillEffectAtPos, false>{
	stCD_EntityMsgInfo	info_;

	template<class Archive>
	void serialize(Archive& ar){
		ar & info_.entity_id_ & info_.dst_entity_id_ & info_.flag_;
	}
};
static_assert(10 == sizeof(stCDR_UseSkillEffectAtPos), "");

//e0��db��ÿ�����ܶ����յ��ġ���С20
struct stCDR_OnHpMp : stCDR_MsgBase<kMIR_OnHpMp, true>{
	enum enValueType : pt_byte{
		kVT_Hp = 0,
		kVT_Mp,
		kVT_Shield,		//��������
	};
	stCDR_OnHpMp();
	bool IsDied() const;
	template<class Archive>
	void serialize(Archive& ar){
		ar & info_.entity_id_ & info_.dst_entity_id_ & info_.flag_
			& cur_value_ & ukn2_ & value_type_ & ukn_b1_;
	}

	stCD_EntityMsgInfo		info_;
	pt_dword				cur_value_;			//��ǰ������Ѫ����Ϣ�����������ֶ�����ʶ��������
	pt_dword				ukn2_;				//һֱ����0������������ʱҲΪ0
	enValueType				value_type_;		//Ѫֵ=0����=1
	pt_byte					ukn_b1_;			//һֱ����0��������û������
};
static_assert(20 == sizeof(stCDR_OnHpMp), "");

struct stCDR_UseSkillIng : stCDR_MsgBase<kMIR_SkillUsing, false>{

};

//ʹ��һ�μ��ܣ�ֻ�ᷢһ�Σ��������Ƿ��ż����š��еļ��ܲŷ����������һ����
struct stCDR_UseSkillEnd : stCDR_MsgBase<kMIR_UseSkillEnd, false>{

};

//��ɫ������ܵ��˺������յ����������С�����Ϊ29���е�Ϊ31��
//���return��������Ĵ�����ô������ʱ��û�и���Ч�ˡ�
struct stCDR_EffectToEntity : stCDR_MsgBase<kMIR_EffectToEntity, false>{
	struct stCDR_DamageUkn{
		pt_word		ukn_dw_;		//0x8107,0x816a
		pt_byte		ukn_b_;			//=0,=2
		pt_byte		ukn_b1_;		//=0
		pt_dword	dst_entity_id_;		//Ŀ��ʵ��id����������
		//��Ӧ���Ǹ�����Ϣid�����ݸ�ֵ��������ȡ���ĺ��������
		pt_word		sub_msg_flag_;	//0x201,�������ֵ��shr 0xa��Ȼ���ж��Ƿ�Ϊ1�����Ϊ1�����ȡ�����word����������
		//���滹�����ݣ���������Ϣid�������ġ�
		char		ukn_[0x1c];
	};

	pt_dword			src_entity_id_;		//�˺��ߣ�����˵ʩ�ż��ܵ���
	pt_dword			ukn_dw1_;		//0xd4,0x80000119
	pt_word				ukn_w_;			//0x7002
	stCDR_DamageUkn		ukn_;
};

//�ܵ�����ͨ��������ʱ��ͻ�����ʾ��������ͨ��������Ҳ���յ����������Ϊ��ʱ��δ���еġ�
//��СΪ19.
//��������ͨ������صģ���ʵ�ǲµ�
struct stCDR_NormalHitted : stCDR_MsgBase<kMIR_NormalHitted, false>{
	stCD_EntityMsgInfo		info_;
	pt_word				ukn_w_;				//0x8131
	pt_byte				ukn_b_;				//=0
	pt_byte				ukn_b1_;			//=0
	pt_dword			dst_entity_id_;		//Ŀ��ʵ��id
	pt_byte				ukn_b2_;			//=1
};
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
#pragma pack(pop)
