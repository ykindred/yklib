#pragma once
#include "../head.hpp"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>


using __gnu_pbds::gp_hash_table;
using __gnu_pbds::null_type;

// 防hack哈希
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

    // 对于pair的支持, 要求T1, T2支持对uint64_t的隐式转换
    template<typename T1, typename T2>
    size_t operator()(const pair<T1, T2>& x) const {
        static const uint64_t FIXED_RANDOM = 
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64((uint64_t)x.first + FIXED_RANDOM) ^ 
               (splitmix64((uint64_t)x.second + FIXED_RANDOM) >> 1);
    }

    // 对于string的支持
    size_t operator()(const string& s) const {
        static const uint64_t FIXED_RANDOM = 
            chrono::steady_clock::now().time_since_epoch().count();
        uint64_t hash = 0;
        for (char c : s) {
            hash = hash * 131 + c; // 简单的多项式哈希，速度快
        }
        // 配合强力哈希
        return splitmix64(hash + FIXED_RANDOM);
    }
};

// 使用方法: HashMap<int, int> mp;
template<typename K, typename V>
using HashMap = gp_hash_table<K, V, chash>;

// 使用方法: HashSet<int> st;
template<typename K>
using HashSet = gp_hash_table<K, null_type, chash>;

// 接口与unordered_set基本一致. 请注意最好不要使用count()