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
    int n, m, q; cin >> n >> m >> q;
    vector<pair<int, int>> edges(m);
    for (auto& [x, y] : edges) cin >> x >> y, --x, --y;
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; ++i) {
        int x, y; cin >> x >> y;
        queries[i] = {x - 1, y - 1};
    }
    vector<pair<int, int>> ranges(q);
    for (int i = 0; i < q; ++i) ranges[i] = {0, m + 1};
    int mx = m;
    while (mx != 0) {
        mx = 0;
        vector<pair<int, int>> s(q);
        for (int i = 0; i < q; ++i) {
            s[i] = {(ranges[i].first + ranges[i].second) / 2, i};
        }
        DSU d(n);
        sort(s.begin(), s.end());
        int c = 0;
        for (int i = 0; i < q; ++i) {
            while (c < s[i].first && c != m) {
                d.unite(edges[c].first, edges[c].second);
                c++;
            }
            int v = s[i].second;
            if (ranges[v].second - ranges[v].first == 0) continue;
            if (d.get(queries[v].first) == d.get(queries[v].second)) {
                ranges[v].second = s[i].first;
            } else {
                ranges[v].first = s[i].first + 1;
            }
            mx = max(mx, ranges[v].second - ranges[v].first);
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << (ranges[i].first != m + 1 ? ranges[i].first : -1) << '\n';
    }
}
