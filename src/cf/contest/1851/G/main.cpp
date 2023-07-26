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

struct dsu {
    int n, q;
    vector<int> e;
    vector<bool> ans;
    vector<int> beg;
    vector<pair<pair<int, int>, int>> v;
    vector<set<int>> qu;

    dsu(int _n, int _q, vector<int> t, vector<pair<pair<int, int>, int>> z) : n(_n), q(_q) {
        e.resize(n, -1);
        qu.resize(n);
        ans.resize(q);
        for (int i = 0; i < q; ++i) {
            if (z[i].first.first == z[i].first.second) {
                ans[i] = true;
                continue;
            }
            qu[z[i].first.first].insert(i);
            qu[z[i].first.second].insert(i);
        }
        beg = t;
        v = z;
    }

    int get(int x) {
        return e[x] < 0 ? x : (e[x] = get(e[x]));
    }

    int size(int x) {
        return -e[get(x)];
    }

    bool unite(int x, int y, int mx) {
        x = get(x);
        y = get(y);
        if (x == y) return false;
        if (qu[x].size() < qu[y].size()) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        for (int z : qu[y]) {
            auto it = qu[x].find(z);
            if (it != qu[x].end()) {
                qu[x].erase(it);
                ans[z] = mx - beg[v[z].first.first] <= v[z].second;
            } else qu[x].insert(z);
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        int n, m; cin >> n >> m;
        vector<int> a(n); for (auto& x : a) cin >> x;
        vector<tuple<int, int, int>> edges;
        while (m--) {
            int x, y; cin >> x >> y;
            edges.push_back({max(a[y - 1], a[x - 1]), x - 1, y - 1});
        }
        int q; cin >> q;
        vector<pair<pair<int, int>, int>> z(q);
        for (auto& [x, t] : z) cin >> x.first >> x.second >> t, --x.first, --x.second;
        dsu d(n, q, a, z);
        sort(edges.begin(), edges.end());
        for (auto& [c, x, y] : edges) {
            d.unite(x, y, c);
        }
        for (bool x : d.ans) cout << (x ? "YES" : "NO") << '\n';
    }
}
