#include <bits/stdc++.h>
using namespace std;
#pragma once

/**
 * Lazy Addition Segment Tree Node
 * Description:
 *    Lazy Segment Tree Node that allows range addition.
 * Time Complexity: N/A
 * Verification: N/A
 */

struct update {
    bool operator==(const update& other) const = default;

    // make sure to set default value for an identity update
    long long add = 0;

    // extend propagated data (two updates into one)
    void extend(const update& np) {
        add += np.add;
    }
};

struct node {
    // make sure to set default value for a node of size 0
    // when initializing the nodes, make sure to set the size to 1
    //  changing size to l, r to find the bounds of the node is also possible
    int size = 0;
    long long val = 0;

    // apply propagated update to node
    void apply_update(const update& p) {
        val += p.add * size;
    }

    // unite left node and right node into parent node
    static node unite(const node& ln, const node& rn) {
        node res;
        res.size = ln.size + rn.size;
        res.val = ln.val + rn.val;
        return res;
    }
};
