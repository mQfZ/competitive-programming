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
        int n, m; cin >> n >> m;
        vector<pair<vector<int>, int>> a(n);
        for (int i = 0; i < n; ++i) {
            a[i] = {vector<int>(m), i}; for (auto& x : a[i].first) cin >> x;
        }
        sort(a.begin(), a.end());
        vector<vector<int>> mx2(n, vector<int>(m)), mx4(n, vector<int>(m)),
                            mn1(n, vector<int>(m)), mn3(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                mx2[i][j] = a[i].first[j];
                if (i > 0) mx2[i][j] = max(mx2[i][j], mx2[i - 1][j]);
                if (j > 0) mx2[i][j] = max(mx2[i][j], mx2[i][j - 1]);
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                mx4[i][j] = a[i].first[j];
                if (i < n - 1) mx4[i][j] = max(mx4[i][j], mx4[i + 1][j]);
                if (j < m - 1) mx4[i][j] = max(mx4[i][j], mx4[i][j + 1]);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = m - 1; j >= 0; --j) {
                mn1[i][j] = a[i].first[j];
                if (i > 0) mn1[i][j] = min(mn1[i][j], mn1[i - 1][j]);
                if (j < m - 1) mn1[i][j] = min(mn1[i][j], mn1[i][j + 1]);
            }
        }
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < m; ++j) {
                mn3[i][j] = a[i].first[j];
                if (i < n - 1) mn3[i][j] = min(mn3[i][j], mn3[i + 1][j]);
                if (j > 0) mn3[i][j] = min(mn3[i][j], mn3[i][j - 1]);
            }
        }
        bool ans = 0;
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < m - 1; ++j) {
                if (mx2[i][j] < mn3[i + 1][j] && mn1[i][j + 1] > mx4[i + 1][j + 1]) {
                    ans = true;
                    string s = string(n, 'R');
                    for (int x = 0; x <= i; ++x) s[a[x].second] = 'B';
                    cout << "YES" << '\n';
                    cout << s << ' ' << j + 1 << '\n';
                    break;
                }
            }
            if (ans) break;
        }
        if (ans) continue;
        cout << "NO" << '\n';
    }
}

/*
1 1 1 0 0 1


*/
