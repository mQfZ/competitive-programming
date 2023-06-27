#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    const long long inf = 1e18;
    int n, k; cin >> n >> k;
    vector<int> a(n); for (auto& x : a) cin >> x, --x;
    vector<long long> dp(n + 1, inf), ndp(n + 1);
    dp[0] = 0;
    int ll = 0, rr = -1;
    long long ans = 0;
    vector<int> freq(n);
    auto add = [&](int i) { ans += freq[a[i]]++; };
    auto remove = [&](int i) { ans -= --freq[a[i]]; };
    auto cost = [&](int l, int r) {
        while (ll < l) remove(ll), ++ll;
        while (ll > l) --ll, add(ll);
        while (rr < r) ++rr, add(rr);
        while (rr > r) remove(rr), --rr;
        return ans;
    };
    function<void(int, int, int, int)> compute = [&](int l, int r, int optl, int optr) {
        if (l > r) return;
        int m = (l + r) >> 1;
        pair<long long, int> best = {inf, -1};
        for (int i = min(m, optr); i >= optl; --i) {
            best = min(best, {dp[i] + cost(i, m - 1), i});
        }
        ndp[m] = best.first;
        int opt = best.second;
        compute(l, m - 1, optl, opt);
        compute(m + 1, r, opt, optr);
    };
    while (k--) {
        compute(0, n, 0, n);
        dp = ndp;
    }
    cout << dp[n] << '\n';
}
