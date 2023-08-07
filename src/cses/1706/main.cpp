#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

/**
 * Disjoint Set Union
 * Description:
 *    Disjoint Set Union with path compression and union by size. Add edges 
 *    and test connectivity.
 * Time Complexity: O(alpha(N))
 * Verification: https://judge.yosupo.jp/submission/141446
 */

struct dsu {
    int n;
    vector<int> e;

    dsu(int _n) : n(_n) {
        e.resize(n, -1);
    }

    int get(int x) {
        return e[x] < 0 ? x : (e[x] = get(e[x]));
    }

    int size(int x) {
        return -e[get(x)];
    }

    bool unite(int x, int y) {
        x = get(x);
        y = get(y);
        if (x == y) return false;
        if (-e[x] < -e[y]) swap(x, y);
        e[x] += e[y];
        e[y] = x;
        return true;
    }
};

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

int main() {
    const int mx = (int) 1e5 + 10;
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    dsu d(n);
    while (m--) {
        int x, y; cin >> x >> y, --x, --y;
        d.unite(x, y);
    }
    vector<int> shift;
    for (int i = 0; i < n; ++i) if (d.get(i) == i) shift.push_back(d.size(i));
    vector<bool> res = possible_subsets_knapsack<mx>(n, shift);
    for (int i = 1; i <= n; ++i) cout << res[i];
}
