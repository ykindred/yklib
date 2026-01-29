#include "../head.hpp"
/*---------trie.hpp----------*/
// 字典树(Trie), sigma为字符集大小, off为偏移量
template <int sigma = 26, int off = 'a'>
struct Trie {
    struct S {
        array<int, sigma> next = {};
        int cnt = 0;    // 以该节点结尾的串数量
        int size = 0;   // 经过该节点的串数量
    };

    vector<S> d;
    int new_node() {
        d.emplace_back();
        return d.size() - 1;
    }
    void build() {
        d.clear();
        new_node(); // root
    }

    Trie(int size_res = 2e5) { // 节点数量
        d.reserve(size_res);
        build();
    }

    template <typename STRING>
    void insert(const STRING& s) {
        int p = 0;
        d[p].size++;
        for (auto c : s) {
            c -= off;
            if (d[p].next[c] == 0) {
                d[p].next[c] = new_node();
            }
            p = d[p].next[c];
            d[p].size++;
        }
        d[p].cnt++;
    }

    struct _RET {
        int cnt, prfx;
    };
    template <typename STRING>
    _RET query(const STRING& s) {
        int p = 0;
        for (auto c : s) {
            c -= off;
            if (d[p].next[c] == 0) {
                return { 0, 0 };
            }
            p = d[p].next[c];
        }
        return { d[p].cnt, d[p].size };
    }
};
/*---------------------------*/