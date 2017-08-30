#pragma once
//for su hui

class IStagePosInfo{
public:
	virtual ~IStagePosInfo(){}
	//�½�һ��pos info���󣬷���һ��pos info�ı�ʶ
	virtual DWORD OnNewPosInfoObj() = 0;
	//�½�һ��������󣬷���һ��room info�ı�ʶ
	virtual DWORD OnNewRoomInfoObj() = 0;
	//��һ��������pos info�ı�ʶ
	virtual void OnAddVertex( DWORD pos_info_obj_id, int vertex_id, float x, float y, float z ) = 0;
	//��һ��������pos info�ı�ʶ
	virtual void OnAddEdge( DWORD pos_info_obj_id, int vertex_id_from, int vertex_id_to ) = 0;
	//��һ�������Ƿ�������ʶ
	virtual void OnAddPosInfo( DWORD room_info_obj_id, int room_id, DWORD pos_info_obj_id ) = 0;
	//�ڶ��������Ƿ�������ʶ
	virtual void OnAddStageInfo( int stage_id, DWORD room_info_obj_id ) = 0;
};

//��ȡ���������ַ��SetStagesPosInfoInterface,�����Ǻ�������������ʼ���ã�ֻ�ܵ���һ��
typedef void (*SetStagesPosInfoInterface_FuncT)( IStagePosInfo* stage_ptr );
//��ȡ������Ϣ���ɶ�ε���,��������DoGainTheStagesPosInfo
typedef void (*DoGainTheStagesPosInfo_FuncT)( const char* lua_full_file_name );