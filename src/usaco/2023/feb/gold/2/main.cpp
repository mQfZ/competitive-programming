#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    const long long inf = (long long) 2e18 + 10;
    int n, t; cin >> n >> t;
    vector<int> cost(n);
    vector<vector<int>> adj(n);
    for (int i = 1; i < n; ++i) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(i);
        cost[i] = y;
    }
    vector<int> sz(n), max_depth(n);
    vector<long long> sum(n);
    vector<vector<long long>> dp(n, vector<long long>(2));
    for (int v = n - 1; v >= 0; --v) {
        ++sz[v];
        sum[v] += cost[v];
        max_depth[v] = 0;
        for (int nv : adj[v]) {
            sz[v] += sz[nv];
            sum[v] += sum[nv];
            max_depth[v] = max(max_depth[v], max_depth[nv] + 1);
        }
        vector<int> can = adj[v];
        int s = (int) can.size();
        if (s == 0) continue;
        sort(can.begin(), can.end(), [&](int x, int y) {
            return sum[x] * sz[y] > sum[y] * sz[x];
        });
        int tt = 0;
        vector<long long> psum(s + 1), psz(s + 1);
        for (int j = 0; j < s; ++j) {
            int nv = can[j];
            ++tt;
            psum[j + 1] = psum[j] + sum[nv];
            psz[j + 1] = psz[j] + sz[nv];
            dp[v][0] += tt * sum[nv];
            dp[v][0] += dp[nv][0];
            tt += 2 * sz[nv] - 2;
            ++tt;
        }
        dp[v][1] = inf;
        for (int j = 0; j < s; ++j) {
            int nv = can[j];
            if (max_depth[nv] == max_depth[v] - 1) {
                dp[v][1] = min(dp[v][1], dp[v][0] - (psum[s] - psum[j + 1]) * 2 * sz[nv]
                                         - dp[nv][0] + dp[nv][1] + (psz[s] - psz[j + 1]) * 2 * sum[nv]);
            }            
        }
    }
    cout << 2 * n - 2 - (t ? max_depth[0] : 0) << " " << dp[0][t] << '\n';
}
