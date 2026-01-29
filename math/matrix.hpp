#include "../head.hpp"
#include "colvector.hpp"
template <typename S, int N>
struct Matrix {
    array<array<S, N>, N> a;
    Matrix(S def = S()) {
        for (int i = 0; i < N; i++) {
            fill(a[i].begin(), a[i].end(), def);
        }
    }

    S* operator[](int i) {
        return a[i].data();
    }
    const S* operator[](int i) const {
        return a[i].data();
    }
    
    // 单位矩阵
    static Matrix e() {
        Matrix ret;
        for (int i = 0; i < N; i++) {
            ret[i][i] = 1;
        }
        return ret;
    }
    
    // 加法
    friend Matrix operator+(Matrix lt, const Matrix& rt) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                lt[i][j] += rt[i][j];
            }
        }
        return lt;
    }

    // 乘法
    friend Matrix operator*(const Matrix& lt, const Matrix& rt) {
        Matrix ret;
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                if (lt[i][k] == S()) {
                    continue;
                }
                
                for (int j = 0; j < N; j++) {
                    ret[i][j] += lt[i][k] * rt[k][j];
                }
            }
        }
        return ret;
    }

    Matrix pow(ll b) const {
        Matrix ret = e();
        Matrix t = *this;
        while (b > 0) {
            if (b & 1) {
                ret = ret * t;
            }
            
            t = t * t;
            b >>= 1;
        }
        return ret;
    }

    ColVector<S, N> operator*(const ColVector<S, N>& vec) {
        ColVector<S, N> ret;
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                if (a[i][k] == 0) {
                    continue;
                }
                
                ret[i] = ret[i] + (a[i][k] * vec[k]);
            }
        }
        return ret;
    }
};