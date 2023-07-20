#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

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
        pair<int, int> p = {(int) 1e9, -1};

        // apply value to node when updating
        void apply(int v, int c) {
            p = {v, c};
        }
    };
    
    node unite(node a, node b) {
        node res;
        res.p = min(a.p, b.p);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    const int mx = (int) 5e5 + 10;
    int n; cin >> n;
    vector<int> a(n); for (auto& x : a) cin >> x;
    vector<int> prev(mx, -1);
    SegTree st(n);
    int q; cin >> q;
    vector<vector<pair<int, int>>> qr(n);
    for (int i = 0; i < q; ++i) {
        int l, r; cin >> l >> r, --l, --r;
        qr[r].push_back({l, i});
    }
    vector<int> ans(q);
    for (int i = 0; i < n; ++i) {
        st.update(i, prev[a[i]], a[i]);
        if (prev[a[i]] != -1) st.update(prev[a[i]], (int) 1e9 + 10, -1);
        prev[a[i]] = i;
        for (auto [l, j] : qr[i]) {
            auto v = st.query(l, i);
            ans[j] = v.p.first < l ? v.p.second : 0;
        }
    }
    for (auto& x : ans) cout << x << '\n';
}
