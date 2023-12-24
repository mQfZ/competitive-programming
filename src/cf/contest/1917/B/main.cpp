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
        int n; string s; cin >> n >> s;
        map<char, bool> seen;
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            if (!seen[s[i]]) {
                seen[s[i]] = true;
                ans += n - i;
            }
        }
        cout << ans << '\n';
    }
}
