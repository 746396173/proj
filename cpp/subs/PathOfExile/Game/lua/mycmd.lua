require("s_command")
mycmd = {

}
local scmd = scmd
local RunInfo = s_command.RunInfo
local RunInfoP = s_command.RunInfoP
local RunInfoF = s_command.RunInfoF
local RunInfoS = s_command.RunInfoS

---------------------------------
---------------�������
function �Զ�������(flag)
    RunInfoP()
    return scmd.EnableAutoOpenChest(flag)
end

function �Զ�����Ʒ(enable)
    if enable == nil then enable = true end
    RunInfoP(enable)
    return scmd.EnableAutoPickupItem(enable)
end

function �Զ������͵�(enable)
    if enable == nil then enable = true end
    RunInfoP(enable)
    return scmd.EnableAutoOpenWaypoint(enable)
end

function �Զ�����(enable)
    if enable == nil then enable = true end
    RunInfoP(enable)
    return scmd.EnableAutoOpenTransitionable(enable)
end

function �����츳��(jobSkillNode)
    RunInfoP()
    return scmd.SetPassiveSkillTree(jobSkillNode)
end

function Ĭ���������ܱ�ʯ(enable)
    if enable == nil then enable = true end
    RunInfoP(enable)
    return scmd.EnableAutoLvlUpSkillGemByDef(enable)
end

--����1��Ѫ�����ڰٷֱ� 0.6 =  60%;����2��ħ�����ڰٷֱ�0.6 = 60%
function �����Զ���Ѫ����(hpRate, mpRate)
    RunInfoP(hpRate, mpRate)
    return scmd.SetAutoUseFlask(hpRate, mpRate)
end

function ����ȫ��Σ�վ���(screenRate)
    RunInfoP(screenRate)
    return scmd.SetGlobalDangerDistance(screenRate)
end

function ��������(skillName)
    RunInfoP(skillName)
    return scmd.MakeSkill(skillName)
end

function ����ʬ�弼��(skillName)
    RunInfoP(skillName)
    return scmd.MakeCorpseSkill(skillName)
end

function ��Ӽ���(skill)
    RunInfoP()
    return scmd.AddSkill(skill)
end

function ��ռ���()
    RunInfoP()
    return scmd.ClearSkills()
end

function ��ռ��ܱ�ʯ������Ϣ()
    RunInfoP()
    return scmd.ClearSkillGemLvlUpInfo()
end

function ��Ӽ��ܱ�ʯ������Ϣ(skillGemName, maxLvl)
    RunInfoP(skillGemName, maxLvl)
    return scmd.AddSkillGemLvlUpInfo(skillGemName, maxLvl)
end
---------------------------------
function �ȴ����ƶ�(timeout)
    if type(timeout) ~= "number" then
        timeout = 60 * 3
    end
    RunInfoP(timeout .. "��")
    return scmd.WaitRoleCanMove(timeout * 1000)
end

--����ʰȡ��Ʒ�������ӣ������ŵȣ�ֻ����Ҫ��������ּ���
function ��Ŀ��(obj)
    if type(obj) ~= "userdata" then
        RunInfoP(obj)
    else
        RunInfoP()
    end
    return scmd.OpenObj(obj)
end

--������ҵ���Ŀ�����
function �ƶ���Ŀ��(obj)
    if type(obj) ~= "userdata" then
        RunInfoP(obj)
    else
        RunInfoP()
    end
    return scmd.MoveToTheObj(obj)
end

function ɱ������(dstName)
    RunInfoP(dstName)
    return scmd.KillToTheRoom(dstName)
end

--ȫͼɱ��
function ȫͼɱ��(clearMarkPosFirst, traMapRate, remaining)
    if clearMarkPosFirst == nil then clearMarkPosFirst = true end
    if traMapRate == nil then traMapRate = -1 end
    if remaining == nil then remaining = -1 end
    RunInfoP(clearMarkPosFirst, traMapRate, remaining)
    return scmd.KillAllMonster(clearMarkPosFirst, traMapRate, remaining)
end

--����: Ŀ������(�޵�ǰ��ͼ)
function ɱ����Ŀ��(objName,rememFind)
     if type(objName) ~= "string" then 
        LogE("ɱ����Ŀ��֮���������Ǽ�������")
        return false
    end
    if rememFind == nil then rememFind = true end
    RunInfoP(objName)
    return scmd.KillToOpenObj(objName,rememFind)
end

