#pragma once
/*
@author zhp
@date 2014-1-04
@purpose �������������Ϸ�е�һЩ���͡��ṹ��
*/
#include "stdafx.h"
#include <CmnMix/Cmn_BinaryStream.h>
#include <CD_CommonFiles/Data/CD_Structs.h>

namespace GType{
	class GameSendSocket;

	enum enHitType{
		kHT_Unknown = 1,
	};
	struct stDirection2d : stCD_Direction2{
		stDirection2d(){
			dir_x = 0;
			dir_y = 0;
		}
		stDirection2d( float x, float y ){
			dir_x = x;
			dir_y = y;
		}
		stDirection2d& operator = (const stCD_Direction2& rhs){
			*(stCD_Direction2*)this = rhs;
			return *this;
		}
		float GetDirX() const{
			return dir_x;
		}
		void SetDirX( float x ){
			dir_x = x;
		}
		float GetDirY() const{
			return dir_y;
		}
		void SetDirY( float y ){
			dir_y = y;
		}
		friend StrOutputBStream&
			operator << ( StrOutputBStream& ostm, const stDirection2d& dir ){
				ostm << dir.dir_x << dir.dir_y;
				return ostm;
		}
	};
	//��Ϸ�е�����
	struct stGameVector3 : stCD_Vector3{
		stGameVector3(){
			fx = 0.;
			fy = 0.;
			fz = 0.;
		}
		stGameVector3( float x, float y, float z ){
			fx = x;
			fy = y;
			fz = z;
		}
		stGameVector3( double x, double y, double z ){
			fx = (float)x;
			fy = (float)y;
			fz = (float)z;
		}
		stGameVector3& operator = (const stCD_Vector3& rhs){
			*(stCD_Vector3*)this = rhs;
			return *this;
		}
		stGameVector3(const stCD_Vector3& rhs){
			*(stCD_Vector3*)this = rhs;
		}
		float GetPosX() const{
			return fx;
		}
		void SetPosX( float x ){
			fx = x;
		}
		float GetPosY() const{
			return fy;
		}
		void SetPosY( float y ){
			fy = y;
		}
		float GetPosZ() const{
			return fz;
		}
		void SetPosZ( float z ){
			fz = z;
		}
		void ConvertToPos(const stCD_PosDirInfo& actor_vec);
		void FromDirection(const stCD_Direction2& direction){
			fx = direction.dir_x;
			fy = direction.dir_y;
			fz = 0.;
		}
		void SetXYZ( float x, float y, float z );
		double Distance3d( const stGameVector3& rhs ) const;
		double Distance3d_ZoomInZ( const stGameVector3& rhs, int zoom_in_z_rate ) const;
		double Distance2d( const stGameVector3& rhs ) const;
		float GetAngleXY() const;
		//��ԭ����ʱ����ת
		void RotateXY_Origin( float angle );
		//xy��������
		float CrossProductXY( const stGameVector3& rhs ) const;
		//xy��ģ
		float ModuleXY() const;
		//�����ļн�
		float IncludedAngleXY( const stGameVector3& rhs ) const;
		void PlusXY( const stGameVector3& rhs );
		bool OriginDistLessThan( const stGameVector3& rhs ) const;
		bool ValueEqual( const stGameVector3& rhs ) const;
		bool FloatAllEqual( const stGameVector3& rhs ) const;
		bool IsXYAllEqual( const stGameVector3& rhs ) const;
		friend stGameVector3 operator + ( const stGameVector3& lhs, const stGameVector3& rhs ){
			stGameVector3 pos(lhs);
			pos.fx += rhs.fx;
			pos.fy += rhs.fy;
			pos.fz += rhs.fz;
			return pos;
		}
		friend stGameVector3 operator - ( const stGameVector3& lhs, const stGameVector3& rhs ){
			stGameVector3 pos(lhs);
			pos.fx -= rhs.fx;
			pos.fy -= rhs.fy;
			pos.fz -= rhs.fz;
			return pos;
		}
		friend StrOutputBStream&
			operator << ( StrOutputBStream& ostm, const stGameVector3& vec ){
				ostm << vec.fx << vec.fy << vec.fz;
				return ostm;
		}
		friend std::ostream&
			operator << ( std::ostream& ostm, const stGameVector3& vec ){
				ostm << "��" << vec.fx << ", " << vec.fy << ", " << vec.fz << "��";
				return ostm;
		}
	};
	struct G_PosDirInfo : stCD_PosDirInfo{
		G_PosDirInfo(const stCD_PosDirInfo& rhs){
			*(stCD_PosDirInfo*)this = rhs;
		}
	};
	const stGameVector3 kVecEmpty;
	//װ����λ����
	enum enEquipPartIndex{
		kEPI_Weapon = 0,		//����
		kEPI_Head,			//ͷ��
		kEPI_Hand,			//�ֲ�
		kEPI_Heart,			//�ز�
		kEPI_Pocket,			//����
		kEPI_Foot,			//�㲿
		kEPI_Ring,			//��ָ
		kEPI_Necklace,		//����
		kEPI_HuShi = 9,		//��ʯ
		kEPI_Invalid,
	};
	
