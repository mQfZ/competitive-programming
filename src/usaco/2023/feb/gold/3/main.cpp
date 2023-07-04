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
 *    Basic modular arithmetic operations (excluding division)
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

int cmp(int x, char c) {
    if (x < c - '0') return 0;
    if (x > c - '0') return 2;
    return 1;
}

vector<vector<mint>> solve(vector<int>& c, long long a) {
    string sa = to_string(a);
    int n = (int) c.size(), ss = (int) sa.size();
    vector<vector<mint>> ans(n, vector<mint>(n));
    vector dp(n + 1, vector(ss + 1, vector(ss + 1, vector(3, (mint) 0))));
    for (int l = 0; l <= ss; ++l) dp[0][l][l][1] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            int v = j - i + 1;
            dp[v] = dp[v - 1];
            for (int s = 0; s <= ss; ++s) {
                for (int l = 0; l <= ss - s; ++l) {
                    int r = l + s;
                    for (int f = 0; f < 3; ++f) dp[v][l][r][f] = dp[v - 1][l][r][f];
                    if (s == 0) continue;
                    int lf = cmp(c[j], sa[l]);
                    if (lf == 1) for (int f = 0; f < 3; ++f) dp[v][l][r][f] += dp[v - 1][l + 1][r][f];
                    else for (int f = 0; f < 3; ++f) dp[v][l][r][lf] += dp[v - 1][l + 1][r][f];
                    int rf = cmp(c[j], sa[r - 1]);
                    for (int f = 0; f < 3; ++f) {
                        if (f == 1) dp[v][l][r][rf] += dp[v - 1][l][r - 1][f];
                        else dp[v][l][r][f] += dp[v - 1][l][r - 1][f];
                    }
                }
            }
            for (int s = 0; s < ss; ++s) {
                for (int f = 0; f < 3; ++f) ans[i][j] += dp[v][0][s][f];
            }
            ans[i][j] += dp[v][0][ss][0] + dp[v][0][ss][1];
        }
    }
    return ans;
}


int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; long long a, b; cin >> n >> a >> b;
    vector<int> c(n); for (auto& x : c) cin >> x;
    auto smaller = solve(c, a - 1);
    auto larger = solve(c, b);
    int q; cin >> q;
    while (q--) {
        int x, y; cin >> x >> y, --x, --y;
        cout << (larger[x][y] - smaller[x][y]).v << '\n';
    }
}
