#include "../head.hpp"
#include "factor.hpp"

inline ll euler_phi(ll n) {
    auto pf = factor(n);
    for (auto&& [p, e]: pf) n -= n / p;
    return n;
}