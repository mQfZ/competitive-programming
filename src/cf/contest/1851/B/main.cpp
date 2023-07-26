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
        vector<int> a, ax, b, bx;
        for (int i = 0; i < n; ++i) {
            int x; cin >> x;
            if (x % 2 == 0) a.push_back(x), ax.push_back(i);
            else b.push_back(x), bx.push_back(i);
        }
        sort(a.begin(), a.end(), greater<int>());
        sort(b.begin(), b.end(), greater<int>());
        reverse(ax.begin(), ax.end());
        reverse(bx.begin(), bx.end());
        vector<int> c(n);
        for (int i = 0; i < n; ++i) {
            if (ax.size() > 0 && ax.back() == i) c[i] = a.back(), ax.pop_back(), a.pop_back();
            else c[i] = b.back(), bx.pop_back(), b.pop_back();
        }
        cout << (is_sorted(c.begin(), c.end()) ? "YES" : "NO") << '\n';
    }
}
