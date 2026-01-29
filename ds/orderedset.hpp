#pragma once
#include "../head.hpp"
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using __gnu_pbds::tree;
using __gnu_pbds::null_type;
using __gnu_pbds::rb_tree_tag;
using __gnu_pbds::tree_order_statistics_node_update;
/*------orderedset.hpp-------*/
template <class K, class V, class Comp = std::less<K>>
using OrderedMap = tree<K, V, Comp, rb_tree_tag, tree_order_statistics_node_update>;
template <class K, class Comp = std::less<K>>
using OrderedSet = OrderedMap<K, null_type, Comp>;
// void insert(T x)
// void erase(T x)
// int size()
// bool empty()
// int order_of_key(T x) : 查排名(严格小于x的元素个数), 最小为0
// auto find_by_order(int k) : 查排名为k的元素迭代器, 需要解引用, 最小元素排名为0

template <class K, class V, class Comp>
auto prev_key(const OrderedMap<K, V, Comp>& st, K x) {
    // 查前驱, 严格小于x的最大元素值, 不存在则返回st.end()
    int rk = st.order_of_key(x);
    if (rk == 0) {
        return st.end();
    }
    return st.find_by_order(rk - 1);
}

template <class K, class V, class Comp>
auto next_key(const OrderedMap<K, V, Comp>& st, K x) {
    // 查后继, 即严格大于x的最小元素值, 不存在返回st.end()
    auto it = st.upper_bound(x);
    return it;
}
/*---------------------------*/