--����ָ������
function AcceptTheTask( quest_ch_name )
	local gps = UpdateRole();
	if gps == nil then
		LuaLogE("UpdateRole error");
		return;
	end
	if not gps:AcceptTheTask(quest_ch_name) then
		LuaLogE("����ָ������ʧ��");
		return;
	end
	Delay(100);
	gps:GetReceivedTask():RebuildUpdateAll();
end

--����ָ�����ѽ�����
function IsAcceptedTheTask( quest_ch_name )
	local gps = UpdateRole();
	if gps == nil then
		LuaLogE("UpdateRole error");
		return false;
	end
	gps:GetReceivedTask():RebuildUpdateAll();
	return gps:IsAcceptedTheTask(quest_ch_name);
end

--ָ�����ѽ����������
function TheAcceptedTaskCompletable( quest_ch_name )
	local gps = UpdateRole();
	if gps == nil then
		LuaLogE("UpdateRole error");
		return false;
	end
	gps:GetReceivedTask():RebuildUpdateAll();
	return gps:TheTaskCompletable(quest_ch_name);
end

--�Զ��ύ�������
function AutoCommitCompleteTasks()
	local gps = UpdateRole();
	if gps == nil then
		LuaLogE("���½�ɫʧ��");
		return;
	end
	if not gps:CommitNoCompleteHandlerTasks() then
		LuaLogE("�Զ��ύ�������ʧ��");
	end
end

--�ύ�����������
function CommitAllCompleteTasks()
	local gps = UpdateRole();
	if gps == nil then
		LuaLogE("���½�ɫʧ��");
		return;
	end
	if not gps:CommitCompleteTasks() then
		LuaLogE("�Զ��ύ�������ʧ��");
	end
end

--����������ӳ��
function RestTaskHandlerMap( func )
	if type(func) ~= "function" then
		LuaLogE("����������ӳ��֮���������Ǻ�������");
		return false;
	end
	g_task_handle_map_ = {};
	if not GameEn2ChNodeMgr_Me():RebuildUpdateAll() then
		LuaLogE("��Ӣӳ����Ƴ�ʼ��ʧ�ܣ���������������ӳ��ʧ��");
		return false;
	end
	func();
	LuaLog("����������ӳ��֮������ɣ������[" .. table.getn(g_task_handle_map_) .. "]��������");
	return true;
end

function TraverseAllTaskHandlers_()
	for i, v in ipairs(g_task_handle_map_) do
		LuaLogW(tostring(i) .. "\tch->" .. v[g_THI_ch_name_] .. "\ten id->" .. WideCharToGbk(v[g_THI_en_id_]) .. "\tkey content->" .. tostring(v[g_THI_key_content_])
		.. "\tfull content->" .. WideCharToGbk(v[g_THI_full_content_]));
	end
end

--��������������������������
function FindTaskHandlerByCh( quest_ch_name )
	if type(quest_ch_name) ~= "string" then
		LuaLogE("����������֮�����������ַ�������");
		return;
	end
	for _, v in ipairs(g_task_handle_map_) do
		if v[g_THI_ch_name_] == quest_ch_name then
			return v;
		end
	end
end

g_task_handle_map_ = {};
--����Ӣ������ID������������
function FindTaskHandlerByEn( quest_id, role_lvl )
	if quest_id == nil or quest_id:empty() then
		LuaLogE("quest_idΪ��");
		return;
	end
	if role_lvl ~= nil then
		local lvl_limt;
		for _, v in ipairs(g_task_handle_map_) do
			lvl_limt = v[g_THI_lvl_limit_];
			if lvl_limt <= 0 or role_lvl <= lvl_limt then
				if quest_id:compare(v[g_THI_en_id_]) == 0 then
					return v;
				end
			end
		end
		return;
	end
	for _, v in ipairs(g_task_handle_map_) do
		if quest_id:compare(v[g_THI_en_id_]) == 0 then
			return v;
		end
	end
end

function ExistTaskCompleteHandler( quest_id, role_lvl )
	local handler_tbl = FindTaskHandlerByEn(quest_id, role_lvl);
	if handler_tbl == nil then
		return false;
	end
	if handler_tbl[g_THI_complete_func_] ~= nil then
		return true;
	end
	return false;
