#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<array<int, 2>> a(n); for (int i = 0; i < n; ++i) cin >> a[i][0] >> a[i][1];
    array<long long, 2> sums;
    sums[0] = sums[1] = 0;
    vector<bool> dp(k);
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        vector<int> pref(k + 1);
        sums[0] += a[i][0];
        sums[1] += a[i][1];
        int lb = max(1, k - a[i][1]);
        int rb = min(a[i][0], k - 1);
        if (lb <= rb) {
            for (int j = 0; j < k; ++j) {
                if (dp[j]) {
                    int l = j + lb, r = j + rb;
                    if (l > k) ++pref[l % k], --pref[r % k + 1];
                    else ++pref[l], --pref[min(r + 1, k)];
                }
            }
        }
        for (int j = 0; j < k; ++j) {
            if (j > 0) pref[j] += pref[j - 1];
            dp[j] = dp[j] || (pref[j] > 0);
        }
    }
    long long ans = sums[0] / k + sums[1] / k;
    for (int i = 1; i < k; ++i) {
        if (dp[i]) ans = max(ans, (sums[0] - i) / k + (sums[1] - k + i) / k + 1);
    }
    cout << ans << '\n';
}
