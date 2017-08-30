#pragma once
/*
@author zhp
@date 2013-12-31
@purpose ���ƫ�Ƶ�ַ
*/
#include "GTypes.h"
#include "../../CrackData/jfzrcalltest/jfzrbase.h"

//g_o_->ƫ�Ƶ�ַһ����g_o_��ͷ
namespace GOffset{
	//�����׽��ֶ����ƫ��
	const int g_o_SendCallSocket = JFZR_REVERSAL_SEND_PACKET_SOCKET_OFFSET___;
	//�����������ƫ��
	const int g_o_SendCallNeedObj1 = JFZR_REVERSAL_SEND_PACKET_OFFSET;
	//�������ܶ���ƫ��
	const int g_o_SendCallSecretObj = JFZR_REVERSAL_SEND_PACKET_JIAMI_OBJ_OFFSET;
	//�����������ƫ��
	const int g_o_SendCallTaskObj = JFZR_REVERSAL_SEND_PACKET_TASK_OBJ_OFFSET;
	//�����������NPC����������
	const int g_o_GainCreatureListInRoom = JFZR_REVERSAL_LOCAL_OBJ_LIST_OFFSET;
	//��ȡ����������ƫ��
	const int g_o_CreatureInRoom[] = { JFZR_REVERSAL_LOCAL_OBJ_OFFSET1, JFZR_REVERSAL_LOCAL_OBJ_OFFSET2, JFZR_REVERSAL_LOCAL_OBJ_OFFSET3, JFZR_REVERSAL_LOCAL_OBJ_OFFSET4___ };
	//����ID
	const int g_o_CreatureSerial = JFZR_REVERSAL_LOCAL_OBJ_SERIAL_OFFSET___;
	//ְҵ���ֵĳ���
	//const int g_o_CreatureJob_Len = JFZR_REVERSAL_LOCAL_OBJ_JOBLEN_OFFSET___;
	//ְҵ��
	const int g_o_CreatureJob_Name = JFZR_REVERSAL_LOACL_OBJ_JOBNAME_OFFSET___;
	//���ֳ���
	//const int g_o_CreatureNameLen[] = { JFZR_REVERSAL_LOCAL_OBJ_NAMELEN_OFFSET___ };
	//����
	const int g_o_CreatureName = JFZR_REVERSAL_LOACL_OBJ_NAME_OFFSET___;
	//���ͳ���
	//const int g_o_CreatureTypeLen[] = { JRZR_REVERSAL_LOCAL_OBJ_TYPELEN_OFFSET___ };
	//������
	/*
	�ڸ���������
	MISC����̬���󣬸���������ӵ���Ʒ
	NPC������
	PLAYER�����
	UNKNOWN��������Ʒ
	�ڳ�����
	NPC������NPC
	PLAYER:���
	*/
	const int g_o_CreatureType = JFZR_REVERSAL_LOCAL_OBJ_TPYE_OFFSET___;
	//����x
	const int g_o_CreaturePosX = JFZR_REVERSAL_LOCAL_OBJ_X_OFFSET;
	/*//����y
	const int g_o_CreaturePosY[] = { JFZR_REVERSAL_LOCAL_OBJ_Y_OFFSET };
	//����z
	const int g_o_CreaturePosZ[] = { JFZR_REVERSAL_LOCAL_OBJ_Z_OFFSET };*/
	//����x
	const int g_o_CreatureDirectionX = JFZR_REVERSAL_LOCAL_OBJ_DIRECTION_X_OFFSET___;
	/*//����y
	const int g_o_CreatureDirectionY[] = { JFZR_REVERSAL_LOCAL_OBJ_DIRECTION_Y_OFFSET___ };
	//����z
	const int g_o_CreatureDirectionZ[] = { JFZR_REVERSAL_LOCAL_OBJ_DIRECTION_Z_OFFSET___ };*/
	//����ƫ��1
	const unsigned int g_o_SkillOffset1 = JFZR_REVERSAL_SKILL_OFFSET1;
	//����ƫ��2
	const unsigned int g_o_SkillOffset2 = JFZR_REVERSAL_SKILL_OFFSET2;
	//�������ֵĳ���
	const int g_o_SkillNameLen = JFZR_REVERSAL_SKILL_OBJ_NAMELEN_OFFSET___;
	//��������
	const int g_o_SkillName = JFZR_REVERSAL_SKILL_OBJ_NAME_OFFSET___;
	//���ܵȼ�
	const int g_o_SkillLevel = JFZR_REVERSAL_SKILL_OBJ_LEVEL_OFFSET___;
	//����ID
	const int g_o_SkillId = JFZR_REVERSAL_SKILL_OBJ_ID_OFFSET___;
	//��ɫ���
	const int g_o_RoleGold1 = JFZR_REVERSAL_ROLE_GOLD_OFFSET1;
	const int g_o_RoleGold2 = JFZR_REVERSAL_ROLE_GOLE_OFFSET2;
	//��ɫ��ţ�������NPC�������һ����
	const int g_o_RoleSerial[] = { JFZR_REVERSAL_ROLE_SERIAL_OFFSET___ };
	//��ɫ�ȼ�
	const int g_o_RoleLevel = JFZR_REVERSAL_ROLE_LEVEL_OFFSET;
	//��������
	const int g_o_RoomMapName = JFZR_REVERSAL_LOCAL_ROOM_MAP_OFFSET___;
	//�������ֳ���
	//const int g_o_RoomMapNameLen[] = { JFZR_REVERSAL_LOCAL_ROOM_MAP_LEN_OFFSET___ };
	//����ID
	const int g_o_RoomMapId = JFZR_REVERSAL_LOCAL_ROOM_ID_OFFSET___;
	//����ID����
	//const int g_o_RoomMapIdLen[] = { JFZR_REVERSAL_LOCAL_ROOM_ID_LEN_OFFSET___ };
	//�����Ŷ���ƫ��
	const int g_o_RoomMapDoorObj = JFZR_REVERSAL_LOCAL_ROOM_DOOR_OBJ_OFFSET___;
	//��������
	const int g_o_RoomMapWarpName = JFZR_REVERSAL_LOCAL_ROOM_WARP_NAME_OFFSET___;
	//���������ĳ���
	//const int g_o_RoomMapWarpNameLen[] = { JFZR_REVERSAL_LOCAL_ROOM_WARP_LEN_OFFSET___ };
	//������Ʒƫ��
	const int g_o_ItemOffset1 = JFZR_REVERSAL_ITEM_BAG_OFFSET1;
	const int g_o_ItemOffset2 = JFZR_REVERSAL_ITEM_BAG_OFFSET2;
	const int g_o_ItemOffset3 = JFZR_REVERSAL_ITEM_BAG_OFFSET3;
	const int g_o_ItemOffset4 = JFZR_REVERSAL_ITEM_BAG_OFFSET4;
	//��Ʒ������
	//const int g_o_ItemNameLen = JFZR_REVERSAL_ITEM_BAG_NAME_LEN_OFFSET___;
	//��Ʒ��
	//const int g_o_ItemName = JFZR_REVERSAL_ITEM_BAG_NAME_OFSSET___;
	//��ƷƷ��������
	//const int g_o_ItemQualityNameLen = JFZR_REVERSAL_ITEM_BAG_QUALITY_NAME_LEN_OFFSET___;
	//��ƷƷ����
	//const int g_o_ItemQualityName = JFZR_REVERSAL_ITEM_BAG_QUALITY_NAME_OFFSET___;
	//��Ʒ����
	//const int g_o_ItemCount = JFZR_REVERSAL_ITEM_BAG_COUNT_OFFSET___;
	//��Ʒ�;ö�
	//const int g_o_ItemDurable = JFZR_REVERSAL_ITEM_BAG_DURABLE_OFFSET___;
	//��Ʒ����
	//const int g_o_ItemObjInfo = JFZR_REVERSAL_ITEM_BAG_OBJ_OFFSET___;
	//��ӡ
	//const int g_o_ItemSeal = JFZR_REVERSAL_ITEM_BAG_SEAL_OFFSET___;
	//��Ʒ����
	//const int g_o_ItemIdentification = JFZR_REVERSAL_ITEM_BAG_IDENTIFICATION_OFFSET___;
	//������Ʒ
	const int g_o_DroppedItem = JFZR_REVERSAL_ITEM_EXISTS_OFFSET___;
	//��Ʒʹ�ò�λ����
	//const int g_o_ItemLocationLen = JFZR_REVERSAL_ITEM_OBJ_USE_LEN_OFFSET___;
	//��Ʒʹ�ò�λ��
	//const int g_o_ItemLocationName = JFZR_REVERSAL_ITEM_OBJ_USE_OFFSET___;
	//��Ʒ���ͳ���
	//const int g_o_ItemTypeLen = JFZR_REVERSAL_ITEM_OBJ_TYPE_LEN_OFFSET___;
	//��Ʒ������
	//const int g_o_ItemTypeName = JFZR_REVERSAL_ITEM_OBJ_TYPE_OFFSET___;
	//װ��ƫ��1
	const int g_o_EquipItemOffset1 = JFZR_REVERSAL_EQUIP_ITEM_OFFSET3;
	//װ��ƫ��2
	const int g_o_EquipItemOffset2 = JFZR_REVERSAL_EQUIP_ITEM_OFFSET4;
	//����ѡ��
	const int g_o_CloneMapOffset1 = JFZR_REVERSAL_FB_OFFSET1;
	const int g_o_CloneMapOffset2 = JFZR_REVERSAL_FB_OFFSET2;
	const int g_o_CloneMapOffset3 = JFZR_REVERSAL_FB_OFFSET3___;
	//������߿���ս���Ѷȵȼ�
	//const int g_o_CloneMapCurMaxLevel = JFZR_REVERSAL_FB_MAX_LEVEL_OFFSET___;
	//ƣ��ֵ
	const int g_o_FatigueOffset = JFZR_REVERSAL_FATIGUE_OFFSET;
	//��ǰ������
	const int g_o_VillageName = JFZR_REVERSAL_VILLAGE_NAME_OFFSET;
	//����������
	//const int g_o_VillageNameLen = JFZR_REVERSAL_VILLAGE_NAME_LEN_OFFSET____;
	//��ǰHP
	const int g_o_CurHp = JFZR_REVERSAL_LOCAL_OBJ_HP_OFFSET___;
	//HP����
	const int g_o_HpLimit = JFZR_REVERSAL_LOCAL_OBJ_MAXHP_OFFSET___;
	//��ǰMP
	const int g_o_CurMp = JFZR_REVERSAL_LOCAL_OBJ_MP_OFFSET___;
	//MP����
	const int g_o_MpLimit = JFZR_REVERSAL_LOCAL_OBJ_MAXMP_OFFSET___;
	//�Ƿ��ڳ�����
	//const int g_o_is_town = JFZR_REVERSAL_ROLE_WHERE_THE_MAP_FLAG_OFFSET___;
	//�����Ŷ��������x
	const int g_o_room_door_obj_x = JFZR_REVERSAL_LOCAL_ROOM_X_OFFSET___;
	//��Ϸ��ͼ��Ϣ����ƫ��
	const int g_o_map_obj = JFZR_REVERSAL_LOCAL_MAP_OBJ_OFFSET;
	//��Ӣ��ӳ��
	const int g_o_en2_ch = JFZR_REVERSAL_CHINESE_ENGLISH_MAP_OFFSET___;
	//�������������npc
	const int g_o_accept_complete_npc_info = JFZR_REVERSAL_TASK_ACCEPT_NPC_OBJ_OFFSET___;
	//����������
	const int g_o_accept_task_condition = JFZR_REVERSAL_TASK_ACCPET_CONDITION_OFFSET___;
	//�����������
	const int g_o_complete_task_condition = JFZR_REVERSAL_TASK_COMPLETE_CONDITION_OFFSET___;
	//�������֮������Ʒ
	const int g_o_task_reward_items = JFZR_REVERSAL_TASK_QUEST_REWARD_OFFSET___;
	//����֮���ܴ���
	const int g_o_task_accept_teleport = JFZR_REVERSAL_TAKS_ACCEPT_TELEPORT_OFFSET___;
	//�ѽ�����
	const int g_o_task_received1 = JFZR_REVERSAL_RECEIVED_TASK_OBJ_OFFSET1;
	const int g_o_task_received2 = JFZR_REVERSAL_RECEIVED_TASK_OBJ_OFFSET2;
	const int g_o_task_received3 = JFZR_REVERSAL_RECEIVED_TASK_OBJ_OFFSET3;
	const int g_o_task_received4 = JFZR_REVERSAL_RECEIVED_TASK_OBJ_OFFSET4;
	//npc�������
	const int g_o_task_npc[] = { JFZR_REVERSAL_SINGLE_TASK_OBJ_OFFSET1, JFZR_REVERSAL_SINGLE_TASK_OBJ_OFFSET2, JFZR_REVERSAL_SINGLE_TASK_OBJ_OFFSET3 + JFZR_REVERSAL_SINGLE_TASK_OBJ_OFFSET4___ };
	//�ɽ�������
	const int g_o_task_npc_acceptable = JFZR_REVERSAL_TASK_NPC_ACCPET_QUEST_OFFSET___;
	//�Ѿ���ɵ�����
	const int g_o_task_npc_complete = JFZR_REVERSAL_TASK_NPC_COMPLETE_QUEST_OFFSET___;
	//���б��ض��������
	const int g_o_all_local_obj_btree = JFZR_REVERSAL_ALLOBJ_MAP_FIN_ADDR_OFFSET;
	//�Ƿ�ɽ���
	//const int g_o_item_tradable = JFZR_REVERSAL_ITEM_BAG_IS_TRADABLE_OFFSET___;
	//ʣ�༼�ܵ�
	const int g_o_left_sp1 = JFZR_REVERSAL_SKILL_SP_OFFSET1___;
	const int g_o_left_sp2 = JFZR_REVERSAL_SKILL_SP_OFFSET2___;
	const int g_o_left_sp_index = JFZR_REVERSAL_SKILL_SP_INDEX_OFFSET___;
	//�ѽ����������
	const int g_o_received_task_active_condition = JFZR_REVERSAL_TASK_ACTIVE_CONDITION_OFFSET___;
	//game wnd proc addr
	const unsigned int						g_o_game_wnd_obj_addr = JFZR_REVERSAL_WND_PROC_OFFSET1___;
	//skill timestamp
	const unsigned int						g_o_skill_timestamp = JFZR_REVERSAL_TIME_STAMP_OFFSET;
	//npc type
	const unsigned int						g_o_game_obj_npc_type = JFZR_REVERSAL_LOCAL_OBJ_NPC_TYPE_FLAG_2___;
	//�Ƿ��ǽǶ���
	const unsigned int						g_o_is_arena_stage = JFZR_REVERSAL_SDB_STAGE_INFO_IS_ARENA_STAGE_OFFSET___;
	//pre action play time
	const unsigned int						g_o_pre_action_play_time1 = JFZR_REVERSAL_LOCAL_PREV_ACTION_PLAY_TIME_OFFSET1;
	const unsigned int						g_o_pre_action_play_time2 = JFZR_REVERSAL_LOCAL_PREV_ACTION_PLAY_TIME_OFFSET2;
	const unsigned int						g_o_pre_action_play_time3 = JFZR_REVERSAL_LOCAL_PREV_ACTION_PLAY_TIME_OFFSET3;
	//local room pos
	const unsigned int						g_o_local_room_pos = JFZR_REVERSAL_GET_LOCAL_ROOM_POSITION_OFFSET___;
	//////////////////////////////////////////////////////////////////////////
}