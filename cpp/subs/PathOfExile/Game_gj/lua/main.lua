
require("mycmd")
s_cmncfg = s_cmncfg

-----------------------------
AddMapRoomRate("The Riverways", 1100)
AddMapRoomRate("The Aqueduct", 1100)
AddMapRoomRate("The Upper Sceptre of God", 1100)
AddMapRoomRate("The Harvest", 1100)
AddMapRoomRate("The Northern Forest", 1100)
AddMapRoomRate("The Cavern of Anger", 1100)
AddMapRoomRate("The Causeway", 1300)
AddMapRoomRate("The Belly of the Beast Level 1", 1100)
AddMapRoomRate("The Belly of the Beast Level 2", 1100)
AddMapRoomRate("The Harvest", 1100)

-----------------------------
--����֮���ϲ�  
SetMapAreaInfo("The Upper Prison", { "The Warden's Quarters", "The Warden's Chambers" })
--Թ��֮���
SetMapAreaInfo("The Cavern of Anger", { "Merveil's Lair","Passage"})
--�󾺼���
SetMapAreaInfo("The Grand Arena", {"The Ring of Blades","Passageway","Arena","The Ring Blades"})
--����֮��
SetMapAreaInfo("The Harvest", { "Shavronne's Arena", "Doedre's Arena", "Maligaro's Arena","The Black Core","The Black Heart"})
--�Ž�����
SetMapAreaInfo("The Ancient Pyramid", {"Stairs","Pyramid Apex"}) 
--��Ӱ���:�� 2 ��
SetMapAreaInfo("The Lunaris Temple Level 2", {"Portal"})
--��Ȩ֮��
SetMapAreaInfo("The Sceptre of God", {"Stairs","The Sceptre of God"})
--�ϲ���Ȩ֮��
SetMapAreaInfo("The Upper Sceptre of God", {"Stairs","Tower Rooftop"})
--֯���߳�Ѩ
SetMapAreaInfo("The Weaver's Chambers", {"The Weaver's Nest"})
--��ķ�ı���
SetMapAreaInfo("Kaom's Stronghold", {"Caldera of The King","Kaom's Stronghold"})
--
SetMapAreaInfo("The Chamber of Innocence", {"Sanctum of Innocence","The Torched Courts"})
--
SetMapAreaInfo("The Cathedral Rooftop", {"Cathedral Apex","Ladder"})
--
SetMapAreaInfo("Shavronne's Tower", {"Stairs","Prison Rooftop"})
--
SetMapAreaInfo("The Wetlands", {"The Spawning Ground"})
--
SetMapAreaInfo("Prisoner's Gate", {"Valley of the Fire Drinker","The Cloven Pass","Valley of the Drinker"})
--
SetMapAreaInfo("The Crypt", {"Stairs"})
--
SetMapAreaInfo("Maligaro's Sanctum", {"Maucaro's Workshop"})
--
SetMapAreaInfo("The Ashen Fields", {"The Fortress Encampment"})
--
SetMapAreaInfo("The Temple of Decay Level 1", {"Stairs"})
--
SetMapAreaInfo("The Temple of Decay Level 2", {"Stairs","Arakaali's Web"})
--
SetMapAreaInfo("The Sarn Ramparts", {"Stairs"})
--
SetMapAreaInfo("Doedre's Cesspool", {"The Cauldron"})

--
SetMapAreaInfo("Aspirant's Trial", {"Stairs"})
--
SetMapAreaInfo("The Solaris Temple Level 2", {"Portal"})
--SetMapAreaInfo("The Harbour Bridge", {"The Sky Shrine"})
--SetMapAreaInfo("The Quay", {"Arena"})
--SetMapAreaInfo("The Brine King's Reef", {"The Brine King's Throne"})
--SetMapAreaInfo("The Harvest", {"The Black Core","The Black Heart"})
--SetMapAreaInfo("�漣֮ǽ", {"¥��","������"})
--SetMapAreaInfo("��������", {"����"})
-----------------------------

local tp = GetDefTerrainParser()
--���͵�
tp:AddAny(enTerrainParserFlag.kTPF_ObjDbPath, "Waypoint", "Metadata/Effects/Environment/waypoint/new/")

--������̲
--->ʨ������
tp:AddMap("The Twilight Strand", "Lioneye's Watch", "Art/Models/Terrain/Beach/areatransitions/southentrance/beachtown_south_entrance_c2r2.tgt")
--������
--tp:AddMap("The Twilight Strand", "Hillock", "Art/Models/Terrain/Beach/areatransitions/southentrance/beachtown_south_entrance_c1r3.tgt")

--ĺ�⺣̲
--->ʨ������
tp:AddMap("The Coast", "Lioneye's Watch", "Art/Models/Terrain/Beach/areatransitions/northentrance02/beachtown_north_entrance_v02_01_c6r3.tgt")
--->�����µ�
--tp:AddMap("The Coast", "The Tidal Island", "Art/Models/Terrain/Beach/areatransitions/beachisland/beach_island_transition_v01_01_c10r3.tgt")
--->��������
tp:AddMap("The Coast", "The Mud Flats", "Art/Models/Terrain/Beach/areatransitions/toswamp/beach_to_swamp_v01_01_c4r2.tgt")

--�����µ�
-->ĺ�⺣̲
tp:AddMap("The Tidal Island", "The Coast", "Art/Models/Terrain/Beach/areatransitions/beachisland/beach_island_transition_v01_01_c10r3.tgt")
--�Ϻ�֮ʹ boos
tp:AddMap("The Tidal Island", "Hailrake", "Art/Models/Terrain/Beach/QuestLocations/kyrenia_boat_medicinequest_v01_01_c3r3.tgt")


--ʨ������
-->ĺ�⺣̲
tp:AddMap("Lioneye's Watch", "The Coast", "Art/Models/Terrain/Beach/BeachTown_v2/beachencampment_v01_01_c6r5.tgt")

--��������
--ĺ�⺣̲(����Ῠס������Ŀ������谭����)
--tp:AddMap("The Mud Flats", "The Coast", "Art/Models/Terrain/Beach/areatransitions/toswamp/beach_to_swamp_v01_01_c4r2.tgt")
--��ˮ��
tp:AddMap("The Mud Flats", "The Fetid Pool", "Art/Models/Terrain/Beach/areatransitions/swamp2/beach_toswamp2_v01_01_c6r4.tgt")
--������Ѩ
tp:AddMap("The Mud Flats", "The Submerged Passage", "Art/Models/Terrain/Beach/areatransitions/beachtowateracave/Beach_to_watercave_c3r2.tgt")
-->���ŵ��Ƶ����ǽ��
tp:AddMap("The Mud Flats", "Strange Glyph Wall", "Art/Models/Terrain/Beach/areatransitions/beachtowateracave/Beach_to_watercave_c2r6.tgt")
-->Fortress Gate
tp:AddMap("The Mud Flats", "Fortress Gate", "Art/Models/Terrain/Beach/areatransitions/swamp_radiantpool/beach_karuipools_v01_01_c6r3.tgt")
-->Nessa
tp:AddMap("The Mud Flats", "Nessa", "Art/Models/Terrain/Beach/areatransitions/beachtowatercave_v2/Beach_to_watercave_v2_c3r5.tgt")
-->Fortress Gate
tp:AddMap("The Mud Flats", "Fortress Gate", "Art/Models/Terrain/Beach/areatransitions/swamp_radiantpool/beach_karuipools_v01_01_c6r3.tgt")
-->Fortress Gate
tp:AddMap("The Mud Flats", "The Karui Fortress", "Art/Models/Terrain/Beach/areatransitions/swamp_radiantpool/beach_karuipools_v01_01_c6r3.tgt")


