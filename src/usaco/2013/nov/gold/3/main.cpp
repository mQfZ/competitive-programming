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
    set_io("nochange");
    ios::sync_with_stdio(0); cin.tie(0);
    const int inf = (int) 1e9 + 10;
    int k, n; cin >> k >> n;
    vector<int> coin(k); for (auto& x : coin) cin >> x;
    vector<int> a(n); for (auto& x : a) cin >> x;
    vector<int> sum(n + 1); for (int i = 0; i < n; ++i) sum[i + 1] = sum[i] + a[i];
    vector<int> dp(1 << k);
    int ans = inf;
    for (int mask = 1; mask < 1 << k; ++mask) {
        int total = 0;
        for (int i = 0; i < k; ++i) {
            if (mask & 1 << i) {
                total += coin[i];
                int prev = mask ^ (1 << i);
                int lst = (int) (upper_bound(sum.begin(), sum.end(), sum[dp[prev]] + coin[i]) - sum.begin()) - 1;
                dp[mask] = max(dp[mask], lst);
            }
        }
        if (dp[mask] == n) ans = min(ans, total);
    }
    cout << (ans == inf ? -1 : accumulate(coin.begin(), coin.end(), 0) - ans) << '\n';
}
