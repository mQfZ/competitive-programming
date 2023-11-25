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
 *     https://judge.yosupo.jp/submission/174000
 *     https://github.com/mQfZ/competitive-programming/blob/master/src/cses/1686/main.cpp
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
