
require("mycmd")
require("���Ľ�ɫ��֧��")
s_cmncfg = s_cmncfg

-----------------------------
AddMapRoomRate("�ӵ�", 1000)
AddMapRoomRate("ˮ���ż�", 1100)
AddMapRoomRate("�ϲ���Ȩ֮��", 1100)
AddMapRoomRate("���׸��޵Ĳ���", 1100)
AddMapRoomRate("�̵�", 1300)
AddMapRoomRate("����֮��", 1300)
AddMapRoomRate("�������� 1 ��", 1300)
AddMapRoomRate("�������� 2 ��", 1300)
AddMapRoomRate("Ѧ��֮��", 1200)

-----------------------------
SetMapAreaInfo("����֮���ϲ�", { "��������", "����֮���ϲ�", "�������ķ���" })
SetMapAreaInfo("Թ��֮���", { "Īޱ���ĳ�Ѩ","¥��","ͨ��"})
SetMapAreaInfo("�󾺼���", { "������", "ͨ��", "����֮��" })
SetMapAreaInfo("�Ž�����", { "¥��", "����������" })
SetMapAreaInfo("��Ӱ��� 2 ��", {"������"})
SetMapAreaInfo("����֮��", {"����֮��","����֮��"})
SetMapAreaInfo("��Ȩ֮��", {"¥��"})
SetMapAreaInfo("�ϲ���Ȩ֮��", {"¥��","��Ȩ֮��(����)"})
SetMapAreaInfo("֯���߳�Ѩ", {"֯���߳�Ѩ"})
SetMapAreaInfo("��ķ�ı���", {"����֮��","��ķ�ı���"})
--
SetMapAreaInfo("����ʥ��", {"����ʥ��"})
--
SetMapAreaInfo("����ö�¥", {"����֮��"})
--
SetMapAreaInfo("��³Ҫ��", {"��³Ҫ��"})
--
SetMapAreaInfo("Ѧ��֮��", {"¥��","����֮��(����)"}) --"�������ķ���"
--
SetMapAreaInfo("��������", {"������ɽ��","������֮��","�ɻ���ɽ��"})
--
SetMapAreaInfo("ʪ��", {"�������ķ���"})
--
SetMapAreaInfo("����֮���ĺ���", {"��������"})
--
SetMapAreaInfo("�ž���Ĺ", {"¥��"})
--
SetMapAreaInfo("���׸��޵Ĳ���", {"���׸��޵Ĺ�����"})
--
SetMapAreaInfo("��ԭ", {"��ɭ��Ӫ��"})
--
SetMapAreaInfo("׹��֮�� 1 ��", {"¥��"})
--  
SetMapAreaInfo("׹��֮�� 2 ��", {"¥��","���������ľ���"})
--  
SetMapAreaInfo("�漣֮ǽ", {"¥��"})
--  
SetMapAreaInfo("�������", {"������"})
--  
SetMapAreaInfo("��Ӱ��� 2 ��", {"������"})
--  
SetMapAreaInfo("��ҫ��� 2 ��", {"������"})
--  
SetMapAreaInfo("б��", {"̧��ͨ��"})
--  
SetMapAreaInfo("������", {"������"})
--  
SetMapAreaInfo("ʥ�ý���ʵ����", {"¥��"})
--  
SetMapAreaInfo("�������ˮ��", {"���͹�¯"})
--  
SetMapAreaInfo("��ת��ͷ", {"������"})
--
SetMapAreaInfo("���廨԰", {"�־�֮��"})
--SetMapAreaInfo("���ö�¥", {"����֮��"})

-----------------------------

local tp = GetDefTerrainParser()
--���͵�
tp:AddAny(enTerrainParserFlag.kTPF_ObjDbPath, "���͵�", "Metadata/Effects/Environment/waypoint/new/")

--������̲
--->ʨ������
tp:AddMap("������̲", "ʨ������", "Art/Models/Terrain/Beach/areatransitions/southentrance/beachtown_south_entrance_c2r2.tgt")

--ĺ�⺣̲
--->��������
tp:AddMap("ĺ�⺣̲", "��������", "Art/Models/Terrain/Beach/areatransitions/toswamp/act6_area2_transition_v01_01_c3r1.tgt")
--NPC��ɯ
tp:AddMap("ĺ�⺣̲", "��ɯ", "Art/Models/Terrain/Beach/areatransitions/beachtowatercave_v2/Beach_to_watercave_v2_c3r5.tgt")

--��������
--��ˮ��
tp:AddMap("��������", "��ˮ��", "Art/Models/Terrain/Beach/areatransitions/swamp2/beach_toswamp2_v01_01_c6r4.tgt")
--������Ѩ
tp:AddMap("��������", "������Ѩ", "Art/Models/Terrain/Beach/areatransitions/beachtowatercave_v2/Beach_to_watercave_v2_c3r2.tgt")
-->���ŵ��Ƶ����ǽ��
tp:AddMap("��������", "���ŵ��Ƶ����ǽ��", "Art/Models/Terrain/Beach/areatransitions/beachtowateracave/Beach_to_watercave_c2r6.tgt")
-->��ɯ
tp:AddMap("��������", "��ɯ", "Art/Models/Terrain/Beach/areatransitions/beachtowatercave_v2/Beach_to_watercave_v2_c3r5.tgt")
-->��³Ҫ��
tp:AddMap("��������", "��³Ҫ��", "Art/Models/Terrain/Beach/areatransitions/swamp_radiantpool/beach_karuipools_v01_01_c6r3.tgt")
-->Fortress Gate
tp:AddMap("��������", "The Karui Fortress", "Art/Models/Terrain/Beach/areatransitions/swamp_radiantpool/beach_karuipools_v01_01_c6r3.tgt")
-->Fortress Gate
tp:AddMap("��������", "Fortress Gate", "Art/Models/Terrain/Beach/areatransitions/swamp_radiantpool/beach_karuipools_v01_01_c6r3.tgt")


