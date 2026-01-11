#pragma once
#include "../head.hpp"
#include "../alg/monoid/add.hpp"
/*--------fwktree.hpp--------*/
// 树状数组(fenwick tree), 行为逻辑与数组类似, FwkTree(n)构造的数组允许访问[0, n - 1]
template <class S>
struct FwkTree {
    int n;
    vector<S> d;

    void build(const vector<S>& arr) {
        n = arr.size();
        d.assign(arr.size() + 1, 0);
        for (int i = 1; i < n + 1; i++) {
            d[i] = arr[i - 1];
        }
        for (int i = 1; i < n + 1; i++) {
            int pa = i + lowbit(i);
            if (pa < n) {
                d[pa] = d[pa] + d[i];
            }
        }
    }
    
    FwkTree() : n(0) {}
    FwkTree(int _n) : n(_n), d(_n + 1, 0) {}
    FwkTree(const vector<S>& arr) {
        build(arr);
    }

    // 单点更新, O(log n)
    void add(int p, S x) {
        assert(0 <= p && p < n);
        for (p++; p <= n; p += lowbit(p)) {
            d[p] = d[p] + x;
        }
    }

    // 查前缀和, O(log n)
    S sum(int p) const {
        assert(p < n);
        S res = 0;
        for (p++; p > 0; p -= lowbit(p)) {
            res = res + d[p];
        }
        return res;
    }

    // 区间查询, 需使用逆运算, 左闭右开[l, r), O(log n)
    S query(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return sum(r - 1) - sum(l - 1);
    }
};