#pragma once
#include "../head.hpp"
#include "tools.hpp"
/*---------exgcd.hpp---------*/
namespace numth {
    // Extended Euclid
    // A >= 0 && B >= 0
    // find [x, y, gcd(A, B)] such that Ax + By = gcd(A, B), O(log min(A, B))
    inline tuple<ll, ll, ll> exgcd(ll A, ll B) {
        if (B == 0) return { 1, 0, A };
        auto [x, y, g] = exgcd(B, A % B);
        return { y, x - A / B * y, g };
    }
    inline ll inv_exgcd(ll a, ll mod) { 
        auto [x, y, g] = exgcd(a, mod);
        if (a == 0 || g != 1) return -1; // not exist
        return norm(x, mod);
    }
}
/*---------------------------*/