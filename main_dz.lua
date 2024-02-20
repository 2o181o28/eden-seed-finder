--[[
This `main.lua` aims to find a Eden seed with Vanishing Twin, 1 red heart, low stats and no bombs. The boss of floor 1 must be Rag Man, the Haunt or Headless Horseman. Its purpose is to find the worst seeds. 
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

	local l=Game():GetLevel()
	local idx=l:QueryRoomTypeIndex(RoomType.ROOM_BOSS,false,RNG())
	local name=l:GetRoomByIdx(idx).Data.Name
	
	if string.find(name,"Haunt") or string.find(name,"Ragman") or string.find(name,"Headless") then
		print(Seeds.Seed2String(Game():GetSeeds():GetStartSeed()) .. " : " .. name)
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
