#include <bits/stdc++.h>
using namespace std;

/**
 * Sparse Segment Tree
 * Description:
 *    Segment Tree that does not allocate storage for nodes with no data.
 *    sparseseg represents the segtree node, node represents the data.
 * Time Complexity:
 *     Update: O(log n)
 *     Query: O(log n)
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/usaco/2018/dec/plat/2/main.cpp
 */

class sparseseg {
private:
    int ll, rr;  // [ll, rr]
    sparseseg* c[2];  // c[0] = left child, c[1] = right child

public:
    struct node;

    sparseseg(int _ll, int _rr) : ll(_ll), rr(_rr) {
        c[0] = c[1] = nullptr;
    }

private:
    // create child nodes (if necessary)
    void extend() {
        if (!c[0] && ll < rr) {
            int m = (ll + rr) >> 1;
            c[0] = new sparseseg(ll, m);
            c[1] = new sparseseg(m + 1, rr);
        }
    }

public:
    // update point x
    template <typename... Ts>
    void update(int x, const Ts&... v) {
        extend();
        if (!c[0]) nv.apply(v...);
        else c[x > c[0]->rr]->update(x, v...), pull();
    }

    // query range [l, r]
    node query(int l, int r) {
        if (l <= ll && rr <= r) return nv;
        if (max(ll, l) > min(r, rr)) return sparseseg(max(ll, l), min(rr, r)).nv;
        extend();
        return unite(c[0]->query(l, r), c[1]->query(l, r));
    }

    struct node {
        // make sure to set default value
        long long val = 0;
        
        // apply value to node when updating
        void apply(long long z) {
            val += z;
        };
    } nv;

    // unite two nodes into one
    node unite(const node& a, const node& b) {
        node res;
        res.val = a.val + b.val;
        return res;
    }

private:
    // pull child nodes into parent node
    inline void pull() {
        nv = unite(c[0]->nv, c[1]->nv);
    }
};
