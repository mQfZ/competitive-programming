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
        int n; long long c; cin >> n >> c;
        vector<long long> a(n); for (auto& x : a) cin >> x;
        vector<pair<long long, long long>> t(n - 1);
        for (int i = 1; i < n; ++i) t[i - 1] = {c * (i + 1) - a[i], a[i]};
        long long s = a[0];
        sort(t.begin(), t.end());
        bool ans = true;
        for (int i = 0; i < n - 1; ++i) {
            if (s >= t[i].first) s += t[i].second;
            else ans = false;
        }
        cout << (ans ? "Yes" : "No") << '\n';
    }
}
