#pragma once
/*
@author zhp
@date 2015/1/15 19:20
@purpose for anti crack
*/
#include <Common/CmnPriLuaData.h>

#define _ANTI_CRACK_LEVEL_0_

#ifdef _ANTI_CRACK_LEVEL_0_

void CheckLocalMachinePort();
//////////////////////////////////////////////////////////////////////////
//lua private data,anti crack
CmnPriLuaData& GetLPD_AC();
//check loginʧ�ܴ���
const std::string kLPD_CheckLoginFailedCnt = "36770294BAD5";
//�õ���֤ʧ������
int GetLPD_CheckLoginFailedCnt();
void SetLPD_CheckLoginFailedCnt( int cnt );
//////////////////////////////////////////////////////////////////////////
#endif