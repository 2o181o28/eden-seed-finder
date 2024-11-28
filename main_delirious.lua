--[[
This `main.lua` aims to find a Eden seed with Delirious, Scapular/Cancer, and an Emperor card. The first floor must contain a sacrifice room, and the first use of Delirious must be Hush. It is intended for Repentance+. 
]]
local finder = RegisterMod("Eden Seed Finder", 1)
local json = require("json")

local r = false
local kill = true
local current = 1
local tbl = {}
local seeds_list = {
-- paste the content of `seeds.txt` (or the output of `generator.cpp`) here.
}

function finder:post_start()
	if kill then return end

	local l=Game():GetLevel()
	local idx=l:QueryRoomTypeIndex(RoomType.ROOM_SACRIFICE,false,RNG())
	if l:GetRoomByIdx(idx).Data.Type ~= RoomType.ROOM_SACRIFICE then
		goto R
	end
	Isaac.GetPlayer(0):UseActiveItem(510)
	l=Game():GetRoom():GetEntities()
	for i=0,#l-1 do
		if l:Get(i).Type==407 then -- Hush
			table.insert(tbl, Seeds.Seed2String(Game():GetSeeds():GetStartSeed()))
			break
		end
	end

	::R::
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
			finder:SaveData(json.encode(tbl))
			return
		end
		Isaac.ExecuteCommand("seed " .. seeds_list[current])
	end
	
	if Input.IsButtonPressed(Keyboard.KEY_T, 0) then
		kill = false
		current = 1
		tbl = {}
		Isaac.ExecuteCommand("seed " .. seeds_list[1])
	end
	
	if Input.IsButtonPressed(Keyboard.KEY_Y, 0) then
		finder:SaveData(json.encode(tbl))
		kill = true
	end
end

finder:AddCallback(ModCallbacks.MC_POST_GAME_STARTED,finder.post_start)
finder:AddCallback(ModCallbacks.MC_POST_RENDER,finder.post_render)
