#include <bits/stdc++.h>
using namespace std;
#pragma once

/**
 * Segment Tree
 * Description:
 *    1D point update and range query where unite is any associatve operation.
 *    Node class must have default value(s) set and a static unite method.
 * Time Complexity:
 *     Build: O(n)
 *     Update: O(log n)
 *     Query: O(log n)
 * Verification: https://judge.yosupo.jp/submission/182986
 */

template <typename N>
class segtree {
protected:
    int n;
    vector<N> tree;

public:
    segtree(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    segtree(const vector<N>& v) {
        init(v);
    }

    void init(int _n) {
        init(vector<N>(_n, N {}));
    }

    void init(const vector<N>& v) {
        n = (int) v.size();
        tree.assign(2 * n, {});
        build(v);
    }

protected:
    inline void pull(int p) {
        tree[p] = N::unite(tree[2 * p], tree[2 * p + 1]);
    }

    inline void pull_single(int x) {
        for (x >>= 1; x > 0; x >>= 1) pull(x);
    }

    void build(const vector<N>& v) {
        for (int i = 0; i < n; ++i) tree[i + n] = v[i];
        for (int i = n - 1; i > 0; --i) pull(i);
    }

public:
    // update point x
    void update(int x, N v) {
        assert(0 <= x && x < n);
        x += n;
        tree[x] = v;
        pull_single(x);
    }

    // query point x
    N query(int x) {
        assert(0 <= x && x < n);
        x += n;
        return tree[x];
    }

    // query range [l, r]
    N query(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        N ra = {}, rb = {};
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ra = N::unite(ra, tree[l++]);
            if (r & 1) rb = N::unite(tree[--r], rb);
        }
        return N::unite(ra, rb);
    }
};
