#pragma once
/*
@author zhp
@date 2014/6/15 15:10
@purpose console.exe��game.dll֮��Ľ���
*/
#include <Protocol/P_Defines.h>

//����̨����gameģ��һ���̶����ַ���
const char* const kStableStr_ConsoleToGame = 
#ifdef __PROJ_JIN_GANG_
	"C5144231-9538-42257-9236-221DaB3353E2f6";
#elif defined(__PROJ_XIAO_ER_)
	"70275346-1A48-43129-8390-3311B92737F18";
#endif
//����̨����gameģ�飬����Ч��֤��Կ��Ч��
//const char* const kCheckPubKey_ConsoleToGame = "44C62BB7-D69C-469A-BD80-3DE8F4DF4BDA";

//�������Ͻ��յĹؼ����ݣ��������ֵ����������Ч��
//const int kAddrDatasAdditional = 10;

enum enGameAcType{
	kGAT_Normal = 0,
	kGAT_Stored,
	kGAT_Invalid,
};

enum enDstServerType{
	kDST_Normal = 1,
	kDST_Invalid,
};
inline P_CoorTypeT MakeTransRouteType( enGameAcType game_ac_type, int game_ser_id ){
	return game_ac_type + (game_ser_id << 4);
}
