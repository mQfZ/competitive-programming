#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

template <typename T>
using gpq = priority_queue<T, vector<T>, greater<T>>;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    vector<vector<tuple<int, int, bool>>> adj(n);
    while (m--) {
        int x, y, d; cin >> x >> y >> d, --x, --y;
        adj[x].push_back({y, d, 0});
        adj[y].push_back({x, d, 0});
    }
    vector<pair<int, int>> s(k);
    for (int i = 0; i < k; ++i) {
        int x, d; cin >> x >> d, --x;
        s[i] = {x, d};
        adj[0].push_back({x, d, 1});
        adj[x].push_back({0, d, 1});
    }
    priority_queue q = gpq<pair<long long, int>>();
    q.push({0, 0});
    vector<long long> dist(n, -1);
    while (!q.empty()) {
        auto [d, v] = q.top(); q.pop();
        if (dist[v] != -1) continue;
        dist[v] = d;
        for (auto [nv, nd, _] : adj[v]) {
            q.push({d + nd, nv});
        }
    }
    vector<bool> nz(n);
    for (int v = 0; v < n; ++v) {
        for (auto [nv, nd, t] : adj[v]) {
            if (!t && dist[nv] + nd == dist[v]) nz[v] = true;
        }
    }
    vector<int> needed(n, 0);
    for (auto [v, d] : s) {
        if (dist[v] > d || (dist[v] == d && !nz[v])) needed[v] = 1;
    }
    cout << k - accumulate(needed.begin(), needed.end(), 0) << '\n';
}
