--���ļ��ṩ����

--�õ���Ϸ״̬
function ��Ϸ״̬()
	RunInfo("��Ϸ״̬")
	return GetGameState();
end

--�Ƿ����ѡ��״̬
function ����ѡ�����()
	RunInfo("����ѡ�����")
	HandleElapseTimers()
	return GetGameState() == enGameState.enGameState_TrainerSelect;
end

--�ڽ���ѡ�񳡾��У�������Ϸ
function ������Ϸ()
	RunInfo("������Ϸ")
	--����
	--LeftBtClick(400, 349);
	--������Ϸ
	LeftBtClick(754, 281);
	--�����趨 ѡ��ȷ��
	L_HandlePressControlSetting()
end

--�Ƿ����ѡ��״̬
function ���뵽��Ϸ()
	RunInfo("���뵽��Ϸ")
	return GetGameState() == enGameState.enGameState_TrainerSelected;
end

--����ر�ÿ������dlg
function �ر�ÿ�������()
	RunInfo("�ر�ÿ�������")
	LeftBtClick(511, 653);
end

--���������
function ѡ��������()
	RunInfo("ѡ��������")
	--��������ӳ٣��ͻ���뵽����ҳ���У���֪Ϊ��
	Delay(2000)
	--�������
	LeftBtClick(275, 751);
	Delay(2000)
	--���������
	LeftBtClick(694, 698);
	Delay(2000)
end

--���������ģʽ
function ѡ������ģʽ()
	RunInfo("ѡ������ģʽ")
	--ѡ������ģʽ
	local match_mgr = GMatchMgr_Instance();
	match_mgr:ChooseMatch(enMatchMode.enMatchMode_Managers);
	--���������ģʽ
	HandlePressManagersMode();
	Delay(1500);
	HandlePressManagersMode();
end

--�Ƿ��ڱ�������״̬
function �ڱ�������()
	RunInfo("�ڱ�������")
	return IsInMatchRoom();
end

function ֻ���ڱ�������()
	RunInfo("ֻ���ڱ�������")
	return enGameState.enGameState_Managers == GetGameState();
end

--�Ƿ�ѡ���˾�����ģʽ�Ķ������
function ѡ���˶������()
	RunInfo("ѡ���˶������")
	return GetGameState() == enGameState.enGameState_Managers_Computer;
end

--���������ģʽ֮�������
function ѡ��������()
	RunInfo("ѡ��������")
	LeftBtClick(796, 615);
end

--�Ƿ�ѡ���˾�����ģʽ�Ķ������
function ѡ���˶������()
	RunInfo("ѡ���˶������")
	return GetGameState() == enGameState.enGameState_Managers_Friend;
end

--���������ģʽ֮�������
function ѡ��������()
	RunInfo("ѡ��������")
	LeftBtClick(799, 581);
end

--�Ƿ���뵽�˱���֮ѡ����Ա״̬
function ����ѡ����Ա���б���()
	RunInfo("����ѡ����Ա���б���")
	return GetGameState() == enGameState.enGameState_Match_Choose_Player;
end

--�Ƿ���뵽�˱���֮����
function �Ѿ���������()
	RunInfo("�Ѿ���������")
	return GetGameState() == enGameState.enGameState_Match_Ready;
end

--������½ǰ�ť
function ������½ǰ�ť()
	RunInfo("������½ǰ�ť")
	LeftBtClick(981, 750);
end

--�Ƿ�Ҫ��ʼ����״̬(���Ͼ�Ҫ���붯��)
function �б�������()
	RunInfo("�б�������")
	return GetGameState() == enGameState.enGameState_Match_BeginFirtAnimate;
end

--�Ƿ��������״̬
function �����Ѿ�����()
	RunInfo("�����Ѿ�����")
	return GetGameState() == enGameState.enGameState_MatchEnd;
end

--�Ƿ��������״̬
function ����ѡ���������()
	RunInfo("����ѡ���������")
	return GetGameState() == enGameState.enGameState_MatchEnd_Prize;
end

--[[
--�Ƿ���������ķ���״̬
function IsMatchEnd_BackState()
	return ��Ϸ״̬() == enGameState.enGameState_MatchEnd_Back;
end
--]]

--�Ƿ��������֮��Լ״̬
function ��������Ҫ��Լ()
	RunInfo("��������Ҫ��Լ")
	return GetGameState() == enGameState.enGameState_Managers_Contract;
