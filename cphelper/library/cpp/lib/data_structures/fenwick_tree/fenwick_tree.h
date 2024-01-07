#include <bits/stdc++.h>
using namespace std;
#pragma once

/**
 * Fenwick Tree
 * Description:
 *    1D point increment/update and rectangle query where the operation is 
 *    invertible (addition, multiplication). Can also be range update and 
 *    point query.
 * Time Complexity:
 *    Update: O(log n)
 *    Query: O(log n)
 * Verification: https://judge.yosupo.jp/submission/180944
 */

template <typename T>
class fenwick {
private:
    int n;
    vector<T> tree;

public:
    fenwick(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    void init(int _n) {
        n = _n;
        tree.assign(n + 1, {});
    }

    // increment point x by v
    void update(int x, T v) {
        for (++x; x <= n; x += x & -x) {
            tree[x] += v;
        }
    }

    // query range [0, x]
    T query(int x) {
        T total = 0;
        for (++x; x > 0; x -= x & -x) {
            total += tree[x];
        }
        return total;
    }
    
    // query range [l, r]
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
