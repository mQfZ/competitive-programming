#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        int n, d, h; cin >> n >> d >> h;
        vector<long long> a(n); for (auto& x : a) cin >> x;
        a.push_back((long long) 1e18);
        long double ans = 0;
        for (int i = 0; i < n; ++i) {
            long long height = min((long long) h, a[i + 1] - a[i]);
            long double slope = (long double) h / ((double) d / 2);
            ans += (d + d - 2 * height * ((long double) 1 / slope)) * height / 2;
        }
        cout << fixed << setprecision(20) << ans << '\n';
    }
}
