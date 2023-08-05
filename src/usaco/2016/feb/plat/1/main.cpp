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
    set_io("balancing");
    ios::sync_with_stdio(0); cin.tie(0);
    const int mx = (int) 5e5 + 10;
    int n; cin >> n;
    vector<pair<int, int>> a(n); for (auto& [x, y] : a) cin >> x >> y, x /= 2, y /= 2;
    vector<int> vx, vy;
    for (auto& [x, y] : a) vx.push_back(x), vy.push_back(y);
    sort(vx.begin(), vx.end());
    sort(vy.begin(), vy.end());
    vector<int> mpx(mx), mpy(mx);
    for (int i = 1; i < n; ++i) {
        if (vx[i] != vx[i - 1]) mpx[vx[i]] = mpx[vx[i - 1]] + 1;
        if (vy[i] != vy[i - 1]) mpy[vy[i]] = mpy[vy[i - 1]] + 1;
    }
    vector<vector<int>> dt(mpx[vx[n - 1]] + 1);
    int ny = mpy[vy[n - 1]] + 1;
    fenwick<int> lhs(ny), rhs(ny);
    for (auto& [x, y] : a) dt[mpx[x]].push_back(mpy[y]), rhs.update(mpy[y], 1);
    int ans = mx;
    for (auto& col : dt) {
        int l = 0, r = ny - 1;
        while (l < r) {
            int m = (l + r + 1) / 2;
            if (max(lhs.query(0, m - 1), rhs.query(0, m - 1)) >
                max(lhs.query(m, ny - 1), rhs.query(m, ny - 1))) r = m - 1;
            else l = m;
        }
        ans = min(ans, max(lhs.query(l, ny - 1), rhs.query(l, ny - 1)));
        for (auto& v : col) rhs.update(v, -1), lhs.update(v, 1);
    }
    cout << ans << '\n';
}
