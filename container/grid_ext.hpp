#pragma once
#include "grid.hpp"
/*-------grid_ext.hpp--------*/
// sum and diff
template<class T>
grid<T> partial_sum(grid<T> ret) {
    for (int i = 0; i < ret.n; i++) {
        for (int j = 0; j < ret.m; j++) {
            if (i >= 1) ret[i][j] += ret[i - 1][j];
            if (j >= 1) ret[i][j] += ret[i][j - 1];
            if (i >= 1 && j >= 1) ret[i][j] -= ret[i - 1][j - 1];
        }
    }
    return ret;
}

template<class T>
grid<T> partial_diff(grid<T> ret) {
    for (int i = ret.n - 1; i >= 0; i--) {
        for (int j = ret.m - 1; j >= 0; j--) {
            if (i >= 1) ret[i][j] -= ret[i - 1][j];
            if (j >= 1) ret[i][j] -= ret[i][j - 1];
            if (i >= 1 && j >= 1) ret[i][j] += ret[i - 1][j - 1];
        }
    }
    return ret;
}

template<typename T>
T ask_sum(const grid<T>& gr, pos_grid minp, pos_grid maxp) {
    auto [minr, minc] = minp;
    auto [maxr, maxc] = maxp;
    minr--, minc--, maxr--, maxc--;
    T ret = gr[maxr][maxc];
    if (minr >= 0 && minc >= 0) ret += gr[minr][minc];
    if (minr >= 0) ret -= gr[minr][maxc];
    if (minc >= 0) ret -= gr[maxr][minc];
    return ret;
}

template<typename T>
void add_diff(const grid<T>& gr, pos_grid minp, pos_grid maxp, T val) {
    auto [minr, minc] = minp;
    auto [maxr, maxc] = maxp;
    gr[minr][minc] += val;
    if (maxr < gr.n && maxc < gr.m) gr[maxr][maxc] += val;
    if (maxr < gr.n) gr[maxr][minc] -= val;
    if (maxr < gr.m) gr[minr][maxc] -= val;
}
/*---------------------------*/