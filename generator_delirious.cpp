/*
this `generator.cpp` aims to find a normal mode seed that Eden starts with Delirious, Scapular/Cancer and an Emperor card. It is intended for repentance+.
*/
#include<bits/stdc++.h>
#include"seedstr.hpp"
#define SEARCH_FOR_CERTAIN_CARD 5
#define NO_HOME
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
		
		if(items.activeId==510
			&& (items.passiveId==142 || items.passiveId==301)
			&& items.card == 5){
			printf("\"%s\",\n",seed_to_str(seed).data());
			//break;
		}
	}
	return 0;
}
