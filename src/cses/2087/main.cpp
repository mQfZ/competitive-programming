#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

/**
 * Line
 * Description:
 *    Line class for line containers.
 * Time Complexity: N/A
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/cses/2087/main.cpp
 */

template <typename T>
struct line {
    mutable T m, b, p;
    T eval(T x) const { return m * x + b; }
    bool operator<(const line& o) const { return m < o.m; }
    bool operator<(T x) const { return p < x; }
};

/**
 * Line Container Deque
 * Description:
 *    Given a set of lines in the form mx + b, computes the greatest y
 *    coordinate for any x, assuming queries and slopes are monotonic. Might
 *    have issues when comparing doubles.
 * Time Complexity: O(1)
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/cses/2087/main.cpp
 */

template <typename T>
class line_container_deque {
private:
    static const T inf = numeric_limits<T>::max();
    deque<line<T>> dq;

    constexpr T div(const T& a, const T& b) {
        return is_integral_v<T> ? a / b - ((a ^ b) < 0 && a % b) : a / b;
    }

public:
    // add line y = mx + b, where m is monotonic
    void add(T m, T b) {
        line<T> l = {m, b, -inf};
        if (dq.empty() || m <= dq.front().m) {
            while (true) {
                if (dq.empty()) { l.p = inf; break; }
                auto o = dq.front();
                l.p = l.m == o.m ? (l.b >= o.b ? inf : -inf) : div(l.b - o.b, o.m - l.m);
                if (l.p >= o.p) dq.pop_front();
                else break;
            }
            dq.push_front(l);
        } else {
            assert(m >= dq.back().m);
            while (true) {
                auto o = dq.back(); dq.pop_back();
                o.p = o.m == l.m ? (o.b >= l.b ? inf : -inf) : div(o.b - l.b, l.m - o.m);
                if (dq.empty() || dq.back().p < o.p) { dq.push_back(o); break; }
            }
            l.p = inf;
            dq.push_back(l);
        }
    }

    // query max y at x-coordinate x.
    // query_order = 1 if x-coordinates are increasing, -1 if decreasing
    T query(T x, int query_order) {
        assert(query_order);
        if (query_order > 0) {
            while (dq.front().p < x) dq.pop_front();
            return dq.front().eval(x);
        } else {
            while (dq.size() > 1 && prev(prev(dq.end()))->p >= x) dq.pop_back();
            return dq.back().eval(x);
        }
    }

    void clear() {
        dq.clear();
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, k; cin >> n >> k;
    vector<long long> a(n); for (auto& x : a) cin >> x;
    vector<long long> pref(n + 1), pref2(n + 1);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + a[i];
        pref2[i + 1] = pref2[i] + i * a[i];
    }
    line_container_deque<long long> lcd, nlcd;
    lcd.add(0, 0);
    while (k--) {
        nlcd.clear();
        for (int j = 0; j <= n; ++j) nlcd.add(j, 2 * pref2[j] - 2 * j * pref[j] + lcd.query(-j, -1));
        lcd.clear();
        for (int j = 0; j <= n; ++j) lcd.add(-pref[j], nlcd.query(pref[j], 1) - 2 * pref2[j]);
    }
    cout << pref2[n] - nlcd.query(pref[n], 1) << '\n';
}
