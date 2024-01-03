#include <bits/stdc++.h>
using namespace std;
#pragma once

/**
 * Possible Subsets Knapsack
 * Description:
 *    Computes all possible subset sums from 0 to n (inclusive) that can be
 *    made using values from sizes.
 * Time Complexity:
 *    O(n sqrt(n) / 64) if the sum of sizes is bounded by n
 *    O(n ^ 2 / 64) otherwise
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/cses/1706/main.cpp
 */

template <const int N_MAX>
vector<bool> possible_subsets_knapsack(int n, const vector<int>& sizes) {
    vector<int> freq(n + 1, 0);
    for (int s : sizes) if (1 <= s && s <= n) ++freq[s];
    bitset<N_MAX> kn;
    kn[0] = 1;
    for (int i = 1; i <= n; ++i) {
        if (freq[i] >= 3) {
            int mv = (freq[i] - 1) / 2;
            freq[i] -= 2 * mv;
            if (2 * i <= n) freq[2 * i] += mv;
        }
        for (int j = 0; j < freq[i]; ++j) kn |= kn << i;
    }
    vector<bool> ret(n + 1);
    for (int i = 0; i <= n; ++i) ret[i] = kn[i];
    return ret;
}
