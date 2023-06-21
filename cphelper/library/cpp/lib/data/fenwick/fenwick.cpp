#include <bits/stdc++.h>
using namespace std;
#pragma once

/**
 * Fenwick Tree
 * Description:
 *    Computes partial sums a[l] + a[l + 1] + ... + a[r], and increments
 *    single element a[x]
 * Time Complexity:
 *    Update: O(log n)
 *    Query: O(log n)
 * Verification: https://judge.yosupo.jp/submission/141443
 */

template <typename T>
struct Fenwick {
    int n;
    vector<T> tree;

    Fenwick(int _n) : n(_n) {
        tree.resize(n);
    }

    // increment a[x]
    void update(int x, T v) {
        for (++x; x <= n; x += x & -x) {
            tree[x - 1] += v;
        }
    }

    // query [0, x]
    T query(int x) {
        T total = 0;
        for (++x; x > 0; x -= x & -x) {
            total += tree[x - 1];
        }
        return total;
    }
    
    // query [l, r]
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
