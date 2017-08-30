#pragma once
/*
@author zhp
@date 2017/1/11 16:36
@purpose state machine
*/
#include <luabind/luabind.hpp>
#include "../DependSelfLib.h"
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <CmnMix/Cmn_PocoMore.h>
#include "DmOper.h"
//////////////////////////////////////////////////////////////////////////
/*
StateRefNode����ʱδ�õ���
StateNodeCont��״̬����������ͨ��ֻ���������ڵ㡣
StateNodePriCont��˽��������㡣
LuaStateNode������״̬�ڵ�ľ�����Ϊ�������ࡣ
StateNodeUnion����ȻStateNodeUnion�Ǽ̳���StateNodeCont�ģ�������������������������һ������Ĵ��ڡ�
	��fn_prepare�������������ӽڵ�����ģ�1.�ӽڵ��fn_prepareȫ�����㣻2.�ӽڵ��fn_prepare����һ�����㡣
	��fn_handle���������StateNodeUnion�Լ�����ɣ�Ҳ����ָ�����ӽڵ�����ɡ�
	��NextState�ļ����������StateNodeUnion�Լ�����ɣ�Ҳ����ָ�����ӽڵ�����ɡ�
----------------------------------------------------
lua���ø�ʽ��
{
	[StateContNode("�������1")] = {
		{ "LuaStateNode���1", fn_prepare, fn_handle },
		{ "LuaStateNode���2", fn_prepare, fn_handle, fn_next_state },
		[StateUnionNode("״̬���Ͻ��1")] = {
			{ "LuaStateNode���1", fn_prepare, fn_handle },
			{ "LuaStateNode���2", fn_prepare, fn_handle, "�������1.״̬���Ͻ��2" },
		},
		[״̬���Ͻ��("״̬���Ͻ��2")] = {
			{ "LuaStateNode���1", fn_prepare, fn_handle },
		},
	},
	[״̬�������("�������2")] = {
		{ "LuaStateNode���2", fn_prepare, fn_handle, "�������1.LuaStateNode���1" },
	},
	[StateFindPicNode("״̬��ͼ���")] = {
	},
}
----------------------------------------------------
StateContNode/״̬������㣬�����ǲ�����Ϣ��
@p1->state_name���ַ������͡�����Ϊ�ա�
@p2->is_private_cont,�Ƿ�˽�д��ڡ���Ϊ�գ�Ĭ��Ϊfalse��
StateUnionNode/״̬������㣬�����ǲ�����Ϣ��
@p1->state_name���ַ������͡�����Ϊ�ա�
@p2->is_all���������ͣ�true��ʾ�ӽ���Prepareȫ������������㣬false��ʾ�����ӽ������ͻ����㣻
	 fn_prepare���������͡�Ϊ�ձ�ʾtrue��
@p3->handle_node_name���ַ������ͣ���ʾ���ɸ��ӽڵ�ȥ����
	 fn_handle���������͡�Ϊ�ձ�ʾhandle_node_name��ֵΪ��һ���������֡�
@p4->next_state_node_name,�ַ������ͣ���ʾ��һ״̬���ж��ɸ��ӽڵ�ȥ������
	 next_state_path���ַ������ͣ���ʾ��һ״̬��·����Ϊ����next_state_node_name���֣�next_state_path�ĵ�һ���ַ������ǿո��ַ���
	 next_state_is_parent���������ͣ�	true��ʾ��һ״̬�Ǹ���㣬false��ʾ��һ״̬Ϊ�գ�
	 fn_next_state���������͡�Ϊ�ձ�ʾtrue��
@p5->next_state_timeout���������ͣ�
	 Ҳ�����ǲ������ͣ�true��ʾdef_next_state_timeout��false��ʾ0��ֻ��@p4��next_state_is_parent��fn_next_state��next_state_path,@p5����Ч��Ϊ��Ĭ��Ϊ0��
StateFindPicNode/״̬��ͼ��㣬�����ǲ�����Ϣ��
@p1->state_name���ַ������͡�����Ϊ�ա�
@p2->dm����Į����
	Ҳ�����Ǻ������ͣ��������dm���󡣲���Ϊ�ա�
@p3->fn_handle_find_pic���������ͣ�
	 { fn_handle_find_pic1, fn_handle_find_pic2 }���������������Ϊ�գ���ʾĬ�ϴ���ɹ���
@p4->next_state_path���ַ������ͣ���ʾ��һ״̬��·����
	 next_state_is_parent���������ͣ�	true��ʾ��һ״̬��StateFindPicNode�ĸ���㣬false��ʾ��һ״̬ΪStateFindPicNode��㣻
	 fn_next_state���������͡�Ϊ�ձ�ʾnext_state_is_parent=false��
@p5->next_state_timeout���������ͣ�
	 Ҳ�����ǲ������ͣ�true��ʾdef_next_state_timeout��false��ʾ0��Ϊ��Ĭ��Ϊ0��
----------------------------------------------------
StateFindPicNode�ӽ���ʽ��{...}�������ǲ�����Ϣ��
@p1->pic_name���ַ������͡�
	 { pic_name1, pic_name2, ... },�����ͣ���ʾ��Ҫͬʱ�ҵ��⼸��ͼƬ(fn_handle_find_pic��pic_name����Ϊpic_name1)������Ϊ�ա�
@p2->fn_handle_idx���������ͣ�
	 fn_handle_find_pic���������͡���Ϊ�գ�Ĭ��Ϊ0.
@p3->next_state_path���ַ������ͣ���ʾ��һ״̬��·����
	 next_state_is_parent���������ͣ�	true��ʾ��һ״̬��StateFindPicNode�ĸ���㣬false��ʾ��һ״̬Ϊ�գ�
	 fn_next_state���������͡�Ϊ�ձ�ʾ����StateFindPicNode����
fn_handle_find_pic�Ĳ�����(StateNode, pic_name,pos_x, pos_y)���䷵��ֵ��fn_handle��ͬ��
----------------------------------------------------
LuaStateNode��㣺
state_name��fn_prepare����Ϊ�գ�fn_handle��Ϊ�գ���ʾ����Ҫ���κ��£����ҷ���true��
{state_name,fn_prepare,fn_handle}->CreateLuaState(state_name,lua_fn_prepare,lua_fn_handle,0);//NextState�Ǹ��ڵ㣬ֱ�ӷ��ظ��ڵ㣬û���ӳ١�
{state_name,fn_prepare,fn_handle,true}->CreateLuaState(state_name,lua_fn_prepare,lua_fn_handle,def_next_state_timeout_);//NextState�Ǹ��ڵ㣬�ӳٷ��ظ��ڵ㣬�ӳ���def_next_state_timeout_��
{state_name,fn_prepare,fn_handle,false}->CreateLuaState(state_name,lua_fn_prepare,lua_fn_handle);//NextStateΪ�գ�ͨ����ʾѭ�����������������ˣ���
{state_name,fn_prepare,fn_handle,next_state_timeout}->CreateLuaState(state_name, lua_fn_prepare, lua_fn_handle, next_state_timeout);//NextState�Ǹ��ڵ㣬�ӳٷ��ظ��ڵ㣬�ӳ���next_state_timeout��
{state_name,fn_prepare,fn_handle,next_state_path}->CreateLuaState(state_name,lua_fn_prepare,lua_fn_handle,next_state_path,def_next_state_timeout_);
{state_name,fn_prepare,fn_handle,next_state_path,next_state_timeout}->CreateLuaState(state_name,lua_fn_prepare,lua_fn_handle,next_state_path,next_state_timeout);
{state_name,fn_prepare,fn_handle,fn_next_state}->CreateLuaState(state_name,lua_fn_prepare,lua_fn_handle,fn_next_state,def_next_state_timeout_);
{state_name,fn_prepare,fn_handle,fn_next_state,next_state_timeout}->CreateLuaState(state_name,lua_fn_prepare,lua_fn_handle,fn_next_state,next_state_timeout);
----------------------------------------------------
state_name��״̬�������֣�ͨ��������ǰ״̬��λ����һ״̬����λ��ʽ���ƣ�root_node_name.next_node_name.the_node_name��Ҳ����ʡ�����ڵ�����֣�next_node_name.the_node_name��
fn_prepare�������жϵ�ǰ��Ϸ�����Ƿ���ϸ�״̬��
	����LUA_TNIL��ʾ�����ϵ�ǰ״̬��
	����true��ʾ��ǰ״̬���ϣ�
	�����ַ�����ʾ�ڵ��·�����ýڵ���ϵ�ǰ��Ϸ������
	����StateNodePtr��ʾ���ýڵ���ϵ�ǰ��Ϸ������
fn_handle������ǰ��Ϸ״̬��Ĭ�Ϸ���true����ʾ��״̬�Ѵ�����ɣ����Խ��ж�λ��һ״̬�ˣ�����false����ʾû�д���ɹ������ٴν���fn_prepare�����̣�ѭ��ֱ��fn_handle�����档
NextState�ļ��㷽ʽ�����֣�
	1.���ؿգ���ʾ��ǰ״̬��û����һ״̬�ˣ�
	2.���ظ��ڵ㣻
	3.������һ��״̬����·����
	4.ͨ��lua��������õ���һ״̬��㡣
next_state_timeout�����õ���һ״̬����next_state_timeout��Ϊ0�������жϸ�״̬��fn_prepare�Ƿ������㡣
next_state_path���ַ����ǽ��·��������λ����һ����㡣
fn_next_state����lua�����ɼ���õ���һ״̬������ֵ��4�֣�
	1.���ؿձ�ʾû����һ״̬�ˣ�
	2.����true��ʾ��һ״̬���ǵ�ǰ״̬������false��ʾû����һ״̬�ˣ�
	3.�����ַ�������ʾ��һ״̬��·����
	4.ֱ�ӷ���StateNodePtr���󣬸ö��������һ״̬�ˡ�
----------------------------------------------------
*/
//////////////////////////////////////////////////////////////////////////

