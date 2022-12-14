#ifndef SEEDSTR_H
#define SEEDSTR_H 1
#include<string>

/* Generate seed string from 32bit integer
   Source: https://www.reddit.com/r/bindingofisaac/comments/2wvp6h/comment/csdppvx/
*/
std::string seed_to_str(uint32_t seed){
	const char* table="ABCDEFGHJKLMNPQRSTWXYZ01234V6789";
	
	uint32_t cksum=0, k=seed;
	do{
		cksum = (cksum + (k & 0xFF)) & 0xFF;
		cksum = (2 * cksum + (cksum >> 7)) & 0xFF;
		k >>= 5;
	}while(k);
	
	uint64_t s= ((seed ^ 0xFEF7FFDull) << 8) | cksum;
	std::string str;
	for(int i=7;~i;i--){
		str += table[s>>(5*i)&31];
		if(i==4)
			str += ' ';
	}
	
	return str;
}

#endif
