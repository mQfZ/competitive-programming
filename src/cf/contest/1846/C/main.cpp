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
        int n, m, h; cin >> n >> m >> h;
        vector<vector<int>> a(n, vector<int>(m));
        for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> a[i][j];
        for (auto& x : a) sort(x.begin(), x.end());
        vector<pair<int, long long>> c(n);
        for (int i = 0; i < n; ++i) {
            long long v = 0;
            for (int j = 0; j < m; ++j) if (v + a[i][j] <= h) v += a[i][j], c[i].second += v, ++c[i].first;
        }
        int ans = 0;
        dbg(c);
        for (int i = 1; i < n; ++i) {
            if (c[0].first > c[i].first || (c[0].first == c[i].first && c[0].second <= c[i].second)) ++ans;
        }
        cout << n - ans << '\n';
    }
}
