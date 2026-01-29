#include "../head.hpp"
/*--------ufset.hpp----------*/
// 并查集(Union-find Set)
struct UfSet {
    int n;
    vector<int> pa, siz;

    void init(int _n = 0) {
        n = _n;
        pa.assign(_n, 0);
        siz.assign(_n, 1);
        iota(pa.begin(), pa.end(), 0);
    }

    UfSet(int _n = 0) { 
        init(_n); 
    }

    int find(int x) {
        while (x != pa[x]) {
            x = pa[x] = pa[pa[x]];
        }
        return x;
    }

    bool uni(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) {
            return false;
        }
        if (siz[x] < siz[y]) {
            swap(x, y);
        }
        pa[y] = x;
        siz[x] += siz[y];
        return true;
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

using DSU = UfSet;
/*---------------------------*/