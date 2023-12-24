#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

/**
 * Fenwick Tree
 * Description:
 *    1D point increment/update and rectangle query where the operation is 
 *    invertible (addition, multiplication). Can also be range update and 
 *    point query.
 * Time Complexity:
 *    Update: O(log n)
 *    Query: O(log n)
 * Verification: https://judge.yosupo.jp/submission/173798
 */

template <typename T>
struct fenwick {
    int n;
    vector<T> tree;

    fenwick(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    void init(int _n) {
        n = _n;
        tree.assign(n, {});
    }

    // increment point x by v
    void add(int x, T v) {
        for (++x; x <= n; x += x & -x) {
            tree[x - 1] += v;
        }
    }

    // query range [0, x]
    T query(int x) {
        T total = 0;
        for (++x; x > 0; x -= x & -x) {
            total += tree[x - 1];
        }
        return total;
    }
    
    // query range [l, r]
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int> a(n); for (auto& x : a) cin >> x;
    fenwick<long long> fw(n); for (int i = 0; i < n; ++i) fw.add(i, a[i]);
    vector<vector<tuple<int, int, int, int>>> s(1);
    for (int i = 0; i < q; ++i) {
        int t, k, l = -1, r = -1; cin >> t >> k, --k;
        if (t != 3) { cin >> l >> r, --l; if (t == 2) --r; }
        else l = (int) s.size();
        s[k].push_back({t, l, r, i});
        if (t == 3) s.push_back({});
    }
    vector<long long> ans(q, -1);
    function<void(int)> solve = [&](int v) {
        for (auto& [t, l, r, i] : s[v]) {
            if (t == 1) {
                fw.add(l, r - a[l]);
                int z = r;
                r = a[l];
                a[l] = z;
            }
            if (t == 2) ans[i] = fw.query(l, r);
            if (t == 3) solve(l);
        }
        reverse(s[v].begin(), s[v].end());
        for (auto& [t, l, r, i] : s[v]) {
            if (t == 1) {
                fw.add(l, r - a[l]);
                int z = r;
                r = a[l];
                a[l] = z;
            }
        }
    };
    solve(0);
    for (int i = 0; i < q; ++i) if (ans[i] != -1) cout << ans[i] << '\n';
}
