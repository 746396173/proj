--����ļ���ĺ�������Ҫ��ע���߳���ִ��

--����������Ϸ����
function UpdateAllGameObjs()
	local obj_mgr = GameObjMgr_Me();
	if not obj_mgr:RebuildUpdateAll() then
		LuaLog("������Ϸ�������ʧ��");
	end
	return obj_mgr;
end

--���½�ɫ
function UpdateRole()
	local gp = GPlayer_Me();
	if not gp:Update() then
		LuaLog("��ɫ��Ϣ����ʧ��");
	end
	return gp;
end

--���µ�ͼ�򷿼�
function UpdateMapRoom()
	local gm = GMap_Me();
	if not gm:Update() then
		LuaLog("��ͼ����ʧ��");
		return;
	end
	if not gm:IsTown() then
		local gr = GCloneMap_Me();
		if not gr:Update() then
			LuaLog("�������ʧ��");
			return;
		end
	end
	return gm;
end

--���·�����Ϣ
function UpdateRoom()
	local gr = GCloneMap_Me();
	if not gr:Update() then
		LuaLog("������Ϣ����ʧ��");
		return;
	end
	return gr;
end

------------------------------------------------
--ɱ�����еĹ���
function KillAllMonster()
	UpdateMapRoom();
	UpdateAllGameObjs();
	UpdateRole();
	local gp = GPlayer_Me();
	if not gp:KillAllMonster() then
		LuaLogE("ɱ�����еĹ���ʧ��");
	end
	return true;
end

--��������
function StepRoomDoor( door_idx )
	local gr = UpdateRoom();
	if gr == nil then
		return;
	end
	local room_door = gr:GetTheDoor(door_idx);
	local gp = GPlayer_Me();
	gp:EnterAnotherRoom(room_door);
end

--ʰȡ������Ʒ
function PickUpAllItems()
	UpdateAllGameObjs();
	local gp = GPlayer_Me();
	if not gp:PickUpAllItems() then
		LuaLog("ʰȡ������Ʒʧ��");
	end
end

--ʰȡ���н��
function PickUpAllGold()
	UpdateAllGameObjs();
	local gp = GPlayer_Me();
	if not gp:PickUpAllGold() then
		LuaLog("ʰȡ������Ʒʧ��");
	end
	return true;
end

--�Զ��������м���
function AutoLvlUpSkills()
	local gps = GPlayer_Me();
	if not gps:Update() then
		LuaLog("gps update failed");
		return false;
	end
	if not gps:AutoLvlUpSkills() then
		LuaLogE("learn skill error");
		return false;
	end
	return true;
end

function AutoLearnLvlUpSkills()
	local gps = GPlayer_Me();
	if not gps:Update() then
		LuaLog("gps update failed");
		return false;
	end
	if not gps:AutoLearnLvlUpSkills() then
		LuaLogE("learn skill error");
		return false;
	end
	return true;
end

--ֱ���������
function UntileEnteredCity( delay_time )
	if type(delay_time) ~= "number" then
		delay_time = 0;
	end
	local ambient = GAmbient_Me();
	if not ambient:UntilCityUiNow(delay_time) then
		LuaLogE("ֱ��������򷵻�false");
	end
end

--ֱ�����븱��
function UntileEnteredFb( delay_time )
	if type(delay_time) ~= "number" then
		delay_time = 0;
	end
	local ambient = GAmbient_Me();
	if not ambient:UntilEnteredFb(delay_time) then
		LuaLogE("ֱ�����븱������false");
	end
end

--ֱ�����Է��س���
function UntileCanRetCity( delay_time )
	if type(delay_time) ~= "number" then
		delay_time = 0;
	end
	local ambient = GAmbient_Me();
	if not ambient:UntilCanRetCity(delay_time) then
		LuaLogE("ֱ�����Է��س��򷵻�false");
		return false;
	end
	return true;
end

--�������з���
function FightThroughAllRooms( func )
	if func == nil then
		LuaLogE("�������з���֮��������Ϊ��");
		return;
	end
	if type(func) ~= "function" then
		LuaLogE("�������з���֮���������Ǻ�������");
	end
	local gps = UpdateRole();
	if gps == nil then
		LuaLog("��ɫ����ʧ��");
		return;
	end
	if not gps:FightThroughAllRooms(func) then
		LuaLog("�������з������");
		return;
	end
	--AutoLvlUpSkills();
	--�Զ�����װ��();
	--�����Ѵ�װ��();
end

