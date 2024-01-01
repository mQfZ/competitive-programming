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

// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template <class Fun>
class y_combinator_result {
    Fun fun_;
  public:
    template <class T>
    explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

    template <class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

int main() {
    set_io("promote");
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i].first, a[i].second = i;
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    vector<int> p(n, -1); for (int i = 1; i < n; ++i) cin >> p[i], --p[i];
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) adj[p[i]].push_back(i);
    vector<int> tin(n), tout(n);
    int time = 0;
    y_combinator([&](auto self, int v) -> void {
        tin[v] = time++;
        for (int nv : adj[v]) self(nv);
        tout[v] = time - 1;
    })(0);
    fenwick<int> fw(n);
    vector<int> ans(n);
    for (auto [_, v] : a) {
        ans[v] = fw.query(tin[v], tout[v]);
        fw.add(tin[v], 1);
    }
    for (auto& x : ans) cout << x << '\n';
}
