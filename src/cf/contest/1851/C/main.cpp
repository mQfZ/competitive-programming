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
        int n, k; cin >> n >> k;
        vector<int> a(n); for (auto& x : a) cin >> x;
        if (a[0] == a[n - 1]) {
            int z = 0;
            for (int i = 0; i < n; ++i) if (a[i] == a[0]) ++z;
            cout << (z >= k ? "YES" : "NO") << '\n';
        } else {
            vector<int> pref(n), suff(n);
            pref[0] = 1;
            suff[n - 1] = 1;
            for (int i = 1; i < n; ++i) pref[i] = pref[i - 1] + (a[i] == a[0]);
            for (int i = n - 2; i >= 0; --i) suff[i] = suff[i + 1] + (a[i] == a[n - 1]);
            bool ans = false;
            dbg(pref, suff);
            for (int i = 1; i < n; ++i) {
                if (pref[i - 1] >= k && suff[i] >= k) ans = true;
            }
            cout << (ans ? "YES" : "NO") << '\n';
        }
    }
}
