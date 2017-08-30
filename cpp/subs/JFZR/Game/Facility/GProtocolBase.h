#pragma once
/*
@author zhp
@date 2014/8/19 15:43
@purpose for game connect protocol
*/

struct CMD_HeaderBase{
protected:
	CMD_HeaderBase();
	CMD_HeaderBase& operator = ( const CMD_HeaderBase& );
public:
	//������ַ
	void* GetFollowAddr(){
		return (char*)this + sizeof(*this);
	}
	const void* GetFollowAddr() const{
		return (const char*)this + sizeof(*this);
	}
	//��������
	WORD GetFollowSize() const{
		assert(total_length_ > sizeof(*this));
		return total_length_ - sizeof(*this);
	}

public:
	WORD			total_length_;			//�ܳ���
	WORD			stable_length_;			//�̶�����,0x55e0
};