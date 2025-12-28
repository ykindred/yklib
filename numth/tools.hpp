#pragma once
#include "../head.hpp"
/*---------tools.hpp---------*/
// if you don't know what you are doing, please use numth/modint/ instead
namespace numth {
    inline ll norm(ll x, ll mod) { ll tmp = x % mod; return (tmp < 0) ? (tmp + mod) : tmp; }
    inline ll mul(ll a, ll b, ll mod) { auto tmp = (i128)a * b % mod; return (tmp < 0) ? (tmp + mod) : tmp; }
    inline ll add(ll a, ll b, ll mod) { return norm(a + b, mod); }
    inline ll sub(ll a, ll b, ll mod) { return norm(a - b, mod); }
    inline ll pow(ll a, ll b, ll mod) { 
        ll ret = 1;
        a = norm(a, mod);
        for (; b; b >>= 1, a = mul(a, a, mod)) if (b & 1) ret = mul(ret, a, mod); 
        return ret;
    }
    inline ll inv(ll a, ll mod_prime) { return pow(a, mod_prime - 2, mod_prime); }
}
/*---------------------------*/