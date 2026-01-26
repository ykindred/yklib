#pragma once
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using i8 = signed char;             // take care when input/output
using i32 = int;
using i64 = ll;
using i128 = __int128_t;
using u32 = unsigned int;
using u64 = unsigned long long;
using u128 = __uint128_t;
constexpr int INF = 0x3f3f3f3f;
constexpr ll INFLL = 2'020'000'000'000'000'000;
inline u64 lowbit(u64 x) { return x & (-x); }
inline u64 ctz(u64 x) { return x == 0 ? -1 : __builtin_ctzll(x); }
inline u64 clz(u64 x) { return x == 0 ? -1 : __builtin_clzll(x); }
template<typename T> using max_heap = priority_queue<T>;
template<typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
inline int __INIT__ = []() {
    ios::sync_with_stdio(false), cin.tie(nullptr);
    return 0;
}();