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
    int n; cin >> n;
    vector<bool> pa(n);
    for (int i = 0; i < n; ++i) { char c; cin >> c; pa[i] = c - '0'; }
    vector<vector<int>> padj(n);
    for (int i = 0; i < n - 1; ++i) {
        int x, y; cin >> x >> y;
        padj[x - 1].push_back(y - 1);
        padj[y - 1].push_back(x - 1);
    }
    map<int, int> rm;
    y_combinator([&](auto self, int v, int pv, int nn) -> int {
        rm[v] = nn; int sz = 1;
        for (int nv : padj[v]) if (nv != pv) sz += self(nv, v, nn + sz);
        return sz;
    })(0, -1, 0);
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) for (int j : padj[i])
        if (rm[i] < rm[j]) adj[rm[i]].push_back(rm[j]);
    vector<bool> a(n); for (int i = 0; i < n; ++i) a[rm[i]] = pa[i];
    auto solve = [&](int k) -> pair<int, int> {
        vector<pair<pair<int, int>, pair<int, int>>> dp(n);
        for (int i = n - 1; i >= 0; --i) {
            dp[i].second.first = k + 1;
            dp[i].second.second = 1;
            for (int j : adj[i]) {
                if (dp[j].first.first < dp[j].second.first) {
                    dp[i].first.first += dp[j].first.first;
                    dp[i].first.second += dp[j].first.second;
                } else {
                    dp[i].first.first += dp[j].second.first;
                    dp[i].first.second += dp[j].second.second;
                }
                if (dp[j].first.first < dp[j].second.first - k) {
                    dp[i].second.first += dp[j].first.first;
                    dp[i].second.second += dp[j].first.second;
                } else {
                    dp[i].second.first += dp[j].second.first - k;
                    dp[i].second.second += dp[j].second.second - 1;
                }
            }
            if (a[i]) dp[i].first.first = inf;
        }
        return min(dp[0].first, dp[0].second);
    };
    vector<pair<int, int>> ans(n + 1);
    ans[1] = solve(1);
    ans[n] = solve(n);
    y_combinator([&](auto self, int l, int r) -> void {
        if (r - l < 2) return;
        if (ans[l].second == ans[r].second) {
            for (int i = l + 1; i < r; ++i) {
                ans[i] = {ans[l].first + (i - l) * ans[l].second, ans[l].second};
            }
        } else {
            int m = (l + r) / 2;
            ans[m] = solve(m);
            self(l, m);
            self(m, r);
        }
    })(1, n);
    for (int i = 1; i <= n; ++i) cout << ans[i].first << '\n';
}
