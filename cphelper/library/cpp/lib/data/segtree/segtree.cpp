#include <bits/stdc++.h>
using namespace std;
#pragma once

/**
 * Segment Tree
 * Description:
 *    1D point update and range query where unite is any associatve operation.
 * Time Complexity:
 *     Update: O(log n)
 *     Query: O(log n)
 * Verification: https://judge.yosupo.jp/submission/173605
 */

struct segtree {
    int n;
    struct node;
    vector<node> tree;

    segtree(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    void init(int _n) {
        n = _n;
        tree.assign(2 * n, {});
    }

    void pull(int p) {
        tree[p] = unite(tree[2 * p], tree[2 * p + 1]);
    }

    // update point x
    template <typename... Ts>
    void update(int x, const Ts&... val) {
        tree[x += n].apply(val...);
        for (x /= 2; x > 0; x /= 2) pull(x);
    }

    // query range [l, r]
    node query(int l, int r) {
        node ra, rb;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) ra = unite(ra, tree[l++]);
            if (r & 1) rb = unite(tree[--r], rb);
        }
        return unite(ra, rb);
    }

    struct node {
        // make sure to set default value
        long long val = 0;

        // apply value to node when updating
        void apply(long long v) {
            val += v;
        }
    };
    
    // unite two nodes into one
    node unite(const node& a, const node& b) {
        node res;
        res.val = a.val + b.val;
        return res;
    }
};
