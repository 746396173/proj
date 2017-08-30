#pragma once
//for su hui
#include "IStagePosInfo.h"

class StagePosInfo : public IStagePosInfo{
public:
	//�½�һ��pos info���󣬷���һ��pos info�ı�ʶ
	virtual DWORD OnNewPosInfoObj();
	//�½�һ��������󣬷���һ��room info�ı�ʶ
	virtual DWORD OnNewRoomInfoObj();
	//��һ��������pos info�ı�ʶ
	virtual void OnAddVertex( DWORD pos_info_obj_id, int vertex_id, float x, float y, float z );
	//��һ��������pos info�ı�ʶ
	virtual void OnAddEdge( DWORD pos_info_obj_id, int vertex_id_from, int vertex_id_to );
	//��һ�������Ƿ�������ʶ
	virtual void OnAddPosInfo( DWORD room_info_obj_id, int room_id, DWORD pos_info_obj_id );
	//�ڶ��������Ƿ�������ʶ
	virtual void OnAddStageInfo( int stage_id, DWORD room_info_obj_id );

	static StagePosInfo& GetMe();
};
