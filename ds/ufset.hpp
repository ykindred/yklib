#include "../head.hpp"

// 并查集(Union-find Set)
struct UfSet {
    int n;
    // 用一个数组同时存 pa 和 siz
    // 如果 pa_siz < 0，则 i 是根，且 -pa_siz[i] 是该集合的大小
    // 如果 pa_siz >= 0，则 pa_siz[i] 是 i 的父节点
    vector<int> pa_siz;
    int _count; // 连通块数量
    explicit UfSet(int _n) : n(_n), pa_siz(_n, -1), _count(_n) {}

    // 查找根节点, 可以认为是 O(1)
    int find(int i) {
        assert(0 <= i && i < n);
        if (pa_siz[i] < 0) return i;
        return pa_siz[i] = find(pa_siz[i]);
    }

    // 合并两个集合, 成功合并返回 true, 否则 false O(1)
    bool merge(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        int x = find(a), y = find(b);
        if (x == y) return false;
        
        if (-pa_siz[x] < -pa_siz[y]) swap(x, y);
        
        pa_siz[x] += pa_siz[y]; 
        pa_siz[y] = x;
        _count--;
        return true;
    }

    // 判断是否在同一个集合 O(1)
    bool same(int a, int b) {
        assert(0 <= a && a < n);
        assert(0 <= b && b < n);
        return find(a) == find(b);
    }

    // 获取所在的连通块大小 O(1)
    int size(int a) {
        assert(0 <= a && a < n);
        return -pa_siz[find(a)];
    }

    // 获取当前连通块的总数 O(1)
    int count() const {
        return _count;
    }

    // 获取所有连通块的分组列表, 调试用 O(N)
    vector<vector<int>> groups() {
        vector<int> leader_buf(n), group_size(n);
        for (int i = 0; i < n; i++) {
            leader_buf[i] = find(i);
            group_size[leader_buf[i]]++;
        }
        vector<vector<int>> result(n);
        for (int i = 0; i < n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        // 去除空集
        result.erase(
            remove_if(result.begin(), result.end(),
                           [&](const vector<int>& v) { return v.empty(); }),
            result.end());
        return result;
    }
};