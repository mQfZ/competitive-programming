#include <bits/stdc++.h>
using namespace std;
#pragma once

#include <lib/graph/primitive/graph.cpp>

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
