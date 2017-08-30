#pragma once
/*
@author zhp
@date 2017/4/26 21:11
@purpose for actions
CA->Common Action.
*/
#include <boost/enable_shared_from_this.hpp>
#include <deque>
#include <type_traits>
#include <ProtocolX/P_BaseTypeX.h>
#include <Net/IoTimer.h>
#include <CmnMix/Cmn_PocoMore.h>
#include "CA_Types.h"
#include <luabind/LuaBase.hpp>
#include "../DependSelfLib.h"

//////////////////////////////////////////////////////////////////////////
/*
��Ϊ����ִ�У�Ҳ���Ա���ֹ����ֹ���õ��쳣��
tester����Ϊ�����ߡ������ߣ��������ж�ĳ��������ĳ����Ϊ��
ProductTester����Ʒ�����ߣ������Ʒ��������ˣ���ô��������Product��Consumer��
Producer�������ߣ������Ԫ�ض���ProductTester��Producer����ProductTester��������Ʒ�Ƿ�ϸ񣬲������Ǻ���Product��
Consumer�������ߣ���������Product�ġ�
Decoration��װ��Ʒ��װ��������װ�εĶ��󡣶���FastTester��Decoration����tester�������������е���Ϊ��
Parent�����ף�����DecorationΪ�գ�Parent����tester�������������е���Ϊ��
******************
CA_IAction����ʾһ����Ϊ�������Ͽ������κ���Ϊ���κκ���ʵ�ֵ���Ϊ����������һ��Action��
CA_Action����Ϊ��ͨ�õ�Ĭ��ʵ�֣������ǵ�����Ϊ��Ҳ�����Ƕ����Ϊ��
CA_Actions����Ϊ��������ʾ�����Ϊ��ÿ��run��ʱ�����α�����������Ϊ��
CA_Consumer��������ģʽ����ʾ�����Ϊ����push˳��ִ��һ������Ϊ���൱�ڶ��С�
CA_EnsureConsumer��ȷ�������ߣ�AddEnsure�ӿڿ���ȷ��������Ϊ�ܹ�ִ������ִ����ϣ������Ƿ���������Ϊ�׳��쳣��
CA_SmartConsumer������CA_EnsureConsumer���ȿ���ȷ����Ϊ���ֿ��Զ�̬���tester��ProductTester��Producer���Ա���Բ����µ���Ϊ��
CA_Producer�������ߡ�
CA_FastProducer�����������ߣ�����кϸ��Product�����Ѹ��ת��Consumer������Consumerʹ�ø�Product��
CA_Product����Ʒ�������Դ���һ��ProductTester���Ա��ж������Ƿ��Ǻϸ�Ļ����������ģ�Ҳ���Դ���һ��Producer��
CA_Decorator��װ���ߡ�װ������װ��Ʒ�Ĺ�ϵ��װ������װ��װ��Ʒ��
CA_AsTimerAction����װһ��Action��ʹ�����ÿ����ʱ��ʹ������һ�Ρ�
CA_Tester�������ߡ������ߣ�ͨ����������һ��������
CA_FastTester����������ߡ�
CA_Not����װһ��Action��������kRR_Succeed->kRR_Failed����kRR_Failed->kRR_Succeed��
CA_Lambda���򵥵�Action��
*/
//////////////////////////////////////////////////////////////////////////
class CA_IAction : public CA_Define{
public:
	static void RegForLua(lua_State* l);
	virtual ~CA_IAction();
	//װ��Ʒ
	virtual CA_ActionPtr Decoration() const = 0;
	virtual CA_ActionPtr Parent() const = 0;
	virtual CA_ActionPtr Consumer() const = 0;
	//��Action�ļ����ߡ������ߡ�
	virtual CA_ActionPtr Tester() = 0;
	virtual void SetParent(const CA_ActionPtr& parent) = 0;
	virtual void SetConsumer(const CA_ActionPtr& consumer) = 0;
	virtual bool IsRunning() const = 0;
	virtual CA_RunRes Run() = 0;
	virtual void Terminate(enTerminateFlag terminate_flag) = 0;
	virtual void Terminate(enTerminateFlag terminate_flag, const CA_ActionPtr& dst_action) = 0;
	void Terminate(int terminate_flag){ return Terminate(enTerminateFlag(terminate_flag)); }
	void Terminate(int terminate_flag, const CA_ActionPtr& dst_action){ return Terminate(enTerminateFlag(terminate_flag), dst_action); }

public:
	virtual int Weight() const = 0;
	virtual void Add(const CA_ActionPtr& action) = 0;
	virtual void Erase(const CA_ActionPtr& action) = 0;
	virtual void AddEnsure(const CA_ActionPtr& action) = 0;
	virtual void EraseEnsure(const CA_ActionPtr& action) = 0;
	virtual void clear() = 0;
};
//////////////////////////////////////////////////////////////////////////
class CA_Action : public CA_IAction, public boost::enable_shared_from_this<CA_Action>{
public:
	CA_Action();
	CA_ActionPtr Decoration() const override;
	CA_ActionPtr Parent() const override final;
	CA_ActionPtr Consumer() const override;
	CA_ActionPtr Tester() override;
	void SetParent(const CA_ActionPtr& parent) override;
	void SetConsumer(const CA_ActionPtr& consumer) override;
	bool IsRunning() const override final;
	CA_RunRes Run() override final;
	void Terminate(enTerminateFlag terminate_flag) override final;
	void Terminate(enTerminateFlag terminate_flag, const CA_ActionPtr& dst_action) override final;
	using CA_IAction::Terminate;

public:
	int Weight() const override;
	void Add(const CA_ActionPtr& action) override;
	void Erase(const CA_ActionPtr& action) override;
	void AddEnsure(const CA_ActionPtr& action) override;
	void EraseEnsure(const CA_ActionPtr& action) override;
	void clear() override;

protected:
	virtual CA_RunRes OnRun() = 0;

private:
	CA_ActionWeakPtr	parent_;
	CA_ActionWeakPtr	consumer_;
	bool				is_running_;
};
//////////////////////////////////////////////////////////////////////////
class CA_Actions : public CA_Action{
public:
	typedef std::deque<CA_ActionPtr> ActionsType;

public:
	const ActionsType& GetActions() const;
	void Add(const CA_ActionPtr& action) override;
	void Erase(const CA_ActionPtr& action) override;
	void clear() override;

protected:
	CA_RunRes OnRun() override;
	void AddImpl(ActionsType& actions, const CA_ActionPtr& action);
	void EraseImpl(ActionsType& actions, const CA_ActionPtr& action);

protected:
	ActionsType		actions_;
};

