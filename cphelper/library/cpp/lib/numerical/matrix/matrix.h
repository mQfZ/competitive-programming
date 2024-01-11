#include <bits/stdc++.h>
using namespace std;
#pragma once

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
protected:
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
