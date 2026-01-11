#include "../head.hpp"
/*-----segtree_lazy.hpp------*/
// 懒标记线段树(Lazy Segment Tree)
// Info 要求包含: 
//     节点数据 = 空区间状态(零元)
//     void apply(const Tag&) 标记作用于数据
//     friend Info operator+(const Info&, const Info&)
// Tag 要求包含:
//     标记数据 = 叠加标记不变的状态(单位元)
//     void apply(const Tag&) 标记叠加
template<class Info, class Tag>
struct SegTree_lazy {
    int n, size, log;
    vector<Info> d;
    vector<Tag> tag;

    #define anc(x) ((x) >> i)
    #define ck(x) ((anc(x) << i) != x)
    void _pull(int x) {
        d[x] = d[x * 2] + d[x * 2 + 1];
    }
    void _apply(int x, const Tag& t) {
        d[x].apply(t);
        if (x < size) {
            tag[x].apply(t);
        }
    }
    void _push(int x) {
        _apply(x * 2, tag[x]); 
        _apply(x * 2 + 1, tag[x]);
        tag[x] = Tag();
    }

    // 对外接口

    // 重新建树
    void build(const vector<Info>& arr) {
        n = arr.size();
        log = 0;
        size = 1;
        while (size < n) {
            size *= 2;
            log++;
        }
        d.assign(2 * size, Info());
        tag.assign(size, Tag());
        for (int i = 0; i < n; i++) {
            d[size + i] = arr[i];
        }
        for (int i = size - 1; i > 0; i--) {
            _pull(i);
        }
    }

    SegTree_lazy() : n(0) {}
    SegTree_lazy(const vector<Info>& arr) {
        build(arr);
    }
    SegTree_lazy(int _n, const Info& def = Info()) {
        build(vector<Info>(_n, def));
    }

    // 单点赋值, O(log n)
    void set(int x, const Info& val) {
        assert(0 <= x && x < n);
        x += size;
        for (int i = log; i > 0; i--) {
            _push(anc(x));
        }
        d[x] = val;
        for (int i = 1; i < log + 1; i++) {
            _pull(anc(x));
        }
    }

    // 区间修改[lt, rt), O(log n)
    void modify(int lt, int rt, const Tag& t) {
        assert(0 <= lt && lt <= rt && rt <= n);
        if (lt == rt) {
            return;
        }
        lt += size;
        rt += size;
        for (int i = log; i > 0; i--) {
            if (ck(lt)) {
                _push(anc(lt));
            }
            if (ck(rt)) {
                _push(anc(rt - 1));
            }
        }
        for (int i = lt, j = rt; i < j; i /= 2, j /= 2) {
            if (i % 2 == 1) {
                _apply(i, t);
                i++;
            }
            if (j % 2 == 1) {
                j--;
                _apply(j, t);
            }
        }
        for (int i = 1; i < log + 1; i++) {
            if (ck(lt)) {
                _pull(anc(lt));
            }
            if (ck(rt)) {
                _pull(anc(rt - 1));
            }
        }
    }

    // 区间查询[lt, rt)
    Info prod(int lt, int rt) {
        assert(0 <= lt && lt <= rt && rt <= n);
        if (lt == rt) {
            return Info();
        }
        lt += size;
        rt += size;
        for (int i = log; i > 0; i--) {
            if (ck(lt)) {
                _push(anc(lt));
            }
            if (ck(rt)) {
                _push(anc(rt - 1));
            }
        }
        Info sumlt, sumrt;
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

    // 扩展接口
    // 查最右rt使[lt, rt)满足check, O(log n)
    template <class F> 
    int search_right(int lt, F check) {
        if (lt == n) {
            return n;
        }
        lt += size;
        for (int i = log; i > 0; i--) {
            _push(anc(lt));
        }
        Info sum;
        do {
            while (lt % 2 == 0) {
                lt /= 2;
            }
            if (!check(sum + d[lt])) {
                while (lt < size) {
                    _push(lt); 
                    lt *= 2;
                    if (check(sum + d[lt])) {
                        sum = sum + d[lt];
                        lt++;
                    }
                }
                return lt - size;
            }
            sum = sum + d[lt];
            lt++;
        } while (lowbit(lt) != lt);
        return n;
    }

    // 查最左lt使得[lt, rt)满足check
    template <class F> 
    int search_left(int rt, F check) {
        if (rt == 0) {
            return 0;
        }
        rt += size;
        for (int i = log; i > 0; i--) {
            _push(anc(rt - 1));
        }
        Info sum;
        do {
            rt--;
            while (rt > 1 && rt % 2 == 1) {
                rt /= 2;
            }
            if (!check(d[rt] + sum)) {
                while (rt < size) {
                    _push(rt); 
                    rt = 2 * rt + 1;
                    if (check(d[rt] + sum)) {
                        sum = d[rt] + sum;
                        rt--;
                    }
                }
                return rt + 1 - size;
            }
            sum = d[rt] + sum;
        } while (lowbit(rt) != rt);
        return 0;
    }
    #undef anc
    #undef ck
};
/*---------------------------*/