class CA_EveryActions : public CA_Actions{
protected:
	CA_RunRes OnRun() override;
};

class CA_Consumer : public CA_Actions{
public:
	CA_ActionPtr Consumer() const override;
	void SetConsumer(const CA_ActionPtr& consumer) override;

protected:
	CA_RunRes OnRun() override;
	//�ɹ�����
	virtual void OnConsumedProduct(const CA_ActionPtr& product);
};

//ȷ��������
class CA_EnsureConsumer : public CA_Consumer{
public:
	CA_ActionPtr Tester() override;
	void AddEnsure(const CA_ActionPtr& action) override;
	void EraseEnsure(const CA_ActionPtr& action) override;
	void clear() override;

protected:
	CA_RunRes OnRun() override;
	void OnConsumedProduct(const CA_ActionPtr& product) override;

protected:
	CA_ActionPtr	tester_;

private:
	ActionsType		ensure_actions_;
};

class CA_SmartConsumer : public CA_Action{
	struct stEnsureTesterInfo{
		CA_ActionWeakPtr	action_;
		CA_ActionWeakPtr	action_tester_;
		CA_ActionWeakPtr	as_timer_action_;
	};
	typedef std::vector<stEnsureTesterInfo> EnsureTesterInfoCont;

public:
	CA_SmartConsumer();
	CA_ActionPtr Consumer() const override;
	void SetConsumer(const CA_ActionPtr& consumer) override;
	CA_ActionPtr Tester() override;
	void Add(const CA_ActionPtr& action) override;
	void Erase(const CA_ActionPtr& action) override;
	void clear() override;
	void AddEnsure(const CA_ActionPtr& action) override;
	//action_tester��������ͨ��tester��Ҳ������ProductTester����������Producer��
	void AddEnsure(const CA_ActionPtr& action, const CA_ActionPtr& action_tester);
	void EraseEnsure(const CA_ActionPtr& action) override;
	//ȫ�ּ��
	void AddTester(const CA_ActionPtr& tester);
	void EraseTester(const CA_ActionPtr& tester);

protected:
	CA_RunRes OnRun() override;

protected:
	CA_ActionPtr				tester_;

private:
	CA_T<CA_EnsureConsumer>		consumer_impl_;
	CA_ActionPtr				timer_actions_;
	CA_ActionPtr				impl_;
	EnsureTesterInfoCont		ensure_testers_;
};

