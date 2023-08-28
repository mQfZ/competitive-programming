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

void read(vector<int>& s) {
    string t; cin >> t;
    for (char c : t) {
        if (c == '1') continue;
        if (c == '0') s.clear();
        s.push_back(c != '+' ? 1 : 0);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        int n; cin >> n;
        vector<int> a, b;
        read(a); read(b);
        int as = (int) a.size(), bs = (int) b.size();
        vector<vector<vector<mint>>> dp(as + 1, vector<vector<mint>>(bs + 1, {0, 0}));
        for (int i = 0; i <= as; ++i) dp[i][0][0] = 1;
        for (int j = 1; j <= bs; ++j) dp[0][j][1] = 1;
        for (int i = 1; i <= as; ++i) {
            for (int j = 1; j <= bs; ++j) {
                dp[i][j][0] += dp[i - 1][j][0];
                dp[i][j][1] += dp[i][j - 1][0] + dp[i][j - 1][1];
                if (a[i - 1] != b[j - 1]) dp[i][j][0] += dp[i - 1][j][1];
            }
        }
        cout << (dp[as][bs][0] + dp[as][bs][1]).v << '\n';
    }
}
