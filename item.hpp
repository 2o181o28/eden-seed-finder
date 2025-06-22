#ifndef ITEM_H
#define ITEM_H 1

#include<bits/stdc++.h>
#include"rng.hpp"
#include"constants.hpp"

bool ITEM_BLACKLIST[ITEM_COUNT + 1], CUR_ROOM_BLACKLIST[ITEM_COUNT + 1];

// check wild item using Entity::InitSeed
int get_wild_item(uint32_t item_seed){
	if(Rng{item_seed, 35}.advance(1) % 87 != 86){
		return 0; // pickup is not a wild item
	}
	return 1; // We don't care which item it is
}

int pick_collectible(ItemPool &pool, bool dec_weight, double rng_val){
	int repick_cnt=10, chosen=0, chosen_idx;
	// omitted: When has trinket NO!, set repick count to 20
	do{
		double sum=0, frac=0;
		for(const auto &x:pool.pool){
			sum += x.weight;
			if(sum<=rng_val)continue;
			frac = (sum-rng_val)/x.weight;
			// printf("id=%d FRAC=%.10lf\n",x.id, frac);
			// omitted: some unknown checks
			if(1-frac < x.weight_now/x.weight && !ITEM_BLACKLIST[x.id] &&
				!CUR_ROOM_BLACKLIST[x.id]){
				chosen=x.id, chosen_idx = &x-pool.pool.data();
				break;
			}
			break;
		}
		if(repick_cnt < 1) break;
		rng_val=pool.total_weight*frac; // interesting... not another RNG call?
		if(rng_val == pool.total_weight)
			rng_val /= 3.37317; // meaning unknown
		repick_cnt--;
	}while(!chosen);
	if(chosen){
		auto &x=pool.pool[chosen_idx];
		if(x.weight_now>0 && dec_weight){
			x.weight_now -= x.dec_by;
			if(x.weight_now < x.remove_on){
				x.weight_now = 0;
				ITEM_BLACKLIST[chosen] = true;
			}
		}
		return chosen;
	}
	return 0;
}

int get_collectible(int pool_id, bool dec_weight, u32 seed){
	// omitted: check trinket NO; check TMTRAINER; check CHAOS; curated daily run effects
	auto r=Rng{seed, 0x1, 0xb, 0x6};
	auto &pool = ITEM_POOLS[pool_id];
	auto rnd_float = r.next()*2.328306e-10;
	auto item_ID = pick_collectible(pool, dec_weight, rnd_float*pool.total_weight);
	// omitted: achievement check
	if(dec_weight) CUR_ROOM_BLACKLIST[item_ID]=true;
	return item_ID;
	// omitted: exhausting item pool (breakfasting); Magic Skin; Rosary Beads; etc.
}

void shuffle_item_pools(u32 start_seed){
	// STAGE_COUNT+1 stage seeds; player init seed; two next() calls
	const auto start_rng_mat=Matrix::from_rng({1, 0x3, 0x17, 0x19}).pow(STAGE_COUNT+1+1+2);
	auto seed=start_rng_mat*start_seed; // seed for item pools init function
	
	// 1 before loading item pools; 2 for each item pool
	const auto new_rng_mat=Matrix::from_rng({1, 0x1, 0x9, 0x1d}).pow(1+2*ITEM_POOLS_COUNT);
	seed=new_rng_mat*seed;
	
	std::mt19937 mt_rng{seed};
	for(auto &[_, v]:ITEM_POOLS){
		auto s=v.size();assert(s>0);
		for(int i=s-1;i;i--)std::swap(v[i],v[mt_rng()%(i+1)]);
	}
}

#endif
