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
        long long x, y, k; cin >> x >> y >> k;
        cout << (k * (x + y) + x - 3) / (x - 1) << '\n';
    }
}
