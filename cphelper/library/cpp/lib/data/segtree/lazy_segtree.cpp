#include <bits/stdc++.h>
using namespace std;
#pragma once

/**
 * Lazy Segment Tree
 * Description:
 *    1D range update and range query where unite is any associatve operation. 
 *    Uses lazy propogation to range update and euler tour traversal to reduce 
 *    memory from 4n to 2n - 1.
 * Time Complexity:
 *     Build: O(n)
 *     Update: O(log n)
 *     Query: O(log n)
 *     Find First/Last: O(log n)
 * Verification:
 *     https://github.com/mQfZ/competitive-programming/blob/master/src/cses/1735/main.cpp
 *     https://github.com/mQfZ/competitive-programming/blob/master/src/cses/1143/main.cpp
 */

struct segtree {
    int n;
    struct node;
    vector<node> tree;

    void build(int x, int l, int r) {
        if (l == r) return;
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        build(x + 1, l, m);
        build(y, m + 1, r);
        pull(x, y);
    }

    template <typename T>
    void build(int x, int l, int r, const vector<T>& v) {
        if (l == r) { tree[x].apply(l, r, v[l]); return; }
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        build(x + 1, l, m, v);
        build(y, m + 1, r, v);
        pull(x, y);
    }

    template <typename... Ts>
    void update(int x, int l, int r, int ll, int rr, const Ts&... v) {
        if (ll <= l && r <= rr) { tree[x].apply(l, r, v...); return; }
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        push(x, l, r);
        if (ll <= m) update(x + 1, l, m, ll, rr, v...);
        if (rr > m) update(y, m + 1, r, ll, rr, v...);
        pull(x, y);
    }

    node query(int x, int l, int r, int ll, int rr) {
        if (ll <= l && r <= rr) return tree[x];
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        push(x, l, r);
        node res = {};
        if (rr <= m) res = query(x + 1, l, m, ll, rr);
        else if (ll > m) res = query(y, m + 1, r, ll, rr);
        else res = unite(query(x + 1, l, m, ll, rr), query(y, m + 1, r, ll, rr));
        pull(x, y);
        return res;
    }

    int find_first_knowingly(int x, int l, int r, const function<bool(const node&)>& f) {
        if (l == r) return l;
        push(x, l, r);
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        int res;
        if (f(tree[x + 1])) res = find_first_knowingly(x + 1, l, m, f);
        else res = find_first_knowingly(y, m + 1, r, f);
        pull(x, y);
        return res;
    }

    int find_first(int x, int l, int r, int ll, int rr, const function<bool(const node&)>& f) {
        if (ll <= l && r <= rr) {
            if (!f(tree[x])) return -1;
            return find_first_knowingly(x, l, r, f);
        }
        push(x, l, r);
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        int res = -1;
        if (ll <= m) res = find_first(x + 1, l, m, ll, rr, f);
        if (rr > m && res == -1) res = find_first(y, m + 1, r, ll, rr, f);
        pull(x, y);
        return res;
    }

    int find_last_knowingly(int x, int l, int r, const function<bool(const node&)>& f) {
        if (l == r) return l;
        push(x, l, r);
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        int res;
        if (f(tree[y])) res = find_last_knowingly(y, m + 1, r, f);
        else res = find_last_knowingly(x + 1, l, m, f);
        pull(x, y);
        return res;
    }

    int find_last(int x, int l, int r, int ll, int rr, const function<bool(const node&)>& f) {
        if (ll <= l && r <= rr) {
            if (!f(tree[x])) return -1;
            return find_last_knowingly(x, l, r, f);
        }
        push(x, l, r);
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        int res = -1;
        if (rr > m) res = find_last(y, m + 1, r, ll, rr, f);
        if (ll <= m && res == -1) res = find_last(x + 1, l, m, ll, rr, f);
        pull(x, y);
        return res;
    }

    segtree(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    template <typename T>
    segtree(const vector<T>& v) {
        init(v);
    }

    void init(int _n) {
        n = _n;
        tree.assign(2 * n - 1, {});
        build(0, 0, n - 1);
    }

    template <typename T>
    void init(const vector<T>& v) {
        n = (int) v.size();
        tree.assign(2 * n - 1, {});
        build(0, 0, n - 1, v);
    }

    // update range [l, r]
    template <typename... Ts>
    void update(int l, int r, const Ts&... v) {
        assert(0 <= l && l <= r && r <= n - 1);
        return update(0, 0, n - 1, l, r, v...);
    }

    // query range [l, r]
    node query(int l, int r) {
        assert(0 <= l && l <= r && r <= n - 1);
        return query(0, 0, n - 1, l, r);
    }

    // finds first index i where f(tree[i]) is true in range [l, r], else -1
    // each parent node must return true iff at least one child node returns true
    int find_first(int l, int r, const function<bool(const node&)>& f) {
        assert(0 <= l && l <= r && r <= n - 1);
        return find_first(0, 0, n - 1, l, r, f);
    }

    // finds last index i where f(tree[i]) is true in range [l, r], else -1
    // each parent node must return true iff at least one child node returns true
    int find_last(int l, int r, const function<bool(const node&)>& f) {
        assert(0 <= l && l <= r && r <= n - 1);
        return find_last(0, 0, n - 1, l, r, f);
    }

    struct node {
        // make sure to set default value
        long long val = 0;
        long long add = 0;

        // apply value to range [l, r] when updating
        void apply(int l, int r, long long v) {
            val += (long long) (r - l + 1) * v;
            add += v;
        }
    };
    
    // unite two nodes into one
    node unite(const node& a, const node& b) {
        node res;
        res.val = a.val + b.val;
        return res;
    }

    // push lazy propogation of parent node into child nodes
    inline void push(int x, int l, int r) {
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        // push from x into (x + 1) with range [l, m] and y with range [m + 1, r]
        tree[x + 1].apply(l, m, tree[x].add);
        tree[y].apply(m + 1, r, tree[x].add);
        tree[x].add = 0;
    }

    // pull child nodes into parent node
    inline void pull(int x, int y) {
        tree[x] = unite(tree[x + 1], tree[y]);
    }
};
