
local dm = dm

--��װ��Ϸapk()
--ж����Ϸapk()
--������Ϸapp()
--�ر���Ϸapp()
-------------------------------------------------------

--dm:FreePic("systemnoticebt.bmp")

--TestReloadGameLua("jyzj", "mycmd", true)
--[[
TestReloadGameLua("jyzj", "StatesInfo", true)
LoadStatesInfo()
OutputScriptInfo("Resolve")
s_StateResolver:Resolve()
--]]

--ѡ�����()

dm:EnablePicCache(0)
print(dm:FindPicEx(500, 100, 800, 200, "gametask.bmp", "", 0.9, 0))
