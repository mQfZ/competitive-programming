#include <bits/stdc++.h>
using namespace std;
#pragma once

/**
 * Topological Sort
 * Description:
 *    Topological sorting. Output is an ordering of vertices, such that for 
 *    each directed edge x -> y, then x comes before y. If there is a cycle, 
 *    then the result will return less than n elements.
 * Time Complexity: O(|V| + |E|)
 * Verification: https://codeforces.com/contest/919/submission/207096730
 */

vector<int> topoSort(vector<vector<int>>& adj) {
    int n = (int) adj.size();
    vector<int> in(n), ret;
    for (auto& li : adj) for (int v : li) ++in[v];
    queue<int> q;
    for (int i = 0; i < n; ++i) if (in[i] == 0) q.push(i);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        ret.push_back(v);
        for (int nv : adj[v]) {
            if ((--in[nv]) == 0) q.push(nv);
        }
    }
    return ret;
}
