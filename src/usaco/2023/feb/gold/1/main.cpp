#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    const int mx = 500 + 10;
    const long long inf = (long long) 1e18 + 10; 
    int n; cin >> n;
    vector<long long> a(n); for (auto& x : a) cin >> x;
    vector<pair<long long, bitset<mx>>> range;
    for (int i = 0; i < n; ++i) {
        long long sum = 0;
        bitset<mx> bs;
        for (int j = i; j < n; ++j) {
            sum += a[j];
            bs[j] = 1;
            range.push_back({sum, bs});
        }
    }
    sort(range.begin(), range.end(), [&](auto x, auto y) { return x.first < y.first; });
    long long sz = n * (n + 1) / 2;
    assert(sz == (int) range.size());
    for (int i = 0; i < n; ++i) {
        int cc = 0, nc = 0;
        long long ans = inf;
        while (true) {
            while (cc < sz && !range[cc].second[i]) ++cc;
            while (nc < sz && range[nc].second[i]) ++nc;
            if (cc >= sz || nc >= sz) break;
            ans = min(ans, abs(range[cc].first - range[nc].first));
            if (cc < nc) ++cc;
            else ++nc;
        }
        cout << ans << '\n';
    }
}
