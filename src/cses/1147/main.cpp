#include <bits/stdc++.h>
using namespace std;
 
#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<string> a(n); for (auto& x : a) cin >> x;
    vector<stack<int>> s(m + 1);
    for (int j = 0; j <= m; ++j) s[j].push(n);
    for (int i = n - 1; i >= 0; --i) {
        for (int j = 0; j < m; ++j) if (a[i][j] == '*') s[j].push(i);
        s[m].push(i);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= m; ++j) if (s[j].top() < i) s[j].pop();
        stack<pair<int, int>> v; v.push({-1, i});
        for (int j = 0; j <= m; ++j) {
            while (s[j].top() < v.top().second) {
                auto t = v.top(); v.pop();
                ans = max(ans, (j - v.top().first - 1) * (t.second - i));
            }
            v.push({j, s[j].top()});
        }
    }
    cout << ans << '\n';
}
