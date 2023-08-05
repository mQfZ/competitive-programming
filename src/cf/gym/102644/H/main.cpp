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

/**
 * Segment Tree
 * Description:
 *    1D point update and range query where unite is any associatve operation.
 * Time Complexity:
 *     Update: O(log n)
 *     Query: O(log n)
 * Verification: https://judge.yosupo.jp/submission/141445
 */

struct segtree {
    int n;
    struct node;
    vector<node> tree;

    segtree(int _n) : n(_n) {
        tree.resize(2 * n);
    }

    void pull(int p) {
        tree[p] = unite(tree[2 * p], tree[2 * p + 1]);
    }

    // update point i
    template <typename... Ts>
    void update(int x, const Ts&... val) {
        tree[x += n].apply(val...);
        for (x /= 2; x > 0; x /= 2) pull(x);
    }

    // query range [l, r]
    node query(int l, int r) {
        node ra, rb;
        for (l += n, r += n + 1; l < r; l /= 2, r /= 2) {
            if (l & 1) ra = unite(ra, tree[l++]);
            if (r & 1) rb = unite(tree[--r], rb);
        }
        return unite(ra, rb);
    }

    struct node {
        // make sure to set default value
        mint hh = 1, hs = 0, sh = 0, ss = 0;

        // apply value to node when updating
        void apply(char c) {
            if (c == 'H') hh = 1, hs = 0, sh = 1, ss = 0;
            else if (c == 'S' || c == 'D') hh = 0, hs = 1, sh = 0, ss = 1;
            else if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') hh = 0, hs = 1, sh = 1, ss = 0;
            else if (c == '?') hh = 19, hs = 7, sh = 6, ss = 20;
            else hh = 1, hs = 0, sh = 0, ss = 1;
        }
    };
    
    // unite two nodes into one
    node unite(const node& a, const node& b) {
        node res;
        res.hh = a.hh * b.hh + a.hs * b.sh;
        res.hs = a.hh * b.hs + a.hs * b.ss;
        res.sh = a.ss * b.sh + a.sh * b.hh;
        res.ss = a.ss * b.ss + a.sh * b.hs;
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;
    string s; cin >> s;
    segtree st(n);
    for (int i = 0; i < n; ++i) st.update(i, s[i]);
    cout << st.query(0, n - 1).hh.v << '\n';
    while (q--) {
        int x; char c; cin >> x >> c, --x;
        st.update(x, c);
        cout << st.query(0, n - 1).hh.v << '\n';
    }
}