--������Ѩ
-->��������
tp:AddMap("The Submerged Passage", "The Mud Flats", "Art/Models/Terrain/CaveDungeon/cave_exit_v01_01_c2r2.tgt")
-->ˮ��֮Ԩ
tp:AddMap("The Submerged Passage", "The Flooded Depths", "Art/Models/Terrain/CaveDungeon/watery_depth_entrance_v01_01_c1r1.tgt")
-->���ź���
tp:AddMap("The Submerged Passage", "The Ledge", "Art/Models/Terrain/CaveDungeon/caveup_exit_v01_01_c2r3.tgt")
-->���з(��û��֤׼ȷ��)
tp:AddMap("The Submerged Passage", "The Deep Dweller", "Art/Models/Terrain/Blank.tgt")

--ˮ��֮Ԩ
-->������Ѩ
tp:AddMap("The Flooded Depths", "The Submerged Passage", "Art/Models/Terrain/CaveDungeon/caveup_exit_v01_01_c2r3.tgt")

--���ź���
-->������Ѩ
tp:AddMap("The Ledge", "The Submerged Passage", "Art/Models/Terrain/Beach/CaveEntrances/beachcaveentrance_v01_01_c2r4.tgt")
-->����ɽ��
tp:AddMap("The Ledge", "The Climb", "Art/Models/Terrain/Beach/areatransitions/passageway/beach_passageway_v01_01_c3r3.tgt")

--����ɽ��
-->���ź���
tp:AddMap("The Climb", "The Ledge", "Art/Models/Terrain/Beach/areatransitions/passageway/beach_passageway_v01_01_c3r3.tgt")
-->����֮���²�
tp:AddMap("The Climb", "The Lower Prison", "Art/Models/Terrain/Beach/Prison/beach_prisonback_c6r4.tgt")

--����֮���²�
-->����ɽ��
tp:AddMap("The Lower Prison", "The Climb", "Art/Models/Terrain/PrisonDungeon/dungeon_prison_wall_straight_hole_v01_01_c1r1.tgt")
-->����֮���ϲ�
tp:AddMap("The Lower Prison", "The Upper Prison", "Art/Models/Terrain/PrisonDungeon/dungeon_prison_exit_up_v01_01_c1r1.tgt")
-->����������
tp:AddMap("The Lower Prison", "Trial of Ascendancy", "Art/Models/Terrain/PrisonDungeon/prison_trial_door_v01_01_c1r1.tgt")
--Trial of Ascendancy Plaque
tp:AddMap("The Lower Prison", "Trial of Ascendancy Plaque", "Art/Models/Terrain/PrisonDungeon/dungeon_prison_floor_height_lower_v01_05.tgt")
--Lever
tp:AddMap("The Lower Prison", "Lever", "Art/Models/Terrain/PrisonDungeon/dungeon_prison_fence_crevice_thickwall_v01_01.tgt")



--����֮���ϲ�  (��С��ͼ)
-->����֮���²�
tp:AddMap("The Upper Prison", "The Lower Prison", "Art/Models/Terrain/PrisonDungeon/dungeon_prison_entrance_down_v01_01_c1r3.tgt")
---->��������³��˹
tp:AddMap("The Upper Prison", "Brutus, Lord Incarcerator", "Art/Models/Terrain/PrisonDungeon/dungeon_prison_fence_stairs_brutus_v01_01.tgt")

--��������
-->��Ӱ��Ĺ
tp:AddMap("Prisoner's Gate", "The Ship Graveyard", "Art/Models/Terrain/Beach/areatransitions/passagewaytoshipgraveyard/shipgraveyard_passageway_v01_01_c4r3.tgt")
--����Ͽ�֮ӡ
tp:AddMap("Prisoner's Gate", "Thaumetic Seal", "Art/Models/Terrain/Beach/areatransitions/spikepassage/beach_passageblock_v01_01_c2r2.tgt")

--��Ӱ��Ĺ
-->��������
tp:AddMap("The Ship Graveyard", "Prisoner's Gate", "Art/Models/Terrain/Beach/areatransitions/passagewaytoshipgraveyard/shipgraveyard_passageway_v01_01_c4r3.tgt")
-->��Ӱ��Ĺ��Ѩ
tp:AddMap("The Ship Graveyard", "The Ship Graveyard Cave", "Art/Models/Terrain/Beach/areatransitions/shipgraveyard_dungeon/ship_entrance_v01_01_c3r5.tgt")
-->Թ��֮��
tp:AddMap("The Ship Graveyard", "The Cavern of Wrath", "Art/Models/Terrain/Beach/areatransitions/beachtoendcave/beach_caveentranceskeleton_v01_01_c7r6.tgt")
--�Ѷ�����
tp:AddMap("The Ship Graveyard", "Captain Fairgrave", "Art/Models/Terrain/Beach/QuestLocations/shipwreck_quest_v01_01_c7r8.tgt")


--��Ӱ��Ĺ��Ѩ
-->��Ӱ��Ĺ
tp:AddMap("The Ship Graveyard Cave", "The Ship Graveyard", "Art/Models/Terrain/CaveDungeon/cave_wall_thin_thick_T_v01_01.tgt")
--����Ů��(Ŀ��) û��Ҫ
--tp:AddMap("The Ship Graveyard Cave", "Slave Girl", "Art/Models/Terrain/Beach/Ships/boat_small_damaged_allflame_v01_01_c1r1.tgt")


--Թ��֮��
-->��Ӱ��Ĺ
tp:AddMap("The Cavern of Wrath", "The Ship Graveyard", "Art/Models/Terrain/Beach/areatransitions/beachtoendcave_inside/caveskeleton_exit_v01_01_c2r2.tgt")
-->Թ��֮���
tp:AddMap("The Cavern of Wrath", "The Cavern of Anger", "Art/Models/Terrain/CaveDungeon/caveup_exit_v01_01_c2r3.tgt")

--Թ��֮���(��С��ͼ)
-->Թ��֮��
tp:AddMap("The Cavern of Anger", "The Cavern of Wrath", "Art/Models/Terrain/CaveDungeon/cavedown_exit_v01_01_c2r3.tgt")
-->�ϲ�ɭ��
tp:AddMap("The Cavern of Anger", "The Southern Forest", "Art/Models/Terrain/Beach/areatransitions/endcavetoforest/merveil_exit_clean_v01_01_c2r2.tgt")
-->Īޱ���ĳ�Ѩ(С��ͼ)
tp:AddMap("The Cavern of Anger", "Merveil's Lair", "Art/Models/Terrain/CaveDungeon/caveup_exit_v01_01_c2r3.tgt", "The Cavern of Anger")
--Īޱ���ĳ�Ѩ->Թ��֮���
tp:AddMap("The Cavern of Anger", "The Cavern of Anger", "Art/Models/Terrain/CaveDungeon/cavedown_boss_exit_v01_01_c2r3.tgt", "Merveil's Lair")

--�ϲ�ɭ��
-->ɭ��Ӫ��
tp:AddMap("The Southern Forest", "The Forest Encampment", "Art/Models/Terrain/ForestTown/forestcamp_dock_v01_01_c2r4.tgt")

--ɭ��Ӫ��
-->�ϲ�ɭ��
tp:AddMap("The Forest Encampment", "The Southern Forest", "Art/Models/Terrain/ForestTown/forestcamp_center_v01_01_c14r9.tgt")
-->ǰ��ԭҰ
tp:AddMap("The Forest Encampment", "The Old Fields", "Art/Models/Terrain/ForestTown/forestcamp_center_v01_01_c10r4.tgt")
-->�ӵ�
tp:AddMap("The Forest Encampment", "The Riverways", "Art/Models/Terrain/ForestTown/forestcamp_center_v01_01_c10r15.tgt")


--ǰ��ԭҰ
-->ɭ��Ӫ��
tp:AddMap("The Old Fields", "The Forest Encampment", "Art/Models/Terrain/ForestTown/forestcamp_right_v01_01_c3r3.tgt")
-->��Ѩ
tp:AddMap("The Old Fields", "The Den", "Art/Models/Terrain/ForestCave/forestcave_entrance_hole_v01_01_c1r1.tgt")
-->Σ����·
tp:AddMap("The Old Fields", "The Crossroads", "Art/Models/Terrain/Forest/areatransitions/wall_gate_v01_01_c2r2.tgt")

