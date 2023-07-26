#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

struct seg {
    int mn_prefix = 0, mx_prefix = 0;
    int mn_suffix = 0, mx_suffix = 0;
    int mn_sum = 0, mx_sum = 0, sum = 0;
    int parent = 0;
};

seg unite(const seg& a, const seg& b) {
    seg res;
    res.mn_prefix = min(a.mn_prefix, a.sum + b.mn_prefix);
    res.mx_prefix = max(a.mx_prefix, a.sum + b.mx_prefix);
    res.mn_suffix = min(b.mn_suffix, b.sum + a.mn_suffix);
    res.mx_suffix = max(b.mx_suffix, b.sum + a.mx_suffix);
    res.mn_sum = min({a.mn_sum, b.mn_sum, a.mn_suffix + b.mn_prefix});
    res.mx_sum = max({a.mx_sum, b.mx_sum, a.mx_suffix + b.mx_prefix});
    res.sum = a.sum + b.sum;
    res.parent = b.parent;
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    const int mx = 18;
    int tt; cin >> tt;
    while (tt--) {
        int q; cin >> q;
        vector<int> depth = {0};
        vector<vector<seg>> jump = {{{0, 1, 0, 1, 0, 1, 1, -1}}};
        while (q--) {
            char t; int u, v, x; cin >> t >> u >> v, --u;
            if (t == '+') {
                depth.push_back(depth[u] + 1);
                seg s;
                if (v == -1) s.mn_prefix = s.mn_suffix = s.mn_sum = s.sum = -1;
                else s.mx_prefix = s.mx_suffix = s.mx_sum = s.sum = 1;
                s.parent = u;
                jump.push_back({s});
                int cur = u, i = 0;
                while (cur != -1 && (int) jump[cur].size() > i) {
                    jump.back().push_back(unite(jump.back().back(), jump[cur][i]));
                    cur = jump[cur][i].parent;
                    ++i;
                }
            } else {
                cin >> x, --v;
                if (depth[u] < depth[v]) swap(u, v);
                int y = u, z = v;
                seg us, vs;
                for (int i = mx; i >= 0; --i) {
                    if (depth[u] - (1 << i) >= depth[v]) {
                        us = unite(us, jump[u][i]);
                        u = jump[u][i].parent;
                    }
                }
                for (int i = mx; i >= 0; --i) {
                    if ((int) jump[u].size() > i && jump[u][i].parent != jump[v][i].parent) {
                        us = unite(us, jump[u][i]);
                        vs = unite(vs, jump[v][i]);
                        u = jump[u][i].parent;
                        v = jump[v][i].parent;
                    }
                }
                if (u != v) {
                    us = unite(us, jump[u][0]);
                    vs = unite(vs, jump[v][0]);
                    u = jump[u][0].parent;
                    v = jump[v][0].parent;
                }
                us = unite(us, jump[u][0]);
                swap(vs.mn_prefix, vs.mn_suffix);
                swap(vs.mx_prefix, vs.mx_suffix);
                seg s = unite(us, vs);
                cout << (s.mn_sum <= x && x <= s.mx_sum ? "YES" : "NO") << '\n';
            }
        }
    }
}