end

function ������Լ()
	RunInfo("������Լ")
	ContractBySendPackage();
	PressEsc();
end

function �ӳ�( ���� )
	RunInfo("�ӳ�")
	Delay(����);
end

--��ʼ����
function ��ʼ����()
	RunInfo("��ʼ����")
	if ��Ҫ��������() or �ڱ������䳬ʱ() then
		SetScriptOutputInfo("Ҫ�ص�����ѡ������");
		�ص�ѡ���������();
	else
		GMatchMgr_Instance():MatchMode():FightMode():BeginMatch();
		������½ǰ�ť();
	end
end

--�ڱ������䳬ʱ
function �ڱ������䳬ʱ()
	RunInfo("�ڱ������䳬ʱ")
	return GPlayerMe():IsTimeoutAtMatchRoom();
end

--��ESC��
function ��ESC��()
	RunInfo("��ESC��")
	PressEsc();
end

--������Ա
function ������Ա()
	RunInfo("������Ա")
	local stplayer_tbl = {};
	for player in Closure_Iterator(GPlayerMe():CreateExchangePlayerIter()) do
		table.insert(stplayer_tbl, player);
		if table.maxn(stplayer_tbl) == 2 then
			stplayer_tbl[1]:ExchangePlayer(stplayer_tbl[2]);
			return;
		end
	end
	LuaLog("�����ܽ�����Ա");
end

--�Ƿ��п��Խ�������Ա
function �п��Խ�������Ա()
	RunInfo("�п��Խ�������Ա")
	return GPlayerMe():IsCanExchangePlayer();
end

--�Ƿ���Ҫ�Զ�ѡ����Ա
function ��Ҫ�Զ�ѡ����Ա()
	RunInfo("��Ҫ�Զ�ѡ����Ա")
	return GPlayerMe():IsNeedAutoSelectPlayer();
end

--�Զ�ѡ����Ա
function �Զ�ѡ����Ա()
	RunInfo("�Զ�ѡ����Ա")
	--AutoSelectPlayersBySend();
	return GPlayerMe():AutoSelectPlayerBySend();
end

--ִ���Զ�ѡ����Ա
function ִ���Զ�ѡ����Ա()
	RunInfo("ִ���Զ�ѡ����Ա")
	local gp = GPlayerMe();
	if gp:IsNeedAutoSelectPlayer() then
		gp:AutoSelectPlayerBySend();
	end
end

--����Ա��
function ����Ա��( ��Ա������ )
	RunInfo("����Ա��")
	if ��Ա������ == "��ɫ" then
		return UseItem(ItemId_GreenCard());
	elseif ��Ա������ == "��ɫ" then
		return UseItem(ItemId_RedCard());
	elseif ��Ա������ == "��ɫ" then
		return UseItem(ItemId_PurpleCard());
	elseif ��Ա������ == "��ɫ" then
		return UseItem(ItemId_BlueCard());
	else
		LuaLogE("��������������Ա�����ͣ�" .. ��Ա������);
		return false;
	end
end

--��Ĭ�ϵ���Ա��
--[[
function ��Ĭ�ϵ���Ա��()
	RunInfo("��Ĭ�ϵ���Ա��")
	if ����Ա��("��ɫ") and ����Ա��("��ɫ") then
		return;
	elseif ����Ա��("��ɫ") and ����Ա��("��ɫ") then
		return;
	elseif ����Ա��("��ɫ") and ����Ա��("��ɫ") then
		return;
	elseif ����Ա��("��ɫ") and ����Ա��("��ɫ") then
		return;
	end
end
--]]

--�Ƿ�����Ա��
function ����Ա��( ��Ա������ )
	RunInfo("����Ա��")
	if ��Ա������ == "��ɫ" then
		return HasItem(ItemId_GreenCard());
	elseif ��Ա������ == "��ɫ" then
		return HasItem(ItemId_RedCard());
	elseif ��Ա������ == "��ɫ" then
		return HasItem(ItemId_PurpleCard());
	elseif ��Ա������ == "��ɫ" then
		return HasItem(ItemId_BlueCard());
	else
		return false;
	end
end

--�Ƿ���Ĭ�ϵ���Ա��
function ��Ĭ�ϵ���Ա��()
	RunInfo("��Ĭ�ϵ���Ա��")
	if ����Ա��("��ɫ") then
		return true;
	elseif ����Ա��("��ɫ") then
		return true;
	elseif ����Ա��("��ɫ") then
		return true;
	elseif ����Ա��("��ɫ") then
		return true;
	else
		return false;
	end
