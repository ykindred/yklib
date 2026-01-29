#include "../head.hpp"
namespace numth {
    // 一维数论分块, 调用f(q, l, r), 其中[l, r)为左闭右开区间.
    // O(sqrt(N))
    template <typename F>
    void block_floor(ll N, F f) {
        if (N <= 0) return;
        for (ll l = 1, r; l <= N; l = r) {
            ll q = N / l;
            r = N / q + 1;
            f(q, l, r);
        }
    }

    // 二维数论分块, 调用f(qn, qm, l, r), 其中[l, r)为左闭右开区间
    // O(sqrt(N) + sqrt(M))
    template <typename F>
    void block_2d(ll N, ll M, F f) {
        ll lim = min(N, M);
        if (lim <= 0) {
            return;
        }
        for (ll l = 1, r; l <= lim; l = r) {
            ll qn = N / l;
            ll qm = M / l;
            r = min({ N / qn, M / qm, lim }) + 1;
            f(qn, qm, l, r);
        }
    }
}