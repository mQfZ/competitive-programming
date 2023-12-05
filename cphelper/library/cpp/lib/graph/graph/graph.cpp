#include <bits/stdc++.h>
using namespace std;
#pragma once

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
