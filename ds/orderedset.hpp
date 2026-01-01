#pragma once
#include "../head.hpp"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

template <typename T, typename Compare = less<T>>
using pb_tree = __gnu_pbds::tree<T, __gnu_pbds::null_type, Compare, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update>;

// 有序集
template <typename T>
struct ordered_set : public pb_tree<T> {
    // 查询第k小元素, 返回值. 最小的元素是第0小
    T kth(int k) {
        assert(k >= 0 && k < (int)this->size());
        return *this->find_by_order(k);
    }
    
    // 查x排名, 即严格小于x的元素的数量.
    int rank(T x) {
        return this->order_of_key(x);
    }

    // 其他用法类似std::set
};

// 多重集
template <typename T>
struct ordered_multiset {
    pb_tree<pair<T, int>> t;
    int timer = 0;

    void insert(T x) {
        t.insert({x, ++timer});
    }

    // 删除一个值为 x 的元素
    void erase(T x) {
        auto it = t.lower_bound({x, 0});
        if (it != t.end() && it->first == x) {
            t.erase(it);
        }
    }

    // 删除所有值为 x 的元素
    void erase_all(T x) {
        while (true) {
            auto it = t.lower_bound({x, 0});
            if (it == t.end() || it->first != x) break;
            t.erase(it);
        }
    }

    int size() const { return t.size(); }
    bool empty() const { return t.empty(); }

    // 查第k小元素, 0based
    T kth(int k) {
        assert(k >= 0 && k < (int)t.size());
        return t.find_by_order(k)->first;
    }

    // 查x排名
    int rank(T x) {
        return t.order_of_key({x, 0});
    }

    // 查x的出现次数.
    int count(T x) {
        return t.order_of_key({x, (int)2e9}) - t.order_of_key({x, 0});
    }
};