--��������������(�޵�ǰ��ͼ)
function ɱ��ɱ��Ŀ��(obj)
    if type(obj) == "string" then 
       RunInfoP(obj)
    else
       RunInfoP()
    end
    return scmd.KillToKillTheObj(obj)
end

--����:Ŀ���ͼ����(��ǰ�Ѷȵȼ�)
function ɱ��ָ����ͼ(mapName,diffLvl,useWay,useNearWay)
    if type(mapName) ~= "string" then
        LogE("ɱ��ָ����ͼ֮����������Ŀ���ͼ����")
        return false;
    end
    if type(diffLvl) ~= "number" then 
        diffLvl = -1
    end
    if useWay == nil then useWay = true end
    if useNearWay == nil then useNearWay = true end
    RunInfoP(mapName, diffLvl, useWay)
    return scmd.KillToTheMap(mapName,diffLvl,useWay,useNearWay)
end

--����:Ŀ������(�޵�ǰ��ͼ)
function ɱ��Ŀ��(objName)
    if type(objName) ~= "string" then
        LogE("ɱ��Ŀ��֮����������Ŀ������")
        return false
    end
    RunInfoP(objName)
    return scmd.KillToTheObj(objName)
end

--������Ŀ��npc����(���ʺ���ɹֵģ��������)
function ɱ��ɱ��NPC��(npcName)
    if type(npcName) ~= "string" then
        LogE("ɱ��ɱ��NPC��֮����������npc����")
        return false
    end
    RunInfoP(npcName)
    return scmd.KillTokillNpc(npcName)
end

function ɱ��ָ��λ��(dst)
    if type(dst) == "string" then
        RunInfoP(dst)
    else
        RunInfoP()
    end
    return scmd.KillMoveTo(dst)
end

function �ƶ���ָ��λ��(dst)
    RunInfoP()
    return scmd.SmartMoveTo(dst)
end

--�ƶ���ָ��npc ����1: �������� ����2: npc����
function �ƶ���ָ��NPC(townName,npcName)
    if type(townName) ~= "string" then
        LogE("�ƶ���ָ��NPC֮Ŀ���ͼ����Ϊ��")
        return false
    end
    if type(npcName) ~= "string" then 
        LogE(�ƶ���ָ��NPC֮Ŀ��npc���Ʋ���Ϊ��)
        return false;
    end
    RunInfoP(townName, npcName)
    return scmd.MoveToTheNpc(townName,npcName)
end

--�ƶ���ָ������������1����ͼ���� ����2����ͼ�ȼ�(1:һ��  2:�п� 3:����)
function �ƶ���ָ����ͼ(mapName,diffLvl)
    if type(mapName) ~= "string" then
        LogE("�ƶ���ָ����ͼ֮Ŀ���ͼ���Ʋ���Ϊ��")
        return false
    end
    if type(diffLvl) ~= "number" then 
        --LogE("�ƶ���ָ����ͼ֮Ŀ���ͼ�ȼ�����Ϊ���� 1- 3֮��")
        --return false
        diffLvl = -1
    end
    RunInfoP(mapName, diffLvl)
    return scmd.SmartMoveMap(mapName, diffLvl)
end

--�˺��� ������ȡ�����ʹ�npc��������Ʒ����Ʒ���ֻ���������
function ��ȡ������Ʒ(itemNameOrIndex)
    if type(itemNameOrIndex) ~= "string" and type(itemNameOrIndex) ~= "number" then
        LogE("��ȡ������Ʒ֮������������Ʒ���ֻ�����Ʒ��������")
        return false
    end
    RunInfoP(itemNameOrIndex)
    return scmd.TakeNpcItem(itemNameOrIndex)
end

--����:npc�Ի�����(�б���е�һ������)
function �Ի�NPC(talkName)
    if type(talkName) ~= "string" then
         LogE("�Ի�NPC֮�Ի����ݱ������ַ�������npc�Ի��б��е�����")
         return false
    end
    RunInfoP(talkName)
    return scmd.TalkToNpc(talkName)
end

function ѡ����ܹ���()
    RunInfoP()
    return scmd.ChooseKillTheMonster()
end

--����:����
function �ر��������(isCloseNpcPanel)
    if isCloseNpcPanel == nil then isCloseNpcPanel = true end
    RunInfoP()
    return scmd.CloseAllPanel(isCloseNpcPanel)
end

--����:ʹ����Ʒ����
function ʹ����Ʒ(itemName)
    if type(itemName) ~= "string" then 
        LogE("ʹ����Ʒ֮��Ʒ���������ַ���")
        return false
    end
    RunInfoP(itemName)
    return scmd.UseItem(itemName)