end

--��EP��
function ��EP��( ���� )
	RunInfo("��EP��")
	OpenCard_EP(����);
end

--EP��������
function EP��������()
	RunInfo("EP��������")
	return EPCardCnt();
end

--��EP��������
function ��EP��������()
	RunInfo("��EP��������")
	return NewEPCardCnt();
end

--����EP��
function ����EP��( ���� )
	RunInfo("����EP��")
	OpenCardNew_EP(����);
end

--�Ƿ����Զ�����ȯ
function ���Զ�����ȯ()
	RunInfo("���Զ�����ȯ")
	return IsHasAutoMatchTicket();
end

--ʹ���Զ�����ȯ������������
function ʹ���Զ�����ȯ������������()
	RunInfo("ʹ���Զ�����ȯ������������")
	HandleAutoMatch();
end

--�Զ�����ȯ������
function �Զ�����ȯ������()
	RunInfo("�Զ�����ȯ������")
	return GPlayerMe():AutoMatchTicketCnt();
end

--ʹ��һЩ�Զ�����ȯ
function ʹ��һЩ�Զ�����ȯ( cnt )
	RunInfo("ʹ��һЩ�Զ�����ȯ")
	GPlayerMe():UseSomeAutoMatchTicket(cnt);
end

--����ű���Ϣ
function ����ű���Ϣ( ��Ϣ )
	RunInfo("����ű���Ϣ, ��Ϣ��" .. ��Ϣ)
	--SetScriptOutputInfo(��Ϣ);
end

--��ӵ�е���Ա������
function ��ӵ�е���Ա������()
	RunInfo("��ӵ�е���Ա������")
	return GetAllPlayersCnt();
end

--��Ҫ�����Ա
function ��Ҫ�����Ա()
	RunInfo("��Ҫ�����Ա")
	return GPlayerMe():IsNeedFirePlayer();
end

--�Զ������Ա
function �Զ������Ա()
	RunInfo("�Զ������Ա")
	GPlayerMe():AutoFirePlayers();
end

--�Ƿ�ѡ��������
function ѡ��������()
	RunInfo("ѡ��������")
	return GPlayerMe():IsSelectedSickEnemy();
end

--�Զ�ѡ������
function �Զ�ѡ������()
	RunInfo("�Զ�ѡ������")
	GPlayerMe():AutoSelectSickEnemy();
	ѡ���������();
end

--����������
function ѡ���������()
	RunInfo("ѡ���������")
	LeftBtClick(802, 643);
end

--ѡ�����������
function ѡ�����������()
	RunInfo("ѡ�����������")
	return GetGameState() == enGameState.enGameState_Managers_Random;
end

--ȡ������
function ȡ������()
	RunInfo("ȡ������")
	assert(false, "����ִ��ȡ������")
	PressDxinputKey(1);
end

--��Ҫ��������
function ��Ҫ��������()
	RunInfo("��Ҫ��������")
	return GPlayerMe():CanJoinedPlayersCnt() <= 18;
end

function �ص�ѡ���������()
	RunInfo("�ص�ѡ���������")
	--�ӱ��������˳���ѡ��״̬
	PressEsc();
	Delay(500);
	PressEsc();
	PressManagers_Back();
	Delay(500);

	while not ����ѡ�����() do
		PressRightTopButton();
		�ر�ÿ�������();
		LuaLog("���Խ���ѡ�������״̬");
		Delay(3000);
	end
end

--�Ƿ���Ҫ�������Ա
function ��Ҫ�������Ա()
	RunInfo("��Ҫ�������Ա")
	return GPlayerMe():NeedSupplyThirdPlayers();
end

--�������Ա
function �������Ա()
	RunInfo("�������Ա")
	GPlayerMe():DegradeAllThirdRubbishPlayers();
	GPlayerMe():FillFullThirdPlayers();
end

--��ʼ��������
function ��ʼ��������()
	RunInfo("��ʼ��������")
	PressCreateCoach();
end

