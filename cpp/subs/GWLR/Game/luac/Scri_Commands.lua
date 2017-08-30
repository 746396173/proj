
function �ӳ�( ���� )
	if type(����) ~= "number" then
		LuaLogE("�ӳ�֮������������������")
		return false
	end
	RunInfo("�ӳ٣�ʱ���ǣ�" .. tostring(����))
	return Delay(����);
end

--[[
���ã����һ��������
����1����������ƣ��������ַ������ͣ�����Ϊ��
����2��������Ĵ�������ȥ�ӿ��Խ��ܵ����񡣱�����һ��������ɵ��õ����ͣ���Ϊ��
����3��������Ĵ�������ȥ���Ѿ��ӵ������񡣱�����һ��������ɵ��õ����ͣ���Ϊ��
����4���������Ĵ�������ȥ��ɻ��ύһ���Ѿ���ɵ����񡣱�����һ��������ɵ��õ����ͣ���Ϊ��
����5���Զ���Ĳ������������ݸ�������Ĵ�������������Ĵ��������������Ĵ�������������ʵ��ĳЩ���������������ͣ���Ϊ��
����6������ID���е��������ͬ������������ֻ��������ID��Ψһȷ��һ�������������ͣ���Ϊ�ա�
ע�����������Ĵ�������������Ĵ��������������Ĵ����������߲���ͬʱΪ�գ���ͬ���Ĳ���������1������ID������2��������������3���Զ���Ĳ���
]]
function ���������( task_name, accept_handler, do_handler, done_handler, unknown_param, task_id )
	g_is_out_to_console = false
	RunInfo("���������,��������:" .. task_name)
	g_is_out_to_console = true
	return TH_Mgr:AddItem(task_name, accept_handler, do_handler, done_handler, unknown_param, task_id)
end

function ��һ���ɽӵ�����()
	RunInfo("��һ���ɽӵ�����")
	return ��ȫִ��֮�����쳣(SafeSkipRun_AutoAcceptOne, false);
end

function ��һ��δ��ɵ�����()
	RunInfo("��һ��δ��ɵ�����")
	return ��ȫִ��֮�����쳣(SafeSkipRun_AutoDoOne, false);
end

function �ύһ������ɵ�����()
	RunInfo("�ύһ������ɵ�����")
	return ��ȫִ��֮�����쳣(SafeSkipRun_AutoDoneOne, false);
end

function �������е����񶼴�������()
	RunInfo("�������е����񶼴�������")
	return not HasUnHandledAtTaskHandles()
end

function ���������()
	RunInfo("���������")
	return TH_Mgr:ClearAll();
end

--[[
��һ�������Ƕ��������ַ������ͣ�����Ϊ��
�ڶ��������Ƕ�����⣬�ַ������ͣ�����Ϊ��
]]
function ����NPC( obj_name, obj_title )
	local the_str = ""
	if type(obj_title) == "string" then
		the_str = " ������⣺" .. obj_title
	end
	RunInfo("����NPC��npc��" .. obj_name .. the_str)
	return scmd():FindNpcByName(obj_name, obj_title)
end

function ����ָ�����ֵĿɴ�Ķ���( obj_name )
	RunInfo("����ָ�����ֵĿɴ�Ķ�����Ϸ��������" .. obj_name)
	return scmd():FindBeatableMonsterByName(obj_name)
end

function ����BOSS()
	RunInfo("����BOSS")
	return scmd():FindTheBoss()
end

function �ȴ�����BOSS( wait_time )
	if type(wait_time) ~= "number" then
		LuaLogE("�ȴ�����BOSS֮�ȴ�ʱ���������������")
		return false
	end
	RunInfo("�ȴ�����BOSS���ȴ�ʱ�䣺" .. tostring(wait_time))
	return scmd():WaitAppearBoss(wait_time)
end

function �ȴ�����NPC( obj_name, wait_time )
	if type(wait_time) ~= "number" then
		LuaLogE("�ȴ�����NPC֮�ȴ�ʱ���������������")
		return false
	end
	if type(obj_name) ~= "string" then
		LuaLogE("�ȴ�����NPC֮�������������ַ�������")
		return false
	end
	RunInfo("�ȴ�����NPC����������" .. obj_name .. " �ȴ�ʱ�䣺" .. tostring(wait_time))
	return scmd():WaitAppearTheNpc(obj_name, wait_time)
end

function �ȴ����ֿɴ�Ĺ���( obj_name, wait_time )
	if type(wait_time) ~= "number" then
		LuaLogE("�ȴ����ֿɴ�Ĺ���֮�ȴ�ʱ���������������")
		return false
	end
	if type(obj_name) ~= "string" then
		LuaLogE("�ȴ����ֿɴ�Ĺ���֮�������������ַ�������")
		return false
	end
	RunInfo("�ȴ����ֿɴ�Ĺ����������" .. obj_name .. " �ȴ�ʱ�䣺" .. tostring(wait_time))
	return scmd():WaitAppearBeatableMonster(obj_name, wait_time)
end

function ��ȡ��ɫ��ǰ�����()
	RunInfo("��ȡ��ɫ��ǰ�����")
	return scmd():GetCurRoleRoom()
end

--�����Ƿ���ţ��������ͣ�����Ϊ�գ���ʾ��ɫ���ڷ���ţ�Ҳ��Ϊ-1����ʾ���з���
function ���Ȳ����������ͨ�������( the_room_num )
	if type(the_room_num) ~= "number" then
		the_room_num = scmd():GetCurRoleRoom()
	end
	RunInfo("���Ȳ����������ͨ������󣬷���ţ�" .. tostring(the_room_num))
	return scmd():FindNearestNormalMonsterFirst(the_room_num)
end

--ֻ��һ������������Ϸ���󣬲���Ϊ��
function ����Ч�Ķ���( obj )
	RunInfo("����Ч�Ķ���")
	return scmd():IsValidGameObj(obj)
end

--ֻ��һ����������������Ϸ��������ͣ������Ϳ�ͨ�� ����ָ�����ֵĶ��� �Ⱥ�����ȡ�õ�
function �ƶ���ָ���Ķ������( obj, steps )
	if obj == nil then
		LuaLogE("�ƶ���ָ���Ķ������֮�������벻��Ϊ��");
		return false;
	end
	if type(steps) ~= "number" then
		steps = 1
	end
	RunInfo("�ƶ���ָ���Ķ������")
	return scmd():SetRoleToBack(obj, steps)
end

function �ƶ���ָ���Ķ�����ǰ( obj, steps )
	if obj == nil then
		LuaLogE("�ƶ���ָ���Ķ�����ǰ֮�������벻��Ϊ��");
		return false;
	end
	if type(steps) ~= "number" then
		steps = -1
	end
	RunInfo("�ƶ���ָ���Ķ�����ǰ")
	return scmd():SetRoleToBack(obj, steps)
end

--ֻ��һ����������������Ϸ��������ͣ������Ϳ�ͨ�� ����ָ�����ֵĶ��� �Ⱥ�����ȡ�õ�
function ��NPC���( obj )
	if obj == nil then
		LuaLogE("��NPC���֮�������벻��Ϊ��");
		return false;
	end
	RunInfo("��NPC���")
	return scmd():OpenNpc(obj)
end

function ��NPC�������( obj )
	if obj == nil then
		LuaLogE("��NPC�������֮�������벻��Ϊ��");
		return false;
	end
	RunInfo("��NPC�������")
	return scmd():OpenNpc_Grid(obj)
end

--ֻ��һ���������������������ͣ�Ϊ����ID
function ����ָ��ID������( task_id )
	if type(task_id) ~= "number" then
		LuaLogE("����ָ��ID������֮������������������")
		return false
	end
	RunInfo("����ָ��ID����������ID��" .. tostring(task_id))
	return scmd():AcceptTaskById(task_id)
end

function ����ָ��ID������( task_id )
	if type(task_id) ~= "number" then
		LuaLogE("����ָ��ID������֮������������������")
		return false
	end
	RunInfo("����ָ��ID����������ID��" .. tostring(task_id))
	return scmd():GiveUpTask(task_id)
end

--ֻ��һ���������������������ͣ�Ϊ����ID
function �ύָ��ID������( task_id )
	if type(task_id) ~= "number" then
		LuaLogE("�ύָ��ID������֮������������������")
		return false
	end
	RunInfo("�ύָ��ID����������ID��" .. tostring(task_id))
	return scmd():CommitTaskById(task_id)
end

function ����NPC�Ի�( task_id )
	if type(task_id) ~= "number" then
		LuaLogE("����NPC�Ի�֮������������������")
		return false
	end
	RunInfo("����NPC�Ի�������ID��" .. tostring(task_id))
	return scmd():DoNpcChat(task_id)
end

--ֻ��һ���������������ַ������ͣ�Ϊ��ׯ��
function �ƶ���ָ���Ĵ�ׯ( village_name, room_num )
	if type(village_name) ~= "string" then
		LuaLogE("�ƶ���ָ���Ĵ�ׯ֮�����������ַ�������")
		return false
	end
	if type(room_num) ~= "number" then
		room_num = 0
	end
	RunInfo("�ƶ���ָ���Ĵ�ׯ����ׯ����" .. village_name .. " ����ţ�" .. tostring(room_num))
	return scmd():MoveToTheVillage(village_name, room_num);
end

--��һ�������Ǹ��������������ַ�������
function �ƶ���ָ���ĸ���( fb_name )
	if type(fb_name) ~= "string" then
		LuaLogE("�ƶ���ָ���ĸ���֮�����������������ַ�������")
		return false
	end
	RunInfo("�ƶ���ָ���ĸ�������������" .. fb_name)
	return scmd():MoveToTheFb(fb_name);
end

function �ƶ���ָ���ĸ���_ID( fb_id )
	if type(fb_id) ~= "number" then
		LuaLogE("�ƶ���ָ���ĸ���_ID֮����ID������������������")
		return false
	end
	RunInfo("�ƶ���ָ���ĸ���_ID������ID��" .. fb_id)
	return scmd():MoveToTheFbById(fb_id);
end

function �ƶ���ָ������������( fb_name )
	if type(fb_name) ~= "string" then
		LuaLogE("�ƶ���ָ������������֮�����������������ַ�������")
		return false
	end
	RunInfo("�ƶ���ָ����������������������" .. fb_name)
	return scmd():MoveToTheFb_Cat(fb_name);
end

function �ƶ���ָ������������( fb_name )
	if type(fb_name) ~= "string" then
		LuaLogE("�ƶ���ָ������������֮�����������������ַ�������")
		return false
	end
	RunInfo("�ƶ���ָ����������������������" .. fb_name)
	return scmd():MoveToTheFb_King(fb_name);
end

function �ƶ���ָ����������Ӣ����( fb_name, unlock_item_name )
	if type(fb_name) ~= "string" then
		LuaLogE("�ƶ���ָ����������Ӣ����֮�����������������ַ�������")
		return -1
	end
	if type(unlock_item_name) ~= "string" then
		unlock_item_name = ""
	end
	RunInfo("�ƶ���ָ����������Ӣ��������������" .. fb_name .. " ������Ʒ����" .. unlock_item_name)
	return scmd():MoveToTheFb_King_Cream(fb_name, unlock_item_name)
end

function ����ָ������������( fb_name )
	if type(fb_name) ~= "string" then
		LuaLogE("����ָ������������֮�����������������ַ�������")
		return false
	end
	RunInfo("����ָ����������������������" .. fb_name)
	return scmd():CanDoTheFb_Cat(fb_name);
end

function �����������������( fb_id )
	if type(fb_id) ~= "number" then
		LuaLogE("�����������������֮����ID������������������")
		return
	end
	RunInfo("�����������������������ID:" .. tostring(fb_id))
	return scmd():AddFbBlackList_Cat(fb_id)
end

function �����������������()
	RunInfo("�����������������")
	return scmd():ClrFbBlackList_Cat()
end

function ��Ӹ���������( fb_id )
	if type(fb_id) ~= "number" then
		LuaLogE("��Ӹ���������֮����ID������������������")
		return
	end
	RunInfo("��Ӹ���������������ID:" .. tostring(fb_id))
	return scmd():AddFbBlackList(fb_id)
end

function ��ո���������()
	RunInfo("��ո���������")
	return scmd():ClrFbBlackList()
end


function �����ؿ�()
	RunInfo("�����ؿ�")
	return scmd():GiveUpFb();
end

function �˳�����ѵ��()
	RunInfo("�˳�����ѵ��")
	return scmd():GiveUpXinShouXunLian();
end

function �ƶ���ָ���ķ���( room_num )
	if type(room_num) ~= "number" then
		LuaLogE("�ƶ���ָ���ķ���֮������Ų�����������������")
		return false
	end
	RunInfo("�ƶ���ָ���ķ��䣬��������ǣ�" .. tostring(room_num))
	return scmd():MoveToTheRoom(room_num);
end

