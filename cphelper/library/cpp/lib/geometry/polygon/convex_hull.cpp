#include <bits/stdc++.h>
using namespace std;
#pragma once

#include <lib/geometry/primitive/point.cpp>

/**
 * Convext Hull
 * Description:
 *    Creates a convex hull (subset of points that forms the smallest convex
 *    polygon which encloses all points in the set). Returns in counter
 *    clockwise order where the leftmost point is first.
 * Time Complexity: O(n log n)
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/usaco/2014/jan/gold/1/main.cpp
 */

template <typename T>
vector<point<T>> convex_hull(vector<point<T>> v) {
    sort(v.begin(), v.end());
    int n = (int) v.size();
    if (n < 3) return v;
    vector<point<T>> h;
    for (int i = 0; i < n; ++i) {
        while (h.size() > 1 && h[h.size() - 2].cross(h.back(), v[i]) <= 0) h.pop_back();
        h.push_back(v[i]);
    }
    auto sz = h.size();
    for (int i = n - 2; i >= 0; --i) {
        while (h.size() > sz && h[h.size() - 2].cross(h.back(), v[i]) <= 0) h.pop_back();
        h.push_back(v[i]);
    }
    h.pop_back();
    return h;
};
