#pragma once
/*
@author zhp
@date 2017/2/3 21:06
@purpose od info
*/
//�������ݹ���
//word[eax] != 0f00 && word[eax] != 0100
//����ƶ�����ID��ȫ�ֱ���
//d 100D70C
//InGameState����
//dd [[[[00FF7168+38]+4]+10]]
//PreGameState����
//dd [[[[00FF7168+38]+4]+10]]
//InGameState�ķ�������
//dd [[[[[[00FF7168+38]+4]+10]]+13c]+3A98]
//InGameState�ķ��������data
//dd [[[[[[[00FF7168+38]+4]+10]]+13c]+3A98]+0c8]
//PreGameState�ķ�������
//dd [[[[[[00FF7168+38]+4]+10]]+28]+828]
//PreGameState�ķ��������data
//dd [[[[[[[00FF7168+38]+4]+10]]+28]+828]+0c8]
//stCD_EntityArray
//dd [[[[[[[[00FF7168+38]+4]+10]]+13c]+3A94]+1c4]+4]
//Player
//dd [[[[[[[[[00FF7168+38]+4]+10]]+13c]+3A94]+1c4]+4]+5*4]
//stCD_BagMgr
//d [[[[[00FF7168+38]+4]+10]]+13c]+3CEC
//stCD_PassiveSkill
//d [[[[[00FF7168+38]+4]+10]]+13c]+3AC4
//stCD_GameLogic
//d [[[[[00FF7168+38]+4]+10]]+13c]
//stCD_World
//d [[[[[[00FF7168+38]+4]+10]]+13c]+3A94]