function FightAllGraph( func )
	if func == nil then
		LuaLogE("ȫͼ�򸱱�֮��������Ϊ��");
		return false;
	end
	if type(func) ~= "function" then
		LuaLogE("ȫͼ�򸱱�֮���������Ǻ�������");
	end
	local gps = UpdateRole();
	if gps == nil then
		LuaLog("��ɫ����ʧ��");
		return false;
	end
	if not gps:FightAllGraph(func) then
		LuaLog("ȫͼ�򸱱�����");
		return false;
	end
	return true;
end

--��ɫ�ڸ�����
function RoleInCloneMap()
	local gm = GMap_Me();
	if not gm:Update() then
		LuaLog("��ͼ����ʧ��");
		return false;
	end
	return not gm:IsTown();
end

function RoleInTown()
	local gm = GMap_Me();
	if not gm:Update() then
		LuaLog("��ͼ����ʧ��");
		return false;
	end
	return gm:IsTown();
end

--�ƻ����й�̬��Ʒ
function DestroyAllMisc()
	UpdateMapRoom();
	UpdateAllGameObjs();
	UpdateRole();
	local gp = GPlayer_Me();
	if not gp:DestroyAllMisc() then
		LuaLog("�ƻ����й�̬��Ʒʧ��");
	end
end

function GetGameState()
	local nor = NormalC_Inst();
	if nor == nil then
		LuaLogE("func obj nor is nil");
		return enGameState.kGS_Invalid;
	end
	return nor.game_state;
end

function IsSelectChannelScene()
	return enGameState.kGS_SelectChannel == GetGameState();
end

function IsSelectRoleScene()
	return enGameState.kGS_SelectRole == GetGameState();
end

function IsRoleInGame()
	return enGameState.kGS_InGame == GetGameState();
end

--���ѡ��Ƶ��
function RandomChooseChannel()
	local nor = NormalC_Inst();
	if nor == nil then
		LuaLogE("func obj nor is nil");
		return enGameState.kGS_Invalid;
	end
	if not nor:ChooseChannel() then
		LuaLogE("ѡ��Ƶ������ʧ��");
	end
end

function AutoCreateOrSelectRole()
	local nor = NormalC_Inst();
	if nor == nil then
		LuaLogE("func obj nor is nil");
		return false;
	end
	if not nor:AutoCreateOrSelectRole() then
		LuaLogE("�Զ�������ѡ���ɫ����ʧ��");
		return false;
	end
	return true;
end

--�ƶ���ָ���ĸ���
function MoveToTheCloneMap( fb_ch_name )
	local gps = GPlayer_Me();
	if not gps:MoveToTheCloneMap(fb_ch_name) then
		LuaLogE("�ƶ���ָ���ĸ���ʧ��");
		return false;
	end
	return true;
end

function MoveToTheVillage( village_ch_name )
	local gps = GPlayer_Me();
	if not gps:MoveToTheVillage(village_ch_name) then
		LuaLogE("�ƶ���ָ���ĳ���ʧ��");
		return false;
	end
	return true;
end

function GetRoleFatigueData()
	local gps = GPlayer_Me();
	return gps:GetFatigueData();
end

function RetChooseRoleScene()
	local nor = NormalC_Inst();
	if nor == nil then
		LuaLogE("func obj nor is nil");
		return false;
	end
	return nor:RetChooseRoleScene();
end

