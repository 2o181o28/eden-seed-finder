/*
Calculate Eden's starting items. Works for Repentance v1.7.9b

Source: https://bindingofisaacrebirth.fandom.com/wiki/Eden_Generation
Modified from https://gist.github.com/bladecoding/5fcc1356bfb0cf26555b0ade7c4fedca
*/

#ifndef EDEN_H
#define EDEN_H 1
#include<bits/stdc++.h>
#include"constants.hpp"
#include"rng.hpp"

// Room::GetSpawnSeed() to Entity::InitSeed
uint32_t to_entity_seed(uint32_t room_spawn_seed){
	auto s = Rng{room_spawn_seed, 11}.advance(6);
	return Rng{s, 35}.next();
}

// Game():GetSeeds():GetStageSeed(13) to Room::GetSpawnSeed()
uint32_t to_room_seed(uint32_t stage_seed){
	auto s = Rng{stage_seed, 35}.advance(14);
	return Rng{s, 12}.advance(1);
}

// Entity::InitSeed for the character and a specific pickup in Home
std::pair<uint32_t, uint32_t> init_seed(uint32_t startSeed){
	auto startRng = Rng{startSeed, 0x3, 0x17, 0x19};
	uint32_t stage_seed{};
	//Stage Seeds
	for (int i = 0; i < STAGE_COUNT+1; i++)
		stage_seed = startRng.next();
	// stage_seed : Game():GetSeeds():GetStageSeed(13)
	return {startRng.next(), to_entity_seed(to_room_seed(stage_seed))};
	 // Seeds::PlayerInitSeed, Entity::InitSeed
}

std::pair<uint32_t, uint32_t> drop_seed(uint32_t startSeed){
	auto pa = init_seed(startSeed);

	//These happen inside Player::Init
	auto playerInitRng = Rng{pa.first, 0x1, 0xB, 0x10};
	playerInitRng.next();
	playerInitRng.next();
	playerInitRng.next();
	playerInitRng.next();
	
	return {playerInitRng.next(), pa.second};
	 // Entity::DropSeed, Entity::InitSeed
}

int get_card(uint32_t seed){
	#ifdef NO_CARD_SEARCH
	return 0;
	#endif

	// Note that the shift arguments have changed in Repentance (originally 0x5, 0x9, 0x7)
	auto cardRng = Rng{seed, 0x3, 0x3, 0x1D};
	/* DEBUG */ // for a brute-force algorithm to find shift1,shift2,shift3,t
	/*auto cardRng = Rng{seed, ga, gb, gc};
	auto b=cardRng;
	for(int t=1;t<10;t++){
		global_arr[global_var][t] = b.next();
	} */
	/* DEBUG END */
	if (cardRng.next() % 25 == 0) {
		// 2 more cards in Repentance.
		int ret = (int)(cardRng.next() % 15) + 42;
		
		if(ret == 55){ret=78;} // Cracked key
		if(ret == 56){ret=80;} // Wild Card
		
		return ret;
	}
	
	// The checks of Runes and Playing card are remove in Repentance, too.
/*	if (cardRng.next() % 10 == 0)
	{
		//Rune
	}
	if (cardRng.next() % 5 == 0 && false)
	{
		//Playing card
		return (int)(cardRng.next() % 9) + 23;
	}*/
	
	int ret = (int)(cardRng.next() % 22) + 1;
	
	// Reversed Major Arcana Cards; added in Repentance
	if(cardRng.next() % 7 == 0){
		ret += 55;
	}
	
	return ret;
}

struct EdenItems{
	int activeId, passiveId, card;
};

EdenItems get_eden_items(uint32_t dropSeed){
	auto rng = Rng{dropSeed, 0x1, 0x5, 0x13};
	
//	int trinket = 0;
	int card = 0;
//	int pill = 0;
//	int hearts = 0;
//	int soulHearts = 0;	
	if ((rng.next() % 3) == 0) {
		//trinket
	}
	else if ((rng.next() & 1) == 0) {
		if ((rng.next() & 1) == 0) {
			card = get_card(rng.next());
		}
		else {
			//pill
			rng.next();
		}
	}
	
	#ifdef SEARCH_FOR_CERTAIN_CARD
	if(card != 12 && card != 52) return {0,0,0};
	#endif
	
	int activeId = 0;
	int passiveId = 0;
	for (int i = 0; i < 100; i++) {
		int itemId = (int)(rng.next() % ITEM_COUNT) + 1;
		
		if(NO_EDEN[itemId])
			continue;
		
		// printf("ENCOUNTER %d\n",itemId);
		
		if (IS_ACTIVE[itemId]){
			
			activeId = activeId != 0 ? activeId : itemId;
		} 
		else{
			passiveId = passiveId != 0 ? passiveId : itemId;
		}
		//Isaac doesn't exit early :thinking:
		if (activeId != 0 && passiveId != 0)
			break;

	}
	
	//Hearts and SoulHearts are actually done in Player::Init
/*	var healthRng = new Rng(dropSeed, 0x1, 0x5, 0x13);
	var halfHearts = (int)healthRng.Next() & 3;
	hearts = halfHearts * 2;
	soulHearts = ((int)healthRng.Next() % (4 - halfHearts)) * 2;
	if (hearts == 0 && soulHearts < 4)
	 	soulHearts = 4;
*/		
	
	
	return EdenItems{activeId, passiveId, card};
}

#endif
