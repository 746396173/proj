#pragma once
/*
@author zhp
@date 2016/1/26 19:05
@purpose һЩLPK�����ݷ���ͨ�ýṹ��
*/
#include <string>

typedef struct  
{
	WORD	wPacketLen;
	WORD	wMethodType;			// �������ͣ����� http�е� get,post,put,delete
	WORD	wUrlType;				// ����ʵ�ַ�����������
}PACKET_TYPE,*PPACKET_TYPE;