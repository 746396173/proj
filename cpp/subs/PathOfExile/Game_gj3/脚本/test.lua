----[[
�������ýű�("ͨ�ú���")
�������ýű�("ͨ������")
--]]
--�Ի�NPC("Lilly Rot","Sail to Wraeclast")
--��Ŀ��("The Black Core")
local c = scmd
local cdi = CD_Interface
local gpm = GPlayerMe()
���庯�� �ƶ���Ŀ���()
    �ƶ���Ŀ��()
����
���庯�� ɱ��Ŀ���()

����
���庯�� ��_��ͼ����ww()
    ��� ��ǰ��ͼ����() == "The Crypt" ��ô
        ɱ��ָ��λ��("Trial of Ascendancy")
        �򿪸�������("Trial of Ascendancy")
        ɱ����Ŀ��("Trial of Ascendancy Plaque")
    ������� ��ǰ��ͼ����() == "The Lower Prison" ��ô
        ɱ��ָ��λ��("Trial of Ascendancy")
        �򿪸�������("Trial of Ascendancy")
        ɱ����Ŀ��("Lever")
        ɱ����Ŀ��("Trial of Ascendancy Plaque")
    ������� ��ǰ��ͼ����() == "The Crypt Level 1" ��ô
        ɱ��ָ��λ��("Trial of Ascendancy")
        �򿪸�������("Trial of Ascendancy")
        �ƶ���Ŀ��()("Lever")
        ɱ����Ŀ��("Trial of Ascendancy Plaque")
    ������� ��ǰ��ͼ����() == "The Chamber of Sins Level 2" ��ô
        ɱ��ָ��λ��("Trial of Ascendancy")
        �򿪸�������("Trial of Ascendancy")
        ɱ����Ŀ��("Trial of Ascendancy Plaque")
    ������� ��ǰ��ͼ����() == "The Crematorium" ��ô
        ɱ��ָ��λ��("Trial of Ascendancy")
        �򿪸�������("Trial of Ascendancy")
        ɱ����Ŀ��("Lever") --�Զ��򿪸ö���
        ɱ����Ŀ��("Trial of Ascendancy Plaque")
    ������� ��ǰ��ͼ����() == "The Catacombs" ��ô
        ɱ��ָ��λ��("Trial of Ascendancy")
        �򿪸�������("Trial of Ascendancy")
        ɱ����Ŀ��("Lever") --�Զ��򿪸ö��� ��һ��
        ɱ����Ŀ��("Trial of Ascendancy Plaque")
    ����
����
--cdi.DebugTheDbWorldArea("Aspirant's Trial");
--��_��ͼ����ww()
--cdi.DebugPlayerEntityInfo()
--cdi.DebugMapModels(30,true)
--ɱ��ָ����ͼ("Ascendancy Chamber")
--ɱ��ָ��λ��("Trial of Ascendancy")
--ɱ����Ŀ��("Trial of Ascendancy")
--ɱ��ָ��λ��("Lever")
--ɱ����Ŀ��("Aspirant's Trial")
--ɱ����Ŀ��("Trial of Ascendancy Plaque")
--ȫͼɱ��()
--ɱ��Ŀ��("Nessa")
--������ͼװ��()
--DbgTestPrint(1)
--cdi.DebugPlayerPosInfo()
--c.KillMoveTo(stCD_VecInt(2702, 494))
--LogE("------------------------------------------------------")
--cdi.DebugPlayerPosInfo()
----c.KillMoveTo("The Warehouse Sewerss")
--TestAutoDetectTerrainObjs({"Aspirant's Trial"})
--cdi.DebugUiFullInfo(0, 1, 2)
--DbgObjs(false,{0,1,2,3,4,5,6,7,8,10})  --������
--DbgObjs(false,{10}) --�ɴ��Ͷ���
--DbgObjs(false,{0}) --npc
--DbgObjs(false,{1}) --����
--DbgObjs(false,{11}) --�ٻ���
--DbgObjs(false,{10}) --�ٻ���
--��Ŀ��("The Causeway111")
--ȫͼɱ��(true)
local start = G_AStarMe(); 
start:DebugPosInfo(true,"f://tmp//tmp1.log")
--start:DebugPosRectInfo("f:/tmp/tmp1.log", 100, false)
--start:DebugPosRectInfo("f:/tmp/tmp1.log", stCD_VecInt(1741, 1764), 50, false)
local path = GPathMarkMe()
--path:DebugPosInfo(true,"f://tmp//tmp1.log")
--�Զ�����װ��()
--c.AutoWearSomeEquips()
--DbgGSP_Resolver(false)
--gpm:SmartMove(stCD_VecInt(1541, 483))
--gpm:SmartMove(stCD_VecInt(1264, 552))

