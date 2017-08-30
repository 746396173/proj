
--�������
function HandlePressOnClick_()
	LuaLog("���뵽�����������");
	local normal = FuncObj_NormalC_Instance();
	if normal ~= nil and normal.game_state == enGameState.enGameState_Invalid then
		normal.game_state = enGameState.enGameState_PressOnClick;
		normal:LuaContinueOnClick();
	end
end

--notice dialog
function HandleNoticeDlgScene_()
	local normal = FuncObj_NormalC_Instance();
	if normal == nil then
		return;
	end

	if normal.game_state == enGameState.enGameState_PressOnClick then
		LuaLog("���뵽notice dialog����");
		normal.game_state = enGameState.enGameState_NoticeDlg;
		normal:LuaCloseNoticeDialog();
	end
end

function �������ǰ��ת������()
	LeftBtClick(282,346);
	Delay(3000)
	LeftBtClick(520,309);

	--�������
	LeftBtClick(964,737);
end

--�رչ���Ի���
function CloseNoticeDlg()
	�������ǰ��ת������()
	LeftBtClick(770, 88);
end

--����ѡ��
function HandleTrainerSelect_( _, coach_list )
	if coach_list ~= nil then
		if coach_list:IsNull() or not coach_list:IsArray() then
			LuaLogE("����ѡ��ʱ�յ������������ж�");
			return;
		end

		local normal = FuncObj_NormalC_Instance();
		if normal == nil then
			return;
		end

		if coach_list:Size() == 0 then
			LuaLog("û�н�������Ҫ��������");
			normal.game_state = enGameState.enGameState_CreateCoach;
		else
			LuaLog("���뵽����ѡ�񳡾�");
			normal.game_state = enGameState.enGameState_TrainerSelect;
		end
	end
end

--�����һ�ν������ѡ������
function HandleFirstTrainerSelected( recv_handler_obj )
	--[[
	--����ѡ������
	HandleTrainerSelected_();

	local normal = FuncObj_NormalC_Instance();
	if normal == nil then
		return;
	end

	--�ر�ÿ������dlg
	normal:LuaCloseTaskDlg();
	--]]
end

--����ѡ��
function HandleTrainerSelected_()
	local normal = FuncObj_NormalC_Instance();
	if normal == nil then
		return;
	end
	normal.game_state = enGameState.enGameState_TrainerSelected;
	if normal.game_state == enGameState.enGameState_TrainerSelected then
		LuaLog("���뵽����ѡ������");
	end
	--ִ�������������Ϊ���ܹ�������һ�������񣬵����������ò����û��Ҫ���ˣ��Ժ���˵��
	--normal:LuaTrainerSelectedScene();
end

--������������
function HandlePressFriendshipMatch()
	--���������
	LeftBtClick(368, 588);
	--test���Ժ������ִ�д������������������¼���������
	--ѡ������ģʽ
	local match_mgr = GMatchMgr_Instance();
	match_mgr:ChooseMatch(enMatchMode.enMatchMode_Managers);
end

--������������ģʽ
function HandlePressManagersMode()
	--���������
	LeftBtClick(914, 562);
	Delay(2000)
end

--��������������
function HandleEnterMatchRoom( template_id )
	--����ƥ��
	MultiStrMatchOnTime_Me():ResetMatch(template_id);

	local normal = FuncObj_NormalC_Instance();
	if normal == nil then
		return;
	end
	--[[
	if normal.game_state ~= enGameState.enGameState_TrainerSelected then
		return;
	end
	--]]

	--����ָ���ı�������
	local match_mgr = GMatchMgr_Instance();

	--test���Ժ������ִ�д������������������¼���������
	--ѡ������ģʽ
	match_mgr:ChooseMatch(enMatchMode.enMatchMode_Managers);

	local match_mode = match_mgr:MatchMode();
	match_mode:EnteredRoom();

	--test���Ժ������ִ�д������������������¼���������
	--ѡ��������ģʽ
	match_mode:ChooseFightMode(enFightMode.enFightMode_Computer);
end

--������������ģʽ֮�������
function HandlePressMangers_Computer()
	LeftBtClick(584, 476);
end

--������������ģʽ֮�������
function HandlePressMangers_Friend()
	LeftBtClick(591, 454);
end

--����ѡ���˾�����ģʽ֮�������
function HandleSelectManagers_Computer()
	LuaLog("ѡ���˾�����ģʽ֮�������");
	local normal = FuncObj_NormalC_Instance();
	if normal == nil then
		return;
	end
	normal.game_state = enGameState.enGameState_Managers_Computer;

	--[[
	local match_mgr = GMatchMgr_Instance();
	local match_mode = match_mgr:MatchMode();
	match_mode:ChooseFightMode(enFightMode.enFightMode_Computer);

	--test���Ժ������ִ�д������������������¼���������
	--��ʼ����
	match_mode:FightMode():BeginMatch();
	--]]
