#pragma once
#include "fwktree.hpp"
/*------fwktree_ext.hpp------*/
namespace fwt_ext {
    // 查找权值树状数组上第k小元素的索引
    // 若总数不满k, 返回n
    // O(log n)
    template <class fwtree>
    int kth(const fwtree& fwk, ll k) {
        int n = fwk.n;
        if (n <= 0 || k <= 0) return -1;
        int pos = 0;
        int max_pow = 1 << (31 - __builtin_clz(n));
        for (int i = max_pow; i > 0; i >>= 1) {
            if (pos + i <= n && fwk.d[pos + i] < k) {
                k -= fwk.d[pos + i];
                pos += i;
            }
        }
        return pos;
    }

    // 采用倍增查找满足check(pref[i]) = true的最大下标i.
    // check 单调谓词函数[T, ..., T, F, ..., F], 返回0-based下的最大下标. 
    // 若check(empty) = false, 返回-1
    template <
        class S, 
        S (*op)(S, S), 
        S (*e)(), 
        S (*inv)(S, S),
        typename F
    >
    int search(const FwkTree<S, op, e, inv>& fwk, F&& check) {
        int n = fwk.n;
        if (n <= 0) return -1;
        int pos = 0;
        int max_pow = 1 << (31 - __builtin_clz(n));
        S cur = e();
        if (!check(cur)) return -1;
        for (int i = max_pow; i > 0; i >>= 1) {
            if (pos + i <= n) {
                S next_val = op(cur, fwk.d[pos + i]);
                if (check(next_val)) {
                    pos += i;
                    cur = next_val;
                }
            }
        }
        return pos - 1;
    }
}
/*---------------------------*/