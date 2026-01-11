#include "../../head.hpp"
#include "../tag/add.hpp"

struct sum_add {
    using T = Tag_add;
    struct S {
        ll v = 0;
        ll len = 0;
        friend S operator+(S a, S b) {
            return {a.v + b.v, a.len + b.len};
        }
        void apply(T c) {
            v += c.v * len;
        }
    };
};