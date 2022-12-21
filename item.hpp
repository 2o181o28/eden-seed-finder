#ifndef ITEM_H
#define ITEM_H 1

#include<bits/stdc++.h>
#include"rng.hpp"

// Entity::InitSeed to wild item id
int get_wild_item(uint32_t item_seed){
	if(Rng{item_seed, 35}.advance(1) % 87 != 86){
		return 0; // pickup is not a wild item
	}
	return 1; // We don't care which item it is
}

#endif
