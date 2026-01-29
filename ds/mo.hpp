#pragma once
#include "../head.hpp"
/*----------mo.hpp-----------*/
struct Mo {
    // 存储左闭右开区间[L, R)
    vector<pair<int, int>> queries;

    // 增加一个左闭右开的查询
    void add_query(int lt, int rt) {
        queries.emplace_back(lt, rt);
    }

    // 计算最优执行顺序
    vector<int> get_mo_order() {
        int qsiz = queries.size();
        if (qsiz == 0) return {};

        int tmp = 0;
        for (auto&& [lt, rt] : queries) {
            if (lt > tmp) tmp = lt;
            if (rt > tmp) tmp = rt;
        }

        // 理论最优块大小为 sqrt(3) * N / sqrt(2 * Q)
        int blocksiz = max(1, (int)(1.732 * tmp / sqrt(max(1.0, 2.0 * qsiz))));
        
        vector<int> ret(qsiz);
        iota(ret.begin(), ret.end(), 0);
        
        sort(ret.begin(), ret.end(), [&](int a, int b) {
            int ab = queries[a].first / blocksiz, bb = queries[b].first / blocksiz;
            if (ab != bb) return ab < bb;
            return (ab & 1) ? (queries[a].second > queries[b].second) : (queries[a].second < queries[b].second);
        });
        // 如果卡常, 则启用下面这段注释

        // auto get_cost = [&](int a, int b) -> int {
        //     return abs(queries[ret[a]].first - queries[ret[b]].first) + abs(queries[ret[a]].second - queries[ret[b]].second);
        // };
        
        // for (int k = 0; k + 4 < qsiz; ++k) {
        //     if (get_cost(k, k + 2) + get_cost(k + 1, k + 3) < get_cost(k, k + 1) + get_cost(k + 2, k + 3)) {
        //         swap(ret[k + 1], ret[k + 2]);
        //     }
        //     if (get_cost(k, k + 3) + get_cost(k + 1, k + 4) < get_cost(k, k + 1) + get_cost(k + 3, k + 4)) {
        //         swap(ret[k + 1], ret[k + 3]);
        //     }
        // }
        return ret;
    }

    // 非对称增删
    template <class F1, class F2, class F3, class F4, class Q>
    void solve(F1 add_l, F2 add_r, F3 rm_l, F4 rm_r, Q query) {
        auto I = get_mo_order();
        int l = 0, r = 0;
        for (int idx : I) {
            while (l > queries[idx].first) add_l(--l);
            while (r < queries[idx].second) add_r(r++);
            while (l < queries[idx].first) rm_l(l++);
            while (r > queries[idx].second) rm_r(--r);
            query(idx);
        }
    }

    // 对称增删
    template <class F1, class F2, class Q>
    void solve(F1 add, F2 rm, Q query) {
        solve(add, add, rm, rm, query);
    }
};
/*---------------------------*/