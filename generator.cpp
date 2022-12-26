/* 
This `generator.cpp` aims to find a Eden seed with the Glowing Hourglass, Sacred Heart or other powerful passive items, and the Home floor containing both Mom's Knife and a wild item in the rightmost small room. It is intended for the Beast Ending speedruns. 
*/
#include<bits/stdc++.h>
#include"seedstr.hpp"
//#define SEARCH_FOR_CERTAIN_CARD
//#define GREED
#define NO_CARD_SEARCH
//#define MOMS_CHEST
#include"eden.hpp"
#include"item.hpp"
using namespace std;
using ll=long long;

int main(){
	srand(clock()+time(0));
	init_constants();

	for(uint32_t seed=1;seed;seed++){
		auto [dseed, item_seed]=drop_seed(seed);
		int wild_item = get_wild_item(item_seed);
		if(wild_item == 0) continue;
		EdenItems items=get_eden_items(dseed);
//		cout<<items.activeId<<" "<<items.passiveId<<" "<<items.card<<endl;
		
		if(items.activeId==422
			&& (items.passiveId==114 || items.passiveId==415 || items.passiveId==310 || items.passiveId==182)
			&& wild_item != 0){
			printf("\"%s\",\n",seed_to_str(seed).data());
			//break;
		}
	}
	return 0;
}
