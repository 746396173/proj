#pragma once
 //�����ڴ������ҳ������,��VirtualProtectEx����һ��
 DWORD MyZwProtectVirtualMemory(	IN HANDLE               ProcessHandle,
												IN OUT PVOID            *BaseAddress,
												IN OUT PULONG           NumberOfBytesToProtect,
												IN ULONG                NewAccessProtection,
												OUT PULONG              OldAccessProtection); 



 BOOL MyWriteProcessMemory(
	 const char* hooker_name,
	 IN HANDLE               ProcessHandle,
	 IN PVOID                BaseAddress,
	 IN PVOID                Buffer,
	 IN ULONG                NumberOfBytesToWrite,
	 OUT PULONG              NumberOfBytesWritten OPTIONAL );



 //��ֵ����ReadProcessMemory�÷�һ��
 DWORD MyReadProcessMemory(
	 IN HANDLE               ProcessHandle,
	 IN PVOID                BaseAddress,
	 OUT PVOID               Buffer,
	 IN ULONG                NumberOfBytesToRead,
	 OUT PULONG              NumberOfBytesReaded OPTIONAL );


 //��������

 DWORD MyTerminateThread(
	 _In_opt_  HANDLE ProcessHandle,
	 _In_      DWORD ExitStatus
	 );//�����߳�

 //���ϵͳʱ��
 DWORD  MyGetTickCount();

 void MyTrace(const char * format,...);

 uintptr_t MyBeginThread(
	 _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
	 _In_ SIZE_T dwStackSize,
	 PVOID lpStartAddress,
	 _In_opt_ __drv_aliasesMem LPVOID lpParameter,
	 _In_ DWORD dwCreationFlags,
	 _Out_opt_ LPDWORD lpThreadId,
	 DWORD dwTheadEntryType
	 );