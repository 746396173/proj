require("frmcmn")
require("WxCmn")
require("consolecfg")
loginui = {
	oper = frmcmn.MakeProxy("loginio", true),
	ui = {
		ShowLogin = nil,
	},
	EndDayTime = nil,
}

local oper = loginui.oper
local ui = loginui.ui

local frameLogin = nil
local statusBar = nil
local toolBar = nil
local textCtrlAc = nil
local textCtrlPwd = nil
local acPwdMinLen = 5
local acPwdMaxLen = 20
local cardIdMinLen = 32
local cardIdMaxLen = 36
local qqMinLen = 4
local qqMaxLen = 12
local endDayTime = nil

local cmdIdLogin = WxCmn.NewID()
local cmdIdRemoveBind = WxCmn.NewID()
local cmdIdReg = WxCmn.NewID()
local cmdIdDoReg = WxCmn.NewID()
local cmdIdPay = WxCmn.NewID()
local cmdIdDoPay = WxCmn.NewID()

function loginui.EndDayTime()
	return endDayTime
end

local function CheckAcPwd(ac, pwd)
	local acLen = #ac
	if acLen < acPwdMinLen then
		wx.wxMessageBox(tostring("�ʺų���С��[", acPwdMinLen, "]"), "�ʺų��ȴ���", wx.wxOK)
		return 
	end
	if acLen > acPwdMaxLen then
		wx.wxMessageBox(tostring("�ʺų��ȴ���[", acPwdMaxLen, "]���벻Ҫ��������"), "�ʺų��ȴ���", wx.wxOK)
		return 
	end
	if pwd == nil then
		return true
	end
	local pwdLen = #pwd
	if pwdLen < acPwdMinLen then
		wx.wxMessageBox(tostring("���볤��С��[", acPwdMinLen, "]"), "���볤�ȴ���", wx.wxOK)
		return 
	end
	if pwdLen > acPwdMaxLen then
		wx.wxMessageBox(tostring("���볤�ȴ���[", acPwdMaxLen, "]���벻Ҫ��������"), "���볤�ȴ���", wx.wxOK)
		return 
	end
	return true
end

local function CheckQq(qq)
	local qqLen = #qq
	if qqLen < qqMinLen or qqLen > qqMaxLen then
		wx.wxMessageBox("����д��ȷ��QQ", "����", wx.wxOK)
		return
	end
	return true
end

local function CheckKey(str, key)
	local keyLen = #key
	if keyLen < cardIdMinLen or keyLen > cardIdMaxLen then
		wx.wxMessageBox("����д��ȷ��" .. str, str .. "����", wx.wxOK)
		return
	end
	return true
end

local function OnCmdLogin()
	local ac = textCtrlAc:GetValue()
	local pwd = textCtrlPwd:GetValue()
	if CheckAcPwd(ac, pwd) ~= true then
		return
	end
	statusBar:PushStatusText("��½��...")
	local res = oper.Login(true, ac, pwd)
	statusBar:PopStatusText()
	if res == nil then
		statusBar:SetStatusText("��½ʧ�ܣ�����ԭ��")
	else
		if res[1] == true then
			statusBar:SetStatusText(tostring("��½�ɹ�������ʱ��->", res[2]))
			endDayTime = res[2]
			frameLogin:Close()
            local loginAcInfo = consolecfg.mainCfg.loginAcInfo
            loginAcInfo.ac = ac
            loginAcInfo.pwd = pwd
		else
			statusBar:SetStatusText(tostring("��½ʧ��->", res[2]))
		end
	end
	Sleep(1500)
end

local function OnCmdRemoveBind()
	local ac = textCtrlAc:GetValue()
	local pwd = textCtrlPwd:GetValue()
	if CheckAcPwd(ac, pwd) ~= true then
		return
	end
	statusBar:PushStatusText("�����...")
	local res = oper.RemoveBind(ac, pwd)
	statusBar:PopStatusText()
	if res == nil then
		statusBar:SetStatusText("���ʧ�ܣ�����ԭ��")
	else
		if res[1] == true then
			statusBar:SetStatusText(res[2])
		else
			statusBar:SetStatusText(tostring("���ʧ��->", res[2]))
		end
	end
	Sleep(1500)
