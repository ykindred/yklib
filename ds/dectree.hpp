#pragma once
#include "../head.hpp"

// 笛卡尔树 (Cartesian Tree)
// 默认 Compare = less<T> -> 大根堆 (Max-Tree) -> 维护区间最大值
template <typename T, typename Compare = std::less<T>>
struct DecTree {
    int n;
    int root;
    vector<int> ltc, rtc; // 左右孩子
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
        if (root != -1) init_range(root);
    }

    // dfs预处理区间
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

    // 返回 [l, r] 闭区间 (0-based)
    pair<int, int> range(int i) const {
        return {L[i], R[i]};
    }
    
    // 计算贡献: (i - L + 1) * (R - i + 1))
    int count(int i) const {
        return (i - L[i] + 1) * (R[i] - i + 1);
    }
};