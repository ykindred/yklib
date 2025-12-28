#pragma once
#include "../head.hpp"
/*---------tools.hpp---------*/
// if you don't know what you are doing, please use numth/modint/ instead
namespace numth {
    inline ll norm(ll x, ll mod) { return (x % mod + mod) % mod; }
    inline ll mul(ll a, ll b, ll mod) { return norm((i128)a * b, mod); }
    inline ll add(ll a, ll b, ll mod) { return norm(a + b, mod); }
    inline ll sub(ll a, ll b, ll mod) { return norm(a - b, mod); }
    inline ll pow(ll a, ll b, ll mod) { 
        ll ret = 1;
        a = norm(a, mod);
        for (; b;b >>= 1, a = mul(a, a, mod)) if (b & 1) ret = mul(ret, a, mod); 
        return ret;
    }
    inline ll inv(ll a, ll mod_prime) { return pow(a, mod_prime - 2, mod_prime); }
}
/*---------------------------*/