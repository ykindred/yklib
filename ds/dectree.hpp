#pragma once
#include "../head.hpp"

// 笛卡尔树(cartesian tree), 为了方便拼读, 写作DecTree(基于笛卡尔原名Descartes)
// 行为与 priority_queue 一致
// Compare = less<T> (默认) -> 大根堆 (Max-Heap)
template <typename T, typename Compare = less<T>>
struct DecTree {
    int n;
    vector<int> ltc, rtc; // 左右子节点
    vector<int> pa;       // 父节点
    int root;             // 根节点

    vector<int> _range_l, _range_r; 

    DecTree(const vector<T>& a, Compare cmp = Compare()) : n(a.size()) {
        ltc.assign(n, -1);
        rtc.assign(n, -1);
        pa.assign(n, -1);
        vector<int> stk;
        
        for (int i = 0; i < n; ++i) {
            int last_popped = -1;
            while (!stk.empty() && cmp(a[stk.back()], a[i])) {
                last_popped = stk.back();
                stk.pop_back();
            }
            if (last_popped != -1) {
                ltc[i] = last_popped;
                pa[last_popped] = i;
            }
            if (!stk.empty()) {
                rtc[stk.back()] = i;
                pa[i] = stk.back();
            }
            stk.push_back(i);
        }
        root = stk.empty() ? -1 : stk[0];
    }

    // 构建区间范围 O(N)
    void _build_ranges() {
        _range_l.resize(n);
        _range_r.resize(n);
        
        if (root == -1) return;

        vector<int> q;
        q.reserve(n);
        q.push_back(root);
        
        int head = 0;
        while(head < (int)q.size()){
            int u = q[head++];
            if (ltc[u] != -1) q.push_back(ltc[u]);
            if (rtc[u] != -1) q.push_back(rtc[u]);
        }

        for (int i = n - 1; i >= 0; --i) {
            int u = q[i];
            // 默认区间只包含自己
            int l_limit = u;
            int r_limit = u;

            // 左边界继承左子树的左边界
            if (ltc[u] != -1) {
                l_limit = _range_l[ltc[u]];
            }
            // 右边界继承右子树的右边界
            if (rtc[u] != -1) {
                r_limit = _range_r[rtc[u]];
            }

            _range_l[u] = l_limit;
            _range_r[u] = r_limit;
        }
    }
    
    // 返回 idx 位置的管辖区间 [L, R), O(n) 处理后 O(1)
    pair<int, int> range(int idx) {
        assert(0 <= idx && idx < n);
        if (_range_l.empty()) {
            _build_ranges();
        }
        return {_range_l[idx], _range_r[idx] + 1};
    }

    int get_siz(int idx) {
        assert(0 <= idx && idx < n);
        if (_range_l.empty()) {
            _build_ranges();
        }
        return _range_r[idx] + 1 - _range_l[idx];
    }

    // 导出邻接表, 方便跑LCA或树形dp. O(n)
    vector<vector<int>> to_adj() const {
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; ++i) {
            if (ltc[i] != -1) {
                adj[i].push_back(ltc[i]);
                adj[ltc[i]].push_back(i);
            }
            if (rtc[i] != -1) {
                adj[i].push_back(rtc[i]);
                adj[rtc[i]].push_back(i);
            }
        }
        return adj;
    }
};