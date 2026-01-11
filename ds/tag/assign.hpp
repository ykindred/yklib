#include "../../head.hpp"
struct Tag_assign {
    using T = Tag_assign;
    bool has = false;
    ll val = 0;
    void apply(const T& t) {
        if (t.has) {
            has = true;
            val = t.val;
        }
    }
};