#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n); for (auto& x : a) cin >> x, --x;
    vector<int> inv(n); for (int i = 0; i < n; ++i) inv[a[i]] = i;
    deque<int> lo, hi;
    vector<vector<int>> push_hi(n);
    for (int i = n - 1; i >= 0; --i) {
        while (!hi.empty() && hi.back() > inv[i]) {
            push_hi[i].push_back(hi.back());
            hi.pop_back();
        }
        reverse(push_hi[i].begin(), push_hi[i].end());
        hi.push_back(inv[i]);
    }
    vector<int> aa(n + 1);
    int ans = 0;
    set<pair<int, bool>> s;
    for (int x : hi) s.insert({x, 0});
    for (int i = 0; i < n; ++i) {
        aa[i] = ans;
        int b = hi.back();
        auto it = s.lower_bound({b, 0});
        if (next(it) != s.end()) {
            if (next(it)->second && (it == s.begin() || prev(it)->second)) --ans;
        }
        s.erase(it);
        hi.pop_back();
        while (!lo.empty() && lo.back() > inv[i]) {
            b = lo.back();
            it = s.lower_bound({b, 1});
            if (it != s.begin()) {
                if (!prev(it)->second && (next(it) == s.end() || !next(it)->second)) --ans;
            }
            s.erase(it);
            lo.pop_back();
        }
        for (int j : push_hi[i]) {
            b = j;
            s.insert({b, 0});
            it = s.lower_bound({b, 0});
            if (next(it) != s.end()) {
                if (next(it)->second && (it == s.begin() || prev(it)->second)) ++ans;
            }
            hi.push_back(j);
        }
        b = inv[i];
        s.insert({b, 1});
        it = s.lower_bound({b, 1});
        if (it != s.begin()) {
            if (!prev(it)->second && (next(it) == s.end() || !next(it)->second)) ++ans;
        }
        lo.push_back(inv[i]);
    }
    for (int i = 0; i <= n; ++i) cout << aa[i] << "\n";
}
