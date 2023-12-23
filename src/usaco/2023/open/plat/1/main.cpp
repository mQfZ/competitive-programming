#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

/**
 * Segment Tree
 * Description:
 *    1D point update and range query where unite is any associatve operation.
 * Time Complexity:
 *     Update: O(log n)
 *     Query: O(log n)
 * Verification: https://judge.yosupo.jp/submission/173605
 */

const string u = "bessie";
const int sz = (int) u.size();

struct segtree {
    int n;
    struct node;
    vector<node> tree;

    segtree(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    void init(int _n) {
        n = _n;
        tree.assign(2 * n, {});
    }

    void pull(int p) {
        tree[p] = unite(tree[2 * p], tree[2 * p + 1]);
    }

    // update point x
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
        vector<long long> mp = vector<long long>(sz);
        vector<long long> c = vector<long long>(sz);
        vector<long long> f = vector<long long>(sz);
        long long fix = 0;

        // apply value to node when updating
        void apply(char nc, int tt) {
            fill(mp.begin(), mp.end(), 0);
            fill(c.begin(), c.end(), 0);
            fill(f.begin(), f.end(), 0);
            for (int i = 0; i < sz; ++i) mp[i] = (i + (nc == u[i])) % sz;
            f[mp[0]] = 1;
            if (mp[sz - 1] == 0) c[sz - 1] = tt;
        }
    };
    
    // unite two nodes into one
    node unite(node& a, node& b) {
        node res;
        res.fix = a.fix + b.fix;
        for (int i = 0; i < sz; ++i) {
            res.mp[i] = b.mp[a.mp[i]];
            res.c[i] = a.c[i] + b.c[a.mp[i]];
            res.f[b.mp[i]] += a.f[i];
            res.f[i] += b.f[i];
            res.fix += b.c[i] * a.f[i]; 
        }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string s; cin >> s;
    int n = (int) s.size();
    segtree st(n);
    for (int i = 0; i < n; ++i) st.update(i, s[i], n - i);
    cout << st.query(0, n - 1).fix << '\n';
    int tq; cin >> tq;
    while (tq--) {
        int x; char c; cin >> x >> c, --x;
        st.update(x, c, n - x);
        cout << st.query(0, n - 1).fix << '\n';
    }
}
