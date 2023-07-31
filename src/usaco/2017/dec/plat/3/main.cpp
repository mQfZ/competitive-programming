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
        long long val = 0;

        // apply value to node when updating
        void apply(int v) {
            val += v;
        }
    };
    
    // unite two nodes into one
    node unite(const node& a, const node& b) {
        node res;
        res.val = a.val + b.val;
        return res;
    }
};

int main() {
    set_io("greedy");
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n); for (auto& x : a) cin >> x;
    vector<vector<int>> c(n); for (int i = 0; i < n; ++i) c[a[i]].push_back(i);
    auto st = segtree(n);
    auto solve = [&](int k) -> int {
        for (auto& x : c[k]) st.update(x, 1);
        int l = 0, r = n;
        while (l < r) {
            int m = (l + r) / 2;
            if (st.query(0, m).val < n - k) l = m + 1;
            else r = m;
        }
        return l;
    };
    int ans = (int) 1e9;
    for (int i = n - 1; i >= 0; --i) {
        ans = min(ans, solve(i));
    }
    cout << n - 1 - ans << '\n';
}
