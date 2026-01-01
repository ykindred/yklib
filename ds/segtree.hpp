#pragma once
#include "../head.hpp"

namespace sg_default {
    inline ll op_sum(ll a, ll b) { return a + b; }
    inline ll e_zero() { return 0; }
}

// 线段树(Segment Tree)
// S  -> 数据类型, 默认为 ll
// op -> 合并操作运算, 默认为加法
// e  -> 零元, 默认为0
template <
    class S = ll, 
    S (*op)(S, S) = sg_default::op_sum, 
    S (*e)() = sg_default::e_zero
>
struct SegTree {
public:
    int n;
    int size;
    int log;
    vector<S> d;
    SegTree() : SegTree(0) {}
    explicit SegTree(int n) : SegTree(vector<S>(n, e())) {}
    explicit SegTree(const vector<S>& v) : n(int(v.size())) {
        log = 0;
        while ((1 << log) < n) log++;
        size = 1 << log;
        d = vector<S>(2 * size, e());
        
        for (int i = 0; i < n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) _update(i);
    }

    // 单点修改
    void set(int p, S x) {
        assert(0 <= p && p < n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) _update(p >> i);
    }


    // 单点查询
    S get(int p) const {
        assert(0 <= p && p < n);
        return d[p + size];
    }

    // 区间查询, 左闭右开
    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    // 全局查询
    S all_prod() const { return d[1]; }
    
    // 树上二分. 传入l, 找到最大的r使得[l, r)的区间和满足check.
    template <class F> int max_right(int l, F check) const {
        assert(0 <= l && l <= n);
        if (!check(e())) return l;
        if (l == n) return n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!check(op(sm, d[l]))) {
                while (l < size) {
                    l = 2 * l;
                    if (check(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return n;
    }

    // 树上二分, 传入r, 找到最小的l使得[l, r)的区间和满足check. O(log n)
    template <class F> int min_left(int r, F check) const {
        assert(0 <= r && r <= n);
        if (!check(e())) return r;
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!check(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (check(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }
private:
    void _update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};