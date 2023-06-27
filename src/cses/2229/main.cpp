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
    vector<mint> dp(k + 1);
    dp[0] = 1;
    for (int i = 1; i <= n; ++i) {
        vector<mint> ndp(k + 1);
        for (int j = 0; j <= k; ++j) {
            ndp[j] = dp[j];
            if (j > 0) ndp[j] += ndp[j - 1];
            if (j >= i) ndp[j] -= dp[j - i];
        }
        dp = ndp;
    }
    cout << dp[k].v << '\n';
}
