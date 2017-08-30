--[[
��Ϸ״̬������
]]
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--[[
�����յ�����Ϣ���жϻ���
��һ��������json��·��(path)
�ڶ��������Ǵ�����������
������������recv msg handleԪ��(recv_handler_obj, last_json_value)��
�����������ǿ�ѡ�ģ��Ǹ����ֱ��Ӧ��һ���������ֵ�����û�У���ʾֻ��Ч��path�Ƿ����
]]
g_tblRecvMsgHandle = {
	----[[
	--�Ժ����Ż���ʱ�򣬿��Կ������ж���Ϸ״̬����ȥ�ж�����Ѱ·�����ж�ֵ
	--{ RetTrue, HandleFirstTrainerSelected, { "channelid" } },
	{ RetTrue, HandleSelectManagers_Computer, { ".resources.[0].body" }, { "^pve_sim$" } },
	{ RetTrue, HandleSelectManagers_Friend, { ".resources.[0].body" }, { "^custom_sim$" } },
	{ RetTrue, HandleSelectManagers_Random, { ".resources.[0].body" }, { "^pvp_sim$" } },
	{ RetTrue, HandleTrainerSelect_, { ".coachlist" } },
	--���ö�����Ϣ
	{ RetTrue, HandleSetEnemyInfo, { ".resources.[3].body.index.team", ".resources.[3].body.index" } },
	--���ط����".resources.[0].body.stage"=="room"
	--{ RetTrue, HandleEnterMatchWaiting, { ".resources.[0].body.type", ".resources.[0].body.method", ".resources.[0].body.stage" }, { "^pve_sim$", "^createRoom$", "^matched$" } },
	{ RetTrue, HandleEnterMatchChoosePlayer, { ".resources.[0].path", ".resources.[0].body" }, { "^stage$", "^squad$" } },
	--{ RetTrue, HandleEnterMatchReady, { ".resources.[0].path", "result" }, { "^side.left.squad$", true } },
	--{
		--RetTrue, HandleMatch_AllReady,
		--{ "resources.[0].path", "resources.[1].path", "resources.[2].path", "resources.[3].path" },
		--{ "^side.left.ready$", "^side.right.ready$", "^side.observer.ready$", "^side.referee.ready$" }
	--},
	{ RetTrue, HandleGainRoomId, { ".resources.[0].body.roomid" } },
	{ RetTrue, HandleGainMatchId, { ".resources.[0].body.matchmaking.matchid" } },
	----------------
	--��Ϸ��ʼ�����յ�������
	{ RetTrue, Handle_GainEpFromServer, { ".resources.[0].uri", ".resources.[0].body.money.ep" }, { "^/coach/me$" } },
	{ RetTrue, Handle_GainBagItems, { ".resources.[0].uri", ".resources.[0].body.items" }, { "^/coach/me$" } },
	{ RetTrue, HandleInit_GainName, { ".resources.[0].uri", ".resources.[0].body.name" }, { "^/coach/me$" } },
	{ RetTrue, Handle_GainLevelInfo, { ".resources.[0].uri", ".resources.[0].body.levelinfo" }, { "^/coach/me$" } },
	{ RetTrue, HandleInit_GainPlayers, { ".resources.[0].uri", ".resources.[0].body.team.players" }, { "^/coach/me$" } },
	{ RetTrue, HandleUpdatePlayersPositions, { ".resources.[0].uri", ".resources.[0].body.team.squad.positions" }, { "^/coach/me$" } },	--��ʼ��ְλ��Ϣ
	{ RetTrue, HandleUpdateTotalPlayersCnt, { ".resources.[0].uri", ".resources.[0].body.limits.players" }, { "^/coach/me$" } },	--���ֲ���Ա��������
	--���������е���Լ���
	{ RetTrue, HandleMatchRoom_ContractDlg,
		{ ".boost.event", ".boost.igr", ".boost.item", "detail.items", "discount", "players.[0].availablematchcount", "total" }
	},
	--������������յ�������
	{ RetTrue, Handle_GainEpFromServer, { ".resources.[2].path", ".resources.[2].body.ep" }, { "^money$" } },
	{ RetTrue, Handle_GainBagItems, { ".resources.[0].path", ".resources.[0].body" }, { "^items$" } },
	{ RetTrue, Handle_GainLevelInfo, { ".resources.[1].path", ".resources.[1].body" }, { "^levelinfo$" } },
	{ RetTrue, HandleMatchEnd_GainPlayers, { ".resources.[5].path", ".resources.[5].body" }, { "^team%.players%.%$$" } },
	{ RetTrue, HandleSetFirstPlayers, { ".resources.[3].path", ".resources.[3].body.home.players" }, { "^result$" } },
	{ RetTrue, HandleSetSecondPlayers, { ".resources.[3].path", ".resources.[3].body.home.reserved" }, { "^result$" } },
	{ CanHandleInputCoachName, HandleInputCoachNameSucceed, { ".result" }, { true } },
	{ CanHandleInputCoachName, HandleInputCoachNameFail, { ".result" }, { false } },
	--�ɾ�
	{ RetTrue, HandleAchievementInfo, { ".summary", ".achievement" } },
	--gp
	{ RetTrue, Handle_GainGpFromServer, { ".resources.[0].uri", ".resources.[0].body.gp" }, { "^/coach/me$" } },
	--gp���
	{ IsGettingGpData, HandleRecvGpData, { ".[0].shopid", "." } },
	--ƣ��
	{ RetTrue, HandleMatchAddict, { ".resources.[0].path", ".matchaddicted" }, { "^items$" } },
	--���
	{ RetTrue, HandleBanAccount, { ".errorCode", ".result" }, { 5, false } },
	--{ RetTrue, HandleBanAccount, { ".errorCode", ".result", ".reason" }, { 5, false, "^1$" } },
	--]]
	-----------------------------------------
	--[[
	--get ep
	{ "HandleGainEpFromServer", { ".resources.[0].path", ".resources.[0].body.ep" }, { "^money$" } },
	--get ������Ʒ����
	{ "HandleGainBagItems", { ".resources.[0].path", ".resources.[0].body" }, { "^items$" } },
	--get ����ȼ�����
	{ "HandleGainLevelInfo", { ".resources.[0].path", ".resources.[0].body" }, { "^levelinfo$" } },
	--get ��������Ա�仯������(����Ȳ���)
	--]]
};
-------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--by send msg
g_tblMsgCataloghandler = {
	--��ʽΪ{ http URI, handler_obj }
	{ RetTrue, HandlePressOnClick_, "^/game/ads$" },
	--{ RetTrue, HandleNoticeDlgScene_, "^/testcbt/externalAssets/notice/notice.png$" },
	{ RetTrue, HandleNoticeDlgScene_, "^/game/inweburl/notice$" },
	{ RetTrue, HandleTrainerSelected_, "^/chat/blacklist$" },
	{ RetTrue, HandleMatchEnd, "^/match/%d+/end$" },
	--{ RetTrue, HandleMatchEnd_Prize, "^/shop/list$" },
	{ RetTrue, HandleMatchEnd_Back, "^/room/%d+/back$" },
	{ RetTrue, HandleLevelUp, "^/coach/me/level/reward$" }, --��������
	{ RetTrue, HandleEnterClubManage, "^/stadium/%d+$" }, --���ֲ�����״̬
	{ RetTrue, HandleEnterAutoSelectPlayer, "^/coach/me/squad$" }, --�Զ�ѡ����Ա�ɹ�
	{ RetTrue, HandleGetGiftPackageData, "^/shop/list/gp$" }, --GP���
	{ RetTrue, HandleEnterMatchReadyOrAnimate, "^/match/%d+/side/left/ready$" }, --׼�������������������״̬
	{ RetTrue, HandleEnterMatchWaiting, "^/match/%d+/player/ready$" },
	{ RetTrue, HandleControlSetting, "^/ob/externalAssets/beginnersguide/mascot4.png$" }, --���� �����趨
	{ RetTrue, HandleScanSoldPlayer, "^/transfer/search/%d+$" }, --����������Ա��
};

