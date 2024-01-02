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

const long long inf = (long long) 2e18 + 10;

/**
 * Sparse Segment Tree
 * Description:
 *    Segment Tree that does not allocate storage for nodes with no data.
 *    segnode represents the segtree node, node represents the data.
 * Time Complexity:
 *     Update: O(log n)
 *     Query: O(log n)
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/usaco/2018/dec/plat/2/main.cpp
 */

class sparseseg {
private:
    int ll, rr;  // [ll, rr]
    sparseseg* c[2];  // c[0] = left child, c[1] = right child

public:
    struct node;

    sparseseg(int _ll, int _rr) : ll(_ll), rr(_rr) {
        c[0] = c[1] = nullptr;
    }

private:
    // create child nodes (if necessary)
    void extend() {
        if (!c[0] && ll < rr) {
            int m = (ll + rr) >> 1;
            c[0] = new sparseseg(ll, m);
            c[1] = new sparseseg(m + 1, rr);
        }
    }

public:
    // update point x
    template <typename... Ts>
    void update(int x, const Ts&... v) {
        extend();
        if (!c[0]) nv.apply(v...);
        else c[x > c[0]->rr]->update(x, v...), pull();
    }

    // query range [l, r]
    node query(int l, int r) {
        if (l <= ll && rr <= r) return nv;
        if (max(ll, l) > min(r, rr)) return sparseseg(max(ll, l), min(rr, r)).nv;
        extend();
        return unite(c[0]->query(l, r), c[1]->query(l, r));
    }

    struct node {
        // make sure to set default value
        long long val = 0;
        
        // apply value to node when updating
        void apply(long long z) {
            val = z;
        };
    } nv;

    // unite two nodes into one
    node unite(const node& a, const node& b) {
        node res;
        res.val = min(a.val + b.val, inf);
        return res;
    }

private:
    // pull child nodes into parent node
    inline void pull() {
        nv = unite(c[0]->nv, c[1]->nv);
    }
};

int main() {
    set_io("itout");
    ios::sync_with_stdio(0); cin.tie(0);
    int n; long long k; cin >> n >> k;
    vector<int> a(n); for (auto& x : a) cin >> x, --x;
    a.push_back(n);
    vector<int> max_length(n + 1), stk(n + 1, -1);
    vector<long long> dp(n + 1);
    vector<sparseseg> seg(n + 1, sparseseg(0, n));
    max_length[n] = 0;
    stk[0] = n;
    dp[n] = 1;
    seg[0].update(n, 1);
    int sz = 0;
    for (int i = n - 1; i >= 0; --i) {
        int v = (int) (lower_bound(stk.begin(), stk.end(), a[i], greater<int>()) - stk.begin());
        max_length[i] = v;
        stk[v] = a[i];
        dp[i] = seg[v - 1].query(a[i], n).val;
        seg[v].update(a[i], dp[i]);
        sz = max(sz, v);
    }
    cout << n - sz << '\n';
    int cur = -1;
    vector<bool> in(n + 1, true);
    for (int i = 0; i <= n; ++i) {
        if (max_length[i] == sz && a[i] > cur) {
            if (k > dp[i]) k -= dp[i];
            else in[a[i]] = false, sz -= 1, cur = a[i];
        }
    }
    for (int i = 0; i < n; ++i) if (in[i]) cout << i + 1 << '\n';
}
