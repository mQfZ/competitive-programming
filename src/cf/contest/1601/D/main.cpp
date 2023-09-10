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
    int n, d; cin >> n >> d;
    vector<pair<int, int>> gr, le;
    for (int i = 0; i < n; ++i) {
        int s, a; cin >> s >> a;
        if (s < a) gr.push_back({a, s});
        else le.push_back({s, a});
    }
    sort(gr.begin(), gr.end());
    sort(le.begin(), le.end());
    int ans = 0;
    int j = 0;
    for (int i = 0; i < (int) le.size(); ++i) {
        while (j < (int) gr.size() && gr[j].first <= le[i].first) {
            if (gr[j].second >= d) ++ans, d = gr[j].first;
            ++j;
        }
        if (le[i].first >= d) ++ans, d = max(d, le[i].second);
    }
    while (j < (int) gr.size()) {
        if (gr[j].second >= d) ++ans, d = gr[j].first;
        ++j;
    }
    cout << ans << '\n';
}
