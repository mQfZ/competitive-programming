#include <bits/stdc++.h>
using namespace std;
#pragma once

#include <lib/numerical/modular_arithmetic/modular_integer.h>

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