--��Ѩ
-->ǰ��ԭҰ -2
tp:AddMap("The Den", "The Old Fields", "Art/Models/Terrain/ForestCave/forestcaveup_exit_v01_01_c2r3.tgt")

--Σ����·
-->ǰ��ԭҰ
tp:AddMap("The Crossroads", "The Old Fields", "Art/Models/Terrain/Forest/areatransitions/wall_gate_v01_01_c2r2.tgt")
-->����֮��:�� 1 ��
--tp:AddMap("The Crossroads", "The Chamber of Sins Level 1", "Art/Models/Terrain/Forest/areatransitions/temple_entrance_v01_01_c2r5.tgt")
-->����ż� -2
tp:AddMap("The Crossroads", "The Fellshrine Ruins", "Art/Models/Terrain/Forest/areatransitions/wall_gate_v01_01_c2r2.tgt")
-->���϶���
tp:AddMap("The Crossroads", "The Broken Bridge", "Art/Models/Terrain/Forest/areatransitions/bridgeconnection_v01_01_c2r2.tgt")

--����֮��:�� 1 ��
-->Σ����·
tp:AddMap("The Chamber of Sins Level 1", "The Crossroads", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_entrance_v01_01_c1r1.tgt")
-->����֮��:�� 2 ��
tp:AddMap("The Chamber of Sins Level 1", "The Chamber of Sins Level 2", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_exit_down_v01_01_c2r3.tgt")

--����֮��:�� 2 ��
-->����֮��:�� 1 ��
tp:AddMap("The Chamber of Sins Level 2", "The Chamber of Sins Level 1", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_exit_up_v01_01_c1r2.tgt")
-->Trial of Ascendancy
tp:AddMap("The Chamber of Sins Level 2", "Trial of Ascendancy", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_labyrinth_door_thin_corridor_v01_03_c1r1.tgt")
--Trial of Ascendancy Plaque
tp:AddMapArea("The Chamber of Sins Level 2", "Trial of Ascendancy Plaque", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_stairs_straight_v02_02.tgt", {{"Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_crevice_corner_concave_v01_01.tgt", 53}})

--����ż�
-->Σ����·
tp:AddMap("The Fellshrine Ruins", "The Crossroads", "Art/Models/Terrain/Forest/areatransitions/wall_gate_v01_01_c2r2.tgt")
-->�ž���Ĺ 1 ¥
tp:AddMap("The Fellshrine Ruins", "The Crypt Level 1", "Art/Models/Terrain/Forest/ChurchRuin/church_dungeon_entrance_v01_01_c2r2.tgt")
-->�ž���Ĺ
tp:AddMap("The Fellshrine Ruins", "The Crypt", "Art/Models/Terrain/Forest/ChurchRuin/church_dungeon_entrance_v01_01_c2r2.tgt")

--�ž���Ĺ 1 ¥
-->Σ����·
tp:AddMap("The Crypt Level 1", "The Fellshrine Ruins", "Art/Models/Terrain/ChurchDungeon/dungeon_church_exit_up_v01_01_c1r1.tgt")
--�ž���Ĺ 2 ¥
tp:AddMap("The Crypt Level 1", "The Crypt Level 2", "Art/Models/Terrain/ChurchDungeon/dungeon_church_exit_down_v01_01_c1r1.tgt")
--Trial of Ascendancy
tp:AddMap("The Crypt Level 1", "Trial of Ascendancy", "Art/Models/Terrain/ChurchDungeon/labyrinth_church_door_v01_01_c2r1.tgt")
--Lever
tp:AddMap("The Crypt Level 1", "Lever", "Art/Models/Terrain/ChurchDungeon/dungeon_church_wall_corner_convex_crevice_v01_01.tgt")
--Trial of Ascendancy Plaque
tp:AddMap("The Crypt Level 1", "Trial of Ascendancy Plaque", "Art/Models/Terrain/ChurchDungeon/dungeon_church_stairs_straight_feature_v01_01.tgt")


--�ž���Ĺ 2 ¥
-->�ž���Ĺ 1 ¥
tp:AddMap("The Crypt Level 2", "The Crypt Level 1", "Art/Models/Terrain/ChurchDungeon/dungeon_church_exit_up_v01_01_c1r1.tgt")
--��̳
tp:AddMap("The Crypt Level 2", "Golden Hand", "Art/Models/Terrain/ChurchDungeon/dungeon_church_relic_altar_v01_01_c1r2.tgt")

--The Crypt
tp:AddMap("The Crypt", "Trial of Ascendancy Plaque", "Art/Models/Terrain/ChurchDungeon/dungeonchurch_fence_crevice_wallthick_v02_01.tgt")
--Trial of Ascendancy
tp:AddMap("The Crypt", "Trial of Ascendancy", "Art/Models/Terrain/ChurchDungeon/labyrinth_church_door_v01_01_c1r1.tgt")



--���϶���
-->Σ����·
--tp:AddMap("The Broken Bridge", "The Crossroads", "Art/Models/Terrain/Forest/areatransitions/bridgeconnection_v01_01_c2r2.tgt")

--�ӵ�
-->ɭ��Ӫ��
tp:AddMap("The Riverways", "The Forest Encampment", "Art/Models/Terrain/ForestTown/forestcamp_left_v01_01_c6r6.tgt")
-->ʪ��
tp:AddMap("The Riverways", "The Wetlands", "Art/Models/Terrain/Forest/areatransitions/bridgeconnection_v01_01_c2r2.tgt")
-->��������
--tp:AddMap("The Riverways", "The Western Forest", "Art/Models/Terrain/Forest/areatransitions/roadtothickforest_entrance_v01_01_c6r2.tgt")

--��������
-->�ӵ�
--tp:AddMap("The Western Forest", "The Riverways", "Art/Models/Terrain/Forest/areatransitions/roadtothickforest_entrance_v01_01_c6r2.tgt")
-->֯���߳�Ѩ
tp:AddMap("The Western Forest", "The Weaver's Chambers", "Art/Models/Terrain/Forest/areatransitions/spidergrove_entrance_v01_01_c4r2.tgt")
-->������
tp:AddMap("The Western Forest", "Alira", "Art/Models/Terrain/Forest/Trees/treewitch_camp_v01_02_c7r6.tgt")

--֯���߳�Ѩ
-->�������� -3
tp:AddMapArea("The Weaver's Chambers", "The Western Forest", "Art/Models/Terrain/SpiderGrove/spidergrove_exit_v01_01_c1r2.tgt", {{"Art/Models/Terrain/Blank.tgt", 70}, {"Art/Models/Terrain/SpiderGrove/forest_spidergrove_convex_v01_02.tgt", 24}})
-->֯���߳�Ѩ(С��ͼ)������ط��Ľ���������
tp:AddMapArea("The Weaver's Chambers", "The Weaver's Nest", "Art/Models/Terrain/Blank.tgt", {{"Art/Models/Terrain/SpiderGrove/forest_spidergrove_middle_v01_01.tgt", 66}, {"Art/Models/Terrain/SpiderGrove/forest_spidergrove_straight_v01_04.tgt",33}, {"Art/Models/Terrain/SpiderGrove/spidergrove_exit_v01_01_c1r3.tgt", 66} }, "The Weaver's Chambers")
tp:AddMapArea("The Weaver's Chambers", "The Weaver's Chambers", "Art/Models/Terrain/SpiderGrove/forest_spidergrove_convex_v01_02.tgt", {{"Art/Models/Terrain/SpiderGrove/forest_spidergrove_straight_v01_04.tgt", 24}, {"Art/Models/Terrain/SpiderGrove/spidergrove_exit_v01_01_c1r3.tgt", 73}}, "The Weaver's Nest")
--������Ʒ
tp:AddMap("The Weaver's Chambers", "Maligaro's Spike", "Art/Models/Terrain/SpiderGrove/forest_spidergrove_wall_thin_T_v01_01.tgt")

--�߶�����(The Vaal Ruins)
-->ʪ��
tp:AddMap("The Vaal Ruins", "The Wetlands", "Art/Models/Terrain/IncaDungeon/dungeon_inca_exit_v01_01_c1r2.tgt")
-->��������(�д���֤)
--tp:AddMap("The Vaal Ruins", "The Northern Forest", "Art/Models/Terrain/IncaDungeon/dungeon_bossrelease_v01_01_c2r1.tgt")

--��������
-->�߶�����
--tp:AddMap("The Northern Forest", "The Vaal Ruins", "Art/Models/Terrain/Forest/areatransitions/forest_caveexit_inca_v01_01_c2r5.tgt")
--��������
tp:AddMap("The Northern Forest", "The Dread Thicket", "Art/Models/Terrain/Forest/areatransitions/grovewall_entrance_v01_01_c1r2.tgt")
--�ٲ���Ѩ
tp:AddMap("The Northern Forest", "The Caverns", "Art/Models/Terrain/Forest/areatransitions/waterfall_cave_entrance_v01_01_c2r4.tgt")

--ʪ��
-->�߶�����
tp:AddMap("The Wetlands", "The Vaal Ruins", "Art/Models/Terrain/Forest/areatransitions/forest_caveentrance_inca_v01_01_c2r5.tgt")
-->�ӵ�
tp:AddMap("The Wetlands", "The Riverways", "Art/Models/Terrain/Forest/areatransitions/bridgeconnection_v01_01_c2r2.tgt")
-->ŷ�� 
tp:AddMap("The Wetlands", "Oak", "Art/Models/Terrain/Forest/OaksCamp/cliffpathconnection_gate_v01_01_c1r1.tgt")
--����
--tp:AddMap("The Wetlands", "Tree Roots", "Art/Models/Terrain/Forest/OaksCamp/cliffpathconnection_gate_v01_01_c1r1.tgt")


--��������
-->��������
tp:AddMap("The Dread Thicket", "The Northern Forest", "Art/Models/Terrain/Grove/grove_wall_exit_v01_01_c2r2.tgt")

--�ٲ���Ѩ
-->��������
tp:AddMap("The Caverns", "The Northern Forest", "Art/Models/Terrain/ForestCave/forestcavedown_exit_v01_01_c2r3.tgt")
-->�Ž�����
tp:AddMap("The Caverns", "The Ancient Pyramid", "Art/Models/Terrain/IncaDungeon/dungeon_stairs_up_v01_01_c1r2.tgt")

--�Ž�����
-->�ٲ���Ѩ
tp:AddMap("The Ancient Pyramid", "The Caverns", "Art/Models/Terrain/IncaDungeon/dungeon_stairs_down_v01_01_c1r2.tgt")
-->�����Ƿ���
tp:AddMap("The Ancient Pyramid", "The City of Sarn", "Art/Models/Terrain/IncaDungeon/dungeon_huangdoor_v01_01_c3r2.tgt")

--�����Ƿ���
-->����Ӫ��
tp:AddMap("The City of Sarn", "The Sarn Encampment", "Art/Models/Terrain/Act3/AreaTransitions/act3_docks_to_town_lower_01_01_c3r3.tgt")

--����Ӫ��
-->�����Ƿ��� 
tp:AddMap("The Sarn Encampment", "The City of Sarn", "Art/Models/Terrain/Act3Town/Act3_town_01_01_c12r21.tgt")
-->ƶ���
tp:AddMap("The Sarn Encampment", "The Slums", "Art/Models/Terrain/Act3Town/Act3_town_01_01_c21r7.tgt")
-->The Lord's Labyrinth
tp:AddMap("The Sarn Encampment", "The Lord's Labyrinth", "Art/Models/Terrain/Act3Town/Act3_town_01_01_c8r8.tgt")


--ƶ���
-->����Ӫ��
tp:AddMap("The Slums", "The Sarn Encampment", "Art/Models/Terrain/Act3/AreaTransitions/act3_to_slums_area_transition_c5r4.tgt")
-->��ˮ����ƶ���
tp:AddMap("The Slums", "The Sewers", "Art/Models/Terrain/Act3/AreaTransitions/slum_sewer_entrance_v02_01.tgt")
-->���᳡
tp:AddMap("The Slums", "The Crematorium", "Art/Models/Terrain/Act3/AreaTransitions/act3_prison_entrance_01_01_c2r3.tgt")

--���᳡
-->ƶ���
tp:AddMap("The Crematorium", "The Slums", "Art/Models/Terrain/PrisonDungeon/dungeon_prison_exit_up_v01_01_c1r1.tgt")
-->�ж���(Ŀ��)
tp:AddMap("The Crematorium", "Tolman", "Art/Models/Terrain/quest_marker.tgt")
-->Trial of Ascendancy
tp:AddMap("The Crematorium", "Trial of Ascendancy", "Art/Models/Terrain/PrisonDungeon/prison_trial_door_v01_01_c2r1.tgt")
-->Trial of Ascendancy Plaque
tp:AddMap("The Crematorium", "Trial of Ascendancy Plaque", "Art/Models/Terrain/PrisonDungeon/dugeon_prison_lava_fence_concave_v01_01.tgt")

--��ˮ����ƶ���
-->ƶ���
tp:AddMap("The Sewers", "The Slums", "Art/Models/Terrain/Act3/Sewers/sewerwall_exit_v01_01_c1r1.tgt")
-->�м��ش�
tp:AddMap("The Sewers", "The Marketplace", "Art/Models/Terrain/Act3/Sewers/sewerwall_exit_v01_01_c1r1.tgt")
-->��Ӫ
tp:AddMap("The Sewers", "The Ebony Barracks", "Art/Models/Terrain/Act3/AreaTransitions/sewerexit_v01_01_c3r1.tgt")

--�ֿ�ش�
-->��ˮ�����ֿ�ش�
tp:AddMap("The Warehouse District", "The Warehouse Sewers", "Art/Models/Terrain/Act3/AreaTransitions/slum_sewer_entrance_v01_01.tgt")
-->�м��ش�()
tp:AddMap("The Warehouse District", "The Marketplace", "Art/Models/Terrain/Act3/LargeCliff/warehouse_transition_market_v01_01_c3r3.tgt")

--�м��ش�
-->�ֿ�ش�
tp:AddMap("The Marketplace", "The Warehouse District", "Art/Models/Terrain/Act3/AreaTransitions/market_transition_warehouse_v01_01_c1r3.tgt")
-->��ʯ��Ĺ()
tp:AddMap("The Marketplace", "The Catacombs", "Art/Models/Terrain/Act3/AreaTransitions/markettochurchdungeon_v01_01_c3r2.tgt")
-->��ˮ�����м��ش�(The Market Sewers)
tp:AddMap("The Marketplace", "The Market Sewers", "Art/Models/Terrain/Act3/AreaTransitions/slum_sewer_entrance_v02_01.tgt")
-->��ս�㳡()
tp:AddMap("The Marketplace", "The Battlefront", "Art/Models/Terrain/Act3/AreaTransitions/market_to_battlefront_v01_01_c5r6.tgt")

--��ˮ�����м��ش�
-->�м��ش�
tp:AddMap("The Market Sewers", "The Marketplace", "Art/Models/Terrain/Act3/Sewers/sewerwall_exit_v01_01_c1r1.tgtt")

--��ʯ��Ĺ
-->�м��ش�
tp:AddMap("The Catacombs", "The Marketplace", "Art/Models/Terrain/ChurchDungeon/dungeon_church_exit_up_v01_01_c1r1.tgt")
-->Trial of Ascendancy
tp:AddMap("The Catacombs", "Trial of Ascendancy", "Art/Models/Terrain/ChurchDungeon/labyrinth_church_door_v01_01_c2r1.tgt")
-->Trial of Ascendancy
tp:AddMap("The Catacombs", "Trial of Ascendancy Plaque", "Art/Models/Terrain/ChurchDungeon/dungeon_church_floor_height_convex_stairs_v01_02.tgt")

--��ս�㳡
-->�м��ش�
tp:AddMap("The Battlefront", "The Marketplace", "Art/Models/Terrain/Act3/AreaTransitions/market_to_battlefront_v01_01_c5r6.tgt")
-->��ҫ���� 1 ��(The Solaris Temple Level 1)
tp:AddMap("The Battlefront", "The Solaris Temple Level 1", "Art/Models/Terrain/Act3/IvoryTemple/act3_temple_entrance_v01_01_c3r2.tgt")
-->���ຣ��()
tp:AddMap("The Battlefront", "The Docks", "Art/Models/Terrain/Act3/Battlefield/battlefield_arch_v01_03_c2r4.tgt")
-->The Harbour Bridge
tp:AddMap("The Battlefront", "The Harbour Bridge", "Art/Models/Terrain/Act3/AreaTransitions/battlefronttobarracks/act3_battlefront_to_harbor_v01_01_c2r3.tgt")

--��ҫ���� 1 ��
-->��ս�㳡
tp:AddMap("The Solaris Temple Level 1", "The Imperial Fields", "Art/Models/Terrain/Act3/AreaTransitions/temple_to_battlefront_v01_01_c3r3.tgt")
-->��ҫ���� 2 ��
tp:AddMap("The Solaris Temple Level 1", "The Solaris Temple Level 2", "Art/Models/Terrain/TempleDungeon/templeclean_exit_down_v01_01_c1r3.tgt")
---->The Battlefront(��The Imperial Fieldsһ��)
--tp:AddMap("The Solaris Temple Level 1", "The Battlefront", "Art/Models/Terrain/Act3/AreaTransitions/temple_to_battlefront_v01_01_c3r3.tgt")

--���ຣ��()
-->��ս�㳡
tp:AddMap("The Docks", "The Battlefront", "Art/Models/Terrain/Act3/Battlefield/battlefield_arch_v01_02_c2r4.tgt")
--װ��ǵ�����
tp:AddMap("The Docks", "Supply Container", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_questcart.tgt")
--�Ѷ�����
tp:AddMap("The Docks", "Captain Fairgraves", "Art/Models/Terrain/Act3/citywaypoint_v01_01_c2r1.tgt")

--��ҫ���� 2 ��
-->��ҫ���� 1 ��
tp:AddMap("The Solaris Temple Level 2", "The Solaris Temple Level 1", "Art/Models/Terrain/TempleDungeon/templeclean_exit_up_v01_02_c3r1.tgt")
-->��������
tp:AddMap("The Solaris Temple Level 2", "Lady Dialla", "Art/Models/Terrain/TempleDungeon/gemling_queen_throne_v01_01_c2r3.tgt")
-->The Sun Orb (��Ʒλ��)
--tp:AddMap("The Solaris Temple Level 2", "Sun Orb", "Art/Models/Terrain/TempleDungeon/gemling_queen_throne_v01_01_c3r3.tgt")

--����������Ӫ
-->��ˮ�����ֿ�ش�
tp:AddMap("The Ebony Barracks", "The Warehouse Sewers", "Art/Models/Terrain/Act3/AreaTransitions/battlefield_to_sewer_stairs_v01_01_c3r2.tgt")
-->��Ӱ���� 1 ��
tp:AddMap("The Ebony Barracks", "The Lunaris Temple Level 1", "Art/Models/Terrain/Act3/IvoryTemple/act3_temple_entrance_v01_01_c3r2.tgt")
-->�ʼһ�԰
tp:AddMap("The Ebony Barracks", "The Imperial Gardens", "Art/Models/Terrain/Act3/Gardens/garden_arch_v01_01_c2r5.tgt")
-->����ά�潫��
tp:AddMap("The Ebony Barracks", "General Gravicius", "Art/Models/Terrain/TempleDungeon/temple_carpet_oneside_01_01.tgt")
-->The Harbour Bridge
tp:AddMap("The Ebony Barracks", "The Harbour Bridger", "Art/Models/Terrain/Act3/AreaTransitions/battlefronttobarracks/act3_riverbridge_transition_v01_01_c9r7.tgt")

--��Ӱ���� 1 ��
-->����������Ӫ
tp:AddMap("The Lunaris Temple Level 1", "The Ebony Barracks", "Art/Models/Terrain/Act3/AreaTransitions/temple_to_battlefront_v01_01_c3r3.tgt")
-->��Ӱ���� 2 ��
tp:AddMap("The Lunaris Temple Level 1", "The Lunaris Temple Level 2", "Art/Models/Terrain/TempleDungeon/templeclean_exit_down_v01_01_c1r3.tgt")

--��Ӱ���� 2 ��
-->��Ӱ���� 1 ��
tp:AddMap("The Lunaris Temple Level 2", "The Lunaris Temple Level 1", "Art/Models/Terrain/TempleDungeon/templeclean_exit_up_v01_02_c3r1.tgt", "")
-->������(С����)
--tp:AddMap("The Lunaris Temple Level 2", "Portal", "Art/Models/Terrain/TempleDungeon/lunariswater/templeclean_prepiety_roundtop_center_01_c1r2.tgt")

--�ʼһ�԰
-->����������Ӫ
tp:AddMap("The Imperial Gardens", "The Ebony Barracks", "Art/Models/Terrain/Act3/Gardens/garden_arch_v01_01_c2r5.tgt")
-->�����Թ�(The Hedge Maze)
tp:AddMap("The Imperial Gardens", "The Hedge Maze", "Art/Models/Terrain/Act3/Gardens/walls/garden_wall_entrance_v01_01_c2r2.tgt")
-->ͼ���
tp:AddMap("The Imperial Gardens", "The Library", "Art/Models/Terrain/Act3/Library/Library_LargeBuilding_entrance_v01_01_c2r3.tgt")
-->��Ȩ֮��
tp:AddMap("The Imperial Gardens", "The Sceptre of God", "Art/Models/Terrain/Act3/AreaTransitions/Act3_EpicDoor_v02_01_c7r7.tgt")
-->��������
tp:AddMap("The Imperial Gardens", "Locked Door", "Art/Models/Terrain/Act3/AreaTransitions/Act3_EpicDoor_v02_01_c7r7.tgt")

--�����Թ�
-->�ʼһ�԰
tp:AddMap("The Hedge Maze", "The Imperial Gardens", "Art/Models/Terrain/Act3/Gardens/walls/garden_wall_entrance_v01_01_c2r2.tgt")
-->÷��
--tp:AddMap("The Hedge Maze", "Plum", "Art/Models/Terrain/Act3/Gardens/fruittree_c2r2.tgt")
-->Trial of Ascendancy
tp:AddMap("The Hedge Maze", "Trial of Ascendancy", "Art/Models/Terrain/Act3/Gardens/walls/garden_labyrinth_gate_v02_02_c1r2.tgt")
--Trial of Ascendancy Plaque(������С�� һ�¾��ܱ�����)

--ͼ���
-->�ʼһ�԰
tp:AddMap("The Library", "The Imperial Gardens", "Art/Models/Terrain/Act3/Library/library_entrance_v01_01_c2r3.tgt")
-->������
tp:AddMap("The Library", "The Archives", "Art/Models/Terrain/Act3/Library/library_entrance_v02_01_c2r3.tgt")

--������
-->ͼ���
tp:AddMap("The Archives", "The Library", "Art/Models/Terrain/Act3/Library/library_entrance_v03_01_c2r3.tgt")

--��Ȩ֮��
-->�ʼһ�԰
tp:AddMap("The Sceptre of God", "The Imperial Gardens", "Art/Models/Terrain/Act3/AreaTransitions/tower_epic_entrance_v01_01_c4r8.tgt")
-->�ϲ���Ȩ֮��
--tp:AddMap("The Sceptre of God", "The Upper Sceptre of God", "Art/Models/Terrain/Act3/SceptreofGod/Corners/tower_transition_up_01_01_c1r2.tgt")

--�ϲ���Ȩ֮��
--��Ȩ֮�� -3
tp:AddMap("The Upper Sceptre of God", "The Sceptre of God", "Art/Models/Terrain/Act3/SceptreofGod/Corners/tower_transition_down_01_01_c2r2.tgt")
--ˮ���ż�
tp:AddMap("The Upper Sceptre of God", "The Aqueduct", "Art/Models/Terrain/Act3/Tower/Act3_tower_01_01_c13r9.tgt")
--Boosλ��
tp:AddMap("The Upper Sceptre of God", "BOOS", "Art/Models/Terrain/Act3/Tower/Act3_tower_01_01_c10r4.tgt")


--ˮ���ż�
-->ͳ����֮��
tp:AddMap("The Aqueduct", "Highgate", "Art/Models/Terrain/Act4/Town/AqueductConnection/mountiantown_connection_c7r13.tgt")

--�ɺԺ���(The Dried Lake)
-->ͳ����֮��
tp:AddMap("The Dried Lake", "Highgate", "Art/Models/Terrain/Act4/DriedLake/lake_entrance_v01_01_c2r4.tgt")

--��ڿ�ӣ��� 1 ��
-->ͳ����֮��
tp:AddMap("The Mines Level 1", "Highgate", "Art/Models/Terrain/Act4/mine/mine_areatransition_entrance_v01_01_c3r4.tgt")
-->��ڿ�ӣ��� 2 ��
tp:AddMap("The Mines Level 1", "The Mines Level 2", "Art/Models/Terrain/Act4/mine/mine_areatransition_v01_01_c1r2.tgt")

--��ڿ�ӣ��� 2 ��
-->ˮ������
tp:AddMap("The Mines Level 2", "The Crystal Veins", "Art/Models/Terrain/Act4/mine/mine_areatransition_v03_01_c1r2.tgt")
-->��ڿ�ӣ��� 1 ��
tp:AddMap("The Mines Level 2", "The Mines Level 1", "Art/Models/Terrain/Act4/mine/mine_areatransition_v02_02_c1r2.tgt")

--ˮ������
-->��ڿ�ӣ��� 2 ��
tp:AddMap("The Crystal Veins", "The Mines Level 2", "Art/Models/Terrain/Act4/mine/mine_areatransition_v04_01_c1r2.tgt")
-->��ķ�Ļþ�
tp:AddMap("The Crystal Veins", "Kaom's Dream", "Art/Models/Terrain/Act4/mine/crystals_openAnimation_v01_01_c1r3.tgt")
-->�������Ļþ�
tp:AddMap("The Crystal Veins", "Daresso's Dream", "Art/Models/Terrain/Act4/mine/crystals_openAnimation_v01_01_c5r3.tgt")
-->����֮������ 1 ��
tp:AddMap("The Crystal Veins", "The Belly of the Beast Level 1", "Art/Models/Terrain/Act4/mine/crystals_openAnimation_v01_01_c3r2.tgt")

--��ķ�Ļþ�
-->ˮ������ -14
tp:AddMap("Kaom's Dream", "The Crystal Veins", "Art/Models/Terrain/Act4/LavaPlateau/KaomTiles/lava_abyss_v02_01_c3r1.tgt")
-->��ķ�ı���
tp:AddMap("Kaom's Dream", "Kaom's Stronghold", "Art/Models/Terrain/Act4/LavaPlateau/AreaTransition/lava_abyss_transition_entrance_v01_01_c3r1.tgt")

--��ķ�ı���
-->��ķ�Ļþ�
tp:AddMap("Kaom's Stronghold", "Kaom's Dream", "Art/Models/Terrain/Act4/LavaPlateau/AreaTransition/lava_kaom3_transition_entrance_v02_01_c2r1.tgt")
--
tp:AddMap("Kaom's Stronghold", "Caldera of The King", "Art/Models/Terrain/Act4/LavaPlateau/AreaTransition/lava_lake_throne_room_v01_01_c2r2.tgt")

--�������Ļþ�
-->ˮ������ -22
tp:AddMap("Daresso's Dream", "The Crystal Veins", "Art/Models/Terrain/Act4/Arena/arena_wall_v02_02.tgt")
-->�󾺼���
tp:AddMap("Daresso's Dream", "The Grand Arena", "Art/Models/Terrain/Act4/Arena/AreaTransition/arena_areatransition_v01_01_c1r2.tgt")

--�󾺼���
-->�������Ļþ�
tp:AddMap("The Grand Arena", "Daresso's Dream", "Art/Models/Terrain/Act4/Arena/AreaTransition/colosseum_areatransition_v01_01_c2r2.tgt")
-->
--tp:AddMap("The Grand Arena", "The Ring of Blades", "Art/Models/Terrain/Act4/Arena/colosseum_entrance_v01_02_c2r1.tgt")

--����֮������ 1 ��
-->ˮ������
--tp:AddMap("The Belly of the Beast Level 1", "The Crystal Veins", "Art/Models/Terrain/Act4/Belly/belly_tunnel_v01_01_c2r3.tgt")
-->����֮������ 2 ��
--tp:AddMap("The Belly of the Beast Level 1", "The Belly of the Beast Level 2", "Art/Models/Terrain/Act4/Belly/belly_tunnel_v01_01_c2r3.tgt")

--����֮������ 2 ��
-->����֮������ 1 ��
--tp:AddMap("The Belly of the Beast Level 2", "The Belly of the Beast Level 1", "Art/Models/Terrain/Act4/Belly/belly_tunnel_level2_v01_02_c2r3.tgt")
---->����֮��(The Harvest)
--tp:AddMap("The Belly of the Beast Level 2", "The Harvest", "Art/Models/Terrain/Act4/Belly/belly_tunnel_level2_v01_02_c2r3.tgt")

--����֮��(The Harvest)
-->����֮������ 2 ��
tp:AddMap("The Harvest", "The Belly of the Beast Level 2", "Art/Models/Terrain/Act4/Belly/Harvest_tunnel_v01_01_c2r3.tgt")
-->�������
tp:AddMap("The Harvest", "The Black Core", "Art/Models/Terrain/Act4/Belly/Taster/TasterMouth_openAnimation_v01_01_c2r1.tgt")
-->��������
tp:AddMap("The Harvest", "The Black Heart", "Art/Models/Terrain/Act4/Belly/MalachaiPlatform/malachai_fight_v01_01_c11r11.tgt")
-->��������boss
tp:AddMap("The Harvest", "Malachai, The Nightmare", "Art/Models/Terrain/Act4/Belly/DepthsPlatform/Belly_BossPlatform_v01_01_c5r6.tgt")

--The Ascent
-->Lever
tp:AddMap("The Ascent", "Lever", "Art/Models/Terrain/Act4/Ascent/Feature/ascent_summit_v01_01_c4r3.tgt")
-->Overseer's Tower
tp:AddMap("The Ascent", "Lever", "Art/Models/Terrain/Act5/Tower/tower_v01_01_c9r4.tgt")

--The Control Blocks
-->Oriath Square
tp:AddMap("The Control Blocks", "Oriath Square", "Art/Models/Terrain/Act5/Area Transitions/security_exit_v01_01_c1r5.tgt")
-->Overseer's Tower
tp:AddMap("The Control Blocks", "Overseer's Tower", "Art/Models/Terrain/Act5/Tower/slave_doublewall_tower_stair_transition_v01_01_c3r1.tgt")

--The Control Blocks
-->Lever
tp:AddMap("Oriath Square", "The Control Blocks", "Art/Models/Terrain/Act5/OriathSquare/slaveden_entrance_steps_v01_01_c2r1.tgt")
-->The Templar Courts
tp:AddMap("Oriath Square", "The Templar Courts", "Art/Models/Terrain/Act5/Area Transitions/Oriath_AreaTransition_v01_03_c2r2.tgt")

--The Templar Courts
-->Oriath Square
tp:AddMap("The Templar Courts", "Oriath Square", "Art/Models/Terrain/Act5/Templar Court/templar_oriath_transition_v01_01_c2r1.tgt")
-->The Templar Courts
tp:AddMap("The Templar Courts", "The Chamber of Innocence", "Art/Models/Terrain/Act5/Templar Court/templar_to_innocents_v01_01_c2r1.tgt")

--The Chamber of Innocence
-->The Templar Courts
tp:AddMap("The Chamber of Innocence", "The Templar Courts", "Art/Models/Terrain/Act5/Innocence/transition_chamber_to_courts_v01_01_c3r4.tgt")
-->Sanctum of Innocence(С����)
tp:AddMap("The Chamber of Innocence", "Sanctum of Innocence", "Art/Models/Terrain/Act5/Innocence/transition_chamber_to_boss_v01_01_c4r4.tgt")
-->The Torched Courts
tp:AddMap("The Chamber of Innocence", "The Torched Courts", "Art/Models/Terrain/Act5/Innocence/transition_chamber_to_courts_v01_01_c3r4.tgt")

--The Torched Courts
-->The Chamber of Innocence
tp:AddMap("The Torched Courts", "The Chamber of Innocence", "Art/Models/Terrain/Act5/Templar Court/templar_to_innocents_v01_01_c2r1.tgt")
-->The Ruined Square
--tp:AddMap("The Torched Courts", "The Ruined Square", "Art/Models/Terrain/Act5/Templar Court/templar_to_innocents_v01_01_c2r1.tgt")

--The Ruined Square
-->The Chamber of Innocence
tp:AddMap("The Ruined Square", "The Ossuary", "Art/Models/Terrain/Act5/OriathSquare/Oriath_AreaTransition_v01_04_c2r2.tgt")
-->The Torched Court
tp:AddMap("The Ruined Square", "The Torched Courts", "Art/Models/Terrain/Act5/Area Transitions/Oriath_AreaTransition_v01_03_c2r2.tgt")
-->The Reliquary(�������ȷ��)
tp:AddMap("The Ruined Square", "The Reliquary", "Art/Models/Terrain/Act5/OriathSquare/Oriath_AreaTransition_v01_02_c2r3.tgt")
-->The Cathedral Rooftop
--tp:AddMap("The Ruined Square", "The Cathedral Rooftop", "Art/Models/Terrain/Act5/OriathSquare/ChitusTiles/chitus_statuewall_transition_v01_01_c1r3.tgt")

--The Ossuary
-->Tomb of the First Templar(��������)
tp:AddMap("The Ossuarye", "Tomb of the First Templar", "Art/Models/Terrain/Doodads/Act5/SkeletonTomb_Quest_Sarcophagus/ossuary_quest_v01_01.tgt")
-->TThe Ruined Square
tp:AddMap("The Ossuarye", "The Ruined Square", "Art/Models/Terrain/Act5/Area Transitions/Ossuary_abyss_transition_v01_01_c1r2.tgt")

--The Cathedral Rooftop
-->Cathedral Apex(С����)
--tp:AddMap("The Cathedral Rooftop", "Cathedral Apex", "Art/Models/Terrain/Act5/CathedralRoof/boss/cathedralroof_boss_area_v02_01_c5r10.tgt")
-->The Ruined Square
tp:AddMap("The Cathedral Rooftop", "The Ruined Square", "Art/Models/Terrain/Act5/CathedralRoof/cathedral_chitus_entrance/cathedral_roof_transition_v01_01_c7r17.tgt")

--The Karui Fortress
-->The Mud Flats
tp:AddMap("The Karui Fortress", "The Mud Flats", "Art/Models/Terrain/Beach/areatransitions/swamp_radiantpool/beach_karuipools_v01_01_c6r3.tgt")
-->The Ridge
tp:AddMap("The Karui Fortress", "The Ridge", "Art/Models/Terrain/Beach/areatransitions/toridge/swamp_to_ridge_v01_01_c5r3.tgt")
-->Tukohama's Keep
--tp:AddMap("The Karui Fortress", "Tukohama's Keep", "Art/Models/Terrain/Beach/SwampPool/swamp_longbridge_v01_01_c6r2.tgt")


--The Ridge
-->The Mud Flats
tp:AddMap("The Ridge", "The Karui Fortress", "Art/Models/Terrain/Beach/areatransitions/fetidpooltoledge/ledge_to_fetidpool_transition_v01_01_c2r5.tgt")
-->The Lower Prison
tp:AddMap("The Ridge", "The Lower Prison", "Art/Models/Terrain/PrisonDungeon/areatransitions/ledge_prisonback_c5r3.tgt")

--The Lower Prison
-->The Ridge
tp:AddMap("The Lower Prison", "The Ridge", "Art/Models/Terrain/PrisonDungeon/areatransitions/act1_2_ceiling_transition_v01_01_c1r1.tgt")
-->Shavronne's Tower
tp:AddMap("The Lower Prison", "Shavronne's Tower", "Art/Models/Terrain/PrisonDungeon/areatransitions/shavronne_prison_door_up_v01_01_c2r2.tgt")

--Shavronne's Tower
-->The Lower Prison
tp:AddMap("Shavronne's Tower", "The Lower Prison", "Art/Models/Terrain/PrisonDungeon/areatransitions/shavronne_prison_door_up_v01_02_c2r1.tgt")

--Prisoner's Gate
-->The Western Forest
tp:AddMap("Prisoner's Gate", "The Western Forest", "Art/Models/Terrain/Beach/areatransitions/spikepassage/beach_passageblock_v01_01_c5r3.tgt")

--The Western Forest
-->Prisoner's Gate
tp:AddMap("The Western Forest", "Prisoner's Gate", "Art/Models/Terrain/Forest/areatransitions/forest_mountainpass_v01_01_c13r4.tgt")
-->The Riverways
tp:AddMap("The Western Forest", "The Riverways", "Art/Models/Terrain/Forest/areatransitions/roadtothickforest_entrance_v01_01_c6r2.tgt")

--The Riverways
-->The Western Forest
tp:AddMap("The Riverways", "The Western Forest", "Art/Models/Terrain/Forest/areatransitions/roadtothickforest_entrance_v01_01_c6r2.tgt")
-->The Wetlands
tp:AddMap("The Riverways", "The Wetlands", "Art/Models/Terrain/Forest/areatransitions/bridgeconnection_v01_01_c2r2.tgt")
-->The Southern Forest
tp:AddMap("The Riverways", "The Southern Forest", "Art/Models/Terrain/ForestTown/forest_to_river_v01_01_c5r2.tgt")

--The Wetlands
-->The Riverways
--tp:AddMap("The Wetlands", "The Riverways", "Art/Models/Terrain/Forest/areatransitions/bridgeconnection_v01_01_c2r2.tgt")

--The Southern Forest
-->The Riverways
tp:AddMap("The Southern Forest", "The Riverways", "Art/Models/Terrain/ForestTown/forest_to_river_v02_01_c2r1.tgt")
-->The Southern Forest
--tp:AddMap("The Southern Forest", "The Cavern of Anger", "Art/Models/Terrain/Forest/areatransitions/forest_caveentrance_v01_01_c2r4.tgt")

--The Cavern of Anger
-->The Southern Forest
tp:AddMap("The Cavern of Anger", "The Southern Forest", "Art/Models/Terrain/Beach/areatransitions/endcavetoforest/merveil_exit_clean_v01_01_c2r2.tgt")
-->The Beacon(С��ͼ��ͨ���Ĵ��ͼ�� ������������)
--tp:AddMap("The Cavern of Anger", "The Beacon", "Art/Models/Terrain/CaveDungeon/caveup_exit_v01_01_c2r3.tgt")

--The Beacon
-->The Cavern of Anger
tp:AddMap("The Beacon", "The Cavern of Anger", "Art/Models/Terrain/Forest/areatransitions/forest_caveentrance_v01_01_c2r4.tgt")
-->Weylam Roth(NPC)
tp:AddMap("The Beacon", "Weylam Roth(", "Art/Models/Terrain/Act3/Beacon/beach_walkablelargecliffwater_weylamwalk_v01_01_c7r3.tgt")
--Metadata/QuestObjects/Act6/BeaconPayload�����ƶ����Ӹ���Ψһ�ĵ�
tp:AddMap("The Beacon", "���ƶ�����", "Art/Models/Terrain/Act3/Battlefield/mosaic_doubleledge_connection_v01_02_c1r1.tgt")

--The Brine King's Reef
-->The Brine King's Throne(����)
--tp:AddMap("The Brine King's Reef", "The Brine King's Throne", "Art/Models/Terrain/Beach/areatransitions/beachisland/beach_island_transition_v01_02_c10r3.tgt")

--Maligaro's Sanctum
-->The Brine King's Throne(����)  --Art/Models/Terrain/Beach/Trees/swamppool_middle_v02_01.tgt
tp:AddMap("Maligaro's Sanctum", "The Brine King's Throne", "Art/Models/Terrain/Beach/SwampPool/swamppool_v01_06.tgt")

--The Den
-->The Ashen Fields
--tp:AddMap("The Den", "The Ashen Fields", "Art/Models/Terrain/ForestCave/forestcaveup_exit_v01_01_c2r3.tgt")

--The Ashen Fields
-->The Den
tp:AddMap("The Ashen Fields", "The Den", "Art/Models/Terrain/ForestCave/forestcave_entrance_hole_v01_01_c1r1.tgt")

--The Northern Forest
-->The Causeway
--tp:AddMap("The Northern Forest", "The Causeway", "Art/Models/Terrain/Forest/areatransitions/city/forestriver_plinthtransition_v01_01_c6r2.tgt")
-->The Dread Thicket
--tp:AddMap("The Northern Forest", "The Dread Thicket", "Art/Models/Terrain/Forest/areatransitions/grovewall_entrance_v01_01_c1r2.tgt")
-->Azmeri Shirine
tp:AddMap("The Northern Forest", "Azmeri Shirine", "Art/Models/Terrain/Forest/Feature/forest_azmeri_shrine_c2r1.tgt")

--The Causeway
-->The Northern Forest
tp:AddMap("The Causeway", "The Northern Forest", "Art/Models/Terrain/IncaDungeon/Causeway/causeway_plinth_transition_v01_01_c2r3.tgt")
-->The Vaal City
--tp:AddMap("The Causeway", "The Vaal City", "Art/Models/Terrain/Forest/areatransitions/city/vaal_stairs_bottom_v01_01_c4r7.tgt")

--The Vaal City
-->The Causewa
--tp:AddMap("The Vaal City", "The Causeway", "Art/Models/Terrain/Forest/areatransitions/city/vaal_stairs_top_v01_01_c4r3.tgt")
-->The Temple of Decay Level 1
tp:AddMap("The Vaal City", "The Temple of Decay Level 1", "Art/Models/Terrain/IncaDungeon/BanteaySrei_Web_c2r4.tgt")

-----�ڰ���------------------------
--The Toxic Conduits
-->Doedre's Cesspool
--tp:AddMap("The Toxic Conduits", "Doedre's Cesspool", "Art/Models/Terrain/Act3/Sewers/sewerwall_end_tunnel_v01_04_c1r2.tgt")
-->The Quay
tp:AddMap("The Toxic Conduits", "The Quay", "Art/Models/Terrain/Act3/Sewers/sewerwall_exit_v01_01_c1r1.tgt")

--The Quay
-->The Grain Gate
tp:AddMap("The Quay", "The Grain Gate", "Art/Models/Terrain/Act3/LargeCliff/Act3_Largecliff_v01_01_c3r1.tgt")

--The Grain Gate
-->The Imperial Fields
tp:AddMap("The Grain Gate", "The Imperial Fields", "Art/Models/Terrain/Act3/AreaTransitions/act8_grain_gate_transition_v01_01_c8r5.tgt")

--The Imperial Fields
-->The Solaris Temple Level 1
--tp:AddMap("The Grain Gate", "The Solaris Temple Level 1", "Art/Models/Terrain/Act8/act8_temple_entrance_v01_01_c3r2.tgt")

--Doedre's Cesspool
-->The Toxic Conduits
tp:AddMap("Doedre's Cesspool", "The Toxic Conduits", "Art/Models/Terrain/Act3/Sewers/sewerwall_end_tunnel_v01_03_c2r2.tgt")
-->The Grand Promenade
--tp:AddMap("Doedre's Cesspool", "The Grand Promenade", "Art/Models/Terrain/Act3/AreaTransitions/sewers/sewer_ladder_up_v01_01_c1r1.tgt")

--The Grand Promenade
-->Doedre's Cesspoo
tp:AddMap("The Grand Promenade", "Doedre's Cesspool", "Art/Models/Terrain/Act3/AreaTransitions/sewers/battlefield_lowstream_ladder_v01_01_c2r1.tgt")
-->The Bath House
--tp:AddMap("The Grand Promenade", "The Bath House", "Art/Models/Terrain/Act3/Battlefield/arch_promenade_to_arsenal_v01_01_c2r3.tgt")

----The Bath House(����Ŀ���Ŷ�һ�������ҵ�ͼ�ܴ�)
---->Hector Titucius, Eternal Servan
--tp:AddMap("The Bath House", "The Ebony Barracks", "Art/Models/Terrain/Act3/Battlefield/arch_promenade_to_arsenal_v01_01_c2r3.tgt")

--The Ebony Barracks
-->The Harbour Bridge
tp:AddMap("The Bath House", "The Ebony Barracks", "Art/Models/Terrain/Act3/AreaTransitions/battlefronttobarracks/act3_riverbridge_transition_v01_01_c9r7.tgt")
-->The Lunaris Temple Level 1
tp:AddMap("The Bath House", "The Lunaris Temple Level 1", "Art/Models/Terrain/TempleDungeon/lunariswater/act3_temple_entrance_v01_01_c3r2.tgt")

-----------------------------�Թ���ͼ

-->Estate Path
tp:AddMap("Estate Path", "Aspirant's Trial", "ArtArt/Models/Terrain/Act3/Gardens/walls/garden_labyrinth_gate_v02_02_c1r2.tgt")

--
-->Basilica Halls(ɱ��������л��ز�̫�ù��� ����·����,������·������ͨ��)
--tp:AddMap("Basilica Halls", "Aspirant's Trial", "ArtArt/Models/Terrain/Act3/Gardens/walls/garden_labyrinth_gate_v02_02_c1r2.tgt")

--Sepulchre Passage
tp:AddMapArea("Basilica Hallsh", "Sepulchre Passage", "Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_exit_up_v01_01_c1r2.tgt", {{"Art/Models/Terrain/RuinedTempleForestDungeon/templeruinforest_wall_corner_concave_crevice_v01_01.tgt", 150}})

--Sepulchre Passage
tp:AddMapArea("Sepulchre Passage", "Aspirant's Trial", "Art/Models/Terrain/ChurchDungeon/dungeon_church_wall_straight_v01_02.tgt", {{"Art/Models/Terrain/ChurchDungeon/dungeon_church_wall_straight_v01_02.tgt", 25}})

--Domain Walkways
--Sepulchre Halls
tp:AddMapArea("Domain Walkways", "Sepulchre Halls", "Art/Models/Terrain/Doodads/labyrinth/Doorway/labyrinth_dry_garden_door_v01_01_c2r5.tgt", {{"Art/Models/Terrain/Blank.tgt", 96}})

--Sepulchre Halls
--Aspirant's Trial
tp:AddMapArea("Sepulchre Halls", "Aspirant's Trial", "Art/Models/Terrain/ChurchDungeon/dungeon_church_exit_up_v01_01_c1r1.tgt", {{"Art/Models/Terrain/ChurchDungeon/dungeon_church_wall_straight_v01_03.tgt", 96}})

--Ascendancy Chamber

