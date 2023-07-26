#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        int n, k; cin >> n >> k;
        vector<int> c(n); for (auto& x : c) cin >> x;
        queue<int> fin;
        while (k--) { int x; cin >> x; c[x - 1] = 0; fin.push(x - 1); }
        vector<int> sz(n);
        vector<vector<int>> adj(n), invadj(n);
        for (int i = 0; i < n; ++i) {
            int z; cin >> z;
            vector<int> v(z); for (auto& x : v) cin >> x, --x;
            if (c[i] == 0) continue;
            if (z == 0) fin.push(i);
            else {
                sz[i] = z;
                for (int q = 0; q < z; ++q) adj[v[q]].push_back(i), invadj[i].push_back(v[q]);
            }
        }
        dbg(adj, invadj);
        while (!fin.empty()) {
            int z = fin.front(); fin.pop();
            long long s = 0;
            for (auto& x : adj[z]) { --sz[x]; if (sz[x] == 0) fin.push(x); }
            for (auto& x : invadj[z]) { s += c[x]; }
            if (invadj[z].size() == 0) continue;
            if (s < c[z]) c[z] = (int) s;
        }
        for (int i = 0; i < n; ++i) cout << c[i] << " \n"[i == n - 1];
    }
}
