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
        int n; cin >> n;
        string s; cin >> s;
        deque<int> a;
        for (int i = 0; i < n; ++i) a.push_back({s[i] - '0'});
        vector<int> ops;
        int lhs = 0;
        while ((int) ops.size() <= 310 && a.size() > 0) {
            while (a.size() > 0 && a.front() != a.back()) {
                a.pop_front();
                if (a.size() > 0) a.pop_back();
                lhs += 1;
            }
            if (a.size() == 0) continue;
            if (a.front() == 1) ops.push_back(lhs), lhs += 1, a.pop_back(), a.push_front(1);
            else ops.push_back(lhs + (int) a.size()), lhs += 1, a.pop_front(), a.push_back(0);
        }
        if (ops.size() >= 310) cout << -1 << '\n';
        else {
            cout << ops.size() << '\n';
            for (auto& x : ops) cout << x << ' ';
            cout << '\n';
        }
    }
}
