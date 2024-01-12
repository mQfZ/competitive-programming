#include <bits/stdc++.h>
using namespace std;
#pragma once
/**
 * Addition Segment Tree Node
 * Description:
 *    Segment Tree Node that allows for addition.
 * Time Complexity: N/A
 * Verification: N/A
 */

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
