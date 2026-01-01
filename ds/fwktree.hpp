#pragma once
#include "../head.hpp"

namespace fw_default {
    inline ll op_add(ll a, ll b) { return a + b; }
    inline ll e_zero() { return 0; }
    inline ll inv_add(ll a, ll b) { return a - b; } // 逆运算
}

// 树状数组(fenwick tree)
template <
    class S = ll, 
    S (*op)(S, S) = fw_default::op_add, 
    S (*e)() = fw_default::e_zero
>
struct FwkTree {
    int n;
    vector<S> d;

    inline int _lowbit(int x) const { return x & -x; }
    
    FwkTree(int _n) : n(_n), d(_n + 1, e()) { assert(n > 0); }

    // 建树, O(n)
    FwkTree(const vector<S>& arr) : n(arr.size()), d(arr.size() + 1, e()) {
        for (int i = 1; i <= n; i++) d[i] = arr[i - 1];
        for (int i = 1; i <= n; i++) {
            int pa = i + _lowbit(i);
            if (pa <= n) d[pa] = op(d[pa], d[i]);
        }
    }

    // 单点更新
    void add(int p, S x) {
        assert(0 <= p && p < n);
        for (p++; p <= n; p += _lowbit(p)) {
            d[p] = op(d[p], x);
        }
    }

    // 查前缀和, O(log n)
    S sum(int p) const {
        assert(-1 <= p && p < n);
        S res = e();
        for (p++; p > 0; p -= _lowbit(p)) {
            res = op(res, d[p]);
        }
        return res;
    }

    // 区间查询, 需使用逆运算 O(log n), 左闭右开
    template <S (*inv)(S, S) = fw_default::inv_add>
    S sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return inv(sum(r - 1), sum(l - 1));
    }

    // 仅在权值树状数组上有意义. 利用倍增查权值树状数组上第k小元素, 若不足k个则返回n. O(log n)
    int kth(S k) const {
        // 增加 n<=0 的特判
        if (n <= 0 || k <= e()) return -1;
        int pos = 0;
        int max_pow = 1 << (31 - __builtin_clz(n));
        
        for (int i = max_pow; i > 0; i >>= 1) {
            if (pos + i <= n && d[pos + i] < k) {
                k -= d[pos + i]; // 先减值
                pos += i;        // 后移动
            }
        }
        return pos;
    }

    // 查前缀和满足check的最大下标, 若不存在返回-1
    template <typename F>
    int search(F&& check) const {
        if (n <= 0) return -1;
        int pos = 0;
        int max_pow = 1 << (31 - __builtin_clz(n));
        S cur = e();
        if (!check(cur)) return -1;
        for (int i = max_pow; i > 0; i >>= 1) {
            if (pos + i <= n) {
                S next_val = op(cur, d[pos + i]);
                if (check(next_val)) {
                    pos += i;
                    cur = next_val;
                }
            }
        }
        return pos - 1;
    }
};