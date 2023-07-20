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
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n)); for (auto& x : a) for (auto& y : x) cin >> y;
    vector<int> ans(n);
    vector<pair<int, int>> edges;
    function<int(vector<int>)> solve = [&](vector<int> in) {
        int mx = 0;
        for (int v : in) for (int nv : in) mx = max(mx, a[v][nv]);
        int q = (in.size() == 1 ? in[0] : (int) ans.size());
        if (in.size() != 1) ans.push_back(mx);
        else ans[q] = mx;
        if (in.size() == 1) return q;
        vector<bool> shown(n);
        for (int v : in) {
            if (shown[v]) continue;
            vector<int> z;
            for (int nv : in) if (a[v][nv] != mx) z.push_back(nv), shown[nv] = true;
            edges.push_back({solve(z), q});
        }
        return q;
    };
    vector<int> v(n); iota(v.begin(), v.end(), 0);
    int q = solve(v);
    cout << ans.size() << '\n';
    for (int i = 0; i < (int) ans.size(); ++i) cout << ans[i] << " \n"[i == (int) ans.size() - 1];
    cout << q + 1 << '\n';
    for (auto& [x, y] : edges) cout << x + 1 << ' ' << y + 1 << '\n';
}
