
wxApp = wx.wxGetApp()
myApp = GetMyApp()

local loadFiles = {
    "loginui", "MyCfg", "MyFrm",
}

for _, v in ipairs(loadFiles) do
	require(v)
end

consolecfg:LoadMainCfg(consolecfg.MakeCfgInfo("����"))
----------------------------------------------------------------------------

loginui.ui.ShowLogin("��½", function()
		mainfrm:CreateFrm("����֮·")
	end)
