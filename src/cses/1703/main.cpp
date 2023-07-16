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
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    while (m--) {
        int x, y; cin >> x >> y;
        adj[x - 1].push_back(y - 1);
    }
    vector<bool> seen(n);
    vector<int> path;
    function<bool(int)> dfs = [&](int v) {
        if (seen[v]) return false;
        seen[v] = true;
        path.push_back(v);
        if (v == n - 1) return true;
        for (int nv : adj[v]) if (dfs(nv)) return true;
        path.pop_back();
        return false;
    };
    dfs(0);
    vector<int> last(n, -1);
    for (int i = 0; i < (int) path.size(); ++i) last[path[i]] = i;
    vector<bool> vis(n);
    function<int(int, bool)> solve = [&](int v, bool first) {
        if (last[v] != -1 && !first) return last[v];
        if (vis[v]) return -1;
        vis[v] = true;
        int mx = last[v];
        for (int nv : adj[v]) mx = max(mx, solve(nv, false));
        return mx;
    };
    vector<pair<int, int>> pos;
    vector<int> count(path.size());
    for (int i = 0; i < (int) path.size(); ++i) {
        int mx = solve(path[i], true);
        if (mx != i) ++count[i + 1], --count[mx];
    }
    int sm = 0;
    vector<int> ans;
    for (int i = 0; i < (int) count.size(); ++i) {
        sm += count[i];
        if (sm == 0) ans.push_back(path[i]);
    }
    sort(ans.begin(), ans.end());
    cout << ans.size() << '\n';
    for (int i = 0; i < (int) ans.size(); ++i) {
        cout << ans[i] + 1 << " \n"[i == (int) ans.size() - 1];
    }
}
