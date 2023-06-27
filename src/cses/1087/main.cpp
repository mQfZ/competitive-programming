#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    string s; cin >> s;
    s.append("ACGT");
    int n = (int) s.size();
    bitset<4> b;
    string ans = "";
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'A') b[0] = 1;
        else if (s[i] == 'C') b[1] = 1;
        else if (s[i] == 'G') b[2] = 1;
        else if (s[i] == 'T') b[3] = 1;
        if (b.count() == 4) {
            b.reset();
            ans.push_back(s[i]);
        }
    }
    cout << ans << '\n';
}