end

--����ѡ���˾�����ģʽ�������
function HandleSelectManagers_Friend( recv_handler_obj )
	LuaLog("ѡ���˾�����ģʽ֮�������");
	local normal = FuncObj_NormalC_Instance();
	if normal == nil then
		return;
	end
	normal.game_state = enGameState.enGameState_Managers_Friend;

	--[[
	local match_mgr = GMatchMgr_Instance();
	local match_mode = match_mgr:MatchMode();
	match_mode:ChooseFightMode(enFightMode.enFightMode_Friend);
	--]]
end

--����ѡ���˾�����ģʽ�������
function HandleSelectManagers_Random()
	LuaLog("ѡ���˾�����ģʽ֮�����������");
	local normal = FuncObj_NormalC_Instance();
	if normal == nil then
		return;
	end
	normal.game_state = enGameState.enGameState_Managers_Random;
end

--����������֮�ȴ�
function HandleEnterMatchWaiting(url, send_json_msg)
	if send_json_msg == nil or send_json_msg:IsNull() then
		return;
	end
	local json_stage =  send_json_msg:Key("stage")
	if json_stage:IsNull() or not json_stage:IsString() then
		return
	end
	local stage_value = json_stage:AsString()
	if stage_value == "created" then
		local fight_mode = GMatchMgr_Instance():MatchMode():FightMode();
		fight_mode:EnterWaiting()
	end
end

--����������֮ѡ����Ա
function HandleEnterMatchChoosePlayer( recv_handler_obj )
	local fight_mode = GMatchMgr_Instance():MatchMode():FightMode();
	fight_mode:EnterChoosePlayer();
end

--����������֮�������������״̬
function HandleEnterMatchReadyOrAnimate( url, send_json_msg )
	if send_json_msg == nil or send_json_msg:IsNull() then
		return;
	end
	local json_stage =  send_json_msg:Key("stage")
	if json_stage:IsNull() or not json_stage:IsString() then
		return
	end
	local stage_value = json_stage:AsString()
	if stage_value == "squad" then
		local fight_mode = GMatchMgr_Instance():MatchMode():FightMode();
		fight_mode:EnterMatchReady();
	elseif stage_value == "setting" then
		local fight_mode = GMatchMgr_Instance():MatchMode():FightMode();
		fight_mode:EnterMatchAllReady();
	end
end

--ѡ������ �����趨 ����ȷ�Ϻ󷢵İ�
function HandleControlSetting( uri, send_json_msg )
	L_HandleControlSetting()
end

function HandleScanSoldPlayer( _, send_json_msg, http_request )
	L_HandleScanSoldPlayer(http_request)
end

--�������½ǰ�ť
function HandlePressRightBottomBt()
	LeftBtClick(755, 580);
end

--����������֮�����˶��Ѿ����������뵽����Ϸ��ʼ�Ķ���
function HandleMatch_AllReady()
	local fight_mode = GMatchMgr_Instance():MatchMode():FightMode();
	fight_mode:EnterMatchAllReady();
end

--�����÷���ID
function HandleGainRoomId( recv_handler_obj, last_json_value )
	if last_json_value == nil or not last_json_value:IsInt() then
		--LuaLogE("LUA�л�÷���ID������");
		return;
	end
	--���÷���ID
	GMatchMgr_Instance():MatchMode():GetMatchInfo().room_id = last_json_value:AsInt();
end

--�����ñ���ID
function HandleGainMatchId( recv_handler_obj, last_json_value )
	if last_json_value == nil or not last_json_value:IsInt() then
		--LuaLogE("LUA�л�ñ���ID������");
		return;
	end

	--���ñ���ID
	GMatchMgr_Instance():MatchMode():GetMatchInfo().match_id = last_json_value:AsInt();
end

--�����������
function HandleMatchEnd()
	local fight_mode = GMatchMgr_Instance():MatchMode():FightMode();
	fight_mode:MatchEnd();
end

--�����������֮��������
function HandleMatchEnd_Prize()
	local fight_mode = GMatchMgr_Instance():MatchMode():FightMode();
	fight_mode:MatchEnd_Prize();
end

