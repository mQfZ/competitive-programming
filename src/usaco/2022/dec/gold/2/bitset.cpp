#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

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
    ios::sync_with_stdio(0); cin.tie(0);
    const int mx = 2000 + 10;
    int n; cin >> n;
    vector<int> a(n); for (auto& x : a) cin >> x;
    vector<bitset_find<mx>> s(n);
    auto hidden = [&](int l, int m, int r) {
        if (l == m) return false;
        return (long long) (a[m] - a[l]) * (r - l) > (long long) (a[r] - a[l]) * (m - l);
    };
    int ans = 0;
    for (int x = 0; x < n; ++x) {
        s[x][x] = 1;
        int z = x;
        for (int j = x + 1; j < n; ++j) {
            if (!hidden(x, z, j)) s[x][j] = 1, z = j, ++ans;
        }
    }
    int q; cin >> q;
    while (q--) {
        int x, y; cin >> x >> y, --x;
        a[x] += y;
        for (int i = 0; i < x; ++i) {
            int z = (int) s[i].find_prev(x);
            if (hidden(i, z, x)) continue;
            if (!s[i][x]) s[i][x] = 1, ++ans;
            z = (int) s[i].find_next(x);
            while (z < n) {
                if (!hidden(i, x, z)) break;
                s[i][z] = 0, --ans;
                z = (int) s[i].find_next(z);
            }
        }
        ans -= (int) s[x].count() - 1;
        s[x].reset();
        s[x][x] = 1;
        int z = x;
        for (int j = x + 1; j < n; ++j) {
            if (!hidden(x, z, j)) s[x][j] = 1, z = j, ++ans;
        }
        cout << ans << '\n';
    }
}