end

--task handler index
g_THI_ch_name_ = 1;
g_THI_en_id_ = 2;
g_THI_do_func = 3;
g_THI_lvl_limit_ = 4;
g_THI_complete_func_ = 5;
g_THI_key_content_ = 6;
g_THI_full_content_ = 7;
g_THI_match_quest_id_ = 8;

--���������role_lvl_limit��ʾ��ɫ�ﵽ�õȼ�����������Ϊ0��û�иò�����ʾ������
function AddTaskHandler( quest_ch_name, func, role_lvl_limit, complete_func, key_content, match_quest_id )
	if type(quest_ch_name) ~= "string" then
		LuaLogE("���������֮�������������ַ�������,������->" .. quest_ch_name);
		return;
	end
	if type(func) ~= "function" then
		LuaLogE("���������֮��������Ĳ��������Ǻ�������,������->" .. quest_ch_name);
		return;
	end
	if complete_func ~= nil and type(complete_func) ~= "function" then
		LuaLogE("���������֮�������Ĳ��������Ǻ�������,������->" .. quest_ch_name);
		return;
	end
	if role_lvl_limit == nil then
		role_lvl_limit = 0;
	end
	if type(role_lvl_limit) ~= "number" then
		LuaLogE("���������֮��ɫ�ȼ����Ʊ�������������,������->" .. quest_ch_name);
		return;
	end
	if key_content == nil then
		key_content = GetEmptyString();
	end
	if type(key_content) ~= "string" then
		LuaLogE("���������֮�ؼ��������ݱ������ַ�������,������->" .. quest_ch_name);
		return;
	end
	if match_quest_id == nil then
		match_quest_id = GetEmptyString();
	end
	if type(match_quest_id) ~= "string" then
		LuaLogE("���������֮ƥ������ID�Ĳ����������ַ�������,������->" .. quest_ch_name);
		return;
	end
	local en2ch_mgr = GameEn2ChNodeMgr_Me();
	local quest_index = en2ch_mgr:GetQuestIndex();
	if quest_index == nil then
		LuaLogE("string quest_index�����ڣ��������������ʧ��,������->" .. quest_ch_name);
		return;
	end
	local wstr_quest_id = quest_index:ThreeCh2EnA(quest_ch_name, key_content, match_quest_id);
	if wstr_quest_id:empty() then
		LuaLogE("���������֮�Ҳ�������������->" .. quest_ch_name);
		return;
	end
	--[[
	local task_template = TaskCurJobTemplateMgr_Me();
	if not task_template:RebuildUpdateAll() then
		task_template:RebuildUpdateAll()
	end
	if task_template:FindByTaskId(wstr_quest_id) == nil then
		LuaLogE("���������֮ʵ�����Ҳ�������������id->" .. WideCharToGbk(wstr_quest_id) .. ",������Ϊ->" .. quest_ch_name);
		return;
	end
	--]]
	if FindTaskHandlerByEn(wstr_quest_id) ~= nil then
		LuaLogE(quest_ch_name .. "\t���������Ѿ�����������ӳ���ˣ����Դ˴���Ӳ��ɹ�,������->" .. quest_ch_name);
		return;
	end
	local content_idx = en2ch_mgr:GetQuestBeginDescIndex();
	if content_idx == nil then
		LuaLogE("���������֮conten index������,������->" .. quest_ch_name);
		return;
	end
	--LuaLog("���������֮�ɹ����->" .. quest_ch_name);
	local full_content = content_idx:En2Ch(wstr_quest_id);
	table.insert(g_task_handle_map_, { quest_ch_name, wstr_quest_id, func, role_lvl_limit, complete_func, key_content, full_content, match_quest_id });
end

