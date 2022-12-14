// RNG used by TBOI.
#ifndef RNG_H
#define RNG_H 1

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
};

#endif
