#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    const int inf = (int) 2e9 + 10;
    int t, s, k; cin >> t >> s >> k;
    vector<pair<int, int>> a(s); for (auto& [x, y] : a) cin >> x >> y;
    a.push_back({inf, 0});
    vector<pair<int, int>> span = {a[0]};
    int ans = 0;
    for (int xz = 1; xz <= s; ++xz) {
        if (a[xz].first - span.back().first > k) {
            int n = (int) span.size();
            if (t == 1) {
                if (n % 2 == 1) {
                    int v = inf;
                    for (int i = 0; i < n; ++i) {
                        if (i % 2 == 0 || span[i + 1].first - span[i - 1].first <= k) {
                            v = min(v, span[i].second);
                        }
                    }
                    ans += v;
                }
            } else {
                vector<pair<int, int>> dp(n + 1);
                dp[0] = {0, -inf};
                int prev = 0;
                for (int i = 0; i < n; ++i) {
                    dp[i + 1] = dp[i];
                    while (span[i].first - span[prev].first > k) ++prev;
                    if (i == 0 || i == n - 1 || span[i + 1].first - span[i - 1].first <= k || i % 2 == 1) {
                        dp[i + 1].first = max(dp[i + 1].first, dp[prev].second + span[i].second);
                    }
                    if (i == 0 || i == n - 1 || span[i + 1].first - span[i - 1].first <= k || i % 2 == 0) {
                        dp[i + 1].second = max(dp[i + 1].second, dp[prev].first + span[i].second);
                    }
                }
                ans += (n % 2 == 0 ? dp[n].first : dp[n].second);
            }
            span.clear();
        }
        span.push_back(a[xz]);
    }
    cout << ans << '\n';
}
