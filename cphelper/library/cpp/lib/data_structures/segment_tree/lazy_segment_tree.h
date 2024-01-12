#include <bits/stdc++.h>
using namespace std;
#pragma once

#include <lib/miscellaneous/highest_bit.h>

/**
 * Lazy Segment Tree
 * Description:
 *    1D range update and range query where unite is any associatve operation. 
 *    Uses lazy propogation to range update. Node class must have default
 *    value(s) set, an apply lazy propgation method, and a static unite method.
 *    Update class must have default value(s) and an extend method.
 * Time Complexity:
 *     Build: O(n)
 *     Update: O(log n)
 *     Query: O(log n)
 * Verification: https://judge.yosupo.jp/submission/182989
 */

template <typename N, typename U>
class lazy_segtree {
protected:
    int n, height;
    vector<N> tree;
    vector<U> lazy;

public:
    lazy_segtree(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    template <typename T>
    lazy_segtree(const vector<T>& v) {
        init(v);
    }

    void init(int _n) {
        init(vector<N>(_n, N {}));
    }

    void init(const vector<N>& v) {
        n = (int) v.size();
        height = most_significant_bit(2 * n - 1) + 1;
        tree.assign(2 * n, {});
        lazy.assign(n, {});
        build(v);
    }

protected:
    inline void apply_lazy(int p, const U& u) {
        tree[p].apply_update(u);
        if (p < n) lazy[p].extend(u);
    }

    inline void pull(int p) {
        tree[p] = N::unite(tree[2 * p], tree[2 * p + 1]);
    }

    void pull_single(int x) {
        for (int i = 1; i < height; ++i) pull(x >> i);
    }

    void pull_range(int l, int r) {
        for (int i = 1; i < height; ++i) {
            if (((l >> i) << i) != l) pull(l >> i);
            if (((r >> i) << i) != r) pull((r - 1) >> i);
        }
    }

    inline void push(int p) {
        if (lazy[p] == U()) return;
        apply_lazy(2 * p, lazy[p]);
        apply_lazy(2 * p + 1, lazy[p]);
        lazy[p] = {};
    }

    void push_single(int x) {
        for (int i = height - 1; i > 0; --i) push(x >> i);
    }

    void push_range(int l, int r) {
        for (int i = height - 1; i > 0; --i) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
    }

    void build(const vector<N>& v) {
        for (int i = 0; i < n; ++i) tree[i + n] = v[i];
        for (int i = n - 1; i > 0; --i) pull(i);
    }

public:
    // update point x
    void update(int x, const N& v) {
        assert(0 <= x && x < n);
        x += n;
        push_single(x);
        tree[x] = v;
        pull_single(x);
    }

    // update range [l, r]
    void update(int l, int r, const U& u) {
        assert(0 <= l && l <= r && r < n);
        l += n, r += n + 1;
        push_range(l, r);
        int ll = l, rr = r;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply_lazy(l++, u);
            if (r & 1) apply_lazy(--r, u);
        }
        pull_range(ll, rr);
    }

    // query point x
    N query(int x) {
        assert(0 <= x && x < n);
        x += n;
        push_single(x);
        return tree[x];
    }

    // query range [l, r]
    N query(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        l += n, r += n + 1;
        push_range(l, r);
        N ra = {}, rb = {};
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ra = N::unite(ra, tree[l++]);
            if (r & 1) rb = N::unite(tree[--r], rb);
        }
        return N::unite(ra, rb);
    }
};
