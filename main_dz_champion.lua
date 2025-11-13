--[[
This `main.lua` aims to find a Eden seed with Experimental Treatment, low stats and no bombs. There must be a dark red reviving champion on floor 1, and it must be a flying enemy or there are no obstacles in the room, to prevent the automatic door opening. This program is for finding the first truly unwinnable seed.
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
local fly_list={222,80,14,214,249,61,256,281,868}
local can_fly={}
for _,item in ipairs(fly_list) do
	can_fly[item]=true
end

function finder:post_start()
	if kill then return end

	local l=Game():GetLevel()
	local rooms=l:GetRooms()
	
	function check_grid()
		local r=Game():GetRoom()
		for i=0,r:GetGridSize()-1 do
			if r:GetGridCollision(i)==3 then -- solid
				return false
			end
		end
		return true
	end
	
	for i=0, rooms.Size-1 do
		local ri=rooms:Get(i)
		if ri.Data.Type==1 then -- default
			l:ChangeRoom(ri.SafeGridIndex)
			local lst=Game():GetRoom():GetEntities()
			for j=0,#lst-1 do 
				local li=lst:Get(j)
				if (li:IsEnemy() and li:ToNPC():GetChampionColorIdx()==12 -- dark red
				    and (can_fly[li.Type] or check_grid())) then
					table.insert(tbl, Seeds.Seed2String(Game():GetSeeds():GetStartSeed()))
					goto FIN
				end
			end
		end
	end
	::FIN:: 
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
		Isaac.ExecuteCommand("seed " .. seeds_list[current])
	end
	
	if Input.IsButtonPressed(Keyboard.KEY_T, 0) then
		kill = false
		current = 1
		Isaac.ExecuteCommand("seed " .. seeds_list[1])
	end
	
	if Input.IsButtonPressed(Keyboard.KEY_Y, 0) then
		finder:SaveData(json.encode(tbl))
		kill = true
	end
end

finder:AddCallback(ModCallbacks.MC_POST_GAME_STARTED,finder.post_start)
finder:AddCallback(ModCallbacks.MC_POST_RENDER,finder.post_render)
