#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

template <typename T>
using gpq = priority_queue<T, vector<T>, greater<T>>;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    while (m--) {
        int x, y, w; cin >> x >> y >> w;
        adj[x - 1].push_back({y - 1, w});
        adj[y - 1].push_back({x - 1, w});
    }
    gpq<tuple<long long, int, int, int>> pq;
    vector<vector<vector<long long>>> dp(n, vector<vector<long long>>(2, vector<long long>(2, -1)));
    pq.push({0, 0, 0, 0});
    while (!pq.empty()) {
        auto [d, v, mx, mn] = pq.top(); pq.pop();
        if (dp[v][mx][mn] != -1) continue;
        dp[v][mx][mn] = d;
        for (auto [nv, nd] : adj[v]) {
            for (int nmx = mx; nmx < 2; ++nmx) {
                for (int nmn = mn; nmn < 2; ++nmn) {
                    if (dp[nv][nmx][nmn] != -1) continue;
                    long long z = d + nd;
                    if (nmx != mx) z -= nd;
                    if (nmn != mn) z += nd;
                    pq.push({z, nv, nmx, nmn});
                }
            }
        }
    }
    for (int i = 1; i < n; ++i) cout << dp[i][1][1] << " \n"[i == n - 1];
}
