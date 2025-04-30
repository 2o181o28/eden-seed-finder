/* 
This `generator.cpp` aims to find a Eden seed with Experimental Treatment, low stats and no bombs. Its purpose is to find the worst seeds.
*/
#include<bits/stdc++.h>
#include"seedstr.hpp"
//#define SEARCH_FOR_CERTAIN_CARD
//#define GREED
#define NO_HOME
#define NO_CARD_SEARCH
//#define MOMS_CHEST
#include"eden.hpp"
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
			if(stats.bombs==0 && dps<=2.45){
				printf("\"%s\",\n",seed_to_str(seed).data());
			}
		}
	}
	return 0;
}
