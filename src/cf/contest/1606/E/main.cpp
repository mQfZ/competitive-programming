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
 *    Basic modular arithmetic operations. Assumes mod is prime.
 * Verification: https://codeforces.com/contest/1279/submission/207090651
 */

const int md = 998244353;

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

    friend ostream& operator<<(ostream& x, mint a) { return x << a.v; }
};

/**
 * Combinatorics
 * Description:
 *    Pre compute factorial and modular inverses. Assumes mod is prime.
 * Time Complexity: O(n)
 * Verification: https://codeforces.com/contest/1462/submission/207091126
 */

vector<mint> fact;
vector<mint> inv_fact;

void gen_fact(int n) {
    if (fact.size() == 0) fact = inv_fact = {1};
    while ((int) fact.size() <= n) {
        fact.push_back(fact.back() * (int) fact.size());
        inv_fact.push_back(1 / fact.back());
    }
}

mint F(int n) {
    gen_fact(n);
    return fact[n];
}

mint C(int n, int k) {
    if (k < 0 || k > n) return 0;
    gen_fact(n);
    return fact[n] * inv_fact[k] * inv_fact[n - k];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, x; cin >> n >> x;
    vector<vector<mint>> dp(n + 1, vector<mint>(x + 1));
    for (int i = 1; i <= x; ++i) dp[1][i] = 1;
    for (int s = 2; s <= n; ++s) {
        for (int h = s; h <= x; ++h) {
            mint v = 0;
            for (int sm = 0; sm < s; ++sm) {
                v += C(s, sm) * pow((mint) s - 1, sm) * dp[s - sm][h - s + 1];
            }
            dp[s][h] = v;
        }
    }
    for (int i = 0; i <= n; ++i) dbgn(dp[i]);
    cout << (pow((mint) x, n) - accumulate(dp[n].begin(), dp[n].end(), (mint) 0)).v << '\n';
}
