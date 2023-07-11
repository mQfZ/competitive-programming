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
    const int C = 4;
    vector<int> sz(C); for (auto& x : sz) cin >> x;
    vector<vector<int>> a(C);
    for (int i = 0; i < C; ++i) {
        a[i].resize(sz[i]);
        for (auto& x : a[i]) cin >> x;
    }
    vector<vector<vector<int>>> cn(C);
    for (int i = 0; i < C; ++i) {
        cn[i].resize(sz[i]);
        if (i == 0) continue;
        int t; cin >> t;
        while (t--) {
            int x, y; cin >> x >> y;
            cn[i][y - 1].push_back(x - 1);
        }
        for (auto& x : cn[i]) sort(x.begin(), x.end());
    }
    vector<pair<int, int>> dp = {{0, 0}};
    for (int i = 0; i < C; ++i) {
        vector<pair<int, int>> ndp;
        for (int j = 0; j < sz[i]; ++j) {
            for (auto [d, k] : dp) {
                auto it = lower_bound(cn[i][j].begin(), cn[i][j].end(), k);
                if (it == cn[i][j].end() || *it != k) {
                    ndp.push_back({d + a[i][j], j});
                    break;
                }
            }
        }
        sort(ndp.begin(), ndp.end());
        dp = ndp;
    }
    cout << (dp.size() == 0 ? -1 : dp[0].first) << '\n';
}