--��һ���ѽ����������û��ȥ���򷵻ؼ�,����Ϊ��
function RunOneAcceptedTaskHandler()
	local gps = UpdateRole();
	if gps == nil then
		LuaLogE("��ɫ����Failed");
		return false;
	end
	local role_lvl = gps:GetLevel();
	if role_lvl < 1 then
		LuaLogE("��ɫ�ȼ�����ȷ->" .. tostring(role_lvl));
		return false;
	end
	local accepted_task_mgr = gps:GetReceivedTask();
	local handler_tbl;
	for accepted_task in Closure_Iterator(accepted_task_mgr:TraverseUncompleteTasks()) do
		handler_tbl = FindTaskHandlerByEn(accepted_task:GetStrTaskId(), role_lvl);
		if handler_tbl ~= nil then
			break;
		end
	end
	if handler_tbl == nil then
		return false;
	end
	local do_func = handler_tbl[g_THI_do_func];
	if do_func == nil then
		assert(false, "������֮������Ϊ��");
		return false;
	end
	LuaLog("��ʼ��������->" .. handler_tbl[g_THI_ch_name_]);
	local res = do_func();
	LuaLog("�����������->" .. handler_tbl[g_THI_ch_name_]);
	if res ~= nil then
		if type(res) ~= "boolean"  then
			LuaLogE(handler_tbl[g_THI_ch_name_] .. "\t�����������ķ������ͱ����ǲ������ͣ�������ʾ�ú���ִ�гɹ����");
			return false;
		end
		if res == false then
			return false;
		end
	end
	--AutoCommitCompleteTasks();
	return true;
end

function RunTheAcceptedTaskHandler( quest_id )
	local task_handler = FindTaskHandlerByEn(quest_id);
	if task_handler == nil then
		return false;
	end
	local do_handler = task_handler[g_THI_do_func]
	if do_handler == nil then
		return false;
	end
	do_handler();
	return true;
end

--���һ���ѽ����������û��ȥ���򷵻ؼ�,����Ϊ��
function RunOneCompletableTaskHandler()
	local gps = UpdateRole();
	if gps == nil then
		LuaLogE("��ɫ����Failed");
		return false;
	end
	local role_lvl = gps:GetLevel();
	if role_lvl < 1 then
		LuaLogE("��ɫ�ȼ�����ȷ->" .. tostring(role_lvl));
		return false;
	end
	local accepted_task_mgr = gps:GetReceivedTask();
	local complete_handler, handler_tbl;
	for accepted_task in Closure_Iterator(accepted_task_mgr:TraverseCompleteTasks()) do
		handler_tbl = FindTaskHandlerByEn(accepted_task:GetStrTaskId(), role_lvl);
		if handler_tbl ~= nil then
			complete_handler = handler_tbl[g_THI_complete_func_];
			if complete_handler ~= nil then
				break;
			end
		end
	end
	if complete_handler == nil then
		return false;
	end
	LuaLog("��ʼ�����������->" .. handler_tbl[g_THI_ch_name_]);
	local res = complete_handler();
	LuaLog("��������������->" .. handler_tbl[g_THI_ch_name_]);
	if res ~= nil then
		if type(res) ~= "boolean"  then
			LuaLogE(handler_tbl[g_THI_ch_name_] .. "\t��������ɴ������ķ������ͱ����ǲ������ͣ�������ʾ�ú���ִ�гɹ����");
			return false;
		end
		if res == false then
			return false;
		end
	end
	if not accepted_task_mgr:RebuildUpdateAll() then
		LuaLogE("���һ���ѽ�������֮����������ѽ�������Ϣʧ��");
		return false;
	end
	return gps:CommitTask(handler_tbl[g_THI_en_id_]);
end

function RunTheCompletableTaskHandler( quest_id )
	local task_handler = FindTaskHandlerByEn(quest_id);
	if task_handler == nil then
		return false;
	end
	local complete_handler = task_handler[g_THI_complete_func_]
	if complete_handler == nil then
		return false;
	end
	complete_handler();
	return true;
end

--����һ���������������û�н��ܳɹ��򷵻ؼ٣�����Ϊ��
function AcceptOneTaskHandlerTask()
	local gps = UpdateRole();
	if gps == nil then
		LuaLogE("��ɫ����Failed");
		return false;
	end
	local role_lvl = gps:GetLevel();
	if role_lvl < 1 then
		LuaLogE("��ɫ�ȼ�����ȷ->" .. tostring(role_lvl));
		return false;
	end
	local npc_mgr = TaskNpcMgr_Me();
	if not npc_mgr:RebuildUpdateAll() then
		LuaLogE("task npc mgr update failed");
		return false;
	end
	local quest_id;
	for task_npc in Closure_Iterator(npc_mgr:TraverseAcceptableNpc()) do
		for task_node in Closure_Iterator(task_npc:GetAcceptableMgr():TraverseAllTask()) do
			if FindTaskHandlerByEn(task_node:GetTaskId(), role_lvl) ~= nil then
				quest_id = task_node:GetTaskId();
				break;
			end
		end
		if quest_id ~= nil then
			break;
		end
	end
	if quest_id == nil then
		return false;
	end
	if not gps:AcceptTheTaskW(quest_id) then
		return false;
	end
	Delay(300);
	return true;
