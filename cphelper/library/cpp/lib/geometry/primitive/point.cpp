#include <bits/stdc++.h>
using namespace std;
#pragma once

/**
 * Point
 * Description:
 *    2D point class (used in place if complex<T>).
 * Time Complexity: N/A
 * Verification: N/A
 */

using dist_t = long double;
using angle_t = long double;

template <typename T> int sign(const T& x) { return (x > 0) - (x < 0); }

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

// 1 iff p is on line segment from s to e
template <typename T>
bool on_seg(const point<T>& s, const point<T>& e, const point<T>& p) {
    return sign(p.cross(s, e)) == 0 && sign((s - p).dot(e - p)) <= 0;
}