--������Ѩ
-->��������
tp:AddMap("������Ѩ", "��������", "Art/Models/Terrain/CaveDungeon/cave_exit_v01_01_c2r2.tgt")
-->ˮ��֮Ԩ
tp:AddMap("������Ѩ", "ˮ��֮Ԩ", "Art/Models/Terrain/CaveDungeon/watery_depth_entrance_v01_01_c1r1.tgt")
-->���ź���
tp:AddMap("������Ѩ", "���ź���", "Art/Models/Terrain/CaveDungeon/caveup_exit_v01_01_c2r3.tgt")

--ˮ��֮Ԩ
-->������Ѩ
tp:AddMap("ˮ��֮Ԩ", "������Ѩ", "Art/Models/Terrain/CaveDungeon/caveup_exit_v01_01_c2r3.tgt")

--���ź���
-->������Ѩ
tp:AddMap("���ź���", "������Ѩ", "Art/Models/Terrain/Beach/CaveEntrances/beachcaveentrance_v01_01_c2r4.tgt")
-->����ɽ��
tp:AddMap("���ź���", "����ɽ��", "Art/Models/Terrain/Beach/areatransitions/passageway/beach_passageway_v01_01_c3r3.tgt")

--����ɽ��
-->���ź���
tp:AddMap("����ɽ��", "���ź���", "Art/Models/Terrain/Beach/areatransitions/passageway/beach_passageway_v01_01_c3r3.tgt")
-->����֮���²�
tp:AddMap("����ɽ��", "����֮���²�", "Art/Models/Terrain/Beach/Prison/beach_prisonback_c6r4.tgt")

--����֮���²�
-->����ɽ��
tp:AddMap("����֮���²�", "����ɽ��", "Art/Models/Terrain/PrisonDungeon/dungeon_prison_wall_straight_hole_v01_01_c1r1.tgt")
-->����֮���ϲ�
tp:AddMap("����֮���²�", "����֮���ϲ�", "Art/Models/Terrain/PrisonDungeon/dungeon_prison_exit_up_v01_01_c1r1.tgt")
-->����������
tp:AddMap("����֮���²�", "��������", "Art/Models/Terrain/PrisonDungeon/prison_trial_door_v01_01_c1r1.tgt")
-->Trial of Ascendancy Plaque
--tp:AddMapArea("The Lower Prison", "Trial of Ascendancy Plaque", "Art/Models/Terrain/PrisonDungeon/dungeon_prison_stairs_convex_v01_01.tgt", {{"Art/Models/Terrain/PrisonDungeon/dungeon_prison_floor_height_lower_v01_03.tgt", 47}})
-->����
tp:AddMap("����֮���²�", "����", "Art/Models/Terrain/PrisonDungeon/dungeon_prison_fence_crevice_thickwall_v01_01.tgt")
-->Ѧ��֮��
tp:AddMap("����֮���²�", "Ѧ��֮��", "Art/Models/Terrain/PrisonDungeon/areatransitions/shavronne_prison_door_up_v01_01_c2r2.tgt")

--Ѧ��֮��
tp:AddMap("Ѧ��֮��", "������Ѧ��", "Art/Models/Terrain/PrisonDungeon/areatransitions/tower_spiral_stair_v01_01_c3r1.tgt")


--����֮���ϲ�  (��С��ͼ)
-->����֮���²�
tp:AddMap("����֮���ϲ�", "����֮���²�", "Art/Models/Terrain/PrisonDungeon/dungeon_prison_entrance_down_v01_01_c1r3.tgt")

--��������
-->��Ӱ��Ĺ
tp:AddMap("��������", "��Ӱ��Ĺ", "Art/Models/Terrain/Beach/areatransitions/passagewaytoshipgraveyard/shipgraveyard_passageway_v01_01_c4r3.tgt")
--����Ͽ�֮ӡ
tp:AddMap("��������", "����Ͽ�֮ӡ", "Art/Models/Terrain/Beach/areatransitions/spikepassage/beach_passageblock_v01_01_c2r2.tgt")
--��������
tp:AddMap("��������", "��������", "Art/Models/Terrain/Beach/areatransitions/spikepassage/beach_passageblock_v01_01_c5r3.tgt")

--��Ӱ��Ĺ
-->��Ӱ��Ĺ��Ѩ
tp:AddMap("��Ӱ��Ĺ", "��Ӱ��Ĺ��Ѩe", "Art/Models/Terrain/Beach/areatransitions/shipgraveyard_dungeon/ship_entrance_v01_01_c3r5.tgt")
-->Թ��֮��
--tp:AddMap("��Ӱ��Ĺ", "Թ��֮��", "Art/Models/Terrain/Beach/areatransitions/beachtoendcave/beach_caveentranceskeleton_v01_01_c7r6.tgt")
--�Ѷ�����
tp:AddMap("��Ӱ��Ĺ", "�Ѷ�����", "Art/Models/Terrain/Beach/QuestLocations/shipwreck_quest_v01_01_c7r8.tgt")

--Թ��֮��
-->Թ��֮���
--tp:AddMap("Թ��֮��", "Թ��֮���", "Art/Models/Terrain/CaveDungeon/caveup_exit_v01_01_c2r3.tgt")

--�ϲ�ɭ��
-->ɭ��Ӫ��iiiiiiiiiiiiiiiiii
tp:AddMap("�ϲ�ɭ��", "ɭ��Ӫ��", "Art/Models/Terrain/ForestTown/forestcamp_dock_v01_01_c2r4.tgt")
--Թ��֮���
tp:AddMap("�ϲ�ɭ��", "Թ��֮���", "Art/Models/Terrain/Forest/areatransitions/forest_caveentrance_v01_01_c2r4.tgt")

--�ӵ�
-->ʪ��
tp:AddMap("�ӵ�", "ʪ��", "Art/Models/Terrain/Forest/areatransitions/bridgeconnection_v01_01_c2r2.tgt")
-->�ϲ�ɭ��
tp:AddMap("�ӵ�", "�ϲ�ɭ��", "Art/Models/Terrain/ForestTown/forest_to_river_v01_01_c5r2.tgt")


