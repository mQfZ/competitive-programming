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
    int n, q; cin >> n >> q;
    multiset<int> s, dist; for (int i = 0; i < n; ++i) { int x; cin >> x; s.insert(x); }
    for (auto it = next(s.begin()); it != s.end(); ++it) dist.insert(*it - *prev(it));
    auto ans = [&]() {
        if (s.size() > 1) cout << *prev(s.end()) - *s.begin() - *prev(dist.end()) << '\n';
        else cout << 0 << '\n';
    };
    ans();
    while (q--) {
        int x, y; cin >> x >> y;
        if (x == 0) {
            auto it = s.find(y);
            if (it != prev(s.end())) dist.erase(dist.find(*next(it) - *it));
            if (it != s.begin()) dist.erase(dist.find(*it - *prev(it)));
            if (it != prev(s.end()) && it != s.begin()) dist.insert(*next(it) - *prev(it));
            s.erase(it);
        } else {
            auto it = s.insert(y);
            if (it != prev(s.end())) dist.insert(*next(it) - *it);
            if (it != s.begin()) dist.insert(*it - *prev(it));
            if (it != prev(s.end()) && it != s.begin()) dist.erase(dist.find(*next(it) - *prev(it)));
        }
        ans();
    }
}
