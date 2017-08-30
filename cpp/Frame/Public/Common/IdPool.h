#pragma once
/*
@author zhp
@date 2014-3-11 17:04
@purpose for id distribute
*/
#include "Iterator.h"

//id distribute by order
class IdDistributeByOrder{
public:
	typedef Iterator<int> IdIter;

public:
	IdDistributeByOrder( IdIter& id_iter );

	//�õ�û�õ���ID
	int GetFreeId();

private:
	IdIter*				id_iter_;
};