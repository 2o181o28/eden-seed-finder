--[[
this `main.lua` aims to find a greed mode seed that Eden starts with Dad's key, 9 Volt/Sharp Plug and a Chaos card, and almost all the greed exit rooms has no enemies. It is intended for greed mode speedruns.
]]
local finder = RegisterMod("Eden Seed Finder", 1)

local r = false
local kill = true
local current = 1
local seeds_list = {
-- paste the content of `seeds.txt` (or the output of `generator.cpp`) here.
}

function finder:post_start()
	if kill then return end

	local p=Isaac.GetPlayer(0)
	
	function finder:check_room_items()
		local lst=Game():GetRoom():GetEntities()
		for i=0, lst.Size-1 do
			if lst:Get(i):IsActiveEnemy() then
				return true
			end
		end
		return false
	end
	
	local cnt = 0
	
	for i = 1, 6 do
		Isaac.ExecuteCommand("stage " .. i)
		Game():GetLevel():ChangeRoom(110) -- greed exit room ID
		if finder:check_room_items() then cnt = cnt + 1; end
	end
		
	if cnt<2 then 
		print(Seeds.Seed2String(Game():GetSeeds():GetStartSeed()) .. " | " .. cnt)
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
		kill = true
	end
end

finder:AddCallback(ModCallbacks.MC_POST_GAME_STARTED,finder.post_start)
finder:AddCallback(ModCallbacks.MC_POST_RENDER,finder.post_render)
