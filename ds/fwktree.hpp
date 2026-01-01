#pragma once
#include <bits/stdc++.h>
using ll = long long;
using namespace std;
/*--------fwktree.hpp--------*/
// 默认为ll类型, 加法, 0, 减法
namespace fw_default {
    template<typename T> inline T op_add(T a, T b) { return a + b; }
    template<typename T> inline T e_zero() { return T(0); }
    template<typename T> inline T inv_add(T a, T b) { return a - b; }
}

// 树状数组(fenwick tree), 行为逻辑与数组类似, FwkTree(n)构造的数组允许访问[0, n - 1]
// 类型S, 合并函数op(a, b), 零元函数e(), 逆运算函数inv(a, b)
template <
    class S = ll,
    S (*op)(S, S) = fw_default::op_add<S>, 
    S (*e)() = fw_default::e_zero<S>,
    S (*inv)(S, S) = fw_default::inv_add<S>
>
struct FwkTree {
    int n;
    vector<S> d;

    static int _lowbit(int x) { return x & -x; }
    
    FwkTree() : n(0) {}
    FwkTree(int _n) : n(_n), d(_n + 1, e()) {}

    // 建树, O(n)
    FwkTree(const vector<S>& arr) : n(arr.size()), d(arr.size() + 1, e()) {
        for (int i = 1; i <= n; i++) d[i] = arr[i - 1];
        for (int i = 1; i <= n; i++) {
            int pa = i + _lowbit(i);
            if (pa <= n) d[pa] = op(d[pa], d[i]);
        }
    }

    // 单点更新, O(log n)
    void add(int p, S x) {
        assert(0 <= p && p < n);
        for (p++; p <= n; p += _lowbit(p)) {
            d[p] = op(d[p], x);
        }
    }

    // 查前缀和, O(log n)
    S sum(int p) const {
        assert(p < n);
        S res = e();
        for (p++; p > 0; p -= _lowbit(p)) {
            res = op(res, d[p]);
        }
        return res;
    }

    // 区间查询, 需使用逆运算, 左闭右开[l, r), O(log n)
    S sum(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return inv(sum(r - 1), sum(l - 1));
    }
};
template <class S = ll, S (*op)(S, S) = fw_default::op_add<S>, S (*e)() = fw_default::e_zero<S>, S (*inv)(S, S) = fw_default::inv_add<S>>
using BIT = FwkTree<S, op, e, inv>;
/*---------------------------*/