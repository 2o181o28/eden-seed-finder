/*
this `generator.cpp` aims to find a greed mode seed that Eden starts with Dad's key, 9 Volt/Sharp Plug and a Chaos card, and almost all the greed exit rooms has no enemies. It is intended for greed mode speedruns.
*/
#include<bits/stdc++.h>
#include"seedstr.hpp"
#define SEARCH_FOR_CERTAIN_CARD
#define GREED
//#define NO_CARD_SEARCH
//#define MOMS_CHEST
#include"eden.hpp"
#include"item.hpp"
using namespace std;
using ll=long long;

int main(){
	srand(clock()+time(0));
	init_constants();

	for(uint32_t seed=1;seed;seed++){
		auto [dseed, _]=drop_seed(seed);
/*		int wild_item = get_wild_item(item_seed);
		if(wild_item == 0) continue;*/
		EdenItems items=get_eden_items(dseed);
//		cout<<items.activeId<<" "<<items.passiveId<<" "<<items.card<<endl;
		
		if(items.activeId==175
			&& (items.passiveId==116 || items.passiveId==205)
			&& items.card == 42){
			printf("\"%s\",\n",seed_to_str(seed).data());
			//break;
		}
	}
	return 0;
}
