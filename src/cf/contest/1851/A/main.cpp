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
        int n, m, k, h; cin >> n >> m >> k >> h;
        int ans = 0;
        while (n--) {
            int z; cin >> z;
            if (abs(h - z) % k == 0 && abs(h - z) / k < m && h != z) ++ans;
        }
        cout << ans << '\n';
    }
}
