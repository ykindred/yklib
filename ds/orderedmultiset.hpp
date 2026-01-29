#pragma once
#include "orderedset.hpp"

/*----orderedmultiset.hpp----*/
template <typename T, typename Comp = std::less<T>>
struct OrderedMultiSet {
    // 内部使用 pair<T, int> 来区分相同元素，int 为时间戳
    using P = std::pair<T, int>;
    
    struct PComp {
        Comp c;
        bool operator()(const P& a, const P& b) const {
            if (c(a.first, b.first)) return true;
            if (c(b.first, a.first)) return false;
            return a.second < b.second;
        }
    };

    OrderedMap<P, null_type, PComp> t;
    int _timer = 0;

    int size() const { 
        return t.size(); 
    }
    bool empty() const {
        return t.empty(); 
    }
    void clear() { 
        t.clear(); 
        _timer = 0; 
    }

    void insert(T x) {
        t.insert({ x, _timer });
        _timer++;
    }

    // 删除一个 x (如果存在多个，删除最早插入的那一个)
    // 返回是否删除成功
    bool erase_one(T x) {
        auto it = t.lower_bound({ x, -1 });
        if (it != t.end() && !Comp()(x, it->first) && !Comp()(it->first, x)) {
            t.erase(it);
            return true;
        }
        return false;
    }

    // 删除所有等于 x 的元素
    void erase_all(T x) {
        while (erase_one(x));
    }

    // 统计 x 的个数
    int count(T x) const {
        // (严格 > x 的排名) - (严格 < x 的排名)
        return t.order_of_key({ x, 2147483647 }) - t.order_of_key({ x, -1 });
    }

    // 查排名, 严格小于x的元素个数
    int order_of_key(T x) const {
        return t.order_of_key({ x, -1 });
    }

    // 查第k小, 返回第k小的值, 要求k不越界, 最小为第0小
    T find_by_order(int k) const {
        return t.find_by_order(k)->first;
    }

    // 如果存在, 返回 true 并将结果写入 res, 如果不存在, 返回 false
    // 前驱：严格小于 x 的最大值
    bool prev(T x, T& res) const {
        auto it = t.lower_bound({ x, -1 });
        if (it == t.begin()) {
            return false;
        }
        --it;
        res = it->first;
        return true;
    }

    // 后继：严格大于 x 的最小值
    bool next(T x, T& res) const {
        auto it = t.upper_bound({ x, 2147483647 });
        if (it == t.end()) return false;
        res = it->first;
        return true;
    }
};

template <typename K, typename V, typename Comp = std::less<K>>
struct OrderedMultiMap {
    using P = std::pair<K, int>;
    
    struct PComp {
        Comp c;
        bool operator()(const P& a, const P& b) const {
            if (c(a.first, b.first)) return true;
            if (c(b.first, a.first)) return false;
            return a.second < b.second;
        }
    };

    OrderedMap<P, V, PComp> t;
    int _timer;

    OrderedMultiMap() : _timer(0) {}

    int size() const { 
        return t.size(); 
    }
    bool empty() const { 
        return t.empty(); 
    }
    void clear() { 
        t.clear(); _timer = 0; 
    }

    void insert(K key, V val) {
        t.insert({ { key, _timer }, val });
        _timer++;
    }

    bool erase_one(K key) {
        auto it = t.lower_bound({ key, -1 });
        if (it != t.end() && !Comp()(key, it->first.first) && !Comp()(it->first.first, key)) {
            t.erase(it);
            return true;
        }
        return false;
    }

    // 返回第k小的Key对应的k, v
    std::pair<K, V> find_by_order(int k) const {
        auto it = t.find_by_order(k);
        return { it->first.first, it->second };
    }
    
    // 查排名
    int order_of_key(K key) const {
        return t.order_of_key({ key, -1 });
    }
};
/*---------------------------*/