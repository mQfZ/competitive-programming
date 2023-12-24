#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        int n; cin >> n;
        vector<int> a(n); for (auto& x : a) cin >> x;
        int inv = 0, zero = 0;
        for (int i = 0; i < n; ++i) { if (a[i] < 0) ++inv; if (a[i] == 0) ++zero; }
        if (inv % 2 == 0 && zero == 0) cout << 1 << '\n' << 1 << ' ' << 0 << '\n';
        else cout << 0 << '\n';
    }
}
