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

const int md = (int) 1e9 + 7;

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
    friend ostream& operator<<(ostream& o, mint a) { return o << a.v; }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<string> a(m); for (auto& x : a) cin >> x;
    vector<int> c(1 << m);
    for (int i = 0; i < n; ++i) {
        int b = 0;
        for (int j = 0; j < m; ++j) b += (a[j][i] == 'H') << j;
        ++c[b];
    }
    vector<mint> order(n + 1);
    order[0] = 1;
    for (int i = 1; i <= n; ++i) order[i] = order[i - 1] * i + 1;
    vector<mint> dp(1 << m);
    vector<vector<mint>> sdp(1 << m, vector<mint>(m));
	mint ans = 0;
	for (int i = 0; i < 1 << m; ++i) {
        dp[i] = order[c[i]] - 1;
		for (int j = 0; j < m; ++j) {
			if (i & (1 << j)) dp[i] += sdp[i ^ (1 << j)][j] * (order[c[i]] - 1);
		}
		ans = ans + dp[i];
		sdp[i][0] = dp[i];
		for (int j = 0; j < m - 1; ++j) {
			sdp[i][j + 1] = sdp[i][j];
			if (i & (1 << j)) sdp[i][j + 1] += sdp[i ^ (1 << j)][j];
		}
	}
	cout << ans.v << '\n';
}
