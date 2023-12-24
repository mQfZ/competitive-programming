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
        vector<vector<bool>> a(n, vector<bool>(n));
        bool flip = false;
        if (n == 2) {
            if (k == 0) {
                cout << "Yes" << '\n';
                cout << "0 0" << '\n';
                cout << "0 0" << '\n';
            } else if (k == 2) {
                cout << "Yes" << '\n';
                cout << "1 0" << '\n';
                cout << "0 1" << '\n';
            } else if (k == 4) {
                cout << "Yes" << '\n';
                cout << "1 1" << '\n';
                cout << "1 1" << '\n';
            } else cout << "No" << '\n';
            continue;
        }
        if (k > n * n / 2) k = n * n - k, flip = true;
        if (k % 2 == 1 || k == 2) { cout << "No" << '\n'; continue; }
        if (k % 4 == 2) {
            a[n - 3][n - 3] = true;
            a[n - 3][n - 2] = true;
            a[n - 2][n - 3] = true;
            a[n - 2][n - 1] = true;
            a[n - 1][n - 2] = true;
            a[n - 1][n - 1] = true;
            k -= 6;
        }
        for (int d = 0; d < k / 4; ++d) {
            int r = d / (n / 2);
            int c = d % (n / 2);
            a[2 * r][2 * c] = true;
            a[2 * r + 1][2 * c] = true;
            a[2 * r][2 * c + 1] = true;
            a[2 * r + 1][2 * c + 1] = true;
        }
        cout << "Yes" << '\n';
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                cout << (flip ? !a[i][j] : a[i][j]) << " \n"[j == n - 1];
        }
    }
}
