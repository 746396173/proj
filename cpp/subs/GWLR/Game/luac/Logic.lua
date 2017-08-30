
g_is_start_run_info = true
g_is_out_to_console = true
function RunInfo( str )
	if g_is_start_run_info then
		LuaLog("��ǰִ����Ϣ��" .. str);
		if g_is_out_to_console then
			OutputScriptInfo(str)
		end
	end
end


function LuaHandleRoleEnteredGame( func, ... )
	local the_param = { ... }
	return scmd():HandleRoleEnteredGame(function ()
		return func(unpack(the_param))
	end)
end

function LuaHandleGameScene( func, ... )
	local the_param = { ... }
	return scmd():HandleGameScene(function ()
		return func(unpack(the_param))
	end)
end

function �������һ��Ψһ��ֵ( tbl, value )
	if type(tbl) ~= "table" then
		LuaLogE("�������һ��Ψһ��ֵ֮����������Ǳ�����")
		return false
	end
	if value == nil then
		LuaLogE("�������һ��Ψһ��ֵֵ֮�������벻��Ϊ��")
		return false
	end
	for _, v in ipairs(tbl) do
		if v == value then
			return true
		end
	end
	RunInfo("�������һ��Ψһ��ֵ��ֵ��" .. tostring(value))
	table.insert(tbl, value)
	return true
end
