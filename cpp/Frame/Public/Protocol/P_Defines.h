#pragma once
#include <tchar.h>
#include <boost/thread/lock_types.hpp>
#include <boost/thread/shared_mutex.hpp>
#include <boost/optional.hpp>
#include <ProtocolX/P_DefinesX.h>
#include "../DependSelfLib.h"

//////////////////////////////////////////////////////////////////////////
//****************����Э��*****************************************
const pt_word P_MaxWord = (pt_word)-1;
typedef pt_word P_ObjId;
typedef pt_word P_MsgNT;
typedef pt_word P_Operate;

struct P_FuncObjOper
{
	P_Operate	operate;
	P_MsgNT		msg_num;

	static P_FuncObjOper MakeOper( P_Operate first, P_MsgNT msg );
};

//�ڲ�Э��
const P_Operate P_Operate_Inner = 1;
//�û���Ϣ
const P_Operate P_Operate_UserMsg = 2;

const P_MsgNT		kInnerMsg_SetSecrectKey = -1;
const P_MsgNT		kInnerMsg_JsonCall = -2;
const P_MsgNT		kInnerMsg_CoorTrans = -3;
const P_MsgNT		kInnerMsg_BufCall = -4;
//////////////////////////////////////////////////////////////////////////
typedef unsigned int P_CoorIdT;
static_assert(sizeof(P_CoorIdT) == sizeof(void*), "");
typedef unsigned int P_CoorTypeT;
const P_CoorTypeT kPCT_Any = P_CoorTypeT(-1 - 1000);
const P_CoorIdT kPCI_Ignore = 0;

enum enWayToNextCoor{
	kWTNC_ByType = 1,
	kWTNC_ById,
};
struct P_WayToNextCoor{
	enWayToNextCoor	method_;
	union{
		P_CoorIdT	coor_id_;
		P_CoorTypeT	coor_type_;
	};
};
//////////////////////////////////////////////////////////////////////////
//send or recv buffer max length
const pt_word P_BufferMaxLen = 256 * 2;
//send or recv buffer type
typedef char (P_BufferT)[P_BufferMaxLen];
//port
const pt_word P_Port_Game = 45398;
const pt_word P_Port_Login = 45399;
//Э����������FIFA�ս��
const pt_word P_Port_Coordinate = 45400;
//��Ϸ��½��֮������½
//const pt_word P_Port_LoginAssist = 45500;

//self ip
const char* const kSelfIpStr = "127.0.0.1";

const P_ObjId kFuncObjTemplateId_CustomBase = 4000;
//funcobjģ��ID
const P_ObjId kFuncObjTemplateId_Addition = 12;

#define DEF_THE_CUSTOM_TEMPLATE_OBJ_ID_( the_id ) (kFuncObjTemplateId_Addition + kFuncObjTemplateId_CustomBase + the_id)
/**/
const P_ObjId kFuncObjTemplateId_Account = 1 + kFuncObjTemplateId_Addition;
const P_ObjId kFuncObjTemplateId_Game = 2 + kFuncObjTemplateId_Addition;
const P_ObjId kFuncObjTemplateId_Dispatcher = 3 + kFuncObjTemplateId_Addition;
const P_ObjId kFuncObjTemplateId_Inter = 4 + kFuncObjTemplateId_Addition;
const P_ObjId kFuncObjTemplateId_GLua = 5 + kFuncObjTemplateId_Addition;
const P_ObjId KFuncObjTemplateId_JsonEcho = 6 + kFuncObjTemplateId_Addition;
//JsonEchoBase default
const P_ObjId kFuncObjTemplateId_JsonEchoBase = 7 + kFuncObjTemplateId_Addition;
//JsonEchoTrans default
const P_ObjId kFuncObjTemplateId_JsonEchoTrans = 8 + kFuncObjTemplateId_Addition;
const P_ObjId kFuncObjTemplateId_LuaScript = 9 + kFuncObjTemplateId_Addition;
const P_ObjId kFuncObjTemplateId_CoorTrans = 10 + kFuncObjTemplateId_Addition;
const P_ObjId kFuncObjTemplateId_JsonEchoCoorTrans = 11 + kFuncObjTemplateId_Addition;
const P_ObjId kFuncObjTemplateId_BufCallCoorTrans = 12 + kFuncObjTemplateId_Addition;
const P_ObjId kFuncObjTemplateId_Login = 12 + kFuncObjTemplateId_Addition;
const P_ObjId kFuncObjTemplateId_GameOrLogin = 13 + kFuncObjTemplateId_Addition;

#define SAFE_DELETE(x) { if (x) { delete (x); (x) = nullptr; } }(void*)0

#ifdef _AFXDLL
#define GET_RUNTIME_CLASS(T) (assert(T::GetThisClass()), T::GetThisClass())
#else
#define GET_RUNTIME_CLASS(T) (&T::class##T)
#endif

