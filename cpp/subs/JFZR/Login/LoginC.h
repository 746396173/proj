#pragma once
/*
@author zhp
@date 2014/4/9 11:05
@purpose func object of login helper
*/
#include "stdafx.h"
#include "socket/client.h"
#include "Common/UsefulClass.h"
#include "Script/JsonCall.h"
#include "Lua_l.h"
#include "../Console/CfgStruct.h"
#include "Common/CrackCaptcha.h"

class LoginC;
class LoginOperC : public JsonEchoBase{
public:
	LoginOperC( LoginC& login_c );
	//��֤�ַ���
	bool CheckLoginStr( const std::string& console_str );

protected:
	virtual bool OnThisMemCall( const stThisCallHelper& helper );

private:
	LoginC&				login_c_;
};

class LoginC : public Connection_Aes, public Singleton<LoginC, Singleton_Instance>{
public:
	LoginC();

public:
	bool Init();
	//get json echo
	JsonEcho& GetJsonEcho();

	//for communication
public:
	//�����ʺź�����
	void SetAccount_Password( const char* account, const char* password );
	//���ô�������
	void SetSerRegion( int pos_x, int pos_y );
	//����Ҫ����ķ�����
	void SetJoinedService( int pos_x, int pos_y );
	//���ô��뷽ʽ
	void SetCrackCaptchaMode( int ccm, const char* account, const char* password, const char* remote_ip, WORD remote_port );
	//��ʼ��½��Ϸ
	void BeginLogin();

public:
	//���Ұ�ȫ����ӽ���
	DWORD Do_CheckSafeSubProcessId();
	//���ڴ�ӳ���ļ�
	bool OpenMemFileMap();
	//ע��Login helperģ��
	bool InjectLoginHelper( DWORD process_id );
	//��ȫ�����¼������Ƿ����
	bool Do_SafeCheckEventExist();
	//�����ʺ�
	bool InputAccount();
	//��������
	bool InputPassword();
	//��½��Ϸ
	bool LoginGame();
	//�����¼���
	bool HandleLoginResult();
	//������֤��
	bool HandleCaptcha();
	//ѡ�����(����/��ͨ)
	bool SelectSerRegion();
	//ѡ�������
	bool SelectService();
	//�������Ѿ�����
	bool HandleServiceFull();
	//ȷ��ѡ��
	bool SelectedService();
	//Ѱ���ʺŴ���
	HWND FindAcWnd();

protected:
	bool OnConnected( IoConnectBase* connect );

private:
	class DaMaTu_JFZR : public DaMaTu{
		const char* SoftKey() const;
	};

	//���
private:
	JsonEcho				json_echo_;
	Lua_l					lua_l_;

private:
	std::string				account_;
	std::string				password_;
	CPoint					ser_region_pos_;				//�����������
	CPoint					service_pos_;					//Ҫѡ��ķ�����������
	stCrackCaptchaMode		crack_captcha_mode_;			//���뷽ʽ

	//���뷽ʽ
private:
	ICrackCaptcha*			crack_captcha_;
	LocalCrackCaptcha		local_crack_captcha_;			//���ش���
	DaMaTu_JFZR					da_ma_tu_;						//������
	LoginOperC				login_oper_;
};