#include "../../head.hpp"
#include "../tag/assign.hpp"
struct summin_assign {
    using T = Tag_assign;
    struct S {
        ll sum = 0;
        ll vmin = INFLL;
        ll len = 0;
        friend S operator+(const S& a, const S& b) {
            return { a.sum + b.sum, std::min(a.vmin, b.vmin), a.len + b.len };
        }
        void apply(const T& t) {
            if (!t.has) return;
            sum = t.val * len;
            vmin = t.val;
        }
    };
};