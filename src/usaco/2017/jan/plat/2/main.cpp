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
    set_io("tallbarn");
    ios::sync_with_stdio(0); cin.tie(0);
    const long double inf = (long double) 1e18, eps = 1e-12;
    int n; long long k; cin >> n >> k;
    vector<long long> a(n); for (auto& x : a) cin >> x;
    long double l = 0, r = inf;
    long double ans = inf;
    while (l + eps < r) {
        long double m = (l + r) / 2, sm = 0;
        long long cc = 0;
        for (int i = 0; i < n; ++i) {
            long double c = floor((1 + sqrt(1 + 4 * a[i] / m)) / 2 + eps);
            cc += (long long) c;
            sm += a[i] / c;
        }
        if (cc <= k) ans = min(ans, sm), r = m;
        else l = m;
    }
    cout << (long long) round(ans) << '\n';
}