end

function ��������ĵ�����Ʒ()
    RunInfoP()
    return scmd.FindNearestObj(GameObjType.kGOT_WorldItem)
end

--����:��������
function ���������Ŀ��(name)
    RunInfoP(name)
    return scmd.FindNearestObj(name)
end

function �����������(monName)
    if type(monName) ~= "string" then
        LogE("�����������֮���������ǹ�������")
        return
    end
    RunInfoP(monName)
    return scmd.FindNearestMonsterObj(monName)
end

--������Ϲ���
function ������Ϲ���(tbl)
    if type(tbl) ~= "table" then
        LogE("������Ϲ���֮���߱����Ǳ�����")
        return
    end
    RunInfoP()
    return scmd.CreateGroupFilter(tbl)
end

--��������
function ��������(filterType,filterTab)
    if type(filterType) ~= "number" then
        LogE("���ô�ֹ���֮�������ͱ���������")
        return;
    end
    RunInfoP(filterType)
    return scmd.CreateFilterObj(filterType,filterTab)
end

function ���ʰȡ����()
    RunInfoP()
    return scmd.ClearFilter(0)
end

function ������۹���()
    RunInfoP()
    return scmd.ClearFilter(1)
end

function �����ֹ���()
    RunInfoP()
    return scmd.ClearFilter(2)
end

function ���ϴ������()
    RunInfoP()
    return scmd.ClearFilter(3)
end

--�ڶ��������Ǹ�tab��
function ���ʰȡ����(filterTab)
    RunInfoP()
    return scmd.AddPickUpFilter(filterTab)
end

function ��Ӵ�ֹ���(filter)
    RunInfoP()
    return scmd.AddStoreFilter(filter)
end

function ��ӳ��۹���(filter)
    RunInfoP()
    return scmd.AddSellFilter(filter)
end

function ���ϴ������(filter)
    RunInfoP()
    return scmd.AddAginRinseFilter(filter)
end

--���ұ�����Ʒ
function ���ұ�����Ʒ(itemName)
    if type(itemName) ~= "string" then
        LogE("���ұ�����Ʒ֮�����������ַ���")
        return nil
    end
    RunInfoP(itemName)
    return scmd.FindPakcetItem(itemName)
end
--��ñ���ĳ����Ʒ���� ����:��Ʒ����
function �����Ʒ����(itemName)
    if type(itemName) ~= "string" then
        LogE("�����Ʒ����֮������������Ʒ��")
        return nil
    end
    RunInfoP(itemName)
    return scmd.GetItemCnt(itemName)
end

--����:��ͼ���� ���޵�ǰ�Ѷȵȼ���
function �Ƿ������͵�(mapName)
    if type(mapName) ~= "string" then
        LogE("�Ƿ������͵�֮���������ǵ�ͼ����")
        return false;
    end
    RunInfoP(mapName)
    return scmd.IsOpenWayPointByMap(mapName)
end

--����1���������ӿ������ ����2:�������Ӹ߶�����
function ���ñ���������С(wight,high)
    if type(wight) ~= "number" then
        LogE("���ñ���������С֮��ȱ�����С�ڱ�����ȵ�ֵ")
        return false;
    end
    if type(high) ~= "number" then
        LogE("���ñ���������С֮�߶ȱ�����С�ڱ����߶ȵ�ֵ")
        return false
    end
    RunInfoP(wight,high)
    return scmd.SetMainBagMinFree(wight,high)
end

--����1:��С�ȼ��� ����2: ���ȼ�������3������ʯ ����4��������ʯ���ӵı�ʯ(������ʯҲ������������ʯ)
function ���ñ�ʯ����(minLevel, maxLevel, mainGemName, otherGemNameTbl)
    if type(mainGemName)  ~= "string" then
        LogE("���ñ�ʯ����֮��һ�����������Ǳ�ʯ��")
        return false;
    end
    if type(otherGemNameTbl)  ~= "table" then
        LogE("���ñ�ʯ����֮�ڶ������������Ǳ�ʯ����")
        return false
    end
    RunInfoP(mainGemName)
    return scmd.SetGemLink(minLevel,maxLevel,mainGemName,otherGemNameTbl)
end

function ����ʯ����()
    RunInfoP()
    return scmd.ClearAllGemLink()
end

--����:��������.���� ��������.˫�� ��������.�޶�λ�õ� 
function ����ʹ����������(weaponType)
    if type(weaponType) ~= "number" then
        LogE("����ʹ����������֮��������")
        return false;
    end
    RunInfoP(weaponType)
    return scmd.SetWearWeaponType(weaponType)
