#include<bits/stdc++.h>
#include"seedstr.hpp"
#define SEARCH_FOR_CERTAIN_CARD
#include"eden.hpp"
using namespace std;
using ll=long long;

int main(){
	srand(clock()+time(0));
	init_constants();

	for(uint32_t seed=1;seed;seed++){
		uint32_t dseed=drop_seed(seed);
		EdenItems items=get_eden_items(dseed);
//		cout<<items.activeId<<" "<<items.passiveId<<" "<<items.card<<endl;
		
		if(items.activeId==422
			&& (items.passiveId==169 || items.passiveId==261 || items.passiveId==118 || items.passiveId==153)
			&& (items.card==12 || items.card==52)){
			if((items.passiveId==169 || items.passiveId==261) && items.card==12)
				continue;
			printf("\"%s\",\n",seed_to_str(seed).data());
			//break;
		}
	}
	return 0;
}
