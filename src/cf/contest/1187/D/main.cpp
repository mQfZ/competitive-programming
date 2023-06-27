#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

template <typename T>
struct SegTree {
    const T ID = (long long) 1e18; T cmb(T a, T b) { return min(a, b); } 
    int n; vector<T> seg;
    SegTree(int _n) : n(_n) { seg.assign(2*n,ID); }
    void pull(int p) { seg[p] = cmb(seg[2*p],seg[2*p+1]); }
    void upd(int p, T val) { // set val at position p
        seg[p += n] = val; for (p /= 2; p; p /= 2) pull(p); }
    T query(int l, int r) {	// zero-indexed, inclusive
        T ra = ID, rb = ID;
        for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
            if (l&1) ra = cmb(ra,seg[l++]);
            if (r&1) rb = cmb(seg[--r],rb);
        }
        return cmb(ra,rb);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        int n; cin >> n;
        vector<int> a(n); for (auto& x : a) cin >> x, --x;
        vector<int> b(n); for (auto& x : b) cin >> x, --x;
        vector<vector<int>> stk(n);
        SegTree<long long> st(n);
        for (int i = 0; i < n; ++i) stk[a[i]].push_back(i), st.upd(i, a[i]);
        for (int i = 0; i < n; ++i) sort(stk[i].begin(), stk[i].end(), greater<int>());
        bool ok = true;
        for (int i = 0; i < n; ++i) {
            int v = b[i];
            if (stk[v].empty()) { ok = false; break; }
            int j = stk[v].back(); stk[v].pop_back();
            if (st.query(0, j) < v) { ok = false; break; }
            st.upd(j, (long long) 1e18);
        }
        cout << (ok ? "YES" : "NO") << '\n';
    }
}
