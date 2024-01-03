#include <bits/stdc++.h>
using namespace std;
#pragma once

/**
 * Line
 * Description:
 *    Line class for line containers.
 * Time Complexity: N/A
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/cses/2087/main.cpp
 */

template <typename T>
struct line {
    mutable T m, b, p;
    T eval(T x) const { return m * x + b; }
    bool operator<(const line& o) const { return m < o.m; }
    bool operator<(T x) const { return p < x; }
};
