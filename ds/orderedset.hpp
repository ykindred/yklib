#pragma once
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using __gnu_pbds::tree;
using __gnu_pbds::null_type;
using __gnu_pbds::rb_tree_tag;
using __gnu_pbds::tree_order_statistics_node_update;

template<class T>
struct OrderedSet {
    using Tree = tree<T, null_type, std::less<T>, rb_tree_tag, tree_order_statistics_node_update>;
    Tree t;

    // 基础操作
    void insert(T x) { t.insert(x); }
    void erase(T x) { t.erase(x); }
    int size() const { return t.size(); }
    bool empty() const { return t.empty(); }
    
    // 排名查询
    // 查询 x 的排名 (有多少个元素严格小于 x), 最小元素的排名是 0
    int rank(T x) const { return t.order_of_key(x); }

    // 第k小. 0-based, k=0返回最小元素
    T kth(int k) const {
        // assert(k >= 0 && k < size());
        return *t.find_by_order(k);
    }

    // 前驱, 严格小于x的最大元素, 不存在返回x
    T prev(T x) const {
        int rk = rank(x);
        if (rk == 0) return x;
        return kth(rk - 1);
    }

    // 后继, 严格大于x的最小元素, 不存在返回x
    T next(T x) const {
        int rk = rank(x + 1);
        auto it = t.upper_bound(x);
        if (it == t.end()) return x;
        return *it;
    }
};

template<class T>
struct OrderedMultiset {
    using P = std::pair<T, int>;
    using Tree = tree<P, null_type, std::less<P>, rb_tree_tag, tree_order_statistics_node_update>;
    Tree t;
    int timer = 0;

    void insert(T x) {
        t.insert({x, ++timer});
    }

    // 删除一个x(如果存在)
    void erase(T x) {
        auto it = t.lower_bound({x, -1});
        if (it != t.end() && it->first == x) {
            t.erase(it);
        }
    }
    
    // 删除所有x
    void erase_all(T x) {
        while (true) {
            auto it = t.lower_bound({x, -1});
            if (it == t.end() || it->first != x) break;
            t.erase(it);
        }
    }

    int size() const { return t.size(); }
    bool empty() const { return t.empty(); }

    // 第k小: 返回值
    T kth(int k) const {
        return t.find_by_order(k)->first;
    }

    // 严格小于 x 的元素个数
    int rank(T x) const {
        return t.order_of_key({x, -1});
    }

    // x 出现的次数
    int count(T x) const {
        // 严格小于 (x+1) 的个数 - 严格小于 x 的个数
        return t.order_of_key({x, 2147483647}) - t.order_of_key({x, -1});
    }

    // 严格小于 x 的最大元素
    // 如果不存在，返回 x
    T prev(T x) const {
        int rk = rank(x);
        if (rk == 0) return x; 
        return kth(rk - 1);
    }

    // 严格大于 x 的最小元素
    // 如果不存在，返回 x
    T next(T x) const {
        int rk = t.order_of_key({x, 2147483647});
        if (rk == size()) return x;
        return kth(rk);
    }
    
    // 第一个 >= x 的元素值
    T lower(T x) const {
        auto it = t.lower_bound({x, -1});
        if (it == t.end()) return x;
        return it->first;
    }
};