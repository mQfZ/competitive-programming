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
    mint(long long _v) : v((int) (_v % md)) {
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

struct shield {
    int durability, threshold, index;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<int> a(n); for (auto& x : a) cin >> x;
    vector<shield> s(m);
    for (int i = 0; i < m; ++i) s[i].index = i, cin >> s[i].durability >> s[i].threshold;
    sort(a.begin(), a.end());
    sort(s.begin(), s.end(), [&](shield x, shield y) { return x.threshold < y.threshold; });
    long long sg = accumulate(a.begin(), a.end(), 0LL);
    long long ss = 0;
    int curr = 0;
    vector<mint> ans(m);
    for (shield sh : s) {
        while (curr < n && a[curr] < sh.threshold) ss += a[curr], sg -= a[curr], ++curr;
        mint exp = (mint) curr / (n - curr + 1) * min(sh.durability, n - curr + 1);
        ans[sh.index] = (mint) ss / curr * (curr - exp) + (mint) sg / (n - curr) * (n - curr - min(sh.durability, n - curr));
    }
    for (auto& x : ans) cout << x.v << '\n';
}
