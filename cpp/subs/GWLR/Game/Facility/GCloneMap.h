#pragma once
/*
@author zhp
@date 2014/8/5 8:32
@purpose for����
*/
#include <Common/UsefulClass.h>
#include "GRoom.h"
#include "GameObj.h"
#include "GameObjMgr.h"

class GMapDb : public GGameObjBase{
public:
	GMapDb();
	void DebugInfo() const override;
	//�õ�����ȼ�
	int GetRequireRoleLvl() const;
	//�õ���ɫ�ȼ�����
	int GetFbRoleLvlLimit() const;
	//�Ƿ�����������
	bool IsKingFb() const;
	//�Ƿ���������Ӣ����
	bool IsKingCreamFb() const;

private:
	bool UpdateImpl() override;
	void DoUpdateClear() override;

public:
	stCD_MapDb*		map_db_;

public:
	std::string		map_name_;
	int				map_id_;
	int				map_db_info_id_;
	CD_En_FbType			fb_type_;			//��������
	CD_En_FbDifficulty	fb_diff_level_;		//�����Ѷȵȼ�

private:
	int				role_lvl_;			//��ɫ�ȼ�����
};

//�ɽ��ĸ���
class GEnterableFbMgr : public GGameObjMgrBase{
public:
	void DebugInfo() const override;
	const GMapDb* FindByName( const std::string& fb_name );
	const GMapDb* FindById( int fb_id ) const;

private:
	bool UpdateAllImpl() override;
	bool RebuildAllImpl() override;
	void DoRebuildUpdateClear() override;

public:
	std::vector<const GMapDb*>	enterable_fb_;
};

//���и�����Ϣ
class MapDbMgr : public GGameObjBase, public Singleton<MapDbMgr, Singleton_MakeMe>{
public:
	MapDbMgr();
	bool Update() override;
	void DebugInfo() const override;
	void DebugInfo_King() const;
	void DebugInfo_KingCream() const;
	const GMapDb* FindByName( const std::string& fb_name );
	const GMapDb* FindById( int fb_id );

private:
	bool UpdateImpl() override;
	void DoUpdateClear() override;

public:
	std::vector<GMapDb>	all_map_;
};

struct stFbDoorLink{
	int				template_map_id_;	//ģ���ͼID
	int				room_id_src_;		//Դ�����
	std::string		door_name_src_;		//Դ�����е��ŵ�����
	int				room_id_dst_;		//Ŀ�귿���
};

class GDoorLinkMgr : public Singleton<GDoorLinkMgr, Singleton_MakeMe>{
	typedef std::pair<std::string, int> DoorName2RoomIdT;
	typedef std::vector<DoorName2RoomIdT> DoorsLinkT;
	typedef std::map<int, DoorsLinkT> RoomIds2DoorsLinkT;
	typedef std::map<int, RoomIds2DoorsLinkT> FbDefId2RoomIdsT;
	typedef std::map<int, int> FbName2FbDefIdT;

public:
	void AddLink( const stFbDoorLink& door_link );
	boost::optional<int> FindTheDstRoomId( int template_map_id, int room_id_src, const std::string& door_name_src ) const;

private:
	FbDefId2RoomIdsT		fb_def_id2room_ids_;
};

class FbDoor : public GameObjBase{
public:
	FbDoor();
	bool ObjValid() override;
	void DebugInfo() const override;

private:
	bool UpdateImpl() override;
	void DoUpdateClear() override;
	bool UpdateOwnerRoomNum() override;
};

class FbDoorsMgr : public GameObjMgr_AnyObj, public Singleton<FbDoorsMgr, Singleton_MakeMe>{
public:
	FbDoorsMgr();
	bool RebuildAll() override;
};

//�ɼ���
class GCollectObj : public GameObjBase{
public:
	GCollectObj();
	void DebugInfo() const override;
	bool UpdateOwnerRoomNum() override;
	bool ObjValid() override;

private:
	bool UpdateImpl() override;
	void DoUpdateClear() override;

public:
	DWORD				monster_packet_id_;
};
class GCollectObjMgr : public GameObjMgr_AnyObj, public Singleton<GCollectObjMgr, Singleton_MakeMe>{
public:
	GCollectObjMgr();
	GameObjBase* FindNearestAsSameRoom( const GameObjBase& obj );
	GameObjBase* FindDeadMonster( const GameObjBase& obj );
	GameObjBase* FindDeadMonsterByPacketId( DWORD packet_id );
};

//��ֹ�Ķ�������������Ķ���
class GObjStatic : public GameObjBase{
public:
	GObjStatic();
	void DebugInfo() const override;

private:
	bool UpdateImpl() override;
	void DoUpdateClear() override;
	bool UpdateOwnerRoomNum() override;
};
class GObjStaticMgr : public GameObjMgr_AnyObj{
public:
	GObjStaticMgr(const std::string& obj_name);
};

//���Ͱ
class GObjMieHuoTong : public GameObjMgr_AnyObj{
public:
	GObjMieHuoTong();
};

class GCloneMap : public Singleton<GCloneMap, Singleton_MakeMe>{
public:
	GCloneMap();
};