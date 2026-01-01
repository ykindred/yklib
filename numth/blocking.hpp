#include "../head.hpp"

namespace numth {
    // call f(q, l, r), q = floor(n / i), i in [l, r), O(sqrt(N))
    template <typename F>
    void block_floor(ll N, F f, bool Q_ASC = true, bool INCLUDE_Q_IS_0 = false) {
        ll sq = sqrtl(N);
        ll n = (sq * sq + sq <= N ? sq : sq - 1);
        if (Q_ASC) {
            if (INCLUDE_Q_IS_0) f(0, N + 1, INFLL);
            for (ll q = 1; q <= n; ++q) { f(q, N / (q + 1) + 1, N / q + 1); }
            for (ll l = sq; l >= 1; --l) { f(N / l, l, l + 1); }
        }
        else {
            for (ll l = 1; l <= sq; ++l) { f(N / l, l, l + 1); }
            for (ll q = n; q >= 1; --q) { f(q, N / (q + 1) + 1, N / q + 1); }
            if (INCLUDE_Q_IS_0) f(0, N + 1, INFLL);
        }
    }

    // call f(q, l, r), q = floor(n / i), i in [l, r), O(sqrt(N))
    template <typename F>
    void block_ceil(ll N, F f) {
        assert(N <= (1LL << 50));
        ll sq = sqrtl(N);
        ll prev = INFLL;
        for (int q = 1; q <= sq; ++q) {
            ll x = (N + q - 1) / q;
            f(q, x, prev), prev = x;
        }
        int n = (N <= sq * sq + sq ? sq : sq + 1);
        if (N == sq * sq) --n;
        for (int l = n; l >= 1; --l) { f((N + l - 1) / l, l, l + 1); }
    }

    // call f(ll qn, ll qm, ll l, ll r), O(sqrt(N) + sqrt(M))
    template <typename F>
    void block_2d(ll N, ll M, F f) {
        if (N == 0 || M == 0) return;
        ll lim = min(N, M);
        for (ll l = 1, r; l <= lim; l = r) {
            ll qn = N / l;
            ll qm = M / l;
            ll rn = N / qn + 1;
            ll rm = M / qm + 1;
            r = (rn < rm ? rn : rm);
            if (r > lim + 1) r = lim + 1;
            f(qn, qm, l, r);
        }
    }
}