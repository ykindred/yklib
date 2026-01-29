#include "../head.hpp"
/*--------sptable.hpp--------*/
// 稀疏表, Sparse Table.
// S为数据类型, 要求定义friend S op(const S& a, const S& b), 要求满足幂等性
template <typename S>
struct SpTable {
    int n;
    int max_log;
    vector<vector<S>> st;

    SpTable(const vector<S>& a) : n(a.size()) {
        assert(n > 0);
        max_log = 32 - __builtin_clz(n);
        st.assign(max_log, vector<S>(n));

        for (int i = 0; i < n; i++) {
            st[0][i] = a[i];
        }

        for (int j = 1; j < max_log; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = op(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    // 查询区间[l, r), O(1)
    S query(int l, int r) const {
        assert(0 <= l && l < r && r <= n);
        int j = 31 - __builtin_clz(r - l);
        return op(st[j][l], st[j][r - (1 << j)]);
    }
};
/*---------------------------*/