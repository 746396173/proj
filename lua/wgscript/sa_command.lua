require("s_command")
require("sa_cmncfg")
sa_command = {
    CopyAssetFileToShareDir = nil,
    ---------------------------------
    ��װapk = nil,
    ж��apk = nil,
    ����app = nil,
    �ر�app = nil,
    ��װ��Ϸapk = nil,
    ж����Ϸapk = nil,
    ������Ϸapp = nil,
    �ر���Ϸapp = nil,
}
GetMyApp():AddScriptExecEnv("sa_command", sa_command)
local RunInfoP = s_command.RunInfoP
local RunInfoF = s_command.RunInfoF
local RunInfoS = s_command.RunInfoS

function sa_command.CopyAssetFileToShareDir(fileName, newFileName)
    newFileName = newFileName or fileName
    return scmd.CopyAssetFileToShareDir(fileName, newFileName)
end

function sa_command.��װapk(apkName, packageName, isPmInstall)
    if isPmInstall == nil then isPmInstall = false end
    RunInfoP(apkName, packageName)
    if isPmInstall then
        return scmd.PmInstallApk(apkName, packageName)
    else
        return scmd.InstallApk(apkName, packageName)
    end
end

function sa_command.ж��apk(packageName)
    RunInfoP(packageName)
    return scmd.UnInstallApk(packageName)
end

function sa_command.����app(packageName, activityName)
    RunInfoP(packageName, activityName)
    return scmd.StartApp(packageName, activityName)
end

function sa_command.�ر�app(packageName)
    RunInfoP(packageName)
    return scmd.StopApp(packageName)
end

function sa_command.��װ��Ϸapk()
    RunInfoP()
    return scmd.PmInstallApk(sa_cmncfg.gameApkName, sa_cmncfg.gamePackageName)
end

function sa_command.ж����Ϸapk()
    RunInfoP()
    return scmd.UnInstallApk(sa_cmncfg.gamePackageName)
end

function sa_command.������Ϸapp()
    RunInfoP()
    return scmd.StartApp(sa_cmncfg.gamePackageName, sa_cmncfg.gameMainActivityName)
end

function sa_command.�ر���Ϸapp()
    RunInfoP()
    return scmd.StopApp(sa_cmncfg.gamePackageName)
end
