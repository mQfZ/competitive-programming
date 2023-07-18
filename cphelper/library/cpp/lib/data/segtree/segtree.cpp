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
 * Verification: https://judge.yosupo.jp/submission/141445
 */

struct SegTree {
    int n;
    struct node;
    vector<node> tree;

    SegTree(int _n) : n(_n) {
        tree.resize(2 * n);
    }

    void pull(int p) {
        tree[p] = unite(tree[2 * p], tree[2 * p + 1]);
    }

    // update a[i]
    template <typename... Ts>
    void update(int i, Ts... val) {
        tree[i += n].apply(val...);
        for (i /= 2; i > 0; i /= 2) pull(i);
    }

    // query [l, r]
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
        int val = 0;

        // apply value to node when updating
        void apply(int v) {
            val += v;
        }
    };
    
    node unite(node a, node b) {
        node res;
        res.val = a.val + b.val;
        return res;
    }
};
