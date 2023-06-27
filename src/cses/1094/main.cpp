#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    int mx = 0;
    long long ans = 0;
    while (n--) {
        int x; cin >> x;
        if (mx < x) mx = x;
        else ans += mx - x;
    }
    cout << ans << '\n';
}
