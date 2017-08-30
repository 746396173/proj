require("WxCmn")
require("FrmStatusBar")
require("FrmMenuBar")
require("AcList")
require("FrmMidArea")
require("FrmHeaderCtrl")
require("BasicSetting")

frmfactory = {
    NewFrmStatusBar_ = nil,
    NewMenuBar_ = nil,
    NewAcList_ = nil,
    NewMidArea_ = nil,
    NewHeaderCtrl_ = nil,
    GetAreaSerInfo_ = nil,
    GetMenuBarMenuInfo_ = nil,
    GetAcListMenuInfo_ = nil,
    GetAcListColumnInfo = nil,
    GetAcListColumnIdxInfo_ = nil,
    GetAcListColumnNameInfo_ = nil,
    GetFrmHeaderCtrlColumnInfo_ = nil,
	NewFrmHeaderCtrlPages_ = nil,
    NewBasicSetting = nil,
}

function frmfactory:NewFrmStatusBar_()
    return FrmStatusBar
end

function frmfactory:NewMenuBar_()
    return FrmMenuBar
end

function frmfactory:NewAcList_()
	return AcList
end

function frmfactory:NewMidArea_()
	return FrmMidArea
end

function frmfactory:NewHeaderCtrl_()
	return FrmHeaderCtrl
end

function frmfactory:GetAreaSerInfo_()
    return {
        ["area1"] = {
            "area1_ser1", "area1_ser2", "area1_ser3",
        },
        ["area2"] = {
            "area2_ser1", "area2_ser2",
        },
    }
end

function frmfactory:GetMenuBarMenuInfo_()
	local tblMenus = 
	{
		{ "�ʺ�", 
				{
                    --A->Account
					{ WxCmn.NewID(), "����ʺ�\tAlt+A", "", function () mainfrm:OnAddAc() end },
                    { WxCmn.NewID(), "����ʺ�", "ɾ�������ʺ�", function () mainfrm:OnP_DeleteAc() end },
                    {},
                    --F->File
                    { WxCmn.NewID(), "��������\tAlt+F", "����ר�е��ʺ����ã���ʹĳЩ�ʺż̳��Ը����ã��Ա���Щ�ʺſ��Թ�������", function () mainfrm:OnCreateAcCfg() end },
                    --Q->Query
                    { WxCmn.NewID(), "ѡ������\tAlt+Q", "ѡ����Ҫ�鿴�����ã����ҿɶԵ�ǰѡ������ý����޸�", function () mainfrm:OnSelectAcCfg() end },
                    {},
                    { WxCmn.NewID(), "�����ʺ�", "�ļ����ݵĸ�ʽ�뵼���ʺ��ļ��ĸ�ʽһ��", function () mainfrm:OnImportAcCfg() end },
                    { WxCmn.NewID(), "�����ʺ�", "������ļ�����->�ʺ�.txt", function () mainfrm:OnExportAcCfg() end },
                    {},
                    --L->Login
                    { WxCmn.NewID(), "�����Ϻ�\tAlt+L", "��ʼ��½�����ʺ�", function () mainfrm:OnP_Login() end },
                    --C->Cancel
                    { WxCmn.NewID(), "ȡ�������Ϻ�\tAlt+C", "ȡ����½���л�δ�ɹ���½���ʺ�", function () mainfrm:OnP_CancelLogin() end },
                    {},
                    --R->Run
                    { WxCmn.NewID(), "��������\tAlt+R", "���������ʺ�", function () mainfrm:OnP_Run() end },
                    --S->Stop
                    { WxCmn.NewID(), "����ֹͣ\tAlt+S", "ֹͣ�����ʺ�", function () mainfrm:OnP_Stop() end },
                    {},
                    --K->Kill
                    { WxCmn.NewID(), "�ر�������Ϸ\tAlt+K", "�ر����д򿪵���Ϸ", function () mainfrm:OnP_CloseGame() end },
				},
		},
	}
    if not GetMyApp():IsDebug() then return tblMenus end
    table.insert(tblMenus,
        { "Test", 
				{
					{ WxCmn.NewID(), "test", "", function () mainfrm:OnTest() end },
                    { WxCmn.NewID(), "�رյ�½����", "", function () mainfrm:OnCloseLoginSession() end },
                    { WxCmn.NewID(), "���е�һ������\tR", "", function () mainfrm:OnRunFirstConnection() end },
                    { WxCmn.NewID(), "ֹͣ��һ������\tS", "", function () mainfrm:OnStopFirstConnection() end },
                    { WxCmn.NewID(), "���Ľű�", "", function () mainfrm:OnP_ChangeScript(false) end },
                    { WxCmn.NewID(), "ִ��lua�ļ�", "", function () mainfrm:OnTestDoFile() end },
				},
		})
    return tblMenus
