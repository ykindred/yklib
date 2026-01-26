#include "../head.hpp"
#include "matrix.hpp"

template <class S, int N>
struct ColVector {
    array<S, N> a;
    ColVector(S def = S()) {
        fill(a.begin(), a.end(), def);
    }
    
    ColVector(std::initializer_list<S> init) {
        fill(a.begin(), a.end(), S());
        int i = 0;
        for (auto val : init) {
            if (i < N) {
                a[i] = val;
                i++;
            }
        }
    }
    
    S& operator[](int i) {
        return a[i];
    }
    const S& operator[](int i) const {
        return a[i];
    }
    
    ColVector& operator+=(const ColVector& oth) {
        for (int i = 0; i < N; i++) {
            a[i] += oth[i];
        }
        return *this;
    }
    
    ColVector& operator-=(const ColVector& oth) {
        for (int i = 0; i < N; i++) {
            a[i] -= oth[i];
        }
        return *this;
    }
    
    friend ColVector operator+(ColVector lt, const ColVector& rt) {
        return lt += rt;
    }

    friend ColVector operator-(ColVector lt, const ColVector& rt) {
        return lt -= rt;
    }
    
    friend ColVector operator*(const Matrix<S, N>& mat, const ColVector& vec) {
        ColVector ret;
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                if (mat[i][k] == S()) {
                    continue;
                }
                
                ret[i] += mat[i][k] * vec[k];
            }
        }
        return ret;
    }
    
    friend ostream& operator<<(ostream& os, const ColVector& a) {
        for (int i = 0; i < N; i++) {
            os << a[i];
            if (i < N - 1) {
                os << ' ';
            }
        }
        return os;
    }
};