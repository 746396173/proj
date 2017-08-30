#pragma once
/*
@author zhp
@date 2014-1-04
@purpose �������������Ϸ�е�һЩ���͡��ṹ��
*/
#include "stdafx.h"

namespace GType{
	class G_HttpSendCall_FirstObj;

	//http����call�������1
	class HttpSendCall_NeededObj1;
	//http����call�������2
	class HttpSendCall_NeededObj2;
	//http����call�������ṹ��
	struct stHttpSendCall_Content
	{
		stHttpSendCall_Content();

		const char*		str_http_content;
		DWORD			unknown_equal_zero;
		int				total_size_http_content;			//http package�ܳ���
	};
	//�����������
	struct stHttpSendCall_NeededObj3{
	private:
		stHttpSendCall_NeededObj3();
		char				buffer_unknown[0x60];

		/* static void* operator new( size_t size );
		 static void operator delete( void* pointee );*/
	};

	enum enHttpSendCall_Result
	{
		enHttpSendCall_Result_Fail = -1,	//ʧ��
		enHttpSendCall_Result_Succeed = 0,	//�ɹ�
	};

	enum enGameState
	{
		enGameState_Invalid,						//��Ч״̬
		enGameState_PressOnClick,					//�������״̬
		enGameState_NoticeDlg,						//����
		enGameState_TrainerSelect,					//����ѡ��
		enGameState_TrainerSelected,				//����ѡ��
		enGameState_Managers,						//������ģʽ״̬
		enGameState_Custom = 6,						//�Զ���ģʽ״̬
		//���¶���ģʽ����������Щö�ٵ���ֵ�ģ����Բ�Ҫ�������˳��
		enGameState_Managers_Computer,				//������֮�������״̬
		enGameState_Managers_Friend,				//������֮�������״̬
		enGameState_Managers_Random,				//������֮�����������
		enGameState_Managers_Contract,				//������֮��Լ״̬
		enGameState_Match_Wait = 11,				//�ȴ����䳡��
		enGameState_Match_Choose_Player,			//ѡ����Ա
		enGameState_Match_Ready,					//׼����������
		enGameState_Match_BeginFirtAnimate,			//��ʼ����ǰ�Ķ���
		enGameState_MatchEnd,						//��������
		enGameState_MatchEnd_Prize = 16,			//��������֮��������
		enGameState_MatchEnd_Back,					//��������֮���ر�������
		enGameState_ClubManage,						//���ֲ�������
		enGameState_AutoSelectPlayer,				//�Զ�ѡ����Ա�ɹ�
		enGameState_CreateCoach,					//������������
	};

	//����������״̬
	enum enCreateCoach_SubState
	{
		enCC_SubState_Invalid,
		//enCC_SubState_Create,				//��������
		enCC_SubState_InputName,			//���������
		enCC_SubState_SelectTeam,			//ѡ�����
	};

	//����ģʽ
	enum enMatchMode
	{
		enMatchMode_Invalid,			//��Ч
		enMatchMode_Custom,				//�Զ���ģʽ
		enMatchMode_Managers,			//������ģʽ
	};
	
	//����ģʽ
	enum enFightMode
	{
		enFightMode_Invalid,			//��Ч
		enFightMode_Friend,				//�������
		enFightMode_Computer,			//�������
		//enFightMode_Random,				//����������֣������Ȳ���
	};

	//������Ϣ
	struct stMatchInfo{
		DWORD				room_id;			//����ID
		DWORD				match_id;			//����ID

	public:
		stMatchInfo();
		DWORD GetRoomId() const;
		void SetRoomId( DWORD id );
		DWORD GetMatchId() const;
		void SetMatchId( DWORD id );
	};

	//��Աְλ
	enum enPlayerPosition{
		enPlayerPosition_No = 0,				//��ְλ
		enPlayerPosition_Third,					//����Ա
		enPlayerPosition_Second,				//�油��Ա
		enPlayerPosition_First,					//�׷���Ա
	};
}