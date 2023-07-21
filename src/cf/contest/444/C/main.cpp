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
        if (ll <= l && r <= rr && tree[x].color != -1) { tree[x].apply(l, r, v...); return; }
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
        long long add = 0;
        int color = -1;
 
        // apply value to range [l, r] when updating
        void apply(int l, int r, int nc, long long a = 0, bool first = true) {
            if (first) {
                color = nc;
                return;
            }
            if (a > 0) {
                val += (long long) (r - l + 1) * a;
                add += a;
                color = nc;
            } else {
                val += (long long) (r - l + 1) * abs(color - nc);
                add += abs(color - nc);
                color = nc;
            }
        }
    };
    
    // unite two nodes into one
    node unite(const node& a, const node& b) {
        node res;
        res.val = a.val + b.val;
        if (a.color == b.color) res.color = a.color;
        return res;
    }
 
    // push lazy propogation of parent node into child nodes
    inline void push(int x, int l, int r) {
        int m = (l + r) >> 1;
        int y = x + ((m - l + 1) << 1);
        // push from x into (x + 1) and y
        if (tree[x].color != -1) {
            tree[x + 1].apply(l, m, tree[x].color, tree[x].add, false);
            tree[y].apply(m + 1, r, tree[x].color, tree[x].add, false);
            tree[x].add = 0;
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
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    segtree st(a);
    while (q--) {
        int t, l, r, x; cin >> t >> l >> r, --l, --r;
        if (t == 1) cin >> x, st.update(l, r, x, 0, false);
        else cout << st.query(l, r).val << '\n';
    }
}
