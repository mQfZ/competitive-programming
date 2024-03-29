#include <bits/stdc++.h>
using namespace std;
#pragma once

/**
 * Disjoint Set Union
 * Description:
 *    Disjoint Set Union with path compression and union by size. Add edges 
 *    and test connectivity.
 * Time Complexity: O(alpha(n))
 * Verification: https://judge.yosupo.jp/submission/180951
 */

class dsu {
protected:
    int n;
    vector<int> e;

public:
    dsu(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    void init(int _n) {
        n = _n;
        e.assign(n, -1);
    }

    int get(int x) {
        return e[x] < 0 ? x : (e[x] = get(e[x]));
    }

    int size(int x) {
        return -e[get(x)];
    }

    bool unite(int x, int y) {
        x = get(x);
        y = get(y);
        if (x == y) return false;
        if (-e[x] < -e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};
