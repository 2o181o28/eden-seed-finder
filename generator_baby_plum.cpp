/* 
This `generator.cpp` aims to find a seed with Baby Plum explosion. 
*/
#include<bits/stdc++.h>
#include"seedstr.hpp"
#include"rng.hpp"
using namespace std;
using ll=long long;

const u32 stt=0xdedbb;

int main(){
	auto spawn_mat_inv1 = Matrix::from_rng(Rng{1, 35}).inv(),
		spawn_mat_inv2 = Matrix::from_rng(Rng{1, 11}).inv(),
		stage_mat_inv = spawn_mat_inv1.pow(5)*
						Matrix::from_rng(Rng{1, 12}).inv().pow(2),
		init_mat_inv = Matrix::from_rng(Rng{1, 0x3, 0x17, 0x19}).inv().pow(2),
		combined_mat = init_mat_inv * stage_mat_inv;
	for(u32 seed=stt;;seed+=1<<20){
		// seed: the init seed of baby plum
		u32 tmp = spawn_mat_inv1 * seed;
		for(int k:{0,2,6,11}){
			u32 spawn_seed = spawn_mat_inv2.pow(k+1)*tmp; // room spawn seed
			u32 start_seed = combined_mat * spawn_seed;
			printf("{\"%s\", %u},\n", seed_to_str(start_seed).data(), seed);
		}
		if(seed+(1<<20)==stt)break;
	}
	return 0;
}
