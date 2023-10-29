#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using llu = unsigned long long;

#define CEIL(x, y) ((x) + (y) - 1) / (y); 
#define PRINTCASE(tc) cout << "Case " << (tc) << ":\n"
#define ALL(con) begin(con), end(con)
#define SIZE(con) ((int)con.size())

#ifdef Pennyroyal
#include <debug.h>
#else
#define debug(...)
#endif

const int inf = 1e9 + 505;
const ll infll = 1e18 + 505;
const int MOD = 1000000007;

const int nmax = 1e5 + 5;
vector<int> g[nmax];

// 0: used cross edge
// 1: used back edge
// -1: that vertice has no more edge
int mark[nmax];

bool DFS(int u, int p) {
    mark[u] = 1;

    for (int v : g[u]) {
        if (v == p) continue;
        if (mark[v] == 1) return true;
        // else if (mark[v] == -1) return false;
        else if (mark[v] == 0 && DFS(v, u)) return true;
    }

    mark[u] = -1;
    return false;
}


// : Cycle detection for Undirected Graph using DFS
// : but wait. there's a diffault cycle for this. I can go u -> v -> u. Isn't it obvious?
// : Still we can find a cycle which is a circuit of different edges!!
//   backEdge(jekhane v != parent(u)) ? cycle : valo

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    bool backEdge = 0;
    for (int i = 1; i <= n; i++) {
        if (!mark[i]) {
            backEdge = DFS(i, -1);
        }
    }

    cout << (backEdge ? "Cycle :(\n" : "Valo! Valo!\n");
}

/*
4 4
1 2
1 3
2 3
2 4
*/

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testcase = 1;
    // cin >> testcase;
    for (int tc = 1; tc <= testcase; tc++) {
        // print_case(tc);
        solve();
    }

    return 0;
}