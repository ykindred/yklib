#pragma once
#include "../../head.hpp"

// to check if T has get_mod
struct has_mod_impl {
    template <class T>
    static auto check(T &&x) -> decltype(x.get_mod(), std::true_type{});
    template <class T>
    static auto check(...) -> std::false_type;
};

template <class T>
class has_mod : public decltype(has_mod_impl::check<T>(std::declval<T>())) {};

// calculate inverses between 1 and n, return inv of n. note that n < mod
template <typename mint>
mint inv(int n) {
    static const int mod = mint::get_mod();
    static vector<mint> dat = {0, 1};
    assert(0 <= n);
    if (n >= mod) n %= mod;
    while (dat.size() <= n) {
        int k = dat.size();
        int q = (mod + k - 1) / k;
        dat.emplace_back(dat[k * q - mod] * mint::raw(q));
    }
    return dat[n];
}

template <>
inline double inv<double>(int n) {
    assert(n != 0);
    return 1.0 / n;
}

// calculate fact between 1 and n
template <typename mint>
mint fact(int n) {
    static const int mod = mint::get_mod();
    assert(0 <= n && n < mod);
    static vector<mint> dat = {1, 1};
    while (dat.size() <= n) dat.emplace_back(dat[dat.size() - 1] * mint(dat.size()));
    return dat[n];
}

// calculate inv of fact between 1 and n
template <typename mint>
mint fact_inv(int n) {
    static vector<mint> dat = {1, 1};
    if (n < 0) return mint(0);
    while (dat.size() <= n) dat.emplace_back(dat[dat.size() - 1] * inv<mint>((int)dat.size()));
    return dat[n];
}

// calculate factinvs product
template <class mint, class... Ts>
mint fact_invs(Ts... xs) {
    return (mint(1) * ... * fact_inv<mint>(xs));
}

// calculate n! / (k_1! k_2! ... k_i!)
template <typename mint, class Head, class... Tail>
mint multinomial(Head &&head, Tail &&...tail) {
    return fact<mint>(head) * fact_invs<mint>(std::forward<Tail>(tail)...);
}

// calculate nCr cached
template <typename mint>
mint ncr_dense(int n, int k) {
    assert(n >= 0);
    if (k < 0 || n < k) return 0;
    static vector<vector<mint>> C;
    static int H = 0, W = 0;
    auto calc = [&](int i, int j) -> mint {
        if (i == 0) return (j == 0 ? mint(1) : mint(0));
        return C[i - 1][j] + (j ? C[i - 1][j - 1] : 0);
    };
    if (W <= k) {
        for (int i = 0; i < H; i++) {
        C[i].resize(k + 1);
        for (int j = W; j < k + 1; j++) {
            C[i][j] = calc(i, j); 
            }
        }
        W = k + 1;
    }
    if (H <= n) {
        C.resize(n + 1);
        for (int i = H; i < n + 1; i++) {
            C[i].resize(W);
            for (int j = 0; j < W; j++) { 
                C[i][j] = calc(i, j); 
            }
        }
        H = n + 1;
    }
    return C[n][k];
}

// calculate nCr
// if large then directly calculate
// if dense then calculate by Yang Hui triangle
template <typename mint, bool large = false, bool dense = false>
mint ncr(ll n, ll k) {
    assert(n >= 0);
    if (k < 0 || n < k) return 0;
    if constexpr (dense) return ncr_dense<mint>(n, k);
    if constexpr (!large) return multinomial<mint>(n, k, n - k);
    k = min(k, n - k);
    mint x(1);
    for (int i = 0; i < k; i++) x *= mint(n - i);
    return x * fact_inv<mint>(k);
}

// faster inv of nCr
template <typename mint, bool large = false>
mint ncr_inv(ll n, ll k) {
    assert(n >= 0);
    assert(0 <= k && k <= n);
    if (!large) return fact_inv<mint>(n) * fact<mint>(k) * fact<mint>(n - k);
    return mint(1) / ncr<mint, 1>(n, k);
}

// stars and bars, find the number of solutions of x_1 + ... + x_n = d that both non-negative
// C(n + d - 1, d)
template <typename mint, bool large = false, bool dense = false>
mint ncr_neg(ll n, ll d) {
    assert(n >= 0);
    if (d < 0) return mint(0);
    if (n == 0) {
        return (d == 0 ? mint(1) : mint(0));
    }
    return ncr<mint, large, dense>(n + d - 1, d);
}

// lucas theorem
template<typename mint>
mint lucas(ll n, ll m) {
    if (m == 0) return 1;
    int mod = mint::get_mod();
    return ncr<mint>(n % mod, m % mod) * lucas<mint>(n / mod, m / mod);
}