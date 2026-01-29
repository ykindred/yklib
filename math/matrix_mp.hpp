#include "../head.hpp"
#include "colvector.hpp"
template <int N>
struct Matrix_mp {
    array<array<ll, N>, N> a;
    Matrix_mp() {
        for (int i = 0; i < N; i++) {
            fill(a[i].begin(), a[i].end(), INFLL);
        }
    }

    ll* operator[](int i) {
        return a[i].data();
    }
    const ll* operator[](int i) const {
        return a[i].data();
    }
    
    static Matrix_mp e() {
        Matrix_mp ret;
        for (int i = 0; i < N; i++) {
            ret[i][i] = 0;
        }
        return ret;
    }
    
    friend Matrix_mp operator+(Matrix_mp lt, const Matrix_mp& rt) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                lt[i][j] = min(lt[i][j], rt[i][j]);
            }
        }
        return lt;
    }
    friend Matrix_mp operator*(const Matrix_mp& lt, const Matrix_mp& rt) {
        Matrix_mp ret;
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                if (lt[i][k] >= INFLL) {
                    continue;
                }
                
                for (int j = 0; j < N; j++) {
                    ll now;
                    if (lt[i][k] >= INFLL || rt[k][j] >= INFLL) {
                        now = INFLL;
                    } else {
                        now = lt[i][k] + rt[k][j];
                    }
                    ret[i][j] = min(ret[i][j], now);
                }
            }
        }
        return ret;
    }
    
    Matrix_mp pow(ll b) const {
        Matrix_mp ret = e();
        Matrix_mp t = *this;
        while (b > 0) {
            if (b & 1) {
                ret = ret * t;
            }
            
            t = t * t;
            b >>= 1;
        }
        return ret;
    }
    
    ColVector<ll, N> operator*(const ColVector<ll, N>& vec) {
        ColVector<ll, N> ret(INFLL);
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                if (a[i][k] >= INFLL) {
                    continue;
                }
                ll now;
                if (a[i][k] >= INFLL || vec[k] >= INFLL) {
                    now = INFLL;
                } else {
                    now = a[i][k] + vec[k];
                }
                ret[i] = min(ret[i], now);
            }
        }
        return ret;
    }
};