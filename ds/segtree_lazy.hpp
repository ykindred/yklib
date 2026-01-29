#include "../head.hpp"
/*-----segtree_lazy.hpp------*/
// 懒标记线段树(Lazy Segment Tree)
// S(info) 要求包含: 
//     节点数据 = 空区间状态(零元)
//     void apply(const T&) 标记作用于数据
//     friend Info operator+(const S&, const S&)
// T(tag) 要求包含:
//     标记数据 = 叠加标记不变的状态(单位元)
//     void apply(const T&) 标记叠加
// 初始化需要手动写出初始化数组
template<class S, class T>
struct SegTree_lazy {
    int n, size, log;
    vector<S> d;
    vector<T> tag;

    #define anc(x) ((x) >> i)
    #define ck(x) ((anc(x) << i) != x)
private:
    void pull(int x) {
        d[x] = d[x * 2] + d[x * 2 + 1];
    }
    void apply(int x, const T& t) {
        d[x].apply(t);
        if (x < size) {
            tag[x].apply(t);
        }
    }
    void push(int x) {
        apply(x * 2, tag[x]); 
        apply(x * 2 + 1, tag[x]);
        tag[x] = T();
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
        tag.assign(size, T());
        for (int i = 0; i < n; i++) {
            d[size + i] = arr[i];
        }
        for (int i = size - 1; i > 0; i--) {
            pull(i);
        }
    }

    SegTree_lazy(const vector<S>& arr) {
        build(arr);
    }

    // 单点赋值, O(log n)
    void set(int pos, const S& val) {
        assert(0 <= pos && pos < n);
        pos += size;
        for (int i = log; i > 0; i--) {
            push(anc(pos));
        }
        d[pos] = val;
        for (int i = 1; i < log + 1; i++) {
            pull(anc(pos));
        }
    }

    // 区间修改[lt, rt), O(log n)
    void modify(int lt, int rt, const T& t) {
        assert(0 <= lt && lt <= rt && rt <= n);
        if (lt == rt) {
            return;
        }
        lt += size;
        rt += size;
        for (int i = log; i > 0; i--) {
            if (ck(lt)) {
                push(anc(lt));
            }
            if (ck(rt)) {
                push(anc(rt - 1));
            }
        }
        for (int i = lt, j = rt; i < j; i /= 2, j /= 2) {
            if (i % 2 == 1) {
                apply(i, t);
                i++;
            }
            if (j % 2 == 1) {
                j--;
                apply(j, t);
            }
        }
        for (int i = 1; i < log + 1; i++) {
            if (ck(lt)) {
                pull(anc(lt));
            }
            if (ck(rt)) {
                pull(anc(rt - 1));
            }
        }
    }
    
    // 区间查询[lt, rt), O(log n)
    S query(int lt, int rt) {
        assert(0 <= lt && lt <= rt && rt <= n);
        if (lt == rt) {
            return S();
        }
        lt += size;
        rt += size;
        for (int i = log; i > 0; i--) {
            if (ck(lt)) {
                push(anc(lt));
            }
            if (ck(rt)) {
                push(anc(rt - 1));
            }
        }
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
    #undef anc
    #undef ck
    
    // 扩展操作
    // 查找最大的r使得[l, r)满足bool check(const S& s), O(log n)
    template <class F>
    int max_right(int l, F check) {
        assert(0 <= l && l <= n);
        assert(check(S()));
        if (l == n) {
            return n;
        }
        l += size;
        for (int i = log; i >= 1; i--) {
            push(l >> i);
        }
        S sum;
        do {
            while (l % 2 == 0) {
                l /= 2;
            }
            if (!check(sum + d[l])) {
                while (l < size) {
                    push(l);
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

    // 查找最小的l使得[l, r)满足bool check(const S& s), O(log n)
    template <class F>
    int min_left(int r, F check) {
        assert(0 <= r && r <= n);
        assert(check(S()));
        if (r == 0) {
            return 0;
        }
        r += size;
        for (int i = log; i >= 1; i--) {
            push((r - 1) >> i);
        }
        S sum;
        do {
            r--;
            while (r > 1 && (r % 2)) {
                r /= 2;
            }
            if (!check(d[r] + sum)) {
                while (r < size) {
                    push(r);
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