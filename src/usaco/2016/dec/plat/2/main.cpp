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
 * Modular Integer
 * Description:
 *    Basic modular arithmetic operations (excluding division).
 * Verification: https://codeforces.com/contest/1279/submission/207090651
 */

const int md = (int) 1e9 + 9;

struct mint {
    int v;
    
    mint() : v(0) {}
    mint(int _v) : v(_v % md) {}

    mint& operator+=(mint o) {
        if ((v += o.v) >= md) v -= md;
        return *this;
    }
    mint& operator-=(mint o) {
        if ((v -= o.v) < 0) v += md;
        return *this;
    }
    mint& operator*=(mint o) {
        v = (int) (((long long) v * o.v) % md);
        return *this;
    }
    
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
};

int main() {
    set_io("team");

    ios::sync_with_stdio(0); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    vector<int> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    vector<vector<vector<mint>>> dp(n + 1, vector<vector<mint>>(m + 1, vector<mint>(k + 1)));
    for (int i = 0; i <= n; ++i) dp[i][0][0] = 1;
    for (int j = 0; j <= m; ++j) dp[0][j][0] = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            for (int d = 0; d <= k; ++d) {
                dp[i][j][d] = (a[i - 1] > b[j - 1] && d > 0 ? dp[i - 1][j - 1][d - 1] : 0)
                                + dp[i - 1][j][d] + dp[i][j - 1][d] - dp[i - 1][j - 1][d];
            }
        }
    }
    cout << dp[n][m][k].v << '\n';
}