end

--�Զ�������������
function AutoRunTaskHandlerTasks()
	repeat
		AutoCommitCompleteTasks();
		repeat
		until not AcceptOneTaskHandlerTask();
	until not RunOneAcceptedTaskHandler() and not RunOneCompletableTaskHandler();
	return true;
end

function AcceptAllTaskHandlerTasks()
	AutoCommitCompleteTasks();
	repeat
	until not AcceptOneTaskHandlerTask();
end

--��������һ������
function AcceptLocalMapAnyTask()
	UpdateMapRoom();
	UpdateAllGameObjs();
	local gps = UpdateRole();
	if gps == nil then
		return false;
	end
	return gps:AcceptLocalMapAnyTask();
end

--���ܱ���ͼ������������
function AcceptLocalMapAnyAllTasks()
	local gps = UpdateRole();
	if gps == nil then
		return 0;
	end
	return gps:AcceptLocalMapAnyAllTasks();
end

--�����������ݵĹؼ�����
function IdxTaskKeyContents( sub_contents )
	if type(sub_contents) ~= "string" then
		LuaLogE("�����������ݵĹؼ����ֵĲ����������ַ�������");
		assert(false, "�����������ݵĹؼ����ֵĲ����������ַ�������");
		return;
	end
	return MakeMatchSubStr(sub_contents);
end

--��������ID�Ĺؼ�����
function IdxTaskIdKey( sub_contents )
	if type(sub_contents) ~= "string" then
		LuaLogE("��������ID�Ĺؼ����ֵĲ����������ַ�������");
		assert(false, "��������ID�Ĺؼ����ֵĲ����������ַ�������");
		return;
	end
	return MakeMatchSubStr(sub_contents);
end

--�����ϸ��������
function AddSpecifyTaskHandler( quest_ch_name, func, role_lvl_limt, complete_func, key_sub, match_quest_id )
	local key_content;
	if key_sub ~= nil then
		key_content = key_sub.str_;
	end
	local match_quest;
	if match_quest_id ~= nil then
		match_quest = match_quest_id.str_;
	end
	return AddTaskHandler(quest_ch_name, func, role_lvl_limt, complete_func, key_content, match_quest);
end

--�����ϸ��ְҵ������
function AddSpecifyJobTaskHandler( quest_ch_name, func, role_lvl_limt, complete_func, key_sub )
	local gps = UpdateRole();
	if gps == nil then
		LuaLogE("�����ϸ��ְҵ������֮��ɫ��Ϣ����ʧ�ܣ������ɫ������Ϸ��������������ӳ��");
		return;
	end
	local job_name = gps:GetJobName();
	if job_name:empty() then
		LuaLogE("�����ϸ��ְҵ������֮��ɫ��ְҵ��Ϊ��");
		return;
	end
	return AddSpecifyTaskHandler(quest_ch_name, func, role_lvl_limt, complete_func, key_sub, IdxTaskIdKey(WideCharToGbk(job_name)));
end

function AddSpecifySubJobTaskHandler( quest_ch_name, func, role_lvl_limt, complete_func, key_sub )
	local gps = UpdateRole();
	if gps == nil then
		LuaLogE("�����ϸ�ķ�ְ֧ҵ������֮��ɫ��Ϣ����ʧ�ܣ������ɫ������Ϸ��������������ӳ��");
		return;
	end
	local job_name = gps:GetSpecifyJobName();
	if job_name:empty() then
		LuaLogE("�����ϸ�ķ�ְ֧ҵ������֮��ɫ��ְҵ��Ϊ��");
		return;
	end
	return AddSpecifyTaskHandler(quest_ch_name, func, role_lvl_limt, complete_func, key_sub, IdxTaskIdKey(WideCharToGbk(job_name)));
end
