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

template <typename T>
struct undigraph : public graph<T> {
    using graph<T>::n;
    using graph<T>::adj;
    using graph<T>::edges;

    undigraph(int _n = -1) : graph<T>(_n) {}

    void init(int _n) {
        graph<T>::init(_n);
    }

    int add(int from, int to, T cost = 1) {
        assert(0 <= from && from < n && 0 <= to && to < n);
        int id = (int) edges.size();
        adj[from].push_back({from, to, cost, id});
        adj[to].push_back({to, from, cost, id});
        edges.push_back({from, to, cost, id});
        return id;
    }
};
