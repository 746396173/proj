#pragma once
/*
@author zhp
@date 2015/1/16 10:04
@purpose comunicate, for anti crack
*/

/*
const BYTE* file_map_ptr;
assert((file_map_ptr + kKeyValueOffset) ^ kXorConstValue == GetCurrentProcessId())
*/
//�ڴ�ӳ���ļ���
const char*const kCheckFileMapName = "847C01AC8C623E883BFD";
//��ҪУ������ݵ�ƫ��
const int kKeyValueOffset = 0x105;
//���ĳ���
const int kXorConstValue = 0x91;

//�����Ż����¼���
const char* const kUseYouHuaEventName = "B9D7F066BDD32C40";