--�������������
function �������������()
	RunInfo("�������������")
	local normal_c = FuncObj_NormalC_Instance();
	if normal_c == nil then
		return;
	end
	local name = GPlayerMe():GenCoachName();
	if name == nil then
		return;
	end
	local str_len = string.len(name);
	LuaLog("coach name: " .. name);
	for i = 1, str_len do
		normal_c:InputCoachName(string.byte(name, i));
	end
	Delay(500);

	GPlayerMe().cc_state = enCreateCoach_SubState.enCC_SubState_InputName;
	PressReturn();
	Delay(500);
end

--������������������
function ������������������()
	RunInfo("������������������")
	PressCreateCoach_FocusInput();
end

--���س�
function ���س�()
	RunInfo("���س�")
	PressReturn();
end

--�Ƿ���Ҫ�ߴ�����������
function ��Ҫ�ߴ�����������()
	RunInfo("��Ҫ�ߴ�����������")
	return GPlayerMe():IsCreateCoachProcedure();
end

--���������Ƿ�ɹ�
function ���������ɹ�()
	RunInfo("���������ɹ�")
	return GPlayerMe().create_coach_succeed;
end

--��ָ���������˸��
function ���˸��( cnt )
	RunInfo("���˸��")
	for i = 1, cnt do
		PressBackSpace();
	end
end

function ����������ֲ�()
	RunInfo("����������ֲ�")
	--������ٴ���
	LeftBtClick(473, 674)
end

function �ر���������()
	RunInfo("�ر���������")
	while not ����ѡ�����() do
		PressRightTopButton();
		Delay(500);
		--�ر���������������dlg
		LeftBtClick(362, 431);

		Delay(500);
		PressRightTopButton();
		LuaLog("�������ɫ�����Խ���ѡ�������״̬");
		Delay(3000);
	end
end

function �ȴ����뵽������������()
	RunInfo("�ȴ����뵽������������")
	local ���� = 0
	while not ���뵽��Ϸ() do
		Delay(2000);
		--�������
		LeftBtClick(965, 734);
		--���ȷ��
		LeftBtClick(890, 545);
		���� = ���� + 1
		if ���� >= 20 then
			local normal = FuncObj_NormalC_Instance();
			if normal == nil then
				return;
			end
			normal:Disconnect();
		end
	end
	LuaLogT("������Ϸ�ɹ�");
end

function ������Ա( ability, price )
	RunInfo("������Ա")
	GPlayerMe():SaleSpecifyPlayers(ability, price);
end

--���ò��ᱻ�������������ֵ
function ���ò��ᱻ�������������ֵ( ability )
	RunInfo("���ò��ᱻ�������������ֵ")
	GPlayerMe().ability_filter = ability;
end

--���ò��ᱻ��������ͼ�ֵ
function ���ò��ᱻ��������ͼ�ֵ( price )
	RunInfo("���ò��ᱻ��������ͼ�ֵ")
	GPlayerMe().exch_price_filter = price;
end

--���ø߼�ֵ��Ա��ʾ
function ���ø߼�ֵ��Ա��ʾ( price )
	RunInfo("���ø߼�ֵ��Ա��ʾ")
	GPlayerMe().high_price_filter = price;
end

--�Ƿ������ڼ���GP���
function ������GP���( idx )
	RunInfo("������GP���")
	GPlayerMe():CanBuyGiftPackage(idx);
end

--��ڼ���GP���
function ��GP���( idx )
	RunInfo("��GP���")
	GPlayerMe():BuyGiftPackageByIdx(idx);
end

function ���ؽű��ļ�( file_name )
	RunInfo("���ؽű��ļ�")
	LoadScriptFile(file_name);
end

--���ձ�������Ʒ
function ���ձ�������Ʒ()
	RunInfo("���ձ�������Ʒ")
	--SendGet_BagBox();
	GPlayerMe():UnpackAllBags();
end

--��������һЩ��Ա
function ��������һЩ��Ա( cnt )
	RunInfo("��������һЩ��Ա")
	GPlayerMe():OpenSomePlayersAs(cnt);
end

--�������㵽
function �������㵽( cnt )
	RunInfo("�������㵽")
	local gp = GPlayerMe();
	local now_cnt = gp:GetAllPlayersCnt();
	if cnt <= now_cnt then
		return;
	end
	local need_cnt = cnt - now_cnt;
	gp:OpenSomePlayersAs(need_cnt);
end

--�Զ�ˢ���ҵĳ����б�
function �Զ�ˢ���ҵĳ����б�()
	RunInfo("�Զ�ˢ���ҵĳ����б�")
	local gp = GPlayerMe();
	if gp:NeedRefreshSelfOffserList() then
		gp:RefreshSelfOfferList();
	end
