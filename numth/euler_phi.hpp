#include "../head.hpp"
#include "factor_fast.hpp"

inline ll euler_phi(ll n) {
    auto pf = factor_fast(n);
    for (auto&& [p, e]: pf) n -= n / p;
    return n;
}