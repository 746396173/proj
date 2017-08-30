#pragma once
/*
@author zhp
@date 2014-1-04
@purpose �������������Ϸ�е�һЩ���͡��ṹ��
*/
#include "GAddr.h"
#include <Common/BinaryStream.h>
#include <set>
#include <json/value.h>
#include <Communicate/CG_Defines.h>
#include <map>
#include <Common/CmnUuid.h>

namespace GType{
	class GameSendSocket;
	
	enum enHitType{
		kHT_Unknown = 1,
	};
	typedef char (GameSkillObjT)[JFZR_REVERSAL_SKILL_OBJ_SIZE___];
	struct GameSkillObjPtr{
	private:
		GameSkillObjPtr();
	public:
		GameSkillObjT*			skill_begin_addr_;
		GameSkillObjT*			skill_end_addr_;
	};
	struct stDirection2d{
		WORD				dir_x_;
		WORD				dir_y_;

		stDirection2d(){
			dir_x_ = 0;
			dir_y_ = 0;
		}
		friend StrOutputBStream&
			operator << ( StrOutputBStream& ostm, const stDirection2d& dir ){
				ostm << dir.dir_x_ << dir.dir_y_;
				return ostm;
		}
	};
	//��Ϸ�е�����
	struct stGameVector{
		float			x_;
		float			z_;
		float			y_;

		stGameVector(){
			x_ = 0.;
			z_ = 0.;
			y_ = 0.;
		}
		stGameVector( float x, float y, float z ){
			x_ = x;
			y_ = y;
			z_ = z;
		}
		float GetPosX() const{
			return x_;
		}
		void SetPosX( float x ){
			x_ = x;
		}
		float GetPosY() const{
			return y_;
		}
		void SetPosY( float y ){
			y_ = y;
		}
		float GetPosZ() const{
			return z_;
		}
		void SetPosZ( float z ){
			z_ = z;
		}
		void FromDirection( const stDirection2d& direction ){
			x_ = direction.dir_x_;
			y_ = direction.dir_y_;
			z_ = 0.;
		}
		friend StrOutputBStream&
			operator << ( StrOutputBStream& ostm, const stGameVector& vec ){
				ostm << vec.x_ << vec.z_ << vec.y_;
			return ostm;
		}
	};
	static_assert(sizeof(stGameVector) == sizeof(XYZ), "");

	//װ����λ
	enum enEquipPart{
		kEP_Weapon = 0,		//����������ʿ������MAIN_WEAPON_Warrior,��ħʦ������MAIN_WEAPON_MagicGunner,������������MAIN_WEAPON_Thief
		kEP_Head,			//ͷ��
		kEP_Upper,			//�ϰ���
		kEP_Lower,			//�°���
		kEP_Hand,			//�ֲ�
		kEP_Foot,			//�㲿
		kEP_Necklace,		//����
		kEP_Earring,		//����
		kEP_Ring = 8,		//��ָ
		//������ʱװ,avatar
		kEP_A_Face,			//���
		kEP_A_Neck,			//�������ϵ�
		kEP_A_Back,			//�����ϵģ������
		kEP_A_Lower,		//����ģ�������
		kEP_A_Head,			//ͷ��
		kEP_A_HasNo = 14,	//�����ֵ��Ϸ��δ�õ�
		kEP_A_Hand,			//�������ϵ�
		kEP_Unknonw,
		kEP_Invalid,		//��Ч��λ
	};

	//��Ʒ������
	enum enTabCategory{
		kTC_Normal = 0,		//��ͨ��
		kTC_Consume,		//����Ʒ��
		kTC_Task,			//������
		kTC_Material,		//������
		kTC_Avatar,			//ʱװ1,2,3(�����)
		//��������Ϸ�еĶ�Ӧ����������Լ������
		kTC_Equiped,		//װ�����������ϵ�
		kTC_AvatarEquiped,	//ʱװ(�����)���������ϵ�
		kTC_Invalid
	};

