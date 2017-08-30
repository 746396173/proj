require("WxCmn")
require("cmdimpl")

function H_New()
	LogT("H_New")
    treeCtrl:GenTreeByRoot(H_DoNew())
end

local lastFilePath = nil
local frameOldTitle = nil
local function SetLastFilePath(filePath)
    if frameOldTitle == nil then
        frameOldTitle = frame:GetTitle()
    end
    lastFilePath = filePath
    if filePath ~= nil then
        frame:SetTitle(frameOldTitle .. "********" .. filePath)
    else
        frame:SetTitle(frameOldTitle)
    end
end

function H_Open()
	LogT("H_Open")
    local filePath = WxCmn.OpenFile(frame, "���ļ�", "��Դϵͳ�ļ�(*.assf)|*.assf")
    if filePath == nil then
        LogE("���ļ�ʧ��")
        return
    end
    SetLastFilePath(filePath)
    treeCtrl:GenTreeByRoot(H_DoOpen(filePath))
end

function H_Close()
	LogT("H_Close")
    treeCtrl:DeleteAllItems()
    SetLastFilePath(nil)
end

local function OpenSaveFile()
    local filePath = WxCmn.OpenFile(frame, "ѡ��Ҫ������ļ�", "AssetSystemFile (*.assf)|*.assf|All files (*)|*", wx.wxFD_SAVE)
    if filePath == nil then
        LogE("����ʧ��")
    end
    return filePath
end

function H_Save()
	LogT("H_Save")
    if lastFilePath == nil then
        local filePath = OpenSaveFile()
        if filePath == nil then
            return
        end
        SetLastFilePath(filePath)
    end
    local root = treeCtrl:GetRootNode()
    if root == nil then
        LogE("û�и��ڵ�")
        return
    end
    H_DoSaveAs(root, lastFilePath)
end

function H_SaveAs()
	LogT("H_SaveAs")
    local filePath = OpenSaveFile()
    if filePath == nil then
        return
    end
    local root = treeCtrl:GetRootNode()
    if root == nil then
        LogE("û�и��ڵ�")
        return
    end
    H_DoSaveAs(root, filePath)
    SetLastFilePath(filePath)
end

function H_AddNode()
	LogT("H_AddNode")
    local wstr = wx.wxArrayString()
    local parentNode = treeCtrl:GetSelectNode()
    for v in Iterate(AS_FactoryMe():ValidClsNmae(parentNode)) do
        wstr:Add(v)
    end    
    local str = WxCmn.SingleChoiceDlg(frame, "ѡ��ڵ�����", wstr)
    if str == nil then
        return
    end
    local node = H_DoAddNode(parentNode, str)
    if node == nil then
        LogE("���ʧ��")
        return
    end
    local item = treeCtrl:GetSelection()
    treeCtrl:GenSubNode(item)
    treeCtrl:RefreshItem(item)
end

function H_DeleteNode()
	LogT("H_DeleteNode")
    local item = treeCtrl:GetSelection()
    H_DoDeleteNode(treeCtrl:GetItemNode(item))
    treeCtrl:Delete(item)
end

local function GetPathFromDlg(node)
    if node:GetCate() == enAS_NodeCate.kDisk then
        if node:GetType() == enAS_NodeType.kDir then
            return WxCmn.OpenDir(frame, "ѡ��Ŀ¼")
        else
            return WxCmn.OpenFile(frame, "ѡ���ļ�")
        end
    else
        return WxCmn.GetTextFromDlg(frame, "����·��", node:GetPath())
    end
end

function H_ReplacePath()
	LogT("H_ReplacePath")
    local item = treeCtrl:GetSelection()
    local node = treeCtrl:GetItemNode(item)
    local path = GetPathFromDlg(node)
    if path == nil or path == "" then
        LogD("δ������Ч·��")
        return
    end
    H_DoReplacePath(node, path)
    treeCtrl:SetItemText(item, node:GetPath())
end

function H_Refresh()
	LogT("H_Refresh")
    local item = treeCtrl:GetSelection()
    local node = treeCtrl:GetItemNode(item)
    if node:Refresh(true) then
        treeCtrl:RefreshItem(item)
    end
end

function H_YesD2M()
    LogT("H_YesD2M")
    local item = treeCtrl:GetSelection()
    local node = treeCtrl:GetItemNode(item)
    node:SetD2M(true)
    treeCtrl:RefreshItem(item, nil, true)
end