//�����ߵ���Ԫ����ProductTester����ProductTester����Ԫ��ֻ��һ������Product��
class CA_Producer : public CA_Actions{
protected:
	CA_RunRes OnRun() override final;
	virtual void OnProduce(const CA_ActionPtr& product, const CA_ActionPtr& consumer);
	virtual enRunRes OnPoor();
};

template<CA_Define::enRunRes OnPoorResult>
class CA_ProducerT : public CA_Producer{
protected:
	enRunRes OnPoor() override final{
		return OnPoorResult;
	}
};

template<CA_Define::enRunRes OnPoorResult>
class CA_FastProducer : public CA_ProducerT<OnPoorResult>{
protected:
	void OnProduce(const CA_ActionPtr& product, const CA_ActionPtr& consumer) override{
		__super::OnProduce(product, consumer);
		assert(consumer);
		Terminate(kTF_ReRun, consumer);
	}
};
//////////////////////////////////////////////////////////////////////////
class CA_Decorator : public CA_Action{
public:
	CA_ActionPtr Decoration() const override final;
	CA_ActionPtr Tester() override;
	void SetParent(const CA_ActionPtr& parent) override final;
	void SetConsumer(const CA_ActionPtr& consumer) override final;
	void Add(const CA_ActionPtr& decoration) override;
	void Erase(const CA_ActionPtr& decoration) override;
	void clear() override;
	int Weight() const override final;

protected:
	CA_RunRes OnRun() override;

private:
	CA_ActionPtr	decoration_;
};

class CA_AsTimerAction : public CA_Decorator{
public:
	CA_AsTimerAction(const CA_ActionPtr& timer_action, pt_dword milli_seconds);
	void SetTimerAction(const CA_ActionPtr& timer_action);
	CA_ActionPtr Tester() override;

protected:
	CA_RunRes OnRun() override;

private:
	DateTimeLocal		last_time_;
	IoTimerPtr			io_timer_;
	CA_ActionPtr		timer_action_;
	pt_dword			milli_seconds_;
};

//�����ߣ���Ӧ�ü̳���CA_Decorator����Ϊtester�Բ�Ʒ�ı���Ӧ���������á�
class CA_Tester : public CA_Action{
public:
	CA_ActionPtr Tester() override;

protected:
	CA_RunRes OnRun() override;
	virtual bool Test() = 0;
};

class CA_FastTester : public CA_Tester{
public:
	CA_FastTester();

protected:
	CA_RunRes OnRun() override final;

protected:
	enTerminateFlag		terminate_flag_;
};

class CA_EnsureTester : public CA_Decorator{
public:
	void AddEnsure(const CA_ActionPtr& action) override;
	void EraseEnsure(const CA_ActionPtr& action) override;
	void clear() override;
	bool IsTesterError(const CA_RunRes& run_res) const;

protected:
	CA_RunRes OnRun() override;

private:
	CA_RunRes RunOneTester(const CA_ActionPtr& tester);

private:
	CA_T<CA_Actions>		action_testers_;
	CA_Actions::ActionsType	action_testers_old_;
	CA_ActionPtr			as_timer_action_;
	CA_ActionPtr			action_do_impl_;
};

