#include <bits/stdc++.h>
using namespace std;
#pragma once

#include <lib/graph/graph/digraph.cpp>

/**
 * Strongly Connected Components (Tarjan's Algorithm)
 * Description:
 *    Tarjan's algorithm to find all strongly connected components in a 
 *    directed graph. Vertices x, y belong in the same component iff y is 
 *    reachable from x and x is reachable from y.
 * Time Complexity: O(|V| + |E|)
 * Verification:
 *     https://judge.yosupo.jp/submission/175097
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
