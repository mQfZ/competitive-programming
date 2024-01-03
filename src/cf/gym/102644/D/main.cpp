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
    friend modular pow(modular& a, const U& p) {
        assert(p >= 0);
        modular res = 1;
        while (p) { if (p & 1) res *= a; p >>= 1; a *= a; }
        return res;
    }
};

constexpr const int md = 1000000007;  // 998244353;
using mint = modular<md>;

/**
 * Matrix
 * Description:
 *    Basic matrix operations (addition, subtraction, multiplication). Uses
 *    vectors, but can be switched to arrays to reduce overhead and speed up
 *    code. 
 * Time Complexity:
 *     Addition/Subtraction: O(r * c) for r by c matrix
 *     Multiplication: O(r * c * h) for r by c matrix * c by h matrix
 *     Exponentiation: O(n ^ 3 * log(k)) for n by n matrix
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/cf/gym/102644/D/main.cpp
 */

template <typename T>
class matrix {
private:
    // switch matrix type to array for performance boost (if TLE)
    using MT = vector<vector<T>>;
    // using MT = array<array<T, COLS>, ROWS>;
    
    int rows, cols;
    MT data;

public:
    matrix() : matrix(0, 0) {}
    matrix(int _rows, int _cols) : rows(_rows), cols(_cols), data() {
        if constexpr (is_same_v<MT, vector<typename MT::value_type>>)
            data.assign(rows, vector<T>(cols));
        else assert(rows <= (int) data.size() && cols <= (int) data[0].size());
    }
    matrix(const vector<vector<T>>& _data) :
                        matrix((int) _data.size(), (int) _data[0].size()) {
        for (int i = 0; i < rows; ++i) {
            assert((int) _data[i].size() == cols);
            for (int j = 0; j < cols; ++j) data[i][j] = _data[i][j];
        }
    }

    matrix& operator+=(const matrix& o) {
        assert(rows == o.rows && cols == o.cols);
        for (int i = 0; i < rows; ++i) for (int j = 0; j < cols; ++j)
            data[i][j] += o.data[i][j];
        return *this;
    }
    matrix& operator-=(const matrix& o) {
        assert(rows == o.rows && cols == o.cols);
        for (int i = 0; i < rows; ++i) for (int j = 0; j < cols; ++j)
            data[i][j] -= o.data[i][j];
        return *this;
    }
    matrix operator+(const matrix& o) { return matrix(*this) += o; }
    matrix operator-(const matrix& o) { return matrix(*this) -= o; }
    
    matrix operator*(const matrix& o) {
        assert(cols == o.rows);
        matrix res(rows, o.cols);
        for (int i = 0; i < rows; ++i) for (int j = 0; j < cols; ++j)
            for (int k = 0; k < o.cols; ++k)
                res.data[i][k] += data[i][j] * o.data[j][k];
        return res;
    }
    matrix& operator*=(const matrix& o) { return *this = (*this) * o; }

    typename MT::value_type& operator[](size_t i) { return data[i]; };

    static matrix make_id(int n) {
        matrix m(n, n);
        for (int i = 0; i < n; ++i) m.data[i][i] = 1;
        return m;
    }

    friend matrix pow(matrix m, int64_t p) {
        assert(m.rows == m.cols && p >= 0);
        matrix res = make_id(m.rows);
        while (p) { if (p & 1) res *= m; p >>= 1; m *= m; }
        return res;
    }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    matrix<mint> a(n, n);
    while (m--) {
        int x, y; cin >> x >> y, --x, --y;
        a[x][y] = 1;
    }
    a = pow(a, k);
    mint ans = 0;
    for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) ans += a[i][j];
    cout << ans << '\n';
}
