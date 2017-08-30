#pragma once
/*
@author zhp
@date 2014/6/15 15:10
@purpose console.exe��game.dll֮��Ľ���
*/
#include <Protocol/P_Defines.h>
#include <Common/JsonMore.h>

//����̨����gameģ��һ���̶����ַ���
const char* const kStableStr_ConsoleToGame =
#ifdef __PROJ_JFZR_
	"713B11BA-173F-455F-9C06-90771EF47930";
#elif defined(__PROJ_JFZR_SM_)
	"C2A67C6B-2765-446F-BCEE-A2C457610B8C";
#elif defined(__PROJ_JFZR_TWO_)
	"696655FE-3F0A-4EEA-9B62-B6981AC472D8";
#endif

//����̨����gameģ�飬����Ч��֤��Կ��Ч��
//const char* const kCheckPubKey_ConsoleToGame = "310279A0293B4EF0B99B9AADFC554592";
//funcobj normal
const P_ObjId kObjIdNormal = DEF_THE_CUSTOM_TEMPLATE_OBJ_ID_(40);

//��ɫ��Ϣ
struct CG_RoleInfo{
	typedef std::vector<CG_RoleInfo> RoleInfoContT;
	bool ParseFromJosn( const Json::Value& json_v );
	bool ConvertToJson( Json::Value& json_v );
	
	std::string		role_job_;
	std::string		role_name_;
};
//��ɫ��������
const int kCG_RoleCntLimit = 9;

//////////////////////////////////////////////////////////////////////////
enum enGameAcType{
	kGAT_Normal = 0,
	kGAT_Stored,
	kGAT_TransStation,
	kGAT_Invalid,
};

enum enDstServerType{
	kDST_Normal = 1,
	kDST_Invalid,
};