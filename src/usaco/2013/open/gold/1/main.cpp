#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

void set_io(string s) {
#ifndef LOCAL
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
#endif
}

const int inf = (int) 1e9 + 10;

/**
 * Segment Tree
 * Description:
 *    1D point update and range query where unite is any associatve operation.
 * Time Complexity:
 *     Update: O(log n)
 *     Query: O(log n)
 * Verification: https://judge.yosupo.jp/submission/141445
 */

struct segtree {
    int n;
    struct node;
    vector<node> tree;

    segtree(int _n) : n(_n) {
        tree.resize(2 * n);
    }

    void pull(int p) {
        tree[p] = unite(tree[2 * p], tree[2 * p + 1]);
    }

    // update point i
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
        int val = -inf;

        // apply value to node when updating
        void apply(int v) {
            val = v;
        }
    };
    
    // unite two nodes into one
    node unite(const node& a, const node& b) {
        node res;
        res.val = max(a.val, b.val);
        return res;
    }
};

int main() {
    set_io("photo");
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<pair<int, int>> a(m); for (auto& [x, y] : a) cin >> x >> y;
    vector<int> mn(n + 1, inf), mx(n + 1, 0);
    for (auto& [l, r] : a) mn[r] = min(mn[r], l), mx[r] = max(mx[r], l);
    for (int i = 1; i <= n; ++i) mx[i] = max(mx[i], mx[i - 1]);
    for (int i = n - 1; i >= 0; --i) mn[i] = min(mn[i], mn[i + 1]);
    segtree st(n + 1);
    int ans = -inf;
    st.update(0, 0);
    for (int i = 1; i <= n; ++i) {
        int v = st.query(mx[i - 1], min(mn[i] - 1, i)).val;
        if (v >= 0) {
            st.update(i, 1 + v);
            if (mx[i] == mx[n]) ans = max(ans, 1 + v);
        }
    }
    cout << (ans == -inf ? -1 : ans) << '\n';
}
