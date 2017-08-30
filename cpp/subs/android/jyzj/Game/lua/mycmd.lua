require("sa_command")
require("dm_command")
mycmd = {
    �����ʺ����� = nil,
}
local RunInfo = s_command.RunInfo
local RunInfoP = s_command.RunInfoP
local RunInfoF = s_command.RunInfoF
local RunInfoS = s_command.RunInfoS

function SelectArea(area)
    local picNames = { 
        { "��ɫ", "loginserrole.bmp" }, 
        { "�Ƽ�", "loginseradvise.bmp" },
        { "ʱ���", "loginsertime.bmp" }, 
        { "�ؽ�", "loginserdi.bmp" },
        { "ħ��", "loginsermo.bmp" }, 
        { "���", "loginsersky.bmp" }, 
        { "�˽�", "loginserman.bmp" },
    }
    local itemKey, item
    for k, v in ipairs(picNames) do
        if v[1] == area then
            itemKey = k
            item = v
            break
        end
    end
    if itemKey == nil then
        assert(false, area)
        return
    end
    local nextIdx = (itemKey + 1) % #picNames + 1
    assert(nextIdx ~= itemKey)
    local nextItem = picNames[nextIdx]
    local picFiles = item[2] .. "|" .. nextItem[2]
    
    local findRes = dm:FindPicEx(0, 0, 137, 490, picFiles, "", 0.9, 0)
    print(picFiles, "\t", findRes)
    local posX, posY = 52, 236
--    dm:MouseDrag(posX, posY, posX, posY + 40)
end

--û��ʵ�ֳ��������
function ѡ�����()
    local acInfo = GetMyApp():GetAcInfo()
    return SelectArea(acInfo.area)
end

function mycmd.�����ʺ�����()
    RunInfo("�����ʺ�����")
    local acInfo = GetMyApp():GetAcInfo()

    dm_command.DmClickLBt(605, 189)
    dm_command.DmInputBindWndString(acInfo.ac, 605, 189)

    Delay(1000)
    dm_command.DmClickLBt(244, 245)
    Delay(1000)
    dm_command.DmClickLBt(604, 241)
    dm_command.DmInputBindWndString(acInfo.pwd, 604, 241)
    Delay(1000)
    dm_command.DmClickLBt(444, 300)
    Delay(1500)
end