end

--��������һЩ��Ա
function ��������һЩ��Ա( price, cnt )
	RunInfo("��������һЩ��Ա")
	GPlayerMe():KeepSellingPlayerAs(price, cnt);
end

--��������һ��������Ա
function ��������һ��������Ա( price_min, price_max )
	RunInfo("��������һ��������Ա")
	GPlayerMe():KeepSellingRubbishPlayer(price_min, price_max);
end

--�ֿ�ű�������һЩ��Ա
function �ֿ�ű�������һЩ��Ա( cnt, price_limit )
	RunInfo("�ֿ�ű�������һЩ��Ա")
	GPlayerMe():KeepSellingGoodPlayers( cnt, price_limit );
end

--����һ������Ա����
function ����һ������Ա����( cnt, price_limit )
	RunInfo("����һ������Ա����")
	GPlayerMe():KeepPlayersCntMoreThan(cnt, price_limit);
end

--����ֿ����Ա
function ����ֿ����Ա( ep )
	RunInfo("����ֿ����Ա")
	local gp = GPlayerMe();
	if gp.ep >= ep then
		gp:BuyOtherPlayers();
	end
end

--����ִ����ͨ�ŵĽ�������
function ����ִ����ͨ�ŵĽ�������()
	RunInfo("����ִ����ͨ�ŵĽ�������")
	local normal = FuncObj_NormalC_Instance();
	if ( normal == nil ) then
		return false;
	end
	return normal:CanNormalTradeProcedure();
end

--����ִ����ͨ�ŵĽ�������
function ����ִ�вֿ�ŵĽ�������()
	RunInfo("����ִ�вֿ�ŵĽ�������")
	local normal = FuncObj_NormalC_Instance();
	if ( normal == nil ) then
		return false;
	end
	return normal:CanStoredTradeProcedure();
end

--����Ĭ�ϵļ۸�����һЩ��Ա
function ����Ĭ�ϵļ۸�����һЩ��Ա( price_lower, price_upper )
	RunInfo("����Ĭ�ϵļ۸�����һЩ��Ա")
	GPlayerMe():SalePlayersAsDefault(price_lower, price_upper);
end

--ȷ�ϴ������ֲ�
function ȷ�ϴ������ֲ�()
	RunInfo("ȷ�ϴ������ֲ�")
	LeftBtClick(522, 619);
end

--��ǰEP
function ��ǰEP()
	RunInfo("��ǰEP")
	return GPlayerMe().ep;
end

--ִ�л���
function ִ�л���()
	RunInfo("ִ�л���")
	ExchangeGameAc();
end

--��ְλ��Ա�н���һЩ��Ա
function ��ְλ��Ա�н���һЩ��Ա( price, cnt )
	RunInfo("��ְλ��Ա�н���һЩ��Ա")
	GPlayerMe():ExchPlayersInPosNo(price, cnt);
end

--������Ա����
function ������Ա����()
	RunInfo("������Ա����")
	return GPlayerMe():GetSecondTeamCnt();
end

--��ȡ���������Ա
function ��ȡ���������Ա()
	RunInfo("��ȡ���������Ա")
	GPlayerMe():ChooseExchPlayer();
end

--���öԷ���Ӫ������յ�������Ϣ�ļ۸�
function ���öԷ���Ӫ������յ�������Ϣ�ļ۸�( price )
	RunInfo("���öԷ���Ӫ������յ�������Ϣ�ļ۸�")
	GPlayerMe().against_offer_price = price;
end

--�Զ�ˢ�½�����Ϣ
function �Զ�ˢ�½�����Ϣ()
	RunInfo("�Զ�ˢ�½�����Ϣ")
	GPlayerMe():RefreshCoachMe();
end

--�Զ������¼�
function �Զ������¼�()
	RunInfo("�Զ������¼�")
	GPlayerMe():HandleTimeCancelSale();
end

--����������ʱ�¼�ʱ��
function ����������ʱ�¼�ʱ��( time_hour )
	RunInfo("����������ʱ�¼�ʱ��")
	GPlayerMe():SetTimeWaitSalePlayer(time_hour);
end

--������������
function �����ʱ���ܽ�������()
	RunInfo("�����ʱ���ܽ�������")
	HttpPackageSend_Me():SendPackageHit();
end

