#include <bits/stdc++.h>
using namespace std;
#pragma once

#include <lib/data_structures/segment_tree/sparse_segment_tree.h>

/**
 * Persistent Sparse Segment Tree
 * Description:
 *    Persistent Sparse Segment Tree that does not allocate storage for nodes 
 *    with no data. Can point update and range query any version of the segment 
 *    tree. Node class must have default value(s) set and a static unite method.
 * Time Complexity:
 *     Update: O(log n)
 *     Query: O(log n)
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/cses/1737/pseg.cpp
 */

template <typename N, typename T = int>
class persistent_sparse_segtree {
private:
    T ln, rn;
    int cur;
    vector<sparse_node<N, T>*> roots;

public:
    persistent_sparse_segtree(T _n = -1) {
        if (_n >= 0) init(_n);
    }

    persistent_sparse_segtree(T _ln, T _rn) {
        init(_ln, _rn);
    }

    void init(int _n) {
        init(0, _n - 1);
    }

    void init(int _ln, int _rn) {
        ln = _ln;
        rn = _rn;
        cur = 0;
        roots.push_back(new sparse_node<N, T>(ln, rn));
    }

    // returns latest version of the segtree
    int current() {
        return cur;
    }

    // copy segtree version t to version (1 + latest version)
    int copy_version(int t) {
        assert(0 <= t && t <= cur);
        roots.push_back(roots[t]->copy());
        return ++cur;
    }

    // copy latest segtree version to version (1 + latest version)
    int copy_current() {
        return copy_version(cur);
    }

    // update point x on segtree version t
    void update_version(int t, int x, const N& v) {
        assert(0 <= t && t <= cur);
        roots[t] = roots[t]->update_new(x, v);
    }

    // update point x on latest segtree version
    void update_current(int x, const N& v) {
        update_version(cur, x, v);
    }

    // query point x on segtree version t
    N query_version(int t, int x) {
        assert(0 <= t && t <= cur);
        return roots[t]->query(x);
    }

    // query point x on latest segtree version
    N query_current(int x) {
        return query_version(cur, x);
    }

    // query range [l, r] on segtree version t
    N query_version(int t, int l, int r) {
        assert(0 <= t && t <= cur);
        return roots[t]->query(l, r);
    }

    // query range [l, r] on latest segtree version
    N query_current(int l, int r) {
        return query_version(cur, l, r);
    }
};
