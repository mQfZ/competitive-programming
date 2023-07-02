#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

/**
 * Disjoint Set Union
 * Description:
 *    Disjoint Set Union with path compression and union by size. Add edges 
 *    and test connectivity.
 * Time Complexity: O(alpha(N))
 * Verification: https://judge.yosupo.jp/submission/141446
 */

struct DSU {
    int n;
    vector<int> e;

    DSU(int _n) : n(_n) {
        e.resize(n, -1);
    }

    int get(int x) {
        return e[x] < 0 ? x : (e[x] = get(e[x]));
    }

    int size(int x) {
        return -e[get(x)];
    }

    bool unite(int x, int y) {
        x = get(x);
        y = get(y);
        if (x == y) return false;
        if (-e[x] < -e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> deg(n);
    while (m--) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
        ++deg[x - 1], ++deg[y - 1];
    }
    set<pair<int, int>> s;
    for (int i = 0; i < n; ++i) s.insert({deg[i], i});
    vector<pair<int, int>> order(n);
    bitset<(int) 1e5 + 10> added;
    added.set();
    for (int i = 0; i < n; ++i) {
        auto [d, v] = *s.begin(); s.erase(s.begin());
        order[n - i - 1] = {d, v};
        added[v] = false;
        for (int nv : adj[v]) {
            if (added[nv]) {
                s.erase({deg[nv], nv});
                s.insert({--deg[nv], nv});
            }
        }
    }
    DSU ds(n);
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        auto [d, v] = order[i];
        added[v] = true;
        for (int nv : adj[v]) {
            if (added[nv]) {
                ds.unite(v, nv);
            }
        }
        ans = max(ans, (long long) ds.size(v) * d);
    }
    cout << ans << '\n';
}