end

local function AcPromptStr()
	return tostring("�ʺŲ��ܰ��������ַ������ȱ�����[", acPwdMinLen, "]��[", acPwdMaxLen, "]֮��")
end

local function PwdPromptStr()
	return tostring("���벻�ܰ��������ַ������ȱ�����[", acPwdMinLen, "]��[", acPwdMaxLen, "]֮��")
end

local function QqPromptStr()
	return tostring("qq���ȱ�����[", qqMinLen, "]��[", qqMaxLen, "]֮��")
end

local function OnCmdReg()
	local dlgReg = wx.wxDialog(frameLogin, wx.wxID_ANY, "ע��")
	local regStatusBar = wx.wxStatusBar(dlgReg, wx.wxID_ANY)
	local staticAc = wx.wxStaticText(dlgReg, wx.wxID_ANY, "�ʺţ�")
	local staticPwd = wx.wxStaticText(dlgReg, wx.wxID_ANY, "���룺")
	local ctrlAc = WxCmn.CreateTextCtrl(dlgReg, "", wx.wxTE_LEFT, acPwdMaxLen, regStatusBar, AcPromptStr())
	local ctrlPwd = WxCmn.CreateTextCtrl(dlgReg, "", bit.bor(wx.wxTE_LEFT, wx.wxTE_PASSWORD), acPwdMaxLen, regStatusBar, PwdPromptStr())
	local staticQQ = wx.wxStaticText(dlgReg, wx.wxID_ANY, "�ۿۣ�")
	local ctrlQQ = WxCmn.CreateTextCtrl(dlgReg, "", wx.wxTE_LEFT, qqMaxLen, regStatusBar, QqPromptStr())
	local staticRegId = wx.wxStaticText(dlgReg, wx.wxID_ANY, "ע���룺")
	local ctrlRegId = WxCmn.CreateTextCtrl(dlgReg, "", wx.wxTE_LEFT, cardIdMaxLen)
	local btReg = wx.wxButton(dlgReg, cmdIdDoReg, "ע��")
	
	dlgReg:Connect(wx.wxEVT_SIZE, function(event)
		event:Skip(true)
		local clientSize = dlgReg:GetClientSize()
		WxCmn.SetStatusBarSize(regStatusBar, clientSize)
		local centerSize = dlgReg:GetClientSize():Scale(0.5, 0.5)
		local staticAcPos = wx.wxPoint(centerSize:GetWidth() * 0.35, centerSize:GetHeight() * 0.2)
		staticAc:Move(staticAcPos)
		local width = (staticAc:GetSize():GetWidth() + staticRegId:GetSize():GetWidth()) * 0.5
		WxCmn.SetVerticalPos(staticAc, staticPwd)
		WxCmn.SetHorizonPos(staticAc, ctrlAc, nil, nil, width, width)
		WxCmn.SetHorizonPos(staticPwd, ctrlPwd, nil, nil, width, width)
		WxCmn.SetVerticalPos(staticPwd, staticQQ)
		WxCmn.SetHorizonPos(staticQQ, ctrlQQ, nil, nil, width, width)
		WxCmn.SetVerticalPos(staticQQ, staticRegId)
		WxCmn.SetHorizonPos(staticRegId, ctrlRegId, nil, nil, width, width)
		btReg:Move(wx.wxPoint(centerSize:GetWidth() - btReg:GetSize():GetWidth() * 0.5, clientSize:GetHeight() * 0.73))
	end)
	
	dlgReg:Connect(cmdIdDoReg, wx.wxEVT_COMMAND_BUTTON_CLICKED, function()
		local ac = ctrlAc:GetValue()
		local pwd = ctrlPwd:GetValue()
		if CheckAcPwd(ac, pwd) ~= true then
			return
		end
		local qq = ctrlQQ:GetValue()
		if CheckQq(qq) ~= true then
			return 
		end
		local regKey = ctrlRegId:GetValue()
		if CheckKey("ע����", regKey) ~= true then
			return
		end
		
		regStatusBar:PushStatusText("ע����...")
		local res = oper.Reg(ac, pwd, qq, regKey)
		regStatusBar:PopStatusText()
		if res == nil then
			regStatusBar:SetStatusText("ע��ʧ�ܣ�����ԭ��")
		else
			if res[1] == true then
				regStatusBar:SetStatusText(res[2])
			else
				regStatusBar:SetStatusText(tostring("ע��ʧ��->", res[2]))
			end
		end
	end)
	
	dlgReg:ShowModal()
	dlgReg:Destroy()
