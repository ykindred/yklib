#pragma once
#include "../head.hpp"
/*----------grid.hpp---------*/
// grid
struct pos_grid {
    int r;
    int c;
    constexpr pos_grid(int x, int y) : r(x), c(y) {}
    constexpr pos_grid operator+(pos_grid b) const { return { r + b.r, c + b.c }; }
    constexpr pos_grid operator*(int b) const { return { r * b, c * b }; }
    constexpr pos_grid operator-() const { return { -r, -c }; }
    constexpr bool operator==(const pos_grid& b) const { return r == b.r && c == b.c; }
    constexpr bool operator!=(const pos_grid& b) const { return !(*this == b); }
};

enum { UP, DN, LT, RT, UPLT, UPRT, DNLT, DNRT };
inline static constexpr pos_grid direction[8] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};

template <class T>
struct grid {
    int n, m;
    std::vector<T> value;

    grid() : n(0), m(0) {}
    grid(int _n, int _m, T _val = T()) 
        : n(_n), m(_m), value(_n * _m, _val) {}
    void assign(int _n, int _m, T _val = T()) {
        n = _n; m = _m;
        value.assign(n * m, _val);
    }

    // get element
    T* operator[](int r) { return value.data() + r * m; }
    const T* operator[](int r) const { return value.data() + r * m; }
    T& operator[](pos_grid p) { return (*this)[p.r][p.c]; }
    const T& operator[](pos_grid p) const { return (*this)[p.r][p.c]; }

    // inside
    bool inside(pos_grid p, pos_grid minp, pos_grid maxp) const {
        auto [r, c] = p;
        auto [minr, minc] = minp;
        auto [maxr, maxc] = maxp;
        assert(0 <= minr && 0 <= minc);
        assert(maxr <= n && maxc <= m);
        return (minr <= r && r < maxr) && (minc <= c && c < maxc);
    }
    bool inside(pos_grid p) const {
        return inside(p, {0, 0}, {n, m});
    }

    // iterator
    auto begin() { return value.begin(); }   // *g.begin() == g[0][0]
    auto end() { return value.end(); }       // *(g.end() - 1) == g[n][m]
    // sort(g[2] + 1, g[3]);
    // max_element(g.begin(), g.end());

    pos_grid mov(pos_grid p, int d, int step = 1) const {
        return p + (direction[d] * step);
    }
};
/*---------------------------*/