class StateResolver;
class StateNode;
typedef boost::shared_ptr<StateNode> StateNodePtr;
typedef boost::weak_ptr<StateNode> StateNodeWeakPtr;
class StateNode : public boost::enable_shared_from_this<StateNode>{
public:
	StateNode();
	virtual ~StateNode();
	static void RegForLua(lua_State* l);
	bool Add(StateNode* sub_node, bool replace_existed = false);
	virtual bool Add(const StateNodePtr& sub_node, bool replace_existed = false);
	virtual bool Erase(const StateNodePtr& sub_node);
	bool Erase(const std::string& path);
	virtual StateNodePtr Find(const std::string& path) const;
	//ֻ��ѯ�ӽڵ�
	virtual StateNodePtr FindChild(const std::string& child_name) const;
	StateNodePtr Parent() const;
	bool SetParent(const StateNodePtr& parent);
	StateNodePtr GetRoot() const;
	template<typename T>
	T* As(){
		return dynamic_cast<T*>(this);
	}
	void SetName(const std::string& name);
	const std::string& GetName() const;
	std::string GetAbsolutePath() const;
	bool IsSamePath(const std::string& path) const;
	virtual bool IsCont() const;
	virtual bool Parse(StateResolver& resolver, const luabind::object& tbl);
	void SetNextStateTimeout(pt_dword next_state_timeout);
	pt_dword GetNextStateTimeout() const;

public:
	virtual StateNodePtr Prepare();
	virtual bool Handle();
	virtual StateNodePtr NextState();

private:
	bool _Add_1_(const StateNodePtr& sub_node);
	bool _Add_2_(const StateNodePtr& sub_node, bool replace_existed);
	bool _Erase_1_(const StateNodePtr& sub_node);
	bool _Erase_2_(const std::string& path);

private:
	StateNodeWeakPtr		parent_;
	std::string				name_;

protected:
	pt_dword				next_state_timeout_;
};

