require("BasicSetting")
MyPages = {
    MyBasicSetting = {
        __index = BasicSetting,
        -------------
        GetSelectPathTitleInfo = nil,
    },
}
local MyBasicSetting = MyPages.MyBasicSetting
setmetatable(MyBasicSetting, MyBasicSetting)

function MyBasicSetting:GetSelectPathTitleInfo()
    return "ѡ������֮·����", "PathOfExile.exe|PathOfExile.exe"
end
