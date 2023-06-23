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
    vector<int> a(n + 1); for (int i = 1; i <= n; ++i) cin >> a[i];
    stack<int> st;
    st.push(0);
    for (int i = 1; i <= n; ++i) {
        while (a[st.top()] >= a[i]) st.pop();
        cout << st.top() << " \n"[i == n];
        st.push(i);
    }
}
