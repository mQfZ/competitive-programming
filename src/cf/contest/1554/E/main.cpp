#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template <class Fun>
class y_combinator_result {
    Fun fun_;
  public:
    template <class T>
    explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

    template <class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

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
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        int n; cin >> n;
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) {
            int x, y; cin >> x >> y;
            adj[x - 1].push_back(y - 1);
            adj[y - 1].push_back(x - 1);
        }
        vector<mint> ans(n + 1);
        ans[1] = pow((mint) 2, n - 1);
        for (int ec = n; ec >= 2; --ec) {
            if ((n - 1) % ec != 0) continue;
            int remainder = y_combinator([&](auto self, int v, int pv) -> int {
                int value = 0;
                bool possible = true;
                for (int nv : adj[v]) {
                    if (nv != pv) {
                        int nrem = self(nv, v);
                        if (nrem % ec == 0) ++value;
                        else if (nrem % ec != ec - 1) possible = false;
                    }
                }
                if (!possible) value = -1;
                return value;
            })(0, -1);
            if (remainder % ec == 0) ans[ec] = 1;
            for (int m = 2 * ec; m <= n; m += ec) ans[ec] -= ans[m];
        }
        for (int m = 2; m <= n; ++m) ans[1] -= ans[m];
        for (int i = 1; i <= n; ++i) cout << ans[i].v << " \n"[i == n];
    }
}
