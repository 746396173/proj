
wxApp = wx.wxGetApp()
myApp = GetMyApp()

local loadFiles = {
    "loginui_p", "MyCfg", "MyFrm",
}

for _, v in ipairs(loadFiles) do
	require(v)
end

consolecfg:LoadMainCfg(consolecfg.MakeCfgInfo("����"))
----------------------------------------------------------------------------
--mainfrm:CreateFrm("����֮·")
----[[
loginui_p.ui.ShowLogin("POE", function()
		mainfrm:CreateFrm("����֮·")
	end)
--]]