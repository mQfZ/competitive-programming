#include <bits/stdc++.h>
using namespace std;
 
#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif
 
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n + 2); for (int i = 1; i <= n; ++i) cin >> a[i];
    stack<int> st;
    vector<long long> v(n + 2);
    st.push(0);
    for (int i = 1; i <= n; ++i) {
        while (a[st.top()] >= a[i]) st.pop();
        v[i] = st.top() + 1;
        st.push(i);
    }
    long long ans = 0;
    st = stack<int>();
    st.push(n + 1);
    for (int i = n; i >= 1; --i) {
        while (a[st.top()] >= a[i]) st.pop();
        long long z = st.top() - 1;
        ans = max(ans, (z - v[i] + 1) * a[i]);
        st.push(i);
    }
    cout << ans << '\n';
}
