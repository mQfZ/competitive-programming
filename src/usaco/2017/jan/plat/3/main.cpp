#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

void set_io(string s) {
#ifndef LOCAL
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
#endif
}

int main() {
    set_io("subrev");
    ios::sync_with_stdio(0); cin.tie(0);
    const int s = 50;
    int n; cin >> n;
    vector<int> a(n); for (auto& x : a) cin >> x, --x;
    vector dp(n, vector(n, vector(s, vector(s, -n))));
    for (int i = 0; i < n; ++i) {
        dp[i][i][a[i]][a[i]] = 1;
    }
    for (int i = 0; i < n - 1; ++i) {
        dp[i][i + 1][a[i]][a[i]] = 1;
        dp[i][i + 1][a[i + 1]][a[i + 1]] = 1;
        dp[i][i + 1][min(a[i], a[i + 1])][max(a[i], a[i + 1])] = 2;
    }
    for (int d = 2; d < n; ++d) {
        for (int i = 0; i + d < n; ++i) {
            int j = i + d;
            for (int l = 0; l < s; ++l) {
                for (int r = l; r < s; ++r) {
                    dp[i][j][l][r] = max({
                        dp[i][j][l][r],
                        dp[i][j - 1][l][r],
                        dp[i + 1][j][l][r]
                    });
                    if (r <= a[j]) {
                        dp[i][j][l][a[j]] = max(dp[i][j][l][a[j]], dp[i][j - 1][l][r] + 1);
                    }
                    if (a[i] <= l) {
                        dp[i][j][a[i]][r] = max(dp[i][j][a[i]][r], dp[i + 1][j][l][r] + 1);
                    }
                    int p, q;
                    p = min(a[i], l);
                    q = max(a[j], r);
                    dp[i][j][p][q] = max(dp[i][j][p][q], dp[i + 1][j - 1][l][r] + (a[i] <= l) + (r <= a[j]));
                    p = min(a[j], l);
                    q = max(a[i], r);
                    dp[i][j][p][q] = max(dp[i][j][p][q], dp[i + 1][j - 1][l][r] + (a[j] <= l) + (r <= a[i]));
                }
            }
        }
    }
    int ans = 0;
    for (int l = 0; l < s; ++l) {
        for (int r = l; r < s; ++r) {
            ans = max(ans, dp[0][n - 1][l][r]);
        }
    }
    cout << ans << '\n';
}
