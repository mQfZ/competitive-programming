#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

/**
 * Fenwick Tree
 * Description:
 *    Computes partial sums a[l] + a[l + 1] + ... + a[r], and increments
 *    single element a[x]
 * Time Complexity:
 *    Update: O(log n)
 *    Query: O(log n)
 * Verification: https://judge.yosupo.jp/submission/141443
 */

template <typename T>
struct Fenwick {
    int n;
    vector<T> tree;

    Fenwick(int _n) : n(_n) {
        tree.resize(n);
    }

    // increment a[x]
    void update(int x, T v) {
        for (++x; x <= n; x += x & -x) {
            tree[x - 1] += v;
        }
    }

    // query [0, x]
    T query(int x) {
        T total = 0;
        for (++x; x > 0; x -= x & -x) {
            total += tree[x - 1];
        }
        return total;
    }
    
    // query [l, r]
    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    const long long inf = 1e18;
    int n, q; cin >> n >> q;
    vector<long long> a(n); for (auto& x : a) cin >> x;
    a.push_back(inf);
    vector<long long> pref(n + 1);
    for (int i = 1; i <= n; ++i) pref[i] = pref[i - 1] + a[i - 1];
    vector<vector<pair<int, int>>> queries(n);
    vector<long long> c(n), ans(n);
    for (int i = 0; i < q; ++i) {
        int x, y; cin >> x >> y;
        queries[x - 1].push_back({y - 1, i});
    }
    deque<int> st = {n};
    Fenwick<long long> fw(n);
    for (int i = n - 1; i >= 0; --i) {
        while (a[st.front()] < a[i]) {
            fw.update(st.front(), -c[st.front()]);
            c[st.front()] = 0;
            st.pop_front();
        }
        c[i] = (st.front() - i) * a[i] - (pref[st.front()] - pref[i]);
        fw.update(i, c[i]);
        st.push_front(i);
        for (auto [y, v] : queries[i]) {
            int p = (int) (upper_bound(st.begin(), st.end(), y) - st.begin() - 1);
            ans[v] = (p > 0 ? fw.query(i, st[p - 1]) : 0)
                            + (y - st[p]) * a[st[p]] - (pref[y + 1] - pref[st[p] + 1]);
        }
    }
    for (int i = 0; i < q; ++i) cout << ans[i] << "\n";
}
