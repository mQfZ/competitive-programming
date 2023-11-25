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
