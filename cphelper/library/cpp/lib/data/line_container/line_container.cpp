#include <bits/stdc++.h>
using namespace std;
#pragma once

#include <lib/data/line_container/line.cpp>

/**
 * Line Container
 * Description:
 *    Given a set of lines in the form mx + b, computes the greatest
 *    y-coordinate for any x. Might have issues when comparing doubles.
 * Time Complexity: O(log n)
 * Verification: https://codeforces.com/contest/1083/submission/239959317
 */

template <typename T>
class line_container {
private:
    static const T inf = numeric_limits<T>::max();
    multiset<line<T>, less<>> ms;

    constexpr T div(const T& a, const T& b) {
        return is_integral_v<T> ? a / b - ((a ^ b) < 0 && a % b) : a / b;
    }

    template <typename Iterator>
    bool isect(Iterator x, Iterator y) {
        if (y == ms.end()) return x->p = inf, 0;
        if (x->m == y->m) x->p = x->b > y->b ? inf : -inf;
        else x->p = div(y->b - x->b, x->m - y->m);
        return x->p >= y->p;
    }
    
public:
    // add line y = mx + b
    void add(T m, T b) {
        auto z = ms.insert({m, b, 0}), y = z++, x = y;
        while (isect(y, z)) z = ms.erase(z);
        if (x != ms.begin() && isect(--x, y)) isect(x, y = ms.erase(y));
        while ((y = x) != ms.begin() && (--x)->p >= y->p) isect(x, ms.erase(y));
    }

    // query max y at x-coordinate x
    T query(T x) {
        assert(!ms.empty());
        return ms.lower_bound(x)->eval(x);
    }

    void clear() {
        ms.clear();
    }
};
