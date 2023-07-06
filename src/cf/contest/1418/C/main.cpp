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
    const int inf = (int) 1e9 + 10;
    int tt; cin >> tt;
    while (tt--) {
        int n; cin >> n;
        vector<int> a(n); for (auto& x : a) cin >> x;
        vector<vector<int>> dp(n + 1, vector<int>(2, inf));
        dp[0][0] = 0;
        for (int i = 0; i < n; ++i) {
            dp[i + 1][0] = min(dp[i + 1][0], dp[i][1]);
            if (i > 0) dp[i + 1][0] = min(dp[i + 1][0], dp[i - 1][1]);
            dp[i + 1][1] = min(dp[i + 1][1], dp[i][0] + a[i]);
            if (i > 0) dp[i + 1][1] = min(dp[i + 1][1], dp[i - 1][0] + a[i - 1] + a[i]);
        }
        cout << min(dp[n][0], dp[n][1]) << '\n';
    }
}
