#include <bits/stdc++.h>
using namespace std;

/**
 * Sparse Segment Tree
 * Description:
 *    Segment Tree that does not allocate storage for nodes with no data.
 *    Node class must have default value(s) set and a static unite method.
 * Time Complexity:
 *     Update: O(log n)
 *     Query: O(log n)
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/usaco/2018/dec/plat/2/main.cpp
 */

template <typename N>
class sparse_node {
private:
    int ll, rr;
    N data;
    sparse_node* c[2];

public:
    sparse_node(int _ll, int _rr) : sparse_node(_ll, _rr, N()) {}
    
    sparse_node(int _ll, int _rr, const N& _data) : ll(_ll), rr(_rr), data(_data) {
        c[0] = c[1] = nullptr;
    }

private:
    inline void pull() {
        data = N::unite(c[0]->data, c[1]->data);
    }

    void extend() {
        if (!c[0] && ll < rr) {
            int m = (ll + rr) >> 1;
            c[0] = new sparse_node(ll, m);
            c[1] = new sparse_node(m + 1, rr);
        }
    }

public:
    // update point x
    void update(int x, const N& v) {
        extend();
        if (!c[0]) data = v;
        else c[x > c[0]->rr]->update(x, v), pull();
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

struct node {
    // make sure to set default value for a node of size 0
    long long val = 0;

    // unite two nodes into one
    static node unite(const node& ln, const node& rn) {
        node res;
        res.val = ln.val + rn.val;
        return res;
    }
};
