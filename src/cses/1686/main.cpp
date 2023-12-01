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

template <typename NV = int, typename EV = int>
struct graph {
    struct edge {
        int from, to, id;
        EV val;
    };
    
    struct node {
        NV val;
        vector<edge> adj;
    };

    int n;
    vector<node> nodes;
    vector<edge> edges;
    function<bool(const edge&)> ignore;

    graph(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    void init(int _n) {
        n = _n;
        nodes.assign(n, {{}, {}});
        edges = {};
        ignore = nullptr;
    }

    void set_node(int index, NV val = 0) {
        nodes[index].val = val;
    }

    virtual int add_edge(int from, int to, EV val) = 0;

    virtual void set_ignore_edge_rule(const function<bool(const edge&)>& f = nullptr) {
        ignore = f;
    }

    virtual bool ignore_edge(const edge& e) {
        return ignore != nullptr && ignore(e);
    }
};

/**
 * Directed Graph
 * Description:
 *    Base class for a directed graph.
 * Time Complexity: N/A
 * Verification: N/A
 */

template <typename NV = int, typename EV = int>
struct digraph : public graph<NV, EV> {
    using graph<NV, EV>::n;
    using graph<NV, EV>::nodes;
    using graph<NV, EV>::edges;
    using graph<NV, EV>::ignore;

    digraph(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    void init(int _n) {
        graph<NV, EV>::init(_n);
    }

    int add_edge(int from, int to, EV cost = 1) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        int id = (int) edges.size();
        nodes[from].adj.push_back({from, to, id, cost});
        edges.push_back({from, to, id, cost});
        return id;
    }

    digraph<NV, EV> reverse() const {
        digraph<NV, EV> rev(n);
        for (auto& e : edges) rev.add(e.to, e.from, e.cost);
        rev.set_ignore_edge_rule(ignore);
        return rev;
    }
};

/**
 * Strongly Connected Components (Tarjan's Algorithm)
 * Description:
 *    Tarjan's algorithm to find all strongly connected components in a 
 *    directed graph. Vertices x, y belong in the same component iff y is 
 *    reachable from x and x is reachable from y.
 * Time Complexity: O(|V| + |E|)
 * Verification:
 *     https://judge.yosupo.jp/submission/174000
 *     https://github.com/mQfZ/competitive-programming/blob/master/src/cses/1686/main.cpp
 */

template <typename NV = int, typename EV = int>
struct scc : digraph<NV, EV> {
    using graph<NV, EV>::n;
    using graph<NV, EV>::nodes;
    using graph<NV, EV>::edges;
    using graph<NV, EV>::ignore_edge;

    int time;
    stack<int> stk;
    vector<bool> in_stk;
    vector<int> tour, low;

    vector<int> which;  // indicates which scc the node belongs to
    vector<vector<int>> comps;  // the vertices in each scc
    int cs;  // comps size

    scc(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    void init(int _n) {
        digraph<NV, EV>::init(_n);
    }

    void dfs(int v) {
        low[v] = tour[v] = time++;
        stk.push(v);
        in_stk[v] = true;
        for (auto& e : nodes[v].adj) {
            if (ignore_edge(e)) continue;
            if (tour[e.to] == -1) {
                dfs(e.to);
                low[v] = min(low[v], low[e.to]);
            } else if (in_stk[e.to]) {
                low[v] = min(low[v], tour[e.to]);
            }
        }
        if (low[v] == tour[v]) {
            comps.push_back({});
            int x;
            do {
                assert(!stk.empty());
                x = stk.top();
                stk.pop();
                in_stk[x] = false;
                which[x] = (int) comps.size() - 1;
                comps.back().push_back(x);
            } while (x != v);
        }
    }

    void build() {
        tour.assign(n, -1);
        low.resize(n);
        which.assign(n, -1);
        in_stk.assign(n, false);
        comps = {};
        time = 0;
        for (int i = 0; i < n; ++i) {
            if (tour[i] == -1) dfs(i);
        }
        // tarjan returns in reverse topological order
        cs = (int) comps.size();
        reverse(comps.begin(), comps.end());
        for (int i = 0; i < n; ++i) {
            which[i] = cs - which[i] - 1;
        }
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    const long long inf = (long long) 2e18 + 10;
    int n, m; cin >> n >> m;
    vector<long long> a(n); for (auto& x : a) cin >> x;
    scc s(n);
    while (m--) {
        int x, y; cin >> x >> y;
        s.add_edge(x - 1, y - 1);
    }
    s.build();
    vector<long long> sm(s.cs), dp(s.cs, -inf);
    for (int i = 0; i < s.cs; ++i) {
        for (int x : s.comps[i]) sm[i] += a[x];
    }
    for (int i = 0; i < s.cs; ++i) {
        dp[i] = max(dp[i], sm[i]);
        for (int x : s.comps[i]) {
            for (auto& e : s.nodes[x].adj) {
                if (i == s.which[e.to]) continue;
                dp[s.which[e.to]] = max(dp[s.which[e.to]], dp[i] + sm[s.which[e.to]]);
            }
        }
    }
    cout << *max_element(dp.begin(), dp.end()) << '\n';
}
