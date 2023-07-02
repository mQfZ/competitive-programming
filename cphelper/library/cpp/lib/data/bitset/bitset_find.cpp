#include <bits/stdc++.h>
using namespace std;

/**
 * Bitset w/ finding next/previous bits
 * Description:
 *    Indentical to C++ Bitset except it can find the next/previous set bit 
 *    relative to index i. Can also find the first and last set bit.
 * Time Complexity:
 *    Find Next/Previous/First/Last: O(n / 64)
 * Verification: https://github.com/mQfZ/competitive-programming/blob/master/src/usaco/2022/dec/gold/2/bitset.cpp
 */

template <int Nb>
struct bitset_find : bitset<Nb> {
    static constexpr int array_size = (Nb + 63) / 64;
    
    template <typename... Args>
    bitset_find(Args... args) : bitset<Nb>(args...) {}

    union raw_cast {
        array<uint64_t, array_size> a;
        bitset_find b;
    };

    // first set bit after i, else size of bitset
    int find_next(int i) const {
        assert(-1 <= i && i < Nb);
        if (i == Nb - 1) return Nb;
        if ((*this)[++i]) return i;
        int p = i / 64;
        const auto &a = ((const raw_cast *) (this))->a;
        uint64_t buf = a[p] & (~0ULL - (1ULL << (i & 63)) + 1);
        if (buf) return p * 64 + __builtin_ffsll(buf) - 1;
        while (++p < array_size) {
            if (a[p]) return p * 64 + __builtin_ffsll(a[p]) - 1;
        }
        return Nb;
    }

    // last set bit before i, else -1
    int find_prev(int i) const {
        assert(0 <= i && i <= Nb);
        if (i == 0) return -1;
        if ((*this)[--i]) return i;
        int p = i / 64;
        const auto &a = ((const raw_cast *) (this))->a;
        uint64_t buf = a[p] & ((1ULL << (i & 63)) - 1);
        if (buf != 0) return p * 64 + 63 - __builtin_clzll(buf);
        while (p--) {
            if (a[p]) return p * 64 + 63 - __builtin_clzll(a[p]);
        }
        return -1;
    }

    // first set bit, else size of bitset
    inline int find_first() const { return find_next(-1); }

    // last set bit, else -1
    inline int find_last() const { return find_prev(Nb); }
};
