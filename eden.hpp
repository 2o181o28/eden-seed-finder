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
u32 to_entity_seed(u32 room_spawn_seed){
#ifdef MOMS_CHEST
	auto s = Rng{room_spawn_seed, 11}.advance(4);
	return Rng{Rng{s, 35}.next(), 7}.next();
#else
	auto s = Rng{room_spawn_seed, 11}.advance(6);
	return Rng{s, 35}.next();
#endif
}

// Game():GetSeeds():GetStageSeed(13) to Room::GetSpawnSeed()
u32 to_room_seed(u32 stage_seed){
#ifdef MOMS_CHEST
	auto s = Rng{stage_seed, 35}.advance(13);
#else
	auto s = Rng{stage_seed, 35}.advance(14);
#endif
	return Rng{s, 12}.advance(1);
}

// Entity::InitSeed for the character and a specific pickup in Home
std::pair<u32, u32> init_seed(u32 startSeed){
	auto startRng = Rng{startSeed, 0x3, 0x17, 0x19};
	[[maybe_unused]] u32 stage_seed{};
	//Stage Seeds
	for (int i = 0; i < STAGE_COUNT+1; i++)
		stage_seed = startRng.next();
	// stage_seed : Game():GetSeeds():GetStageSeed(13)
	return {startRng.next(), 
	#ifdef NO_HOME
		0
	#else
		to_entity_seed(to_room_seed(stage_seed))
	#endif
	};
	 // Seeds::PlayerInitSeed, Entity::InitSeed
}

std::pair<u32, u32> drop_seed(u32 startSeed){
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

int get_card(u32 seed, bool playing=false){
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
		#ifdef GREED
			int ret = (int)(cardRng.next() % 14) + 42;
		
			if(ret == 55){ret=80;} // Wild Card
		#else
			int ret = (int)(cardRng.next() % 15) + 42;
		
			if(ret == 55){ret=78;} // Cracked key
			if(ret == 56){ret=80;} // Wild Card
		#endif
		
		return ret;
	}
	
	// The RNG used for checks of Runes and Playing cards are removed in Repentance, too.
/*	if (cardRng.next() % 10 == 0)
	{
		//Rune
	} */
	if (playing && cardRng.next() % 5 == 0)
	{
		//Playing card
		return (int)(cardRng.next() % 9) + 23;
	}
	
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

EdenItems get_eden_items(u32 dropSeed){
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
	if(card != SEARCH_FOR_CERTAIN_CARD) return {0,0,0};
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

	return EdenItems{activeId, passiveId, card};
}

// from [0,1) to p.MaxFireDelay; see https://bindingofisaacrebirth.fandom.com/wiki/Tears
double to_delay(double t){
	t=t*1.5-0.75;
	if(t<0)t*=0.68; // FIXME: precise formula unknown

	if(t>=0)return 16-6*sqrt(t*1.3+1);
	if(t>-0.77)return 16-6*sqrt(t*1.3+1)-6*t;
	return 16-6*t;
}

// from [0,1) to p.Damage
double to_damage(double t){return 2*t+2.5;}

struct EdenStats{
	int hearts, soul_hearts, coins, keys, bombs;
	double delay, damage, speed;
};

EdenStats get_eden_stats(u32 drop_seed){
	//Hearts and SoulHearts are actually done in Player::Init
	auto rng = Rng{drop_seed, 2};
	auto halfHearts = rng.next() & 3;
	EdenStats res={};
	res.hearts = halfHearts * 2;
	res.soul_hearts = (rng.next() % (4 - halfHearts)) * 2;
	if (res.hearts == 0 && res.soul_hearts < 4)
		res.soul_hearts = 4;
	if(rng.next()%3==0 || rng.next()%2==0){
		// No coins / bombs / keys. 
	}else{
		switch(rng.next()%3){
			case 0: res.coins=rng.next()%5+1; break;
			case 1: res.keys=1; break;
			case 2: res.bombs=rng.next()%2+1;
		}
	}
	res.damage = to_damage((double)rng.next()/(1ll<<32));
	res.speed = (double)rng.next()/(1ll<<32)*0.3+0.85;
	res.delay = to_delay((double)rng.next()/(1ll<<32));
	return res;
}

#endif
