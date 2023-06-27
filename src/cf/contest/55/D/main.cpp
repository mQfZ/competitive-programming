#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    const int p = 2520, z = 50, y = 20;
    vector<int> mp(p + 1);
    for (int i = 1; i <= p; ++i) mp[i] = mp[i - 1] + (p % i == 0);
    vector<int> p10(y); p10[0] = 1;
    for (int i = 1; i < y; ++i) p10[i] = (p10[i - 1] * 10) % p;
    auto solve = [&](long long n) {
        vector<int> d;
        while (n > 0) d.push_back((int) (n % 10)), n /= 10;
        vector<vector<vector<long long>>> dp(d.size(), vector<vector<long long>>(p, vector<long long>(z, -1)));
        function<long long(int, int, int, bool)> dfs = [&](int s, int r, int l, bool f) -> long long {
            if (s == -1) return r % l == 0;
            if (!f && dp[s][r][mp[l]] != -1) return dp[s][r][mp[l]];
            int cur = f ? d[s] : 9;
            long long ans = 0;
            for (int i = 0; i <= cur; ++i) {
                ans += dfs(s - 1, (r + i * p10[s]) % p, i > 0 ? lcm(l, i) : l, f && i == cur);
            }
            if (!f) dp[s][r][mp[l]] = ans;
            return ans;
        };
        return dfs((int) d.size() - 1, 0, 1, true);
    };
    int tt; cin >> tt;
    while (tt--) {
        long long l, r; cin >> l >> r;
        cout << solve(r) - solve(l - 1) << '\n';
    }
}
