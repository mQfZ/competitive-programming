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
    const long long inf = (long long) 1e18 + 10;
    int tt; cin >> tt;
    while (tt--) {
        int n, k; cin >> n >> k;
        vector<int> a(n); for (auto& x : a) cin >> x;
        vector<int> b(n); for (auto& x : b) cin >> x;
        array<vector<long long>, 5> dp;
        dp.fill(vector<long long>(k + 1, -inf));
        dp[0][0] = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = k; j >= 0; --j) {
                if (j != 0) {
                    dp[1][j] = max(dp[1][j - 1], dp[0][j - 1] + a[i] + b[i]);
                    dp[2][j] = max(dp[2][j - 1], dp[0][j - 1] + a[i] - b[i]);
                    dp[3][j] = max(dp[3][j - 1], dp[0][j - 1] - a[i] + b[i]);
                    dp[4][j] = max(dp[4][j - 1], dp[0][j - 1] - a[i] - b[i]);
                }
                dp[0][j] = max(dp[0][j], dp[1][j] - a[i] - b[i]);
                dp[0][j] = max(dp[0][j], dp[2][j] + a[i] - b[i]);
                dp[0][j] = max(dp[0][j], dp[3][j] - a[i] + b[i]);
                dp[0][j] = max(dp[0][j], dp[4][j] + a[i] + b[i]);
            }
        }
        cout << dp[0][k] << '\n';
    }
}
