#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

template <typename T>
struct matrix {
    // switch matrix type to array for performance boost (if TLE)
    using MT = vector<vector<T>>;
    // using MT = array<array<T, COLS>, ROWS>;
    static constexpr bool RS = is_same_v<MT, vector<typename MT::value_type>>;

    int rows, cols;
    MT data;

    matrix() : matrix(0, 0) {}
    matrix(int _rows, int _cols) : rows(_rows), cols(_cols), data() {
        if constexpr (RS) data.assign(rows, vector<T>(cols));
        else assert(rows <= (int) data.size() && cols <= (int) data[0].size());
    }
    matrix(const vector<vector<T>>& _data) : matrix((int) _data.size(), (int) _data[0].size()) {
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
            for (int k = 0; k < o.cols; ++k) res.data[i][k] += data[i][j] * o.data[j][k];
        return res;
    }
    matrix& operator*=(const matrix& o) { return *this = (*this) * o; }

    typename MT::value_type operator[](int i) { return data[i]; };

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
    long long n; cin >> n;
    matrix<mint> m({{1, 1}, {1, 0}});
    cout << pow(m, n)[0][1].v << '\n';
}
