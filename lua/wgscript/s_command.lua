require("s_cmncfg")
s_command = {
    RunInfo = nil,
    RunInfoP = nil,     --P->param
    RunInfoF = nil,     --F->Format
    RunInfoS = nil,     --S->Specific
    CopyAssetFile = nil,
    ----------------------
    --test
    TestReloadCmnLua = nil,
    TestReloadGameLua = nil,
    ----------------------
    ����ִ����Ϣ = nil,
    �ر�ִ����Ϣ = nil,
    �������������̨ = nil,
    �ر����������̨ = nil,
    �ӳ� = nil,       --��λ��
    �ȴ� = nil,       --��λ��
    �պ��� = nil,
    ���ؽű� = nil,
    �������ýű� = nil,
    ��������ű� = nil,
    �Զ�ѡ�����нű� = nil,
    �ı����еĽű� = nil,
    ִ�в��ȴ��¼� = nil,
    �����¼� = nil,
    ----------------------
    ��������ɫ���� = nil,
    �Զ�����ѡ���ɫ = nil,
}
GetMyApp():AddScriptExecEnv("s_command", s_command)
local g_is_start_run_info = true
local g_is_out_to_console = true
local print = print
local OutputScriptInfo = OutputScriptInfo

function s_command.RunInfo(...)
    if g_is_start_run_info then
        local str = tostring(...)
		print("ִ�У�" .. str)
		if g_is_out_to_console then
			OutputScriptInfo(str)
		end
	end
end

function s_command.RunInfoP(...)
	if g_is_start_run_info then
        local fnName = LuaD_GetLevelFnName(2)
        local p_n = select("#", ...)
        local str
        if p_n > 0 then
            str = string.rep("%s,\t", p_n - 1)
            str = str .. "%s"
            str = string.format(str, ...)
        else
            str = ""
        end
        str = fnName .. "(" .. str .. ")"
		print("ִ�У�" .. str)
		if g_is_out_to_console then
			OutputScriptInfo(fnName)
		end
	end
end

function s_command.RunInfoF(...)
	if g_is_start_run_info then
        local param = {...}
        local str = ""
        local idx = 0
		for i = 1, table.maxn(param) / 2 do
			str = str .. "\t" .. param[i] .. ":%s"
            idx = idx + 1
		end
        for i = 1, idx do
            table.remove(param, 1)
        end
        str = string.format(str, unpack(param))
        local fnName = LuaD_GetLevelFnName(2)
        str = fnName .. "\t" .. str
		print("ִ�У�" .. str)
		if g_is_out_to_console then
			OutputScriptInfo(fnName)
		end
	end
end

function s_command.RunInfoS(...)
	if g_is_start_run_info then
        local fnName = LuaD_GetLevelFnName(2)
        local str = fnName .. "\t\t" .. tostring(...)
		print("ִ�У�" .. str)
		if g_is_out_to_console then
			OutputScriptInfo(fnName)
		end
	end
end
local RunInfoP = s_command.RunInfoP
local RunInfoF = s_command.RunInfoF
local RunInfoS = s_command.RunInfoS

function s_command.CopyAssetFile(fileName, newFilePath)
    return scmd.CopyAssetFile(fileName, newFilePath)
end

function s_command.TestReloadCmnLua(dirName, scriptName)
    local app = GetMyApp()
    app:EraseScriptExecEnv(scriptName)
    dofile([[F:\proj\lua\]] .. dirName "\\".. scriptName .. ".lua")
end

function s_command.TestReloadGameLua(projName, scriptName, isAndroid)
    local path = [[F:\proj\cpp\subs\]]
    if isAndroid then
        path = path .. [[android\]]
    end
    dofile(path .. projName .. [[\Game\lua\]] .. scriptName .. ".lua")
end

function s_command.����ִ����Ϣ()
	g_is_start_run_info = true
end

function s_command.�ر�ִ����Ϣ()
	g_is_start_run_info = false
end

function s_command.�������������̨()
	g_is_out_to_console = true
end

function s_command.�ر����������̨()
	g_is_out_to_console = false
end

function s_command.�ӳ�(seconds)
    if seconds == nil then seconds = 0.01 end
    RunInfoP(seconds .. "��")
    return Sleep(seconds * 1000)
end

function s_command.�ȴ�(seconds)
    if seconds == nil then seconds = 0.01 end
    RunInfoP(seconds .. "��")
    return Sleep(seconds * 1000)
end

function s_command.�պ���()
end

function s_command.���ؽű�(file_name)
	RunInfoP(file_name)
	return LoadScriptFile(file_name)
end

function s_command.�������ýű�(file_name)
	RunInfoP(file_name)
	return LoadScriptFile("����\\" .. file_name);
end

function s_command.��������ű�(file_name)
    RunInfoP(file_name)
	return LoadScriptFile("����\\" .. file_name);
end

function s_command.�Զ�ѡ�����нű�(sceneHandler, fnGetScriptName)
    RunInfoP()
	return AutoChooseRunScript(sceneHandler, fnGetScriptName);
end

function s_command.�ı����еĽű�(topN)
    if topN == nil then topN = 0 end
    RunInfoP(topN)
	return ChangeRunningScript(topN);
end

function s_command.ִ�в��ȴ��¼�(fnRun, fnEventHandler, event)
    RunInfoP()
	return RunWaitEvent(fnRun, fnEventHandler, event);
end

function s_command.�����¼�(eventName)
    RunInfoP(eventName)
	return TriggerEvent(eventName);
end

function s_command.��������ɫ����(maxRoleCnt)
    RunInfoP(maxRoleCnt)
	return SetMaxGameRoles(maxRoleCnt);
end

function s_command.�Զ�����ѡ���ɫ()
    RunInfoP()
	return AutoCreateSelectRole();
end
