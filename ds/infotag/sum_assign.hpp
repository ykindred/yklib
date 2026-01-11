#include "../tag/assign.hpp"

struct sum_assign {
    using T = Tag_assign;
    struct S { // sum
        ll v = 0;
        ll len = 0;
        friend S operator+(S a, S b) {
            return {a.v + b.v, a.len + b.len};
        }
        void apply(T c) {
            if (!c.has) return;
            v = len * c.val;
        }
    };
};