class CA_ProductTester : public CA_Tester{
public:
	CA_ActionPtr Decoration() const override final;
	void Add(const CA_ActionPtr& product) override;
	void Erase(const CA_ActionPtr& product) override;
	void clear() override;

protected:
	CA_ActionWeakPtr	product_;
};

class CA_Product : public CA_Tester{
public:
	CA_ActionPtr Tester() override;
	virtual CA_ActionPtr Producer();

protected:
	CA_RunRes OnRun() override;
	virtual CA_ActionPtr MakeProductTester(const CA_ActionPtr& shared_this);

private:
	CA_ActionWeakPtr		product_tester_;
	CA_ActionWeakPtr		producer_;
};

//����CA_FastProduct��˵�����Բ���Producer�ӿ��ˡ�
class CA_FastProduct : public CA_Product{
protected:
	CA_ActionPtr MakeProductTester(const CA_ActionPtr& shared_this) override;

private:
	CA_ActionPtr Producer() override final;
};

template<typename ProductImplT_, typename ProductBase>
class CA_ProductT : public ProductBase{
public:
	typedef typename std::conditional<std::is_same<ProductImplT_, CA_IAction>::value,
		CA_ActionPtr, CA_T<ProductImplT_> >::type ProductImplType;
	typedef CA_ProductT ProductType;

public:
	void Add(const CA_ActionPtr& product_impl) override{
		if (product_impl.get() == this)
		{
			assert(false);
			return;
		}
#ifdef _DEBUG
		if (product_impl)
		{
			if (!dynamic_cast<ProductImplT_*>(product_impl.get()))
			{
				assert(false);
				return;
			}
		}
#endif
		//__super::Add(product_impl);
		product_impl_ = product_impl;
	}
	void Erase(const CA_ActionPtr& product_impl) override{
		//__super::Erase(product_impl);
		if (product_impl_ == product_impl)
			product_impl_.reset();
	}
	void clear() override{
		//__super::clear();
		product_impl_.reset();
	}

protected:
	CA_RunRes OnRun() override final{
		if (!product_impl_)
			return __super::OnRun();
		return product_impl_->Run();
	}

protected:
	ProductImplType		product_impl_;
};

class CA_Not : public CA_Decorator{
protected:
	CA_RunRes OnRun() override final;
};

