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
 * Verification: https://judge.yosupo.jp/submission/141443
 */

template <typename T>
struct fenwick {
    int n;
    vector<T> tree;

    fenwick(int _n) : n(_n) {
        tree.resize(n);
    }

    // update point x
    void update(int x, T v) {
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
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i], a[i] = i + 1 - a[i];
    vector<vector<pair<int, int>>> queries(n);
    for (int i = 0; i < q; ++i) {
        int x, y; cin >> x >> y;
        queries[n - 1 - y].push_back({x, i});
    }
    fenwick<int> fw(n);
    vector<int> ans(q);
    for (int i = 0; i < n; ++i) {
        if (a[i] >= 0) {
            int l = 0, r = i, res = -1;
            while (l <= r) {
                int m = (l + r) / 2;
                if (fw.query(m) >= a[i]) l = m + 1, res = m;
                else r = m - 1;
            }
            fw.update(0, 1);
            fw.update(res + 1, -1);
        }
        for (auto [x, idx] : queries[i]) ans[idx] = fw.query(x);
    }
    for (int i = 0; i < q; ++i) cout << ans[i] << '\n';
}
