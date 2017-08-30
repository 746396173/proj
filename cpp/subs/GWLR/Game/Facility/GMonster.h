#pragma once
#include "GameObj.h"

class GMonsterBase : public GameObjBase{
public:
	GMonsterBase();
	bool ObjValid() override;

public:
	stCD_ObjDbInfo*		game_obj_db_info_;
};

class GMonster : public GMonsterBase{
public:
	GMonster();
	void DebugInfo() const override;
	const std::string& GetCnName() const;
	const std::string& GetTitle() const;
	CD_En_ObjSubType GetSubType() const;
	void SetCurHp( int cur_hp );
	bool IsBoss() const;
	int GetObjDbId() const;
	bool ObjValid() override;

protected:
	bool UpdateImpl() override;

private:
	int GetCurHp() const;

protected:
	int					cur_hp_;

public:
	GObjDbInfo			obj_db_info_;
};

//��Ҫ������������£����µ�ʱ����ȥhook����������
class GMonster_HitPartBase : public GMonster{
public:
	GMonster_HitPartBase();
	stCD_BodyPartObj* GetBodyPartsObj() const;
	bool SetBodyPartsObjAddr(stCD_BodyPartObj* body_part_obj);
	bool ObjValid() override;
	bool UpdatePacketId() override;

public:
	stCD_BodyPartObj*	body_parts_obj_;
	stCD_DummyArray<stCD_BodyPartInfo>	body_parts_info_;
};

//��λ�޸�
class GMonster_HitPart : public GMonster_HitPartBase{
	typedef std::vector<stCD_BodyPartInfo> BodyPartsT;
	typedef std::map<std::string, int> BodyPart2IdxT;
	typedef std::map<std::string, BodyPart2IdxT> MonsterName2BodyPartInfoT;

public:
	GMonster_HitPart();
	GMonster_HitPart(const GMonster_HitPart&) = delete;
	GMonster_HitPart& operator = (const GMonster_HitPart&) = delete;
	bool From( const GMonster_HitPartBase& rhs );

	void SetHitInfo( int cur_hit_part_idx, int hit_cnt, DWORD cur_packet_id );
	//SharedMutex& GetBodyPartMutex();
	const stCD_BodyPartInfo* GetCurHitPart() const;
	bool HasHitCnt() const;
	void DecHitCnt();
	static GMonster_HitPart& GetMonsterHitPart();
	void ClrAll();

private:
	bool UpdateImpl() override;
	void DoUpdateClear() override;

	//��λ��Ϣ
public:
	//��ӹ��ﲿλ��Ϣ
	bool AddMonsterBodyPartInfo( const std::string& monster_name, const std::string& part_name, int body_part_idx );
	//Ѱ�ҵ�ǰ�����ָ����λ������
	int FindThePartIdx( const std::string& monster_name, const std::string& part_name ) const;
	int FindThePartIdx( const std::string& part_name ) const;
	//��������������λ��λ����
	int FindPartIdxByTaskDesc( const std::string& monster_name, const std::string& task_desc ) const;
	const MonsterName2BodyPartInfoT::value_type* FindByMonsterName( const std::string& monster_name ) const;
	//���֧�ֵĹ��ﲿλ��Ϣ
	void DebuInfo_AllBodyPart();
	//���Ե�ǰ��λ��Ϣ
	bool TestCurBodyPartInfo() const;

private:
	//BodyPartsT		body_parts_;
	int				cur_hit_part_idx_;		//��ǰҪ�����Ĳ�λ����
	int				hit_cnt_;				//�������������Ϊ0����Ͳ��޸�������
	bool			is_new_hit_;
	//SharedMutex		body_part_mutex_;

	MonsterName2BodyPartInfoT	monster_part_info_;

public:
	DWORD			cur_hit_obj_packet_id_;
};