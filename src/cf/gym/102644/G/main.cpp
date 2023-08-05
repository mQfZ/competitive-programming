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
    // using MT = array<array<T, COLS>, ROWS>;
    
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
 
    typename MT::value_type& operator[](size_t i) { return data[i]; };
 
    static matrix make_id(int n) {
        matrix m(n, n);
        for (int i = 0; i < n; ++i) m.data[i][i] = 1;
        return m;
    }

    // returns a[row][0] + a[row][1] + ... + a[row][n - 1]
    T row_sum(int row) {
        assert(0 <= row && row < rows);
        T sum = {};
        for (int j = 0; j < cols; ++j) sum += data[row][j];
        return sum;
    }

    // returns a[0][col] + a[1][col] + ... + a[n - 1][col]
    T col_sum(int col) {
        assert(0 <= col && col < cols);
        T sum = {};
        for (int i = 0; i < rows; ++i) sum += data[i][col];
        return sum;
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

    friend ostream& operator<<(ostream& os, mint x) { return os << x.v; }
};
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; long long k; cin >> n >> k;
    matrix<mint> init(n + 3, n + 3), mt(n + 3, n + 3);
    for (int i = 0; i < n; ++i) cin >> init[i][i].v;
    init[n][n] = 1;
    init[n + 1][n + 1] = n;
    init[n + 2][n + 2] = n * n;
    for (int i = 0; i < n; ++i) cin >> mt[n - i - 1][n - 1].v;
    for (int i = 1; i < n; ++i) mt[i][i - 1] = 1;
    mt[n][n] = 1;
    mt[n][n + 1] = 1;
    mt[n + 1][n + 1] = 1;
    mt[n][n + 2] = 1;
    mt[n + 1][n + 2] = 2;
    mt[n + 2][n + 2] = 1;
    cin >> mt[n][n - 1].v >> mt[n + 1][n - 1].v >> mt[n + 2][n - 1].v;
    if (k < n) { cout << init.data[k][k].v << '\n'; return 0; }
    cout << (init * pow(mt, k - n + 1)).col_sum(n - 1).v << '\n';
}
