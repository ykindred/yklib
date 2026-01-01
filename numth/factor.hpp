#pragma once
#include "../others/random/rng64.hpp"
#include "modint/mongomery_modint.hpp"
#include "primetest.hpp"

// pollard-rho, O(n^0.25)
template <typename mint>
ll rho(ll n, ll c) {
    assert(n > 1);
    const mint cc(c);
    auto f = [&](mint x) { return x * x + cc; };
    mint x = 1, y = 2, z = 1, q = 1;
    ll g = 1;
    const ll m = 1LL << (__lg(n) / 5);
    for (ll r = 1; g == 1; r <<= 1) {
        x = y;
        for (int _ = 0; _ < r; _++) y = f(y);
        for (ll k = 0; k < r && g == 1; k += m) {
            z = y;
            for (int _ = 0; _ < min(m, r - k); _++) y = f(y), q *= x - y;
            g = gcd(q.val(), n);
        }
    }
    if (g == n) do {
        z = f(z);
        g = gcd((x - z).val(), n);
    } while (g == 1);
    return g;
}

// find any prime factor of n, O(n^0.25)
inline ll find_prime_factor(ll n) {
    assert(n > 1);
    if (primetest(n)) return n;
    for (int i = 0; i < 100; i++) {
        ll m = 0;
        if (n < (1 << 30)) {
            using mint = Mongomery_modint_32<20231025>;
            mint::set_mod(n);
            m = rho<mint>(n, RNG(0, n));
        } 
        else {
            using mint = Mongomery_modint_64<20231025>;
            mint::set_mod(n);
            m = rho<mint>(n, RNG(0, n));
        }
        if (primetest(m)) return m;
        n = m;
    }
    assert(0);
    return -1;
}

// return vector of { prime, exponent }, O(n^0.25)
inline vector<pair<ll, int>> factor(ll n) {
    assert(n >= 1);
    vector<pair<ll, int>> pf;
    for (int p = 2; p < 100; p++) {
        if (p * p > n) break;
        if (n % p == 0) {
            ll e = 0;
            do { n /= p, e += 1; } while (n % p == 0);
            pf.emplace_back(p, e);
        }
    }
    while (n > 1) {
        ll p = find_prime_factor(n);
        ll e = 0;
        do { n /= p, e += 1; } while (n % p == 0);
        pf.emplace_back(p, e);
    }
    sort(pf.begin(), pf.end());
    return pf;
}

// with sieve precalculated minimum prime factors (minp)
// return vector of { prime, exponent }, O(log n)
inline vector<pair<ll, int>> factor_by_lpf(ll n, vector<int>& minp) {
    vector<pair<ll, int>> res;
    while (n > 1) {
        int p = minp[n];
        int e = 0;
        while (n % p == 0) {
            n /= p;
            ++e;
        }
        res.emplace_back(p, e);
    }
    return res;
}