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
        int ans = 0;
        while (n--) {
            int x, y; cin >> x >> y;
            if (x > y) ++ans;
        }
        cout << ans << '\n';
    }
}
