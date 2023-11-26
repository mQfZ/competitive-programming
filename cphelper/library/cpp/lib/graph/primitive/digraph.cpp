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