--�����������ʱ�ĵ�������
function �����������ʱ�ĵ�������()
	RunInfo("�����������ʱ�ĵ�������")
	LeftBtClick(522, 619);
end

function �������Լ����()
	RunInfo("�������Լ����")
	--1����ԱʱY=120
	--[20,150]
	for i = 150, 20, -10 do
		LeftBtClick(602, i)
	end
end

function ����½�����ϰ������()
	RunInfo("����½�����ϰ������")
	local cnt = 0;
	while true do
		LeftBtClick(695, 424);
		Delay(1000);
		if cnt > 10 then
			break;
		end
		cnt = cnt + 1;
	end
	local normal = FuncObj_NormalC_Instance();
	if normal == nil then
		return;
	end
	normal:Disconnect();
end

function ���ñ�����������( cnt )
	RunInfo("���ñ�����������")
	GPlayerMe().match_limit_cnt = cnt;
end

function ����߼�����һЩ��Ա( player_cnt )
	RunInfo("����߼�����һЩ��Ա")
	return GPlayerMe():SaleSomePlayersAsMaxPrice(player_cnt);
end

function ����߼�����ָ������Ա( player_id, player_cnt )
	RunInfo("����߼�����ָ������Ա")
	local the_cnt = 1;
	if type(player_cnt) == "number" then
		the_cnt = player_cnt;
	end
	return GPlayerMe():SaleThePlayersAsMaxPrice(the_cnt, player_id);
end

function ����ͼ�����һЩ��Ա( player_cnt )
	RunInfo("����ͼ�����һЩ��Ա")
	return GPlayerMe():SaleSomePlayersAsMinPrice(player_cnt);
end

function ����ͼ�����ָ������Ա( player_id, player_cnt )
	RunInfo("����ͼ�����ָ������Ա")
	local the_cnt = 1;
	if type(player_cnt) == "number" then
		the_cnt = player_cnt;
	end
	return GPlayerMe():SaleThePlayersAsMinPrice(the_cnt, player_id);
end

function �ǵ�һ�ο�ʼ��ʱ˫��()
	RunInfo("�ǵ�һ�ο�ʼ��ʱ˫��")
	return GPlayerMe():IsFirstCalcDoubleTime();
end

function ����˫��()
	RunInfo("����˫��")
	return GPlayerMe():IsAtDoubleTime();
end

function ����˫���ʱ()
	RunInfo("����˫���ʱ")
	GPlayerMe():UpdateDoubleTime();
end

function ����ָ����ʱ����( time_minustes )
	RunInfo("����ָ����ʱ����")
	return GPlayerMe():IsAtTheTimeSpan(time_minustes);
end

function ��ָ���ļ۸�����һЩָ������Ա( player_id, player_cnt, price )
	RunInfo("��ָ���ļ۸�����һЩָ������Ա")
	return GPlayerMe():SaleThePlayersAsPrice_Cnt(player_id, player_cnt, price);
end

--[[
��һ����������ԱID
�ڶ���������ǿ���ȼ�����
������������ǿ���ȼ�����
���ĸ�������Ҫ�����������������������Ա�Ѿ������������ĸ����ˣ��򲻻���������
����������������۸�
]]
function ��ָ���ļ۸�����ָ������Ա( player_id, grade_min, grade_max, player_cnt, price )
	RunInfo("��ָ���ļ۸�����ָ������Ա")
	return GPlayerMe():SaleThePlayersSpecific(player_id, grade_min, grade_max, player_cnt, price);
end

function ���˽ؿ�ָ����ʱ����( time_minustes )
	RunInfo("���˽ؿ�ָ����ʱ����")
	return GPlayerMe():IsJieCardTheTimeSpan(time_minustes);
end

function ���˽ؿ�ָ����ʱ����_��( time_minustes )
	RunInfo("���˽ؿ�ָ����ʱ����_��")
	return GPlayerMe():IsJieCardTheTime_Sec(time_minustes);
end

function ��ָ������Ա���нؿ�( player_id, grade, price )
	RunInfo("��ָ������Ա���нؿ�")
	return GPlayerMe():JieCardThePlayer(player_id, grade, price);
end

function ��ָ���ļ۸���һ��ָ������Ա( player_id, grade, price_lower, price_upper )
	RunInfo("��ָ���ļ۸���һ��ָ������Ա")
	return GPlayerMe():BuyThePlayerAsPrice(player_id, grade, price_lower, price_upper);
end

