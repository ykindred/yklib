#include "../head.hpp"
template <typename S, int N>
struct Matrix {
    array<array<S, N>, N> a;
    Matrix(S def = S()) {
        for (int i = 0; i < N; i++) {
            fill(a[i].begin(), a[i].end(), def);
        }
    }
    
    // 允许 Matrix<int, 2> mat = {{1, 2}, {3, 4}};
    Matrix(std::initializer_list<std::initializer_list<S>> init) {
        S def = S();
        for (int i = 0; i < N; i++) {
            fill(a[i].begin(), a[i].end(), def);
        }
        int i = 0;
        for (auto& row : init) {
            if (i >= N) break;
            int j = 0;
            for (auto& val : row) {
                if (j >= N) break;
                a[i][j] = val;
                j++;
            }
            i++;
        }
    }

    S* operator[](int i) {
        return a[i].data();
    }
    const S* operator[](int i) const {
        return a[i].data();
    }
    
    static Matrix e() {
        Matrix ret;
        for (int i = 0; i < N; i++) {
            ret[i][i] = 1;
        }
        return ret;
    }

    Matrix& operator+=(const Matrix& oth) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] += oth[i][j];
            }
        }
        return *this;
    }
    
    Matrix operator-() const {
        Matrix ret;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                ret[i][j] = -a[i][j];
            }
        }
        return ret;
    }
    
    Matrix& operator-=(const Matrix& oth) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                a[i][j] -= oth[i][j];
            }
        }
        return *this;
    }
    
    Matrix& operator*=(const Matrix& oth) {
        Matrix ret;
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                if (a[i][k] == S()) {
                    continue;
                }
                
                for (int j = 0; j < N; j++) {
                    ret[i][j] += a[i][k] * oth[k][j];
                }
            }
        }
        *this = ret;
        return *this;
    }
    
    Matrix inv() const {
        Matrix ret = e();
        Matrix tmp = *this;
        for (int i = 0; i < N; i++) {
            int piv = i;
            while (piv < N && tmp[piv][i] == S()) {
                piv++;
            }
            if (piv == N) {
                return Matrix();
            }
            
            if (piv != i) {
                swap(tmp.a[i], tmp.a[piv]);
                swap(ret.a[i], ret.a[piv]);
            }

            S invval = S(1) / tmp[i][i];
            for (int j = 0; j < N; j++) {
                tmp[i][j] *= invval;
                ret[i][j] *= invval;
            }
            
            for (int k = 0; k < N; k++) {
                if (k != i) {
                    S factor = tmp[k][i];
                    if (factor == S()) {
                        continue;
                    }
                    for (int j = 0; j < N; j++) {
                        tmp[k][j] -= factor * tmp[i][j];
                        ret[k][j] -= factor * ret[i][j];
                    }
                }
            }
        }
        return ret;
    }
    
    Matrix& operator/=(const Matrix& oth) {
        return *this *= oth.inv();
    }
    
    friend Matrix operator+(Matrix lt, const Matrix& rt) {
        return lt += rt;
    }
    friend Matrix operator-(Matrix lt, const Matrix& rt) {
        return lt -= rt;
    }
    friend Matrix operator*(Matrix lt, const Matrix& rt) {
        return lt *= rt;
    }
    friend Matrix operator/(Matrix lt, const Matrix& rt) {
        return lt /= rt;
    }
    
    Matrix pow(ll b) const {
        Matrix ret = e();
        Matrix t = *this;
        while (b > 0) {
            if (b & 1) {
                ret *= t;
            }
            
            t *= t;
            b >>= 1;
        }
        return ret;
    }
    
    friend ostream& operator<<(ostream& os, const Matrix& mat) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                os << mat[i][j];
                if (j < N - 1) {
                    os << ' ';
                }
            }
            if (i < N - 1) {
                os << '\n';
            }
        }
        return os;
    }
};