#include "grid.hpp"

// sum and diff
template<class T>
grid<T> partial_sum(grid<T> ret) {
    for (int i = 0; i <= ret.n; i++) {
        for (int j = 0; j <= ret.m; j++) {
            if (i >= 1) ret[i][j] += ret[i - 1][j];
            if (j >= 1) ret[i][j] += ret[i][j - 1];
            if (i >= 1 && j >= 1) ret[i][j] -= ret[i - 1][j - 1];
        }
    }
    return ret;
}

template<class T>
grid<T> partial_diff(grid<T> ret) {
    for (int i = ret.n; i >= 0; i--) {
        for (int j = ret.m; j >= 0; j--) {
            if (i >= 1) ret[i][j] -= ret[i - 1][j];
            if (j >= 1) ret[i][j] -= ret[i][j - 1];
            if (i >= 1 && j >= 1) ret[i][j] += ret[i - 1][j - 1];
        }
    }
    return ret;
}

template<typename T>
T ask_sum(const grid<T>& gr, int r1, int c1, int r2, int c2) {
    T ret = gr[r2][c2];
    if (r1 >= 1 && c1 >= 1) ret += gr[r1 - 1][c1 - 1];
    if (r1 >= 1) ret -= gr[r1 - 1][c2];
    if (c1 >= 1) ret -= gr[r2][c1 - 1];
    return ret;
}

template<typename T>
T ask_sum(const grid<T>& gr, pair<int, int> minp, pair<int, int> maxp) {
    return ask_sum(gr, minp.first, minp.second, maxp.first, maxp.second);
}

template<typename T>
void add_diff(grid<T>& gr, int r1, int c1, int r2, int c2, T val) {
    gr[r1][c1] += val;
    if (r2 < gr.n && c2 < gr.m) gr[r2 + 1][c2 + 1] += val;
    if (r2 < gr.n) gr[r2 + 1][c1] -= val;
    if (c2 < gr.m) gr[r1][c2 + 1] -= val;
}

template<typename T>
void add_diff(grid<T>& gr, pair<int, int> p1, pair<int, int> p2, T val) {
    add_diff(gr, p1.first, p1.second, p2.first, p2.second, val);
}