end

--����:��������
function ��������(questName)
    if type(questName) ~= "string" then
        LogE("��������֮�������ֱ������ַ���")
        return false
    end
    RunInfoP(questName)
    return scmd.HasTheQuestByName(questName)
end

function �ڳ���()
    RunInfoP()
    return scmd.InTown()
end

function �Զ����()
    RunInfoP()
    return scmd.AutoStoreBagItemToStore()
end

function �Զ�����(npcName)
    if npcName == nil then npcName = "" end
    RunInfoP(npcName)
    return scmd.AutoSellBagItem(npcName)
end

--����1:NPC����  ����2:�������Ʒ����
function ������Ʒ(npcName,itemName,cnt)
    if type(npcName) ~= "string" then
        LogE("�Զ�������Ʒ֮npc���ֱ������ַ���")
        return 0
    end
    if type(itemName) ~= "string" then
        LogE("�Զ�������Ʒ֮��Ʒ�������ַ���")
        return 0
    end
    if type(cnt) ~= "number" then
        LogE("�Զ�������Ʒ֮��Ʒ��������Ϊ��")
        return 0
    end
    RunInfoP(npcName, itemName, cnt)
    return scmd.BuyItemByNpc(npcName,itemName,cnt)
end

function ʰȡ���������Ʒ()
    RunInfoP()
    return scmd.PickUpQuestItem()
end

--����:ְҵ���� ("Ů��"...��)
function ����Ĭ�ϴ�����ɫ��ְҵ(professionName)
    RunInfoP(professionName)
    return scmd.SetDefCreateProfessionType(professionName)
end

--��������������
function ����Ĭ�ϴ�����ɫ����(gameArea)
    RunInfoP(gameArea)
    return scmd.SetDefCreateGameArea(gameArea)
end

--��������ɫ����(ѡ�������Ϸ�Ľ�ɫ����)
function ѡ�������Ϸ(roleName)
    RunInfoP(roleName)
    return scmd.SelectEnterGame(roleName)
end

function ��½����(fn)
    return scmd.GScene_LoginState(fn)
end

function ѡ���ɫ����(fn)
    --RunInfoP()
    return scmd.GScene_PreGameState(fn)
end

function ��Ϸ�ڳ���(fn)
    --RunInfoP()
    return scmd.GScene_InGameState(fn)
end

--�����Զ���װ
function �Զ���װ(enable)
    RunInfoP(enable)
    return scmd.EnableAutoWearEquip(enable)
end

--�Զ�ϴ��
function �Զ�ϴ��()
    RunInfoP()
    scmd.AutoAgainRinseEquip()
end

--���û�װ����
function ���û�װ����(scoreType,tab)
    if type(scoreType) ~= "number" then
        LogE("���û�װ����֮��һ�������������趨����")
        return 
    end
    RunInfoP(scoreType)
    return scmd.SetItemScore(scoreType,tab)
end

function �����Ʒ���Խ���()
    RunInfoP()
    return scmd.ClearItemAttrParser()
end

function ��Ʒ���Խ���(propName)
    if type(propName) ~= "string" then
        Loge("��Ʒ���Խ���֮��һ�������������Զ�����������")
        return
    end
    RunInfoP(propName)
    return scmd.CreateItemAttrParser(propName)
end

function ��ǰ�Ѷ�()
    return scmd.GetCurDiffLvl()
end

function ���ñ���ҩƷ����(tbl)
    if type(tbl) ~= "table" then
        LogE("����ҩƷ����֮���������Ǳ����ͣ���ο�������")
        return
    end
    RunInfoP()
    return scmd.SetFlaskCnt(tbl)
end

--��һ������ ��ȡ����Ʒ���ͣ��ڶ���������ȡ������()
function �ֿ���ȡ����ͼ(itemCnt)
    RunInfoP()
    return scmd.TakeOutYiJieMapFromStorage(itemCnt)
end

--�ֿ���ȡָ�����ֵ���Ʒ + ����
function �ֿ���ȡ��Ʒ(itemName,itemCnt)
    if type(itemName) ~= "string" then
        LogE("�ֿ���ȡ��Ʒ֮��һ������������ָ����Ʒ����")
        return false
    end
    if type(itemCnt) ~= "number" then
        LogE("�ֿ���ȡ��Ʒ֮�ڶ���������������Ʒ����")
        return false
    end
    RunInfoP(itemName)
    return scmd.TakeOutItemByName(itemName,itemCnt)
