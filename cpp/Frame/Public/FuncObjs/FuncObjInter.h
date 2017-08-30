#pragma once
/*
@author zhp
@date 2014-1-01
@purpose ��ͬ���̵Ķ�����̼�ͨ��ʹ��
*/
#include "stdafx.h"
#include "FuncObj.h"
#include <boost/function.hpp>
#include "../DependSelfLib.h"
#include <ProtocolX/P_DefinesX.h>

//������console
//interface internal
class FuncObj_IInter : public FuncObj{
public:
	FuncObj_IInter(FuncObj* parent);
};

class FuncObj_Inter : public FuncObj_IInter{
protected:
	FuncObj_Inter(FuncObj_Inter* sink, FuncObj* parent);

public:
	typedef FunctionVoid ExecFnType;
	//֪ͨ��Ϣ
	static const UINT kMsgNotify = MAXWORD - 1111;

public:
	virtual void Close();
	//�첽ִ��
	virtual bool AsyncExec(const ExecFnType& async_func) = 0;
	//����״̬
	bool GetState();
	//����״̬
	void SetState(bool state);

protected:
	bool OperEncode(P_FuncObjOper oper, const void* param, pt_dword param_size, 
		FuncObj* msg_owner) override;

private:
	//decode
	void Decode(P_Main* p_main, pt_dword msg_size);

protected:
	bool				state_;
	FuncObj_Inter*		sink_;
};

//ֻ����һ��ʵ��
//�����������Ϸ�������������߳���ִ��
class FuncObj_GWnd : public FuncObj_Inter{
public:
	FuncObj_GWnd( HWND hwnd, FuncObj_Inter* sink );
	~FuncObj_GWnd();

public:
	//new_hwndΪ�գ������ó�֮ǰ��
	bool ResetHwnd( HWND new_hwnd );
	bool AsyncExec(const ExecFnType& async_func) override;
	//ͬ������
	template<typename ResultT, typename FuncT>
	bool SyncExec( ResultT& res, const FuncT& func ){
		ExecFnType fn = [&res, &func](){
			res = func();
		};
		return SyncExec(fn);
	}
	bool SyncExec( const ExecFnType& func );
	//get the wnd handle
	HWND GetWndHandle() const;
	//�����������ʾ����ǰ
	void ForegroundWindow() const;
	DWORD GetWndThrdId() const;

protected:
	HWND		hwnd_;
	DWORD		thread_id_;
};

//ֻ����һ��ʵ��
//���������game.dll���ٵ��߳���ִ��
class FuncObj_Inject : public FuncObj_Inter{
protected:
	FuncObj_Inject( FuncObj_Inter* sink, FuncObj* parent );

public:
	bool AsyncExec(const ExecFnType& async_func) override;

protected:
	//virtual FuncObj_GWnd* CreateGWnd();

protected:
};

class FuncObj_InterInjectComposite : public FuncObj_Inject{
public:
	FuncObj_InterInjectComposite( FuncObj* parent, HWND hwnd );
	FuncObj_GWnd& GetInterGWnd();
	void DeleteSelf();

protected:
	FuncObj_GWnd			gwnd_;
};