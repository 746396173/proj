#pragma once
/*
@author zhp
@date 2014/7/6 21:36
@purpose manage game objects
*/
#include <Common/UsefulClass.h>
#include "GameObj.h"
#include <list>
#include <Common/Iterator.h>
#include <boost/shared_ptr.hpp>
#include <Common/GameObjBase.h>

class GameObjMgr : public GGameObjMgrBase, public Singleton<GameObjMgr, Singleton_MakeMe>{
	//type definitions
public:
	typedef std::list<GameObjBase::SelfPtrT> GameObjContT;
	typedef TraverseTraits<GameObjBase::SelfPtrT, GameObjBase::SelfPtrT&> GameObjTraTraits;
	typedef GameObjTraTraits::IteratorBase GameObjIterBase;
	typedef GameObjTraTraits::IteratorBasePtr GameObjIterPtr;
	typedef GameObjTraTraits::DoEveryTraverse DoEveryGameObjFuncT;
	typedef GameObjTraTraits::DoAnyTraverse DoAnyGameObjFuncT;
	typedef IteratorImpl<GameObjTraTraits, GameObjContT> GameObjIteratorImpl;
	typedef IteratorCounterImpl<GameObjTraTraits, GameObjContT> GameObjIterCounter;
	
public:
	GameObjMgr();

	//������ˢ����Ϸ����
public:
	//��������game object
	bool UpdateAll();
	//���¹�������
	bool RebuildUpdateAll();
	void ResetForceUpdate();
	//��Ϸ��������
	void OnGameObjDestroy( void* gameobj_addr );
	//ɾ����Ϸ����
	void DeleteGameObj( GameObjBase::SelfPtrT& gameobj );
	void SetGameObjParser( GameObj_Parser* game_obj_parser );

	//��Ϸ��������������
public:
	//�õ�������Ϸ����
	GameObjContT& GetAllGameObjs();
	bool IsGameObjsEmpty() const;
	std::size_t GetAllGameObjCnt() const;
	//�õ�ĳ�����͵���Ϸ��������
	std::size_t GetGameObjCntByType( GameObjType gameobj_type );
	//�õ�ĳ�����͵���Ϸ��������������
	std::size_t GetGameObjCntByTypeBut( GameObjType gameobj_type, const DoAnyGameObjFuncT& except_filter );
	//����ĳ�����͵���Ϸ����
	GameObjIterPtr TraverseGameObjByType( GameObjType gameobj_type );
	//����ĳ�����͵���Ϸ�������
	GameObjIterPtr TraverseGameObjByTypeBut( GameObjType gameobj_type, const DoAnyGameObjFuncT& except_filter );
	//����ĳ�����͵���Ϸ�����������
	GameObjIterPtr TraverseGameObjByTypeLimit( GameObjType gameobj_type, std::size_t max_cnt );
	//��������ĳЩ������ĳ�����͵���Ϸ�����������
	GameObjIterPtr TraverseGameObjByTypeBut_Limit( GameObjType gameobj_type, const DoAnyGameObjFuncT& except_filter, std::size_t max_cnt );
	//������������
	void DoItemByType( GameObjType gameobj_type, const DoEveryGameObjFuncT& func );
	void DoItemByTypeLimit( GameObjType gameobj_type, const DoEveryGameObjFuncT& func, std::size_t max_cnt );
	void DoItemUntilByType( GameObjType gameobj_type, const DoAnyGameObjFuncT& func );
	//����
	GameObjIterPtr TraverseIf( const DoAnyGameObjFuncT& func );
	//���ҵ�һ��
	GameObjBase::SelfPtrT FindIf( const DoAnyGameObjFuncT& func );
	GameObjIterPtr FindGameObjLimit( const DoAnyGameObjFuncT& func, std::size_t max_valid_cnt );
	GameObjBase::SelfPtrT FindGameObjByAddr( void* gameobj_addr );
	GameObjBase::SelfPtrT FindByName( const std::wstring& obj_name );
	GameObjBase::SelfPtrT FindBySerial( DWORD obj_serial );
	GameObjBase::SelfPtrT FindFirstByJob( const std::wstring& obj_job );
	//δ��������Ϸ����
	GameObjIterPtr TraverseAliveGameObj( GameObjType gameobj_type );
	GameObjIterPtr TraverseAliveGameObjLimit( GameObjType gameobj_type, std::size_t max_cnt );

public:
	//Ѱ��һ������ͼ����ƷNPC
	GameObjBase::SelfPtrT FindFirstShopNpc();

	//����������
public:
	void ResetNpcBlacklist();
	void AddNpcBlacklist( std::wstring&& obj_id );
	bool ExistTheBlacklist( const std::wstring& obj_id ) const;

private:
	bool DoUpdateImpl();

private:
	GameObjContT				game_objs_;
	GClass::TimerSyncExec		timer_sync_exec_;
	bool						force_update_;
	std::set<std::wstring>		npc_blacklist_;
	GameObj_Parser*				obj_parser_;
};

//factory
class GameObjFactory : public Singleton<GameObjFactory, Singleton_MakeMe>{
public:
	~GameObjFactory();
	GameObjBase::SelfPtrT CreateGameObj( GameObjType obj_type );
};