function �Զ�ʹ��һЩ��Ʒ( item_cnt )
	RunInfo("�Զ�ʹ��һЩ��Ʒ")
	if type(item_cnt) ~= "number" then
		LuaLogE("�Զ�ʹ��һЩ��Ʒ֮��Ʒ����������������������")
		return false
	end
	return UseSomeItem(item_cnt)
end

--[[
��һ����������ԱID����ԱID�Ļ�ȡ��ʽ��ο� ��ָ���ļ۸�����һЩָ������Ա ����
�ڶ��������Ǳ�ǿ����Ա��ǿ���ȼ�����
�����������Ǳ�ǿ����Ա��ǿ���ȼ�����
���ĸ�������ǿ����Ա��ǿ���ȼ�����
ǿ����Ա������Ҫ������ͬ��Ա�ſ��ԣ���ǿ����Աָ���ǽϸ�ǿ���ȼ����Ǹ���Ա��ǿ����Ա��������߱�ǿ����Ա�ȼ����Ǹ���Ա��
���ڱ�ǿ����Ա����ǿ���ȼ��� ǿ���ȼ����� �� ǿ���ȼ����� ֮��ĲŻᱻǿ����
����ǿ����Ա����ǿ���ȼ�С�ڵȼ� ǿ����Ա��ǿ���ȼ����� �Ż�ǿ����
]]
function ǿ��ָ������Ա(player_id, dst_grade_min, dst_grade_max, src_grade_max)
	if type(player_id) ~= "number" then
		LuaLogE("ǿ��ָ������Ա֮��ԱID������������������")
		return
	end
	if type(dst_grade_min) ~= "number" then
		LuaLogE("ǿ��ָ������Ա֮��ǿ����Ա��ǿ���ȼ����޲�����������������")
		return
	end
	if type(dst_grade_max) ~= "number" then
		LuaLogE("ǿ��ָ������Ա֮��ǿ����Ա��ǿ���ȼ����޲�����������������")
		return
	end
	if type(src_grade_max) ~= "number" then
		LuaLogE("ǿ��ָ������Ա֮ǿ����Ա��ǿ���ȼ����޲�����������������")
		return
	end
	RunInfo("ǿ��ָ������Ա")
	return L_EnhanceThePlayer(player_id, dst_grade_min, dst_grade_max, 0, src_grade_max)
end

--[[
��һ����������ԱID����ԱID�Ļ�ȡ��ʽ��ο� ��ָ���ļ۸�����һЩָ������Ա ����
�ڶ��������Ǳ�ǿ����Ա��ǿ���ȼ�����
�����������Ǳ�ǿ����Ա��ǿ���ȼ�����
���ĸ�������ǿ����Ա��ǿ���ȼ�����
�����������ǿ����Ա��ǿ���ȼ�����
ǿ����Ա������Ҫ������ͬ��Ա�ſ��ԣ���ǿ����Աָ���ǽϸ�ǿ���ȼ����Ǹ���Ա��ǿ����Ա��������߱�ǿ����Ա�ȼ����Ǹ���Ա��
���ڱ�ǿ����Ա����ǿ���ȼ��� ǿ���ȼ����� �� ǿ���ȼ����� ֮��ĲŻᱻǿ����
����ǿ����Ա����ǿ���ȼ�С�ڵȼ� ǿ����Ա��ǿ���ȼ����� �Ż�ǿ����
]]
function ָ��ǿ��ָ������Ա(player_id, dst_grade_min, dst_grade_max, src_grade_min, src_grade_max)
	if type(player_id) ~= "number" then
		LuaLogE("ָ��ǿ��ָ������Ա֮��ԱID������������������")
		return
	end
	if type(dst_grade_min) ~= "number" then
		LuaLogE("ָ��ǿ��ָ������Ա֮��ǿ����Ա��ǿ���ȼ����޲�����������������")
		return
	end
	if type(dst_grade_max) ~= "number" then
		LuaLogE("ָ��ǿ��ָ������Ա֮��ǿ����Ա��ǿ���ȼ����޲�����������������")
		return
	end
	if type(src_grade_min) ~= "number" then
		LuaLogE("ָ��ǿ��ָ������Ա֮ǿ����Ա��ǿ���ȼ����޲�����������������")
		return
	end
    if type(src_grade_max) ~= "number" then
		LuaLogE("ָ��ǿ��ָ������Ա֮ǿ����Ա��ǿ���ȼ����޲�����������������")
		return
	end
	RunInfo("ָ��ǿ��ָ������Ա")
	return L_EnhanceThePlayer(player_id, dst_grade_min, dst_grade_max, src_grade_min, src_grade_max)
