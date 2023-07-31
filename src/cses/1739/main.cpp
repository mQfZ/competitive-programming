#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

/**
 * 2D Fenwick Tree
 * Description:
 *    2D point increment/update and rectangle query where the operation is 
 *    invertible (addition, multiplication). Can also be rectangle update 
 *    and point query.
 * Time Complexity:
 *    Update: O(log n)
 *    Query: O(log n)
 * Verification:
 *     https://github.com/mQfZ/competitive-programming/blob/master/src/usaco/2017/open/plat/1/main.cpp
 *     https://github.com/mQfZ/competitive-programming/blob/master/src/cses/1739/main.cpp
 */

template <typename T>
struct fenwick2d {
    int n, m;
    vector<vector<T>> tree;

    fenwick2d(int _n, int _m) : n(_n), m(_m) {
        tree.resize(n, vector<int>(m));
    }

    // update point (x, y)
    void update(int x, int y, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            for (int j = y + 1; j <= m; j += j & -j) {
                tree[i - 1][j - 1] += v;
            }
        }
    }

    // query rectangle [(0, 0), (x, y)]
    T query(int x, int y) {
        T total = {};
        for (int i = x + 1; i > 0; i -= i & -i) {
            for (int j = y + 1; j > 0; j -= j & -j) {
                total += tree[i - 1][j - 1];
            }
        }
        return total;
    }
    
    // query rectangle [(x1, y1), (x2, y2)]
    T query(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x1 - 1, y2)
               - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;
    vector<vector<int>> a(n, vector<int>(n));
    fenwick2d<int> fw(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char c; cin >> c; a[i][j] = c == '*';
            if (a[i][j]) fw.update(i, j, 1);
        }
    }
    while (q--) {
        int t, x1, y1, y2, x2; cin >> t >> x1 >> y1, --x1, --y1;
        if (t == 1) fw.update(x1, y1, 1 - 2 * a[x1][y1]), a[x1][y1] = 1 - a[x1][y1];
        if (t == 2) cin >> x2 >> y2, --x2, --y2, cout << fw.query(x1, y1, x2, y2) << '\n';
    }
}
