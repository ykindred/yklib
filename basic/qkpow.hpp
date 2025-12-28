#pragma once
#include "../numth/tools.hpp"
#include "../head.hpp"
#include "inv.hpp"
/*---------qkpow.hpp---------*/

// calculate a ** b mod m
template <typename T> T qkpow(T a, ll b) {
    // fit for class like ModInt, BigInt, Matrix, etc, O(log b)
    if (b < 0) return qkpow(inv(a), -b);
    assert(b >= 0);
    T ret(1);
    while (b > 0) {
        if (b & 1) {
            ret = ret * a;
        }
        a = a * a;
        b >>= 1;
    }
    return ret;
}
inline ll qkpow(ll a, ll b, ll mod) {
    // for integers, O(log b)
    ll ret = 1;
    a %= mod;
    while (b > 0) {
        if (b & 1) {
            ret = numth::mul(ret, a, mod);
        }
        a = numth::mul(a, a, mod);
        b >>= 1;
    }
    return ret;
}
/*---------------------------*/