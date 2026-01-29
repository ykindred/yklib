#include "../head.hpp"
#include "tools.hpp"
#include "primetest.hpp"

namespace numth {
    // 简易版pollard-rho算法
    inline ll rho(ll n) {
        if (!(n & 1)) return 2;
        ll x = 0, y = 0, prod = 1;
        auto f = [&](ll x) -> ll {
            return mul(x, x, n) + 5; // 这里的种子为 1 时能被 hack，取 5 到目前为止没有什么问题
        };
        for (int t = 30, z = 0; t % 64 || gcd(prod, n) == 1; ++t) {
            if (x == y) x = ++z, y = f(x);
            if (ll q = mul(prod, x + n - y, n)) prod = q;
            x = f(x), y = f(f(y));
        }
        return gcd(prod, n);
    }
    inline vector<ll> factorize(ll x) {
        vector<ll> res;
        auto f = [&](auto f, ll x) {
            if (x == 1) return;
            if (primetest(x)) return res.push_back(x);
            ll y = rho(x);
            f(f, y), f(f, x / y);
        };
        f(f, x), sort(res.begin(), res.end());
        return res;
    }
}