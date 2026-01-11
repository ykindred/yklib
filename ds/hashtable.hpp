#pragma once
#include "../head.hpp"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using __gnu_pbds::gp_hash_table;
using __gnu_pbds::null_type;
/*-------hashtable.hpp-------*/
// 防hack哈希表, 基于gp_hash_table, 速度快
// 支持整数类型作为键. 其他类型需先转换.
// 接口与unordered_set基本一致. 请注意最好不要使用count()
struct chash {
    // 你问我这堆数字是什么, 我也不知道
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = 
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
template<typename K, typename V>
using HashMap = gp_hash_table<K, V, chash>;
template<typename K>
using HashSet = gp_hash_table<K, null_type, chash>;
