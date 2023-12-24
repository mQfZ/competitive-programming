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
        int n, k, d; cin >> n >> k >> d;
        vector<int> a(n); for (auto& x : a) cin >> x;
        vector<int> v(k); for (auto& x : v) cin >> x;
        int ans = 0;
        for (int i = 0; i < n; ++i) a[i] -= i + 1;
        for (int i = 0; i < min(2 * n + 1, d); ++i) {
            int pos = 0;
            for (auto& x : a) if (x == 0) ++pos;
            ans = max(ans, (d - i - 1) / 2 + pos);
            for (int j = 0; j < v[i % k]; ++j) ++a[j];
        }
        cout << ans << '\n';
    }
}
