#pragma once
/*
@author zhp
@date 2016/4/10 22:55
*/
#include <ProtocolX/P_DefinesX.h>
#include "../DependSelfLib.h"


class GGameObjBase{
public:
	virtual ~GGameObjBase(){}
	//��������
	virtual bool Update();
	virtual void DebugInfo() const;
	CMN_CAST_TO

protected:
	virtual bool UpdateImpl() = 0;
	virtual void DoUpdateClear();
};

class GGameObjMgrBase{
public:
	virtual ~GGameObjMgrBase(){}
	//��������
	virtual bool UpdateAll();
	//���¹�������������
	virtual bool RebuildAll();
	virtual void DebugInfo() const;
	CMN_CAST_TO

protected:
	virtual bool UpdateAllImpl();
	virtual bool RebuildAllImpl() = 0;
	virtual void DoRebuildUpdateClear();
};
