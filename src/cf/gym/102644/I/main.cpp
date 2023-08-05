#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

/**
 * Matrix
 * Description:
 *    Basic matrix operations (addition, subtraction, multiplication). Uses
 *    vectors, but can be switched to arrays to reduce overhead and speed up
 *    code. 
 * Time Complexity:
 *     Addition/Subtraction: O(r * c) for r by c matrix
 *     Multiplication: O(r * c * h) for r by c matrix * c by h matrix
 *     Exponentiation: O(n ^ 3 * log2(k)) for n by n matrix
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/cf/gym/102644/D/main.cpp
 */

template <typename T>
struct matrix {
    // switch matrix type to array for performance boost (if TLE)
    using MT = vector<vector<T>>;
    // using MT = array<array<T, 200>, 200>;
    
    int rows, cols;
    MT data;

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

    typename MT::value_type& operator[](int i) { return data[i]; };

    static matrix make_id(int n) {
        matrix m(n, n);
        for (int i = 0; i < n; ++i) m.data[i][i] = 1;
        return m;
    }

    friend matrix pow(matrix m, long long p) {
        assert(m.rows == m.cols && p >= 0);
        matrix res = make_id(m.rows);
        for (; p > 0; p /= 2, m *= m) if (p & 1) res *= m;
        return res;
    }
};

/**
 * Modular Integer
 * Description:
 *    Basic modular arithmetic operations (excluding division).
 * Verification: https://codeforces.com/contest/1279/submission/207090651
 */

const int md = (int) 1e9 + 7;

struct mint {
    int v;
    
    mint() : v(0) {}
    mint(int _v) : v(_v % md) {}

    mint& operator+=(mint o) {
        if ((v += o.v) >= md) v -= md;
        return *this;
    }
    mint& operator-=(mint o) {
        if ((v -= o.v) < 0) v += md;
        return *this;
    }
    mint& operator*=(mint o) {
        v = (int) (((long long) v * o.v) % md);
        return *this;
    }
    
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    const int mxf = 30;
    int n, m, q; cin >> n >> m >> q;
    matrix<mint> a(n, n);
    while (m--) {
        int x, y; cin >> x >> y, --x, --y;
        a[x][y] = 1;
    }
    vector<matrix<mint>> p;
    p.push_back(a);
    for (int i = 0; i < mxf; ++i) p.push_back(p.back() * p.back());
    while (q--) {
        int x, y, k; cin >> x >> y >> k, --x, --y;
        matrix<mint> z = matrix<mint>(1, n);
        z[0][x] = 1;
        for (int i = 0; i < mxf; ++i) {
            if (k & (1 << i)) z *= p[i];
        }
        cout << z[0][y].v << '\n';
    }
}
