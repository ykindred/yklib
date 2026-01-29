#pragma once
#include "../head.hpp"
/*--------fwktree.hpp--------*/
// 树状数组(fenwick tree), 行为逻辑与数组类似, FwkTree(n)构造的数组允许访问[0, n)
// 只用于数字类型的单点加, 区间查询, 需要更复杂的操作请使用线段树
template <class S>
struct FwkTree {
    int n;
    vector<S> d;

    void build(int _n) {
        n = _n;
        d.resize(n + 1);
    }
    void build(const vector<S>& arr) {
        build(arr.size());
        for (int i = 1; i <= n; i++) {
            d[i] = arr[i - 1];
        }
        for (int i = 1; i <= n; i++) {
            int pa = i + lowbit(i);
            if (pa <= n) {
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
    void add(int pos, S val) {
        assert(0 <= pos && pos < n);
        for (pos++; pos <= n; pos += lowbit(pos)) {
            d[pos] = d[pos] + val;
        }
    }

    // 查前缀和, O(log n)
    S sum(int pos) const {
        assert(-1 <= pos && pos < n);
        S res = 0;
        for (pos++; pos > 0; pos -= lowbit(pos)) {
            res = res + d[pos];
        }
        return res;
    }

    // 区间查询, 左闭右开[l, r), O(log n)
    S query(int l, int r) const {
        assert(0 <= l && l <= r && r <= n);
        return sum(r - 1) - sum(l - 1);
    }
    
    // 扩展: 权值树状数组查第k小
    int kth(S k) const {
        int idx = 0;
        for (int i = 1 << __lg(n); i > 0; i /= 2) {
            if (idx + i > n) {
                continue;
            }
            if (d[idx + i] < k) {
                idx += i;
                k -= d[idx];
            }
        }
        return idx;
    }
};
/*---------------------------*/