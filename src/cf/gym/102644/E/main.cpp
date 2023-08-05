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
    
    int rows, cols;
    MT data;

    matrix() : matrix(0, 0) {}
    matrix(int _rows, int _cols) : rows(_rows), cols(_cols), data() {
        if constexpr (is_same_v<MT, vector<typename MT::value_type>>)
            data.assign(rows, vector<T>(cols));
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

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    matrix<unsigned int> mt(65, 65);
    mt[64][64] = 1;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            for (int x = 0; x < 8; ++x) {
                for (int y = 0; y < 8; ++y) {
                    if (abs(i - x) + abs(j - y) == 3 && i != x && j != y) {
                        mt[8 * i + j][8 * x + y] = 1;
                    }
                }
            }
            mt[8 * i + j][64] = 1;
        }
    }
    cout << pow(mt, n + 1)[0][64] << '\n';
}
