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
 * Verification: https://judge.yosupo.jp/submission/180944
 */

template <typename T>
class fenwick {
private:
    int n;
    vector<T> tree;

public:
    fenwick(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    void init(int _n) {
        n = _n;
        tree.assign(n + 1, {});
    }

    // increment point x by v
    void update(int x, T v) {
        for (++x; x <= n; x += x & -x) {
            tree[x] += v;
        }
    }

    // query range [0, x]
    T query(int x) {
        T total = 0;
        for (++x; x > 0; x -= x & -x) {
            total += tree[x];
        }
        return total;
    }
    
    // query range [l, r]
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    set_io("mincross");
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n); for (auto& x : a) cin >> x, --x;
    vector<int> b(n); for (auto& x : b) cin >> x, --x;
    vector<int> pa(n); for (int i = 0; i < n; ++i) pa[a[i]] = i;
    vector<int> pb(n); for (int i = 0; i < n; ++i) pb[b[i]] = i;
    vector<pair<int, int>> range(n);
    for (int i = 0; i < n; ++i) {
        range[a[i]].first = i;
        range[b[i]].second = 2 * n - i - 1;
    }
    sort(range.begin(), range.end());
    fenwick<int> fw(2 * n);
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += fw.query(range[i].first, range[i].second);
        fw.update(range[i].second, 1);
    }
    long long lhs = ans, rhs = ans;
    for (int i = 0; i < n; ++i) {
        lhs += n - 1 - 2 * pa[b[i]];
        rhs += n - 1 - 2 * pb[a[i]];
        ans = min(ans, min(lhs, rhs));
    }
    cout << ans << '\n';
}
