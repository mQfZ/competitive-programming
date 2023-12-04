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

/**
 * Point
 * Description:
 *    2D point class (used in place if complex<T>).
 * Time Complexity: N/A
 * Verification: N/A
 */

using dist_t = long double;
using angle_t = long double;

const dist_t eps = 1e-9;
template <typename T> int sign(const T& x) { return (x > eps) - (x < -eps); }

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
    template <typename U> friend U& operator>>(U& stream, point& p) {
        return stream >> p.x >> p.y;
    }
    template <typename U> friend U& operator<<(U& stream, const point& p) {
        return stream << "(" << p.x << ", " << p.y << ")"; }
};

// 1 = left, 0 = on, -1 = right
template <typename T>
int side_of(const point<T>& s, const point<T>& e, const point<T>& p) {
    return sign(s.cross(e, p));
}

template <typename T>
bool on_seg(const point<T>& s, const point<T>& e, const point<T>& p) {
    return sign(p.cross(s, e)) == 0 && sign((s - p).dot(e - p)) <= 0;
}

/**
 * Convext Hull
 * Description:
 *    Creates a convex hull (subset of points that forms the smallest convex
 *    polygon which encloses all points in the set). Returns in counter
 *    clockwise order where the leftmost point is first.
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

/**
 * Point in Convex Hull
 * Description:
 *    Checks if a point is inside the convex hull. Returns 1 if inside, 0 if
 *    on an edge and -1 if outside.
 * Time Complexity: O(log n)
 * Verification: N/A
 */

template <typename T>
int inside_hull(const vector<point<T>>& h, const point<T>& p) {
    assert(h.size() > 0);
    if (h.size() < 3) return on_seg(h[0], h.back(), p) ? 0 : -1;
    if (side_of(h[0], h[1], p) == -1 || side_of(h[0], h.back(), p) == 1) return -1;
    int l = 1, r = (int) h.size() - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        if (side_of(h[0], h[m], p) <= 0) r = m;
        else l = m;
    }
    assert(side_of(h[0], h[l], p) >= 0);
    assert(side_of(h[0], h[r], p) <= 0);
    return side_of(h[l], h[r], p);
}

int main() {
    set_io("curling");
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<point<long long>> a(n), b(n);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;
    vector<point<long long>> ha = convex_hull(a), hb = convex_hull(b);
    int aa = 0, bb = 0;
    for (int i = 0; i < n; ++i) {
        aa += inside_hull(ha, b[i]) >= 0;
        bb += inside_hull(hb, a[i]) >= 0;
    }
    cout << aa << ' ' << bb << '\n';
}
