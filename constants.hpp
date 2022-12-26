/* Some constants about TBOI. They may change as the game updates. */
#ifndef CONSTANTS_H
#define CONSTANTS_H 1
#include<bits/stdc++.h>

const int ITEM_COUNT=732;
const int STAGE_COUNT=13;

bool NO_EDEN[ITEM_COUNT + 1], IS_ACTIVE[ITEM_COUNT + 1];

void init_constants(){
	for(int i=1; i<=ITEM_COUNT; i++)
		NO_EDEN[i]=true;

	std::fstream s("item_data/items_metadata.xml",s.in);
	assert(s.is_open());
	
	char buf[2010];
	
	while(s.getline(buf,sizeof buf)){
		char *pos=strstr(buf,"id=\"");
		if(!pos) continue;
		int id=strtol(pos+strlen("id=\""),NULL,10);
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
		char *pos=strstr(buf,"id=\"");
		if(!pos) continue;
		int id=strtol(pos+strlen("id=\""),NULL,10);
		if(id<=0 || id>ITEM_COUNT) continue;
		
		if(strstr(buf,"active"))
			IS_ACTIVE[id]=true;
	}
}

#endif
