#pragma once
#include "../../head.hpp"
/*---------modint.hpp--------*/
// 静态modint
template <int mod> 
struct ModInt {
    u32 val;

    constexpr ModInt() : val(0) {}
    constexpr ModInt(ll x) : val((x %= mod) < 0 ? x + mod : x) {};
    constexpr ModInt(int x) : val((x %= mod) < 0 ? x + mod : x) {};
    static constexpr ModInt raw(u32 v) {
        ModInt x;
        x.val = v;
        return x;
    }

    ModInt &operator+=(const ModInt &p) {
        if ((val += p.val) >= mod) {
            val -= mod;
        }
        return *this;
    }
    ModInt &operator-=(const ModInt &p) {
        if ((val += mod - p.val) >= mod) {
            val -= mod;
        }
        return *this;
    }
    ModInt &operator*=(const ModInt &p) {
        val = u64(val) * p.val % mod;
        return *this;
    }
    ModInt &operator/=(const ModInt &p) {
        // O(log mod)
        assert(p.val != 0 && "modint div zero");
        *this *= p.inv();
        return *this;
    }
    ModInt operator-() const { return ModInt(val ? mod - val : u32(0)); }
    ModInt operator+(const ModInt &p) const { return ModInt(*this) += p; }
    ModInt operator-(const ModInt &p) const { return ModInt(*this) -= p; }
    ModInt operator*(const ModInt &p) const { return ModInt(*this) *= p; }
    ModInt operator/(const ModInt &p) const { return ModInt(*this) /= p; }  // O(log mod)
    bool operator==(const ModInt &p) const { return val == p.val; }
    bool operator!=(const ModInt &p) const { return val != p.val; }
    
    // 快速幂, O(log n)
    ModInt pow(ll n) const {
        if (n < 0) return inv().pow(-n);
        ModInt ret(1), mul(val);
        while (n > 0) {
            if (n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    // 求逆元, 使用exgcd. O(log mod)
    ModInt inv() const {
        assert(val != 0);
        assert((std::gcd(val, mod) == 1));

        int a = val, b = mod, u = 1, v = 0, t;
        while (b > 0) {
            t = a / b;
            swap(a -= t * b, b);
            swap(u -= t * v, v);
        }
        return ModInt(u);
    }

    // 输入输出
    friend std::istream &operator>>(std::istream &is, ModInt &a) {
        ll t;
        is >> t;
        a = ModInt(t);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const ModInt &a) {
        return os << a.val;
    }
};
using mint107 = ModInt<1000000007>;
using mint998 = ModInt<998244353>;
/*---------------------------*/