#include <bits/stdc++.h>
using namespace std;
#pragma once

/**
 * 2D Fenwick Tree
 * Description:
 *    2D point increment/update and rectangle query where the operation is 
 *    invertible (addition, multiplication). Can also be rectangle update 
 *    and point query.
 * Time Complexity:
 *    Update: O(log n * log m)
 *    Query: O(log n * log m)
 * Verification:
 *     https://github.com/mQfZ/competitive-programming/blob/master/src/usaco/2017/open/plat/1/main.cpp
 *     https://github.com/mQfZ/competitive-programming/blob/master/src/cses/1739/main.cpp
 */

template <typename T>
struct fenwick2d {
    int n, m;
    vector<vector<T>> tree;

    fenwick2d(int _n = -1, int _m = -1) {
        if (_n >= 0 && _m >= 0) init(_n, _m);
    }

    void init(int _n, int _m) {
        n = _n;
        m = _m;
        tree.assign(n, vector<T>(m, {}));
    }

    // increment point (x, y) by v
    void add(int x, int y, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            for (int j = y + 1; j <= m; j += j & -j) {
                tree[i - 1][j - 1] += v;
            }
        }
    }

    // query rectangle [(0, 0), (x, y)]
    T query(int x, int y) {
        T total = {};
        for (int i = x + 1; i > 0; i -= i & -i) {
            for (int j = y + 1; j > 0; j -= j & -j) {
                total += tree[i - 1][j - 1];
            }
        }
        return total;
    }
    
    // query rectangle [(x1, y1), (x2, y2)]
    T query(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x1 - 1, y2)
               - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};
