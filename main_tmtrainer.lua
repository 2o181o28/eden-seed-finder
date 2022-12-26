--[[
This `main.lua` aims to find a Eden seed with the Glowing Hourglass, TMTRAINER, and the mom's chest in Home floor containing a glitched item with the effect of Mega Mush. It is intended for the Beast Ending speedruns. 
]]
local finder = RegisterMod("Eden Seed Finder", 1)

local checking = false
local r = false
local kill = true
local current = 1

local seeds_list = {
-- paste the content of `seeds.txt` (or the output of `generator.cpp`) here.
{"TEST ONLY", 996},
}

function finder:check_item(seed, init_seed)
	checking = true
	local l = Game():GetRoom():GetEntities()
	for i = 0, l.Size-1 do
		if l:Get(i).Type==5 and l:Get(i).Variant==100 then
			checking = false
			return
		end
	end
	if kill then
		checking = false
		return
	end
	
	local p = Isaac.GetPlayer(0)
	local e = Game():Spawn(5,100,p.Position,Vector(0,0),p,1,init_seed):ToPickup()
	if (e.Charge == 0) or (e.Charge >= 3 and e.Charge <= 12) then
		Isaac.ExecuteCommand("rewind")
		r=true
		checking = false
		return
	end
	
--	print("Debugging... check active item " .. init_seed)
	p:UseActiveItem(4294967295)
	local l = p:GetEffects():GetEffectsList()
	local fnd = false
	for i = 0, l.Size-1 do
		if l:Get(i).Item.ID == 625 then -- mega mush
			fnd=true
			break
		end
	end
	if fnd then
		print(seed .. " | " .. e.Charge)
	end
	
	Isaac.ExecuteCommand("rewind")
	r=true
	checking = false
end

function finder:post_update()
	if Game():IsPaused() then
		return
	end	

	if r then
		r=false
		if (not checking) and (current < #seeds_list)then
			current = current + 1
			finder:check_item(seeds_list[current][1],seeds_list[current][2])
		end
	end
	
	if Input.IsButtonPressed(Keyboard.KEY_T, 0) and not checking then
		kill = false
		current = 1
		finder:check_item(seeds_list[current][1],seeds_list[current][2])
	end
	
	if Input.IsButtonPressed(Keyboard.KEY_Y, 0) then
		kill = true
	end
end

-- finder:AddCallback(ModCallbacks.MC_POST_GAME_STARTED,finder.post_start)
finder:AddCallback(ModCallbacks.MC_POST_UPDATE,finder.post_update)
