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
        int ans = 0;
        int revans = 0;
        int lc = 0;
        int rc = 0;
        bool flip = false;

        // apply value to range [l, r] when updating
        void apply(int l, int r, bool f) {
            if (ans == 0) ans = revans = lc = r - l + 1;
            if (f) flip ^= f, swap(lc, rc), swap(ans, revans);
        }
    };
    
    // unite two nodes into one
    node unite(const node& a, const node& b) {
        node res;
        res.ans = max(a.ans + b.rc, a.lc + b.ans);
        res.revans = max(a.revans + b.lc, a.rc + b.revans);
        res.lc = a.lc + b.lc;
        res.rc = a.rc + b.rc;
        return res;
    }

    // push lazy propogation of parent node into child nodes
    inline void push(int x, int l, int r) {
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        // push from x into (x + 1) and y
        if (tree[x].flip) {
            tree[x + 1].apply(l, m, tree[x].flip);
            tree[y].apply(m + 1, r, tree[x].flip);
            tree[x].flip = false;
        }
    }

    // pull two child nodes into parent node
    inline void pull(int x, int y) {
        tree[x] = unite(tree[x + 1], tree[y]);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;
    vector<bool> a(n);
    string s; cin >> s; for (int i = 0; i < n; ++i) a[i] = s[i] == '7';
    segtree st(a);
    while (q--) {
        string p; int l, r; cin >> p;
        if (p[0] == 's') cin >> l >> r, --l, --r, st.update(l, r, true);
        else cout << st.query(0, n - 1).ans << '\n';
    }
}