//shared mutex type
typedef boost::shared_mutex SharedMutex;
//read lock
typedef boost::shared_lock<SharedMutex> ReadLock;
//write lock
typedef boost::unique_lock<SharedMutex> WriteLock;

//�ʺ���󳤶�
const int kAccountMaxLen = 19;
//�ʺ���С����
const int kAccountMinLen = 5;
//������󳤶�
const int kPasswordMaxLen = 19;
//������С����
const int kPasswordMinLen = 5;

//////////////////////////////////////////////////////////////////////////
//*****************************database***********************************
//���ݿ�����󳤶�
const pt_dword kDbNameMaxLen = 20;
//��Ŀ����󳤶�
const pt_dword kProjectNameMaxLen = 20;
//�û�����󳤶�
const pt_dword kUserNameMaxLen = 20;
//�û�����С����
const pt_dword kUserNameMinLen = 5;
//�û�������󳤶�
const pt_dword kUserPwdMaxLen = 20;
//�û�������С����
const pt_dword kUserPwdMinLen = 5;
//������ĳ���
const pt_dword kMachineCodeLen = kUuidStrLen;
//cookie�ĳ���
const pt_dword kCookieStrLen = kUuidStrLenEx;
//���԰���Ϣ��󳤶�
const pt_dword kMsgBoardMsgMaxLen = 150;
//ÿ��������Ը���
const pt_dword kMsgBoardMaxCnt_EveryDay = 2;
//ÿ���ʺ��ܹ�������Ը���
const pt_dword kMsgBoardMaxTotalCnt_OneAc = 20;
//qq��С����
const pt_dword kQQMinLen = 4;
//qq��󳤶�
const pt_dword kQQMaxLen = 12;
//ip��󳤶�
const pt_dword kIPMaxLen = 15;
//��ID�ĳ���
const pt_dword kCardIdLen = kUuidStrLen;
const pt_dword kCardIdLenEx = kUuidStrLenEx;
//ע����ĳ���
const pt_dword kRegKeyIdLen = kUuidStrLen;
const pt_dword kRegKeyIdLenEx = kUuidStrLenEx;
//������ĳ���
const pt_dword kCardPwdLen = kUuidStrLen;
const pt_dword kCardPwdLenEx = kUuidStrLenEx;
static_assert(kCardIdLen == kRegKeyIdLen, "");
static_assert(kCardIdLen == kCardPwdLen, "");
static_assert(kCardIdLenEx == kRegKeyIdLenEx, "");
static_assert(kCardIdLenEx == kCardPwdLenEx, "");
//ָ����ʱ�����֤��������Ͽ����ӣ���λ:����
const pt_dword kCheckSvrActiveTime = 1000 * 12;
//tbl_StrData֮�ַ�����󳤶�
const pt_dword kTblStrDataMaxLen = 200;
//////////////////////////////////////////////////////////////////////////
struct P_StringCheck{
	static bool ValidUserName( pt_csz user_name );
	static bool ValidUserPwd( pt_csz user_pwd );
	static bool ValidMachineCode( pt_csz machine_code );
	static bool ValidMsgBoard( pt_csz msg );
	static bool ValidQQ( pt_csz qq );
	static bool ValidCard( pt_csz str );
	static bool ValidStrData( pt_csz str );
	static bool ValidCookie( pt_csz cookie );
};
//////////////////////////////////////////////////////////////////////////
//�û�Ȩ�޵ȼ�
enum enUserGrantLvl{
	kGUL_RestrictBind = 0,
	kUGL_PeerAcByCard,
	kUGL_PeerCardByAc,
	kUGL_PeerAcInfo,
	kUGL_PeerCardInfo,
	kUGL_RemoveBind,
	kUGL_MgrAcState,
	kUGL_PeerUsedCardInfo,
	kUGL_PeerAllCardInfo,
	kUGL_RemoveBindKing,
	kUGL_RollbackPay,
	kUGL_OpenCard,
	kUGL_GenRegKey,
	kUGL_ModifyProjData,
	kUGL_Invalid,
};

//�û��ķ���Ȩ��
typedef unsigned __int64 enUserGrant;
static_assert(sizeof(enUserGrant) * 8 >= kUGL_Invalid, "");