end

function frmfactory:GetAcListMenuInfo_()
    return {
        { WxCmn.NewID(), "����ʺ�", "", function () mainfrm:OnAddAc() end },
        { WxCmn.NewID(), "ɾ���ʺ�", "ɾ��һ��������ѡ�ʺ�", function () mainfrm:OnP_DeleteAc(false) end },
        {},
        { WxCmn.NewID(), "��������", "����һ��������ѡ�ʺŵ�����", function () mainfrm:OnP_ChangeAcCfg(false) end },
        { WxCmn.NewID(), "�����ű�", "����һ��������ѡ�ʺŵĽű�", function () mainfrm:OnP_ChangeScript(false) end },
        { WxCmn.NewID(), "�л�����", "�л��ʺŵ����ࣺ��ͨ�Ż�ֿ��", function () mainfrm:OnP_AcCate(false) end },
        { WxCmn.NewID(), "�����ʺ�״̬", "�ָ����������ʺ�״̬", function () mainfrm:OnP_ResetAcState(false) end },
        {},
        { WxCmn.NewID(), "�Ϻ�", "��ʼ��½һ��������ѡ�ʺ�", function () mainfrm:OnP_Login(false) end },
        { WxCmn.NewID(), "ȡ���Ϻ�", "ȡ����½һ��������ѡ�ʺ�", function () mainfrm:OnP_CancelLogin(false) end },
        {},
        { WxCmn.NewID(), "����", "����һ��������ѡ�ʺ�", function () mainfrm:OnP_Run(false) end },
        { WxCmn.NewID(), "ֹͣ", "ֹͣ����һ��������ѡ�ʺ�", function () mainfrm:OnP_Stop(false) end },
        {},
        { WxCmn.NewID(), "�ر���Ϸ", "�ر�һ��������Ϸ", function () mainfrm:OnP_CloseGame(false) end },
        { WxCmn.NewID(), "��ʾ��Ϸ", "��ʾһ����Ϸ����", function () mainfrm:OnShowGameWnd() end },
    }
end

function frmfactory:GetAcListColumnInfo()
    local idxInfo = self:GetAcListColumnIdxInfo_()
    local nameInfo = self:GetAcListColumnNameInfo_()
    local tblIdx = {}
    for k, v in pairs(nameInfo) do
        local name = idxInfo[k + 1]
        assert(name)
        tblIdx[name] = k
    end
    return tblIdx, nameInfo
end

function frmfactory:GetAcListColumnIdxInfo_()
    return {
        "ac",
        "pwd",
        "area",
        "ser",
        "cate",
        "cfg",
        "script",
        "state",
        "scriptInfo",
        "lastTime",
    }
end

function frmfactory:GetAcListColumnNameInfo_()
    return {
        [0] = "�ʺ�",
        "����",
        "����",
        "������",
        "����",
        "����",
        "�ű�",
        "״̬",      
        "�����Ϣ",
        "��Чʱ��",
    }
end

function frmfactory:GetFrmHeaderCtrlColumnInfo_()
	return 
		{
			"��������",
		}
end

function frmfactory:NewFrmHeaderCtrlPages_(parent)
    local basicSetting = self:NewBasicSetting()
	return {
		basicSetting:Create(parent),		
	}
end

function frmfactory:NewBasicSetting()
    return BasicSetting
end
