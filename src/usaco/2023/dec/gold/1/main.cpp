#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<vector<bool>> mat(n, vector<bool>(n)), dir(n, vector<bool>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            char c; cin >> c;
            mat[i][j] = c == '1';
        }
    }
    int ans = 0;
    for (int d = 1; d < n; ++d) {
        for (int l = 0; l < n - d; ++l) {
            int r = l + d;
            int par = 0;
            for (int i = l + 1; i < r; ++i) {
                par += (int) mat[l][i] * (int) dir[i][r];
            }
            if (par % 2 != (int) mat[l][r]) {
                dir[l][r] = true;
                ++ans;
            }
        }
    }
    cout << ans << '\n';
}