end

--[[
���������� ��ɨ�� ������ͼ۸� �� ������߼۸� ֮����Ա��ÿ�ι���ļ۸���������һ�ι���۸�+�����۸�
���� ɨ���ؿ�(1, 1, 10, 30, 10)����ʾɨ ��ԱIDΪ1��ǿ���ȼ�Ϊ1����Ա������۸�������10��20��30��������۸�Ϊ20�ܹ�����ɹ����������20��������۸���Ϣ������̨�� ������ ��Ŀ�¡�
��һ����������ԱID����ԱID�Ļ�ȡ��ʽ��ο� ��ָ���ļ۸�����һЩָ������Ա ����
�ڶ�����������Աǿ���ȼ�
�����������ǹ�����ͼ۸�
���ĸ������ǹ�����߼۸�
����������ǵ����۸�
]]
function ɨ���ؿ�(player_id, grade, price_lower, price_high, price_addition)
	if type(player_id) ~= "number" then
		LuaLogE("ɨ���ؿ�֮��ԱID������������������")
		return -1
	end
	if type(grade) ~= "number" then
		LuaLogE("ɨ���ؿ�֮��Աǿ���ȼ�������������������")
		return -1
	end
	if type(price_lower) ~= "number" then
		LuaLogE("ɨ���ؿ�֮������ͼ۸������������������")
		return -1
	end
	if type(price_high) ~= "number" then
		LuaLogE("ɨ���ؿ�֮������߼۸������������������")
		return -1
	end
	if type(price_addition) ~= "number" then
		LuaLogE("ɨ���ؿ�֮�����۸������������������")
		return -1
	end
	RunInfo("ɨ���ؿ�")
	return L_ScanHideCard(player_id, grade, price_lower, price_high, price_addition)
end

--[[
��ָ���ļ۸�ɨ���ؿ�(1, 2, 30, 10) ��ʾ ��ԱIDΪ1����Աǿ���ȼ�Ϊ2����Ա����30�ļ۸���10����
��һ����������ԱID����ԱID�Ļ�ȡ��ʽ��ο� ��ָ���ļ۸�����һЩָ������Ա ����
�ڶ�����������Աǿ���ȼ�
�����������ǹ���۸�
���ĸ������ǹ������
]]
function ��ָ���ļ۸�ɨ���ؿ�(player_id, grade, price, cnt)
	if type(player_id) ~= "number" then
		LuaLogE("��ָ���ļ۸�ɨ���ؿ�֮��ԱID������������������")
		return -1
	end
	if type(grade) ~= "number" then
		LuaLogE("��ָ���ļ۸�ɨ���ؿ�֮��Աǿ���ȼ�������������������")
		return -1
	end
	if type(price) ~= "number" then
		LuaLogE("��ָ���ļ۸�ɨ���ؿ�֮�۸������������������")
		return -1
	end
	if type(cnt) ~= "number" then
		LuaLogE("��ָ���ļ۸�ɨ���ؿ�֮�������������������������")
		return -1
	end
	RunInfo("��ָ���ļ۸�ɨ���ؿ�")
	return L_ScanHideCardAsPrice(player_id, grade, price, cnt)
end

--[[
��һ����������ԱID����ԱID�Ļ�ȡ��ʽ��ο� ��ָ���ļ۸�����һЩָ������Ա ����
�ڶ�����������Ա���ǿ���ȼ�
��������������Ա���ǿ���ȼ�
ָ����Ա������(1, 1, 1)����ʾ��ԱidΪ1��ǿ���ȼ�Ϊ1����Ա������
]]
function ָ����Ա������(player_id, grade_min, grade_max)
	if type(player_id) ~= "number" then
		LuaLogE("ָ����Ա������֮��ԱID������������������")
		return -1
	end
	if type(grade_min) ~= "number" then
		LuaLogE("ָ����Ա������֮���ǿ���ȼ�������������������")
		return -1
	end
	if type(grade_max) ~= "number" then
		LuaLogE("ָ����Ա������֮���ǿ���ȼ���������������")
		return -1
	end
	RunInfo("ָ����Ա������")
	return L_GetThePlayerCnt(player_id, grade_min, grade_max)
end
