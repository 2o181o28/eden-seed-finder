--[[
This `main.lua` aims to find a Eden seed with the Glowing Hourglass, Sacred Heart or other powerful passive items, and the Home floor containing both Mom's Knife and a wild item in the rightmost small room. It is intended for the Beast Ending speedruns. 
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
	local dps = p.Damage * (30 / (p.MaxFireDelay + 1))
	local lst
	local id
	
	function finder:check_room_items()
		local lst=Game():GetRoom():GetEntities()
		for i=0, lst.Size-1 do
			if lst:Get(i).Type==5 and lst:Get(i).Variant==390 then -- mom's chest
				lst:Get(i):ToPickup():TryOpenChest()
				break
			end
		end
		lst=Game():GetRoom():GetEntities()
		for i=0, lst.Size-1 do
			if lst:Get(i).Type==5 and lst:Get(i).Variant==100 then -- item
				-- print(lst:Get(i).SubType)
				if lst:Get(i).SubType==114 then -- mom's knife
					return false
				end
			end
		end
		return true
	end
	
	Isaac.ExecuteCommand("stage 13")
	Game():GetLevel():ChangeRoom(82) -- mom's bedroom ID
	if finder:check_room_items() then goto R; end
	
	Game():GetLevel():ChangeRoom(98)
	lst=Game():GetRoom():GetEntities()
	id=0
	for i=0, lst.Size-1 do
		if lst:Get(i).Type==5 and lst:Get(i).Variant==100 then
			id = lst:Get(i).SubType
		end
	end
	
	print(Seeds.Seed2String(Game():GetSeeds():GetStartSeed()) .. " : c" .. id)
		
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
