#pragma once
/*
@author zhp
@date 2016/4/18 20:38
@purpose some config,some base type
*/
#include <ProtocolX/P_BaseTypeX.h>
#include <boost/uuid/uuid.hpp>


//type index�����ͣ�Ĭ��ֻռһ���ֽڴ�С������֧��256������
typedef pt_byte	BC_TypeIndexT;

namespace Detail{
typedef boost::uuids::uuid BC_Uuid;
}	//Detail