--cdi.DebugDbInfo("Data/WorldAreas.dat")
--cdi.DebugDbWorldArea()

--ɱ����Ŀ��("The Upper Prison")
--ɱ����Ŀ��("The Warden's Quarters")
--ɱ����Ŀ��("The Cavern of Anger")
--cdi.DebugMySkillInfo()
--ȫͼɱ��()
--cdi.DebugMySkillInfo()
--��Ŀ��("Nessa")
--��Ŀ��("Dying Exile")

--cdi.DebugEntityObjs(9)
--cdi.DebugEntityObjs(1)
--�ȴ����ƶ�(60 * 3)
--cdi.DebugUiFullInfo(0, 1, 2)
--cdi.DebugTheParentUiInfo(0x537C9A00)
--cdi.TestShowUi(0x4A845158)

--�ر��������()

--cdi.DebugWorldInfo()
--cdi.DebugEntityObjs(-1)
--cdi.DebugMapModels(50, false)

local tp = GetDefTerrainParser()

--TestAutoDetectTerrainObjs({ "The Western Forest" })
TestDetectUniqueTerrain(100, 1)
TestDetectOneTerrainArea(100, 2)
--[[
TestDetectUniqueTerrainByPos({stCD_VecInt(368, 759), stCD_VecInt(437, 736)
, stCD_VecInt(391, 713) 
, stCD_VecInt(368, 644), stCD_VecInt(414, 736), stCD_VecInt(414, 736)
})
--]]
--cdi.DbgPlayerPosModel()

--cdi.DebugInGameState()
--ɱ����Ŀ��("Nessa")
--ɱ����Ŀ��("The Upper Prison")
--ɱ����Ŀ��("The Warden's Quarters")
--ɱ����Ŀ��("The Warden's Chambers")
--ɱ��ɱ��Ŀ��("Brutus, Lord Incarcerator")
--ɱ��Ŀ��("Prisoner's Gate")


--cdi.DebugStateInfo()
--cdi.DebugUiFullInfo(0, 1, 2)
--cdi.DebugUiFullInfo(0x57B9B088, 3, 4)
--cdi.DebugUiFullInfo(, 1, 4)

--cdi.TestShowUi(0x538F8578)

--cdi.TestShowUi(0x5914CA98)

--cdi.TestShowUi(0x14CB49E8)

--�ʺ�
--cdi.TestShowUi(0x15753B28)
--����
--cdi.TestShowUi(0x15754A30)
--����
--cdi.TestShowUi(0x15742920)
--��½��ť
--cdi.TestShowUi(0x158922F8)

--TestLoginAccount("2181249973@qq.com", "poe123456", "Singapore")

--cdi.DebugLoginState()
--cdi.DebugPreGameState()
--�Զ���½�ʺ�()
--cdi.DebugSelectRoleTop()
--DbgSortedObjs(false, {4})
--�Զ�����ѡ���ɫ()
--cdi.DebugPlayerEntityInfo()
--cdi.DebugPlayerPosInfo()
--TestActorUseSkill("Fireball", stCD_VecInt(322, 246))
--gpm:SmartMove(stCD_VecInt(428, 229))

--�Զ����()
--TestTerminateCurSkill()
--cdi.DebugWorldInfo()
--cdi.DebugWorldInfo()
--cdi.DebugCurQuestInfo()
--cdi.DebugUiQuestItem(3, 1, 1)
--cdi.DebugUiQuestStateItem()
--cdi.DebugPlayerInfo()
--cdi.DebugPlayerEntityInfo()
--cdi.DebugWorldInfo()
--cdi.DebugEntityObjs(1)
--cdi.DebugInventoryItems(1)
--cdi.DebugFindGridPanelFromDlgProp(1)
--��ȡ������Ʒ("Lightning Tendrils")
--�Զ�����װ��()
--cdi.DebugDbWorldArea()
--������Ʒ("Nessa","Rustic Sash",1)
--cdi.DebugPassiveSkill()
--TestAutoLvlUpPassiveSkills(0)
--�ƶ���ָ����ͼ("Prisoner's Gate", 1)
--cdi.DebugTheDbWorldArea("Lioneye's Watch")
--cdi.DebugTheDbWorldArea("Prisoner's Gate")