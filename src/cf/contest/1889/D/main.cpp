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
    int n, st; cin >> n;
    vector<int> sz(n), s(n), ans(n);
    vector<queue<int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> sz[i];
        for (int j = 0; j < sz[i]; ++j) {
            int x; cin >> x, --x; ++s[x], a[i].push(x);
        }
    }
    queue<int> c;
    iota(ans.begin(), ans.end(), 0);
    for (int i = 0; i < n; ++i) c.push(i);
    while (!c.empty()) {
        int i = c.front(); c.pop();
        while (s[i] < sz[i]) {
            int z = a[i].front();
            --s[z], --sz[i], c.push(z), a[i].pop();
            ans[i] = z;
        }
    }
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) adj[ans[i]].push_back(i);
    function<void(int, int)> dfs = [&](int v, int pv) {
        for (int nv : adj[v]) if (nv != pv) ans[nv] = st, dfs(nv, v);
    };
    for (st = 0; st < n; ++st) if (ans[st] == st) dfs(st, -1);
    for (int i = 0; i < n; ++i) cout << ans[i] + 1 << " \n"[i == n - 1];
}
