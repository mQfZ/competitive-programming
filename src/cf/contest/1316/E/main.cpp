#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

struct Person {
    long long a;
    vector<long long> s;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    const long long inf = 1e18;
    int n, p, k; cin >> n >> p >> k;
    vector<Person> a(n);
    for (auto& x : a) cin >> x.a;
    for (auto& x : a) {
        x.s.resize(p);
        for (auto& v : x.s) cin >> v;
    }
    sort(a.begin(), a.end(), [&](auto x, auto y) { return x.a > y.a; });
    vector<long long> dp(1 << p, -inf);
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        vector<long long> ndp(1 << p, -inf);
        for (int j = 0; j < (1 << p); ++j) {
            for (int b = 0; b < p; ++b) {
                if ((1 << b) & j) ndp[j] = max(ndp[j], dp[j ^ (1 << b)] + a[i].s[b]);
            }
            if (i - __builtin_popcount(j) < k) {
                ndp[j] = max(ndp[j], dp[j] + a[i].a);
            } else ndp[j] = max(ndp[j], dp[j]);
        }
        dp = ndp;
    }
    cout << dp[(1 << p) - 1] << '\n';
}