end

local function OnCmdPay()
	local dlgPay = wx.wxDialog(frameLogin, wx.wxID_ANY, "��ֵ")
	local payStatusBar = wx.wxStatusBar(dlgPay, wx.wxID_ANY)
	local staticCardId = wx.wxStaticText(dlgPay, wx.wxID_ANY, "���ţ�")
	local staticCardPwd = wx.wxStaticText(dlgPay, wx.wxID_ANY, "���ܣ�")
	local staticAc = wx.wxStaticText(dlgPay, wx.wxID_ANY, "�ʺţ�")
	local ctrlCardId = WxCmn.CreateTextCtrl(dlgPay, "", wx.wxTE_LEFT, cardIdMaxLen, payStatusBar, "��ֵ����")
	local ctrlCardPwd = WxCmn.CreateTextCtrl(dlgPay, "", wx.wxTE_LEFT, cardIdMaxLen, payStatusBar, "��ֵ����")
	local ctrlAc = WxCmn.CreateTextCtrl(dlgPay, "", wx.wxTE_LEFT, acPwdMaxLen, payStatusBar, "����ֵ���ʺţ�" .. AcPromptStr())
	local btPay = wx.wxButton(dlgPay, cmdIdDoPay, "��ֵ")
	
	dlgPay:Connect(wx.wxEVT_SIZE, function(event)
		event:Skip(true)
		local clientSize = dlgPay:GetClientSize()
		WxCmn.SetStatusBarSize(payStatusBar, clientSize)
		local centerSize = dlgPay:GetClientSize():Scale(0.5, 0.5)
		staticCardId:Move(wx.wxPoint(centerSize:GetWidth() * 0.35, centerSize:GetHeight() * 0.4))
		WxCmn.SetVerticalPos(staticCardId, staticCardPwd)
		WxCmn.SetHorizonPos(staticCardId, ctrlCardId)
		WxCmn.SetHorizonPos(staticCardPwd, ctrlCardPwd)
		WxCmn.SetVerticalPos(staticCardPwd, staticAc)
		WxCmn.SetHorizonPos(staticAc, ctrlAc)
		btPay:Move(wx.wxPoint(centerSize:GetWidth() - btPay:GetSize():GetWidth() * 0.5, clientSize:GetHeight() * 0.7))
	end)
	
	dlgPay:Connect(cmdIdDoPay, wx.wxEVT_COMMAND_BUTTON_CLICKED, function()
		local cardId = ctrlCardId:GetValue()
		if CheckKey("����", cardId) ~= true then
			return
		end
		local cardPwd = ctrlCardPwd:GetValue()
		if CheckKey("����", cardPwd) ~= true then
			return
		end
		local ac = ctrlAc:GetValue()
		if CheckAcPwd(ac) ~= true then
			return
		end
		
		payStatusBar:PushStatusText("��ֵ��...")
		local res = oper.Pay(ac, cardId, cardPwd)
		payStatusBar:PopStatusText()
		if res == nil then
			payStatusBar:SetStatusText("��ֵʧ�ܣ�����ԭ��")
		else
			if res[1] == true then
				payStatusBar:SetStatusText(res[2])
			else
				payStatusBar:SetStatusText(tostring("��ֵʧ��->", res[2]))
			end
		end
	end)
	
	dlgPay:ShowModal()
	dlgPay:Destroy()
end