function AddPerItemFilter( tbl, i, v )
	if type(v) ~= "table" then
		LuaLogE("�����Ʒ����֮��[" .. tostring(i) .. "]����Ǳ�����");
		return;
	end
	local tbl_tmp = {};
	local item_name = v[1];
	if item_name ~= nil then
		if type(item_name) ~= "string" then
			LuaLogE("�����Ʒ����֮��[" .. tostring(i) .. "]�����Ʒ���Ʊ������ַ�������");
			return;
		end
		--[[
		local item_id = GameEn2ChNodeMgr_Me():GetItemIndex():Ch2EnA(item_name);
		if item_id:empty() then
			LuaLogE("�����Ʒ����֮��[" .. tostring(i) .. "]�����Ʒ���Ʋ�����->" .. item_name);
			return;
		end
		tbl_tmp[1] = item_id;
		--]]
		tbl_tmp[1] = GbkToWideChar(item_name);
		if tbl_tmp[1]:empty() then
			LuaLogE("�����Ʒ����֮��[" .. tostring(i) .. "]�����Ʒ���Ʋ���Ϊ��");
			return;
		end
	end
	local item_quality = v[2];
	if item_quality ~= nil then
		if type(item_quality) ~= "number" then
			LuaLogE("�����Ʒ����֮��[" .. tostring(i) .. "]�����ƷƷ�ʱ�������������");
			return;
		end
		if item_quality < enItemQuality.kIQ_Low or item_quality > enItemQuality.kIQ_Legendary then
			LuaLogE("�����Ʒ����֮��[" .. tostring(i) .. "]�����ƷƷ����ֵ��Ч");
			return;
		end
		tbl_tmp[2] = item_quality;
	end
	local item_lvl = v[3];
	if item_lvl ~= nil then
		if type(item_lvl) ~= "number" then
			LuaLogE("�����Ʒ����֮��[" .. tostring(i) .. "]�����Ʒ�ȼ���������������");
			return;
		end
		if item_lvl <= 0 or item_lvl > 200 then
			LuaLogE("�����Ʒ����֮��[" .. tostring(i) .. "]�����Ʒ�ȼ���ֵ��Ч");
			return;
		end
		tbl_tmp[3] = item_lvl;
	end
	local handler = v[4];
	if type(handler) ~= "function" then
		LuaLogE("�����Ʒ����֮��[" .. tostring(i) .. "]�����Ʒ���˴�������Ǻ�������");
		return;
	end
	if table.maxn(tbl_tmp) > 0 then
		tbl_tmp[4] = handler;
		table.insert(tbl, tbl_tmp);
	end
end

function CmnCmpFunc( lhs, rhs )
	if rhs == nil then
		return true;
	end
	return lhs >= rhs;
end
function WStrCmpFunc( lhs, rhs )
	if rhs == nil then
		return true;
	end
	return 0 == lhs:compare(rhs);
end

function WStrBlurCmpFunc( lhs, rhs )
	if rhs == nil then
		return true;
	end
	if lhs:empty() then
		return true;
	end
	return FindSubWStr(lhs, rhs);
end

function QualityCmpFunc( lhs, rhs )
	if rhs == nil then
		return true;
	end
	return lhs == rhs;
end

function AddTradeItemFilter( filter_tbl, tab_cate )
	if type(filter_tbl) ~= "table" then
		LuaLogE("��ӽ�����Ʒ������֮���˱�Ĳ������ͱ����Ǳ�����");
		return false;
	end
	if type(tab_cate) ~= "number" then
		LuaLogE("��ӽ�����Ʒ������֮��Ʒ����Ĳ������Ͳ��ԣ���������������");
		return false;
	end
	if tab_cate < 1 or tab_cate > 3 then
		LuaLogE("��ӽ�����Ʒ������֮��Ʒ����Ĳ�����ֵ���ԣ����꿴����˵��");
		return false;
	end
	local tbl_tmp = {}
	for i, v in ipairs(filter_tbl) do
		AddPerItemFilter(tbl_tmp, i, v);
	end
	if table.maxn(tbl_tmp) <= 0 then
		return;
	end
	local tmp = GPlayer_Me():GetPacket();
	if tab_cate == 1 then
		tmp = tmp:GetTabNormal();
	elseif tab_cate == 2 then
		tmp = tmp:GetTabMaterial();
	else
		tmp = tmp:GetTabConsume();
	end
	local tbl_item;
	return tmp:AddTradeFilterHandler(function( item )
		local lvl = item:GetItemLevel();
		local item_qua = item:GetItemQualityValue();
		--[[
		local item_id = item:GetItemId();
		for _, v in ipairs(tbl_tmp) do
			if WStrCmpFunc(item_id, v[1]) and CmnCmpFunc(item_qua, v[2]) and CmnCmpFunc(lvl, v[3]) then
				tbl_item = v;
				return true;
			end
		end
		--]]
		local item_cn_name = item:GetItemCnName();
		for _, v in ipairs(tbl_tmp) do
			if WStrBlurCmpFunc(item_cn_name, v[1]) and QualityCmpFunc(item_qua, v[2]) and CmnCmpFunc(lvl, v[3]) then
				tbl_item = v;
				return true;
			end
		end
		return false;
	end, function( item )
		return tbl_item[4](item);
	end);
end

local g_ac_type_normal_ = 1;
local g_ac_type_storehouse_ = 2;
local g_ac_type_trans_station = 3;
local g_ac_type_invalid = 4;

function SaleProductAsPriceImpl( item, price, cnt, product_cnt, ac_type )
	local item_cnt = item:GetItemCnt();
	if item_cnt < cnt then
		cnt = item_cnt;
	end
	GPlayer_Me():SaleProductAsPrice(item, price, cnt, product_cnt, ac_type);
