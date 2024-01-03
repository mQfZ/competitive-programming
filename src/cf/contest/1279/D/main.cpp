#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

/**
 * Modular Integer
 * Description:
 *    Static/Dynamic modular integer.
 * Verification: 
 */

template <auto _MOD>
class modular {
public:
    using T = decay_t<decltype(_MOD)>;
    static constexpr T MOD = _MOD;

private:
    T v;

    template <typename U>
    static T normalize(const U& x) {
        T v;
        if (-MOD <= x && x < MOD) v = static_cast<T>(x);
        else v = static_cast<T>(x % MOD);
        if (v < 0) v += MOD;
        return v;
    }

    template <typename T>
    T mod_inv(T a, T m) {
        T x = 0, y = 1;
        while (a != 0) {
            T t = m / a;
            m -= t * a;
            x -= t * y;
            swap(a, m);
            swap(x, y);
        }
        assert(m == 1);
        return x;
    }

public:
    modular() : v(0) {}
    template <typename U> modular(const U& x) : v(normalize(x)) {}
    
    const T& operator()() const { return v; }
    template <typename U> explicit operator U() const { return static_cast<U>(v); }

    modular& operator+=(const modular& o) { if ((v += o.v) >= MOD) v -= MOD; return *this; }
    modular& operator-=(const modular& o) { if ((v -= o.v) < 0) v += MOD; return *this; }
    modular& operator*=(const modular& o) { v = normalize((int64_t) v * o.v) % MOD; return *this; }
    modular& operator/=(const modular& o) { return *this *= mod_inv(o.v, MOD); }
    
    friend modular operator+(const modular& a, const modular& b) { return modular(a) += b; }
    friend modular operator-(const modular& a, const modular& b) { return modular(a) -= b; }
    friend modular operator*(const modular& a, const modular& b) { return modular(a) *= b; }
    friend modular operator/(const modular& a, const modular& b) { return modular(a) /= b; }

    modular& operator++() { return *this += 1; }
    modular& operator--() { return *this -= 1; }
    modular operator++(int) { modular res(*this); *this += 1; return res; }
    modular operator--(int) { modular res(*this); *this -= 1; return res; }
    modular operator-() const { return modular(-v); }
    modular operator+() const { return modular(*this); }

    friend bool operator==(const modular& a, const modular& b) { return a.v == b.v; }
    friend bool operator!=(const modular& a, const modular& b) { return a.v != b.v; }
    friend bool operator<(const modular& a, const modular& b) { return a.v < b.v; }
    friend bool operator<=(const modular& a, const modular& b) { return a.v <= b.v; }
    friend bool operator>(const modular& a, const modular& b) { return a.v > b.v; }
    friend bool operator>=(const modular& a, const modular& b) { return a.v >= b.v; }

    template <typename U>
    friend U& operator<<(U& stream, const modular& a) { return stream << a.v; }
    template <typename U>
    friend U& operator>>(U& stream, modular& a) { modular::T x; stream >> x; a = x; return stream; }

    friend string to_string(const modular& a) { return to_string(a.v); }
    
    template <typename U>
    friend modular pow(modular a, U p) {
        assert(p >= 0);
        modular res = 1;
        while (p) { if (p & 1) res *= a; p >>= 1; a *= a; }
        return res;
    }
};

constexpr int md = 998244353;
using mint = modular<md>;

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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    const int mx = (int) (1e6) + 10;
    vector<mint> sums(mx), freq(mx);
    for (int i = 0; i < n; ++i) {
        mint num; cin >> num;
        mint prob = 1 / num;
        assert(prob == pow((mint) num, md - 2));
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
