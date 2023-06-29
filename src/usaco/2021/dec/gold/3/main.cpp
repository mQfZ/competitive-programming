#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        int n, m; cin >> n >> m;
        vector<vector<int>> a(m);
        vector<vector<pair<int, int>>> pos(m, vector<pair<int, int>>(n, {-1, -1}));
        vector<pair<int, int>> range(n, {-1, -1});
        bool ans = true;
        #define check() if (!ans) { cout << "NO" << '\n'; continue; }
        for (int i = 0; i < m; ++i) {
            int s; cin >> s;
            a[i].resize(s);
            for (int j = 0; j < s; ++j) {
                cin >> a[i][j], --a[i][j];
                if (pos[i][a[i][j]].first == -1) pos[i][a[i][j]].first = j;
                else pos[i][a[i][j]].second = j;
            }
            // Not Necessary
            // for (int j = 0; j < n; ++j) {
            //     if (pos[i][j].first != -1 && (pos[i][j].second - pos[i][j].first) % 2 == 0) ans = false;
            // }
        }
        check();
        for (int c = 0; c < n; ++c) {
            for (int i = 0; i < m; ++i) {
                if (pos[i][c].first != -1) {
                    if (range[c].first == -1) range[c].first = i, range[c].second = i - 1;
                    if (range[c].second == i - 1) ++range[c].second;
                    else ans = false;
                }
            }
        }
        check();
        dbg(a);
        for (int c1 = 0; c1 < n; ++c1) {
            for (int c2 = c1 + 1; c2 < n; ++c2) {
                if (range[c1].first == -1 || range[c2].first == -1) continue;
                int l = max(range[c1].first, range[c2].first);
                int r = min(range[c1].second, range[c2].second);
                if (l > r) continue;
                int z = -1;
                for (int i = l; i <= r; ++i) {
                    bool ls = pos[i][c1].first < pos[i][c2].first;
                    bool rs = pos[i][c1].second < pos[i][c2].second;
                    dbg(pos[i][c1], pos[i][c2], ls, rs);
                    if ((ls && rs && pos[i][c1].second > pos[i][c2].first) || 
                            (!ls && !rs && pos[i][c2].second > pos[i][c1].first)) {
                        dbg("TRIGGER");
                        ans = false;
                    }
                    int nz = (int) (ls) + ((int) (rs) * 2);
                    if (z == -1) z = nz;
                    if (z != nz) ans = false;
                }
                if (z == 1) {
                    dbg(c1, c2);
                    if (range[c2].first < l || range[c2].second > r) ans = false;
                }
                if (z == 2) {
                    dbg(c1, c2);
                    if (range[c1].first < l || range[c1].second > r) ans = false;
                }
                dbg(c1, c2, ans);
            }
        }
        dbg(ans);
        dbg("END");
        check();
        cout << "YES" << '\n';
    }
}