class StateRefNode : public StateNode{
public:
	StateRefNode(const std::string& node_path);
	bool Add(const StateNodePtr& sub_node, bool replace_existed) override;
	bool Erase(const StateNodePtr& sub_node) override;
	StateNodePtr Find(const std::string& path) const override;
	StateNodePtr FindChild(const std::string& child_name) const override;
	bool IsCont() const override;

public:
	StateNodePtr Prepare() override;
	bool Handle() override;
	StateNodePtr NextState() override;

private:
	StateNodePtr GetImpl() const;

private:
	std::string					node_path_;
	mutable	StateNodeWeakPtr	impl_;
};

class StateNodeCont : public StateNode{
	typedef std::vector<StateNodePtr> NodeCont;

public:
	StateNodeCont();
	bool Add(const StateNodePtr& sub_node, bool replace_existed) override;
	bool Erase(const StateNodePtr& sub_node) override;
	StateNodePtr Find(const std::string& path) const override;
	StateNodePtr FindChild(const std::string& child_name) const override;
	bool IsCont() const override;
	const NodeCont& GetNodes() const;
	bool Parse(StateResolver& resolver, const luabind::object& tbl) override;

public:
	StateNodePtr Prepare() override;

protected:
	bool ParseSubNode(StateResolver& resolver, const luabind::object& key, const luabind::object& tbl);

private:
	NodeCont		nodes_;
};

