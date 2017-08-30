#pragma once
/*
@author zhp
@date 2017/4/2 18:28
@purpose for against tp
*/
#include <CmnMix/Cmn_FileMap.h>
#include <CommonX/CmnX_UsefulClass.h>

struct stAtpDummyBugTrace{
	int				h_safe_check_done_;				//hook��ȫ������,SecureCheck.dll�����ƫ��
	int				o_msg_hook_proc_;
	int				edit_pwd_pos_x_;
	int				edit_pwd_pos_y_;
	unsigned long	edit_pwd_gwl_style_;					//���ڷ��

	stAtpDummyBugTrace(){
		h_safe_check_done_ = 0;
		o_msg_hook_proc_ = 0;
		edit_pwd_pos_x_ = 0;
		edit_pwd_pos_y_ = 0;
		edit_pwd_gwl_style_ = 0;
	}
};

class Atp_MemFileMap : public MemFileMap, public Singleton<Atp_MemFileMap, Singleton_MakeMe>{
	//type definition
public:
	struct stCommunicate{
		bool			safe_check_done_;			//��ȫ���
		bool			pwd_input_error_;			//�����������
		bool			ac_freeze_;					//�ʺű�����
		bool			login_succeed_;				//��¼�ɹ�
		bool			begin_input_pwd_;			//��ʼ�����ʺ�
		bool			end_input_pwd_;
		bool			input_pwd_has_except_;
		char			pwd_[50];

		stCommunicate();
	};

public:
	Atp_MemFileMap();
	//Read
	const stCommunicate* ReadAsCommu() const;
	//Write
	stCommunicate* WriteAsCommu();
};
