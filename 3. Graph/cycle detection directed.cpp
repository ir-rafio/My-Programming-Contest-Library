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

// these are for printing the cycle
int cycleStart = -1, cycleEnd = -1;
int parent[nmax];

bool DFS(int u) {
    mark[u] = 1;

    for (int v : g[u]) {
        if (mark[v] == 1) {
            cycleStart = v;
            cycleEnd = u;
            return true;
        }
        else if (mark[v] == 0) {
            parent[v] = u;
            if(DFS(v)) return true;
        }
    }

    mark[u] = -1;
    return false;
}

// https://cses.fi/problemset/task/1678/
// --------------------------------------------
// Cycle detection and generating cycle for Directed Graph
// backEdge ? printCycle() : print(-1)

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (!mark[i] && DFS(i)) {
            break;
        }
    }

    if (cycleStart == -1) {
        cout << -1 << '\n';
    }
    else {
        vector<int> cycle;

        cycle.emplace_back(cycleStart);
        for (int i = cycleEnd; i != cycleStart; i = parent[i]) {
            cycle.emplace_back(i);
        }

        cycle.emplace_back(cycleStart);
        reverse(ALL(cycle));

        for(auto it : cycle) cout << it << ' ';
    }
}

/*
4 5
1 3
2 1
2 4
3 2
3 4
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