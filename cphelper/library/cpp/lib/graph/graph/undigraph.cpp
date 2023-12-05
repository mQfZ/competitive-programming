#include <bits/stdc++.h>
using namespace std;
#pragma once

#include <lib/graph/graph/graph.cpp>

/**
 * Undirected Graph
 * Description:
 *    Base class for a undirected graph.
 * Time Complexity: N/A
 * Verification: N/A
 */

template <typename NV = int, typename EV = int>
struct undigraph : public graph<NV, EV> {
    using graph<NV, EV>::n;
    using graph<NV, EV>::nodes;
    using graph<NV, EV>::edges;

    undigraph(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    void init(int _n) {
        graph<NV, EV>::init(_n);
    }

    int add(int from, int to, EV cost = 1) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        int id = (int) edges.size();
        nodes[from].adj.push_back({from, to, id, cost});
        nodes[to].adj.push_back({to, from, id, cost});
        edges.push_back({from, to, id, cost});
        return id;
    }
};
