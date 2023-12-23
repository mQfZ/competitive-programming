#include <bits/stdc++.h>
using namespace std;

const int md = (int) 1e9 + 7;

struct mint {
    long long v;
    
    mint() : v(0) {}
    mint(long long _v) : v(_v % md) { if (v < 0) v += md; }

    mint& operator+=(mint o) { if ((v += o.v) >= md) v -= md; return *this; }
    mint& operator-=(mint o) { if ((v -= o.v) < 0) v += md; return *this; }
    mint& operator*=(mint o) { v = (int) (((long long) v * o.v) % md); return *this; }
    
    friend mint pow(mint a, long long p) {
        mint ans = 1;
        for (; p > 0; p /= 2, a *= a) {
            if (p & 1) ans *= a;
        }
        return ans;
    }
    
    friend mint operator+(mint a, mint b) { return a += b; }
    friend mint operator-(mint a, mint b) { return a -= b; }
    friend mint operator*(mint a, mint b) { return a *= b; }

    template <typename U>
    friend U& operator<<(U& stream, const mint& a) { return stream << a.v; }
};


const mint p = 3011;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<vector<pair<int, long long>>> adj(n);
    while (m--) {
        int x, y; long long w; cin >> x >> y >> w;
        adj[x - 1].push_back({y - 1, w});
    }
    vector<int> len(n, -1);              // distance of path
    vector<long long> edge(n);           // edge length of path
    vector<long long> sum(n);            // sum of path
    vector<vector<mint>> hash(n);        // hash of path, where hash[v][i] is the hash of the first 2^i edges
    vector<vector<int>> desc(n);         // descendants of path, where desc[v][i] is the node down 2^i edges
    function<void(int)> dfs = [&](int v) -> void {
        if (len[v] != -1) return;
        int mx = -1; long long lex = -1;
        vector<int> canidate;
        for (auto [nv, w] : adj[v]) {
            dfs(nv);
            if (len[nv] > mx || (len[nv] == mx && w < lex)) {
                canidate.clear();
                mx = len[nv];
                lex = w;
            }
            if (len[nv] > mx || (len[nv] == mx && w <= lex)) canidate.push_back(nv);
        }
        // no canidates, then return empty path
        if (canidate.size() == 0) {
            len[v] = 0;
            sum[v] = 0;
            return;
        }
        vector<int> z = canidate;  // copy of canidate
        int s = (int) hash[canidate[0]].size();
        int index = 0;
        for (int i = 0; i < s; ++i) {
            bool same = true;
            for (int nv : canidate) {
                if (hash[nv][i].v == hash[canidate[0]][i].v) continue;
                same = false;
                break;
            }
            if (same && i != s - 1) continue;
            if (same && i == s - 1) {
                for (auto& nv : canidate) {
                    nv = desc[nv][i];
                }
                 s = (int) hash[canidate[0]].size();
                i = -1;
                continue;
            }
            if (i == 0) {
                for (int j = 0; j < (int) canidate.size(); ++j) {
                    if (edge[canidate[j]] < edge[canidate[index]]) index = j;
                }
                break;
            }
            for (auto& nv : canidate) {
                nv = desc[nv][i - 1];
            }
            s = (int) hash[canidate[0]].size();
            i = -1;
        }
        int fin = z[index];
        len[v] = len[fin] + 1;
        edge[v] = lex;
        sum[v] = sum[fin] + lex;
        desc[v].push_back(fin);
        while (desc[desc[v].back()].size() >= desc[v].size()) {
            desc[v].push_back(desc[desc[v].back()][desc[v].size() - 1]);
        }
        hash[v].push_back((mint) lex);
        for (int i = 1; i < (int) desc[v].size(); ++i) {
            hash[v].push_back(hash[v].back() + hash[desc[v][i - 1]][i - 1] * pow(p, pow((mint) 2, i - 1).v));
        }
    };
    for (int i = 0; i < n; ++i) dfs(i);
    for (int i = 0; i < n; ++i) {
        cout << len[i] << " " << sum[i] << '\n';
    }
}