--�����������֮���ر�������
function HandleMatchEnd_Back( handler_obj )
	local fight_mode = GMatchMgr_Instance():MatchMode():FightMode();
	fight_mode:MatchEnd_Back();

	--ѭ���߱���
	--LuaLogT("ѭ���߱���");
	--GMatchMgr_Instance():MatchMode():FightMode():BeginMatch();
end

--��ʼ��֮������EP
function Handle_GainEpFromServer( recv_handler_obj, exp_json_int )
	if  exp_json_int == nil or not exp_json_int:IsInt() then
		LuaLogW("���EP�������������ж�");
		return;
	end

	GPlayerMe().ep = exp_json_int:AsInt();
end

--��ʼ��֮�����ñ�����Ʒ����
function Handle_GainBagItems( recv_handler_obj, bag_items_json_array )
	if bag_items_json_array == nil or not bag_items_json_array:IsArray() then
		LuaLogW("��ñ�����Ʒ�������������ж�");
		return;
	end

	GPlayerMe():SetBagItems(bag_items_json_array);
end

--��ʼ��֮�����ý�������
function HandleInit_GainName( recv_handler_obj, trainer_name_json_str )
	if trainer_name_json_str == nil or not trainer_name_json_str:IsString() then
		LuaLogW("��ý������ƣ������������ж�");
		return;
	end

	GPlayerMe().name = trainer_name_json_str:AsString();
end

--��ʼ��֮��������ȼ�����
function Handle_GainLevelInfo( recv_handler_obj, level_info_json_obj )
	GPlayerMe():SetJsonLevelInfo(level_info_json_obj);
end

--������dialog֮��Լ
function HandlePressDlg_Contract()
	LeftBtClick(365, 461);
end

--������dialog֮�����Լ
function HandlePressDlg_DoneContract()
	LeftBtClick(400, 348);
end

--�����������֮��Լdialog
function HandleMatchRoom_ContractDlg( recv_handler_obj )
	--LuaLogT("������Լ�Ի���");
	--GMatchMgr_Instance():MatchMode():MatchRoom_CloseContractDlg();
	----[[
	local normal = FuncObj_NormalC_Instance();
	if normal == nil then
		return;
	end
	normal.game_state = enGameState.enGameState_Managers_Contract;
	--]]
end

--�رձ�������֮�����ԼDLG
function CloseMatchRomm_DoneContractDlg()
	LeftBtClick(400, 348);
end

--��������
function HandleLevelUp()
	local normal = FuncObj_NormalC_Instance();
	if normal == nil then
		return;
	end
	normal:CloseLevelUpDlg(500, 2);
end

--�����Ա��Ϣ
function HandleInit_GainPlayers( _, player_json_array )
	GPlayerMe():Init_SetAllPlayers(player_json_array);
end

--��������������Ա����Ϣ
function HandleMatchEnd_GainPlayers( _, player_json_array )
	GPlayerMe():MatchEnd_UpdatePlayers(player_json_array);
end

--���ص�����ѡ������
function ReturnSelectedScene()
	local normal = FuncObj_NormalC_Instance();
	if normal == nil then
		LuaLogE("���ص�����ѡ��������func obj normalû�д���");
		return;
	end
	if normal.game_state == enGameState.enGameState_Managers then
		PressManagers_Back();
	end

	PressRightTop_ReturnSelected();
end

--��������˷���֮����
function PressManagers_Back()
	LeftBtClick(791, 748);
end

--������Ͻǰ�ť
function PressRightTopButton()
	LeftBtClick(971, 68);
end

--������Ͻ�֮����ѡ������
function PressRightTop_ReturnSelected()
	PressRightTopButton();
end

--������ֲ�����
function PressClubManage()
	--[[
	local game_state = GetGameState();
	if game_state ~= enGameState.enGameState_TrainerSelected then
		LuaLogE("��ǰ״̬�ǣ�" .. tostring(game_state) .. "���ܵ�����ֲ�����");
		return;
	end
	--]]
	LeftBtClick(460, 587);
end

--�õ���Ϸ״̬
function GetGameState()
	local normal = FuncObj_NormalC_Instance();
	if normal == nil then
		return enGameState.enGameState_Invalid;
	end
	return normal.game_state;
end

--������Ϸ״̬
function SetGameState( new_game_state )
	local normal = FuncObj_NormalC_Instance();
	if normal == nil then
		LuaLogE("LUA������Ϸ״̬����û���ҵ�func ob normal");
		return;
	end
	normal.game_state = new_game_state;
end

--�����ӹ���
function PressTeamManage()
	LeftBtClick(220, 59);
end

--����Զ�ѡ����Ա
function PressAutoSelectPlayers()
	LeftBtClick(188, 208);
end

