--[[
This `main.lua` aims to find a Eden seed with Experimental Treatment and low stats. Experimental Treatment must decrease tears and damage. The treasure rooms and boss rooms of the first 3 floors must contain trash items. Its purpose is to find the worst seeds.
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

local items_eval = {
	2, 2, 0, 2, 2, 2, 2, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 2, 2, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 2, 2, 0, 2, 1, 0, 1, 0, 1, 0, 2, 2, 0, 0, 0, 1, 0, 1, 0, 1, 0, 2, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 2, 0, 0, 2, 2, 0, 1, 0, 2, 1, 0, 1, 1, 2, 2, 0, 1, 2, 0, 2, 2, 2, 1, 1, 0, 0, 2, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 1, 1, 2, 2, 2, 1, 0, 1, 0, 0, 1, 2, 0, 1, 2, 2, 0, 1, 2, 2, 2, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 2, 2, 2, 0, 0, 0, 1, 1, 2, 2, 2, 0, 1, 0, 0, 2, 1, 0, 0, 0, 1, 0, 0, 0, 0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 1, 2, 0, 2, 0, 0, 0, 2, 1, 2, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 2, 2, 2, 0, 2, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 2, 1, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1, 2, 0, 0, 2, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 2, 1, 0, 2, 1, 2, 2, 2, 0, 0, 0, 0, 2, 1, 1, 0, 1, 0, 1, 0, 0, 0, 2, 0, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 2, 2, 1, 0, 0, 1, 0, 0, 0, 2, 0, 2, 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 2, 0, 2, 1, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 2, 1, 0, 0, 2, 0, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 2, 0, 0, 2, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 2, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 1, 0, 0, 2, 0, 2, 1, 0, 0, 1, 2, 2, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 2, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 2, 1, 0, 2, 0, 1, 1, 0, 2, 2, 2, 1, 0, 1, 0, 2, 2, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 1, 1, 1, 2, 0, 1, 0, 0, 0, 0, 2, 0, 0, 2, 0, 1, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 1, 2, 2, 0, 0, 0, 2, 0, 2, 2, 2, 0, 0, 0, 0, 1, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 2, 0, 1, 0, 1, 0, 0, 0, 0, 2, 1, 1, 0, 0, 0, 0, 1, 1, 2, 0, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 0, 0, 0, 1, 2, 2, 1, 2, 0, 2, 1, 0, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 2, 2, 2
}
local stages = {
	"1","2","1c","2c","3"--,"4","3c",-- "4c","5","6","5c","6c"
}

function finder:post_start()
	if kill then return end

	function finder:check_room_items(tol)
		local lst=Game():GetRoom():GetEntities()
		for i=0, lst.Size-1 do
			if lst:Get(i).Type==5 and lst:Get(i).Variant==100 then -- item
				if items_eval[lst:Get(i).SubType]>=tol then
					return true
				end
			end
		end
		return false
	end
	
	for _,name in ipairs(stages) do
		Isaac.ExecuteCommand("stage " .. name)
		local l=Game():GetLevel()
		local stage=l:GetStage()
		if l:IsAltStage() then stage=stage+1 end
		local tol = stage>3 and 2 or 1
		
		local id = l:QueryRoomTypeIndex(RoomType.ROOM_TREASURE, false, RNG())
		l:ChangeRoom(id)
		if finder:check_room_items(tol) then goto R; end
		-- boss check no longer needed, as it was done in C++
	end
	
	table.insert(tbl, Seeds.Seed2String(Game():GetSeeds():GetStartSeed()))
	
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
