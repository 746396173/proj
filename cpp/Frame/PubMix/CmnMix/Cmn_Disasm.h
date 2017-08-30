#pragma once
/*
@author zhp
@date 2016/4/14 0:50
@purpose for disasm
*/
#include "../DependExternLib.h"
#include "../DependSelfLib.h"
#include <string>

/*
instruction->insn
*/
class Cmn_Disasm{
	Cmn_Disasm( const Cmn_Disasm& );
	Cmn_Disasm& operator = ( const Cmn_Disasm& );

public:
	Cmn_Disasm();
	~Cmn_Disasm();

public:
	void SetInputBuffer( const unsigned char* buffer, unsigned int buffer_size );

public:
	//�����һ��
	//Returns:	the number of bytes disassembled. A 0 indicates end of input.
	unsigned int DisassembleOnce() const;
	//����һ�Σ�DisassembleOnce == DecodeOnce + TranslateIntel
	unsigned int DecodeOnce() const;
	//ת����intel
	void TranslateIntel() const;

public:
	//�õ���ǰ���ַ�������
	const char* GetCurInsnAsm() const;
	//�õ���ǰ��hex��ʽ��ָ��
	const char* GetCurInsnHex() const;
	//�õ���ǰָ���
	unsigned int GetCurInsnLen() const;
	//�õ���ǰָ���������ʼ��ദ��ƫ��
	unsigned long long GetCurInsnOff() const;
	//�õ���ǰָ��Ļ�����ָ��
	const unsigned char* GetCurBytesPtr() const;

public:
	std::string GenFeatureCode() const;

private:
	void*		impl_;
};