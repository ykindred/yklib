#include "../head.hpp"

// 稀疏表, Sparse Table.
// T为数据类型, op为一个函数指针, 默认产生区间最小值
template <typename T, T (*op)(T, T) = std::min>
struct SpTable {
    int n;
    int max_log;
    vector<vector<T>> st;

    SpTable(const vector<T>& a) : n(a.size()) {
        if (n == 0) return;
        max_log = 32 - __builtin_clz(n);
        st.assign(max_log, vector<T>(n));

        for (int i = 0; i < n; i++) st[0][i] = a[i];

        for (int j = 1; j < max_log; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                st[j][i] = op(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    // 查询区间 [l, r) 的结果: O(1)
    T prod(int l, int r) const {
        assert(0 <= l && l < r && r <= n);
        int j = 31 - __builtin_clz(r - l);
        return op(st[j][l], st[j][r - (1 << j)]);
    }
};
/*---------------------------*/