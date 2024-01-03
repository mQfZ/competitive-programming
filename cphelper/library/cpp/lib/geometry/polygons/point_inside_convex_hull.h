#include <bits/stdc++.h>
using namespace std;
#pragma once

#include <lib/geometry/primitives/point.h>

#include <lib/geometry/polygons/convex_hull.h>

/**
 * Point in Convex Hull
 * Description:
 *    Checks if a point is inside the convex hull. Returns 1 if inside, 0 if
 *    on an edge and -1 if outside.
 * Time Complexity: O(log n)
 * Verification:
 *    https://github.com/mQfZ/competitive-programming/blob/master/src/usaco/2014/jan/gold/1/main.cpp
 *    https://codeforces.com/contest/1299/submission/235671377
 */

template <typename T>
int inside_hull(const vector<point<T>>& h, const point<T>& p) {
    assert(h.size() > 0);
    if (h.size() < 3) return on_seg(h[0], h.back(), p) ? 0 : -1;
    if (side_of(h[0], h[1], p) == -1 || side_of(h[0], h.back(), p) == 1) return -1;
    int l = 1, r = (int) h.size() - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (side_of(h[0], h[m], p) <= 0) r = m;
        else l = m;
    }
    assert(side_of(h[0], h[l], p) >= 0);
    assert(side_of(h[0], h[r], p) <= 0);
    return side_of(h[l], h[r], p);
}
