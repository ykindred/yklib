#include "fwktree.hpp"

template <class S = ll>
struct FwkTree_range {
    int n;
    FwkTree<S> bit0; // 维护 D[i]
    FwkTree<S> bit1; // 维护 D[i] * i

    FwkTree_range() : n(0) {}
    FwkTree_range(int _n) : n(_n), bit0(_n), bit1(_n) {}

    // 建树 O(n)
    FwkTree_range(const vector<S>& arr) : n(arr.size()), bit0(arr.size()), bit1(arr.size()) {
        vector<S> d0(n), d1(n);
        S prev = 0;
        for (int i = 0; i < n; i++) {
            S diff = arr[i] - prev;
            d0[i] = diff;
            d1[i] = diff * S(i);
            prev = arr[i];
        }
        bit0 = BIT(d0);
        bit1 = BIT(d1);
    }

    // 对开区间 [l, r) + val, O(log n)
    void range_add(int l, int r, S val) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        bit0.add(l, val);
        bit1.add(l, val * S(l));
        if (r < n) {
            bit0.add(r, -val);
            bit1.add(r, -val * S(r));
        }
    }

    // 求0到p的前缀和sum[0~p], O(log n)
    S range_sum(int p) const {
        assert(p < n);
        if (p < 0) return 0; 
        return bit0.sum(p) * S(p + 1) - bit1.sum(p);
    }

    // 区间查询 [l, r), O(log n)
    S range_sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return 0;
        return range_sum(r - 1) - range_sum(l - 1);
    }
};