#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

template <typename T>
using gpq = priority_queue<T, vector<T>, greater<T>>;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    const long long inf = (long long) 1e18 + 10;
    int tt; cin >> tt;
    while (tt--) {
        int n, m; cin >> n >> m;
        string s; cin >> s;
        vector<vector<long long>> adj(1 << n, vector<long long>(1 << n, inf));
        while (m--) {
            int x; string a, b; cin >> x >> a >> b;
            int l = (int) bitset<10>(a).to_ulong(), r = (int) bitset<10>(b).to_ulong();
            for (int i = 0; i < 1 << n; ++i) adj[i][(i | r) - (i & l)] = min((long long) x, adj[i][(i | r) - (i & l)]);
        }
        vector<long long> dist(1 << n, inf);
        gpq<pair<long long, int>> q;
        q.push({0, bitset<10>(s).to_ulong()});
        while (!q.empty()) {
            auto [d, v] = q.top(); q.pop();
            if (dist[v] != inf) continue;
            dist[v] = d;
            for (int nv = 0; nv < 1 << n; ++nv) if (adj[v][nv] != inf) q.push({d + adj[v][nv], nv});
        }
        cout << (dist[0] >= inf ? -1 : dist[0]) << '\n';
    }
}