class StateNodePriCont : public StateNodeCont{
public:
	StateNodePtr Prepare() override;
};

class LuaStateNode : public StateNode{
private:
	LuaStateNode(const luabind::object& fn_prepare, const luabind::object& fn_handle, bool* out_valid);

public:
	class NextStatePolicy{
	public:
		virtual ~NextStatePolicy();
		virtual StateNodePtr CalcNextState(StateNode& self_node) = 0;
	};

public:
	LuaStateNode(const luabind::object& fn_prepare, const luabind::object& fn_handle, bool next_state_is_parent, bool* out_valid);
	LuaStateNode(const luabind::object& fn_prepare, const luabind::object& fn_handle, const std::string& next_state_path, bool* out_valid);
	LuaStateNode(const luabind::object& fn_prepare, const luabind::object& fn_handle, const luabind::object& fn_next_state, bool* out_valid);
	~LuaStateNode();

public:
	StateNodePtr Prepare() override;
	bool Handle() override;
	StateNodePtr NextState() override;

private:
	luabind::object		fn_prepare_;
	luabind::object		fn_handle_;
	NextStatePolicy*	next_state_policy_;
};

class StateNodeUnion : public StateNodeCont{
public:
	class PreparePolicy{
	public:
		virtual ~PreparePolicy();
		virtual StateNodePtr DoPrepare(StateNodeUnion& self_node) = 0;
	};
	class HandlePolicy{
	public:
		virtual ~HandlePolicy();
		virtual bool DoHandle(StateNode& self_node) = 0;
	};
	typedef LuaStateNode::NextStatePolicy NextStatePolicy;

public:
	StateNodeUnion();
	~StateNodeUnion();
	bool SetPrepareInfo(bool is_all);
	bool SetPrepareInfo(const luabind::object& fn_prepare);
	bool SetHandleInfo(const luabind::object& fn_handle);
	bool SetHandleInfo(const std::string& handle_node_name);
	bool SetNextStateInfo(const std::string& next_state_node_name);
	bool SetNextStateInfo(bool next_state_is_parent);
	bool SetNextStateInfo(const luabind::object& fn_next_state);
	bool SetNextStatePath(const std::string& next_state_path);
	bool IsCont() const override;

public:
	StateNodePtr Prepare() override;
	bool Handle() override;
	StateNodePtr NextState() override;

private:
	PreparePolicy*		prepare_policy_;
	HandlePolicy*		handle_policy_;
	NextStatePolicy*	next_state_policy_;
};

