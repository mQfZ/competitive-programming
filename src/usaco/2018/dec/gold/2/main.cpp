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

int main() {
    set_io("cowpatibility");
    ios::sync_with_stdio(0); cin.tie(0);
    const int g = 10, m = 5, mx = (int) 5e4 + 10, md = (int) 5e6 + 10;
    int n; cin >> n;
    vector<vector<int>> ind(md);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int x; cin >> x;
            ind[x].push_back(i);
        }
    }
    vector<bitset<mx>> bs(n / g + 1);
    long long ans = 0;
    for (int i = 0; i < g; ++i) {
        for (auto& v : ind) {
            if (v.size() == 0) continue;
            bitset<mx> b;
            for (int x : v) b[x] = 1;
            for (int x : v) if ((i * n) / g <= x && x < (i * n + n) / g) bs[x - (i * n) / g] |= b;
        }
        for (auto& x : bs) ans += x.count(), x.reset();
    }
    cout << ((long long) n * n - ans) / 2 << '\n';
}
