#pragma once
#include "tools.hpp"
#include "exgcd.hpp"
/*-------equations.hpp-------*/
namespace numth {
    // solve linear diophantine equation with 2 variables
    // solve Ax + By = C, return [is_solved, x0, y0, stepx, stepy]
    // x = x0 + k * stepx, y = y0 + k * stepy, x is minimum non-negative
    inline tuple<bool, ll, ll, ll, ll> solve_LDE(ll A, ll B, ll C) {
        if (A == 0 && B == 0) {
            if (C == 0) return { true, 0, 0, 0, 0 };
            else return { false, 0, 0, 0, 0 };
        }

        auto [_x, _y, g] = exgcd(A, B);
        if (C % g != 0) return { false, 0, 0, 0, 0 };
        ll t = C / g;

        ll stepx = B / g, stepy = -A / g;
        if (stepx < 0) {
            stepx = -stepx;
            stepy = -stepy;
        }
        ll x0;
        if (stepx == 0) {
            x0 = _x * t;
        } 
        else {
            x0 = mul(_x, t, stepx);
        }
        ll y0 = 0;
        if (B != 0) {
            y0 = ((i128)C - (i128)A * x0) / B;
        }
        return { true, x0, y0, stepx, stepy };
    }

    // solve linear congruence equation
    // find x such that Ax === C (mod B), return -1 if x not exists
    inline ll solve_LCE(ll A, ll C, ll B) {
        auto [exist, x, y, _, __] = solve_LDE(A, B, C);
        if (!exist) return -1;
        return x;
    }
}
/*---------------------------*/