end

function ������ͼװ��(mapName) 
    RunInfoP()
    if mapName == nil then mapName = "" end
    return scmd.OpenMapDevice(mapName)
end

function Ѱ����紫����()
    RunInfoP()
    return scmd.FindYiJieTransitonable()
end

function �������ͻ����Ʒ����(type)
    RunInfoP(type)
    return scmd.GetItemCntByType(type)
end

function ��ǰ��ͼ����()
    RunInfoP()
    return scmd.GetCurMapName()
end

function ʹ�ô��;��ᵽ��ͼ(dstMap)
    if dstMap == nil then dstMap = "" end
    RunInfoP()
    return scmd.UseWayReelToMap(dstMap)
end

function ���õ�ͼ����(type,tbl)
    RunInfoP(type)
    return scmd.SetYiJieFilter(type,tbl);
end

function ������װ����(cnt)
    if type(cnt) ~= "number" then
        LogE("������װ����֮��������������")
        return
    end
    RunInfoP(cnt)
    return scmd.SetEmboitementCnt(cnt)
end

--���ֿ���װ����ȡ������(��ȡ�ɹ������� ��֮���ؼ�)
function ���ֿ�װ����װ����ȡ()
    RunInfoP()
    return scmd.CheckStoreEmboitementToBag()
end

function ���ֿⱦʯ��װ����ȡ(totalQuality)
     RunInfoP(totalQuality)
     return scmd.CheckStoreGemTotalQualityToBag(totalQuality)
end

function ��ý���������ͼ()
    RunInfoP()
    return scmd.GetCurYiJieMapName()
end

function ���ý��뷿�俪������(state)
    RunInfoP()
    return scmd.SetJoinRoomOpenWayReel(state)
end

function ��������������Ʒ()
    RunInfoP()
    return scmd.AutoIdentifiedItem(true)
end

function ���������Ʒ����()
    RunInfoP()
    return scmd.PrintBagItemWeight()
end

function ���ֹ�����Ʒ(itemName,itemCnt)
     RunInfoP(itemName,itemCnt)
     return scmd.KeepBuyItem(itemName,itemCnt)
end

function �����Ʒ��ȡ��ʽ(itemName, mapName, npcName)
    RunInfoP(itemName, mapName, npcName)
    return scmd.AddItemPathway(itemName, mapName,npcName)
end
 
function �����ֿ��ͼ(stuffTbl)
    RunInfoP()
    return scmd.UpLevelStashMap(stuffTbl)
end

function ���ô���ʣ�౦ʯ���ȼ�(Level)
    RunInfoP()
    return scmd.SetAutoWearSurplusGem(Level)
end

function ��ǰ��ɫ�ȼ�()
    RunInfoP()
    return scmd.GetRoleLvl()
end

function ���ݹ��տ����ƽ���ͼ��(craft)
    if craft == nil then craft = "" end
    RunInfoP(craft)
    return scmd.OpenHideoutMapDeviceByCarft(craft)
end

function �Զ���Ƕ��ʯ()
    RunInfoP()
    return scmd.AutoWearSomeGem()
end

function �Զ�����װ��()
    RunInfoP()
    return scmd.AutoWearSomeEquips()
end

function ����ϴ��װ��(itemType, minLvl, maxLvl)
    RunInfoP(itemType, maxLvl, maxLvl)
    return scmd.CreateItemTypeRinse(itemType, minLvl, maxLvl)
end

function �Զ���½�ʺ�()
    RunInfoP()
    return scmd.AutoLoginAccount()
end

function ������()
    RunInfoP()
    return scmd.AdjustPack()
end

function �򿪸�������(objName)
    RunInfoP()
    return scmd.CheckNearestObjAndOpen(objName)
end

function �ȴ��ٻ�������(checkCalled)
    if checkCalled == nil then checkCalled = true end
    RunInfoP(checkCalled)
    return scmd.WaitCalledDie(checkCalled)
end

function ɱ�Ÿ�����ƶ�����()
    RunInfoP()
    return scmd.KillFollowMovement()
end

function �������õ�ͼ(state)
    RunInfoP(state)
    return scmd.SetResetMap(state)
end

function ���δ���������ͼ()
    RunInfoP()
    return scmd.GetUndoneLabyrinthMap()
end

function ���ݵȼ������Թ�(level)
    RunInfoP(level)
    return scmd.OpenLabyrinthDevice(level)
end

function ��õ�ǰ�½�()
    RunInfoP()
    return scmd.GetCurChapter()
end