	//ְҵ����
	enum enJobCategory{
		kJC_JianDouShi = 1,		//����ʿ,WARRIOR
		kJC_RenWuZhe = 2,		//������,THIEF
		kJC_ZhanKuang,			//ն��,GLADIBERSERKER
		kJC_QuanSha,			//ȭɲ,GIGONGSA
		kJC_FengWuXing,			//������,RIPPER
		kJC_LieRenXing,			//������,ASSASSIN
		kJC_TianLangXing,		//������,MISTRESSOFFENRIR
		kJC_JianMo,				//��ħ,DOOMBLADE
		kJC_KongMoShi = 9,		//��ħʦ,MAGICGUNNER
		kJC_MoYingShi,			//ħӰʦ,DARKSTALKER
		kJC_ShiKongShuShi,		//ʱ����ʿ,ARCHITECT
		kJC_ShuangYuZhe,		//˪����,ICEMAGICIAN
		//���Ѻ�ְҵ
		kJC_LuanZhan = 13,		//��ս,F_SCYTHE_00
		kJC_XiXueYaoHua,		//��Ѫ����,F_SCYTHE_01
		kJC_XieHunShuShi,		//а����ʿ,F_SCYTHE_02
		kJC_KuLuoSha,			//����ɲ,F_SCYTHE_03
		kJC_Any,				//����ְҵ����ռλ��������
		kJC_Invalid,
	};

	//�����Ѷ�
	enum enFbDifficulty{
		kFD_Zero = 0,			//�����У�����ȼ�Ϊ0
		kFD_Normal,				//��ͨ
		kFD_Fight,				//��ս
		kFD_Master,				//��ʦ
		kFD_Overmaster,			//����
		kFD_OrangeFb = 9,			//�ȱ�
		kFD_Invalid,
	};
	//�������
	enum enTaskCategory{
		kTC_InvalidBegin,
		kTC_Normal_KillMonster = 4,	//��ͨ����֮����ɱ������
		kTC_Main,					//��������
		kTC_CollectMaterial,		//��ͨ����֮�ռ���������
		kTC_InvalidEnd,
	};
	//��Ϸ״̬
	enum enGameState{
		kGS_Invalid = 0,
		kGS_SelectChannel,
		kGS_SelectRole,
		kGS_InGame,			//��ɫ�ѽ�����Ϸ
	};
	//��Ʒ�ȼ�����ƷƷ��
	enum enItemQuality{
		kIQ_Invalid = 0,
		kIQ_Low,
		kIQ_Middle,
		kIQ_High,
		kIQ_Rare,		//������
		kIQ_Legendary,	//��˵��
	};
	//��Ϸ�е���ƷƷ�ʣ���ֵ����Ϸ�е�һ��
	enum enItemQualityOfGame{
		kIQOG_Low = 1,
		kIQOG_Middle = 1 << 1,
		kIQOG_High = 1 << 2,
		kIQOG_Rare = 1 << 3,
		kIQOG_Legendary = 1 << 4,
	};
	//��Ʒʹ�����
	enum enItemUsableType{
		kIUT_Identify = 0,		//������
		kIUT_Unseal,			//���ʯ
		kIUT_Invalid,
	};

	struct stProductInfo{
		LONGLONG		serial_;
		LONGLONG		price_;
		int				item_cnt_;

		stProductInfo();
		bool FromJson( const Json::Value& json_v );
		bool ConverToJson( Json::Value& json_v ) const;

		friend bool operator < ( const stProductInfo& lhs, const stProductInfo& rhs ){
			return lhs.serial_ < rhs.serial_;
		}
	};
	typedef std::set<stProductInfo> ProductInfoContT;
	typedef std::map<CmnUuid, ProductInfoContT> RoleProductInfoContT;
	bool IsPrivateProduct( LONGLONG price );
	enGameAcType Price2GameAcType( LONGLONG price );
	LONGLONG MakePriceByAcType( LONGLONG price, enGameAcType game_ac_type );
}