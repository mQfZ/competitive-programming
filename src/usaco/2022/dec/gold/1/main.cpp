#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

struct person {
    int p, b, c;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m, t; cin >> n >> m >> t;
    vector<person> a(n); for (auto& x : a) cin >> x.p >> x.b >> x.c;
    sort(a.begin(), a.end(), [&](auto x, auto y) { return x.c < y.c; });
    vector<int> dp(m + t + 2);
    for (auto& p : a) {
        vector<int> ndp = dp;
        for (int i = t; i > 0; --i) {
            dp[m + i] = max(dp[m + i + 1], dp[m + i]);
            if (p.b * p.c <= i) {
                ndp[m + i - p.b * p.c] = max(ndp[m + i - p.b * p.c], dp[m + i] + p.p);
            }
            else {
                int d = i / p.c;
                if (m - p.b + d >= 0) {
                    ndp[m - p.b + d] = max(ndp[m - p.b + d], dp[m + i] + p.p);
                }
            }
        }
        for (int i = m; i >= 0; --i) {
            dp[i] = max(dp[i + 1], dp[i]);
            if (i - p.b >= 0) {
                ndp[i - p.b] = max(ndp[i - p.b], dp[i] + p.p);
            }
        }
        dp = ndp;
    }
    cout << *max_element(dp.begin(), dp.end()) << '\n';
}