end

function SaleProductAsPrice( price, cnt, product_cnt, ac_type )
	if type(price) ~= "number" then
		LuaLogE("��ָ���ļ۸�����֮�۸������������������");
		return;
	end
	if ac_type ~= nil then
		if type(ac_type) ~= "number" then
			LuaLogE("��ָ���ļ۸�����֮�ʺ�����Ĳ�����������������");
			return;
		end
		if ac_type < g_ac_type_normal_ or ac_type > g_ac_type_trans_station then
			LuaLogE("��ָ���ļ۸�����֮�ʺ�������ֵ����ȷ");
			return;
		end
	else
		ac_type = g_ac_type_invalid;
	end
	ac_type = ac_type - 1;
	if product_cnt ~= nil then
		if type(product_cnt) ~= "number" then
			LuaLogE("��ָ���ļ۸�����֮�����������ƵĲ�����������������");
			return;
		end
		if product_cnt <= 0 then
			product_cnt = -1;
		end
	else
		product_cnt = 1;
	end
	if cnt == nil then
		cnt = 1;
	elseif type(cnt) ~= "number" then
		LuaLogE("��ָ���ļ۸�����֮����������������������");
		return;
	elseif cnt <= 0 then
		cnt = 1;
	end
	if price <= 0 then
		price = 10;
	end
	return function( item )
		return SaleProductAsPriceImpl(item, price, cnt, product_cnt, ac_type);
	end
end

function SaleProductAsPriceBaseImpl( item, price_delta, dlt_price, cnt, product_cnt, ac_type )
	local item_cnt = item:GetItemCnt();
	if item_cnt < cnt then
		cnt = item_cnt;
	end
	GPlayer_Me():SaleProductAsPriceBase(item, price_delta, dlt_price, cnt, product_cnt, ac_type);
end

function SaleProductAsPriceBase( price_delta, dlt_price, cnt, product_cnt, ac_type )
	if type(price_delta) ~= "number" then
		LuaLogE("���г��۵�ĳ����Χ����֮�۸�Χ������������������");
		return;
	end
	if ac_type ~= nil then
		if type(ac_type) ~= "number" then
			LuaLogE("���г��۵�ĳ����Χ����֮�ʺ�����Ĳ�����������������");
			return;
		end
		if ac_type < g_ac_type_normal_ or ac_type > g_ac_type_trans_station then
			LuaLogE("���г��۵�ĳ����Χ����֮�ʺ�������ֵ����ȷ");
			return;
		end
	else
		ac_type = g_ac_type_invalid;
	end
	ac_type = ac_type - 1;
	if product_cnt ~= nil then
		if type(product_cnt) ~= "number" then
			LuaLogE("���г��۵�ĳ����Χ����֮�����������ƵĲ�����������������");
			return;
		end
		if product_cnt <= 0 then
			product_cnt = -1;
		end
	else
		product_cnt = 1;
	end
	if type(dlt_price) ~= "number" then
		LuaLogE("���г��۵�ĳ����Χ����֮Ĭ�ϼ۸����ͱ�������������");
		return;
	end
	if dlt_price < 1 then
		LuaLogE("���г��۵�ĳ����Χ����֮Ĭ�ϼ۸���������ڵ���1");
		return;
	end
	if cnt == nil then
		cnt = 1;
	elseif type(cnt) ~= "number" then
		LuaLogE("���г��۵�ĳ����Χ����֮����������������������");
		return;
	elseif cnt <= 0 then
		cnt = 1;
	end
	return function( item )
		return SaleProductAsPriceBaseImpl(item, price_delta, dlt_price, cnt, product_cnt, ac_type);
	end
end

function KeepPromptDiscoverItemImpl( item )
end

function KeepPromptDiscoverItem()
	return function( item )
		return KeepPromptDiscoverItemImpl(item);
	end
end

function SendMailItemImpl( item, role_name )
	GPlayer_Me():SendMailItem(role_name, item);
end

function SendMailItem( role_name )
	if type(role_name) ~= "string" then
		LuaLogE("�ʼ���Ʒ֮��ɫ�������������ַ�������");
		return;
	end
	return function( item )
		return SendMailItemImpl(item, GbkToWideChar(role_name));
	end
end

function SellTheItemToShopImpl( item )
	GPlayer_Me():SellTheItemToShop(item);
end

function SellTheItemToShop()
	return SellTheItemToShopImpl;
end
