#pragma once
/*
@author zhp
@date 2017/4/3 13:26
@purpose for app atp login
*/
#include "OnlyLoginComponent.h"
#include <CommonX/CmnX_Math.h>

class AtpLoginConnectionOper : public LoginConnectionOper{
public:
	AtpLoginConnectionOper(LoginConnectionC& connection);

private:
	BC_REG_CLS_DECLARE(AtpLoginConnectionOper);
};

class AtpLoginConnection : public LoginConnectionC{
public:
	AtpLoginConnection(Cmn_GameDllApp& app, pt_word dest_port);
};

class AtpAppLoginFactory : public OnlyLoginAppFactory{
public:
	AtpLoginConnection* CreateLoginConnection(pt_word dest_port) override;
	AtpLoginConnectionOper* CreateLoginConnectionOper(LoginConnectionC& connection) override;
	DaMaTu* CreateDaMaTu() override;
};

class AtpAppLogin : public Cmn_OnlyLoginDllApp{
	friend class AtpLoginConnectionOper;
	friend class AtpLoginConnection;

private:
	enum enHandleCaptchaRes{
		kHCR_HasNotCaptcha,
		kHCR_CaptchaFailed,
		kHCR_Error,
		kHCR_HandleSucceed,
	};

public:
	AtpAppLogin();
	~AtpAppLogin();
	static AtpAppLogin& GetApp();
	AtpAppLoginFactory& GetAppFactory() const;
	AtpLoginConnection* GetConnection();
	void ReloginAc();

protected:
	bool PreBeginLogin() override;
	void BeginLogin() override;
	//�ȴ���ȫ���ɹ�
	bool WaitSafeCheckDone();
	//��ʼ��������
	bool BeginInputPwd();
	//��½��Ϸ���������������ǰ
	bool LoginGame();
	//��ʼ��Ϸ�����������������
	bool StartGame();

protected:
	AtpAppLoginFactory* CreateAppFactory() override;
	void BindFrame(lua_State* l) override;
	virtual pt_cwsz GetLoginClientWndTitle() const = 0;
	virtual stVec2Int GetCaptchaInputPos() const = 0;
	virtual bool EnteredServiceScene() const = 0;
	//������
	virtual void HandleAdvert();
	WXHWND GetLoginClientMainWnd() const;
	//�ж�TASLogin�����Ƿ�����
	bool IsTASLoginValid() const;
	//����Ƿ���Ч�����������µ�½
	void CheckToRelogin();

private:
	void __SetLocalCrackCaptcha__(const char* remote_ip, pt_word remote_port);
	void __SetDmtCrackCaptcha__(const char* account, const char* password);
	void __BeginLogin__();
	enHandleCaptchaRes HandleCaptcha();
	void ClearPreLogin_();
	void PressReturnKey();

private:
	mutable WXHWND		login_client_main_wnd_;
};
