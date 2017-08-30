#pragma once
/*
@author zhp
@date 2013-12-31
@purpose ��ź�����ַ��ȫ�ֱ����ĵ�ַ
*/
#include "Common/MemOper.h"
#include "../../CrackData/jfzrcalltest/jfzrbase.h"
#include "../../CrackData/jfzrcalltest/jfzrstruct.h"
#include "../../CrackData/jfzrcalltest/JFZRPacket.h"
#include "../../CrackData/jfzrcalltest/jfzrpacketstruct.h"

//g_f_s_->stdcall function
//g_f_c_->cdecl function
//g_f_t_->thiscall function
//g_f_a_->��������Լ���ĺ���
//g_v_->�麯����
//g_sa_->���ֽ��ַ���
//g_sw_->���ֽ��ַ���
namespace GAddr{
	/*
	����http��
	@1:�����ַ
	@2:ָ��������(ASCII�ַ���)
	@3:�����Ч���ݳ���
	*/
	//////////////////////////////////////////////////////////////////////////
	//�����׽���,socket
	extern unsigned int						g_pSendCallSocket /*=JFZR_REVERSAL_SEND_PACKET_SOCKET_ADDR*/;
	//const unsigned int						g_pSendCallSocket = JFZR_REVERSAL_SEND_PACKET_SOCKET_ADDR;
	//ͨ��HOOK�˴���ȡ����CALL�ļ��ܶ����������Ķ����ַ
	const unsigned int						g_pHookGetAllmMemorySendObjAddr = JFZR_REVERSAL_SEND_ARGC3_ARGC4_HOOK_ADDR;
	//����call��ַ
	const unsigned int						g_pSendCallAddr = JFZR_REVERSAL_SEND_PUSH_ARGC3_ARGC4_CALL;
	//����call֮���ķ���֮��ַ
	const unsigned int						g_pOriginalSendCallAddr = JFZR_REVERSAL_SEND_ADDR_CALL;
	//����CALL֮ǰ�������
	const unsigned int						g_pSendCallConstructObj = JFZR_REVERSAL_SEND_ALLOC_OBJ_CALL;
	//����CALL֮���ͷŶ���
	const unsigned int						g_pSendCallDestroyObj = JFZR_REVERSAL_SEND_FREE_OBJ_CALL;
	//��Ϸ�ڲ������ڴ�
	const unsigned int						g_pGameAlloc = JFZR_REVERSAL_ALLMMEMORY_ALLOC_ADDR;
	//��Ϸ�ڲ��ͷ��ڴ�
	const unsigned int						g_pGameFree = JFZR_REVERSAL_ALLMMEMORY_FREE_ADDR;
	//��Ϸ�ڲ����ƿ��ַ���
	const unsigned int						g_pGameStrCpy = JFZR_REVERSAL_GAME_MEMCPY_CALL;
	//��·����call
	const unsigned int						g_pWalkCallAddr = JFZR_REVERSAL_ZOULU_CALL;
	//�����������NPC���������ȣ�hook�����ַ�õ��������
	const unsigned int						g_pHookGainCreatureInRoom = JFZR_REVERSAL_LOCAL_OBJ_ADDR_HOOK;
	//��ɫ����/��ҵ�ַ
	const unsigned int						g_pRoleObjAddr = JFZR_REVERSAL_ROLE_OBJ_ADDR;
	//�����ַ
	const unsigned int						g_pRoleBaseAddr = JFZR_REVERSAL_ROLE_BASE_ADDR;
	//��ɫ����ʱ���
	const auto								g_pRoleSkillRunSerialAddr = (DWORD*)JFZR_REVERSAL_ROLE_SKILL_RUN_SERIAL_ADDR;
	//�������
	const unsigned int						g_pRandomSeekCall = JFZR_REVERSAL_RANDOMSEED_CALL;
	//ͨ��hook�õ�������󣬵�ǰ�������š��ŵ�
	const unsigned int						g_pHookGainRoomObj = JFZR_REVERSAL_LOCAL_ROOM_OBJ_HOOK;
	const unsigned int						g_pHookGainTownRoomObj = JFZR_REVERSAL_LOCAL_CITY_OBJ_HOOK;
	//�õ������Ѷȵȼ�
	//const unsigned int						g_pGetCloneMapDiffiLevel = JFZR_REVERSAL_FB_SEACH_CALL;
	//��ͼ����
	//const unsigned int						g_pGameMapObj_ = JFZR_REVERSAL_ROLE_WHERE_THE_MAP_HOOK;
	//��Ϸ������������
	//const unsigned int						g_pGameObjDestroy = JFZR_REVERSAL_NPC_OBJ_DESTRUCTOR_HOOK;
	// �жϵ�ǰ��ɫ���ڳ�����߸������Ҹ����ȼ��������������з�������
	const unsigned int						g_pCurMapObjHook = JFZR_REVERSAL_LOCAL_MAP_OBJ_HOOK;
	//��Ӣ��ӳ��
	const unsigned int						g_pEn2ChMapAddr = JFZR_REVERSAL_CHINESE_ENGLISH_MAP_ADDR;
	//��ǰְҵ��������
	const unsigned int						g_pCurJobAllTask = JFZR_REVERSAL_TASK_OBJ_ADDR1;
	//local all obj map
	const unsigned int						g_pHookLocalAllObjMapAddr = JFZR_REVERSAL_ALLOBJ_MAP_FIND_ADDR_HOOK;
	//����ģ��
	const unsigned int						g_pSkillTemplate = JFZR_REVERSAL_SDB_SKILL_ADDR;
	//hook�հ�
	const unsigned int						g_pHookRecvPacket = JFZR_REVERSAL_RECV_UN_PACKET_HOOK;
	//��Ʒģ��
	const unsigned int						g_pItemTemplate = JFZR_REVERSAL_SDB_ITEM_INFO_ADDR;
	//��ͼģ��
	const unsigned int						g_pStageTemplate = JFZR_REVERSAL_SDB_STAGE_INFO_ADDR;
	//��Ϸ��������
	const unsigned int						g_pGameAmbientCondition = JFZR_REVERSAL_GAME_CONDITION_HOOK;
	//��Ʒģ��
	const unsigned int						g_pShopTemplate = JFZR_REVERSAL_SHOP_INFO_SELL_ITEM_ADDR;
	//hook����
	const unsigned int						g_pHookGameSendCall = JFZR_REVERSAL_SEND_ADDR_PRE_CALL_HOOK;
	/*
	�����õ������ھ��
	hook Call CreateWindowEx����һ��ָ��
	*/
	//const unsigned int						g_pHookForGainMainWndHandle_ = JFZR_REVERSAL_CREATE_WINDOWN_EX_HOOK;	// ���ھ��
	//game wnd proc call
	const unsigned int						g_pGameWndProcCall_ = JFZR_REVERSAL_WND_PROC_CALL;
	//class info
	const unsigned int						g_pClassInfoTemplate = JFZR_REVERSAL_CLASS_INFO_ADDR;
	//ְҵclass name
	const unsigned int						g_pJobClassNameTemplate = JFZR_REVERSAL_CLASS_CLASSTYPE_ADDR;
	//region template
	const unsigned int						g_pRegionStageMapTemplate = JFZR_REVERSAL_REGION_INFO_ADDR;
	//����
	//const unsigned int						g_pGameOffline = JFZR_REVERSAL_TCPCHANNEL_CLOSE_HOOK___;
	//skill timestamp
	const unsigned int						g_pSkillTimestamp = JFZR_REVERSAL_TIME_STAMP_HOOK;
	//pre action play time
	const unsigned int						g_pPreActionPlayTime = JFZR_REVERSAL_LOCAL_PREV_ACTION_PLAY_TIME_HOOK;
	//get local room pos
	const unsigned int						g_pGetLocalRoomPos = JFZR_REVERSAL_GET_LOCAL_ROOM_POSITION_HOOK;
	//�޵�
	const unsigned int						g_pWuDiAddr = JFZR_REVERSAL_WUDI_CODE_ADDR___;
	//////////////////////////////////////////////////////////////////////////
	const MemOper<Oper_ThisCall>			g_pSendCallConstructObj_ = g_pSendCallConstructObj;
	const MemOper<Oper_ThisCall>			g_pSendCallDestroyObj_ = g_pSendCallDestroyObj;
	const MemOper<Oper_ThisCall>			g_pSendCallAddr_ = g_pSendCallAddr;
	const MemOper<Oper_Cdecl>				g_pOriginalSendCallAddr_ = g_pOriginalSendCallAddr;
	const MemOper<Oper_Cdecl>				g_pRandomSeekCall_ = g_pRandomSeekCall;
	const MemOper<Oper_ThisCall>			g_pGameWndProcCal = g_pGameWndProcCall_;
	//const MemOper<Oper_ThisCall>			g_pGetFbUnknownObj = g_pGetCloneMapDiffiLevel;
	//////////////////////////////////////////////////////////////////////////
	//��������
	extern void*							g_pSendObjAddr;
	//local object addr
	extern void*							g_pLocalObjAddr;
	//local room object addr
	extern void*							g_pLocalRoomObjAddr;
	//local town room object addr
	extern void*							g_pLocalTownRoomObjAddr;
	//map object
	//extern void*							g_pGameMapObjAddr;
	//��ǰ��ͼ(����򸱱�)
	extern void*							g_pCurMapObjAddr;
	//local all obj map
	extern void*							g_pLocalAllObjMapAddr;
	//skill timestamp
	extern void*							g_pSkillTimestampValue;
	//��ͼ��Ч����
	extern DWORD							g_through_room_valid_data_x;
	extern DWORD							g_through_room_valid_data_y;
	extern bool								g_through_room_dummy_exist;
	//pre action play time addr
	extern void*							g_pPreActionPlayTimeAddr;
	//local room pos
	extern void*							g_pLocalRoomPos;
	//////////////////////////////////////////////////////////////////////////
}