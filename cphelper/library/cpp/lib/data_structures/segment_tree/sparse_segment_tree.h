#include <bits/stdc++.h>
using namespace std;

/**
 * Sparse Segment Tree
 * Description:
 *    Segment Tree that does not allocate storage for nodes with no data.
 *    Node class must have default value(s) set and a static unite method.
 *    Range type (int, long long) can be changed.
 * Time Complexity:
 *     Update: O(log n)
 *     Query: O(log n)
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/usaco/2018/dec/plat/2/main.cpp
 */

template <typename N, typename T = int>
class sparse_node {
protected:
    T ll, rr;
    N data;
    sparse_node* c[2];

public:
    sparse_node(T _n) : sparse_node(0, _n - 1, N()) {}
    sparse_node(T _ll, T _rr) : sparse_node(_ll, _rr, N()) {}
    
    sparse_node(T _ll, T _rr, const N& _data) : ll(_ll), rr(_rr), data(_data) {
        c[0] = c[1] = nullptr;
    }

protected:
    inline void pull() {
        data = N::unite(c[0]->data, c[1]->data);
    }

    virtual inline void extend() {
        if (!c[0] && ll < rr) {
            int m = (ll + rr) >> 1;
            c[0] = new sparse_node(ll, m);
            c[1] = new sparse_node(m + 1, rr);
        }
    }

public:
    // copy node
    sparse_node* copy() {
        return new sparse_node(ll, rr, data);
    }

    // update point x
    void update(int x, const N& v) {
        extend();
        if (!c[0]) data = v;
        else c[x > c[0]->rr]->update(x, v), pull();
    }

    // returns an updated point x without overriding old point x
    sparse_node* update_new(int x, const N& v) {
        extend();
        sparse_node* d = new sparse_node(ll, rr);
        if (!c[0]) d->data = v;
        else {
            int w = x > c[0]->rr;
            d->c[w] = c[w]->update_new(x, v);
            d->c[1 - w] = c[1 - w];
            d->pull();
        }
        return d;
    }

    // query point x
    N query(int x) {
        extend();
        if (!c[0]) return data;
        else return c[x > c[0]->rr]->query(x);
    }

    // query range [l, r]
    N query(int l, int r) {
        if (l <= ll && rr <= r) return data;
        if (max(ll, l) > min(r, rr)) return N();
        extend();
        return N::unite(c[0]->query(l, r), c[1]->query(l, r));
    }
};
