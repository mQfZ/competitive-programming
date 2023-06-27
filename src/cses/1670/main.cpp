#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    array<int, 9> a;
    for (int i = 0; i < 9; ++i) cin >> a[i];
    unordered_map<int, bool> vis;
    queue<pair<array<int, 9>, int>> q;
    q.push({{1, 2, 3, 4, 5, 6, 7, 8, 9}, 0});
    const vector<pair<int, int>> swaps = {
        {0, 1}, {1, 2}, {3, 4}, {4, 5}, {6, 7}, {7, 8},
        {0, 3}, {1, 4}, {2, 5}, {3, 6}, {4, 7}, {5, 8}
    };
    vector<int> pow9(9);
    pow9[0] = 1;
    for (int i = 1; i < 9; ++i) {
        pow9[i] = pow9[i - 1] * 9;
    }
    auto hash = [&](array<int, 9> v) {
        int r = 0;
        for (int i = 0; i < 9; ++i) {
            r += pow9[i] * v[i];
        }
        return r;
    };
    while (!q.empty()) {
        auto [v, s] = q.front(); q.pop();
        if (v == a) {
            cout << s << '\n';
            return 0;
        }
        for (auto [x, y] : swaps) {
            swap(v[x], v[y]);
            auto h = hash(v);
            if (!vis[h]) vis[h] = true, q.push({v, s + 1});
            swap(v[x], v[y]);
        }
    }
}
