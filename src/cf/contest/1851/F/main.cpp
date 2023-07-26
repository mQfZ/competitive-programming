#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        int n, k; cin >> n >> k;
        vector<int> a(n); for (auto& x : a) cin >> x;
        function<pair<pair<int, int>, pair<int, int>>(vector<int>, int)>
        dfs = [&](vector<int> c, int b) -> pair<pair<int, int>, pair<int, int>> {
            if (c.size() < 2) return {{-1, -1}, {-1, -1}};
            if (b == -1) {
                int x = a[c[0]], y = a[c[1]];
                int v = 0;
                for (int z = 0; z < k; ++z) {
                    if ((x & (1 << z)) == 0 && (y & (1 << z)) == 0) v += 1 << z;
                }
                return {{(x ^ v) & (y ^ v), v}, {c[0], c[1]}};
            }
            vector<int> p, q;
            for (auto& x : c) if (a[x] & (1 << b)) p.push_back(x); else q.push_back(x);
            if (p.size() == 1 && q.size() == 1) return dfs(c, b - 1);
            else {
                auto y = dfs(p, b - 1), z = dfs(q, b - 1);
                if (y.first.first > z.first.first) return y;
                else return z;
            }
        };
        vector<int> t(n); iota(t.begin(), t.end(), 0);
        auto ans = dfs(t, k - 1);
        cout << ans.second.first + 1 << ' ' << ans.second.second + 1 << ' ' << ans.first.second << '\n';
    }
}
