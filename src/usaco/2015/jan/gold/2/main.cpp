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
    set_io("movie");
    ios::sync_with_stdio(0); cin.tie(0);
    int n, l; cin >> n >> l;
    vector<int> a(n), sz(n);
    vector<vector<int>> show(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> sz[i];
        show[i].resize(sz[i]);
        for (auto& x : show[i]) cin >> x;
    }
    vector<int> dp(1 << n, -1);
    dp[0] = 0;
    int ans = n + 1;
    for (int mask = 1; mask < 1 << n; ++mask) {
        for (int b = 0; b < n; ++b) {
            if (mask & (1 << b)) {
                auto it = upper_bound(show[b].begin(), show[b].end(), dp[mask ^ (1 << b)]);
                if (it != show[b].begin()) {
                    dp[mask] = max(dp[mask], *(--it) + a[b]);
                }
            }
        }
        if (dp[mask] >= l) ans = min(ans, __builtin_popcount(mask));
    }
    if (ans == n + 1) ans = -1;
    cout << ans << '\n';
}
