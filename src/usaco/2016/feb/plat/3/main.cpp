#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

void set_io(string s) {
#ifndef LOCAL
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
#endif
}

struct Line {
	mutable long long k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(long long x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const long long inf = LLONG_MAX;
	long long div(long long a, long long b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(long long k, long long m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	long long query(long long x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

int main() {
    set_io("cbarn");
    ios::sync_with_stdio(0); cin.tie(0);
    const long long inf = (long long) 1e18 + 10;
    int n, k; cin >> n >> k;
    vector<long long> a(n); for (auto& x : a) cin >> x;
    long long ans = inf;
    for (int rot = 0; rot < n; ++rot) {
        vector<long long> dp(n + 1, inf), pref(n + 1), pref_mult(n + 1);
        dp[0] = pref[0] = pref_mult[0] = 0;
        for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + a[i];
        for (int i = 0; i < n; ++i) pref_mult[i + 1] = pref_mult[i] + a[i] * i;
        for (int itr = 1; itr <= k; ++itr) {
            vector<long long> ndp = dp;
            deque<pair<long long, long long>> lines;
            LineContainer lc;
            for (int i = 0; i <= n; ++i) {
                long long slope = -i, height = dp[i] - pref_mult[i] + pref[i] * i;
                lc.add(-slope, -height);
                lc.query(pref[i]);
                ndp[i] = -lc.query(pref[i]) + pref_mult[i];
            }
            dp = ndp;
        }
        ans = min(ans, dp[n]);
        rotate(a.begin(), a.begin() + 1, a.end());
    }
    cout << ans << '\n';
}
