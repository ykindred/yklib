#include "../../head.hpp"
#include "../tag/add.hpp"

struct max_add {
    using T = Tag_add;
    struct S {
        ll v = -INFLL;
        friend S operator+(S a, S b) {
            return {std::max(a.v, b.v)};
        }
        void apply(T c) {
            v += c.v;
        }
    };
};