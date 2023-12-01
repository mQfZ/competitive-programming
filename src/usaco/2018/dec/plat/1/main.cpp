#include <bits/stdc++.h>
using namespace std;

#include <utility>

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

/**
 * Point
 * Description:
 *    Point class (used in place if complex<T>).
 * Time Complexity: N/A
 * Verification: N/A
 */

using dist_t = long double;
using angle_t = long double;

template <typename T>
struct point {
    T x, y;

    point() : x(0), y(0) {}
    point(const T& _x, const T& _y) : x(_x), y(_y) {}
    template <typename U, typename V> point(const U& _x, const V& _y) : point((T) _x, (T) _y) {}
    point(const pair<T, T>& p) : point(p.first, p.second) {}
    template <typename U, typename V> point(const pair<U, V>& p) : point(p.first, p.second) {}
    point(const complex<T>& p) : x(p.real()), y(p.imag()) {}

    point& operator+=(const point& o) { x += o.x; y += o.y; return *this; }
    point& operator-=(const point& o) { x -= o.x; y -= o.y; return *this; }
    point& operator*=(T s) { x *= s; y *= s; return *this; }
    point& operator/=(T s) { x /= s; y /= s; return *this; }

    point operator+(const point& o) const { return point(*this) += o; }
    point operator-(const point& o) const { return point(*this) -= o; }
    point operator*(const T& s) const { return point(*this) *= s; }
    friend point operator*(const T& s, const point& p) { return p * s; }
    point operator/(const T& s) const { return point(*this) /= s; }
    point operator-() const { return point(-x, -y); }

    bool operator==(const point& o) const { return tie(x, y) == tie(o.x, o.y); }
    bool operator!=(const point& o) const { return tie(x, y) != tie(o.x, o.y); }
    bool operator<(const point& o) const { return tie(x, y) < tie(o.x, o.y); }
    bool operator<=(const point& o) const { return tie(x, y) <= tie(o.x, o.y); }
    bool operator>(const point& o) const { return tie(x, y) > tie(o.x, o.y); }
    bool operator>=(const point& o) const { return tie(x, y) >= tie(o.x, o.y); }

    T dot(const point& o) const { return x * o.x + y * o.y; }
    T cross(const point& o) const { return x * o.y - y * o.x; }
    T cross(const point& a, const point& b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    dist_t dist() const { return sqrt((dist_t) dist2()); }
    angle_t angle() const { return atan2(y, x); }
    point<dist_t> unit() const { return point<dist_t>(x, y) / dist(); }
    point perp() const { return point(-y, x); }
    point<dist_t> normal() const { return point<dist_t>(x, y).perp().unit(); }
    point<dist_t> rotate(angle_t a) const {
        return point<dist_t>(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a)); }
    template <typename U> friend U& operator>>(U& stream, const point& p) {
        cin >> p.x >> p.y;
    }
    template <typename U> friend U& operator<<(U& stream, const point& p) {
        return stream << "(" << p.x << ", " << p.y << ")"; }
};

/**
 * Convext Hull
 * Description:
 *    Creates a convex hull (subset of points that forms the smallest convex
 *    polygon which encloses all points in the set). Returns in clockwise order
 *    where the leftmost point is first.
 * Time Complexity: O(n log n)
 * Verification: N/A
 */

template <typename T>
vector<point<T>> convex_hull(vector<point<T>> v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    int n = (int) v.size();
    if (n < 3) return v;
    vector<point<T>> h;
    for (int i = 0; i < n; ++i) {
        while (h.size() > 1 && h[h.size() - 2].cross(h.back(), v[i]) <= 0) h.pop_back();
        h.push_back(v[i]);
    }
    auto sz = h.size();
    for (int i = n - 2; i >= 0; --i) {
        while (h.size() > sz && h[h.size() - 2].cross(h.back(), v[i]) <= 0) h.pop_back();
        h.push_back(v[i]);
    }
    h.pop_back();
    return h;
};

void set_io(string s) {
#ifndef LOCAL
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
#endif
}

int main() {
    set_io("balance");
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<point<long double>> a(n + 2);
    a[n + 1] = {n + 1, 0};
    for (int i = 1; i <= n; ++i) {
        int x; cin >> x;
        a[i] = {i, 1e5 * x};
    }
    auto h = convex_hull(a);
    reverse(h.begin() + 1, h.end());
    vector<long double> ans(n + 1);
    for (int i = 1; i < (int) h.size(); ++i) {
        long double m = (h[i].y - h[i - 1].y) / (h[i].x - h[i - 1].x);
        for (int j = (int) h[i - 1].x; j < (int) h[i].x; ++j) {
            ans[j] = h[i - 1].y + (j - (int) h[i - 1].x) * m;
        }
    }
    cout << fixed << setprecision(0);
    for (int i = 1; i <= n; ++i) cout << (long double) floor(ans[i]) << '\n';
}
