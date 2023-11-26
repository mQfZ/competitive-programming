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
    set_io("sabotage");
    ios::sync_with_stdio(0); cin.tie(0);
    const int inf = (int) 1e9 + 10;
    const long double eps = 1e-4;
    int n; cin >> n;
    vector<int> a(n); for (auto& x : a) cin >> x;
    long double l = 1, r = inf;
    while (abs(l - r) > eps) {
        long double m = (l + r) / 2;
        long double mx = -inf, sum = 0, need = a[0] - m + a[n - 1] - m;
        for (int i = 1; i < n - 1; ++i) {
            sum = max(sum, 0.0L) + a[i] - m;
            mx = max(mx, sum);
            need += a[i] - m;
        }
        if (mx >= need) r = m;
        else l = m;
    }
    cout << fixed << setprecision(3) << l << '\n';
}
