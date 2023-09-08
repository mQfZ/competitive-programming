#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template <class Fun>
class y_combinator_result {
    Fun fun_;
  public:
    template <class T>
    explicit y_combinator_result(T &&fun) : fun_(std::forward<T>(fun)) {}

    template <class ...Args>
    decltype(auto) operator()(Args &&...args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template <class Fun>
decltype(auto) y_combinator(Fun &&fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    const long long inf = (long long) 1e18 + 11;
    int n, k; cin >> n >> k;
    vector<int> size(n);
    vector<vector<int>> a(n);
    vector<long long> sum(n);
    for (int i = 0; i < n; ++i) {
        cin >> size[i]; a[i].resize(size[i]); for (auto& x : a[i]) cin >> x;
        if (size[i] > k) size[i] = k, a[i].resize(k);
        sum[i] = accumulate(a[i].begin(), a[i].end(), 0LL);
    }
    vector<long long> knapsack(k + 1, 0);
    long long ans = 0;
    auto add = [&](int s, long long ad) -> void {
        for (int i = k; i >= s; --i) knapsack[i] = max(knapsack[i], knapsack[i - s] + ad);
    };
    y_combinator([&](auto self, int l, int r) -> void {
        if (l == r) {
            long long sm = 0;
            ans = max(ans, knapsack[k]);
            for (int i = 0; i < size[l]; ++i) {
                sm += a[l][i];
                ans = max(ans, knapsack[k - i - 1] + sm);
            }
            add(size[l], sum[l]);
            return;
        }
        int m = (l + r) / 2;
        vector<long long> init = knapsack;
        for (int i = l; i <= m; ++i) add(size[i], sum[i]);
        self(m + 1, r);
        knapsack = init;
        for (int i = m + 1; i <= r; ++i) add(size[i], sum[i]);
        self(l, m);
    })(0, n - 1);
    cout << ans << '\n';
}
