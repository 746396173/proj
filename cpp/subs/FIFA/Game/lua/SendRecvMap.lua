
--test
--[[
function RecvGet( json_msg )
	LuaLog("recv get succeed");
end
--]]

--��ѯ��������Ʒ
function Get_BagBox( bag_items )
	--[[
	if bag_items:Size() > 0 then
		--ȫ�����ձ�������Ʒ
		SendNormalMsgAsync("/bag/unpackall", "{}");
	end
	--]]
end

--���Ͳ�ѯ��������Ʒ
function SendGet_BagBox()
	--SendGetMsgAsync("/bag");
end

--������Ա
function Post_SellPlayer( quest, json_msg )
	local quest_msg = JsonValue();
	if not quest:DeContentToJson(quest_msg) then
		LuaLogE("can not convert to json");
		return;
	end
	if not RequestMsgSucceed(json_msg) then
		LuaLogW("������Աû�гɹ�");
	end
	GPlayerMe():OnSellPlayerSucceed(quest_msg:Key("playerobjectid"):AsString());
end