--ǰ��ԭҰ
-->ɭ��Ӫ��
tp:AddMap("ǰ��ԭҰ", "ɭ��Ӫ��t", "Art/Models/Terrain/ForestTown/forestcamp_right_v01_01_c3r3.tgt")
-->��Ѩ
tp:AddMap("ǰ��ԭҰ", "��Ѩ", "Art/Models/Terrain/ForestCave/forestcave_entrance_hole_v01_01_c1r1.tgt")
-->Σ����·
tp:AddMap("ǰ��ԭҰ", "Σ����·", "Art/Models/Terrain/Forest/areatransitions/wall_gate_v01_01_c2r2.tgt")

--Σ����·
-->ǰ��ԭҰ
tp:AddMap("Σ����·", "ǰ��ԭҰ", "Art/Models/Terrain/Forest/areatransitions/wall_gate_v01_01_c2r2.tgt")
-->����֮�� 1 ��
tp:AddMap("Σ����·", "����֮�� 1 ��", "Art/Models/Terrain/Forest/areatransitions/temple_entrance_v01_01_c2r5.tgt")
-->����ż� 
tp:AddMap("Σ����·", "����ż�", "Art/Models/Terrain/Forest/areatransitions/wall_gate_v01_01_c2r2.tgt")
-->���϶���
tp:AddMap("Σ����·", "���϶���", "Art/Models/Terrain/Forest/areatransitions/bridgeconnection_v01_01_c2r2.tgt")

