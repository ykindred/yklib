#pragma once
#include <bits/stdc++.h>
using namespace std;
using i8 = signed char;             // take care when input/output
using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128_t;
using u8 = unsigned char;           // take care when input/output
using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;
using ll = i64;
using ull = u64;
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 2'020'000'000'000'000'000;
inline u64 lowbit(u64 x) { return x & (-x); }
inline u64 ctz(u64 x) { return x == 0 ? -1 : __builtin_ctzll(x); }
template<typename T> using max_heap = priority_queue<T>;
template<typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
inline int __INIT__ = []() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    return 0;
}();