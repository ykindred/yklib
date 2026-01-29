#pragma once
#include "../head.hpp"
/*--------segtree.hpp--------*/
// 线段树(Segment Tree)
// S(info) 要求包含:
//     数据 = 零元
//     friend S operator+(const S&, const S&)
// 初始化需要手动写出初始化数组.
template<class S>
struct SegTree {
    int n, size, log;
    vector<S> d;
private:
    void pull(int x) {
        d[x] = d[x * 2] + d[x * 2 + 1];
    }

public:
    // 重新建树, O(n)
    void build(const vector<S>& arr) {
        n = arr.size();
        log = 0;
        size = 1;
        while (size < n) {
            size *= 2;
            log++;
        }
        d.assign(2 * size, S());
        for (int i = 0; i < n; i++) {
            d[size + i] = arr[i];
        }
        for (int i = size - 1; i > 0; i--) {
            pull(i);
        }
    }

    SegTree(const vector<S>& arr) {
        build(arr);
    }

    // 单点赋值, O(log n)
    void set(int pos, const S& val) {
        assert(0 <= pos && pos < n);
        pos += size;
        d[pos] = val;
        pos /= 2;
        for (; pos > 0; pos /= 2) {
            pull(pos);
        }
    }
    
    // 单点查询, O(1)
    S get(int pos) {
        assert(0 <= pos && pos < n);
        return d[pos + size];
    }

    // 区间查询[lt, rt), O(log n)
    S query(int lt, int rt) {
        assert(0 <= lt && lt <= rt && rt <= n);
        if (lt == rt) {
            return S();
        }
        if (lt + 1 == rt) {
            return d[size + lt];
        }
        lt += size;
        rt += size;
        S sumlt, sumrt;
        for (; lt < rt; lt /= 2, rt /= 2) {
            if (lt % 2 == 1) {
                sumlt = sumlt + d[lt];
                lt++;
            }
            if (rt % 2 == 1) {
                rt--;
                sumrt = d[rt] + sumrt;
            }
        }
        return sumlt + sumrt;
    }
    // 扩展操作:

    // 查找最大的r(l<=r<= n)使得check(const S& s)为真
    // check(S())必须为true, O(log n)
    template <class F>
    int max_right(int l, F check) {
        assert(0 <= l && l <= n);
        assert(check(S()));
        if (l == n) {
            return n;
        }
        l += size;
        S sum;
        do {
            while (l % 2 == 0) {
                l /= 2;
            }
            if (!check(sum + d[l])) {
                while (l < size) {
                    l *= 2;
                    if (check(sum + d[l])) {
                        sum = sum + d[l];
                        l++;
                    }
                }
                return l - size;
            }
            sum = sum + d[l];
            l++;
        } while (l != lowbit(l));
        return n;
    }

    // 查找最小的l(0<=l<=r)使得check(const S& s)为真
    // check(S())必须为 true, O(log n)
    template <class F>
    int min_left(int r, F check) {
        assert(0 <= r && r <= n);
        assert(check(S()));
        if (r == 0) {
            return 0;
        }
        r += size;
        S sum;
        do {
            r--;
            while (r > 1 && (r % 2)) {
                r /= 2;
            }
            if (!check(d[r] + sum)) {
                while (r < size) {
                    r = 2 * r + 1;
                    if (check(d[r] + sum)) {
                        sum = d[r] + sum;
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sum = d[r] + sum;
        } while (r != lowbit(r));
        return 0;
    }
};
/*---------------------------*/