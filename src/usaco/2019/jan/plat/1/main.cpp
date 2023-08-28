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
        int mn = (int) 1e9 + 10;

        // apply value to node when updating
        void apply(int v) {
            mn = v;
        }
    };
    
    // unite two nodes into one
    node unite(const node& a, const node& b) {
        node res;
        res.mn = min(a.mn, b.mn);
        return res;
    }
};

int main() {
    set_io("redistricting");
    ios::sync_with_stdio(0); cin.tie(0);
    const int inf = (int) 1e9 + 10;
    const int mx = (int) 3e5 + 10;
    int n, k; string s; cin >> n >> k >> s;
    vector<int> dx(n + 1);
    vector<set<pair<int, int>>> p(mx);
    segtree dp(n + 1), st(mx);
    for (int i = 1; i <= n; ++i) dx[i] = dx[i - 1] + (s[i - 1] == 'H' ? 1 : -1);
    int ss = -*min_element(dx.begin(), dx.end());
    dp.update(0, 0);
    p[ss + 0].insert({0, 0});
    st.update(ss + 0, 0);
    for (int i = 1; i <= n; ++i) {
        if (i - k >= 0) {
            p[ss + dx[i - k]].erase({dp.query(i - k, i - k).mn, i - k});
            st.update(ss + dx[i - k], p[ss + dx[i - k]].size() > 0 ? p[ss + dx[i - k]].begin()->first : inf);
        }
        dp.update(i, dp.query(max(0, i - k), i - 1).mn + 1);
        int v = st.query(0, ss + dx[i] - 1).mn;
        if (v != inf) dp.update(i, min(dp.query(i, i).mn, v));
        p[ss + dx[i]].insert({dp.query(i, i).mn, i});
        st.update(ss + dx[i], p[ss + dx[i]].begin()->first);
    }
    cout << dp.query(n, n).mn << '\n';
}
