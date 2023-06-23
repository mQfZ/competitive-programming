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
    vector<int> a(n); for (auto& x : a) cin >> x, --x;
    vector<int> f(n, -1), l(n, -1), t(n);
    for (int i = 0; i < n; ++i) {
        if (f[a[i]] == -1) f[a[i]] = i;
        l[a[i]] = i;
    }
    vector<int> dp(n + 1);
    for (int i = n - 1; i >= 0; --i) {
        dp[i] = max(dp[i + 1], ++t[a[i]] + (i == f[a[i]] ? dp[l[a[i]] + 1] : 0));
    }
    cout << n - dp[0] << '\n';
}
