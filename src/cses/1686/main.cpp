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

    virtual int add(int from, int to, T cost) = 0;
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
 * Strongly Connected Components (Tarjan's Algorithm)
 * Description:
 *    Tarjan's algorithm to find all strongly connected components in a 
 *    directed graph. Vertices x, y belong in the same component iff y is 
 *    reachable from x and x is reachable from y.
 * Time Complexity: O(|V| + |E|)
 * Verification: https://judge.yosupo.jp/submission/174000
 */

template <typename T>
struct scc : digraph<T> {
    using digraph<T>::n;
    using digraph<T>::adj;
    using digraph<T>::edges;

    int time;
    stack<int> stk;
    vector<bool> in_stk;
    vector<int> tour, low;

    vector<int> which;  // indicates which scc the node belongs to
    vector<vector<int>> comp;  // the vertices in each scc

    scc(int _n = -1) : digraph<T>(_n) {
        if (_n >= 0) init(_n);
    }

    void init(int _n) {
        digraph<T>::init(_n);
    }

    void dfs(int v) {
        low[v] = tour[v] = time++;
        stk.push(v);
        in_stk[v] = true;
        for (auto& e : adj[v]) {
            if (tour[e.to] == -1) {
                dfs(e.to);
                low[v] = min(low[v], low[e.to]);
            } else if (in_stk[e.to]) {
                low[v] = min(low[v], tour[e.to]);
            }
        }
        if (low[v] == tour[v]) {
            comp.push_back({});
            int x;
            do {
                assert(!stk.empty());
                x = stk.top();
                stk.pop();
                in_stk[x] = false;
                which[x] = (int) comp.size() - 1;
                comp.back().push_back(x);
            } while (x != v);
        }
    }

    void build() {
        tour.assign(n, -1);
        low.resize(n);
        which.assign(n, -1);
        in_stk.assign(n, false);
        comp = {};
        time = 0;
        for (int i = 0; i < n; ++i) {
            if (tour[i] == -1) dfs(i);
        }
        // tarjan returns in reverse topological order
        reverse(comp.begin(), comp.end());
        for (int i = 0; i < n; ++i) {
            which[i] = (int) comp.size() - which[i] - 1;
        }
    }

    // compress scc into a topologically sorted graph (each scc is one node)
    digraph<T> compress() {
        assert(comp.size() > 0);
        digraph<T> ng((int) comp.size());
        for (auto& e : edges) {
            if (which[e.from] != which[e.to]) {
                ng.add(which[e.from], which[e.to], e.dist);
            }
        }
        return ng;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    const long long inf = (long long) 2e18 + 10;
    int n, m; cin >> n >> m;
    vector<long long> a(n); for (auto& x : a) cin >> x;
    scc<int> s(n);
    while (m--) {
        int x, y; cin >> x >> y;
        s.add(x - 1, y - 1);
    }
    s.build();
    digraph<int> dg = s.compress();
    vector<long long> sm(dg.n), dp(dg.n, -inf);
    for (int i = 0; i < dg.n; ++i) {
        for (int x : s.comp[i]) sm[i] += a[x];
    }
    for (int i = 0; i < dg.n; ++i) {
        dp[i] = max(dp[i], sm[i]);
        for (auto& e : dg.adj[i]) {
            dp[e.to] = max(dp[e.to], dp[i] + sm[e.to]);
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << '\n';
}
