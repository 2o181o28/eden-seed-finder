/* 
This `generator.cpp` aims to find a Eden seed with Experimental Treatment, low stats and bad items in boss rooms. Its purpose is to find the worst seeds.
*/
#include<bits/stdc++.h>
#include"seedstr.hpp"
//#define SEARCH_FOR_CERTAIN_CARD
//#define GREED
#define NO_HOME
#define NO_CARD_SEARCH
//#define MOMS_CHEST
#include"eden.hpp"
#include"item.hpp"
using namespace std;
using ll=long long;

const int items_eval[]={0,
2, 2, 0, 2, 2, 2, 2, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 2, 2, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 2, 2, 0, 2, 1, 0, 1, 0, 1, 0, 2, 2, 0, 0, 0, 1, 0, 1, 0, 1, 0, 2, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 2, 0, 0, 2, 2, 0, 1, 0, 2, 1, 0, 1, 1, 2, 2, 0, 1, 2, 0, 2, 2, 2, 1, 1, 0, 0, 2, 1, 0, 0, 0, 2, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 1, 1, 2, 2, 2, 1, 0, 1, 0, 0, 1, 2, 0, 1, 2, 2, 0, 1, 2, 2, 2, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 2, 2, 2, 0, 0, 0, 1, 1, 2, 2, 2, 0, 1, 0, 0, 2, 1, 0, 0, 0, 1, 0, 0, 0, 0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 1, 2, 0, 2, 0, 0, 0, 2, 1, 2, 0, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 0, 2, 2, 2, 0, 2, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 2, 1, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 1, 2, 0, 0, 2, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 2, 1, 0, 2, 1, 2, 2, 2, 0, 0, 0, 0, 2, 1, 1, 0, 1, 0, 1, 0, 0, 0, 2, 0, 2, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 2, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 2, 2, 1, 0, 0, 1, 0, 0, 0, 2, 0, 2, 0, 0, 2, 2, 0, 0, 0, 2, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 2, 0, 2, 0, 2, 1, 2, 2, 0, 0, 0, 2, 2, 2, 0, 0, 2, 1, 0, 0, 2, 0, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 2, 0, 0, 2, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 2, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 2, 0, 0, 0, 2, 2, 1, 1, 0, 0, 2, 0, 2, 1, 0, 0, 1, 2, 2, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 2, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0, 0, 2, 0, 2, 1, 0, 2, 0, 1, 1, 0, 2, 2, 2, 1, 0, 1, 0, 2, 2, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 1, 1, 1, 2, 0, 1, 0, 0, 0, 0, 2, 0, 0, 2, 0, 1, 2, 0, 0, 2, 0, 0, 2, 0, 0, 0, 0, 2, 1, 2, 2, 0, 0, 0, 2, 0, 2, 2, 2, 0, 0, 0, 0, 1, 0, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 2, 0, 2, 0, 1, 0, 1, 0, 0, 0, 0, 2, 1, 1, 0, 0, 0, 0, 1, 1, 2, 0, 2, 0, 2, 2, 0, 2, 2, 2, 0, 2, 0, 0, 0, 1, 2, 2, 1, 2, 0, 2, 1, 0, 2, 2, 2, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 2, 2, 2
};

int main(){
	srand(clock()+time(0));
	init_constants();
	
	const u32 exp_id=240; // ID of experimental treatment
	auto coll_rng = Rng{1, 0x1, 0x13, 0x3};
	auto coll_rng_mat = Matrix::from_rng(coll_rng).pow(exp_id+1);

	for(uint32_t seed=1;seed;seed++){
		auto [iseed, _]=init_seed(seed);
		auto playerInitRng = Rng{iseed, 0x1, 0xB, 0x10},	
			exp_rng = Rng{coll_rng_mat*playerInitRng.next(), 5, 9, 7};
		auto dseed=playerInitRng.advance(3);
		auto items=get_eden_items(dseed);
		if(items.passiveId!=exp_id || items_eval[items.activeId])continue;
		int v[7];iota(v,v+7,0);
		for(int i=7-1;i;i--)swap(v[i],v[exp_rng.next()%(i+1)]);
		// v[4] and v[5]: decreased stats; v[6]: unmodified stat
		if(v[4]+v[5]==5 && v[4]*v[5]==6){
			// decreased damage and tears
			auto stats=get_eden_stats(dseed);
	//		cout<<items.activeId<<" "<<items.passiveId<<" "<<items.card<<endl;
			auto dps=(30/(stats.delay+1)-0.5)*(stats.damage-1);
			if(dps<=3){
				ITEM_BLACKLIST[items.activeId]=ITEM_BLACKLIST[items.passiveId]=1;
				auto backup=ITEM_POOLS;
				shuffle_item_pools(seed);
				for(int stg=1;stg<=3;stg++){
					// award seed of boss room
					// only works when "Map Generated in 1 Loop" (high probability)
					auto award_seed=Rng{Rng{STAGE_SEED[stg], 35}.advance(4), 12}.advance(2);
					auto boss_item_id=get_collectible(2,true,Rng{award_seed, 35}.next());
					CUR_ROOM_BLACKLIST[boss_item_id]=0;
					if(items_eval[boss_item_id])goto fail;
				}
				printf("\"%s\",\n",seed_to_str(seed).data());
				fail: memset(ITEM_BLACKLIST, 0, sizeof ITEM_BLACKLIST);
				ITEM_POOLS=backup;
			}
		}
	}
	return 0;
}
