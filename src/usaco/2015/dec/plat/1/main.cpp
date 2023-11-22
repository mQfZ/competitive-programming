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
    set_io("maxflow");
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; ++i) {
        int x, y; cin >> x >> y, --x, --y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<set<int>> s(n);
    for (int i = 0; i < m; ++i) {
        int x, y; cin >> x >> y, --x, --y;
        s[x].insert(i);
        s[y].insert(i);
    }
    int ans = 0;
    y_combinator([&](auto self, int v, int pv) -> void {
        int rm = 0;
        for (int nv : adj[v]) if (nv != pv) {
            self(nv, v);
            if (s[v].size() < s[nv].size()) swap(s[v], s[nv]);
            for (int x : s[nv]) {
                if (s[v].find(x) != s[v].end()) ++rm, s[v].erase(x);
                else s[v].insert(x);
            }
        }
        ans = max(ans, (int) s[v].size() + rm);
    })(0, -1);
    cout << ans << '\n';
}
