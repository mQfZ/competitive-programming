#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
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
    int n; cin >> n;
    vector<int> a(n); for (auto& x : a) cin >> x;
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
        adj[y - 1].push_back(x - 1);
    }
    DSU d(n);
    vector<int> can(n);
    iota(can.begin(), can.end(), 0);
    sort(can.begin(), can.end(), [&](int x, int y) { return a[x] < a[y]; });
    vector<bool> added(n);
    long long max_ans = 0;
    for (int v : can) {
        long long total = 0, sq = 0;
        for (int nv : adj[v]) {
            if (!added[nv]) continue;
            total += d.size(nv);
            sq += (long long) d.size(nv) * d.size(nv);
            d.unite(v, nv);
        }
        added[v] = true;
        max_ans += ((total * total - sq) / 2 + total + 1) * a[v];
    }
    d = DSU(n);
    sort(can.begin(), can.end(), [&](int x, int y) { return a[x] > a[y]; });
    added = vector<bool>(n);
    long long min_ans = 0;
    for (int v : can) {
        long long total = 0, sq = 0;
        for (int nv : adj[v]) {
            if (!added[nv]) continue;
            total += d.size(nv);
            sq += (long long) d.size(nv) * d.size(nv);
            d.unite(v, nv);
        }
        added[v] = true;
        min_ans += ((total * total - sq) / 2 + total + 1) * a[v];
    }
    cout << max_ans - min_ans << '\n';
}
