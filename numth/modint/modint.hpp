#pragma once
#include "../../head.hpp"
/*---------modint.hpp--------*/

// static modular integer for 0 < MOD < 2^31
// MOD should be constexpr
template <int MOD> 
struct modint {
    static constexpr u32 umod = u32(MOD);
    static constexpr int mod = MOD;
    static constexpr int get_mod() { return mod; }
    static_assert(umod < u32(1) << 31);
    u32 val;

    // fast construction of raw modint
    static modint raw(u32 v) {
        modint x;
        x.val = v;
        return x;
    }

    // constructors
    constexpr modint() : val(0) {}
    constexpr modint(u32 x) : val(x % umod) {}
    constexpr modint(unsigned long x) : val(x % umod) {}
    constexpr modint(u64 x) : val(x % umod) {}
    constexpr modint(u128 x) : val(x % umod) {}
    constexpr modint(int x) : val((x %= mod) < 0 ? x + mod : x) {};
    constexpr modint(ll x) : val((x %= mod) < 0 ? x + mod : x) {};
    constexpr modint(i128 x) : val((x %= mod) < 0 ? x + mod : x) {};

    // operators
    bool operator<(const modint &other) const { return val < other.val; }
    modint &operator+=(const modint &p) {
        if ((val += p.val) >= umod) {
            val -= umod;
        }
        return *this;
    }
    modint &operator-=(const modint &p) {
        if ((val += umod - p.val) >= umod) {
            val -= umod;
        }
        return *this;
    }
    modint &operator*=(const modint &p) {
        val = u64(val) * p.val % umod;
        return *this;
    }
    modint &operator/=(const modint &p) {
        // O(log mod)
        assert(p.val != 0 && "modint div zero");
        *this *= p.inv();
        return *this;
    }
    modint operator-() const { return modint::raw(val ? mod - val : u32(0)); }
    modint operator+(const modint &p) const { return modint(*this) += p; }
    modint operator-(const modint &p) const { return modint(*this) -= p; }
    modint operator*(const modint &p) const { return modint(*this) *= p; }
    modint operator/(const modint &p) const { return modint(*this) /= p; }  // O(log mod)
    bool operator==(const modint &p) const { return val == p.val; }
    bool operator!=(const modint &p) const { return val != p.val; }
    
    // quick power of O(log n)
    modint qkpow(ll n) const {
        if (n < 0) return inv().qkpow(-n);
        modint ret(1), mul(val);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    // inv by extgcd of O(log mod)
    modint inv() const {
        // no inv for zero, no inv for non-coprime
        assert(val != 0 && "modint inv zero");
        assert((gcd((int)val, mod) == 1) && "modint inv not coprime");

        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b), swap(u -= t * v, v);
        }
        return modint(u);
    }

    // stream IO
    friend std::istream &operator>>(std::istream &is, modint &a) {
        ll t;
        is >> t;
        a = modint(t);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const modint &a) {
        return os << a.val;
    }
};
using mint107 = modint<1000000007>;
using mint998 = modint<998244353>;
/*---------------------------*/