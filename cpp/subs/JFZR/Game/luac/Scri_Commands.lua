
function �ӳ�( ���� )
	return Delay(����);
end

--�Ƿ�����ű�
function ���Խ����ű�()
	assert(false, "�������ÿ��Խ����ű�ָ����");
end

--���ؽű��ļ�
function ���ؽű��ļ�( file_name )
	return LoadScriptFile(file_name);
end

function �պ���()
end

function ��������Ŀ¼�ű�( �ű��� )
	return LoadScriptFile("����\\" .. �ű���);
end
-------------------------------------------------------
--ɱ�����й���
function ɱ�����й���()
	return KillAllMonster();
end

function ��������( room_idx )
	return StepRoomDoor(room_idx);
end

function ʰȡ������Ʒ()
	return PickUpAllItems();
end

function ʰȡ���н��()
	return PickUpAllGold();
end

function �������з���( func )
	return FightThroughAllRooms(func);
end

function ȫͼ�򸱱�( func )
	return FightAllGraph(func);
end

function �����Ѵ�װ��()
	UpdateAllGameObjs();
	local gp = GPlayer_Me();
	gp:RepairAllWearEquip();
end

function �Զ�����װ��()
	local gps = UpdateRole();
	if gps == nil then
		LuaLog("���½�ɫʧ��");
		return;
	end
	local packet = gps:GetPacket();
	if not packet:AutoReplaceEquip() then
		LuaLog("�Զ�����װ��ʧ��");
	end
end

function �Զ��������м���()
	return AutoLvlUpSkills();
end

function �Զ�ѧϰ���������м���()
	return AutoLearnLvlUpSkills();
end

function ���س���()
	UpdateMapRoom();
	local gps = GPlayer_Me();
	gps:ReturnCity();
end

function �Զ��ύ�������()
	return AutoCommitCompleteTasks();
end

function ����ָ������( quest_ch_name )
	return AcceptTheTask(quest_ch_name);
end

function ����ָ�����ѽ�����( quest_ch_name )
	return IsAcceptedTheTask(quest_ch_name);
end

function ָ�����ѽ����������( quest_ch_name )
	return TheAcceptedTaskCompletable(quest_ch_name);
end

function �ƶ���ָ���ĳ���( village_ch_name )
	return MoveToTheVillage(village_ch_name);
end

function �ƶ���ָ���ĸ���( fb_ch_name )
	return MoveToTheCloneMap(fb_ch_name);
end

function ������ͨ������װ��()
	UpdateMapRoom();
	UpdateAllGameObjs();
	local gps = UpdateRole();
	if gps == nil then
		LuaLogE("role update failed");
		return;
	end
	if not gps:SellNormalTabAllEquips() then
		LuaLogE("������ͨ������װ��ʧ��");
		return;
	end
end

function ֱ���������( delay_time )
	return UntileEnteredCity(delay_time)
end

function ֱ�����븱��( delay_time )
	return UntileEnteredFb(delay_time)
end

function ѧϰָ������( skill_ch_name )
	local gps = UpdateRole();
	if gps == nil then
		LuaLogE("update role failed");
		return;
	end
	if not gps:LearnTheSkill(skill_ch_name) then
		LuaLogE("ѧϰ����ʧ��");
	end
end

function ֱ�����Է��س���( delay_time )
	return UntileCanRetCity(delay_time)
end

function ����������ӳ��( func )
	return RestTaskHandlerMap(func);
end

--��һ�����������������ڶ�����������ĺ���
--�������ǽ�ɫ�ȼ����ƣ���ɫ�ȼ�С�������ɫ�ȼ����ƣ��������Ż�ӣ����ܹ��õ�����
--�������������Բ����Ϊ0����ʾ���ܽ�ɫ���ٵȼ�����Ҫ���������Ӧ������
function ���������( quest_ch_name, func, role_lvl_limt )
	return AddTaskHandler(quest_ch_name, func, role_lvl_limt);
end

--���ĸ�������ʾӦ�����ȥ�������
function �������������( quest_ch_name, func, role_lvl_limt, complete_func )
	return AddTaskHandler(quest_ch_name, func, role_lvl_limt, complete_func);
end

--���������������Ĺؼ�����
function �����ϸ��ְҵ������( quest_ch_name, func, role_lvl_limt, complete_func, key_sub )
	return AddSpecifyJobTaskHandler(quest_ch_name, func, role_lvl_limt, complete_func, key_sub);
end

--���������������Ĺؼ�����
--������������ʾƥ������id
function �����ϸ��������( quest_ch_name, func, role_lvl_limt, complete_func, key_sub, match_quest_id )
	return AddSpecifyTaskHandler(quest_ch_name, func, role_lvl_limt, complete_func, key_sub, match_quest_id);
end

function �����ϸ�ķ�ְ֧ҵ������( quest_ch_name, func, role_lvl_limt, complete_func, key_sub, match_quest_id )
	return AddSpecifySubJobTaskHandler(quest_ch_name, func, role_lvl_limt, complete_func, key_sub, match_quest_id);
end

function �Զ�������������()
	return AutoRunTaskHandlerTasks();
end

function ��ɫ�ڸ�����()
	return RoleInCloneMap();
end

function ��ɫ�ڳ�����()
	return RoleInTown();
end

function ���ܱ���ͼ����һ������()
	return AcceptLocalMapAnyTask();
end

function ���ܱ���ͼ������������()
	return AcceptLocalMapAnyAllTasks();
end

function �����������ݵĹؼ�����( sub_contents )
	return IdxTaskKeyContents(sub_contents);
end

function ��������ID�Ĺؼ�����( sub_quest_id )
	return IdxTaskIdKey(sub_quest_id);
end

function �ƻ����й�̬��Ʒ()
	return DestroyAllMisc();
end

function ��ѡ��Ƶ������()
	return IsSelectChannelScene();
end

function ��ѡ���ɫ����()
	return IsSelectRoleScene();
end

function ��ɫ�Ѿ�������Ϸ��()
	return IsRoleInGame();
end

function ���ѡ��Ƶ��()
	return RandomChooseChannel();
end

function �Զ�������ѡ���ɫ()
	return AutoCreateOrSelectRole();
end

function �õ���ɫƣ��ֵ()
	return GetRoleFatigueData();
end

function ���ص�ѡ���ɫ����()
	return RetChooseRoleScene();
end

function Ĭ��תְ()
	local gps = GPlayer_Me();
	return gps:ChangeJobAsDlt();
end

function ��Ҫתְ()
	local gps = GPlayer_Me();
	return gps:NeedChangeJob();
end

function ���װ���Ľ�����Ʒ������( tbl )
	return AddTradeItemFilter(tbl, 1);
end

function ��Ӳ��ϵĽ�����Ʒ������( tbl )
	return AddTradeItemFilter(tbl, 2);
end

function �������Ʒ�Ľ�����Ʒ������( tbl )
	return AddTradeItemFilter(tbl, 3);
end

function ��ָ���ļ۸�����( price, cnt, product_cnt, ac_type )
	return SaleProductAsPrice(price, cnt, product_cnt, ac_type);
end

function ���г��۵�ĳ����Χ����( price_delta, dlt_price, cnt, product_cnt, ac_type )
	return SaleProductAsPriceBase(price_delta, dlt_price, cnt, product_cnt, ac_type);
end

function ��������ʾ��Ʒ()
	return KeepPromptDiscoverItem();
end

function �ʼ���Ʒ( role_name )
	return SendMailItem(role_name);
end

function �����̵�()
	return SellTheItemToShop();
end

function �ֽ���Ʒ()
	return DisassemblyTheItem;
end
