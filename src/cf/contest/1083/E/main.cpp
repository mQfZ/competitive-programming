#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

/**
 * Line Container
 * Description:
 *    Given a set of lines in the form mx + b, computes the greatest
 *    y-coordinate for any x. Might have issues when comparing doubles.
 * Time Complexity: O(log n)
 * Verification: N/A
 */

template <typename T>
struct line {
    mutable T m, b, p;
    T eval(T x) const { return m * x + b; }
    bool operator<(const line& o) const { return m < o.m; }
    bool operator<(T x) const { return p < x; }
};

template <typename T>
struct line_container {
    static const T inf = numeric_limits<T>::max();
    multiset<line<T>, less<>> ms;

    constexpr T div(const T& a, const T& b) {
        return is_integral_v<T> ? a / b - ((a ^ b) < 0 && a % b) : a / b;
    }

    template <typename Iterator>
    bool isect(Iterator x, Iterator y) {
        if (y == ms.end()) return x->p = inf, 0;
        if (x->m == y->m) x->p = x->b > y->b ? inf : -inf;
        else x->p = div(y->b - x->b, x->m - y->m);
        return x->p >= y->p;
    }
    
    // add line y = mx + b
    void add(T m, T b) {
        auto z = ms.insert({m, b, 0}), y = z++, x = y;
        while (isect(y, z)) z = ms.erase(z);
        if (x != ms.begin() && isect(--x, y)) isect(x, y = ms.erase(y));
        while ((y = x) != ms.begin() && (--x)->p >= y->p) isect(x, ms.erase(y));
    }

    // query max y at x-coordinate x
    T query(T x) {
        assert(!ms.empty());
        return ms.lower_bound(x)->eval(x);
    }

    void clear() {
        ms.clear();
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<array<long long, 3>> a(n);
    for (auto& [x, y, z] : a) cin >> x >> y >> z;
    sort(a.begin(), a.end());
    vector<long long> dp(n + 1, 0);
    line_container<long long> lc;
    lc.add(0, 0);
    for (int i = 0; i < n; ++i) {
        dp[i + 1] = max(dp[i], a[i][0] * a[i][1] - a[i][2] + lc.query(a[i][1]));
        lc.add(-a[i][0], dp[i + 1]);
    }
    cout << dp[n] << '\n';
}
