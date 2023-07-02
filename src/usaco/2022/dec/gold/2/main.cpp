#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n); for (auto& x : a) cin >> x;
    vector<set<int>> s(n);
    auto hidden = [&](int l, int m, int r) {
        if (l == m) return false;
        return (long long) (a[m] - a[l]) * (r - l) > (long long) (a[r] - a[l]) * (m - l);
    };
    int ans = 0;
    for (int x = 0; x < n; ++x) {
        s[x].insert(x);
        for (int j = x + 1; j < n; ++j) {
            if (!hidden(x, *s[x].rbegin(), j)) s[x].insert(j), ++ans;
        }
    }
    int q; cin >> q;
    while (q--) {
        int x, y; cin >> x >> y, --x;
        a[x] += y;
        for (int i = 0; i < x; ++i) {
            auto it = prev(s[i].upper_bound(x));
            if (*it != x) {
                if (hidden(i, *it, x)) continue;
                s[i].insert(x), ++ans;
                ++it;
            }
            ++it;
            while (it != s[i].end()) {
                if (!hidden(i, x, *it)) break;
                it = s[i].erase(it), --ans;
            }
        }
        ans -= (int) s[x].size() - 1;
        s[x].clear();
        s[x].insert(x);
        for (int j = x + 1; j < n; ++j) {
            if (!hidden(x, *s[x].rbegin(), j)) s[x].insert(j), ++ans;
        }
        cout << ans << '\n';
    }
}
