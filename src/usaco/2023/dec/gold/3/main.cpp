#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<long long> s(n); for (auto& x : s) cin >> x;
    sort(s.begin(), s.end());
    vector<long long> pref(n + 1);
    for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + s[i];
    int q; cin >> q;
    while (q--) {
        long long a, b; cin >> a >> b;
        int m = (int) ((b * n) / (a + b));
        long long ans = a * (m * s[m] - pref[m]) + b * ((pref[n] - pref[m]) - s[m] * (n - m));
        cout << ans << '\n';
    }
}
