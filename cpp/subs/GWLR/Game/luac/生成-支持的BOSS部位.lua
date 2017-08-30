
local g_scmd = {}
local g_all_boss_body_info = {}

function scmd()
	return g_scmd
end

function g_scmd:AddMonsterBodyPartInfo(boss_name, part_name, part_id)
	if part_name == "����" or part_name == "ʧ��" then
		return
	end

	local boss = g_all_boss_body_info[boss_name]
	if boss == nil then
		boss = {}
		g_all_boss_body_info[boss_name] = boss
	end
	table.insert(boss, part_name)
end

dofile("./BodyPartInfo/BodyPartInfo.lua")

local out_file = io.open("./֧�ֵ�BOSS��λ.lua", "w+")

for k, v in pairs(g_all_boss_body_info) do
	out_file:write("֧�ֵ�boss����" .. k .. " �����Ǹ�boss�Ĳ�λ����\n")
	for _, part in ipairs(v) do
		print("part name:", part)
		out_file:write("��λ����" .. part .. "\n")
	end
	out_file:write("\n")
end

out_file:close()
