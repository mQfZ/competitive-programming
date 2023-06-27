#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        int n; cin >> n;
        vector<pair<int, long long>> a(n); for (auto& [x, y] : a) cin >> x >> y;
        vector<vector<long long>> st(n);
        for (int i = 0; i < n; ++i) st[a[i].first].push_back(a[i].second);
        multiset<long long> ms;
        long long ans = 0;
        int total = n;
        for (int i = n - 1; i >= 0; --i) {
            for (long long v : st[i]) ms.insert(v);
            total -= (int) st[i].size();
            while (total < i) {
                ans += *ms.begin();
                ms.erase(ms.begin());
                ++total;
            }
        }
        cout << ans << '\n';
    }
}