--����֮�� 1 ��
-->Σ����·
tp:AddMap("����֮�� 1 ��", "Σ����·", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_entrance_v01_01_c1r1.tgt")
-->����֮��:�� 2 ��
tp:AddMap("����֮�� 1 ��", "����֮�� 2 ��", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_exit_down_v01_01_c2r3.tgt")
-->��ͼװ��
tp:AddMap("����֮�� 1 ��", "��ͼװ��", "Art/Models/Terrain/Doodads/TempleDungeon/temple_maporrery4_c1r2.tgt")
-->���׸��޵Ĳ���
tp:AddMap("����֮�� 1 ��", "���׸��޵Ĳ���", "Art/Models/Terrain/Doodads/TempleDungeon/temple_maporrery4_c1r2.tgt")


--����֮��:�� 2 ��
-->����֮��:�� 1 ��
tp:AddMap("����֮�� 2 ��", "����֮�� 1 ��", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_exit_up_v01_01_c1r2.tgt")
-->Trial of Ascendancy
tp:AddMap("����֮��:�� 2 ��", "Trial of Ascendancy", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_labyrinth_door_thin_corridor_v01_03_c1r1.tgt")
--Trial of Ascendancy Plaque
tp:AddMapArea("����֮��:�� 2 ��", "Trial of Ascendancy Plaque", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_stairs_straight_v02_02.tgt", {{"Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_crevice_corner_concave_v01_01.tgt", 53}})
-->����ͨ��
tp:AddMap("����֮�� 2 ��", "����ͨ��", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_maligaro_passage_c1r1.tgt")
-->��Ѩ
tp:AddMap("����֮�� 2 ��", "��Ѩ", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_maligaro_passage_c1r1.tgt")

--��Ѩ
tp:AddMap("��Ѩ", "��ԭ", "Art/Models/Terrain/ForestCave/forestcaveup_exit_v01_01_c2r3.tgt")

--��ԭ
tp:AddMap("��ԭ", "��ɭ��Ӫ��", "Art/Models/Terrain/ForestTown/oldfields_campboss_v01_01_c8r5.tgt")

--����ż�
-->Σ����·
tp:AddMap("����ż�", "Σ����·", "Art/Models/Terrain/Forest/areatransitions/wall_gate_v01_01_c2r2.tgt")
-->�ž���Ĺ 1 ¥
tp:AddMap("����ż�", "�ž���Ĺ 1 ¥", "Art/Models/Terrain/Forest/ChurchRuin/church_dungeon_entrance_v01_01_c2r2.tgt")
-->�ž���Ĺ
tp:AddMap("����ż�", "�ž���Ĺ", "Art/Models/Terrain/Forest/ChurchRuin/church_dungeon_entrance_v01_01_c2r2.tgt")

--�ž���Ĺ 1 ¥
-->�ž���Ĺ 2 ¥
tp:AddMap("�ž���Ĺ 1 ¥", "�ž���Ĺ 2 ¥", "Art/Models/Terrain/ChurchDungeon/dungeon_church_exit_down_v01_01_c1r1.tgt")
-->Trial of Ascendancy
tp:AddMap("�ž���Ĺ 1 ¥", "Trial of Ascendancy", "Art/Models/Terrain/ChurchDungeon/labyrinth_church_door_v01_01_c2r1.tgt")
-->Lever
tp:AddMap("�ž���Ĺ 1 ¥", "Lever", "Art/Models/Terrain/ChurchDungeon/dungeon_church_wall_corner_convex_crevice_v01_01.tgt")
-->Trial of Ascendancy Plaque
tp:AddMap("�ž���Ĺ 1 ¥", "Trial of Ascendancy Plaque", "Art/Models/Terrain/ChurchDungeon/dungeon_church_stairs_straight_feature_v01_01.tgt")


--�ž���Ĺ 2 ¥
-->�ž���Ĺ 1 ¥
tp:AddMap("�ž���Ĺ 2 ¥", "�ž���Ĺ 1 ¥", "Art/Models/Terrain/ChurchDungeon/dungeon_church_exit_up_v01_01_c1r1.tgt")
--��̳
tp:AddMap("�ž���Ĺ 2 ¥", "�ƽ�֮��", "Art/Models/Terrain/ChurchDungeon/dungeon_church_relic_altar_v01_01_c1r2.tgt")

--���϶���
-->Σ����·
tp:AddMap("���϶���", "Σ����·", "Art/Models/Terrain/Forest/areatransitions/bridgeconnection_v01_01_c2r2.tgt")

--��������
-->�ӵ�
tp:AddMap("��������", "�ӵ�", "Art/Models/Terrain/Forest/areatransitions/roadtothickforest_entrance_v01_01_c6r2.tgt")
-->֯���߳�Ѩ
tp:AddMap("��������", "֯���߳�Ѩ", "Art/Models/Terrain/Forest/areatransitions/spidergrove_entrance_v01_01_c4r2.tgt")
-->������
tp:AddMap("��������", "������", "Art/Models/Terrain/Forest/Trees/treewitch_camp_v01_02_c7r6.tgt")

--�߶�����
-->ʪ��
tp:AddMap("�߶�����", "ʪ��", "Art/Models/Terrain/IncaDungeon/dungeon_inca_exit_v01_01_c1r2.tgt")
-->��������(�д���֤)
--tp:AddMap("�߶�����", "��������", "Art/Models/Terrain/IncaDungeon/dungeon_bossrelease_v01_01_c2r1.tgt")

--��������
-->�߶�����
--tp:AddMap("��������", "�߶�����", "Art/Models/Terrain/Forest/areatransitions/forest_caveexit_inca_v01_01_c2r5.tgt")
--��������
tp:AddMap("��������", "��������", "Art/Models/Terrain/Forest/areatransitions/grovewall_entrance_v01_01_c1r2.tgt")
--�ٲ���Ѩ
tp:AddMap("��������", "�ٲ���Ѩ", "Art/Models/Terrain/Forest/areatransitions/waterfall_cave_entrance_v01_01_c2r4.tgt")
--�̵�
tp:AddMap("��������", "�̵�", "Art/Models/Terrain/Forest/areatransitions/city/forestriver_plinthtransition_v01_01_c6r2.tgt")

--ʪ��
-->�߶�����
tp:AddMap("ʪ��", "�߶�����", "Art/Models/Terrain/Forest/areatransitions/forest_caveentrance_inca_v01_01_c2r5.tgt")
-->�ӵ�
tp:AddMap("ʪ��", "�ӵ�", "Art/Models/Terrain/Forest/areatransitions/bridgeconnection_v01_01_c2r2.tgt")
-->ŷ�� 
tp:AddMap("ʪ��", "ŷ��", "Art/Models/Terrain/Forest/OaksCamp/cliffpathconnection_gate_v01_01_c1r1.tgt")
--����
tp:AddMap("ʪ��", "����", "Art/Models/Terrain/Forest/areatransitions/forest_caveentrance_inca_v01_01_c2r5.tgt")


--��������
-->��������
tp:AddMap("��������", "��������", "Art/Models/Terrain/Grove/grove_wall_exit_v01_01_c2r2.tgt")

--�ٲ���Ѩ
-->��������
tp:AddMap("�ٲ���Ѩ", "��������", "Art/Models/Terrain/ForestCave/forestcavedown_exit_v01_01_c2r3.tgt")
-->�Ž�����
tp:AddMap("�ٲ���Ѩ", "�Ž�����", "Art/Models/Terrain/IncaDungeon/dungeon_stairs_up_v01_01_c1r2.tgt")

--�Ž�����
-->�ٲ���Ѩ
tp:AddMap("�Ž�����", "�ٲ���Ѩ", "Art/Models/Terrain/IncaDungeon/dungeon_stairs_down_v01_01_c1r2.tgt")
-->�����Ƿ���
tp:AddMap("�Ž�����", "�����Ƿ���", "Art/Models/Terrain/IncaDungeon/dungeon_huangdoor_v01_01_c3r2.tgt")

--�����Ƿ���
-->����Ӫ��
tp:AddMap("�����Ƿ���", "����Ӫ��", "Art/Models/Terrain/Act3/AreaTransitions/act3_docks_to_town_lower_01_01_c3r3.tgt")

--����Ӫ��
-->�����Ƿ��� 
tp:AddMap("����Ӫ��", "�����Ƿ��� ", "Art/Models/Terrain/Act3Town/Act3_town_01_01_c12r21.tgt")
-->ƶ���
tp:AddMap("����Ӫ��", "ƶ���", "Art/Models/Terrain/Act3Town/Act3_town_01_01_c21r7.tgt")
-->The Lord's Labyrinth
tp:AddMap("����Ӫ��", "The Lord's Labyrinth", "Art/Models/Terrain/Act3Town/Act3_town_01_01_c8r8.tgt")

--The Crypt
tp:AddMap("The Crypt", "Trial of Ascendancy Plaque", "Art/Models/Terrain/ChurchDungeon/dungeonchurch_fence_crevice_wallthick_v02_01.tgt")
--Trial of Ascendancy
tp:AddMap("The Crypt", "Trial of Ascendancy", "Art/Models/Terrain/ChurchDungeon/labyrinth_church_door_v01_01_c1r1.tgt")


--ƶ���
-->����Ӫ��
tp:AddMap("ƶ���", "����Ӫ��", "Art/Models/Terrain/Act3/AreaTransitions/act3_to_slums_area_transition_c5r4.tgt")
-->��ˮ��
tp:AddMap("ƶ���", "��ˮ��", "Art/Models/Terrain/Act3/AreaTransitions/slum_sewer_entrance_v02_01.tgt")
-->���᳡
tp:AddMap("ƶ���", "���᳡", "Art/Models/Terrain/Act3/AreaTransitions/act3_prison_entrance_01_01_c2r3.tgt")

--���᳡
-->ƶ���
tp:AddMap("���᳡", "ƶ���", "Art/Models/Terrain/PrisonDungeon/dungeon_prison_exit_up_v01_01_c1r1.tgt")
-->�ж���(Ŀ��)
--tp:AddMap("���᳡", "�ж���", "Art/Models/Terrain/quest_marker.tgt")
-->Trial of Ascendancy
tp:AddMap("���᳡", "Trial of Ascendancy", "Art/Models/Terrain/PrisonDungeon/prison_trial_door_v01_01_c2r1.tgt")
-->Trial of Ascendancy Plaque
tp:AddMap("���᳡", "Trial of Ascendancy Plaque", "Art/Models/Terrain/PrisonDungeon/dugeon_prison_lava_fence_concave_v01_01.tgt")

--��ˮ��
-->ƶ���
tp:AddMap("��ˮ��", "ƶ���", "Art/Models/Terrain/Act3/Sewers/sewerwall_exit_v01_01_c1r1.tgt")
-->�м��ش�
tp:AddMap("��ˮ��", "�м��ش�", "Art/Models/Terrain/Act3/Sewers/sewerwall_exit_v01_01_c1r1.tgt")
-->����������Ӫu
tp:AddMap("��ˮ��", "����������Ӫ", "Art/Models/Terrain/Act3/AreaTransitions/sewerexit_v01_01_c3r1.tgt")

--�м��ش�
-->�ֿ�ش�
tp:AddMap("�м��ش�", "�ֿ�ش�", "Art/Models/Terrain/Act3/Sewers/sewerwall_exit_v01_01_c1r1.tgt")
-->��ʯ��Ĺ()
tp:AddMap("�м��ش�", "��ʯ��Ĺ", "Art/Models/Terrain/Act3/AreaTransitions/markettochurchdungeon_v01_01_c3r2.tgt")
-->��ˮ��
tp:AddMap("�м��ش�", "��ˮ��", "Art/Models/Terrain/Act3/AreaTransitions/slum_sewer_entrance_v02_01.tgt")
-->��ս�㳡()
tp:AddMap("�м��ش�", "��ս�㳡", "Art/Models/Terrain/Act3/AreaTransitions/market_to_battlefront_v01_01_c5r6.tgt")

--��ʯ��Ĺ
-->�м��ش�
tp:AddMap("��ʯ��Ĺ", "�м��ش�", "Art/Models/Terrain/ChurchDungeon/dungeon_church_exit_up_v01_01_c1r1.tgt")
-->Trial of Ascendancy
tp:AddMap("��ʯ��Ĺ", "Trial of Ascendancy", "Art/Models/Terrain/ChurchDungeon/labyrinth_church_door_v01_01_c2r1.tgt")
-->Trial of Ascendancy
tp:AddMap("��ʯ��Ĺ", "Trial of Ascendancy Plaque", "Art/Models/Terrain/ChurchDungeon/dungeon_church_floor_height_convex_stairs_v01_02.tgt")

--��ս�㳡
-->�м��ش�
tp:AddMap("��ս�㳡", "�м��ش�", "Art/Models/Terrain/Act3/AreaTransitions/market_to_battlefront_v01_01_c5r6.tgt")
-->��ҫ���� 1 ��(The Solaris Temple Level 1)
tp:AddMap("��ս�㳡", "��ҫ��� 1 ��", "Art/Models/Terrain/Act3/IvoryTemple/act3_temple_entrance_v01_01_c3r2.tgt")
-->���ຣ��()
tp:AddMap("��ս�㳡", "���ຣ��", "Art/Models/Terrain/Act3/Battlefield/battlefield_arch_v01_03_c2r4.tgt")
-->The Harbour Bridge
tp:AddMap("��ս�㳡", "The Harbour Bridge", "Art/Models/Terrain/Act3/AreaTransitions/battlefronttobarracks/act3_battlefront_to_harbor_v01_01_c2r3.tgt")

--��ҫ���� 1 ��
-->��ս�㳡
tp:AddMap("��ҫ��� 1 ��", "��ս�㳡", "Art/Models/Terrain/Act3/AreaTransitions/temple_to_battlefront_v01_01_c3r3.tgt")
-->��ҫ���� 2 ��
tp:AddMap("��ҫ��� 1 ��", "��ҫ��� 2 ��", "Art/Models/Terrain/TempleDungeon/templeclean_exit_down_v01_01_c1r3.tgt")
---->The Battlefront(��The Imperial Fieldsһ��)
--tp:AddMap("The Solaris Temple Level 1", "The Battlefront", "Art/Models/Terrain/Act3/AreaTransitions/temple_to_battlefront_v01_01_c3r3.tgt")

--���ຣ��()
-->��ս�㳡
tp:AddMap("���ຣ��", "��ս�㳡", "Art/Models/Terrain/Act3/Battlefield/battlefield_arch_v01_02_c2r4.tgt")
--װ��ǵ�����
tp:AddMap("���ຣ��", "����Ͽ�������", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_questcart.tgt")
--�Ѷ�����
tp:AddMap("���ຣ��", "�Ѷ�����", "Art/Models/Terrain/Act3/citywaypoint_v01_01_c2r1.tgt")

--��ҫ���� 2 ��
-->��ҫ���� 1 ��
tp:AddMap("��ҫ��� 2 ��", "��ҫ��� 1 ��", "Art/Models/Terrain/TempleDungeon/templeclean_exit_up_v01_02_c3r1.tgt")
-->��������
tp:AddMap("��ҫ��� 2 ��", "��������", "Art/Models/Terrain/TempleDungeon/gemling_queen_throne_v01_01_c2r3.tgt")
-->The Sun Orb (��Ʒλ��)
--tp:AddMap("��ҫ��� 2 ��", "Sun Orb", "Art/Models/Terrain/TempleDungeon/gemling_queen_throne_v01_01_c3r3.tgt")
-->������
tp:AddMap("��ҫ��� 2 ��", "������", "Art/Models/Terrain/TempleDungeon/gemling_queen_throne_v01_01_c2r3.tgt")

--����������Ӫ
-->��ˮ��
tp:AddMap("����������Ӫ", "��ˮ��", "Art/Models/Terrain/Act3/AreaTransitions/battlefield_to_sewer_stairs_v01_01_c3r2.tgt")
-->��Ӱ��� 1 ��
tp:AddMap("����������Ӫ", "��Ӱ��� 1 ��", "Art/Models/Terrain/Act3/IvoryTemple/act3_temple_entrance_v01_01_c3r2.tgt")
-->�ʼһ�԰
tp:AddMap("����������Ӫ", "�ʼһ�԰", "Art/Models/Terrain/Act3/Gardens/garden_arch_v01_01_c2r5.tgt")
-->The Harbour Bridge
tp:AddMap("����������Ӫ", "The Harbour Bridger", "Art/Models/Terrain/Act3/AreaTransitions/battlefronttobarracks/act3_riverbridge_transition_v01_01_c9r7.tgt")

-->��Ӱ��� 1 ��
tp:AddMap("��Ӱ��� 1 ��", "��Ӱ��� 2 ��", "Art/Models/Terrain/TempleDungeon/templeclean_exit_down_v01_01_c1r3.tgt")

--�ʼһ�԰
-->����������Ӫ
tp:AddMap("�ʼһ�԰", "����������Ӫ", "Art/Models/Terrain/Act3/Gardens/garden_arch_v01_01_c2r5.tgt")
-->�����Թ�(The Hedge Maze)
tp:AddMap("�ʼһ�԰", "�����Թ�", "Art/Models/Terrain/Act3/Gardens/walls/garden_wall_entrance_v01_01_c2r2.tgt")
-->ͼ���
tp:AddMap("�ʼһ�԰", "ͼ���", "Art/Models/Terrain/Act3/Library/Library_LargeBuilding_entrance_v01_01_c2r3.tgt")
-->��Ȩ֮��
tp:AddMap("�ʼһ�԰", "��Ȩ֮��", "Art/Models/Terrain/Act3/AreaTransitions/Act3_EpicDoor_v02_01_c7r7.tgt")
-->��������
tp:AddMap("�ʼһ�԰", "��������", "Art/Models/Terrain/Act3/AreaTransitions/Act3_EpicDoor_v02_01_c7r7.tgt")

--�����Թ�
-->�ʼһ�԰
tp:AddMap("�����Թ�", "�ʼһ�԰", "Art/Models/Terrain/Act3/Gardens/walls/garden_wall_entrance_v01_01_c2r2.tgt")
-->÷��
--tp:AddMap("�����Թ�", "÷��", "Art/Models/Terrain/Act3/Gardens/fruittree_c2r2.tgt")
-->Trial of Ascendancy
tp:AddMap("The Hedge Maze", "Trial of Ascendancy", "Art/Models/Terrain/Act3/Gardens/walls/garden_labyrinth_gate_v02_02_c1r2.tgt")
--Trial of Ascendancy Plaque(������С�� һ�¾��ܱ�����)

--ͼ���
-->�ʼһ�԰
tp:AddMap("ͼ���", "�ʼһ�԰", "Art/Models/Terrain/Act3/Library/library_entrance_v01_01_c2r3.tgt")
-->������
tp:AddMap("ͼ���", "������", "Art/Models/Terrain/Act3/Library/library_entrance_v02_01_c2r3.tgt")

--������
-->ͼ���
tp:AddMap("������", "ͼ���", "Art/Models/Terrain/Act3/Library/library_entrance_v03_01_c2r3.tgt")

--ˮ���ż�
-->ͳ����֮��
tp:AddMap("ˮ���ż�", "ͳ����֮��", "Art/Models/Terrain/Act4/Town/AqueductConnection/mountiantown_connection_c7r13.tgt")

--��ڿ��:�� 1 ��
-->ͳ����֮��
tp:AddMap("��ڿ��:�� 1 ��", "ͳ����֮��", "Art/Models/Terrain/Act4/mine/mine_areatransition_entrance_v01_01_c3r4.tgt")
-->��ڿ��:�� 2 ��
tp:AddMap("��ڿ��:�� 1 ��", "��ڿ��:�� 2 ��", "Art/Models/Terrain/Act4/mine/mine_areatransition_v01_01_c1r2.tgt")

--��ڿ�ӣ��� 2 ��
-->ˮ������
tp:AddMap("��ڿ��:�� 2 ��", "ˮ������", "Art/Models/Terrain/Act4/mine/mine_areatransition_v03_01_c1r2.tgt")
-->��ڿ�ӣ��� 1 ��
tp:AddMap("��ڿ��:�� 2 ��", "��ڿ��:�� 1 ��", "Art/Models/Terrain/Act4/mine/mine_areatransition_v02_02_c1r2.tgt")

--ˮ������
-->��ڿ�ӣ��� 2 ��
tp:AddMap("ˮ������", "��ڿ��:�� 2 ��", "Art/Models/Terrain/Act4/mine/mine_areatransition_v04_01_c1r2.tgt")
-->��ķ�Ļþ�
tp:AddMap("ˮ������", "��ķ�Ļþ�", "Art/Models/Terrain/Act4/mine/crystals_openAnimation_v01_01_c1r3.tgt")
-->�������Ļþ�
tp:AddMap("ˮ������", "�������Ļþ�", "Art/Models/Terrain/Act4/mine/crystals_openAnimation_v01_01_c5r3.tgt")
-->����֮������ 1 ��
tp:AddMap("ˮ������", "����֮��:�� 1 ��", "Art/Models/Terrain/Act4/mine/crystals_openAnimation_v01_01_c3r2.tgt")

--��ķ�Ļþ�
-->ˮ������ -14
--tp:AddMap("��ķ�Ļþ�", "The Crystal Veins", "Art/Models/Terrain/Act4/LavaPlateau/KaomTiles/lava_abyss_v02_01_c3r1.tgt")
-->��ķ�ı���
tp:AddMap("��ķ�Ļþ�", "��ķ�ı���", "Art/Models/Terrain/Act4/LavaPlateau/AreaTransition/lava_abyss_transition_entrance_v01_01_c3r1.tgt")

--��ķ�ı���
-->��ķ�Ļþ�
tp:AddMap("��ķ�ı���", "��ķ�Ļþ�", "Art/Models/Terrain/Act4/LavaPlateau/AreaTransition/lava_kaom3_transition_entrance_v02_01_c2r1.tgt")
--����֮��
tp:AddMap("��ķ�ı���", "����֮��", "Art/Models/Terrain/Act4/LavaPlateau/AreaTransition/lava_lake_throne_room_v01_01_c2r2.tgt")

--�������Ļþ�
-->ˮ������ -22
--tp:AddMap("�������Ļþ�", "The Crystal Veins", "Art/Models/Terrain/Act4/Arena/arena_wall_v02_02.tgt")
-->�󾺼���
tp:AddMap("�������Ļþ�", "�󾺼���", "Art/Models/Terrain/Act4/Arena/AreaTransition/arena_areatransition_v01_01_c1r2.tgt")

-->��������
tp:AddMap("��������", "����Ī������", "Art/Models/Terrain/Forest/Feature/forest_azmeri_shrine_c2r1.tgt")

--����֮��(The Harvest)
-->����֮������ 2 ��
tp:AddMap("����֮��", "����֮�� 2 ��", "Art/Models/Terrain/Act4/Belly/Harvest_tunnel_v01_01_c2r3.tgt")
-->����֮��
tp:AddMap("����֮��", "����֮��", "Art/Models/Terrain/Act4/Belly/Taster/TasterMouth_openAnimation_v01_01_c2r2.tgt")

--������֮��
tp:AddMap("������֮��", "���Ϳ���", "Art/Models/Terrain/Act4/Ascent/Feature/ascent_summit_v01_01_c4r3.tgt")

--ū�����
tp:AddMap("ū�����", "����֮��", "Art/Models/Terrain/Act5/Tower/tower_v01_01_c9r4.tgt")
--�๤ͷ����
tp:AddMap("ū�����", "�๤ͷ����", "Art/Models/Terrain/Act5/Tower/tower_v01_01_c9r4.tgt")

--������
tp:AddMap("������", "�����ǹ㳡", "Art/Models/Terrain/Act5/Area Transitions/security_exit_v01_01_c1r5.tgt")
tp:AddMap("������", "���г���˹���˹", "Art/Models/Terrain/Act5/SlavePen/slave_crater_v01_01_c2r1.tgt")
tp:AddMap("������", "�����ǹ㳡", "Art/Models/Terrain/Act5/Area Transitions/security_exit_v01_01_c1r5.tgt")

--�����ǹ㳡
tp:AddMap("�����ǹ㳡", "ʥ�ø�ͥ", "Art/Models/Terrain/Act5/Area Transitions/Oriath_AreaTransition_v01_03_c2r2.tgt")

--ʥ�ø�ͥ
tp:AddMap("ʥ�ø�ͥ", "����ʥ��", "Art/Models/Terrain/Act5/Templar Court/templar_to_innocents_v01_01_c2r1.tgt")

--����ʥ��
-->����ʥ��(С����)
tp:AddMap("����ʥ��", "����ʥ��", "Art/Models/Terrain/Act5/Innocence/transition_chamber_to_boss_v01_01_c4r4.tgt")
-->��Ϊ�𺣵ĸ�ͥ
tp:AddMap("����ʥ��", "�����𺣵ĸ�ͥ", "Art/Models/Terrain/Act5/Innocence/transition_chamber_to_courts_v01_01_c3r4.tgt")

--��Ϊ�𺣵ĸ�ͥ
tp:AddMap("�����𺣵ĸ�ͥ", "�㳡�ż�", "Art/Models/Terrain/Act5/Templar Court/templar_oriath_transition_v01_01_c2r1.tgt")

--�ع���
tp:AddMap("�ع���", "�㳡�ż�", "Art/Models/Terrain/Act5/Area Transitions/Ossuary_abyss_transition_v01_01_c1r2.tgt")

--�㳡�ż�
tp:AddMap("�㳡�ż�", "����ʥ��", "Art/Models/Terrain/Act5/OriathSquare/Oriath_AreaTransition_v01_04_c2r2.tgt")
tp:AddMap("�㳡�ż�", "����ʥ��", "Art/Models/Terrain/Act5/OriathSquare/Oriath_AreaTransition_v01_02_c2r2.tgt")
tp:AddMap("�㳡�ż�", "����ö�¥", "Art/Models/Terrain/Act5/OriathSquare/ChitusTiles/chitus_statuewall_transition_v01_01_c1r3.tgt")

--���ö�¥
tp:AddMap("���ö�¥", "����֮��", "Art/Models/Terrain/Act5/CathedralRoof/boss/cathedralroof_boss_area_v02_01_c5r10.tgt")

--��³Ҫ��
tp:AddMap("��³Ҫ��", "��Ĭɽ��", "Art/Models/Terrain/Beach/areatransitions/toridge/swamp_to_ridge_v01_01_c5r3.tgt")

--��Ĭɽ��
tp:AddMap("��Ĭɽ��", "����֮���²�", "Art/Models/Terrain/PrisonDungeon/areatransitions/ledge_prisonback_c5r3.tgt")

--�µ����� --Art/Models/Terrain/Act3/Beacon/beacon_stairs_v01_01_c2r1.tgt
tp:AddMap("�µ�����", "���ƶ�����", "Art/Models/Terrain/Act3/Beacon/beacon_nostairs_v01_01_c5r6.tgt")
--tp:AddMap("�µ�����", "���ƶ�����", "Art/Models/Terrain/Act3/Battlefield/mosaic_doubleledge_connection_v01_02_c1r1.tgt")
tp:AddMap("�µ�����", "����ķ����˹", "Art/Models/Terrain/Act3/Beacon/beach_walkablelargecliffwater_weylamwalk_v01_01_c7r3.tgt")

--����֮���ĺ���
tp:AddMap("����֮���ĺ���", "��������", "Art/Models/Terrain/Beach/areatransitions/beachisland/beach_island_transition_v01_02_c10r3.tgt")

-->�̵� --Art/Models/Terrain/Forest/areatransitions/city/vaal_stairs_bottom_v01_01_c4r7.tgt
tp:AddMap("�̵�", "�߶��ų�", "Art/Models/Terrain/Forest/areatransitions/city/vaal_stairs_bottom_v01_01_c5r9.tgt")

-->�߶��ų�
tp:AddMap("�߶��ų�", "����(�����ӻ�)", "Art/Models/Terrain/IncaDungeon/BanteaySrei_Web_c2r4.tgt")

-->�߶��ų�
tp:AddMap("׹��֮�� 2 ��", "BOOSλ��", "Art/Models/Terrain/IncaDungeon/Arakaali_Balcony_Arch/dungeon_web_arakaali_balcony_v01_03_c1r3.tgt")

-->��Ӱ�㳡
tp:AddMap("��Ӱ�㳡", "�������", "Art/Models/Terrain/Act3/AreaTransitions/battlefronttobarracks/act3_riverbridge_transition_v01_01_c9r7.tgt")

-->��������
tp:AddMap("��������", "����֮��", "Art/Models/Terrain/Act3/AreaTransitions/battlefronttobarracks/act3_riverbridge_transition_v01_01_c9r7.tgt")

-->�綾�ܵ�
tp:AddMap("�綾�ܵ�", "�������ˮ��", "Art/Models/Terrain/Act3/Sewers/sewerwall_end_tunnel_v01_04_c1r2.tgt")

-->�������ˮ��
tp:AddMap("�������ˮ��", "���͹�¯", "Art/Models/Terrain/Act3/AreaTransitions/slum_sewer_entrance_v03_01.tgt")
--��ɫ����
tp:AddMap("�������ˮ��", "��ɫ����", "Art/Models/Terrain/Act3/AreaTransitions/sewers/sewer_ladder_up_v01_01_c1r1.tgt")
--��ɫ����
tp:AddMap("�������ˮ��", "��ת��ͷ", "Art/Models/Terrain/Act3/Sewers/sewerwall_exit_v01_01_c1r1.tgt")

--��ɫ����
tp:AddMap("��ɫ����", "�ű�����", "Art/Models/Terrain/Act3/Battlefield/arch_promenade_to_arsenal_v01_01_c2r3.tgt")

----�ű�����(������һ������  ���ö�λ)
--tp:AddMap("�ű�����", "�ű�����", "Art/Models/Terrain/Act3/Battlefield/arch_promenade_to_arsenal_v01_01_c2r3.tgt")

--��Ӱ�㳡
tp:AddMap("��Ӱ�㳡", "�������", "Art/Models/Terrain/Act3/AreaTransitions/battlefronttobarracks/act3_riverbridge_transition_v01_01_c9r7.tgt")

--��Ӱ��� 1 ��
tp:AddMap("��Ӱ�㳡", "��Ӱ��� 1 ��", "Art/Models/Terrain/TempleDungeon/lunariswater/act3_temple_entrance_v01_01_c3r2.tgt")

--��Ӱ��� 2 ��
tp:AddMapArea("��Ӱ��� 2 ��", "������", "Art/Models/Terrain/TempleDungeon/lunariswater/templeclean_prepiety_sidehigh_01_c1r2.tgt", {{"Art/Models/Terrain/TempleDungeon/lunariswater/templeclean_bloodpool_ledge_straight_v01_01.tgt", 84}})

--��ת��ͷ(�����׼ȷ)
--tp:AddMap("��ת��ͷ", "����֮��", "Art/Models/Terrain/Act3/LargeCliff/Act3_Largecliff_v01_01_victario_c3r1.tgt")

--����֮��
tp:AddMap("����֮��", "�۹�ƽԭ", "Art/Models/Terrain/Act3/AreaTransitions/act8_grain_gate_transition_v01_01_c8r5.tgt")

--�۹�ƽԭ
tp:AddMap("�۹�ƽԭ", "��ҫ��� 1 ��", "Art/Models/Terrain/Act8/act8_temple_entrance_v01_01_c3r2.tgt")

--�۹�ƽԭ
tp:AddMap("�۹�ƽԭ", "��ҫ��� 1 ��", "Art/Models/Terrain/Act8/act8_temple_entrance_v01_01_c3r2.tgt")

-----------------------------�Թ���ͼ

-->Estate Path  
tp:AddMap("Estate Path", "Aspirant's Trial", "Art/Models/Terrain/Act3/ElegantHouse/eleganthouse_transition_v01_01_c1r1.tgt")

-->Basilica Halls(ɱ��������л��ز�̫�ù��� ����·����,������·������ͨ��)
--tp:AddMap("Basilica Halls", "Aspirant's Trial", "ArtArt/Models/Terrain/Act3/Gardens/walls/garden_labyrinth_gate_v02_02_c1r2.tgt")

--Basilica Hallsh
tp:AddMapArea("Basilica Hallsh", "Sanitorium Passage", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_exit_up_v01_01_c1r2.tgt", {{"Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_wall_corner_concave_crevice_v01_01.tgt", 150}})

--Sepulchre Passage
tp:AddMapArea("Sepulchre Passage", "Aspirant's Trial", "Art/Models/Terrain/ChurchDungeon/dungeon_church_wall_straight_v01_02.tgt", {{"Art/Models/Terrain/ChurchDungeon/dungeon_church_wall_straight_v01_02.tgt", 25}})

--Domain Walkways
--Sepulchre Halls
tp:AddMapArea("Domain Walkways", "Sepulchre Halls", "Art/Models/Terrain/Doodads/labyrinth/Doorway/labyrinth_dry_garden_door_v01_01_c2r5.tgt", {{"Art/Models/Terrain/Blank.tgt", 96}})

--Sepulchre Halls
--Aspirant's Trial
tp:AddMapArea("Sepulchre Halls", "Aspirant's Trial", "Art/Models/Terrain/ChurchDungeon/dungeon_church_exit_up_v01_01_c1r1.tgt", {{"Art/Models/Terrain/ChurchDungeon/dungeon_church_wall_straight_v01_03.tgt", 96}})


