#pragma once
#include "../head.hpp"
/*---------tools.hpp---------*/
// if you don't know what you are doing, please use numth/modint/ instead
namespace numth {
    inline ll mul(ll a, ll b, ll mod) { return (i128)a * b % mod; }
    inline ll add(ll a, ll b, ll mod) { return ((a % mod) + (b % mod)) % mod; }
    inline ll sub(ll a, ll b, ll mod) { return ((a % mod) - (b % mod) + mod) % mod; }
    inline ll pow(ll a, ll b, ll mod) { 
        ll ret = 1 % mod;
        for (; b >>= 1; a = mul(a, a, mod)) { 
            if (b & 1) ret = mul(ret, a, mod); 
        }
        return ret;
    }
    inline ll inv(ll a, ll mod) { return pow(a, mod - 2, mod); }
}
/*---------------------------*/