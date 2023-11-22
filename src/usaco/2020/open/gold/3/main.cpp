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
 *    Basic modular arithmetic operations. Assumes mod is prime.
 * Verification: https://codeforces.com/contest/1279/submission/207090651
 */

int md = (int) 1e9 + 7;

struct mint {
    int v;
    
    mint() : v(0) {}
    mint(int _v) : v(_v % md) {
        if (v < 0) v += md;
    }

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
    mint& operator/=(mint o) {
        return (*this) *= inv(o);
    }
    
    friend mint pow(mint a, int p) {
        mint ans = 1;
        for (; p > 0; p /= 2, a *= a) {
            if (p & 1) ans *= a;
        }
        return ans;
    }
    friend mint inv(mint a) {
        return pow(a, md - 2);
    }
    
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
    friend mint operator/(mint a, mint b) { return a /= b; }
};

int main() {
    set_io("exercise");
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n >> md;
    vector<bool> prime(n + 1, true);
    for (int i = 2; i <= n; ++i) for (int j = 2 * i; j <= n; j += i) prime[j] = false;
    vector<mint> dp(n + 1, 1);
    for (int i = 2; i <= n; ++i) {
        if (!prime[i]) continue;
        vector<mint> ndp = dp;
        for (int j = 0; j <= n; ++j) {
            int p = i;
            while ((int) p <= j) ndp[j] += dp[j - p] * p, p *= i; 
        }
        dp = ndp;
    }
    cout << dp[n].v << '\n';
}
