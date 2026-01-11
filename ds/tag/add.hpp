#include "../../head.hpp"
struct Tag_add {
    ll v = 0;
    void apply(Tag_add a) {
        v += a.v;
    }
};