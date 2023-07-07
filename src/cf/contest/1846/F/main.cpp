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
        vector<int> a(n); for (auto& x : a) cin >> x;
        cout << '-' << ' ' << 0 << endl;
        vector<int> b(n); for (auto& x : b) cin >> x;
        vector<int> q = a, p = b;
        sort(q.begin(), q.end()); sort(p.begin(), p.end());
        if (p == q) {
            cout << '-' << ' ' << 0 << endl;
            for (auto& x : b) cin >> x;
        }
        vector<int> cnt(10);
        int z = -1;
        for (int i = 0; i < n; ++i) ++cnt[a[i]], --cnt[b[i]];
        for (int i = 0; i < 10; ++i) if (cnt[i] == -1) z = i;
        assert(z != -1);
        vector<int> d;
        for (int i = 0; i < n; ++i) if (b[i] != z) d.push_back(i);
        cout << '-' << ' ' << d.size(); for (auto& x : d) cout << ' ' << x + 1; cout << endl;
        vector<int> v(n - d.size()); for (auto& x : v) cin >> x;
        int qqq = -1;
        for (int i = 0; i < n - (int) d.size(); ++i) {
            if (v[i] != z) qqq = i;
        }
        if (qqq == -1) {
            cout << '-' << ' ' << 0 << endl;
            for (auto& x : v) cin >> x;
            for (int i = 0; i < n - (int) d.size(); ++i) {
                if (v[i] != z) qqq = i;
            }
        }
        assert(qqq != -1);
        cout << '!' << ' ' << qqq + 1 << endl;
    }
}
