/* 
This `generator.cpp` aims to find a Eden seed with the Wiz, 1 red heart, low stats and no bombs. Its purpose is to find the worst seeds.
*/
#include<bits/stdc++.h>
#include"seedstr.hpp"
//#define SEARCH_FOR_CERTAIN_CARD
//#define GREED
#define NO_CARD_SEARCH
//#define MOMS_CHEST
#include"eden.hpp"
using namespace std;
using ll=long long;

int main(){
	srand(clock()+time(0));
	init_constants();

	for(uint32_t seed=1;seed;seed++){
		auto [dseed, _]=drop_seed(seed);
		auto items=get_eden_items(dseed);
		auto stats=get_eden_stats(dseed);
//		cout<<items.activeId<<" "<<items.passiveId<<" "<<items.card<<endl;
		
		if(items.passiveId==358 && stats.hearts==2 &&
			stats.soul_hearts==0 && stats.bombs==0 && 
			stats.damage*30/(stats.delay+1)<=2.6*30/(15+1) &&
			!(stats.delay>15 && stats.damage<2.6)){
			printf("\"%s\",\n",seed_to_str(seed).data());
			//break;
		}
	}
	return 0;
}