class StateNodeFindPic : public StateNodeCont{
public:
	typedef StateNodeUnion::HandlePolicy HandlePolicy;
	typedef LuaStateNode::NextStatePolicy NextStatePolicy;
	typedef boost::shared_ptr<HandlePolicy> HandlePolicyPtr;
	typedef boost::shared_ptr<NextStatePolicy> NextStatePolicyPtr;
	typedef std::vector<std::string> PicNameContT;
	struct stPicItem{
		PicNameContT		pic_names_;
		luabind::object		fn_handle_find_pic_;
		NextStatePolicyPtr	next_state_policy_;
		int					fn_handle_idx_;
		bool				next_state_nil_;
		stPicItem();
	};
	typedef std::vector<stPicItem> PicContT;
	typedef std::vector<luabind::object> ObjContT;

public:
	StateNodeFindPic();
	~StateNodeFindPic();
	bool SetDmObj(const luabind::object& dm);
	bool SetHandleInfo(const luabind::object& handle);
	bool SetNextStateInfo(const std::string& next_state_path);
	bool SetNextStateInfo(bool next_state_is_parent);
	bool SetNextStateInfo(const luabind::object& fn_next_state);
	bool Parse(StateResolver& resolver, const luabind::object& tbl) override;

public:
	StateNodePtr Prepare() override;
	bool Handle() override;
	StateNodePtr NextState() override;

private:
	const std::string& GetPicNameMix();
	bool ParsePicItem(stPicItem& item, const luabind::object& tbl);
	DmOper& GetDm() const;

private:
	PicContT			pic_items_;
	std::string			pic_name_mix_;
	ObjContT			fn_handles_;
	luabind::object		dm_holder_;
	mutable DmOper*		dm_;
	NextStatePolicy*	next_state_policy_;
	const stPicItem*	last_pic_item_;
	long				last_pos_x_;
	long				last_pos_y_;
};

class StateResolver{
	friend class StateNode;
	friend class StateNodeCont;
public:
	StateResolver();
	StateResolver(pt_dword def_next_state_timeout);
	virtual ~StateResolver();
	void SetRoot(const StateNodePtr& root);
	const StateNodePtr& GetRoot() const;
	const StateNodePtr& CurState() const;
	int Resolve();
	StateNodePtr ParseStates(const luabind::object& tbl);
	StateNodePtr ParseStates(const luabind::object& tbl, const std::string& root_state_name);
	StateNodePtr CreateLuaState(const std::string& state_name, const luabind::object& fn_prepare, const luabind::object& fn_handle);
	StateNodePtr CreateLuaState(const std::string& state_name, const luabind::object& fn_prepare, const luabind::object& fn_handle, pt_dword next_state_timeout);
	StateNodePtr CreateLuaState(const std::string& state_name, const luabind::object& fn_prepare, const luabind::object& fn_handle, 
		const std::string& next_state_path, pt_dword next_state_timeout);
	StateNodePtr CreateLuaState(const std::string& state_name, const luabind::object& fn_prepare, const luabind::object& fn_handle, 
		const luabind::object& fn_next_state, pt_dword next_state_timeout);
	StateNodePtr StateContNode(const std::string& state_name, bool is_private_cont);
	StateNodePtr StateUnionNode(lua_State* l, const std::string& state_name);
	StateNodePtr StateFindPicNode(lua_State* l, const std::string& state_name, const luabind::object& fn_find_pic);

protected:
	virtual bool DoNext();

private:
	StateNodePtr _StateContNode_2_(const std::string& state_name);
	StateNodePtr _ParseStates_1_(const luabind::object& tbl);
	StateNodePtr _ParseStates_2_(const luabind::object& tbl, const std::string& root_state_name);
	StateNodePtr _CreateLuaState_1_(const std::string& state_name, const luabind::object& fn_prepare, const luabind::object& fn_handle);
	StateNodePtr _CreateLuaState_2_(const std::string& state_name, const luabind::object& fn_prepare, const luabind::object& fn_handle, 
		const std::string& next_state_path, pt_dword next_state_timeout);
	StateNodePtr _CreateLuaState_3_(const std::string& state_name, const luabind::object& fn_prepare, const luabind::object& fn_handle,
		const luabind::object& fn_next_state, pt_dword next_state_timeout);
	StateNodePtr _CreateLuaState_4_(const std::string& state_name, const luabind::object& fn_prepare, const luabind::object& fn_handle, 
		pt_dword next_state_timeout);
	StateNodePtr ParseCreateLuaState(const luabind::object& tbl);

private:
	StateNodePtr	root_;
	StateNodePtr	cur_state_;
	DateTimeLocal	last_time_;
	pt_dword		def_next_state_timeout_;
};