#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

/**
 * Lazy Segment Tree
 * Description:
 *    1D range update and range query where unite is any associatve operation.
 *    Uses lazy propogation to range update and euler tour traversal to reduce 
 *    memory from 4 * n to 2 * n - 1.
 * Time Complexity:
 *     Build: O(n)
 *     Update: O(log n)
 *     Query: O(log n)
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/cses/1735/main.cpp
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

    segtree(int _n) : n(_n) {
        assert(n > 0);
        tree.resize(2 * n - 1);
        build(0, 0, n - 1);
    }

    template <typename T>
    segtree(const vector<T>& v) : n((int) v.size()) {
        assert(n > 0);
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, v);
    }

    // update [l, r]
    template <typename... Ts>
    void update(int l, int r, const Ts&... v) {
        assert(0 <= l && l <= r && r <= n - 1);
        return update(0, 0, n - 1, l, r, v...);
    }

    // query [l, r]
    node query(int l, int r) {
        assert(0 <= l && l <= r && r <= n - 1);
        return query(0, 0, n - 1, l, r);
    }

    struct node {
        // make sure to set default value
        long long val = 0;
        long long inc = 0;
        long long st = -1;

        // apply value to range [l, r] when updating
        void apply(int l, int r, long long i, long long s = -1) {
            if (s != -1) st = s, inc = 0, val = (r - l + 1) * s;
            inc += i; val += (r - l + 1) * i;
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
        // push from x into (x + 1) and y
        tree[x + 1].apply(l, m, tree[x].inc, tree[x].st);
        tree[y].apply(m + 1, r, tree[x].inc, tree[x].st);
        tree[x].inc = 0;
        tree[x].st = -1;
    }

    // pull two child nodes into parent node
    inline void pull(int x, int y) {
        tree[x] = unite(tree[x + 1], tree[y]);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int> a(n); for (auto& x : a) cin >> x;
    segtree st(a);
    while (q--) {
        int t, l, r, x = 0, y = -1; cin >> t >> l >> r, --l, --r;
        if (t == 1) cin >> x;
        if (t == 2) cin >> y;
        if (t == 3) cout << st.query(l, r).val << '\n';
        else st.update(l, r, x, y);
    }
}
