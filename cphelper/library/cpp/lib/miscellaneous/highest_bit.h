#include <bits/stdc++.h>
using namespace std;
#pragma once

int most_significant_bit(unsigned int x) {
    return (x == 0 ? 0 : sizeof(int) * 8 - __builtin_clz(x)) - 1;
}
