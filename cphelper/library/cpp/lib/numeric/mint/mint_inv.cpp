#include <bits/stdc++.h>
using namespace std;
#pragma once

/**
 * Modular Integer
 * Description:
 *    Basic modular arithmetic operations. Assumes mod is prime.
 * Verification: https://codeforces.com/contest/1279/submission/207090651
 */

const int md = (int) 1e9 + 7;

struct mint {
    int v;
    
    mint() : v(0) {}
    mint(int _v) : v(_v % md) {
        if (v < 0) v += md;
    }

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
    mint& operator/=(mint o) {
        return (*this) *= inv(o);
    }
    
    friend mint pow(mint a, int p) {
        mint ans = 1;
        for (; p > 0; p /= 2, a *= a) {
            if (p & 1) ans *= a;
        }
        return ans;
    }
    friend mint inv(mint a) {
        return pow(a, md - 2);
    }
    
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }
    friend mint operator/(mint a, mint b) { return a /= b; }
};
