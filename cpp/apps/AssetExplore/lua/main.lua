
wxApp = wx.wxGetApp()
myApp = GetMyApp()
------------------------------------------------------------------------------------------------------------
local inFileCnt = myApp:FileCount(true)
if inFileCnt > 0 then
	print("����������ģʽ")
--	require("CmnBase")
	require("cmdimpl")
	H_DoCmdLineFiles()
	print("�����ļ��Ѵ�����ϣ��˳���Ϣѭ����������������")
	ShellM([[
	wxApp:ExitMainLoop()
	]])
	return
end
------------------------------------------------------------------------------------------------------------
require("mainui")
------------------------------------------------------
frame = wx.wxFrame(wx.NULL, wx.wxID_ANY, "AssetExplore")
statusBar = frame:CreateStatusBar()
menuBar = wx.wxMenuBar()
frame:SetMenuBar(menuBar)
toolBar = frame:CreateToolBar(wx.wxNO_BORDER + wx.wxTB_FLAT + wx.wxTB_DOCKABLE)
config = WxCmn.FileConfig()
treeCtrl = nil
listCtrl = nil


CreateMenuBar()
CreateToolBar()
CreateCmdMap()
CreateWorkArea()
AutoEnableMenu()

toolBar:Realize()
------------------------------------------------------
frame:SetStatusText("��������Disk2Memory����ýڵ��ǩ�Ǵ���״̬������������״̬")

config:RestoreWndPos(frame, "MainFrame")
local function CloseWindow(event)
    --print("close frame")
    config:SaveWndPos(frame, "MainFrame")
    config:delete() -- always delete the config
    event:Skip(true)   --let fame call frame:Destroy()
end
frame:Connect(wx.wxEVT_CLOSE_WINDOW, CloseWindow)
frame:Show(true)
------------------------------------------------------
------------------------------------------------------------------------------------------------------------