	enum enEquipPartSubType_Defense{
		kEPSTDEF_Head = 1,
		kEPSTDEF_Hand,
		kEPSTDEF_Heart,
		kEPSTDEF_Pocket,
		kEPSTDEF_Foot,
		kEPSTDEF_Invalid,
	};
	enum enEquipPartSubType_Decorate{
		kEPSTDEC_Ring = 1,
		kEPSTDEC_Necklace,
		kEPSTDEC_HuShi = 4,
		kEPSTDEC_Invalid,
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
		kGS_SelectRole,
		kGS_InGame,			//��ɫ�ѽ�����Ϸ
	};
	//UI����
	enum enUiState{
		kUS_StartGame = 0,		//��ʼ��Ϸ��ť
		kUS_OldPlayer,			//����������
		kUS_RandomSkin,			//���Ƥ��������
		kUS_CreateRoleOk,		//������ɰ�ť
		kUS_CreateRoleBt6,		//�����������½�ɫ��ť
		kUS_Invalid,
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
	//////////////////////////////////////////////////////////////////////////
	class GameSkillType;

	/*enum enShopInfoCategory{
		kSIC_LieShouBuJiPin = MMOCLIENT_SHOP_INFO_LIE_SHOU_BU_JI_PIN,				//���Բ���Ʒ
		kSIC_XinShouLieShouEquip = MMOCLIENT_SHOP_INFO_XIN_SHOU_LIE_SHOU_EQUIP,		//��������װ��
		kSIC_DanYaoBuJi = MMOCLIENT_SHOP_INFO_DAN_YAO_BU_JI,						//��ҩ����
		kSIC_GongJianPingTeMai = MMOCLIENT_SHOP_INFO_GONG_JIAN_PING_TE_MAI,			//����ƿ����
		kSIC_EquipRuMenXuKe = MMOCLIENT_SHOP_INFO_RU_MEN_XU_KE,						//���������������
		kSIC_EquipSkill = MMOCLIENT_SHOP_INFO_EQUIP_SKILL,							//��������
		kSIC_LiWei = MMOCLIENT_SHOP_INFO_LI_WEI,									//���ص�����
		kSIC_AiLuMaoGuYong = MMOCLIENT_SHOP_INFO_AI_LU_MAO_GU_YONG,					//��·è��Ӷ
		kSIC_AiLuNongYeTeGong = MMOCLIENT_SHOP_INFO_AI_LU_NONG_YE_TE_GONG,			//��¶ũҵ�ع�
		kSIC_ZhuangYuanBiXuPin = MMOCLIENT_SHOP_INFO_ZHUANG_YUAN_BI_XU_PIN,			//ׯ԰����Ʒ
		kSIC_TeChanShangPin = MMOCLIENT_SHOP_INFO_TE_CAN_SHANG_DIAN,				//�ز���Ʒ
	};*/

