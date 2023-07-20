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
        int mn = 0, mx = 0;
        int v = 0;

        // apply value to node when updating
        void apply(char c) {
            v = c == '+' ? 1 : -1;
            mn = mx = v;
        }
    };
    
    node unite(node a, node b) {
        node res;
        res.mn = min(a.mn, a.v + b.mn);
        res.mx = max(a.mx, a.v + b.mx);
        res.v = a.v + b.v;
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        int n, q; cin >> n >> q;
        string s; cin >> s;
        SegTree st(n); for (int i = 0; i < n; ++i) st.update(i, s[i]);
        while (q--) {
            int x, y; cin >> x >> y, --x, --y;
            auto ans = st.unite(st.query(0, x - 1), st.query(y + 1, n - 1));
            cout << ans.mx - ans.mn + 1 << '\n';
        }
    }
}
