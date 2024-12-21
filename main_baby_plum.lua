--[[
This `main.lua` aims to find a seed with Baby Plum explosion.
]]
local finder = RegisterMod("Eden Seed Finder", 1)
local json = require("json")

local r = false
local kill = true
local current = 1
local seeds_list = {
-- paste the content of `seeds.txt` (or the output of `generator.cpp`) here.
}
local tbl={}

function finder:post_start()
	if kill then return end

	local l=Game():GetLevel()
	l:ChangeRoom(l:GetRooms():Get(0).GridIndex)
	l=Game():GetRoom():GetEntities()
	local fnd=false
	for i=0,#l-1 do
		local e=l:Get(i)
		if e.Type==908 and e.InitSeed==seeds_list[current][2] then -- Baby Plum
			fnd=true
			break
		end
	end
	
	if fnd then
		table.insert(tbl, seeds_list[current][1])
		finder:SaveData(json.encode(tbl))
	end
	
	r=true
end

function finder:post_render()
	if Game():IsPaused() then
		return
	end	

	if r then
		r=false
		current = current + 1
		if current > #seeds_list then
			return
		end
		Isaac.ExecuteCommand("seed " .. seeds_list[current][1])
	end
	
	if Input.IsButtonPressed(Keyboard.KEY_T, 0) then
		kill = false
		current = 1
		Isaac.ExecuteCommand("seed " .. seeds_list[1][1])
	end
	
	if Input.IsButtonPressed(Keyboard.KEY_Y, 0) then
		finder:SaveData(json.encode(tbl))
		kill = true
	end
end

finder:AddCallback(ModCallbacks.MC_POST_GAME_STARTED,finder.post_start)
finder:AddCallback(ModCallbacks.MC_POST_RENDER,finder.post_render)