template<typename ActionBase, typename FnT>
class CA_Lambda : public Details::CA_LambdaImpl<std::is_base_of<CA_Tester, ActionBase>::value,
	ActionBase, FnT>{
public:
	CA_Lambda(const FnT& fn) : MyLambdaType(fn){}
};
//////////////////////////////////////////////////////////////////////////
class CA_Factory{
	template<typename AddPolicy>
	struct stAddHelper{
		template<typename... SubActions>
		static void Add(const CA_ActionPtr& parent, const SubActions&... sub_actions){
			return AddSubActionImpl_(parent, sub_actions...);
		}
	};
	template<>
	struct stAddHelper<CA_tagAddEnsure>{
		template<typename... SubActions>
		static void Add(const CA_ActionPtr& parent, const SubActions&... sub_actions){
			return AddEnsureSubActionImpl_(parent, sub_actions...);
		}
	};

public:
	virtual ~CA_Factory();
	static CA_T<CA_AsTimerAction> MakeAsTimerAction(const CA_ActionPtr& decoration, const CA_ActionPtr& timer_action, pt_dword milli_seconds);
	static CA_ActionPtr MakeNot(const CA_ActionPtr& decoration);
	template<typename ActionT, typename AddPolicy = CA_tagAdd, typename... SubActions>
	static CA_T<ActionT> MakeAction(const SubActions&... sub_actions){
		CA_T<ActionT> res(new ActionT);
		if (!res)
		{
			assert(false);
			return nullptr;
		}
		stAddHelper<AddPolicy>::Add(res, sub_actions...);
		return res;
	}
	template<typename ActionBase, typename FnT, typename... SubActions>
	static CA_ActionPtr MakeLambda(const FnT& fn, const SubActions&... sub_actions){
		CA_ActionPtr res(new CA_Lambda<ActionBase, FnT>(fn));
		AddSubActionImpl_(res, sub_actions...);
		return res;
	}
	template<typename FnT>
	static CA_ActionPtr MakeLambda(const FnT& fn){
		return CA_ActionPtr(new CA_Lambda<CA_Action, FnT>(fn));
	}
	//product_tester��ü̳���CA_Decorator��
	template<typename... ProductsInfo>
	static CA_ActionPtr MakeProducer(const CA_ActionPtr& consumer, const ProductsInfo&... products_info){
		return MakeProducer<CA_FastProducer<CA_IAction::kRR_Succeed> >(consumer, products_info...);
	}
	template<typename ProducerT, typename... ProductsInfo>
	static CA_ActionPtr MakeProducer(const CA_ActionPtr& consumer, const ProductsInfo&... products_info){
		if (!consumer)
		{
			assert(false);
			return nullptr;
		}
		CA_ActionPtr producer = MakeAction<ProducerT>();
		if (!producer)
		{
			assert(false);
			return nullptr;
		}
		producer->SetConsumer(consumer);
		FillProducts(producer, products_info...);
		return producer;
	}
	template<typename... ProductsInfo>
	static void FillProducts(const CA_ActionPtr& producer, const ProductsInfo&... products_info){
		AddProductImpl_(producer, products_info...);
	}
	template<typename... SubActions>
	static CA_T<CA_Actions> MakeActions(const SubActions&... sub_actions){
		return MakeAction<CA_Actions>(sub_actions...);
	}
	template<typename... SubActions>
	static CA_ActionPtr MakeConsumer(const SubActions&... sub_actions){
		return MakeAction<CA_Consumer>(sub_actions...);
	}
	template<typename... SubActions>
	static CA_T<CA_EnsureConsumer> MakeEnsureConsumer(const SubActions&... sub_actions){
		return MakeAction<CA_EnsureConsumer, CA_tagAddEnsure>();
	}

private:
	static void AddSubActionImpl_(const CA_ActionPtr& parent){}
	static void AddSubActionImpl_(const CA_ActionPtr& parent, const CA_ActionPtr& sub_action){
		assert(sub_action);
		parent->Add(sub_action);
	}
	template<typename... SubActions>
	static void AddSubActionImpl_(const CA_ActionPtr& parent, const CA_ActionPtr& sub_action, const SubActions&... sub_actions){
		AddSubActionImpl_(parent, sub_action);
		AddSubActionImpl_(parent, sub_actions...);
	}
	static void AddProductImpl_(const CA_ActionPtr& producer){}
	static void AddProductImpl_(const CA_ActionPtr& producer, const CA_ActionPtr& product_tester, const CA_ActionPtr& product){
		if (!product_tester || !product)
		{
			assert(false);
			return;
		}
		product_tester->Add(product);
		producer->Add(product_tester);
	}
	template<typename... ProductsInfo>
	static void AddProductImpl_(const CA_ActionPtr& producer, const CA_ActionPtr& product_tester, const CA_ActionPtr& product, const ProductsInfo&... products_info){
		AddProductImpl_(producer, product_tester, product);
		AddProductImpl_(producer, products_info...);
	}
	static void AddEnsureSubActionImpl_(const CA_T<CA_EnsureConsumer>& parent){}
	static void AddEnsureSubActionImpl_(const CA_T<CA_EnsureConsumer>& parent, const CA_ActionPtr& sub_action){
		assert(sub_action);
		parent->AddEnsure(sub_action);
	}
	template<typename... SubActions>
	static void AddEnsureSubActionImpl_(const CA_T<CA_EnsureConsumer>& parent, const CA_ActionPtr& sub_action, const SubActions&... sub_actions){
		AddEnsureSubActionImpl_(parent, sub_action);
		AddEnsureSubActionImpl_(parent, sub_actions...);
	}
};
//////////////////////////////////////////////////////////////////////////