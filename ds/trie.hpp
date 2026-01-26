#include "../head.hpp"
/*---------trie.hpp----------*/
template <int sigma = 26, int off = 'a'>
struct Trie {
    struct S {
        array<int, sigma> next{};
        int cnt = 0;    // 以该节点结尾的串数量
        int siz = 0;    // 经过该节点的串数量
    };

    vector<S> d;
    void build() {
        d.clear();
        d.emplace_back(); // root
    }

    int new_node() {
        d.emplace_back();
        return d.size() - 1;
    }

    Trie(int size_res = 2e5) {
        d.reserve(size_res);
        build();
    }

    template <typename STRING>
    void insert(const STRING& s) {
        int p = 0;
        d[p].siz++;
        for (auto c : s) {
            c -= off;
            if (d[p].next[c] == 0) {
                d[p].next[c] = new_node();
            }
            p = d[p].next[c];
            d[p].siz++;
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
        return { d[p].cnt, d[p].siz };
    }
};
/*---------------------------*/