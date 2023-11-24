#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

void set_io(string s) {
#ifndef LOCAL
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
#endif
}

/**
 * 2D Fenwick Tree
 * Description:
 *    2D point increment/update and rectangle query where the operation is 
 *    invertible (addition, multiplication). Can also be rectangle update 
 *    and point query.
 * Time Complexity:
 *    Update: O(log n * log m)
 *    Query: O(log n * log m)
 * Verification:
 *     https://github.com/mQfZ/competitive-programming/blob/master/src/usaco/2017/open/plat/1/main.cpp
 *     https://github.com/mQfZ/competitive-programming/blob/master/src/cses/1739/main.cpp
 */

template <typename T>
struct fenwick2d {
    int n, m;
    vector<vector<T>> tree;

    fenwick2d(int _n = -1, int _m = -1) {
        if (_n >= 0 && _m >= 0) init(_n, _m);
    }

    void init(int _n, int _m) {
        n = _n;
        m = _m;
        tree.assign(n, vector<T>(m, {}));
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
    set_io("art");
    ios::sync_with_stdio(0); cin.tie(0);
    const int inf = (int) 1e9 + 10;
    int n; cin >> n;
    vector<vector<int>> a(n, vector<int>(n));
    for (auto& x : a) for (auto& y : x) cin >> y, --y;
    vector<pair<pair<int, int>, pair<int, int>>> b(n * n, {{inf, inf}, {-1, -1}});
    vector<bool> colors(n * n);
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
        int x = a[i][j];
        if (x == -1) continue;
        colors[x] = true;
        b[x].first.first = min(b[x].first.first, i);
        b[x].first.second = min(b[x].first.second, j);
        b[x].second.first = max(b[x].second.first, i);
        b[x].second.second = max(b[x].second.second, j);
    }
    if (accumulate(colors.begin(), colors.end(), 0) == 1) {
        cout << n * n - 1 << '\n';
        return 0;
    }
    fenwick2d<int> fw(n, n);
    for (int i = 0; i < n * n; ++i) {
        if (b[i].first.first == inf) continue;
        fw.update(b[i].first.first, b[i].first.second, 1);
        fw.update(b[i].second.first + 1, b[i].first.second, -1);
        fw.update(b[i].first.first, b[i].second.second + 1, -1);
        fw.update(b[i].second.first + 1, b[i].second.second + 1, 1);
    }
    vector<bool> pos(n * n, true);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j] == -1) continue;
            if (fw.query(i, j) != 1) pos[a[i][j]] = false;
        }
    }
    cout << accumulate(pos.begin(), pos.end(), 0) << '\n';
}
