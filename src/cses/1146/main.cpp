#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    long long n; cin >> n;
    long long a = 0, c = 0, ans = 0;
    for (int p = 50; p >= 0; --p) {
        if (a + (1LL << p) <= n + 1) {
            ans += c * (1LL << p) + p * (1LL << (p - 1));
            a += 1LL << p;
            ++c;
        }
    }
    cout << ans << '\n';
}
