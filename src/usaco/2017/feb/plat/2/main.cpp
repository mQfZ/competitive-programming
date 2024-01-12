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
 * Segment Tree
 * Description:
 *    1D point update and range query where unite is any associatve operation.
 *    Node class must have default value(s) set and a static unite method.
 * Time Complexity:
 *     Build: O(n)
 *     Update: O(log n)
 *     Query: O(log n)
 * Verification: https://judge.yosupo.jp/submission/182462
 */

template <typename N>
class segtree {
private:
    int n;
    vector<N> tree;

public:
    segtree(int _n = -1) {
        if (_n >= 0) init(_n);
    }

    segtree(const vector<N>& v) {
        init(v);
    }

    void init(int _n) {
        init(vector<N>(_n, N {}));
    }

    void init(const vector<N>& v) {
        n = (int) v.size();
        tree.assign(2 * n, {});
        build(v);
    }

private:
    inline void pull(int p) {
        tree[p] = N::unite(tree[2 * p], tree[2 * p + 1]);
    }

    inline void pull_single(int x) {
        for (x >>= 1; x > 0; x >>= 1) pull(x);
    }

    void build(const vector<N>& v) {
        for (int i = 0; i < n; ++i) tree[i + n] = v[i];
        for (int i = n - 1; i > 0; --i) pull(i);
    }

public:
    // update point x
    void update(int x, N v) {
        assert(0 <= x && x < n);
        x += n;
        tree[x] = v;
        pull_single(x);
    }

    // query point x
    N query(int x) {
        assert(0 <= x && x < n);
        x += n;
        return tree[x];
    }

    // query range [l, r]
    N query(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        N ra = {}, rb = {};
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ra = N::unite(ra, tree[l++]);
            if (r & 1) rb = N::unite(tree[--r], rb);
        }
        return N::unite(ra, rb);
    }
};

struct node {
    // make sure to set default value for a node of size 0
    int val = 0;

    // unite two nodes into one
    static node unite(const node& a, const node& b) {
        node res;
        res.val = max(a.val, b.val);
        return res;
    }
};

int main() {
    set_io("nocross");
    ios::sync_with_stdio(0); cin.tie(0);
    const int k = 4;
    int n; cin >> n;
    vector<int> a(n); for (auto& x : a) cin >> x, --x;
    vector<int> b(n); for (auto& x : b) cin >> x, --x;
    vector<int> pb(n); for (int i = 0; i < n; ++i) pb[b[i]] = i;
    segtree<node> st(n + 1);
    for (int i = 0; i < n; ++i) {
        vector<int> con;
        for (int z = max(0, a[i] - k); z <= min(n - 1, a[i] + k); ++z) {
            con.push_back(pb[z]);
        }
        sort(con.begin(), con.end());
        reverse(con.begin(), con.end());
        for (int v : con) {
            int t = st.query(0, v).val + 1;
            if (st.query(v + 1).val < t) st.update(v + 1, {t});
        }
    }
    cout << st.query(0, n).val << '\n';
}