	enum enPlayerLineType{
		kPLT_Smooth = 1,		//����
		kPLT_Fine = 2,			//����
		kPLT_Yellow = 3,		//��ɫ��æ
		kPLT_Red = 4,			//��ɫ
		kPLT_Unknown = 5,		//δ֪
	};

	//����ί�еȼ�
	enum enSociatyTaskLvl{
		kSTL_Invalid = 0,
		kSTL_Lvl1 = 0x64,	//MMOCLIENT_REVERSAL_ACCEPT_GONG_HUI_FB_LEVEL1___,
		kSTL_Lvl2 = 0x65,	//MMOCLIENT_REVERSAL_ACCEPT_GONG_HUI_FB_LEVEL2___,
		kSTL_Lvl3 = 0x66,	//MMOCLIENT_REVERSAL_ACCEPT_GONG_HUI_FB_LEVEL3___,
		kSTL_Lvl4 = 0x67,	//MMOCLIENT_REVERSAL_ACCEPT_GONG_HUI_FB_LEVEL4___,
		kSTL_Lvl5 = 0x67,	//MMOCLIENT_REVERSAL_ACCEPT_GONG_HUI_FB_LEVEL5___,
		kSTL_Lvl6 = 0x67,	//MMOCLIENT_REVERSAL_ACCEPT_GONG_HUI_FB_LEVEL6___,
	};
	struct stSociatyTaskLvlMap{
		const char*			task_lvl_name_;
		enSociatyTaskLvl	task_lvl_;
	};
	const stSociatyTaskLvlMap g_sociaty_task_name2lvl[] = {
		{ "ί��*", kSTL_Lvl1 },
		{ "ί��**", kSTL_Lvl2 },
		{ "ί��***", kSTL_Lvl3 },
		{ "ί��****", kSTL_Lvl4 },
		{ "ί��*****", kSTL_Lvl5 },
		{ "ί��******", kSTL_Lvl6 },
	};

	struct stFbTypeKeyMap{
		CD_En_FbType	fb_type_;
		DWORD			fb_key_flag_;
	};
	const stFbTypeKeyMap g_fb_type_key_map[] = {
		{ CD_En_FbType::kFT_Sociaty, 0x0000985E/*MMOCLIENT_REVERSAL_PACKET_MSG_ID_GONG_HUI_KEY___*/ },
		{ CD_En_FbType::kFT_Cat, 0x000075C2/*MMOCLIENT_REVERSAL_PACKET_MSG_ID_MIAO_MIAO_KEY___*/ },
		{ CD_En_FbType::kFT_QianShou, 0x000075B6/*MMOCLIENT_REVERSAL_PACKET_MSG_ID_QIAN_SHOU_KEY___*/ }
	};

	//npc������
	enum enNpcOpenType{
		kNOT_Normal = 2,
		kNOT_JiaoNaXiang = 0x0a,		//������
	};

	//��������ģʽ
	enum enFbConsumeMode{
		kFCM_ShouLieQuan = 0,		//ֻʹ������ȯ
		kFCM_Silver,				//ֻʹ������
		kFCM_All,					//��ʹ������ȯ����ʹ������
	};
	//////////////////////////////////////////////////////////////////////////
}

enum class AcceptTaskType{
	kNormal = 0x01,		//MMOCLIENT_REVERSAL_ACCEPT_TASK_TYPE_PU_TONG___
};

//game object type
enum GameObjType{
	kGOT_Invalid = 0,
	//kGOT_MISC,				//��̬���󣬸���������ӵ���Ʒ
	kGOT_Npc,
	kGOT_Player,			//���
	//kGOT_Unknown,			//������Ʒ
	kGOT_Monster,
	kGOT_Door,
	kGOT_Collect,
	kGOT_Static,
	kGOT_StaticBeatable,
	kGOT_AnyObj,			//�������
	kGOT_ParseObjType,		//�����ڵõ���ʱ��Ϸ�����type
};
