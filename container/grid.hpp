#pragma once
#include "../head.hpp"
#include "../stl_ext.hpp"
/*----------grid.hpp---------*/
// grid
template <class T>
struct grid {
    int n, m;               // (n + 1) * (m + 1) grid
    std::vector<T> value;    // has (n + 1) * (m + 1) size

    // constructor
    grid() : n(0), m(0) {}
    grid(int _n, int _m, T _val = T()) 
        : n(_n), m(_m), value((_n + 1) * (_m + 1), _val) {}
    void assign(int _n, int _m, T _val = T()) {
        n = _n; m = _m;
        value.assign((n + 1) * (m + 1), _val);
    }

    // get element
    inline T* operator[](int r) { return value.data() + r * (m + 1); }
    inline const T* operator[](int r) const { return value.data() + r * (m + 1); }
    inline T& operator[](pair<int, int> p) { return value[p.first * (m + 1) + p.second]; }
    inline const T& operator[](pair<int, int> p) const { return value[p.first * (m + 1) + p.second]; }

    // inside
    inline bool inside(pair<int, int> p, pair<int, int> minp, pair<int, int> maxp) const {
        auto [r, c] = p;
        auto [minr, minc] = minp;
        auto [maxr, maxc] = maxp;
        return (minr <= r && r <= maxr) && (minc <= c && c <= maxc);
    }
    inline bool inside(pair<int, int> p) const {
        return inside(p, {1, 1}, {n, m});
    }

    // iterator
    auto begin() { return value.begin(); }   // *g.begin() == g[0][0]
    auto end() { return value.end(); }       // *(g.end() - 1) == g[n][m]
    // std::sort(g[2] + 1, g[3]);
    // std::max_element(g.begin(), g.end());

    // move
    enum { UP, DN, LT, RT, UPLT, UPRT, DNLT, DNRT };
    static constexpr pair<int, int> direction[8] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    pair<int, int> mov(pair<int, int> p, int d, int step = 1) const {
        return p + (direction[d] * step);
    }
    
    // stream, 1-based
    friend std::istream& operator>>(std::istream& is, grid& g) {
        for (int i = 1; i <= g.n; i++) {
            for (int j = 1; j <= g.m; j++) {
                is >> g[i][j];
            }
        }
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const grid& g) {
        for (int i = 1; i <= g.n; i++) {
            for (int j = 1; j <= g.m; j++) {
                os << g[i][j];
                if (j != g.m) os << ' ';
            }
            if (i != g.n) os << '\n';
        }
        return os;
    }
};
/*---------------------------*/