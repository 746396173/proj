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
const char*const kCheckFileMapName = "28C159FD41C5";
//��ҪУ������ݵ�ƫ��
const int kKeyValueOffset = 0x109;
//���ĳ���
const int kXorConstValue = 0x56;