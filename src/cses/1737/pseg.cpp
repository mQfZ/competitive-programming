#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

static char buf[450 << 20];
void* operator new(size_t s) {
    static size_t i = sizeof buf;
    assert(s < i);
    return (void*) & buf[i -= s];
}
void operator delete(void*) noexcept {}
void operator delete(void*, size_t) noexcept {}

/**
 * Sparse Segment Tree
 * Description:
 *    Segment Tree that does not allocate storage for nodes with no data.
 *    Node class must have default value(s) set and a static unite method.
 *    Range type (int, long long) can be changed.
 * Time Complexity:
 *     Update: O(log n)
 *     Query: O(log n)
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/usaco/2018/dec/plat/2/main.cpp
 */

template <typename N, typename T = int>
class sparse_node {
protected:
    T ll, rr;
    N data;
    sparse_node* c[2];

public:
    sparse_node(T _n) : sparse_node(0, _n - 1, N()) {}
    sparse_node(T _ll, T _rr) : sparse_node(_ll, _rr, N()) {}
    
    sparse_node(T _ll, T _rr, const N& _data) : ll(_ll), rr(_rr), data(_data) {
        c[0] = c[1] = nullptr;
    }

protected:
    inline void pull() {
        data = N::unite(c[0]->data, c[1]->data);
    }

    inline void extend() {
        if (!c[0] && ll < rr) {
            int m = (ll + rr) >> 1;
            c[0] = new sparse_node(ll, m);
            c[1] = new sparse_node(m + 1, rr);
        }
    }

public:
    // copy node
    sparse_node* copy() {
        sparse_node* d = new sparse_node(ll, rr, data);
        d->c[0] = c[0];
        d->c[1] = c[1];
        return d;
    }

    // update point x
    void update(int x, const N& v) {
        extend();
        if (!c[0]) data = v;
        else c[x > c[0]->rr]->update(x, v), pull();
    }

    // returns an updated point x without overriding old point x
    sparse_node* update_new(int x, const N& v) {
        extend();
        sparse_node* d = new sparse_node(ll, rr);
        if (!c[0]) d->data = v;
        else {
            int w = x > c[0]->rr;
            d->c[w] = c[w]->update_new(x, v);
            d->c[1 - w] = c[1 - w];
            d->pull();
        }
        return d;
    }

    // query point x
    N query(int x) {
        extend();
        if (!c[0]) return data;
        else return c[x > c[0]->rr]->query(x);
    }

    // query range [l, r]
    N query(int l, int r) {
        if (l <= ll && rr <= r) return data;
        if (max(ll, l) > min(r, rr)) return N();
        extend();
        return N::unite(c[0]->query(l, r), c[1]->query(l, r));
    }
};

/**
 * Persistent Sparse Segment Tree
 * Description:
 *    Persistent Sparse Segment Tree that does not allocate storage for nodes 
 *    with no data. Can point update and range query any version of the segment 
 *    tree. Node class must have default value(s) set and a static unite method.
 * Time Complexity:
 *     Update: O(log n)
 *     Query: O(log n)
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/usaco/2018/dec/plat/2/main.cpp
 */

template <typename N, typename T = int>
class persistent_sparse_segtree {
private:
    T ln, rn;
    int cur;
    vector<sparse_node<N, T>*> roots;

public:
    persistent_sparse_segtree(T _n = -1) {
        if (_n >= 0) init(_n);
    }

    persistent_sparse_segtree(T _ln, T _rn) {
        init(_ln, _rn);
    }

    void init(int _n) {
        init(0, _n - 1);
    }

    void init(int _ln, int _rn) {
        ln = _ln;
        rn = _rn;
        cur = 0;
        roots.push_back(new sparse_node<N, T>(ln, rn));
    }

    // returns latest version of the segtree
    int current() {
        return cur;
    }

    // copy segtree version t to version (1 + latest version)
    int copy_version(int t) {
        assert(0 <= t && t <= cur);
        roots.push_back(roots[t]->copy());
        return ++cur;
    }

    // copy latest segtree version to version (1 + latest version)
    int copy_current() {
        return copy_version(cur);
    }

    // update point x on segtree version t
    void update_version(int t, int x, const N& v) {
        assert(0 <= t && t <= cur);
        roots[t] = roots[t]->update_new(x, v);
    }

    // update point x on latest segtree version
    void update_current(int x, const N& v) {
        update_version(cur, x, v);
    }

    // query point x on segtree version t
    N query_version(int t, int x) {
        assert(0 <= t && t <= cur);
        return roots[t]->query(x);
    }

    // query point x on latest segtree version
    N query_current(int x) {
        return query_version(cur, x);
    }

    // query range [l, r] on segtree version t
    N query_version(int t, int l, int r) {
        assert(0 <= t && t <= cur);
        return roots[t]->query(l, r);
    }

    // query range [l, r] on latest segtree version
    N query_current(int l, int r) {
        return query_version(cur, l, r);
    }
};

struct node {
    // make sure to set default value for a node of size 0
    long long val = 0;

    // unite two nodes into one
    static node unite(const node& ln, const node& rn) {
        node res;
        res.val = ln.val + rn.val;
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, q; cin >> n >> q;
    vector<int> a(n); for (auto& x : a) cin >> x;
    persistent_sparse_segtree<node> pseg(n);
    for (int i = 0; i < n; ++i) {
        pseg.update_current(i, {a[i]});
    }
    while (q--) {
        int t, k; cin >> t >> k, --k;
        if (t == 1) {
            int l, v; cin >> l >> v, --l;
            pseg.update_version(k, l, {v});
        } else if (t == 2) {
            int l, r; cin >> l >> r, --l, --r;
            cout << pseg.query_version(k, l, r).val << '\n';
        } else if (t == 3) pseg.copy_version(k);
    }
}
