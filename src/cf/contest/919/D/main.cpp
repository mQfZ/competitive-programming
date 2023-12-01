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
        vector<edge> adj;
        NV val;
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
 * Topological Sort
 * Description:
 *    Topological sorting. Output is an ordering of vertices, such that for 
 *    each directed edge x -> y, then x comes before y. If there is a cycle, 
 *    then the result will return less than n elements.
 * Time Complexity: O(|V| + |E|)
 * Verification: https://codeforces.com/contest/919/submission/234176228
 */

template <typename NV, typename EV>
vector<int> topo_sort(const digraph<NV, EV>& g) {
    vector<int> in(g.n), ret;
    for (auto& e : g.edges) ++in[e.to];
    queue<int> q;
    for (int i = 0; i < g.n; ++i) if (in[i] == 0) q.push(i);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        ret.push_back(v);
        for (auto& e : g.nodes[v].adj) {
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
    digraph g(n);
    while (m--) {
        int x, y; cin >> x >> y;
        g.add_edge(x - 1, y - 1);
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
