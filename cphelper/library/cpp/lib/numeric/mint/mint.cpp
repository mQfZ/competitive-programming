#include <bits/stdc++.h>
using namespace std;
#pragma once

/**
 * Modular Integer
 * Description:
 *    Static/Dynamic modular integer.
 * Verification: https://codeforces.com/contest/1279/submission/234538787
 */

template <typename T>
T inverse(T a, T m) {
    T u = 0, v = 1;
    while (a != 0) {
        T t = m / a;
        m -= t * a; swap(a, m);
        u -= t * v; swap(u, v);
    }
    assert(m == 1);
    return u;
}

template <typename MT>
struct modular {
    using T = typename decay<decltype(MT::value)>::type;
    T v;

    constexpr modular() : v(0) {}
    template <typename U>
    modular(const U& x) : v(normalize(x)) {}

    template <typename U>
    static T normalize(const U& x) {
        T v;
        if (-mod() <= x && x < mod()) v = static_cast<T>(x);
        else v = static_cast<T>(x % mod());
        if (v < 0) v += mod();
        return v;
    }

    const T& operator()() const { return v; }
    template <typename U>
    explicit operator U() const { return static_cast<U>(v); }
    constexpr static T mod() { return MT::value; }

    modular& operator+=(const modular& o) { if ((v += o.v) >= mod()) v -= mod(); return *this; }
    template <typename U> modular& operator+=(const U& o) { return *this += modular(o); }
    modular& operator-=(const modular& o) { if ((v -= o.v) < 0) v += mod(); return *this; }
    template <typename U> modular& operator-=(const U& o) { return *this -= modular(o); }
    modular& operator*=(const modular& o) { v = normalize((long long) v * o.v); return *this; }
    template <typename U> modular& operator*=(const U& o) { return *this *= modular(o); }
    modular& operator/=(const modular& o) { return *this *= inverse(o.v, mod()); }
    template <typename U> modular& operator/=(const U& o) { return *this /= modular(o); }

    modular& operator++() { return *this += 1; }
    modular operator++(int) { modular result(*this); *this += 1; return result; }
    modular& operator--() { return *this -= 1; }
    modular operator--(int) { modular result(*this); *this -= 1; return result; }
    modular operator-() const { return modular(-v); }
};

template <typename T> bool operator==(const modular<T>& a, const modular<T>& b) { return a.v == b.v; }
template <typename T, typename U> bool operator==(const modular<T>& a, U b) { return a.v == b; }
template <typename T, typename U> bool operator==(U a, const modular<T>& b) { return a == b.v; }
 
template <typename T> bool operator!=(const modular<T>& a, const modular<T>& b) { return a.v != b.v; }
template <typename T, typename U> bool operator!=(const modular<T>& a, U b) { return a.v != b; }
template <typename T, typename U> bool operator!=(U a, const modular<T>& b) { return a != b.v; }
 
template <typename T> bool operator<(const modular<T>& a, const modular<T>& b) { return a.v < b.v; }
template <typename T, typename U> bool operator<(const modular<T>& a, U b) { return a.v < b; }
template <typename T, typename U> bool operator<(U a, const modular<T>& b) { return a < b.v; }
 
template <typename T> bool operator<=(const modular<T>& a, const modular<T>& b) { return a.v <= b.v; }
template <typename T, typename U> bool operator<=(const modular<T>& a, U b) { return a.v <= b; }
template <typename T, typename U> bool operator<=(U a, const modular<T>& b) { return a <= b.v; }
 
template <typename T> bool operator>(const modular<T>& a, const modular<T>& b) { return a.v > b.v; }
template <typename T, typename U> bool operator>(const modular<T>& a, U b) { return a.v > b; }
template <typename T, typename U> bool operator>(U a, const modular<T>& b) { return a > b.v; }
 
template <typename T> bool operator>=(const modular<T>& a, const modular<T>& b) { return a.v >= b.v; }
template <typename T, typename U> bool operator>=(const modular<T>& a, U b) { return a.v >= b; }
template <typename T, typename U> bool operator>=(U a, const modular<T>& b) { return a >= b.v; }
 
template <typename T> modular<T> operator+(const modular<T>& a, const modular<T>& b) { return modular<T>(a) += b; }
template <typename T, typename U> modular<T> operator+(const modular<T>& a, U b) { return modular<T>(a) += b; }
template <typename T, typename U> modular<T> operator+(U a, const modular<T>& b) { return modular<T>(a) += b; }
 
template <typename T> modular<T> operator-(const modular<T>& a, const modular<T>& b) { return modular<T>(a) -= b; }
template <typename T, typename U> modular<T> operator-(const modular<T>& a, U b) { return modular<T>(a) -= b; }
template <typename T, typename U> modular<T> operator-(U a, const modular<T>& b) { return modular<T>(a) -= b; }
 
template <typename T> modular<T> operator*(const modular<T>& a, const modular<T>& b) { return modular<T>(a) *= b; }
template <typename T, typename U> modular<T> operator*(const modular<T>& a, U b) { return modular<T>(a) *= b; }
template <typename T, typename U> modular<T> operator*(U a, const modular<T>& b) { return modular<T>(a) *= b; }
 
template <typename T> modular<T> operator/(const modular<T>& a, const modular<T>& b) { return modular<T>(a) /= b; }
template <typename T, typename U> modular<T> operator/(const modular<T>& a, U b) { return modular<T>(a) /= b; }
template <typename T, typename U> modular<T> operator/(U a, const modular<T>& b) { return modular<T>(a) /= b; }


template <typename U, typename T>
U& operator<<(U& stream, const modular<T>& a) {
    return stream << a.v;
}

template <typename U, typename T>
U& operator>>(U& stream, modular<T>& a) {
    typename common_type<typename modular<T>::T, long long>::type x;
    stream >> x;
    a.v = modular<T>::normalize(x);
    return stream;
}

template <typename T>
string to_string(const modular<T>& a) {
    return to_string(a.v);
}

template <typename T, typename U>
T intpow(const T& a, const U& b) {
    T x = a, res = 1;
    U p = b;
    while (p > 0) {
        if (p & 1) res *= x;
        x *= x;
        p >>= 1;
    }
    return res;
}

// change to false if mod is not known at compile time
#if true  // constant mod
const long long md = 1000000007;  // 998244353;
using mint = modular<std::integral_constant<decay<decltype(md)>::type, md>>;
#else    // dynamic mod
using mod_type = int;
struct var_mod { static mod_type value; };
mod_type var_mod::value;
mod_type& md = var_mod::value;
using mint = modular<var_mod>;
#endif
