#pragma once
#include "fwktree.hpp"
/*-----fwktree_range.hpp-----*/
// 树状数组(区间加, 区间和). Monoid要求包含:
// 类型value_type, 合并运算op(S, S), 零元e(), 逆运算inv(S), 数乘mul(S, int)
template <class S>
struct FwkTree_range {
    int n;
    FwkTree<S> bit0;
    FwkTree<S> bit1;
    void build(const vector<S>& arr) {
        n = arr.size();
        vector<S> d0(n), d1(n);
        S prev = 0;
        for (int i = 0; i < n; i++) {
            S diff = arr[i] - prev;
            d0[i] = diff;
            d1[i] = diff * i;
            prev = arr[i];
        }
        bit0 = fwr(d0);
        bit1 = fwr(d1);
    }

    FwkTree_range() : n(0) {}
    FwkTree_range(int _n) : n(_n), bit0(_n), bit1(_n) {}
    FwkTree_range(const vector<S>& arr) : n(arr.size()), bit0(n), bit1(n) {
        build(arr);
    }

    // 区间修改 [l, r) <- + val, O(log n)
    void range_add(int l, int r, S val) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        
        bit0.add(l, val);
        bit1.add(l, val * l);
        if (r < n) {
            bit0.add(r, -val);
            bit1.add(r, -val * r);
        }
    }

    // 前缀和 S[idx] = A[0] + ... + A[idx], idx in [0, n - 1]
    // (idx + 1) * sum(D) - sum(D * i), O(log n)
    S sum(int idx) const {
        assert(idx < n); 
        if (idx < 0) return 0;
        S term1 = bit0.sum(idx) * (idx + 1);
        S term2 = bit1.sum(idx);
        return term1 - term2;
    }

    // 区间查询 [l, r) in [0, n), O(log n)
    S sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return 0;
        return sum(r - 1) - sum(l - 1);
    }
};
/*---------------------------*/