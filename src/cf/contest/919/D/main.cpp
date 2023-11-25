#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

/**
 * Graph
 * Description:
 *    Abstract base graph class.
 * Time Complexity: N/A
 * Verification: N/A
 */

template <typename T>
struct graph {
    struct edge {
        int from;
        int to;
        T dist;
        int id;
    };

    int n;
    vector<vector<edge>> adj;
    vector<edge> edges;

    graph(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    void init(int _n) {
        n = _n;
        adj.assign(n, {});
        edges = {};
    }

    virtual int add_edge(int from, int to, T cost) = 0;
};

/**
 * Directed Graph
 * Description:
 *    Base class for a directed graph.
 * Time Complexity: N/A
 * Verification: N/A
 */

template <typename T>
struct digraph : public graph<T> {
    using graph<T>::n;
    using graph<T>::adj;
    using graph<T>::edges;

    digraph(int _n = -1) : graph<T>(_n) {}

    void init(int _n) {
        graph<T>::init(_n);
    }

    int add(int from, int to, T cost = 1) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        int id = (int) edges.size();
        adj[from].push_back({from, to, cost, id});
        edges.push_back({from, to, cost, id});
        return id;
    }
};

/**
 * Topological Sort
 * Description:
 *    Topological sorting. Output is an ordering of vertices, such that for 
 *    each directed edge x -> y, then x comes before y. If there is a cycle, 
 *    then the result will return less than n elements.
 * Time Complexity: O(|V| + |E|)
 * Verification: https://codeforces.com/contest/919/submission/234165355
 */

template <typename T>
vector<int> topo_sort(const digraph<T>& g) {
    vector<int> in(g.n), ret;
    for (auto& e : g.edges) ++in[e.to];
    queue<int> q;
    for (int i = 0; i < g.n; ++i) if (in[i] == 0) q.push(i);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        ret.push_back(v);
        for (auto& e : g.adj[v]) {
            if ((--in[e.to]) == 0) q.push(e.to);
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    string s; cin >> s;
    vector<vector<int>> inv(n);
    digraph<int> g(n);
    while (m--) {
        int x, y; cin >> x >> y;
        g.add(x - 1, y - 1);
        inv[y - 1].push_back(x - 1);
    }
    vector<int> topo = topo_sort(g);
    if ((int) topo.size() < n) {
        cout << -1 << '\n';
        return 0;
    }
    vector<vector<int>> dp(n, vector<int>(26));
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int v = topo[i];
        for (int pv : inv[v]) {
            for (int j = 0; j < 26; ++j) {
                dp[v][j] = max(dp[v][j], dp[pv][j]);
                ans = max(ans, dp[v][j]);
            }
        }
        ++dp[v][s[v] - 'a'];
        ans = max(ans, dp[v][s[v] - 'a']);
    }
    cout << ans << '\n';
}
