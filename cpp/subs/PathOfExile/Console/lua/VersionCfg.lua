VersionCfg = {}

local proxyId = 1

if proxyId == 0 then    --���Ի�
    VersionCfg.ip = "192.168.1.12"
    VersionCfg.port = 59421
    VersionCfg.loginTitle = "��½"
    VersionCfg.frmTitle = "����֮·"
elseif proxyId == 1 then --����
    VersionCfg.ip = "23.234.25.16"
    VersionCfg.port = 59422
    VersionCfg.loginTitle = "����֮·(��)"
    VersionCfg.frmTitle = "DEMON(��)"
elseif proxyId == 2 then --��ĭ
    VersionCfg.ip = "23.234.25.16"
    VersionCfg.port = 59423
    VersionCfg.loginTitle = "��½"
    VersionCfg.frmTitle = "����֮·"
elseif proxyId == 3 then --����
    VersionCfg.ip = "23.234.25.16"
    VersionCfg.port = 59424
    VersionCfg.loginTitle = "��½-ħ"
    VersionCfg.frmTitle = "����֮·-ħ"
end
