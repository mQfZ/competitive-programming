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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    const int inf = (int) 1e9 + 10;
    int tt, t; cin >> tt >> t;
    while (tt--) {
        int n; cin >> n;
        vector<int> parent(n, -1);
        vector<vector<int>> adj(n);
        for (int i = 1; i < n; ++i) cin >> parent[i], --parent[i], adj[parent[i]].push_back(i);
        vector<pair<int, int>> a(n), range(n); for (auto& [x, y] : a) cin >> x >> y;
        vector<int> ans(n, -1);
        int total = 0;
        y_combinator([&](auto self, int v) -> pair<int, int> {
            int l = -1, r = inf;
            for (int nv : adj[v]) {
                auto [ll, rr] = self(nv);
                l = max(l, ll);
                r = min(r, rr);
            }
            int x = max(l, a[v].first), y = min(r, a[v].second);
            if (x > y) {
                int m = (x + y) / 2;
                if (a[v].first <= m && m <= a[v].second) {
                    ans[v] = m;
                    total = max({total, x - m, m - y});
                } else {
                    int f = max(x - a[v].first, a[v].first - y);
                    int s = max(x - a[v].second, a[v].second - y);
                    ans[v] = f < s ? a[v].first : a[v].second;
                    total = max(total, min(f, s));
                }
            }
            range[v] = {x, y};
            return {x, y};
        })(0);
        y_combinator([&](auto self, int v, int l, int r) -> void {
            if (ans[v] == -1) {
                if (range[v].first <= l && r <= range[v].second) ans[v] = l;
                else {
                    int m = (l + r) / 2;
                    if (range[v].first <= m && m <= range[v].second) ans[v] = m;
                    else {
                        int f = max(abs(r - range[v].first), abs(range[v].first - l));
                        int s = max(abs(r - range[v].second), abs(range[v].second - l));
                        ans[v] = f < s ? range[v].first : range[v].second;
                    }
                }
            }
            int ll = min(l, ans[v]);
            int rr = max(r, ans[v]);
            for (int nv : adj[v]) self(nv, ll, rr);
        })(0, inf, -1);
        cout << total << '\n';
        if (t) for (int i = 0; i < n; ++i) cout << ans[i] << " \n"[i == n - 1];
    }
}