const enUserGrant kUG_No = 0;											//��Ȩ��
const enUserGrant kUG_RestrictBind = 1 << kGUL_RestrictBind;			//���ƽ���ʺ�
const enUserGrant kUG_PeerAcByCard = 1 << kUGL_PeerAcByCard;			//ͨ�����źͿ��ܲ�ѯ�ʺ���Ϣ
const enUserGrant kUG_PeerCardByAc = 1 << kUGL_PeerCardByAc;			//ͨ���ʺź������ѯ������Ϣ
const enUserGrant kUG_PeerAcInfo = 1 << kUGL_PeerAcInfo;				//�鿴�ʻ���Ϣ
const enUserGrant kUG_PeerCardInfo = 1 << kUGL_PeerCardInfo;			//�鿴������Ϣ
const enUserGrant kUG_RemoveBind = 1 << kUGL_RemoveBind;				//���Ȩ�ޣ���ͨ��
const enUserGrant kUG_MgrAcState = 1 << kUGL_MgrAcState;				//�����ʺ�״̬�����ᡢ��š��ⶳ�����
const enUserGrant kUG_PeerUsedCardInfo = 1 << kUGL_PeerUsedCardInfo;	//�鿴ʹ�ù��Ŀ�����Ϣ
const enUserGrant kUG_PeerAllCardInfo = 1 << kUGL_PeerAllCardInfo;		//�鿴���п�����Ϣ
const enUserGrant kUG_RemoveBindKing = 1 << kUGL_RemoveBindKing;		//���Ȩ�ޣ�Ҳ�ɽ�����ƽ���ʺţ�
const enUserGrant kUG_RollbackPay = 1 << kUGL_RollbackPay;				//֧���ع�����������ʹ�ù��ģ������ʺŵ�ʱ��ᱻ��ȥ��
const enUserGrant kUG_OpenCard = 1 << kUGL_OpenCard;					//����Ȩ��
const enUserGrant kUG_GenRegKey = 1 << kUGL_GenRegKey;					//����ע�����Ȩ��
const enUserGrant kUG_ModifyProjData = 1 << kUGL_ModifyProjData;		//�޸���Ŀ����Ȩ��
//�����Ȩ��
const enUserGrant kUG_TheProxyPerson = kUG_RestrictBind | kUG_PeerAcByCard | kUG_PeerCardByAc | kUG_PeerAcInfo | kUG_PeerCardInfo | kUG_RemoveBind | kUG_MgrAcState | kUG_PeerUsedCardInfo;
//û�г�ֵ�ع�Ȩ��
const enUserGrant kUG_KingLower = kUG_PeerAcByCard | kUG_PeerCardByAc | kUG_PeerAcInfo | kUG_PeerCardInfo | kUG_RemoveBind | kUG_MgrAcState | kUG_PeerUsedCardInfo | kUG_PeerAllCardInfo | kUG_RemoveBindKing | kUG_OpenCard | kUG_GenRegKey;
//����Ȩ��
const enUserGrant kUG_TheKingMax = kUG_KingLower | kUG_RollbackPay | kUG_ModifyProjData;
//////////////////////////////////////////////////////////////////////////
enum class enAcState{
	kAS_Normal = 0,
	kAS_Freeze,				//���ᣬ�޽�ֹ���ڣ�ʱ�䲻������
	kAS_Ban,				//��ţ��н�ֹ���ڣ�ʱ�������
	kAS_Invalid,
};
//////////////////////////////////////////////////////////////////////////
/*
//��Ѷ��½���İ�ȫ�����¼���������֣�Ŀǰδʹ��
const char* const kLogin_SafeCheckEventName = "0CFFBDDA408A41C2A693A0BB76E2451D";
*/

//��֤���ƶ�Ψһʵ���¼�����
//#ifdef __PROJ_FIFA_MAIN_
//uuid of key
const char* const kRSA_UuidPrivate_CtoS = "8e395278-7fe6-592d-9f8a-3cc6e7a3ee98";
const char* const kRSA_UuidPublic_StoC = "a49b0d72-8668-5dda-8c1e-88ef08a470a5";

extern const std::string kStrPlaceholder;
//extern const std::wstring kWStrPlaceholder;

//math
//////////////////////////////////////////////////////////////////////////
const double kPi = 3.141592653589793238462643383279502884197169399375105820974944592307816;
//////////////////////////////////////////////////////////////////////////
const TCHAR* const kQxAqDllName = _T("_kolavb_.dll");
//��½�ȴ�ʱ��
const int kToServerWaitTime = 1000 * 60;
//////////////////////////////////////////////////////////////////////////
const char* const kLoginLocalInfo_FileMapNameS = "51A2002A-1B8E-4E81-AABE-52C86D4AB5A0";

enum enCrackCaptchaMode{
	kCCMode_DaMaTu,
	kCCMode_Local,
};

const char* const kGameDllVersion = "A434BD281F23460EB3B87D98F3F351F8";
const char* const kLoginDllVersion = "B6C866C183F34676BB0FD6B148D1DA23";
struct stAcSerInfo{
	template<class Archive>
	void serialize(Archive & ar){
		ar & ac_
			& pwd_
			& area_
			& ser_;
	}

	std::string		ac_;
	std::string		pwd_;
	std::string		area_;
	std::string		ser_;
};

struct stAsSerSessionInfo : public stAcSerInfo{
	std::string		login_process_info_;

	template<class Archive>
	void serialize(Archive & ar){
		__super::serialize(ar);
		ar & login_process_info_;
	}
};
//////////////////////////////////////////////////////////////////////////
//**************��Ϸ���
//������ɫ���
enum enCmnCreateRoleRes{
	kCmnCRR_NameErr,
	kCmnCRR_Error,
	kCmnCRR_Succeed,
};
//////////////////////////////////////////////////////////////////////////