function H_NoD2M()
    LogT("H_NoD2M")
    local item = treeCtrl:GetSelection()
    local node = treeCtrl:GetItemNode(item)
    node:SetD2M(false)
    treeCtrl:RefreshItem(item, nil, true)
end

function H_D2M()
    LogT("H_D2M")
    local item = treeCtrl:GetSelection()
    local node = treeCtrl:GetItemNode(item)
    node = H_DoD2M(node)
	if node == nil then
		return
	end
    treeCtrl:RefreshItem(item, node)
end

local refAsSrc = nil
function ValidRefAsSrc()
    if refAsSrc == nil then
        return false
    end
    return refAsSrc:IsOk()
end

function H_SetRefAsSrc()
	LogT("H_SetRefAsSrc")
    refAsSrc = treeCtrl:GetSelection()
end

function H_SetRefAsDst()
	LogT("H_SetRefAsDst")
    if refAsSrc == nil then
        LogW("��δѡ������Դ")
        return
    end
    if not refAsSrc:IsOk() then
        LogW("����Դ��ʧЧ��������ѡ������Դ")
        refAsSrc = nil
        return
    end
    local nodeSrc = treeCtrl:GetItemNode(refAsSrc)
    local nodeDst = treeCtrl:GetSelectNode()
    if nodeSrc:Equal(nodeDst) then
        LogE("����Դ������Ŀ�겻����ͬ��������ѡ������Ŀ��")
        return
    end
    H_DoSetRef(nodeSrc, nodeDst)
    local p = treeCtrl:GetItemParent(refAsSrc)
    refAsSrc = nil
    --refAsSrc��NodeLvl���ˣ�����ˢ���¸��ڵ�
    treeCtrl:RefreshItem(p)
end

local findExt_ = {}
local dlgFind = nil
local lastFindText = ""
function findExt_:FindFrist(event)
    Log("find")
    local findStr = event:GetFindString()
    lastFindText = findStr
    local node
    if CmnBase.Startwith(findStr, ":") then
        node = self.curNode:FindChild(string.sub(findStr, 2))
    elseif CmnBase.Startwith(findStr, "?") then
        node = self.curNode:FindPosterity(string.sub(findStr, 2))
    else
        node = self.curNode:Find(findStr)
    end
    if node == nil then
        Log("û���ҵ���", findStr)
        treeCtrl:Collapse(self.curItem)
        return
    end
    treeCtrl:FocuseItemByNode(node)
end

function findExt_:OnCloseDlg()
    LogT("user close find dlg")
    dlgFind = nil;
    statusBar:PopStatusText()
end

local function GetDlgFind(title)
    if dlgFind then
        dlgFind:Destroy()
        dlgFind = nil
    else
        statusBar:PushStatusText(Id.Find.prompt)
    end
    local data = wx.wxFindReplaceData()
    dlgFind = wx.wxFindReplaceDialog(frame, data, title, 
                    wx.wxFR_NOUPDOWN + wx.wxFR_NOMATCHCASE + wx.wxFR_NOWHOLEWORD)
    dlgFind = CmnBase.ExtCObj(findExt_, dlgFind)
    local dlg = dlgFind
    dlgFind:Connect(wx.wxID_ANY, wx.wxEVT_COMMAND_FIND, function (event) dlg:FindFrist(event) end)
    dlgFind:Connect(wx.wxID_ANY, wx.wxEVT_COMMAND_FIND_NEXT, function (event) dlg:FindFrist(event) end)
    dlgFind:Connect(wx.wxID_ANY, wx.wxEVT_COMMAND_FIND_CLOSE, function (event) dlg:OnCloseDlg() end)
    return dlgFind
end
function H_Find()
	LogT("H_Find")
    local curNode = treeCtrl:GetSelectNode()
    local abs_path = curNode:GetAbsolutePath(false, true, false)
    if abs_path == "" then
        abs_path = "root"
    end
    local dlg = GetDlgFind("���ڸýڵ���ң�" .. abs_path)
    dlg:GetData():SetFindString(lastFindText)
    dlg.curNode = curNode
    dlg.curItem = treeCtrl:GetSelection()
    dlg:Show(true)
end

function H_SaveTo()
	LogT("H_SaveTo")
    local curNode = treeCtrl:GetSelectNode()
    if curNode == nil then
        LogE("û�и��ڵ�")
        return
    end
    local filePath = OpenSaveFile()
    if filePath == nil then
        return
    end
    curNode:SaveToDisk(filePath)
end
--------------------------------------------------------
