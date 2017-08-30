require("androidfrm")
require("MyPages")
MyFrm = {
    __index = androidfrm,
    -------------------------
    ---------test
    OnTest = nil,
    OnCloseLoginSession = nil,
    -------------------------
    NewFrmFactory_ = nil,
}
setmetatable(MyFrm, MyFrm)
mainfrm = MyFrm

MyFrmFactory = {
    __index = androidfrmfactory,
    ----------------
    GetMenuBarMenuInfo_ = nil,
    GetFrmHeaderCtrlColumnInfo_ = nil,
	NewFrmHeaderCtrlPages_ = nil,
    GetAreaSerInfo_ = nil,
}
setmetatable(MyFrmFactory, MyFrmFactory)


function MyFrm:OnTest()
--    --[[
	local app = GetMyApp()
    app:Test("")
    --]]
end

function MyFrm:OnCloseLoginSession()
    local acList = self:GetAcListCfg()
    local stateLogining = acList.stateLogining
    for item in self.acList:IteratorP_Selected(isAll) do
        local itemData = acList:FindItemByIdx(item + 1)
        if itemData:GetState() == stateLogining then
            self.uiOperHandler:CloseLoginSession(itemData:GetItemKey())
        end
    end
end

function MyFrm:NewFrmFactory_()
	return MyFrmFactory
end

function MyFrmFactory:GetMenuBarMenuInfo_()
    local res = CmnBase.Super(self).GetMenuBarMenuInfo_(self)
    local my = 
	{
		{ "Test", 
					{
						{ WxCmn.NewID(), "test", "", function () mainfrm:OnTest() end },
                        { WxCmn.NewID(), "�رյ�½����", "", function () mainfrm:OnCloseLoginSession() end },
                        { WxCmn.NewID(), "���е�һ������\tR", "", function () mainfrm:OnRunFirstConnection() end },
                        { WxCmn.NewID(), "ֹͣ��һ������\tS", "", function () mainfrm:OnStopFirstConnection() end },
                        { WxCmn.NewID(), "���Ľű�", "", function () mainfrm:OnP_ChangeScript(false) end },
                        { WxCmn.NewID(), "ִ��lua�ļ�", "", function () mainfrm:OnTestDoFile([[F:\proj\cpp\subs\android\jyzj\Console\lua\test.lua]]) end },
					},
		},
	}
    for _, v in ipairs(my) do
        table.insert(res, v)
    end
    return res
end

function MyFrmFactory:GetFrmHeaderCtrlColumnInfo_()
	return 
		{
			"��������",
		}
end

function MyFrmFactory:NewFrmHeaderCtrlPages_(parent)
	return {
		MyPages.basic:Create(parent),
	}
end

function MyFrmFactory:GetAreaSerInfo_()
    return {
        ["ʱ���"] = {
            "һ����˳", "�����껪", "���Ķ���",
        },
        ["�ؽ�"] = {
            "���񳯷�", "��ò����", "Ե������",
        },
    }
end
