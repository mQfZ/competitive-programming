#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

template <typename T>
using gpq = priority_queue<T, vector<T>, greater<T>>;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string s; cin >> s;
    bool ok = true;
    long long ans = 0, cur = 0;
    gpq<pair<int, int>> q;
    for (int i = 0; i < (int) s.size(); ++i) {
        cur += s[i] == '(' ? 1 : -1;
        if (s[i] == '?') {
            int x, y; cin >> x >> y;
            ans += y;
            q.push({x - y, i});
        }
        if (s[i] != '(') s[i] = ')';
        if (cur < 0) {
            if (q.size() == 0) { ok = false; break; }
            auto t = q.top(); q.pop();
            ans += t.first;
            s[t.second] = '(';
            cur += 2;
        }
    }
    if (ok && cur == 0) cout << ans << '\n' << s << '\n';
    else cout << -1 << '\n';
}
