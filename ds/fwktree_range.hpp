#include "fwktree.hpp"

/*-----fwktree_range.hpp-----*/
template <class S = ll>
struct FwkTree_range {
    using BIT = FwkTree<S>;
    int n;
    BIT bit0; // 维护 D[i]
    BIT bit1; // 维护 D[i] * i

    FwkTree_range() : n(0) {}
    // O(n) 建树
    FwkTree_range(int _n) : n(_n), bit0(_n), bit1(_n) {}
    FwkTree_range(const vector<S>& arr) : n(arr.size()), bit0(n), bit1(n) {
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

    // 区间修改[l, r), 即A[l, r) <- A[l, r) + val
    // [l, r) 包含于 [0, n), O(log n)
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

    // 前缀和S[idx], 即A[0, idx]
    // idx 属于 [0, n), O(log n)
    S sum(int idx) const {
        assert(idx < n); 
        if (idx < 0) return 0;
        return bit0.sum(idx) * S(idx + 1) - bit1.sum(idx);
    }

    // 区间查询 [l, r), 即A[l, r)
    // [l, r) 包含于 [0, n), O(log n)
    S sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return 0;
        return sum(r - 1) - sum(l - 1);
    }
};
/*---------------------------*/