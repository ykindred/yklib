#pragma once
#include "fwktree.hpp"
/*-----fwktree_range.hpp-----*/
namespace fw_default {
    // 默认数乘a * b
    template<typename T> inline T op_mul(T a, int b) { return a * b; }
}

// 树状数组(区间加, 区间和). 模板参数为:
// 类型S, 合并运算op(S, S), 零元e(), 逆运算inv(S, S), 数乘mul(S, int)
template <
    class S = ll,
    S (*op)(S, S) = fw_default::op_add<S>, 
    S (*e)() = fw_default::e_zero<S>,
    S (*inv)(S, S) = fw_default::inv_add<S>,
    S (*mul)(S, int) = fw_default::op_mul<S>
>
struct FwkTree_range {
    using BIT = FwkTree<S, op, e, inv>;
    int n;
    BIT bit0;
    BIT bit1;

    FwkTree_range() : n(0) {}
    FwkTree_range(int _n) : n(_n), bit0(_n), bit1(_n) {}
    FwkTree_range(const vector<S>& arr) : n(arr.size()), bit0(n), bit1(n) {
        vector<S> d0(n), d1(n);
        S prev = e(); 
        for (int i = 0; i < n; i++) {
            S diff = inv(arr[i], prev);
            
            d0[i] = diff;
            d1[i] = mul(diff, i);
            prev = arr[i];
        }
        bit0 = BIT(d0);
        bit1 = BIT(d1);
    }

    // 区间修改 [l, r) <- + val, O(log n)
    void range_add(int l, int r, S val) {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return;
        
        S neg_val = inv(e(), val);
        bit0.add(l, val);
        bit1.add(l, mul(val, l));
        if (r < n) {
            bit0.add(r, neg_val);
            bit1.add(r, mul(neg_val, r));
        }
    }

    // 前缀和 S[idx] = A[0] + ... + A[idx], idx in [0, n - 1]
    // (idx + 1) * sum(D) - sum(D * i), O(log n)
    S sum(int idx) const {
        assert(idx < n); 
        if (idx < 0) return e();
        S term1 = mul(bit0.sum(idx), idx + 1);
        S term2 = bit1.sum(idx);
        return inv(term1, term2);
    }

    // 区间查询 [l, r) in [0, n), O(log n)
    S sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        if (l == r) return e();
        return inv(sum(r - 1), sum(l - 1));
    }
};
/*---------------------------*/