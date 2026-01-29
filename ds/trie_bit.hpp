#include "../head.hpp"
/*-------trie_bit.hpp--------*/
template <int LOG = 30, typename INT = int>
struct Trie_bit {   
    struct S {
        array<int, 2> next = {};
        int cnt = 0;
    };
    vector<S> d;

    void build() {
        d.clear();
        d.emplace_back();
    }

    Trie_bit(int size_res = 2e6) {
        d.reserve(size_res);
        build();
    }
    
    int new_node() {
        d.emplace_back();
        return d.size() - 1;
    }

    void add(INT x, int v = 1) { // insert or delete
        int p = 0;
        d[p].cnt += v;
        for (int i = LOG; i >= 0; i--) {
            int u = (x >> i) & 1;
            if (d[p].next[u] == 0) {
                d[p].next[u] = new_node();
            }
            p = d[p].next[u];
            d[p].cnt += v;
        }
    }
    
    // 第k小. 最小是第0小[0, d[0].cnt)
    INT kth_xor(int k, INT x) {
        if (k >= d[0].cnt) {
            return -1;
        }

        int p = 0;
        INT res = 0;

        for (int i = LOG; i >= 0; i--) {
            int u = (x >> i) & 1;

            int np = d[p].next[u]; // 希望走uh
            int ncnt = (np == 0) ? 0 : d[np].cnt;
            if (ncnt > k) {
                // 走uh
                p = np;
            } else {
                // 走u
                k -= ncnt;
                p = d[p].next[u ^ 1];
                res |= ((INT)1 << i);
            }
        }
        return res;
    }

    INT max_xor(INT x) {
        return kth_xor(d[0].cnt - 1, x);
    }

    INT min_xor(INT x) {
        assert(d[0].cnt >= 1);
        return kth_xor(0, x);
    }
};
/*---------------------------*/