--[[
��������Ʒ�����ַ������ͣ�����Ϊ��
]]
function ��ȡ��������Ʒ( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("��ȡ��������Ʒ֮��Ʒ�������������ַ�������")
		return 0
	end
	RunInfo("��ȡ��������Ʒ����Ʒ����" .. item_name)
	return scmd():GainSupplyItem(item_name);
end

--[[
��һ�������ǹ�����󣬿ɴ� ����ָ�����ֵĶ��� �Ⱥ������أ�����Ϊ��
�ڶ��������ǹ����ļ������λ�Ǻ��룬����Ϊ0����ʾû�м�����������ͣ�����Ϊ��
���ع�������
]]
function ����ָ���Ĺ���ֱ������( obj, sleep_time, is_any_direction )
	if type(sleep_time) ~= "number" then
		LuaLogE("����ָ���Ĺ���ֱ������֮���ʱ�������������������")
		return 0
	end
	if type(is_any_direction) ~= "boolean" then
		is_any_direction = false
	end
	RunInfo("����ָ���Ĺ���ֱ�����������ʱ�䣺" .. tostring(sleep_time) .. "����")
	return scmd():HitTheMonsterToDie(obj, sleep_time, is_any_direction, true)
end

function ���ù���ģʽ_ʹ�ñ�����Ʒ( item_name, steps )
	if type(item_name) ~= "string" then
		LuaLogE("���ù���ģʽ_ʹ�ñ�����Ʒ֮��Ʒ���������ַ�������");
		return false
	end
	if type(steps) ~= "number" then
		steps = 1
	end
	RunInfo("���ù���ģʽ_ʹ�ñ�����Ʒ����Ʒ����" .. item_name)
	return scmd():SetHitMode_UsePacketItem(item_name, steps)
end

--���õĹ���ģʽֻ�Ǵ˴���Ч����ִ����ĳ��������Ľű�����󣬱��ָ���Ĭ�ϵĹ���ģʽ
--�����ǹ���ģʽ����֧�֣��Ҽ�����
function ���ô˴ι���ģʽ( mode_name )
	if type(mode_name) ~= "string" then
		LuaLogE("���ô˴ι���ģʽ֮�����������ַ�������")
		return false
	end
	RunInfo("���ô˴ι���ģʽ��ģʽ����" .. mode_name)
	return scmd():SetCurTimeHitMode(mode_name)
end

--��һ�������ǹ����ļ������λ�Ǻ��룬����Ϊ0����ʾû�м�����������ͣ�����Ϊ��
--�ڶ��������� �Ƿ��Ƥ�����Ϊ�棬���Ƥÿ�������Ĺ���
--����ɱ���Ĺ��������
function ɱ�Ȿ�������( sleep_time, is_collect )
	if type(sleep_time) ~= "number" then
		LuaLogE("ɱ�Ȿ�������֮���ʱ�������������������")
		return 0
	end
	if type(is_collect) ~= "boolean" then
		is_collect = false
	end
	RunInfo("ɱ�Ȿ������ÿ�δ�������ʱ�����ǣ�" .. tostring(sleep_time) .. "  �Ƿ�Ҫ��Ƥ��" .. tostring(is_collect))
	return scmd():KillOverTheRoomMonsters(sleep_time, is_collect, scmd():GetCurRoleRoom())
end

--��һ�������ǹ����ļ������λ�Ǻ��룬����Ϊ0����ʾû�м�����������ͣ�����Ϊ��
--�ڶ��������� �Ƿ��Ƥ�����Ϊ�棬���Ƥÿ�������Ĺ���
--������������ ����ţ����Ϊ�գ���ʾ��ɫ���ڷ��䣬-1��ʾ���з���
--����ɱ���Ĺ��������
function ɱ��ָ�����������й���( sleep_time, is_collect, room_num )
	if type(sleep_time) ~= "number" then
		LuaLogE("ɱ��ָ�����������й���֮���ʱ�������������������")
		return 0
	end
	if type(is_collect) ~= "boolean" then
		is_collect = false
	end
	if type(room_num) ~= "number" then
		room_num = scmd():GetCurRoleRoom()
	end
	RunInfo("ɱ��ָ�����������й��ÿ�δ�������ʱ�����ǣ�" .. tostring(sleep_time) .. "  �Ƿ�Ҫ��Ƥ��" .. tostring(is_collect) .. "  ����ţ�" .. tostring(room_num))
	return scmd():KillOverTheRoomMonsters(sleep_time, is_collect, room_num)
end

function ������ǰִ����Ϣ()
	g_is_start_run_info = true
end

function �رյ�ǰִ����Ϣ()
	g_is_start_run_info = false
end

function ���������Ϣ������̨()
	g_is_out_to_console = true
end

function �ر������Ϣ������̨()
	g_is_out_to_console = false
end

--ֻ��һ���������ɼ��ȴ�ʱ�䣬�������ͣ���Ϊ0����ʾ���ȴ�������Ϊ��
function �Զ��ɼ�һ������Ķ���( collect_time )
	if type(collect_time) ~= "number" then
		LuaLogE("�Զ��ɼ�һ������Ķ���֮�ɼ��ȴ�ʱ���������������");
		return false
	end
	RunInfo("�Զ��ɼ�һ������Ķ��󣬲ɼ��ȴ�ʱ�䣺" .. tostring(collect_time))
	return scmd():AutoCollectNearestCollectableObjAsSameRoom(collect_time)
end

function �Զ��ɼ�������Ķ���( collect_time )
	if type(collect_time) ~= "number" then
		LuaLogE("�Զ��ɼ�������Ķ���֮�ɼ��ȴ�ʱ���������������");
		return false
	end
	RunInfo("�Զ��ɼ�������Ķ��󣬲ɼ��ȴ�ʱ�䣺" .. tostring(collect_time))
	return scmd():AutoCollectOverNearestCollectableObjAsSameRoom(collect_time)
end

--ֻ��һ���������ɼ��ȴ�ʱ�䣬�������ͣ���Ϊ0����ʾ���ȴ�������Ϊ��
function �Զ��ɼ�һ�η������ж���( collect_time )
	if type(collect_time) ~= "number" then
		LuaLogE("�Զ��ɼ�һ�η������ж���֮�ɼ��ȴ�ʱ���������������");
		return false
	end
	RunInfo("�Զ��ɼ�һ�η������ж��󣬲ɼ��ȴ�ʱ�䣺" .. tostring(collect_time))
	return scmd():AutoCollectOnceAllRoomCollectableObj(collect_time)
end

--ֻ��һ���������ɼ��ȴ�ʱ�䣬�������ͣ���Ϊ0����ʾ���ȴ�������Ϊ��
function �Զ��ɼ��귿�����ж���( collect_time )
	if type(collect_time) ~= "number" then
		LuaLogE("�Զ��ɼ��귿�����ж���֮�ɼ��ȴ�ʱ���������������");
		return 0
	end
	RunInfo("�Զ��ɼ��귿�����ж��󣬲ɼ��ȴ�ʱ�䣺" .. tostring(collect_time))
	return scmd():AutoCollectOverAllObj(collect_time)
end

--[[
�����������ɼ�ָ���ķ�������еķ��䣻�������òɼ��Ķ��������������Ͷ�ÿ������ɼ���������������ֻ�ɼ��ض����ֵĶ���
��һ��������ÿ�βɼ��ȴ�ʱ�䣬�������ͣ�����Ϊ��
�ڶ��������Ƿ���ţ���ʾҪ���ĸ�������вɼ����������ͣ�����Ϊ�գ�Ϊ�ձ�ʾ��ɫ���ڵķ���ţ�Ϊ-1��ʾ�����з�����вɼ�
�����������ǲɼ�����������������ʾ���ɼ�ָ�������Ĳɼ������������ͣ�����Ϊ�գ���ʾû���������ƣ�
���ĸ������Ƕ�ÿ���ɼ�����ɼ������������������ͣ�����Ϊ�գ���ʾû�д�������
����������ǲɼ�������֣���ʾֻ�ɼ����и����ֵĶ����������ͣ�����Ϊ�գ���ʾ����ʲô���ֵĶ��󶼻ᱻ�ɼ�
����������ÿ�βɼ����������£��������ͣ���Ϊ��
]]
function �Զ���ϸ�ɼ�( collect_time, room_num, obj_cnt, every_collect_cnt, collect_obj_name, gained_item, do_after_every_collect )
	if type(collect_time) ~= "number" then
		LuaLogE("�Զ���ϸ�ɼ�֮�ɼ��ȴ�ʱ���������������");
		return 0
	end
	if room_num == nil then
		room_num = -2
	end
	if type(room_num) ~= "number" then
		LuaLogE("�Զ���ϸ�ɼ�֮����Ų�����������������");
		return 0
	end
	if obj_cnt == nil then
		obj_cnt = -1
	end
	if type(obj_cnt) ~= "number" then
		LuaLogE("�Զ���ϸ�ɼ�֮Ҫ�ɼ��Ķ�����������������������������");
		return 0
	end
	if every_collect_cnt == nil then
		every_collect_cnt = -1
	end
	if type(every_collect_cnt) ~= "number" then
		LuaLogE("�Զ���ϸ�ɼ�֮��ÿ������ɼ��������Ĳ�����������������");
		return 0
	end
	if collect_obj_name == nil then
		collect_obj_name = ""
	end
	if type(collect_obj_name) ~= "string" then
		LuaLogE("�Զ���ϸ�ɼ�֮��ָ���Ĳɼ���������ֵĲ����������ַ�������");
		return 0
	end
	if type(gained_item) ~= "string" then
		gained_item = ""
	end
	if type(do_after_every_collect) ~= "function" then
		do_after_every_collect = nil
	end
	RunInfo("�Զ���ϸ�ɼ����ɼ��ȴ�ʱ�䣺" .. tostring(collect_time) .. " ����ţ�" .. tostring(room_num) .. "  �ɼ��������������" .. tostring(obj_cnt) .. " ÿ����������ɼ�������" .. tostring(every_collect_cnt) .. " �ɼ���������" .. collect_obj_name
		.. " ��Ҫ�ɼ��õ�����Ʒ����" .. gained_item)
	return scmd():AutoCollectSpecifc(collect_time, room_num, obj_cnt, every_collect_cnt, collect_obj_name, gained_item, do_after_every_collect)
end

--[[
�����������ɼ�ָ���ķ�������еķ��䣻�������òɼ��Ķ��������������Ͷ�ÿ������ɼ���������������ֻ�ɼ��ض����ֵĶ���
��һ��������ÿ�βɼ��ȴ�ʱ�䣬�������ͣ�����Ϊ��
�ڶ��������ǲɼ�����������������ʾ���ɼ�ָ�������Ĳɼ������������ͣ�����Ϊ�գ���ʾû���������ƣ�
�����������Ƕ�ÿ���ɼ�����ɼ������������������ͣ�����Ϊ�գ���ʾû�д�������
���ĸ������ǲɼ�������֣�֧�ֵĶ������У��󳡡����������ܵء�����ľ�����䷿����ҩ��1����ҩ��2����ҩ��3
]]
function �Զ�ׯ԰�ɼ�( collect_time, obj_cnt, every_collect_cnt, collect_obj_name )
	if type(collect_time) ~= "number" then
		LuaLogE("�Զ�ׯ԰�ɼ�֮�ɼ��ȴ�ʱ���������������");
		return 0
	end
	if obj_cnt == nil then
		obj_cnt = -1
	end
	if type(obj_cnt) ~= "number" then
		LuaLogE("�Զ�ׯ԰�ɼ�֮Ҫ�ɼ��Ķ�����������������������������");
		return 0
	end
	if every_collect_cnt == nil then
		every_collect_cnt = -1
	end
	if type(every_collect_cnt) ~= "number" then
		LuaLogE("�Զ�ׯ԰�ɼ�֮��ÿ������ɼ��������Ĳ�����������������");
		return 0
	end
	if collect_obj_name == nil then
		collect_obj_name = ""
	end
	if type(collect_obj_name) ~= "string" then
		LuaLogE("�Զ�ׯ԰�ɼ�֮��ָ���Ĳɼ���������ֵĲ����������ַ�������");
		return 0
	end
	RunInfo("�Զ�ׯ԰�ɼ����ɼ��ȴ�ʱ�䣺" .. tostring(collect_time) .. "  �ɼ��������������" .. tostring(obj_cnt) .. " ÿ����������ɼ�������" .. tostring(every_collect_cnt) .. " �ɼ���������" .. collect_obj_name)
	return scmd():AutoCollectSpecifc_Farm(collect_time, obj_cnt, every_collect_cnt, collect_obj_name)
end

function �Զ��ɼ��귿��ָ���Ķ���( obj_name, collect_time )
	if type(collect_time) ~= "number" then
		LuaLogE("�Զ��ɼ��귿��ָ���Ķ���֮�ɼ��ȴ�ʱ���������������");
		return 0
	end
	if type(obj_name) ~= "string" then
		LuaLogE("�Զ��ɼ��귿��ָ���Ķ���֮�ɼ������Ʊ������ַ�������");
		return 0
	end
	RunInfo("�Զ��ɼ��귿��ָ���Ķ��󣬲ɼ�����" .. obj_name .. "  �ɼ��ȴ�ʱ�䣺" .. tostring(collect_time))
	return scmd():AutoCollectOverTheObj(obj_name, collect_time)
end

--[[
��һ�������ǵȴ�ʱ�䣬�������ͣ�����Ϊ��
�ڶ��������Ƕ��������ַ������ͣ�����Ϊ��
�����������Ƿ���ţ��������ͣ���Ϊ�գ���ʾ��ɫ���ڷ����
]]
function �ȴ����ֲɼ�����( wait_time, obj_name, room_num )
	if type(wait_time) ~= "number" then
		LuaLogE("�ȴ����ֲɼ�����֮�ȴ�ʱ���������������");
		return false
	end
	if type(obj_name) ~= "string" then
		LuaLogE("�ȴ����ֲɼ�����֮�ɼ������Ʊ������ַ�������");
		return false
	end
	if room_num == nil then
		room_num = -2
	end
	if type(room_num) ~= "number" then
		LuaLogE("�ȴ����ֲɼ�����֮����ű�������������");
		return false
	end
	RunInfo("�ȴ����ֲɼ����󣬵ȴ�ʱ�䣺" .. tostring(wait_time) .. "  �ɼ���������" .. obj_name .. " ����ţ�" .. tostring(room_num))
	return scmd():WaitTheCollectableObj(wait_time, obj_name, room_num)
end

--�޲��������زɼ�����
function ��õ�ǰ�������ɫ����Ĳɼ�����()
	RunInfo("��õ�ǰ�������ɫ����Ĳɼ�����")
	return FindNearestCollectObjAsSameRoom()
end

function ���ָ�����ֵĿɲɼ�����( obj_name )
	RunInfo("���ָ�����ֵĿɲɼ����󣬶�������" .. obj_name)
	return scmd():FindCollectObjByName(obj_name)
end

--[[
��һ�������ǲɼ����󣬿��� ��õ�ǰ�������ɫ����Ĳɼ����� ���
�ڶ��������ǲɼ��ȴ�ʱ�䣬�������ͣ���Ϊ0����ʾ���ȴ�������Ϊ��
]]
function �ɼ�һ��ָ���Ķ���( obj, collect_time )
	if type(collect_time) ~= "number" then
		LuaLogE("�ɼ�һ��ָ���Ķ���֮�ɼ��ȴ�ʱ���������������");
		return false
	end
	RunInfo("�ɼ�һ��ָ���Ķ��󣬲ɼ��ȴ�ʱ�䣺" .. tostring(collect_time))
	return scmd():CollectTheCollectableObj(obj, collect_time)
end

function �ȴ��ɰ�Ƥ( wait_time )
	if type(wait_time) ~= "number" then
		LuaLogE("�ȴ��ɰ�Ƥ֮���ȴ�ʱ���������������");
		return false
	end
	RunInfo("�ȴ��ɰ�Ƥ�����ȴ�ʱ�䣺" .. tostring(wait_time))
	return scmd():WaitForCutSkin(wait_time)
end

function �õ��������з����()
	RunInfo(�õ��������з����)
	return scmd():GetCurFbAllRoomNum()
end

--�޲���
function �յ�()
	RunInfo("�յ�")
	return scmd():TakeInKnife();
end

--ֻ��һ����������Ʒ�����ַ������ͣ���Ϊ��
function ʹ�ñ�����Ʒ( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("ʹ�ñ�����Ʒ֮��Ʒ���������ַ�������");
		return false
	end
	RunInfo("ʹ�ñ�����Ʒ����Ʒ����" .. item_name)
	return scmd():UsePackageItem(item_name)
end

--��������Ʒ����֧��ģ��ƥ��
function ����ʹ����Ʒ( item_name, use_cnt )
	if type(item_name) ~= "string" then
		LuaLogE("����ʹ����Ʒ֮��Ʒ���������ַ�������");
		return 0
	end
	if type(use_cnt) ~= "number" or use_cnt <= 0 then
		use_cnt = 0xfffffff
	end
	RunInfo("����ʹ����Ʒ����Ʒ����" .. item_name .. " ������" .. tostring(use_cnt))
	return scmd():UseSomeItems(item_name, use_cnt)
end

--��������Ʒ����֧��ģ��ƥ��
function ʹ��������Ʒ( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("ʹ��������Ʒ֮��Ʒ���������ַ�������");
		return 0
	end
	RunInfo("ʹ��������Ʒ����Ʒ����" .. item_name)
	return scmd():UseTaskItem(item_name)
end

function ����������Ʒ( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("����������Ʒ֮��Ʒ���������ַ�������");
		return false
	end
	RunInfo("����������Ʒ����Ʒ����" .. item_name)
	return scmd():ManuFactureItem(item_name)
end

--��һ���������������ͣ���ʾ���ȴ�ʱ�䣬��λ���룬����Ϊ��
function �ȴ���ͼ( wait_time )
	if type(wait_time) ~= "number" then
		LuaLogE("�ȴ���ͼ֮�ȴ�ʱ���������������")
		return false
	end
	RunInfo("�ȴ���ͼ���ȴ�ʱ�䣺" .. tostring(wait_time))
	return scmd():WaitCrossedGraph(wait_time)
end

--��һ���������������ͣ���ʾ���ȴ�ʱ�䣬��λ���룬����Ϊ��
function �ȴ����س���( wait_time )
	if type(wait_time) ~= "number" then
		LuaLogE("�ȴ����س���֮�ȴ�ʱ���������������")
		return false
	end
	RunInfo("�ȴ����س��򣬵ȴ�ʱ�䣺" .. tostring(wait_time))
	return scmd():WaitRetCity(wait_time)
end

--��һ�������ǵȴ�ʱ�䣬�������ͣ�����Ϊ��
--�ڶ���������Ҫ����ţ��������ͣ���Ϊ�գ���ʾ��ǰ��ɫ���ڷ��䣬Ҳ��Ϊ-1����ʾ���з���
function ��һ��Ƥ( wait_time, room_num )
	if type(wait_time) ~= "number" then
		LuaLogE("��һ��Ƥ֮�ȴ�ʱ���������������")
		return false
	end
	if type(room_num) ~= "number" then
		room_num = scmd():GetCurRoleRoom()
	end
	RunInfo("��һ��Ƥ���ȴ�ʱ�䣺" .. tostring(wait_time) .. "  ����ţ�" .. tostring(room_num))
	return scmd():CutNearestSkinOnce(wait_time, room_num)
end

--��һ�������ǵȴ�ʱ�䣬�������ͣ�����Ϊ��
--�ڶ���������Ҫ����ţ��������ͣ���Ϊ�գ���ʾ��ǰ��ɫ���ڷ��䣬Ҳ��Ϊ-1����ʾ���з���
function ����Ƥ( wait_time, room_num )
	if type(wait_time) ~= "number" then
		LuaLogE("����Ƥ֮�ȴ�ʱ���������������")
		return 0
	end
	if type(room_num) ~= "number" then
		room_num = scmd():GetCurRoleRoom()
	end
	RunInfo("����Ƥ���ȴ�ʱ�䣺" .. tostring(wait_time) .. "  ����ţ�" .. tostring(room_num))
	return scmd():CutOverNearestSkin(wait_time, room_num)
end

--һ����������ʾ�ȴ�ʱ�䣬�������ͣ�����Ϊ�գ�����Ϊ0��Ĭ�ϵȴ�2����
function �ȴ�������״̬( wait_time )
	if wait_time == nil then
		wait_time = 0
	end
	if type(wait_time) ~= "number" then
		LuaLogE("�ȴ�������״̬֮�ȴ�ʱ���������������")
		return false
	end
	RunInfo("�ȴ�������״̬���ȴ�ʱ�䣺" .. tostring(wait_time))
	return scmd():WaitToFree(wait_time)
end

function ��Z��()
	RunInfo("��Z��")
	return scmd():PressKeyZ()
end

function ��Q��()
	RunInfo("��Q��")
	return scmd():PressKeyQ()
end

function ��W��()
	RunInfo("��W��")
	return scmd():PressKeyW()
end

function ��S��()
	RunInfo("��S��")
	return scmd():PressKeyS()
end

function ��A��()
	RunInfo("��A��")
	return scmd():PressKeyA()
end

function ��D��()
	RunInfo("��D��")
	return scmd():PressKeyD()
end

function ���ո��()
	RunInfo("���ո��")
	return scmd():PressKeySpace()
end

function ��ESC��()
	RunInfo("��ESC��")
	return scmd():PressKeyEsc()
end

function ������( x, y )
	RunInfo("������,x:" .. tostring(x) .. " y:" .. tostring(y))
	return scmd():LeftButtonClick(x, y)
end

function �ر�����UI()
	RunInfo("�ر�����UI")
	return scmd():CloseAllUi()
end

function ������й�����Ϣ()
	RunInfo("������й�����Ϣ")
	return scmd():DebugInfoMonsterInfo()
end

function ������пɽ�������Ϣ()
	RunInfo("������пɽ�������Ϣ")
	return scmd():DebugInfoAccetableTask()
end

function ���������Ʒ��Ϣ()
	RunInfo("���������Ʒ��Ϣ")
	return scmd():DebugInfoPackageItemInfo()
end

function ����ɲɼ�����Ϣ()
	RunInfo("����ɲɼ�����Ϣ")
	return scmd():DebugInfoCollectableObjs()
end

--ֻ��һ����������Ʒ���󣬲���Ϊ��
function �õ���Ʒ��( item )
	if item == nil then
		LuaLogE("�õ���Ʒ��֮��Ʒ��������Ϊ��")
		return "";
	end
	local name = scmd():GetItemName(item)
	RunInfo("�õ���Ʒ������Ʒ����" .. name)
	return name
end

--ֻ��һ����������Ʒ���󣬲���Ϊ��
function �õ���Ʒ����( item )
	if item == nil then
		LuaLogE("�õ���Ʒ����֮��Ʒ��������Ϊ��")
		return -1;
	end
	RunInfo("�õ���Ʒ����")
	return scmd():GetItemCnt(item)
end

function �õ�ָ����Ʒ����������( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("�õ�ָ����Ʒ����������֮��Ʒ�������������ַ�������")
		return -1;
	end
	local res = scmd():GetTheItemTotalCnt(item_name);
	RunInfo("�õ�ָ����Ʒ��������������Ʒ����" .. item_name .. " ����:" .. tostring(res))
	return res
end

--ֻ��һ����������Ʒ���󣬲���Ϊ��
function �õ���Ʒ�ȼ�( item )
	if item == nil then
		LuaLogE("�õ���Ʒ�ȼ�֮��Ʒ��������Ϊ��")
		return -1;
	end
	local res = scmd():GetItemLvl(item)
	RunInfo("�õ���Ʒ�ȼ�,�����" .. tostring(res))
	return res
end

--ֻ��һ����������Ʒ���󣬲���Ϊ��
function �õ���Ʒ��ɫ�ȼ�( item )
	if item == nil then
		LuaLogE("�õ���Ʒ��ɫ�ȼ�֮��Ʒ��������Ϊ��")
		return -1;
	end
	local res = scmd():GetItemRoleLvl(item)
	RunInfo("�õ���Ʒ��ɫ�ȼ�,�����" .. tostring(res))
	return res
end

--ֻ��һ����������Ʒ���󣬲���Ϊ��
function ��Ʒ��̫��( item )
	if item == nil then
		LuaLogE("��Ʒ��̫��֮��Ʒ��������Ϊ��")
		return false
	end
	local res = scmd():IsTaiDaoType(item)
	RunInfo("��Ʒ��̫��,�����" .. tostring(res))
	return res
end

--ֻ��һ����������Ʒ���󣬲���Ϊ��
function ����Ч��Ʒ����( item )
	RunInfo("����Ч��Ʒ����")
	if item == nil then
		return false;
	end
	return scmd():IsValidItem(item)
end

--��һ������Ϊ��Ʒ�����ַ������ͣ�����Ϊ��
function ���ұ�����Ʒ( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("���ұ�����Ʒ֮��Ʒ�������������ַ�������")
		return;
	end
	RunInfo("���ұ�����Ʒ����Ʒ����" .. item_name)
	return scmd():FindPakcetItem(item_name)
end

function ���Ҳֿ���Ʒ( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("���Ҳֿ���Ʒ֮��Ʒ�������������ַ�������")
		return;
	end
	RunInfo("���Ҳֿ���Ʒ����Ʒ����" .. item_name)
	return scmd():FindStoreItem(item_name)
end

function ����������Ʒ( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("����������Ʒ֮��Ʒ�������������ַ�������")
		return;
	end
	RunInfo("����������Ʒ����Ʒ����" .. item_name)
	return scmd():FindTaskItem(item_name)
end

--֧��ģ��ƥ��
function �õ�ָ��������Ʒ������( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("�õ�ָ��������Ʒ������֮��Ʒ�������������ַ�������")
		return;
	end
	RunInfo("�õ�ָ��������Ʒ����������Ʒ����" .. item_name)
	return scmd():GetTaskTotalItemCnt(item_name)
end

function ���ұ����Ͳֿ���Ʒ( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("���ұ����Ͳֿ���Ʒ֮��Ʒ�������������ַ�������")
		return;
	end
	RunInfo("���ұ����Ͳֿ���Ʒ����Ʒ����" .. item_name)
	return scmd():FindItemFromPacketAndStore(item_name)
end

function ����װ��( װ���� )
	if type(װ����) ~= "string" then
		LuaLogE("����װ��֮װ���������������ַ�������")
		return false;
	end
	RunInfo("����װ����װ�����ǣ�" .. װ����)
	return scmd():DoCraft(װ����)
end

--װ����֧��ģ������
--װ���������޿�Ϊ�գ���ʾҪ����������������װ��
function �Զ�����װ��( װ����, װ���������� )
	if type(װ����) ~= "string" then
		LuaLogE("�Զ�����װ��֮װ���������������ַ�������")
		return false;
	end
	if type(װ����������) ~= "number" then
		װ���������� = -1
	end
	RunInfo("�Զ�����װ����װ������" .. װ���� .. " װ���������ޣ�" .. tostring(װ����������))
	return scmd():AutoMakeEquip(װ����, װ����������)
end

--[[
��һ����������Ʒ���࣬�ַ������ͣ�����Ϊ�գ�֧�ֵ���Ʒ�����У����ز���Ʒ����������װ������ҩ����������ƿ��������������������ɡ��������ܡ����ص����ˡ���·è��Ӷ����¶ũҵ�ع���ׯ԰����Ʒ
�ڶ�����������Ʒ��
�����������ǹ����������������ͣ�����Ϊ��
���ĸ����������ӵ�������������ϵĸ���Ʒ�Ѿ����������������ˣ��Ͳ��������ˣ��������ͣ�����Ϊ�գ���Ϊ-1����ʾû��ӵ������
�����������Ҫ�����ĳ�����
������������NPC��
]]
function ���ֹ���һ����������Ʒ( shop_category_name, item_name, buy_cnt, max_cnt, village_name, npc_name, gold_limit )
	if type(shop_category_name) ~= "string" then
		LuaLogE("���ֹ���һ����������Ʒ֮��Ʒ��������������ַ�������")
		return false;
	end
	if type(item_name) ~= "string" then
		LuaLogE("���ֹ���һ����������Ʒ֮��Ʒ�������������ַ�������")
		return false;
	end
	if type(buy_cnt) ~= "number" then
		LuaLogE("���ֹ���һ����������Ʒ֮��������������������������")
		return false;
	end
	if type(max_cnt) ~= "number" then
		LuaLogE("���ֹ���һ����������Ʒ֮���ӵ������������������������")
		return false;
	end
	if village_name == nil then
		village_name = ""
	end
	if type(village_name) ~= "string" then
		LuaLogE("���ֹ���һ����������Ʒ֮�����������������ַ�������")
		return false;
	end
	if type(npc_name) ~= "string" then
		LuaLogE("���ֹ���һ����������Ʒ֮NPC�������������ַ�������")
		return false;
	end
	if type(gold_limit) ~= "boolean" then
		gold_limit = true
	end
	RunInfo("���ֹ���һ����������Ʒ����Ʒ���ࣺ" .. shop_category_name .. " ��Ʒ���ǣ�" .. item_name .. " ��������:" .. tostring(buy_cnt) .. " ���ӵ������:" ..
		tostring(max_cnt) .. " ��������" .. village_name .. " NPC����" .. npc_name .. " �Ƿ��������ƣ�" .. tostring(gold_limit))
	return scmd():BuyTheItemAsMaxCnt(shop_category_name, item_name, buy_cnt, max_cnt, village_name, npc_name, gold_limit)
end

--[[
��һ����������Ʒ�����ַ������ͣ�����Ϊ��
�ڶ���������Ŀ��װ���������������ͣ�����Ϊ�ա���ʾ���װ����Ҫ�������Ϊ��װ������������1��ʼ����
]]
function ����װ��( equip_name, lvl_up_equip_idx )
	if type(equip_name) ~= "string" then
		LuaLogE("����װ��֮��Ʒ�������������ַ�������")
		return false;
	end
	if type(lvl_up_equip_idx) ~= "number" then
		LuaLogE("����װ��֮Ŀ��װ������������������������")
		return false;
	end
	RunInfo("����װ������Ʒ����" .. equip_name .. " Ŀ��װ��������" .. tostring(lvl_up_equip_idx))
	return scmd():LvlUpEquip(equip_name, lvl_up_equip_idx)
end

--ֻ��ȥ�Զ���������װ�����ѣ������ϲ��㣬�������Զ�ȥ��ȡ����
function �Զ���������װ��( village_npc )
	if type(village_npc) ~= "table" then
		LuaLogE("�Զ���������װ��֮����NPC��Ϣ���������Ǳ�����")
		return false;
	end
	RunInfo("�Զ���������װ��")
	return scmd():AutoLvlUpBodyEquips(village_npc)
end

--ֻ��ȥ��ȡ ����Զ�����װ�������� ������ӵ�װ������Ĳ��ϡ�����ǰ�������ڰ������У��ǲ�ȥ���ȡ��ǰ����������ϵġ�
function �Զ�ȥ��ȡ��ǰ�����������()
	RunInfo("�Զ�ȥ��ȡ��ǰ�����������")
	return scmd():AutoDoGainCurWeaponMaterial()
end

--[[
����Ӱ�� �Զ���������װ�� �����ָ����Ʒ�����Զ�������
��������Ʒ�����ַ������ͣ�����Ϊ��
]]
function ����Զ���������װ��������( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("����Զ���������װ��������֮��Ʒ�������������ַ�������")
		return false;
	end
	RunInfo("����Զ���������װ������������Ʒ����" .. item_name)
	return scmd():AddAutoLvlUpBlackList(item_name)
end

function ����Զ�����װ��������()
	RunInfo("����Զ�����װ��������")
	return scmd():ClrAutoLvlUpEquipBlackList()
end

function ����Ч������ID( task_id )
	if type(task_id) ~= "number" then
		LuaLogE("����Ч������ID֮����ID������������������")
		return false;
	end
	RunInfo("����Ч������ID")
	return scmd():IsValidTaskId(task_id)
end

function ����ʣ��ɽ��ͽ���������()
	local res = scmd():GetLeftAcceptableShangJinCntToday()
	RunInfo("����ʣ��ɽ��ͽ�����������������" .. tostring(res))
	return res
end

function ��ȡһ���ɽӵ��ͽ�����ID()
	RunInfo("��ȡһ���ɽӵ��ͽ�����ID")
	local res = scmd():GetAnyAcceptableShangJinTaskId(0)
	return unpack(res)
end

function ��ȡһ���������ͽ�����ID()
	RunInfo("��ȡһ���������ͽ�����ID")
	local res = scmd():GetAnyCanDoShangJinTaskId(0)
	return unpack(res)
end

function ��ȡһ�����ύ���ͽ�����ID()
	RunInfo("��ȡһ�����ύ���ͽ�����ID")
	return scmd():GetAnyCommitableShangJinTaskId()
end

function ��ȡ��������������( task_id )
	if type(task_id) ~= "number" then
		LuaLogE("��ȡ��������������֮����ID������������������")
		return;
	end
	RunInfo("��ȡ��������������")
	return scmd():GetTaskToDstFbName(task_id)
end

function ��ȡ������������ID( task_id )
	if type(task_id) ~= "number" then
		LuaLogE("��ȡ������������ID֮����ID������������������")
		return;
	end
	RunInfo("��ȡ������������ID, ����ID��" .. tostring(task_id))
	return scmd():GetTaskToDstFbId(task_id)
end

function ����ID��ȡ������( fb_id )
	if type(fb_id) ~= "number" then
		LuaLogE("����ID��ȡ������֮����ID������������������")
		return;
	end
	RunInfo("����ID��ȡ������������ID��" .. tostring(fb_id))
	return scmd():GetTheFbNameById(fb_id)
end

function ���ݸ�������ȡ����ID( fb_name )
	if type(fb_name) ~= "string" then
		LuaLogE("���ݸ�������ȡ����ID֮�����������������ַ�������")
		return -1;
	end
	RunInfo("���ݸ�������ȡ����ID����������" .. fb_name)
	return scmd():GetTheFbIdByName(fb_name)
end

function ��ȡ������( task_id )
	if type(task_id) ~= "number" then
		LuaLogE("��ȡ������֮����ID������������������")
		return;
	end
	RunInfo("��ȡ������")
	return scmd():GetTheTaskName(task_id)
end

--[[
��һ����������Ʒ������Ʒ�����������ͣ�����Ϊ�ա�1Ϊ��������2Ϊ�ֿ�����3Ϊװ������4Ϊ�ز���
�ڶ�����������Ʒ�����ַ������ͣ�����Ϊ��
��������������Ʒ�ȼ����������ͣ�����Ϊ��
���ĸ���������ƷҪ��������Ʒ�����������ͣ�����Ϊ�ա�1Ϊ��������2Ϊ�ֿ�����3Ϊװ������4Ϊ�ز���
�����������Ҫ��������Ʒ���ĸ����������������ͣ�����Ϊ�գ�1�ǵ�һ������
]]
function �ƶ���Ʒ( tab_category_src, item_name, tab_category_dst, dst_slot_idx )
	if type(tab_category_src) ~= "number" then
		LuaLogE("�ƶ���Ʒ֮��Ʒ������Ʒ��������������������")
		return false
	end
	if type(item_name) ~= "string" then
		LuaLogE("�ƶ���Ʒ֮Ҫ�ƶ�����Ʒ�������������ַ�������")
		return false
	end
	if type(tab_category_dst) ~= "number" then
		LuaLogE("�ƶ���Ʒ֮��������Ʒ��������������������")
		return false
	end
	if type(dst_slot_idx) ~= "number" then
		LuaLogE("�ƶ���Ʒ֮��������Ʒ����������������������")
		return false
	end
	RunInfo("�ƶ���Ʒ����Ʒ����" .. item_name)
	return scmd():MoveItem(tab_category_src, item_name, tab_category_dst, dst_slot_idx)
end

--[[
�����Ǳ����Ŀո��ӵ��������������ͣ�����Ϊ��
������ʹ�����ճ�������������ĸ��ӣ����Ѷ������Ʒ�ŵ��ֿ���ȥ
]]
function ���һЩ������Ʒ���ֿ�( reserve_cnt )
	if type(reserve_cnt) ~= "number" then
		LuaLogE("���һЩ������Ʒ���ֿ�֮�����Ŀո��ӵ�����������������������")
		return false
	end
	RunInfo("���һЩ������Ʒ���ֿ⣬�����Ŀո��ӵ�������" .. tostring(reserve_cnt))
	return scmd():StoreSomePackageItemsToStore(reserve_cnt)
end

function �Ӳֿ���ȡ��Ʒ( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("�Ӳֿ���ȡ��Ʒ֮��Ʒ�������������ַ�������")
		return false
	end
	RunInfo("�Ӳֿ���ȡ��Ʒ����Ʒ����" .. item_name)
	return scmd():GainItemFromStore(item_name)
end

function ����Ʒ���ֿ�( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("����Ʒ���ֿ�֮��Ʒ�������������ַ�������")
		return false
	end
	RunInfo("����Ʒ���ֿ⣬��Ʒ����" .. item_name)
	return scmd():PackageItemToStore(item_name)
end

--��������Ʒ����֧��ģ������
function �Ӳֿ���ȡһЩ��Ʒ( item_name, cnt )
	if type(item_name) ~= "string" then
		LuaLogE("�Ӳֿ���ȡһЩ��Ʒ֮��Ʒ�������������ַ�������")
		return false
	end
	if type(cnt) ~= "number" then
		cnt = -1
	end
	RunInfo("�Ӳֿ���ȡһЩ��Ʒ����Ʒ����" .. item_name .. " ������" .. tostring(cnt))
	return scmd():GainSomeItemsFromStore(item_name, cnt)
end

function ��Ӵ�ֿ���Ʒ������( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("��Ӵ�ֿ���Ʒ������֮��Ʒ���������ַ�������")
		return
	end
	RunInfo("��Ӵ�ֿ���Ʒ����������Ʒ����" .. item_name)
	return scmd():AddStoreWhiteList(item_name)
end

function ��մ�ֿ���Ʒ������()
	RunInfo("��մ�ֿ���Ʒ������")
	return scmd():ClrStoreWhiteList()
end

--[[
��������Ʒ�����ַ������ͣ�����Ϊ��
]]
function ������Ʒ( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("������Ʒ֮Ҫ�ƶ�����Ʒ�������������ַ�������")
		return false
	end
	RunInfo("������Ʒ����Ʒ����" .. item_name)
	return scmd():WearEquip(item_name)
end

--[[
ֻ����С�ڵ��ڲ���ָ����Ʒ�ʵ�װ��
��������ƷƷ�����ޣ��������ͣ�����Ϊ�գ������Ǵ�1��8֮�䣬���α�ʾ����ɫ����ɫ����õ�졢��ɫ����õ�졢��ɫ���ٻ�ɫ�����ɫ
]]
function �Զ�����һЩװ��( equip_quality_limit, is_auto_gian )
	if type(equip_quality_limit) ~= "number" then
		LuaLogE("������Ʒ֮װ��Ʒ�����޲�����������������")
		return false
	end
	if type(is_auto_gian) ~= "boolean" then
		is_auto_gian = false
	end
	RunInfo("�Զ�����һЩװ����װ��Ʒ�����ޣ�" .. tostring(equip_quality_limit) .. " �Ƿ����Զ�ȥ��ȡװ�����ϣ�" .. tostring(is_auto_gian))
	return scmd():AutoWearSomeEquips(equip_quality_limit, is_auto_gian)
end

function ����Զ�����װ��������( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("����Զ�����װ��������֮��Ʒ�������������ַ�������")
		return false
	end
	RunInfo("����Զ�����װ������������Ʒ����" .. item_name)
	return scmd():AddAutoWearBlackList(item_name)
end

function ����Զ�����װ��������()
	RunInfo("����Զ�����װ��������")
	return scmd():ClrAutoWearBlackList()
end

function ����Զ�����װ��������( item_name, item_type )
	if type(item_name) ~= "string" then
		LuaLogE("����Զ�����װ��������֮װ���������������ַ�������")
		return false
	end
	if type(item_type) ~= "string" then
		LuaLogE("����Զ�����װ��������֮װ�����Ͳ����������ַ�������")
		return false
	end
	RunInfo("����Զ�����װ����������װ������" .. item_name .. " װ�����ͣ�" .. item_type)
	return scmd():AddAutoWearWhiteList(item_name, item_type)
end

function ����Զ�����װ��������()
	RunInfo("����Զ�����װ��������")
	return scmd():ClrAutoWearWhiteList()
end

--[[
������װ���������ţ��������ͣ�����Ϊ�գ���һ��������������1���ֲ�����������2����������
]]
function ����װ��( equip_part_idx )
	if type(equip_part_idx) ~= "number" then
		LuaLogE("����װ��֮װ������������������������")
		return false
	end
	RunInfo("����װ����װ��������" .. tostring(equip_part_idx))
	return scmd():GetOffEquipByIdx(equip_part_idx)
end

function ���뵽�Լ���ׯ԰()
	RunInfo("���뵽�Լ���ׯ԰")
	return scmd():EnterSelfFarm()
end

function ��������ѵ��()
	RunInfo("��������ѵ��")
	return scmd():EnterXinShou()
end

function �뿪ׯ԰()
	RunInfo("�뿪ׯ԰")
	return scmd():LeaveFarm()
end

function ���һ�����е�������()
	local the_name = scmd():GetExistFarmSeedName()
	RunInfo("���һ�����е�����������������" .. the_name)
	return the_name
end

--[[
��һ����������������Ҳ����Ʒ��
�ڶ�����������������֧�ֲ�ҩ��1����ҩ��2����ҩ��3����Ϊ�գ�Ĭ��Ϊ��ҩ��1
]]
function ��ֲ����( seed_name, land_name )
	if type(seed_name) ~= "string" then
		LuaLogE("��ֲ����֮�����������������ַ�������")
		return false
	end
	if land_name == nil then
		land_name = ""
	end
	if type(land_name) ~= "string" then
		LuaLogE("��ֲ����֮�������������������ַ�������")
		return false
	end
	RunInfo("��ֲ���ӣ���������" .. seed_name .. " ��������" .. land_name)
	return scmd():PlantFarmSeed(seed_name, land_name)
end

function ��մ��ʱ�Ĵ���()
	RunInfo("��մ��ʱ�Ĵ���")
	return scmd():ClrHandleAtHitting()
end

--[[
��һ���������ж������ĺ����������棬����Ϊ��ա�������������棬�Ż�ȥִ�еڶ�������
�ڶ������������µĺ������������κ�ֵ������Ϊ��
]]
function ��Ӵ��ʱ�Ĵ���( judge_func, do_func )
	RunInfo("��Ӵ��ʱ�Ĵ���")
	return scmd():AddHandleAtHitting(judge_func, do_func)
end

function ��սű�ֹͣʱ�Ĵ���()
	RunInfo("��սű�ֹͣʱ�Ĵ���")
	return scmd():ClrHandlersAtScriptStoped()
end

function ��ӽű�ֹͣʱ�Ĵ���( func )
	RunInfo("��ӽű�ֹͣʱ�Ĵ���")
	return scmd():AddHandlersAtScriptStoped(func)
end

function ��ȡ��ɫ��ǰѪֵ()
	local res = scmd():GetRoleCurHp()
	RunInfo("��ȡ��ɫ��ǰѪֵ��" .. tostring(res))
	return res
end

--��һ�������Ǵ�ׯ�����ڶ��������������NPC��
function ���������ʼ�( village_name, npc_name )
	if type(village_name) ~= "string" then
		LuaLogE("���������ʼ�֮��ׯ�������������ַ�������")
		return 0
	end
	if type(npc_name) ~= "string" then
		LuaLogE("���������ʼ�֮NPC�������������ַ�������")
		return 0
	end
	RunInfo("���������ʼ�, ��ׯ����" .. village_name .. " NPC����" .. npc_name)
	return scmd():HandleAllMails(village_name, npc_name)
end

--��һ�������Ǹ�������������{ { "����֮��", 1 }, { "��ʯ", 10, �� }, { "һ����֮��", -1 } }��
--��������1��ʾ�ʼĹ���֮�������Ϊ1��-1��ʾ�ʼ�����һ����֮�����л�ʯ��һ������������Ǹ��������ͣ��ɲ�����Ϊ�٣�Ϊ���ʾ��ʯ�ﵽ��10���Ż�ȥ�ʼġ�
--�ڶ���������Ҫ�ʼĵĽ�ң��������ͣ�����Ϊ�գ�Ϊ0��ʾ���ʼĽ�ң������-100����ʾ����100��ң�����ȫ���ʼ�
--�����������ǽ����ʼ��Ľ�ɫ��
--���ĸ������Ǵ�ׯ��
--�����������NPC�������ʼ�NPC������
function �����ʼ�( tbl_items, gold, target_role_name, village_name, npc_name )
	if type(gold) ~= "number" then
		LuaLogE("�����ʼ�֮��Ҳ�����������������")
		return -1
	end
	if type(target_role_name) ~= "string" then
		LuaLogE("�����ʼ�֮��ɫ�������������ַ�������")
		return -1
	end
	if type(village_name) ~= "string" then
		LuaLogE("�����ʼ�֮��ׯ�������������ַ�������")
		return -1
	end
	if type(npc_name) ~= "string" then
		LuaLogE("�����ʼ�֮NPC�������������ַ�������")
		return -1
	end
	RunInfo("�����ʼ�, ��ң�" .. tostring(gold) .. " ��ɫ����" .. target_role_name)
	return scmd():SendMail(tbl_items, gold, target_role_name, village_name, npc_name)
end

--�ʼ�������Ʒ �� �����ʼ� �������ƣ�����������������ĸ���������һ��
--��һ��������ָ���ʼ��������������ͣ�����Ϊ�ա�����Ʒ�������ﵽָ���ʼ����������ȥ�ʼġ�
function �ʼ�������Ʒ(item_reach_cnt, gold, target_role_name, village_name, npc_name)
	if type(item_reach_cnt) ~= "number" then
		LuaLogE("�ʼ�������Ʒָ֮���ʼ�����������������������")
		return -1
	end
	if type(gold) ~= "number" then
		LuaLogE("�ʼ�������Ʒ֮��Ҳ�����������������")
		return -1
	end
	if type(target_role_name) ~= "string" then
		LuaLogE("�ʼ�������Ʒ֮��ɫ�������������ַ�������")
		return -1
	end
	if type(village_name) ~= "string" then
		LuaLogE("�ʼ�������Ʒ֮��ׯ�������������ַ�������")
		return -1
	end
	if type(npc_name) ~= "string" then
		LuaLogE("�ʼ�������Ʒ֮NPC�������������ַ�������")
		return -1
	end
	RunInfo("�ʼ�������Ʒ, ָ���ʼ�������" .. tostring(item_reach_cnt) .. " ��ң�" .. tostring(gold) .. " ��ɫ����" .. target_role_name)
	return scmd():SendAnyMail(item_reach_cnt, gold, target_role_name, village_name, npc_name)
end

--[[
��һ�������ǲɼ�����������1��6�����ǿ󳡡����������ܵء�����ľ�����䷿����ҩ��
�ڶ��������ǵȼ����ޣ���Ϊ�գ���ʾ������
]]
function ����ׯ԰�ɼ�( collect_obj_name, lvl_limit, is_open_npc )
	if type(collect_obj_name) ~= "string" then
		LuaLogE("����ׯ԰�ɼ�֮�ɼ����������ַ�������")
		return 0
	end
	if lvl_limit == nil then
		lvl_limit = -1;
	end
	if type(lvl_limit) ~= "number" then
		LuaLogE("����ׯ԰�ɼ�֮�ȼ����ޱ�������������")
		return 0
	end
	if type(is_open_npc) ~= "boolean" then
		is_open_npc = true
	end
	RunInfo("����ׯ԰�ɼ����ɼ�����" .. collect_obj_name .. " �ȼ�����:" .. tostring(lvl_limit))
	return scmd():LvlUpCollectOfFarm(collect_obj_name, lvl_limit, is_open_npc)
end

--�����ǲɼ������ַ������ͣ���Ϊ�գ���ʾ��̵Ĳɼ�ʱ�䣬֧�ֵ����ƣ��󳡡����������ܵء�����ľ�����䷿����ҩ��1����ҩ��2����ҩ��3
function ����ׯ԰�ɼ���ʱ��( collect_name )
	if type(collect_name) ~= "string" then
		collect_name = ""
	end
	RunInfo("����ׯ԰�ɼ���ʱ�䣬�ɼ�����" .. collect_name)
	return scmd():IsTimeToCollectFarm(collect_name)
end

function ѡ��ָ�����ֵĽ�ɫ( role_name )
	if type(role_name) ~= "string" then
		LuaLogE("ѡ��ָ�����ֵĽ�ɫ֮��ɫ�������������ַ�������")
		return false
	end
	RunInfo("ѡ��ָ�����ֵĽ�ɫ����ɫ����" .. role_name)
	return scmd():SelectRoleByName(role_name)
end

function ѡ��ָ���Ľ�ɫ( role_idx )
	if type(role_idx) ~= "number" then
		LuaLogE("ѡ��ָ���Ľ�ɫ֮��ɫ����������������������")
		return false
	end
	RunInfo("ѡ��ָ���Ľ�ɫ����ɫ������" .. tostring(role_idx))
	return scmd():SeletRoleByIdx(role_idx)
end

function �ȴ���ѡ���ɫ( wait_time )
	if type(wait_time) ~= "number" then
		LuaLogE("�ȴ���ѡ���ɫ֮�ȴ�ʱ���������������")
		return false
	end
	RunInfo("�ȴ���ѡ���ɫ���ȴ�ʱ�䣺" .. tostring(wait_time))
	return scmd():WaitForSelectableRole(wait_time)
end

function �Զ�������ɫ()
	RunInfo("�Զ�������ɫ")
	return scmd():AutoCreateRole()
end

function �Զ�������ѡ���ɫ()
	RunInfo("�Զ�������ѡ���ɫ")
	return scmd():AutoCreateOrSelectRole()
end

function ���õ�ǰҪɾ���Ľ�ɫ����( role_idx )
	if type(role_idx) ~= "number" then
		LuaLogE("���õ�ǰҪɾ���Ľ�ɫ����֮��ɫ����������������������")
		return false
	end
	RunInfo("���õ�ǰҪɾ���Ľ�ɫ��������ɫ������" .. tostring(role_idx))
	return scmd():SetCurDeleteRoleIdx(role_idx)
end

function �õ���ǰ��ɫ�Ľ�ɫ�б�����()
	local res = scmd():GetCurRoleIdxAtRoleList()
	RunInfo("�õ���ǰ��ɫ�Ľ�ɫ�б�����:" .. tostring(res))
	return res
end

function �õ���ǰҪɾ���Ľ�ɫ����()
	local res = scmd():GetCurDeleteRoleIdx()
	RunInfo("�õ���ǰҪɾ���Ľ�ɫ����:" .. tostring(res))
	return res
end

function ����ɾ����ɫ( change_ac_at_delete_one_role )
	if type(change_ac_at_delete_one_role) ~= "boolean" then
		change_ac_at_delete_one_role = true
	end
	RunInfo("����ɾ����ɫ���Ƿ���ɾ��ÿ����ɫ��ʱ�򻻺ţ�" .. tostring(change_ac_at_delete_one_role))
	return scmd():DoDeleteRole(change_ac_at_delete_one_role)
end

function ��ѡ���ɫ����()
	RunInfo("��ѡ���ɫ����")
	return scmd():IsAtSelectRole()
end

function �ѽ��뵽��Ϸ()
	RunInfo("�ѽ��뵽��Ϸ")
	return scmd():IsAtInGame()
end

function ����ɫ()
	RunInfo("����ɫ")
	return scmd():ChangeRole()
end

function ����( str )
	if type(str) ~= "string" then
		str = ""
	end
	RunInfo("���ţ�" .. str)
	return scmd():ChangeGameAc(str)
end

function ��Ҫ������ɫ()
	RunInfo("��Ҫ������ɫ")
	return scmd():NeedCreateRole()
end

function ��ȡ��ɫ����()
	RunInfo("��ȡ��ɫ����")
	return scmd():GetRoleCnt()
end

--[[
��һ�������Ǿ��������ַ������ͣ�����Ϊ��
�ڶ��������ǵȴ�ʱ�䣬�������ͣ�����Ϊ��
]]

function �ȴ�ָ���ľ���( str_ju_qing, wait_time )
	if type(str_ju_qing) ~= "string" then
		LuaLogE("�ȴ�ָ���ľ���֮�����������������ַ�������")
		return false
	end
	if type(wait_time) ~= "number" then
		LuaLogE("�ȴ�ָ���ľ���֮�ȴ�ʱ�������������������")
		return false
	end
	RunInfo("�ȴ�ָ���ľ��飬��������" .. str_ju_qing .. "  �ȴ�ʱ�䣺" .. tostring(wait_time))
	return scmd():WaitForTheJuQing(str_ju_qing, wait_time)
end

function ����ָ�����ֵľ�ֹ����( obj_name )
	if type(obj_name) ~= "string" then
		LuaLogE("����ָ�����ֵľ�ֹ����֮�������������ַ�������")
		return 0
	end
	return scmd():StepOverTheStaticObjs(obj_name)
end

function ��������Ķ���()
	RunInfo("��������Ķ���")
	return ����ָ�����ֵľ�ֹ����("Bug_SFX_")
end

function �����ֹ������Ϣ( obj_name )
	if type(obj_name) ~= "string" then
		LuaLogE("�����ֹ������Ϣ֮�������������ַ�������")
		return 0
	end
	RunInfo("�����ֹ������Ϣ����������" .. obj_name)
	return scmd():DebugInfoStaticObjs(obj_name)
end

function �����ֹ�ɴ�Ķ�����Ϣ()
	RunInfo("�����ֹ�ɴ�Ķ�����Ϣ")
	return scmd():DebugInfoStaticBeatableObjs()
end

function �Զ�ȥ��ָ���Ĺ���ί��( task_lvl, task_name, do_func )
	if type(task_lvl) ~= "string" then
		LuaLogE("�Զ�ȥ��ָ���Ĺ���ί��֮����ȼ��������ַ�������")
		return 0
	end
	if type(task_name) ~= "string" then
		LuaLogE("�Զ�ȥ��ָ���Ĺ���ί��֮�������������ַ�������")
		return 0
	end
	RunInfo("�Զ�ȥ��ָ���Ĺ���ί�У�����ȼ���" .. task_lvl .. "  ��������" .. task_name)
	if scmd():AutoToDoTheSociatyTask(task_lvl, task_name, do_func) then
		return 1
	end
	return 0
end

--[[
��һ����������Ʒ�����ַ������ͣ�����Ϊ��
�ڶ���������Ҫ��������Ʒ�������������ͣ�����Ϊ��
���������������ļۣ��������ͣ�����Ϊ��
���ĸ�������һ�ڼۣ��������ͣ�����Ϊ��
������������һ�ڼۣ��������ͣ�����Ϊ�ա��ο�ǰ5(���߸�����)�����һ�ڼ۵�ƽ���ۣ����˲���Ϊ��������ʾ��ƽ���۵Ļ����ϼӣ������ʾ��ƽ���۵Ļ����ϼ���
�������������һ�ڼۣ��������ͣ�����Ϊ�ա�ͨ����5���������������һ�ڼۣ�����С��������һ�ڼۣ�����һ�ڼ۰���4�������趨��
���߸�������ƽ����ȡֵ��Ĭ��Ϊ5����ʾȡǰ5����ͼ۵�ƽ��ֵ����Ϊ�գ���಻����һ������ҳ���������
�ڰ˸�������ֱ�����ļۣ��������ͣ���Ϊ�գ�Ĭ��Ϊ�棬��ʾ����������(���ļ�)�������ֵ���������ɹ�������ļ۾�Ϊ���١����ò���Ϊ�٣������������ĺ���Ϊ������ļۣ�����һ����1��100֮�����ֵ����ʾ�����һ�ڼ۵İٷֱȡ��������������Ϊ80����ʾ���ļ۰�һ�ڼ۵İٷ�֮��ʮ�����㡣
���Ǹ���Ʒ��û��������������ô��5��6��7�������������á�
]]
function ������( item_name, item_cnt, begin_price, smart_price, relative_smart_price, min_smart_price, average_cnt, begin_price_direct )
	if type(item_name) ~= "string" then
		LuaLogE("������֮��Ʒ�������������ַ�������");
		return false
	end
	if type(item_cnt) ~= "number" then
		LuaLogE("������֮Ҫ��������Ʒ����������������������");
		return false
	end
	if type(begin_price) ~= "number" then
		LuaLogE("������֮���ļ۲�����������������");
		return false
	end
	if type(smart_price) ~= "number" then
		LuaLogE("������֮һ�ڼ۲�����������������");
		return false
	end
	if type(relative_smart_price) ~= "number" then
		LuaLogE("������֮���һ�ڼ۲�����������������");
		return false
	end
	if type(min_smart_price) ~= "number" then
		LuaLogE("������֮���һ�ڼ۲�����������������");
		return false
	end
	if type(average_cnt) ~= "number" then
		average_cnt = 5
	end
	if type(begin_price_direct) ~= "boolean" then
		begin_price_direct = true
	end
	RunInfo("����������Ʒ����" .. item_name .. " ��Ʒ������" .. tostring(item_cnt) .. " ���ļۣ�" .. tostring(begin_price) ..
		" һ�ڼۣ�" .. tostring(smart_price) .. " ���һ�ڼۣ�" .. tostring(relative_smart_price) .. " ���һ�ڼۣ�" .. tostring(min_smart_price)
		.. " ƽ����ȡֵ��" .. tostring(average_cnt) .. " �Ƿ�Ϊֱ�����ļۣ�" .. tostring(begin_price_direct))
	return scmd():SellToAuction(item_name, item_cnt, begin_price, smart_price, relative_smart_price, min_smart_price, average_cnt, begin_price_direct)
end

--[[
��һ����������Ʒ�����ַ������ͣ�����Ϊ��
�ڶ���������Ҫ��������Ʒ�������������ͣ�����Ϊ��
���������������ļۣ��������ͣ�����Ϊ��
���ĸ�������һ�ڼۣ��������ͣ�����Ϊ��
]]
function ���������Է���( item_name, item_cnt, begin_price, smart_price )
	if type(item_name) ~= "string" then
		LuaLogE("���������Է���֮��Ʒ�������������ַ�������");
		return false
	end
	if type(item_cnt) ~= "number" then
		LuaLogE("���������Է���֮Ҫ��������Ʒ����������������������");
		return false
	end
	if type(begin_price) ~= "number" then
		LuaLogE("���������Է���֮���ļ۲�����������������");
		return false
	end
	if type(smart_price) ~= "number" then
		LuaLogE("���������Է���֮һ�ڼ۲�����������������");
		return false
	end
	RunInfo("���������Է��ţ���Ʒ����" .. item_name .. " ��Ʒ������" .. tostring(item_cnt) .. " ���ļۣ�" .. tostring(begin_price) .. " һ�ڼۣ�" .. tostring(smart_price))
	return scmd():SellToOtherSide(item_name, item_cnt, begin_price, smart_price)
end

--[[
��һ����������Ʒ������ʾҪ�������Ʒ���ַ������ͣ�����Ϊ��
�ڶ��������ǲ�ѯҳ�����������ͣ�����Ϊ�ա������Ʒ����ҳ��Ϊ10����ѯҳ��Ϊ3����ʾ��1��3��ҳ����Ʒ�в��Ҹ���Ʒ�������ѯҳ��Ϊ-3����ʾ��7��10��ҳ����Ʒ�в��Ҹ���Ʒ��
�����������������ˣ��ַ������ͣ���Ϊ�գ�Ϊ��ʱ��ʾ�κ������ߣ���Ϊ��ʱ����ʾֻ��ָ�����ֵ������˵���Ʒ
���ĸ������Ǽ۸����ޣ��������ͣ�����Ϊ�գ���ʾ�����ҵ�����Ʒ�������۸�С�ڵȼ��ü۸����ޣ��ŻṺ�����Ʒ
����������ǹ�����������ʾ�����������������������Ʒ�����������������Ϊ2����ʾҪ�������������ֵ���Ʒ
]]
function һ�ڼ۹���( item_name, search_page_cnt, seller, price_limit, buy_cnt )
	if type(item_name) ~= "string" then
		LuaLogE("һ�ڼ۹���֮��Ʒ�������������ַ�������");
		return 0
	end
	if type(search_page_cnt) ~= "number" then
		LuaLogE("һ�ڼ۹���֮��ѯҳ��������������������");
		return 0
	end
	if seller == nil then
		seller = ""
	end
	if type(seller) ~= "string" then
		LuaLogE("һ�ڼ۹���֮�����˲����������ַ�������");
		return 0
	end
	if type(price_limit) ~= "number" then
		LuaLogE("һ�ڼ۹���֮�۸����޲�����������������");
		return 0
	end
	if type(buy_cnt) ~= "number" then
		LuaLogE("һ�ڼ۹���֮��������������������������");
		return 0
	end
	RunInfo("һ�ڼ۹�����Ʒ����" .. item_name .. " ��ѯҳ����" .. tostring(search_page_cnt) .. " �����ߣ�" .. seller .. " �۸����ޣ�" .. tostring(price_limit) .. " ����������" .. tostring(buy_cnt))
	return scmd():SmartBuy(item_name, search_page_cnt, seller, price_limit, buy_cnt)
end

function ����һЩ�Է���Ӫ��������Ʒ()
	RunInfo("����һЩ�Է���Ӫ��������Ʒ")
	return scmd():SmartBuyOtherSide()
end

--[[
����Ϊ��Ʒ�����ַ������ͣ�����Ϊ��
]]
function ��ѯ��������Ŀ��( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("��ѯ��������Ŀ��֮��Ʒ������Ϊ�ַ�������")
		return 0;
	end
	local cnt = scmd():QuerySoldCnt(item_name)
	RunInfo("��ѯ��������Ŀ������Ʒ����" .. item_name .. " ���ؽ����" .. tostring(cnt))
	return cnt;
end

--[[
�����ں������еģ���һ���ᱻ���������������ڲ��������е���Ʒ
��һ�������Ǳ����Ŀո��ӵı����������������ͣ�����Ϊ��
�ڶ��������ǲֿ�Ŀո��ӵı����������������ͣ�����Ϊ��
�����������ǳ��������ַ������ͣ�����Ϊ��
���ĸ�������NPC�����ַ������ͣ�����Ϊ�ա�������Ʒ�ͻ�����ָ��������ָ��NPC��
]]
function �����ֿ�ͱ�����������Ʒ( packet_reserve_cnt, stored_reserve_cnt, village_name, npc_name )
	if type(packet_reserve_cnt) ~= "number" then
		LuaLogE("�����ֿ�ͱ�����������Ʒ֮�����Ŀ��б�������������������������")
		return 0;
	end
	if type(stored_reserve_cnt) ~= "number" then
		LuaLogE("�����ֿ�ͱ�����������Ʒ֮�ֿ�Ŀ��б�������������������������")
		return 0;
	end
	if village_name == nil then
		village_name = ""
	end
	if type(village_name) ~= "string" then
		LuaLogE("�����ֿ�ͱ�����������Ʒ֮�����������������ַ�������")
		return 0;
	end
	if type(npc_name) ~= "string" then
		LuaLogE("�����ֿ�ͱ�����������Ʒ֮NPC�������������ַ�������")
		return 0;
	end
	RunInfo("�����ֿ�ͱ�����������Ʒ���������б���������" .. tostring(packet_reserve_cnt) .. " �ֿ���б���������" .. tostring(stored_reserve_cnt))
	return scmd():SellStored_PacketRubbishItems(packet_reserve_cnt, stored_reserve_cnt, village_name, npc_name);
end

--[[
�����Ǻ�������
]]
function �������̵���Ʒ���˺�����( item_func )
	if type(item_func) ~= "function" then
		LuaLogE("�������̵���Ʒ���˺�����֮��������Ϊ��������")
		return;
	end
	RunInfo("�������̵���Ʒ���˺�����")
	return scmd():SetItemFilterBlackList(item_func);
end

--[[
�����Ǻ�������
]]
function �������̵���Ʒ���˰�����( item_func )
	if type(item_func) ~= "function" then
		LuaLogE("�������̵���Ʒ���˰�����֮��������Ϊ��������")
		return;
	end
	RunInfo("�������̵���Ʒ���˰�����")
	return scmd():SetItemFilterWhiteList(item_func);
end

--[[
��������Ʒ�����ַ������ͣ�����Ϊ��
]]
function ������̵���Ʒ��������( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("������̵���Ʒ��������֮��������Ϊ��������")
		return;
	end
	RunInfo("������̵���Ʒ������������Ʒ����" .. item_name)
	return scmd():AddItemNameBlackList(item_name);
end

function ������̵���Ʒ��������()
	RunInfo("������̵���Ʒ��������")
	return scmd():ClrItemNameBlackList()
end

--[[
��������Ʒ�����ַ������ͣ�����Ϊ��
]]
function ������̵���Ʒ��������( item_name )
	if type(item_name) ~= "string" then
		LuaLogE("������̵���Ʒ��������֮��������Ϊ��������")
		return;
	end
	RunInfo("������̵���Ʒ������������Ʒ����" .. item_name)
	return scmd():AddItemNameWhiteList(item_name);
end

function ������̵���Ʒ��������()
	RunInfo("������̵���Ʒ��������")
	return scmd():ClrItemNameWhiteList()
end

--[[
���˺������е���Ʒ��������Ʒ�ȼ�����ƷƷ���ܹ�ͬʱ���ϵģ�������ӵ���������
������һ����Ʒ����Ʒ�ȼ�=20����ƷƷ��Ϊ3(���м���Ʒ)����� 20���ڵȼ���һ����������3���ڵȼ��ڶ�����������Ѹ���Ʒ��ӵ���������
��һ����������Ʒ�ȼ����������ͣ�����Ϊ��
�ڶ�����������ƷƷ�ʣ��������ͣ�����Ϊ�գ������Ǵ�1��8֮�䣬���α�ʾ����ɫ����ɫ����õ�졢��ɫ����õ�졢��ɫ���ٻ�ɫ�����ɫ
]]
function �������̵���Ʒ��Ϣ������( item_lvl, item_quality )
	if type(item_lvl) ~= "number" then
		LuaLogE("�������̵���Ʒ��Ϣ������֮��Ʒ�ȼ���������Ϊ��������")
		return;
	end
	if type(item_quality) ~= "number" then
		LuaLogE("�������̵���Ʒ��Ϣ������֮��ƷƷ�ʲ�������Ϊ��������")
		return;
	end
	RunInfo("�������̵���Ʒ��Ϣ����������Ʒ�ȼ���" .. tostring(item_lvl) .. " ��ƷƷ��:" .. tostring(item_quality))
	return scmd():SetItemInfoWhiteList(item_lvl, item_quality);
end

--[[
��ǰ��ƷΪ���ϣ����������ôһ����������Ʒ������Ʒ�ȼ�����ƷƷ���ܹ�ͬʱ���϶�Ӧ�����ģ��ͻ���ӵ���������
��һ����������Ʒ�ȼ����������ͣ�����Ϊ��
�ڶ�����������ƷƷ�ʣ��������ͣ�����Ϊ�գ������Ǵ�1��8֮�䣬���α�ʾ����ɫ����ɫ����õ�졢��ɫ����õ�졢��ɫ���ٻ�ɫ�����ɫ
]]
function �������̵������Ʒ������( item_lvl, item_quality )
	if type(item_lvl) ~= "number" then
		LuaLogE("�������̵������Ʒ������֮��Ʒ�ȼ���������Ϊ��������")
		return;
	end
	if type(item_quality) ~= "number" then
		LuaLogE("�������̵������Ʒ������֮��ƷƷ�ʲ�������Ϊ��������")
		return;
	end
	RunInfo("�������̵������Ʒ����������Ʒ�ȼ���" .. tostring(item_lvl) .. " ��ƷƷ��:" .. tostring(item_quality))
	return scmd():SetCraftItemWhiteList(item_lvl, item_quality);
end

--[[
��ǰ��ƷΪ���ϣ����������ôһ�����������Ʒ������Ʒ�ȼ�����ƷƷ���ܹ�ͬʱ���϶�Ӧ�����ģ��ͻ���ӵ���������
��һ����������Ʒ�ȼ����������ͣ�����Ϊ��
�ڶ�����������ƷƷ�ʣ��������ͣ�����Ϊ�գ������Ǵ�1��8֮�䣬���α�ʾ����ɫ����ɫ����õ�졢��ɫ����õ�졢��ɫ���ٻ�ɫ�����ɫ
]]
function �������̵�����װ��������( item_lvl, item_quality )
	if type(item_lvl) ~= "number" then
		LuaLogE("�������̵�����װ��������֮��Ʒ�ȼ���������Ϊ��������")
		return;
	end
	if type(item_quality) ~= "number" then
		LuaLogE("�������̵�����װ��������֮��ƷƷ�ʲ�������Ϊ��������")
		return;
	end
	RunInfo("�������̵�����װ������������Ʒ�ȼ���" .. tostring(item_lvl) .. " ��ƷƷ��:" .. tostring(item_quality))
	return scmd():SetLvlUpEquipWhiteList(item_lvl, item_quality);
end

--[[
��ǰ��ƷΪ���ϣ����������ôһ�����ͺ����Ʒ������Ʒ�ȼ�����ƷƷ���ܹ�ͬʱ���϶�Ӧ�����ģ��ͻ���ӵ���������
��һ����������Ʒ�ȼ����������ͣ�����Ϊ��
�ڶ�����������ƷƷ�ʣ��������ͣ�����Ϊ�գ������Ǵ�1��8֮�䣬���α�ʾ����ɫ����ɫ����õ�졢��ɫ����õ�졢��ɫ���ٻ�ɫ�����ɫ
]]
function �������̵���Ͱ�����( item_lvl, item_quality )
	if type(item_lvl) ~= "number" then
		LuaLogE("�������̵���Ͱ�����֮��Ʒ�ȼ���������Ϊ��������")
		return;
	end
	if type(item_quality) ~= "number" then
		LuaLogE("�������̵���Ͱ�����֮��ƷƷ�ʲ�������Ϊ��������")
		return;
	end
	RunInfo("�������̵���Ͱ���������Ʒ�ȼ���" .. tostring(item_lvl) .. " ��ƷƷ��:" .. tostring(item_quality))
	return scmd():SetFactureWhiteList(item_lvl, item_quality);
end

function �ȴ���ɫ�����ƶ�( wait_time )
	if type(wait_time) ~= "number" then
		LuaLogE("�ȴ���ɫ�����ƶ�֮�ȴ�ʱ���������Ϊ��������")
		return false;
	end
	RunInfo("�ȴ���ɫ�����ƶ����ȴ�ʱ�䣺" .. tostring(wait_time))
	return scmd():WaitRoleCanMove(wait_time)
end

function ���ý�ɫ����( x, y, z )
	if type(x) ~= "number" then
		LuaLogE("���ý�ɫ����֮��һ��������X�������Ϊ��������")
		return;
	end
	if type(y) ~= "number" then
		LuaLogE("���ý�ɫ����֮�ڶ���������Y�������Ϊ��������")
		return;
	end
	if type(z) ~= "number" then
		LuaLogE("���ý�ɫ����֮������������Z�������Ϊ��������")
		return;
	end
	RunInfo("���ý�ɫ���꣬x��" .. tostring(x) .. " y:" .. tostring(y) .. " z:" .. tostring(z))
	return scmd():SetRoleToPos(x, y, z)
end

function ���õ�Ŀ�����ĳ���( x, y, z )
	if type(x) ~= "number" then
		LuaLogE("���õ�Ŀ�����ĳ���֮��һ��������X�������Ϊ��������")
		return;
	end
	if type(y) ~= "number" then
		LuaLogE("���õ�Ŀ�����ĳ���֮�ڶ���������Y�������Ϊ��������")
		return;
	end
	if type(z) ~= "number" then
		LuaLogE("���õ�Ŀ�����ĳ���֮������������Z�������Ϊ��������")
		return;
	end
	RunInfo("���õ�Ŀ�����ĳ���x��" .. tostring(x) .. " y:" .. tostring(y) .. " z:" .. tostring(z))
	return scmd():SetDirFromDstObj(x, y, z)
end

function ���´����Ľ�ɫ()
	RunInfo("���´����Ľ�ɫ")
	return scmd():IsTheNewRole()
end

function ʣ�൥������()
	local res = scmd():G_GetLeftSingleExp();
	RunInfo("ʣ�൥�����飬���أ�" .. tostring(res))
	return res
end

function ʣ��˫������()
	local res = scmd():G_GetLeftDoubleExp();
	RunInfo("ʣ��˫�����飬���أ�" .. tostring(res))
	return res;
end

function ����_��������()
	RunInfo("����_��������")
	return scmd():ZuoReQiQiu();
end

function ��ȡ���ʵȼ��ĸ�����()
	local fb_name = scmd():FindSuitableFbName()
	RunInfo("��ȡ���ʵȼ��ĸ���������������" .. fb_name)
	return fb_name
end

function ������״̬()
	RunInfo("������״̬")
	return scmd():IsHotStatus()
end

function �ں���״̬()
	RunInfo("�ں���״̬")
	return scmd():IsColdStatus()
end

function ���ж�״̬()
	RunInfo("���ж�״̬")
	return scmd():IsPoisoningStatus()
end

function ���ý��븱����Ĵ���( func )
	RunInfo("���ý��븱����Ĵ���")
	return scmd():SetAfterEnteredFb(func)
end

function ��Ҫĥ��()
	RunInfo("��Ҫĥ��")
	return scmd():NeedMoDao()
end

function ��ɫ�ȼ�()
	local res = scmd():GetRoleLvl()
	RunInfo("��ɫ�ȼ�,���أ�" .. tostring(res))
	return res
end

--��һ����������������֧��ģ��ƥ�䣩���ַ������ͣ�����Ϊ��
--�ڶ����������ͽ�������Ѷȵȼ�����Ϊ�գ���ʾ�κ��Ѷȵȼ���֧�֣���������ս
function ����ͽ����������( task_name, �Ѷȵȼ� )
	if type(task_name) ~= "string" then
		LuaLogE("����ͽ����������֮��������������Ϊ�ַ�������")
		return;
	end
	if type(�Ѷȵȼ�) ~= "string" then
		�Ѷȵȼ� = ""
	end
	RunInfo("����ͽ��������������������" .. task_name .. " �Ѷȵȼ���" .. �Ѷȵȼ�)
	return scmd():AddShangJinWhiteList(task_name, �Ѷȵȼ�)
end

function ����ͽ����������()
	RunInfo("����ͽ����������")
	return scmd():ClrShangJinWhiteList()
end

function ����ͽ�Ŀ�긱��������( fb_id )
	if type(fb_id) ~= "number" then
		LuaLogE("����ͽ�Ŀ�긱��������֮����ID��������Ϊ��������")
		return;
	end
	RunInfo("����ͽ�Ŀ�긱��������������ID��" .. tostring(fb_id))
	return scmd():AddShangJinDstFbBlackList(fb_id)
end

function ����ͽ�Ŀ�긱��������()
	RunInfo("����ͽ�Ŀ�긱��������")
	return scmd():ClrShangJinDstFbBlackList()
end

function ����ͽ�Ŀ�긱���̶�������( fb_name )
	if type(fb_name) ~= "string" then
		LuaLogE("����ͽ�Ŀ�긱���̶�������֮��������������Ϊ�ַ�������")
		return;
	end
	RunInfo("����ͽ�Ŀ�긱���̶�����������������" .. fb_name)
	return scmd():AddShangJinDstFbStableBlackList(fb_name)
end

function ����ͽ�Ŀ�긱���̶�������()
	RunInfo("����ͽ�Ŀ�긱���̶�������")
	return scmd():ClrShangJinDstFbStableBlackList()
end

function ʣ������ȯ()
	local res = scmd():LeftShouLieQuanCnt()
	RunInfo("ʣ������ȯ�����أ�" .. tostring(res))
	return res
end

--���Ƿ���-1����ʾ��ǰ�ĸ�������ģʽ����Ч��ԭ���������������ȯ��û���㹻������
--�˺��������жϻ���ɫ
function �õ���ǰ��Ч�ĸ�������ģʽ()
	local res = scmd():GetCurFbValidConsumeMode()
	RunInfo("�õ���ǰ��Ч�ĸ�������ģʽ�����أ�" .. tostring(res))
	return res
end

function ����ƣ��ֵ( data )
	if type(data) ~= "number" then
		data = 0
	end
	RunInfo("����ƣ��ֵ��" .. tostring(data))
	return scmd():SetFatigueData(data)
end

function �ַ���Ϊ��( str )
	if type(str) ~= "string" then
		RunInfo("�ַ���Ϊ��")
		return true
	end
	RunInfo("�ַ���Ϊ�գ��ַ�����" .. str)
	return IsStringEmpty(str)
end

function �ݻپ�̬�ɴ�Ĺ���( obj_name, every_hit_cnt, obj_cnt, delay_time )
	if type(obj_name) ~= "string" then
		LuaLogE("�ݻپ�̬�ɴ�Ĺ���֮�������������ַ�������")
		return 0
	end
	if type(every_hit_cnt) ~= "number" then
		every_hit_cnt = 1
	end
	if type(obj_cnt) ~= "number" then
		obj_cnt = -1
	end
	if type(delay_time) ~= "number" then
		obj_cnt = 700
	end
	RunInfo("�ݻپ�̬�ɴ�Ĺ����������" .. obj_name .. " ÿ�δ��������" .. tostring(every_hit_cnt) .. " ������" .. tostring(obj_cnt))
	return scmd():DestoryStaticBeatableMonster(obj_name, every_hit_cnt, obj_cnt, delay_time)
end

function �Զ���ȡ���()
	RunInfo("�Զ���ȡ���")
	return scmd():AutoGainGiftBag()
end

function ���õ�ǰBOSS�Ĺ�����λ( part_name )
	if type(part_name) ~= "string" then
		LuaLogE("���õ�ǰBOSS�Ĺ�����λ֮��λ����������Ϊ�ַ�������")
		return;
	end
	RunInfo("���õ�ǰBOSS�Ĺ�����λ����λ����" .. part_name)
	return scmd():SetCurBossHitBodyPart(part_name)
end

function ���֧�ֵĹ��ﲿλ��Ϣ()
	RunInfo("���֧�ֵĹ��ﲿλ��Ϣ")
	return scmd():DebuInfo_AllBodyPart()
end

----------------------------------------------
--��һ�������ǲ��������ַ������ͣ�����Ϊ��
--�ڶ��������ǲ��ϻ�ȡ���������������ͣ�����Ϊ��
--��������������������������ݸ���ȡ������
function ��Ӳ��ϻ�ȡӳ��( material_name, gain_func, ... )
	if type(material_name) ~= "string" then
		LuaLogE("��Ӳ��ϻ�ȡӳ��֮�����������������ַ�������")
		return false
	end
	if type(gain_func) ~= "function" then
		LuaLogE("��Ӳ��ϻ�ȡӳ��֮��ȡ�������������Ǻ�������")
		return false
	end
	RunInfo("��Ӳ��ϻ�ȡӳ�䣬��������" .. material_name)
	return MM_AddItem(material_name, gain_func, ...)
end

function ��ղ��ϻ�ȡӳ��()
	RunInfo("��ղ��ϻ�ȡӳ��")
	return MM_Clear()
end

function ����ָ���Ĳ��ϻ�ȡӳ��( material_name )
	if type(material_name) ~= "string" then
		LuaLogE("����ָ���Ĳ��ϻ�ȡӳ��֮�����������������ַ�������")
		return false
	end
	RunInfo("����ָ���Ĳ��ϻ�ȡӳ��")
	return MM_ExistTheItem(material_name)
end

--��һ�������ǲ�����
--�ڶ��������ǲ����������ޣ������ӵ�еĲ����������ڵ��ڸ�������ȥ��ȡ�ò����ˣ���Ϊ�գ���ʾ������
function ȥ��ȡָ���Ĳ���( material_name, cnt_limit )
	if type(material_name) ~= "string" then
		LuaLogE("ȥ��ȡָ���Ĳ���֮�����������������ַ�������")
		return false
	end
	if type(cnt_limit) ~= "number" then
		cnt_limit = -1
	end
	RunInfo("ȥ��ȡָ���Ĳ��ϣ���������" .. material_name .. " �����������ޣ�" .. tostring(cnt_limit))
	return scmd():MM_DoGainTheMaterial(material_name, cnt_limit)
end
----------------------------------------------
function ��ȡ������ȯ()
	RunInfo("��ȡ������ȯ")
	return scmd():GainWeekShouLieQuan()
end

function ��Ӳɼ�������( collect_name )
	if type(collect_name) ~= "string" then
		LuaLogE("��Ӳɼ�������֮�ɼ��������������ַ�������")
		return
	end
	RunInfo("��Ӳɼ������������֣�" .. collect_name)
	return scmd():AddCollectBlackList(collect_name)
end

function ��ղɼ�������()
	RunInfo("��ղɼ�������")
	return scmd():ClrCollectBlackList()
end

function ����ִ��_�����( func, cnt )
	RunInfo("����ִ��_�����")
	return scmd():DoEveryObj_Bucket(func, cnt)
end

function �ڳ�����()
	RunInfo("�ڳ�����")
	return scmd():IsInVillage()
end

function �ڸ�����()
	RunInfo("�ڸ�����")
	return scmd():IsInFb()
end

function ��ȡ��ǰ��������()
	RunInfo("��ȡ��ǰ��������")
	return scmd():GetSelfWeapon()
end

function ��ɫ�ѽ�����Ϸ��( func, ... )
	if type(func) ~= "function" then
		LuaLogE("��ɫ�ѽ�����Ϸ��֮���������������Ǻ�������")
		return false
	end
	RunInfo("��ɫ�ѽ�����Ϸ��")
	return LuaHandleRoleEnteredGame(func, ...)
end

function ������Ϸ����( func, ... )
	if type(func) ~= "function" then
		LuaLogE("������Ϸ����֮���������������Ǻ�������")
		return false
	end
	RunInfo("������Ϸ����")
	return LuaHandleGameScene(func, ...)
end

function ��BOSS����( obj )
	RunInfo("��BOSS����")
	return scmd():IsTheBoss(obj)
end

function ���ò�ȥ���ֹ���֮�Ƹ�����( min_gold, min_silver )
	if type(min_gold) ~= "number" then
		LuaLogE("���ò�ȥ���ֹ���֮�Ƹ�����֮������Ʋ�����������������")
		return
	end
	if type(min_silver) ~= "number" then
		LuaLogE("���ò�ȥ���ֹ���֮�Ƹ�����֮�������Ʋ�����������������")
		return
	end
	RunInfo("���ò�ȥ���ֹ���֮�Ƹ����ƣ�������ƣ�" .. tostring(min_gold) .. " �������ƣ�" .. tostring(min_silver))
	return scmd():SetMinMoneyToKeepBuy(min_gold, min_silver)
end

function ��ĳ�������ĳ��NPC( village_name, npc_name, npc_title, room_num, cur_village_first )
	if type(village_name) ~= "string" then
		LuaLogE("��ĳ�������ĳ��NPC֮�����������������ַ�������")
		return false
	end
	if type(npc_name) ~= "string" then
		LuaLogE("��ĳ�������ĳ��NPC֮NPC�����������ַ�������")
		return false
	end
	if type(npc_title) ~= "string" then
		npc_title = ""
	end
	if type(room_num) ~= "number" then
		room_num = 0
	end
	if type(cur_village_first) ~= "boolean" then
		cur_village_first = false
	end
	RunInfo("��ĳ�������ĳ��NPC������" .. village_name .. " NPC��" .. npc_name .. " ����ţ�" .. tostring(room_num) .. " �Ƿ������ڱ��������NPC:" .. tostring(cur_village_first))
	return scmd():OpenTheNpcOfVillage(village_name, room_num, npc_name, npc_title, cur_village_first)
end

function ��ĳ�������ָ��NPC( village_name, npc_id, room_num, cur_village_first )
	if type(village_name) ~= "string" then
		LuaLogE("��ĳ�������ָ��NPC֮�����������������ַ�������")
		return false
	end
	if type(npc_id) ~= "number" then
		LuaLogE("��ĳ�������ָ��NPC֮NpcId������������������")
		return false
	end
	if type(room_num) ~= "number" then
		room_num = 0
	end
	if type(cur_village_first) ~= "boolean" then
		cur_village_first = false
	end
	RunInfo("��ĳ�������ָ��NPC������" .. village_name .. " NpcId��" .. tostring(npc_id) .. " ����ţ�" .. tostring(room_num) .. " �Ƿ������ڱ��������NPC:" .. tostring(cur_village_first))
	return scmd():OpenVillageNpcById(village_name, room_num, npc_id, cur_village_first)
end

function �õ����������NpcId( task_id )
	if type(task_id) ~= "number" then
		LuaLogE("�õ����������NpcId֮����ID������������������")
		return -1
	end
	RunInfo("�õ����������NpcId,����ID��" .. tostring(task_id))
	return scmd():GetTaskNpcId(true, task_id)
end

function �õ��ύ�����NpcId( task_id )
	if type(task_id) ~= "number" then
		LuaLogE("�õ��ύ�����NpcId֮����ID������������������")
		return -1
	end
	RunInfo("�õ��ύ�����NpcId,����ID��" .. tostring(task_id))
	return scmd():GetTaskNpcId(false, task_id)
end

--��һ�������ǹ��������ַ������ͣ�����Ϊ��
--�ڶ�������Ҫɱ���������������ͣ���Ϊ�գ�Ϊ�ձ�ʾɱ������ֵĹ���
function ɱ��ָ�����ֺ������Ĺ���( obj_name, kill_cnt, use_item_name, steps_at_use_item )
	if type(obj_name) ~= "string" then
		LuaLogE("ɱ��ָ�����ֺ������Ĺ���֮�����������������ַ�������")
		return 0
	end
	if type(kill_cnt) ~= "number" then
		kill_cnt = -1
	end
	if type(use_item_name) ~= "string" then
		use_item_name = ""
	end
	if type(steps_at_use_item) ~= "number" then
		steps_at_use_item = 1
	end
	RunInfo("ɱ��ָ�����ֺ������Ĺ���,��������" .. obj_name .. " Ҫɱ����������" .. tostring(kill_cnt))
	return scmd():KillTheMonsterAsCnt(obj_name, kill_cnt, use_item_name, steps_at_use_item)
end

function ���ݵ�ǰ�����Զ����õ�ǰBOSS�Ĺ�����λ( task_id )
	if type(task_id) ~= "number" then
		LuaLogE("���ݵ�ǰ�����Զ����õ�ǰBOSS�Ĺ�����λ֮����ID������������������")
		return
	end
	RunInfo("���ݵ�ǰ�����Զ����õ�ǰBOSS�Ĺ�����λ,����ID��" .. tostring(task_id))
	return scmd():AutoSetCurBossHitBodyPartAsTheTask(task_id)
end

function ��Ӻ���( role_name )
	if type(role_name) ~= "string" then
		LuaLogE("��Ӻ���֮��ɫ�������������ַ�������")
		return
	end
	RunInfo("��Ӻ���,��ɫ����" .. role_name)
	return scmd():AddNewFriend(role_name)
end

function ��ȡ����_������������������()
	local res = scmd():GetError_FbSerIsFull()
	RunInfo("��ȡ����_������������������,������" .. tostring(res))
	return res
end

--�����Ƕ����ű���������Ϊ�գ��������ַ�������
function ���и���ָ���Ľű�( script_name )
	if type(script_name) ~= "string" then
		LuaLogE("���и���ָ���Ľű�֮�����ű��������������ַ�������")
		return
	end
	RunInfo("���и���ָ���Ľű���" .. script_name)
	return scmd():DoChangeRunScriptLevel0(script_name)
end

function �õ���Ҫ�����Ķ����ű���()
	local res = scmd():GetNextChangeScriptNameLevel0()
	RunInfo("�õ���Ҫ�����Ķ����ű�����" .. res)
	return res
end

function �õ�ӵ�еĽ��()
	local res = scmd():GetRoleCurGold()
	RunInfo("�õ�ӵ�еĽ�ң�" .. tostring(res))
	return res
end

function �õ�ӵ�е�����()
	local res = scmd():GetRoleCurSilver()
	RunInfo("�õ�ӵ�е����ң�" .. tostring(res))
	return res
end

function ����Ҫѡ��ĵڼ�����������·( ser_line )
	if type(ser_line) ~= "number" then
		LuaLogE("����Ҫѡ��ĵڼ�����������·֮��������·������������������")
		return
	end
	RunInfo("����Ҫѡ��ĵڼ�����������·����������·��" .. tostring(ser_line))
	return scmd():SetCurSerLine(ser_line)
end

function ��������潻��( func_pre_deal, func_do_deal, func_after_deal )
	RunInfo("��������潻��")
	return scmd():DoDealFaceToFace(func_pre_deal, func_do_deal, func_after_deal)
end

function ����潻��_������( player_name, wait_time )
	if type(player_name) ~= "string" then
		LuaLogE("����潻��_������֮Ŀ�꽻�׶�������������ַ�������")
		return false
	end
	if type(wait_time) ~= "number" then
		wait_time = 1000 * 60 * 2
	end
	RunInfo("����潻��_�����ף�Ŀ����ң�" .. player_name .. " �ȴ�ʱ�䣺" .. tostring(wait_time))
	return scmd():Deal_RequestDeal(player_name, wait_time)
end

function ����潻��_�ȴ�������һ����������( time_out )
	if type(time_out) ~= "number" then
		time_out = 1000 * 60
	end
	RunInfo("����潻��_�ȴ�������һ���������󣬳�ʱʱ�䣺" .. tostring(time_out))
	return scmd():Deal_UntilAcceptOneDealRequest(time_out)
end

--��һ�������Ǹ�������������{ { "����֮��", 1 }, { "һ����֮��", -1 } }����������1��ʾ���׹���֮�������Ϊ1��-1��ʾ��������һ����֮��
--�ڶ���������Ҫ���׵Ľ�ң��������ͣ�����Ϊ�գ�Ϊ0��ʾ�����׽�ң������-100����ʾ����100��ң�����ȫ������
function ����潻��_�Ƶ���Ʒ�ͽ�ҵ�������( tbl_items, gold )
	if type(gold) ~= "number" then
		LuaLogE("����潻��_�Ƶ���Ʒ�ͽ�ҵ�������֮��Ҳ�����������������")
		return false
	end
	RunInfo("����潻��_�ȴ�������һ���������󣬽��:" .. tostring(gold))
	return scmd():Deal_MoveSomeItems_Gold(tbl_items, gold)
end

function ����潻��_����������()
	RunInfo("����潻��_����������")
	return scmd():Deal_LockDealTab()
end

function ����潻��_ȷ�Ͻ���()
	RunInfo("����潻��_ȷ�Ͻ���")
	return scmd():Deal_EnterDeal()
end

function ������״̬()
	local res = scmd():IsNiRenState()
	RunInfo("������״̬��" .. tostring(res))
	return res
end

function ��������״̬( time_out )
	if type(time_out) ~= "number" then
		LuaLogE("��������״̬֮��ʱʱ���������������")
		return false
	end
	RunInfo("��������״̬����ʱʱ�䣺" .. tostring(time_out))
	return scmd():HandleNiRenState(time_out)
end

function ��ȼ��״̬()
	local res = scmd():IsRanShaoStatus()
	RunInfo("��ȼ��״̬��" .. tostring(res))
	return res
end

function ����ȼ��״̬( time_out )
	if type(time_out) ~= "number" then
		LuaLogE("����ȼ��״̬֮��ʱʱ���������������")
		return false
	end
	RunInfo("����ȼ��״̬����ʱʱ�䣺" .. tostring(time_out))
	return scmd():HandleRanShaoStatus(time_out)
end

function �Ƕ��״̬()
	local res = scmd():IsErChouStatus()
	RunInfo("�Ƕ��״̬��" .. tostring(res))
	return res
end

function ��ѩ��״̬()
	local res = scmd():IsSnowManStatus()
	RunInfo("��ѩ��״̬��" .. tostring(res))
	return res
end

function ����ѩ��״̬( time_out )
	if type(time_out) ~= "number" then
		LuaLogE("����ѩ��״̬֮��ʱʱ���������������")
		return false
	end
	RunInfo("����ѩ��״̬����ʱʱ�䣺" .. tostring(time_out))
	return scmd():HandleSnowManState(time_out)
end

--[[
���Կ��ƴ�һ�θ������ĵ���ʲô
��һ������������ģʽ��0��ʾֻ��������ȯ��1��ʾֻ�������ң�2��ʾ����������ȯ������ȯ�������������
�ڶ���������������ң�ֻ�е�ǰӵ�е����Ҵ��ڵ�������������Ż�ʹ�����ҽ��븱��
]]
function ���ø�������ģʽ( mode, min_silver )
	if type(mode) ~= "number" then
		LuaLogE("���ø�������ģʽ֮����ģʽ������������������")
		return
	end
	if type(min_silver) ~= "number" then
		LuaLogE("���ø�������ģʽ֮������Ҳ�����������������")
		return
	end
	RunInfo("���ø�������ģʽ��ģʽ��" .. tostring(mode) .. " ������ң�" .. tostring(min_silver))
	return scmd():SetFbConsumeMode(mode, min_silver)
end

function �ǲ���״̬()
	local res = scmd():IsChanRaoStatus()
	RunInfo("��ѩ��״̬��" .. tostring(res))
	return res
end

function �������״̬( time_out )
	if type(time_out) ~= "number" then
		LuaLogE("�������״̬֮��ʱʱ���������������")
		return false
	end
	RunInfo("�������״̬����ʱʱ�䣺" .. tostring(time_out))
	return scmd():HandleChanRaoStatus(time_out)
end

function �������װ���Ĳ��ϳ�����Ϣ()
	RunInfo("�������װ���Ĳ��ϳ�����Ϣ")
	return scmd():TestOutEquipMaterialFrom()
end
