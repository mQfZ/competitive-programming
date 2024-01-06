#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

void set_io(string s) {
#ifndef LOCAL
    freopen((s + ".in").c_str(), "r", stdin);
    freopen((s + ".out").c_str(), "w", stdout);
#endif
}

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
class bitset_find : public bitset<Nb> {
private:
    static constexpr int SZ = (Nb + 63) / 64;

    union raw_cast {
        array<uint64_t, SZ> a;
        bitset_find b;
    };

public:
    template <typename... Ts>
    bitset_find(Ts... args) : bitset<Nb>(args...) {}

    // first set bit after i, else size of bitset
    int find_next(int i) const {
        assert(-1 <= i && i < Nb);
        if (i == Nb - 1) return Nb;
        if ((*this)[++i]) return i;
        int p = i / 64;
        const auto &a = ((const raw_cast *) (this))->a;
        uint64_t buf = a[p] & (~0ULL - (1ULL << (i & 63)) + 1);
        if (buf) return p * 64 + __builtin_ffsll(buf) - 1;
        while (++p < SZ) if (a[p]) return p * 64 + __builtin_ffsll(a[p]) - 1;
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
        while (p--) if (a[p]) return p * 64 + 63 - __builtin_clzll(a[p]);
        return -1;
    }

    // first set bit, else size of bitset
    inline int find_first() const { return find_next(-1); }

    // last set bit, else -1
    inline int find_last() const { return find_prev(Nb); }
};

int main() {
    set_io("fortmoo");
    ios::sync_with_stdio(0); cin.tie(0);
    const int mx = 200;
    int n, m; cin >> n >> m;
    vector<vector<bool>> a(n, vector<bool>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c; cin >> c;
            a[i][j] = c == 'X';
        }
    }
    vector row(n, vector(n, bitset_find<mx>())), rowinv(n, vector(n, bitset_find<mx>()));
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            for (int j = 0; j < m; ++j) {
                row[l][r][j] = (l == r ? false : row[l][r - 1][j]) || a[r][j];
                rowinv[l][r][j] = !row[l][r][j];
            }
        }
    }
    int ans = 0;
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            for (int j = 0; j < m; ++j) {
                if (row[l][r][j]) continue;
                int z = max(row[l][l].find_prev(j), row[r][r].find_prev(j));
                ans = max(ans, (j - rowinv[l][r].find_next(z) + 1) * (r - l + 1));
            }
        }
    }
    cout << ans << '\n';
}
