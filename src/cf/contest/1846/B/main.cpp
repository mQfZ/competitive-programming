#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <debug.h>
#else
#define dbg(...) 0
#define dbgn(...) 0
#endif

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int tt; cin >> tt;
    while (tt--) {
        string a, b, c; cin >> a >> b >> c;
#define pre(x) { if (x != '.') {cout << x << '\n'; continue; }  }
        if (a[0] == a[1] && a[1] == a[2]) pre(a[0]);
        if (b[1] == b[2] && b[1] == b[0]) pre(b[0]);
        if (c[1] == c[2] && c[1] == c[0]) pre(c[0]);
        if (a[0] == b[0] && b[0] == c[0]) pre(a[0]);
        if (a[1] == b[1] && b[1] == c[1]) pre(a[1]);
        if (a[2] == b[2] && b[2] == c[2]) pre(a[2]);
        if (a[0] == b[1] && b[1] == c[2]) pre(a[0]);
        if (a[2] == b[1] && b[1] == c[0]) pre(a[2]);
        cout << "DRAW" << '\n';
    }
}
