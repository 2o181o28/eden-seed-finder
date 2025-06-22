/* Some constants about TBOI. They may change as the game updates. */
#ifndef CONSTANTS_H
#define CONSTANTS_H 1
#include<bits/stdc++.h>

const int ITEM_COUNT=732;
const int STAGE_COUNT=13;
const int ITEM_POOLS_COUNT=0x1f;

bool NO_EDEN[ITEM_COUNT + 1], IS_ACTIVE[ITEM_COUNT + 1];

struct ItemPoolEntry{
	int id;
	double weight, weight_now, dec_by, remove_on;
};
struct ItemPool{
	double total_weight=0;
	std::vector<ItemPoolEntry> pool;
	void append(const ItemPoolEntry &x){
		total_weight+=x.weight;
		pool.push_back(x);
	}
};
std::vector<ItemPool> ITEM_POOLS;

void init_item_data(){
	for(int i=1; i<=ITEM_COUNT; i++)
		NO_EDEN[i]=true;

	std::fstream s("item_data/items_metadata.xml",s.in);
	assert(s.is_open());
	
	char buf[2010];
	
	while(s.getline(buf,sizeof buf)){
		if(strstr(buf,"!--")) continue; // skip comment
		char *pos=strstr(buf,"id=\"");
		if(!pos) continue;
		int id=strtol(pos+strlen("id=\""),nullptr,10);
		if(id<=0 || id>ITEM_COUNT) continue;
		
		if(!strstr(buf,"noeden")
		#ifdef GREED
		 && !strstr(buf, "nogreed")
		#endif
		)
			NO_EDEN[id]=false;
	}
	
	s.close();
	s.open("item_data/items.xml",s.in);
	assert(s.is_open());
	
	while(s.getline(buf,sizeof buf)){
		if(strstr(buf,"!--")) continue; // skip comment
		char *pos=strstr(buf,"id=\"");
		if(!pos) continue;
		int id=strtol(pos+strlen("id=\""),nullptr,10);
		if(id<=0 || id>ITEM_COUNT) continue;
		
		if(strstr(buf,"active"))
			IS_ACTIVE[id]=true;
	}
}

void init_item_pools(){
	std::fstream s("item_data/itempools.xml",s.in);
	assert(s.is_open());
	
	char buf[2010];
	
	while(s.getline(buf,sizeof buf)){
		if(strstr(buf,"!--")) continue; // skip comment
		char *pos=strstr(buf,"Name=\"");
		if(pos){
			ITEM_POOLS.push_back({});
			continue;
		}
		pos=strstr(buf,"Id=\"");
		if(!pos) continue;
		int id=strtol(pos+strlen("Id=\""),nullptr,10);
		
		auto parse=[&](const char *s){
			pos=strstr(buf,s);
			assert(pos);
			return strtod(pos+strlen(s),nullptr);
		};
		auto weight=parse("Weight=\"");
		ITEM_POOLS.back().append({
			id, weight, weight,
			parse("DecreaseBy=\""),
			parse("RemoveOn=\"")
		});
	}
	
	assert(ITEM_POOLS.size()==ITEM_POOLS_COUNT);
}

void init_constants(){
	init_item_data();
	init_item_pools();
}

#endif
