#include <bits/stdc++.h>
using namespace std;

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

dist_t eps = 1e-9;

template <typename T>
int sign(T x) { return (x > eps) - (x < -eps); }

template <typename T>
struct point {
    T x, y;

    point() : x(0), y(0) {}
    point(T _x, T _y) : x(_x), y(_y) {}
    point(pair<T, T> p) : x(p.first), y(p.second) {}
    point(complex<T> p) : x(p.real()), y(p.imag()) {}

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
 *    polygon which encloses all points in the set).
 * Time Complexity: O(n log n)
 * Verification: N/A
 */

template <typename T>
vector<point<T>> convex_hull(vector<point<T>> v) {
    sort(v.begin(), v.end());
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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<point<long double>> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        int z; cin >> z;
        a[i] = {(long double) i, a[i - 1].y + z};
    }
    vector<point<long double>> h = convex_hull(a);
    vector<long double> ans(n);
    dbg(h);
    for (int i = 1; i < (int) h.size(); ++i) {
        long double curr = (h[i].y - h[i - 1].y) / (h[i].x - h[i - 1].x);
        for (int j = (int) h[i - 1].x; j < (int) h[i].x; ++j) ans[j] = curr;
        if ((int) h[i].x == n) break;
    }
    cout << fixed << setprecision(9);
    for (auto& x : ans) cout << x << '\n';
}