--���������ֲ�������
function HandleEnterClubManage()
	LuaLogT("���뵽���ֲ�����״̬");
	SetGameState(enGameState.enGameState_ClubManage);
end

--��������Զ�ѡ����Ա״̬
function HandleEnterAutoSelectPlayer()
	LuaLogT("���뵽�Զ�ѡ����Ա״̬");
	SetGameState(enGameState.enGameState_AutoSelectPlayer);
end

--�����ʼ��֮��Աְλ��Ϣ���ͱ�����������µ���Ϣ
function HandleUpdatePlayersPositions( _, player_json_array )
	if player_json_array == nil then
		LuaLogE("player_json_array����Ϊ��");
		return;
	end
	GPlayerMe():SetFirstSecondPlayers(player_json_array);
end

function HandleUpdateTotalPlayersCnt( _, players_cnt )
	if players_cnt == nil then
		LuaLogE("players_cnt����Ϊ��");
		return;
	end
	GPlayerMe():SetTotalPlayersCnt(players_cnt);
end

--ʹ����Ʒ
function UseItemByItemId( item_id )
	local item = GPlayerMe():FindItemByItemId(item_id);
	if item == nil then
		LuaLogE("UseItemByItemId,û��item_idΪ��" .. item_id .. "����Ʒ");
		return;
	end
	item:Use();
end

--�Ƿ����ʹ����Ʒ
function CanUseItemByItemId( item_id )
	local item = GPlayerMe():FindItemByItemId(item_id);
	if item_id == nil then
		LuaLogE("CanUseItemByItemId,û��item_idΪ��" .. item_id .. "����Ʒ");
		return false;
	end
	return item:CanUse();
end

--������Լ
function ContractBySendPackage()
	if not GPlayerMe():ContractFirstAndSecondPlayers() then
		LuaLogE("������Լʧ��");
	end
end

--������Լ
function ContractByPress()
	LeftBtClick(375, 471);
	LeftBtClick(375, 455);
	CloseMatchRomm_DoneContractDlg();
	Delay(500);
	PressEsc();
end

----[[
--�Զ�ѡ����Ա
function AutoSelectPlayersByPress()
	--�ӱ��������˳���ѡ��״̬
	PressEsc();
	Delay(500);
	PressManagers_Back();
	Delay(500);
	PressRightTop_ReturnSelected();

	AutoSelectPlayersFromSelected();
	--return selected
	PressRightTop_ReturnSelected();

	EnterManagersRoomFromSelected();
end
--]]
--�Ƿ��ڱ�������
function IsInMatchRoom()
	local game_state = GetGameState();
	return game_state == enGameState.enGameState_Managers or game_state == enGameState.enGameState_Managers_Contract or
	game_state == enGameState.enGameState_Managers_Computer or game_state == enGameState.enGameState_Managers_Friend
	or game_state == enGameState.enGameState_Managers_Random;
end

--��ѡ��״̬���뵽�����˷���
function EnterManagersRoomFromSelected()
	while not IsInMatchRoom() do
		Delay(500);
		ѡ��������();
		Delay(500);
		ѡ������ģʽ();
	end
end

--��ѡ��״̬���뵽���ֲ�����Ȼ���Զ�ѡ����Ա
function AutoSelectPlayersFromSelected()
	while GetGameState() ~= enGameState.enGameState_ClubManage do
		PressClubManage();
		Delay(500);
	end

	PressTeamManage();
	Delay(500);
	PressAutoSelectPlayers();
	Delay(500);
end

--ʹ����Ʒ
function UseItem( item_id )
	local item = GPlayerMe():FindItemByItemId(item_id);
	if item == nil then
		return false;
	end
	return item:Use();
end

--�Ƿ���ָ������Ʒ
function HasItem( item_id )
	local item = GPlayerMe():FindItemByItemId(item_id);
	if item == nil then
		return false;
	else
		return item.remains > 0;
	end
end

--EP������
function EPCardCnt()
	local item = GPlayerMe():FindItemByItemId(ItemId_EpCard());
	if item == nil then
		return 0;
	else
		return item.remains;
	end
end

--������EP������
function NewEPCardCnt()
	local item = GPlayerMe():FindItemByItemId(ItemId_EpCardNew());
	if item == nil then
		return 0;
	else
		return item.remains;
	end
end

--��EP��
function OpenCard_EP( cnt )
	if cnt <= 0 then
		LuaLogE("OpenCard_EP֮����Ϊ" .. cnt);
		return;
	end
	local item_cnt = EPCardCnt();
	if item_cnt < cnt then
		cnt = item_cnt;
	end
	local gp = GPlayerMe();

	for i = 1, cnt do
		local item = gp:FindItemByItemId(ItemId_EpCard());
		if item == nil then
			LuaLogE("item��ȻΪ�գ�Ӧ��ִ�в�������");
			return;
		end
		item:Use();
	end