------------------------------------------------------------------------------
-------------------------------------------------------------------------------
--�������հ���ӳ��,post
g_tblMapPost = {
	--handle,uri
	--handle ->������json msg
};
g_tblRequestMapPost = {
	--handle, uri
	--handle ->@p1=quest,@p2=json msg
	--������Ա
	{ Post_SellPlayer ,"/transfer/offer" },
};
--�������հ���ӳ��,get
g_tblMapGet = {
	--handle,uri
	{ Get_BagBox, "/bag" },
};
g_tblRequestMapGet = {

};
-----------------------------------------------------------------------------
-------------------------------------------------------------------------------
--ͨ��hook����call���������ַ���ƥ��ı�
--��ʽ����һ��Ԫ������ֵ����ʾtemplate_id,int
--�ڶ���Ԫ���ǣ��Ƿ��ճ�ʼ����˳�����ƥ�䣬bool
--���ĸ�Ԫ���Ǹ�����ʾҪƥ����ַ���,֧��lua string���ģʽƥ��
--������Ԫ���Ǹ�ȫ��ƥ���Ĵ���ʵ�����ַ���, void( int template_id )
--{ template_id, is_order, { matched_strings }, handle_function_name
g_tblMultiMatch_ByHookSendPackage = {
	---[[
	--������ģʽ
	{ 1, true, "HandleEnterMatchRoom", { "^/room$", "^/contact/list$" } },
	--]]
};

--ͨ��һ�������ı��������ַ���ƥ��ĳ�ʼ������
function InitMultiStrMatchByTbl( tbl )
	local multi_match = MultiStrMatchOnTime_Me();
	if multi_match ~= nil then
		for _, v in ipairs(tbl) do
			multi_match:InitTemplateIdObj(v[1], multi_match:GetLifecycleForever(), v[2]);
			if v[1] ~= nil and v[2] ~= nil and v[3] ~= nil and v[4] ~= nil then
				for _, matched_str in ipairs(v[4]) do
					multi_match:AddMatchedStr(v[1], matched_str);
				end
			end
		end
	end
end

--ͨ��IDƥ��ָ���ַ���
function MatchSpecifyStrById( template_id, specify_str )
	if specify_str == nil then
		return false;
	end
	local multi_match = MultiStrMatchOnTime_Me();
	if multi_match ~= nil then
		return multi_match:AllMatchSpecifyStr(template_id, specify_str);
	end
	return false;
end

--ͨ��һ����ƥ��ָ���ַ���
function MatchSpecifyStrByTbl( tbl, specify_str )
	for _, v in ipairs(tbl) do
		if MatchSpecifyStrById(v[1], specify_str) == true then
			--ȫ��ƥ��ɹ������ô�����
			_G[v[3]](v[1]);
		end
	end
end

--��ʼ��hook send packat multi match table
InitMultiStrMatchByTbl(g_tblMultiMatch_ByHookSendPackage);
-----------------------------------------------------------------------------
-------------------------------------------------------------------------------
