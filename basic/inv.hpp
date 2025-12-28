#pragma once
#include "../head.hpp"
#include "../numth/equations.hpp"
/*----------inv.hpp----------*/

// find x such that ax === 1 (mod m)
template <typename T, typename std::enable_if<!std::is_integral<T>::value, int>::type = 0>
inline T inv(T A) { 
    // fit for Class like ModInt, Matrix, etc, O(div)
    return T(1) / A;
}
inline ll inv(ll a, ll mod) { 
    // for integers, O(log mod)
    assert(a != 0 && "inv zero");
    return solve_LCE(a, 1LL, mod); 
}
/*---------------------------*/