end

--��������EP��
function OpenCardNew_EP( cnt )
	if cnt <= 0 then
		LuaLogE("OpenCardNew_EP֮����Ϊ" .. cnt);
		return;
	end
	local item_cnt = NewEPCardCnt();
	if item_cnt < cnt then
		cnt = item_cnt;
	end
	local gp = GPlayerMe();

	for i = 1, cnt do
		local item = gp:FindItemByItemId(ItemId_EpCardNew());
		if item == nil then
			LuaLogE("item��ȻΪ�գ�Ӧ��ִ�в�������");
			return;
		end
		item:Use();
	end
end

--�Ƿ����Զ�����ȯ
function IsHasAutoMatchTicket()
	return GPlayerMe():HasAutoMatchTicket();
end

--�Զ�����
function HandleAutoMatch()
	GPlayerMe():SendAutoMatch();
end

--�õ�������Ա������
function GetAllPlayersCnt()
	return GPlayerMe():GetAllPlayersCnt();
end

--���ö�����Ϣ
function HandleSetEnemyInfo( _, json_obj )
	LuaLog("ѡ������");
	if json_obj == nil or not json_obj:IsObject() then
		LuaLogE("���ö�����Ϣʱ�������������ж�");
		return;
	end
	GPlayerMe():SetEnemyInfo(json_obj);
end

--���DX����
function PressDxinputKey( di_key )
	local normal_c = FuncObj_NormalC_Instance();
	if normal_c ~= nil then
		normal_c:PressDxinputKey(di_key);
	end
end

--�����׷���Ա
function HandleSetFirstPlayers( _, json_players )
	GPlayerMe():SetFirstPlayers(json_players);
end

--�����油��Ա
function HandleSetSecondPlayers( _, json_players )
	GPlayerMe():SetSecondPlayers(json_players);
end

--�����������
function PressCreateCoach()
	LeftBtClick(416, 377);
end

--�����������dlg֮focus input edit control
function PressCreateCoach_FocusInput()
	LeftBtClick(597, 357);
end

--�õ�����������״̬
function GetCC_SubState()
	return GPlayerMe().cc_state;
end

--�Ƿ���Խ�������������ֺ󷵻���Ϣ
function CanHandleInputCoachName()
	return GetCC_SubState() == enCreateCoach_SubState.enCC_SubState_InputName;
end

--����������ɹ�
function HandleInputCoachNameSucceed()
	LuaLog("����������ɹ�");
	local gplayer = GPlayerMe();
	gplayer.cc_state = enCreateCoach_SubState.enCC_SubState_SelectTeam;
	gplayer.create_coach_succeed = true;
end

--���������ʧ��
function HandleInputCoachNameFail()
	LuaLog("���������ʧ��");
	local gplayer = GPlayerMe();
	gplayer.cc_state = enCreateCoach_SubState.enCC_SubState_Invalid;
	gplayer.create_coach_succeed = false;
end

--���óɾ���Ϣ
function HandleAchievementInfo(_, achievement )
	GPlayerMe():SetAchievementInfo(achievement);
end

--��ʼ��֮������GP
function Handle_GainGpFromServer( _, gp_json_int )
	if  gp_json_int == nil or not gp_json_int:IsInt() then
		LuaLogW("���GP�������������ж�");
		return;
	end

	GPlayerMe().gp = gp_json_int:AsInt();
end

--����������GP�������
function HandleGetGiftPackageData()
	LuaLogT("������GP�������");
	GPlayerMe().getting_gp_data = true;
end

--�Ƿ����ڻ��GP�������
function IsGettingGpData()
	return GPlayerMe().getting_gp_data;
end

--������յ���GP����
function HandleRecvGpData( _, gp_data )
	local gplayer = GPlayerMe();
	if gplayer:SetGiftPackageInfo(gp_data) then
		gplayer.getting_gp_data = false;
	end
end

--����ƣ��
function HandleMatchAddict( _, is_addict )
	if  is_addict == nil or not is_addict:IsBool() then
		LuaLogW("����ƣ�ͣ������������ж�");
		return;
	end

	GPlayerMe():SetMatchAddict(is_addict:AsBool());
end

--���
function HandleBanAccount( _, _ )
	local normal = FuncObj_NormalC_Instance();
	if normal ~= nil then
		normal:BanAccount();
	end
end
