// RNG used by TBOI.
#ifndef RNG_H
#define RNG_H 1

// https://www.jstatsoft.org/article/view/v008i14/xorshift.pdf
const int SHIFT_TB[][3] = {
 {1, 3,10}, { 1, 5,16}, { 1, 5,19}, { 1, 9,29}, { 1,11, 6}, { 1,11,16}, { 1,19, 3}, { 1,21,20}, { 1,27,27}, 
 { 2, 5,15}, { 2, 5,21}, { 2, 7, 7}, { 2, 7, 9}, { 2, 7,25}, { 2, 9,15}, { 2,15,17}, { 2,15,25}, { 2,21, 9}, 
 { 3, 1,14}, { 3, 3,26}, { 3, 3,28}, { 3, 3,29}, { 3, 5,20}, { 3, 5,22}, { 3, 5,25}, { 3, 7,29}, { 3,13, 7}, 
 { 3,23,25}, { 3,25,24}, { 3,27,11}, { 4, 3,17}, { 4, 3,27}, { 4, 5,15}, { 5, 3,21}, { 5, 7,22}, { 5, 9,7 }, 
 { 5, 9,28}, { 5, 9,31}, { 5,13, 6}, { 5,15,17}, { 5,17,13}, { 5,21,12}, { 5,27, 8}, { 5,27,21}, { 5,27,25}, 
 { 5,27,28}, { 6, 1,11}, { 6, 3,17}, { 6,17, 9}, { 6,21, 7}, { 6,21,13}, { 7, 1, 9}, { 7, 1,18}, { 7, 1,25}, 
 { 7,13,25}, { 7,17,21}, { 7,25,12}, { 7,25,20}, { 8, 7,23}, { 8,9,23 }, { 9, 5,1 }, { 9, 5,25}, { 9,11,19}, 
 { 9,21,16}, {10, 9,21}, {10, 9,25}, {11, 7,12}, {11, 7,16}, {11,17,13}, {11,21,13}, {12, 9,23}, {13, 3,17}, 
 {13, 3,27}, {13, 5,19}, {13,17,15}, {14, 1,15}, {14,13,15}, {15, 1,29}, {17,15,20}, {17,15,23}, {17,15,26}, 
};
const int SHIFT_TB_LEN = sizeof(SHIFT_TB) / sizeof(int) / 3;
static_assert(SHIFT_TB_LEN == 81, "unreachable!");

struct Rng{
	uint32_t seed;
	int shift1, shift2, shift3;
	uint32_t next(){
		auto num = seed;
		num ^= num >> shift1;
		num ^= num << shift2;
		num ^= num >> shift3;
		return seed = num;
	}
	
	uint32_t advance(uint32_t k){
		uint32_t res;
		do{
			res = next();
		}while(k--);
		return res;
	}
	
	Rng(uint32_t s, int s1, int s2, int s3):
		seed(s), shift1(s1), shift2(s2), shift3(s3){}
	
	// RNG::SetSeed
	Rng(uint32_t s, int idx): seed(s){
		shift1 = SHIFT_TB[idx][0];
		shift2 = SHIFT_TB[idx][1];
		shift3 = SHIFT_TB[idx][2];
	}
};

#endif
