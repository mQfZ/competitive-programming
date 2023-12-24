#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

/**
 * Fenwick Tree
 * Description:
 *    1D point increment/update and rectangle query where the operation is 
 *    invertible (addition, multiplication). Can also be range update and 
 *    point query.
 * Time Complexity:
 *    Update: O(log n)
 *    Query: O(log n)
 * Verification: https://judge.yosupo.jp/submission/173798
 */

template <typename T>
struct fenwick {
    int n;
    vector<T> tree;

    fenwick(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    void init(int _n) {
        n = _n;
        tree.assign(n, {});
    }

    // increment point x by v
    void add(int x, T v) {
        for (++x; x <= n; x += x & -x) {
            tree[x - 1] += v;
        }
    }

    // query range [0, x]
    T query(int x) {
        T total = 0;
        for (++x; x > 0; x -= x & -x) {
            total += tree[x - 1];
        }
        return total;
    }
    
    // query range [l, r]
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

/**
 * Modular Integer
 * Description:
 *    Basic modular arithmetic operations (excluding division).
 * Verification: https://codeforces.com/contest/1279/submission/207090651
 */

const int md = 998244353;

struct mint {
    int v;
    
    mint() : v(0) {}
    mint(long long _v) : v((int) (_v % md)) {}

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
    int tt; cin >> tt;
    while (tt--) {
        int n, k; cin >> n >> k;
        vector<int> p(n); for (auto& x : p) cin >> x;
        vector<int> q(k); for (auto& x : q) cin >> x;
        fenwick<mint> fw(k);
        mint inside = 0;
        for (int i = 0; i < k; ++i) {
            inside += i - fw.query(q[i]);
            fw.add(q[i], 1);
        }
        inside *= n;
        mint outside = 0;
        fenwick<mint> ft(4 * n);
        for (int i = 0; i < n; ++i) {
            int z = p[i];
            mint vv = (mint) ((long long) k * (k - 1) / 2);
            int dx = k - 1;
            while (true) {
                mint num = ft.query(z / 2 + 1, z);
                outside += num * vv;
                vv -= dx;
                if (dx > 0) dx -= 1;
                if (z == 0) break;
                z /= 2;
            }
            z = p[i];
            vv = (mint) ((long long) k * (k + 1) / 2);
            dx = k - 1;
            while (true) {
                mint num = ft.query(z, 2 * z);
                outside += num * vv;
                vv += dx;
                if (dx > 0) dx -= 1;
                if (2 * z > 2 * n - 1) break;
                z *= 2;
            }
            ft.add(p[i], 1);
        }
        cout << (inside + outside).v << '\n';
    }
}
