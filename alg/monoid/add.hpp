#pragma once
#include "../../head.hpp"
template <typename S>
struct Monoid_Add {
    using value_type = S;
    static constexpr S op(const S &x, const S &y) noexcept { return x + y; }
    static constexpr S inv(const S &x) noexcept { return -x; }
    static constexpr S mul(const S &x, ll n) noexcept { return S(n) * x; }
    static constexpr S e() { return S(0); }
    static constexpr bool commute = true;
};