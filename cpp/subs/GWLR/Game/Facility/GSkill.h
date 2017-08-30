#pragma once
/*
@author zhp
@date 2014/7/1 20:44
@purpose for skills
*/
#include <string>
#include <json/value.h>
#include <Common/UsefulFunc.h>
#include <Common/GameObjBase.h>
#include "GClass.h"

//��ѧskill
class GSkillObj{
public:
	GSkillObj(){
		skill_obj_addr_ = nullptr;
		skill_lvl_ = 0;
		skill_id_ = 0;
	}
	void SetSkillObjAddr( void* obj_addr );
	void* GetSkillObjAddr() const;
	const std::wstring& GetStrId() const;
	int GetLvl() const;
	DWORD GetId() const;
	//bool Update();
	
	//��json����
	
public:
	char*					skill_obj_addr_;
	std::wstring			skill_name_;
	int						skill_lvl_;
	DWORD					skill_id_;		//��������hash��==skill hash
};

//��ѧ����
class GSkillMgr : public GGameObjMgrBase{
public:
	typedef std::vector<GSkillObj> SkillContT;
	typedef TraverseTraits<GSkillObj&, GSkillObj&> SkillTraTraits;
	typedef SkillTraTraits::DoAnyTraverse DoAnySkillObjT;

	//������ˢ����Ϸ����
public:
	GSkillMgr();
	/*//��������
	bool UpdateAll();
	//���¹�������
	bool RebuildAll();*/

	//����������
public:
	//Ѱ�Ҽ��ܶ���
	GSkillObj* FindSkillObjIf( const DoAnySkillObjT& func );
	GSkillObj* FindSkillObjByStrId( const std::wstring& skill_name );
	GSkillObj* FindSkillObjById( DWORD skill_id );
	SkillContT& GetSkills();
	bool IsSkillEmpty() const;

public:
	//�õ�Ĭ��ʹ�õļ���
	GSkillObj* GetDefaultUseSkill();

	//�Զ��л��ɽ��ܵļ���
	bool SwtichAcceptableSkillBranch();

private:
	SkillContT				skills_;
};