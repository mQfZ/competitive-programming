#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

/**
 * Modular Integer
 * Description:
 *    Basic modular arithmetic operations (excluding division).
 * Verification: https://codeforces.com/contest/1279/submission/207090651
 */

const int md = (int) 1e9 + 7;

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

const int m = 4;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string s; cin >> s;
    int n = (int) s.size();
    vector<vector<int>> a(n);
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'A' || s[i] == '?') a[i].push_back(0);
        if (s[i] == 'C' || s[i] == '?') a[i].push_back(1);
        if (s[i] == 'G' || s[i] == '?') a[i].push_back(2);
        if (s[i] == 'T' || s[i] == '?') a[i].push_back(3);
    }
    vector dp(vector(n, vector(m, vector(m, vector(m, (mint) 0)))));
    for (int pl = 0; pl < m; ++pl) for (int l : a[0]) dp[0][pl][l][l] = 1;
    for (int i = 1; i < n; ++i) {
        for (int c : a[i]) for (int pl = 0; pl < m; ++pl)
        for (int l = 0; l < m; ++l) for (int r = 0; r < m; ++r) {
            if (r != c) dp[i][pl][l][c] += dp[i - 1][pl][l][r];
            if (pl == r) dp[i][l][c][c] += dp[i - 1][pl][l][r];    
        }
    }
    mint ans = 0;
    for (int l = 0; l < m; ++l) for (int r = 0; r < m; ++r) ans += dp[n - 1][r][l][r];
    cout << ans.v << '\n';
}
