#pragma once
#include "head.hpp"
template <typename T, typename F>
bool binary_search(F check, T good, T bad, T &ans) {
    if (check(good)) {
        if (check(bad)) {
            ans = bad;
            return true;
        }
    } 
    else if (check(bad)) std::swap(good, bad);
    else return false;

    while (std::abs(good - bad) > 1) {
        T mid = good + (bad - good) / 2;
        if (check(mid)) good = mid;
        else bad = mid;
    }
    ans = good;
    return true;
}