#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<long long> a(n); for (auto& x : a) cin >> x;
    vector<long long> dp(n);
    dp[1] = abs(a[1] - a[0]);
    for (int i = 2; i < n; ++i) {
        if ((a[i] < a[i - 1]) ^ (a[i - 1] < a[i - 2])) {
            dp[i] = max(dp[i - 2] + abs(a[i] - a[i - 1]), dp[i - 1]);
        } else dp[i] = dp[i - 1] + abs(a[i] - a[i - 1]);
    }
    cout << dp[n - 1] << '\n';
}
