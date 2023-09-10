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
        vector<int> a(n); for (auto& x : a) cin >> x, --x;
        vector<int> nxt(n + 1, -1), dp(n + 1);
        vector<map<int, int>> mp(n + 1);
        for (int i = n - 1; i >= 0; --i) {
            if (mp[i + 1].contains(a[i])) {
                nxt[i] = mp[i + 1][a[i]];
                dp[i] = 1 + dp[nxt[i] + 1];
                swap(mp[i], mp[nxt[i] + 1]);
            }
            mp[i][a[i]] = i;
        }
        cout << accumulate(dp.begin(), dp.end(), 0LL) << '\n';
    }
}
