#include <bits/stdc++.h>
using namespace std;
#pragma once

#include <lib/graph/primitive/digraph.cpp>

/**
 * Topological Sort
 * Description:
 *    Topological sorting. Output is an ordering of vertices, such that for 
 *    each directed edge x -> y, then x comes before y. If there is a cycle, 
 *    then the result will return less than n elements.
 * Time Complexity: O(|V| + |E|)
 * Verification: https://codeforces.com/contest/919/submission/234176228
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
