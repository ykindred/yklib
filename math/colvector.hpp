#include "../head.hpp"

template <class S, int N>
struct ColVector {
    array<S, N> a;
    ColVector(S def) {
        fill(a.begin(), a.end(), def);
    }
    
    S& operator[](int i) {
        return a[i];
    }
    const S& operator[](int i) const {
        return a[i];
    }
};