local function CreateLoginUi()
	local wndClient = wx.wxWindow(frameLogin, wx.wxID_ANY, wx.wxDefaultPosition, wx.wxDefaultSize, wx.wxSP_3DSASH)	
	local staticAc = wx.wxStaticText(wndClient, wx.wxID_ANY, "�ʺţ�")
	local staticPwd = wx.wxStaticText(wndClient, wx.wxID_ANY, "���룺")
    local loginAcInfo = consolecfg.mainCfg.loginAcInfo
	textCtrlAc = WxCmn.CreateTextCtrl(wndClient, loginAcInfo.ac, wx.wxTE_LEFT, acPwdMaxLen, statusBar, AcPromptStr())
	textCtrlPwd = WxCmn.CreateTextCtrl(wndClient, loginAcInfo.pwd, bit.bor(wx.wxTE_LEFT, wx.wxTE_PASSWORD), acPwdMaxLen, statusBar, PwdPromptStr())
	local btLogin = wx.wxButton(wndClient, cmdIdLogin, "��½")
	local btRemoveBind = wx.wxButton(wndClient, cmdIdRemoveBind, "���")
	
	wndClient:Connect(wx.wxEVT_SIZE, function(event)
		event:Skip(true)
		local centerSize = event:GetSize():Scale(0.5, 0.5)
		local staticAcPos = wx.wxPoint(centerSize:GetWidth() * 0.35, centerSize:GetHeight() * 0.3)
		staticAc:Move(staticAcPos)
		WxCmn.SetVerticalPos(staticAc, staticPwd)
		WxCmn.SetHorizonPos(staticAc, textCtrlAc)
		WxCmn.SetHorizonPos(staticPwd, textCtrlPwd)
		WxCmn.SetVerticalPos(staticPwd, btLogin, 1.3, 2)
		WxCmn.SetHorizonPos(btLogin, btRemoveBind)
	end)
end

local function CreateToolBar()
	toolBar = frameLogin:CreateToolBar(wx.wxNO_BORDER + wx.wxTB_FLAT + wx.wxTB_DOCKABLE)
	local toolBmpSize = toolBar:GetToolBitmapSize()
	toolBar:AddTool(cmdIdReg, "ע��", wx.wxArtProvider.GetBitmap(wx.wxART_ADD_BOOKMARK, wx.wxART_TOOLBAR, toolBmpSize), "ע��һ���ʺ�")
	toolBar:AddTool(cmdIdPay, "��ֵ", wx.wxArtProvider.GetBitmap(wx.wxART_REPORT_VIEW, wx.wxART_TOOLBAR, toolBmpSize), "��ֵ�ʺ�")
	toolBar:Realize()
end

local function CreateCmdMap()
	frameLogin:Connect(cmdIdLogin, wx.wxEVT_COMMAND_BUTTON_CLICKED, OnCmdLogin)
	frameLogin:Connect(cmdIdRemoveBind, wx.wxEVT_COMMAND_BUTTON_CLICKED, OnCmdRemoveBind)
	frameLogin:Connect(cmdIdReg, wx.wxEVT_COMMAND_MENU_SELECTED, OnCmdReg)
	frameLogin:Connect(cmdIdPay, wx.wxEVT_COMMAND_MENU_SELECTED, OnCmdPay)
end

function ui.ShowLogin(title, onLoginSucceed)
	local style = CmnBase.BitExcept(wx.wxDEFAULT_FRAME_STYLE, bit.bor(wx.wxMINIMIZE_BOX, wx.wxMAXIMIZE_BOX, wx.wxRESIZE_BORDER))
	frameLogin = wx.wxFrame(wx.NULL, wx.wxID_ANY, title, wx.wxDefaultPosition, wx.wxDefaultSize
				, style
					)
	frameLogin:CenterOnScreen()
	frameLogin:Connect(wx.wxEVT_DESTROY, function (event) 
		event:Skip(true)
		if endDayTime ~= nil then onLoginSucceed() end
	end)
	statusBar = frameLogin:CreateStatusBar()
	CreateToolBar()
	CreateLoginUi()
	CreateCmdMap()
	frameLogin:Show(true)
end
