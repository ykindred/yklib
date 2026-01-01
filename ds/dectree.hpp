#pragma once
#include "../head.hpp"
/*--------dectree.hpp--------*/
// 笛卡尔树 (Cartesian Tree), 可以完全代替单调栈
// 默认 Compare = less<T> -> 大根堆 (Max-Tree) -> 维护区间最大值
template <typename T, typename Compare = std::less<T>>
struct DecTree {
    int n;
    int root;
    vector<int> ltc, rtc; // 左右孩子, 分别代表管辖区间内左右的次大(小)值.
    vector<int> L, R;     // 管辖区间 [L, R] (闭区间)

    DecTree(const vector<T>& a, Compare cmp = Compare()) : n(a.size()) {
        ltc.assign(n, -1);
        rtc.assign(n, -1);
        L.resize(n);
        R.resize(n);
        
        vector<int> stk;
        for (int i = 0; i < n; ++i) {
            L[i] = i; 
            R[i] = i; 
            int last_popped = -1;
            while (!stk.empty() && cmp(a[stk.back()], a[i])) {
                last_popped = stk.back();
                stk.pop_back();
            }
            if (last_popped != -1) {
                ltc[i] = last_popped;
            }
            if (!stk.empty()) {
                rtc[stk.back()] = i;
            }
            stk.push_back(i);
        }
        root = stk.empty() ? -1 : stk[0];
        if (root != -1) init_range(root);   // 与建树复杂度一致
    }

    // dfs预处理区间, O(n).
    void init_range(int u) {
        if (ltc[u] != -1) {
            init_range(ltc[u]);
            L[u] = L[ltc[u]];
        }
        if (rtc[u] != -1) {
            init_range(rtc[u]);
            R[u] = R[rtc[u]];
        }
    }

    // 返回 [l, r) 左闭右开区间 (0-based), 总贡献为((i + 1) - l)(r - i)
    // 即 [l, i + 1) 和 [i, r) 区间. O(1)
    pair<int, int> range(int i) const {
        return {L[i], R[i] + 1};
    }
};
template<typename T, class Compare = std::less<T>>
using CartesianTree = DecTree<T, Compare>;
template<typename T, class Compare = std::less<T>>
using CtTree = DecTree<T, Compare>;
/*---------------------------*/