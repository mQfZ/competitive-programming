#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<int> a(n); for (auto& x : a) cin >> x;
    a.push_back(0);
    sort(a.begin(), a.end());
    vector<vector<mint>> dp(n, vector<mint>(k + 1));
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        vector<vector<mint>> ndp(n, vector<mint>(k + 1));
        for (int j = 0; j <= i; ++j) {
            for (int p = 0; p <= k; ++p) {
                if (dp[j][p].v == 0) continue;
                int np = p + j * (a[i + 1] - a[i]);
                if (np <= k) {
                    if (j > 0) ndp[j - 1][np] += dp[j][p] * j;
                    ndp[j][np] += dp[j][p] * (j + 1);
                    if (j < n - 1) ndp[j + 1][np] += dp[j][p];
                }
            }
        }
        dp = ndp;
    }
    cout << accumulate(dp[0].begin(), dp[0].end(), (mint) 0).v << '\n';
}
