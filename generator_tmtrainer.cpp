/* 
This `generator.cpp` aims to find a Eden seed with the Glowing Hourglass, TMTRAINER, and the mom's chest in Home floor containing a glitched item with the effect of Mega Mush. It is intended for the Beast Ending speedruns. 
*/
#include<bits/stdc++.h>
#include"seedstr.hpp"
//#define SEARCH_FOR_CERTAIN_CARD
//#define GREED
#define NO_CARD_SEARCH
#define MOMS_CHEST
#include"eden.hpp"
#include"item.hpp"
using namespace std;
using ll=long long;

int main(){
	srand(clock()+time(0));
	init_constants();

	for(uint32_t seed=1;seed;seed++){
		auto [dseed, item_seed]=drop_seed(seed);
		EdenItems items=get_eden_items(dseed);
//		cout<<items.activeId<<" "<<items.passiveId<<" "<<items.card<<endl;
		
		if(items.activeId==422
			&& (items.passiveId==721)){
			printf("{\"%s\", %u},\n",seed_to_str(seed).data(), item_seed);
			//break;
		}
	}
	return 0;
}
