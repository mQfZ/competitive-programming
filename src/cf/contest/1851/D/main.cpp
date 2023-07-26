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
        int n; cin >> n;
        vector<long long> a(n); for (int i = 1; i < n; ++i) cin >> a[i];
        a[0] = 0;
        vector<bool> d(n + 1);
        long long out = -1;
        for (int i = 1; i < n; ++i) {
            long long diff = a[i] - a[i - 1];
            if (diff > n || d[diff]) out = diff;
            else d[diff] = true;
        }
        long long t = 0, z = 0;
        for (int i = 1; i <= n; ++i) {
            if (!d[i]) ++t, z += i;
        }
        bool ans = false;
        if (t == 1) ans = true;
        if (t == 2) ans = z == out;
        cout << (ans ? "YES" : "NO") << '\n';
    }
}
