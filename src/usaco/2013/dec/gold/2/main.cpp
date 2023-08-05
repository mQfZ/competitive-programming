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
        long long ans = 0, x11 = 0, x10 = 0, x01 = 0, x00 = 0;

        // apply value to node when updating
        void apply(int v) {
            ans = x11 = v;
            x00 = 0;
            x10 = x01 = (long long) -1e17 - 10;
        }
    };
    
    // unite two nodes into one
    node unite(const node& a, const node& b) {
        node res;
        res.x11 = max({a.x10 + b.x01, a.x10 + b.x11, a.x11 + b.x01});
        res.x01 = max({a.x00 + b.x01, a.x00 + b.x11, a.x01 + b.x01});
        res.x10 = max({a.x10 + b.x00, a.x10 + b.x10, a.x11 + b.x00});
        res.x00 = max({a.x00 + b.x00, a.x00 + b.x10, a.x01 + b.x00});
        res.ans = max({res.x11, res.x01, res.x10, res.x00});
        return res;
    }
};

int main() {
    set_io("optmilk");
    ios::sync_with_stdio(0); cin.tie(0);
    int n, d; cin >> n >> d;
    vector<int> a(n); for (auto& x : a) cin >> x;
    segtree st(n);
    for (int i = 0; i < n; ++i) st.update(i, a[i]);
    long long ans = 0;
    while (d--) {
        int x, y; cin >> x >> y;
        st.update(x - 1, y);
        ans += st.query(0, n - 1).ans;
    }
    cout << ans << '\n';
}
