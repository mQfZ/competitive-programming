#include <bits/stdc++.h>
using namespace std;

/**
 * Modular Integer
 * Description:
 *    Static/Dynamic modular integer.
 * Verification: https://codeforces.com/contest/1279/submission/234657671
 */

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

    template <typename T>
    T mod_inv(T a, T m) {
        T x = 0, y = 1;
        while (a != 0) {
            T t = m / a;
            m -= t * a; swap(a, m);
            x -= t * y; swap(x, y);
        }
        assert(m == 1);
        return x;
    }

    modular& operator+=(const modular& o) { if ((v += o.v) >= mod()) v -= mod(); return *this; }
    modular& operator-=(const modular& o) { if ((v -= o.v) < 0) v += mod(); return *this; }
    modular& operator*=(const modular& o) { v = normalize((long long) v * o.v); return *this; }
    modular& operator/=(const modular& o) { return *this *= mod_inv(o.v, mod()); }

    friend modular operator+(const modular& a, const modular& b) { return modular(a) += b; }
    friend modular operator-(const modular& a, const modular& b) { return modular(a) -= b; }
    friend modular operator*(const modular& a, const modular& b) { return modular(a) *= b; }
    friend modular operator/(const modular& a, const modular& b) { return modular(a) /= b; }

    modular& operator++() { return *this += 1; }
    modular operator++(int) { modular result(*this); *this += 1; return result; }
    modular& operator--() { return *this -= 1; }
    modular operator--(int) { modular result(*this); *this -= 1; return result; }
    modular operator-() const { return modular(-v); }

    friend bool operator==(const modular& a, const modular& b) { return a.v == b.v; }
    friend bool operator!=(const modular& a, const modular& b) { return a.v != b.v; }
    friend bool operator<(const modular& a, const modular& b) { return a.v < b.v; }
    friend bool operator<=(const modular& a, const modular& b) { return a.v <= b.v; }
    friend bool operator>(const modular& a, const modular& b) { return a.v > b.v; }
    friend bool operator>=(const modular& a, const modular& b) { return a.v >= b.v; }

    template <typename U>
    friend U& operator<<(U& stream, const modular& a) {
        return stream << a.v;
    }

    template <typename U, typename T>
    friend U& operator>>(U& stream, modular<T>& a) {
        typename common_type<typename modular<T>::T, long long>::type x;
        stream >> x;
        a.v = modular<T>::normalize(x);
        return stream;
    }

    friend string to_string(const modular& a) {
        return to_string(a.v);
    }

    template <typename T, typename U>
    friend T intpow(const T& a, const U& b) {
        T x = a, res = 1;
        U p = b;
        while (p > 0) {
            if (p & 1) res *= x;
            x *= x;
            p >>= 1;
        }
        return res;
    }
};

// change to false if mod is not known at compile time
#if true  // constant mod
const int md = 998244353;
using mint = modular<std::integral_constant<decay<decltype(md)>::type, md>>;
#else    // dynamic mod
using mod_type = int;
struct var_mod { static mod_type value; };
mod_type var_mod::value;
mod_type& md = var_mod::value;
using mint = modular<var_mod>;
#endif

/**
 * Combinatorics
 * Description:
 *    Pre compute factorial and modular inverses. Assumes mod is prime.
 * Time Complexity: O(n)
 * Verification: https://codeforces.com/contest/1462/submission/207091126
 */

vector<mint> fact;
vector<mint> inv_fact;

void gen_fact(int n) {
    if (fact.size() == 0) fact = inv_fact = {1};
    while ((int) fact.size() <= n) {
        fact.push_back(fact.back() * (int) fact.size());
        inv_fact.push_back(1 / fact.back());
    }
}

mint F(int n) {
    gen_fact(n);
    return fact[n];
}

mint C(int n, int k) {
    if (k < 0 || k > n) return 0;
    gen_fact(n);
    return fact[n] * inv_fact[k] * inv_fact[n - k];
}

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    const int mx = (int) (1e6) + 10;
    vector<mint> sums(mx), freq(mx);
    for (int i = 0; i < n; ++i) {
        mint num; cin >> num;
        mint prob = 1 / num;
        assert(prob == intpow((mint) num, md - 2));
        while (num--) {
            int x; cin >> x;
            sums[x] = sums[x] - (md - prob);
            ++freq[x];
        }
    }
    mint ans = 0;
    for (int i = 0; i < mx; ++i) {
        ans += freq[i] * sums[i];
    }
    cout << to_string(ans / n / n) << '\n';
}
