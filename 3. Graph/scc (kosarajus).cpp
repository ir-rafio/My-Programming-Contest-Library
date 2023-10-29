#include <bits/stdc++.h>

// code n drink Pennyroyal tea
#ifdef Pennyroyal
#include <debug.h>
#else
#define debug(...)
#define sdebug(...)
#endif

using namespace std;
using ll = long long;

/*
SCC: A connected component in graph, where you can reach
from any node to another node, i.e. for all pairs of node
(u, v), there's a path from u to v, and also there's a path
from v to u.

Usage:
# Condensed Graph: It's a DAG where each node is an SCC of the
                the original Graph.
To get DAG: Topological sort isn't able to provide a DAG
            when the graph has cycles. In that case,
            for getting DAG, Condensed Graph is useful.

Algo:
1. Almost topsort (ignore cycle)
2. DFS on nodes in almost topsort order on the reveresed graph.
    The components here are the SCC.

Input:
7 10
2 1
5 1
5 4
4 2
2 3
3 4
5 6
6 5
7 6
7 3

scc:
1 {7}
2 {5, 6}
3 {2, 3, 4}
4 {1}

condensed (DAG):
1 {2, 3}
2 {3, 4}
3 {4}
4 {}
*/

// tested: https://cses.fi/problemset/task/1686

struct SCC {
    vector<vector<int>> g, rg, scc, condensed;
    vector<int> topsort, vis, who;
    int comp, n;
    void init(int n) {
        this->n = n;
        g.assign(n + 1, {});
        rg.assign(n + 1, {});
        vis.assign(n + 1, 0);
        topsort.clear();
        who.assign(n + 1, 0);
        comp = 0;
    }
    SCC(int n = 0) {
        init(n);
    }
    void addEdge(int u, int v) {
        g[u].push_back(v);
        rg[v].push_back(u);
    }
    void dfs1(int u) {
        vis[u] = 1;
        for (int v : g[u]) {
            if (!vis[v]) dfs1(v);
        }
        topsort.push_back(u);
    }
    void dfs2(int u) {
        who[u] = comp;
        for (int v : rg[u]) {
            if (!who[v]) dfs2(v);
        }
    }
    void build() {
        for (int i = 1; i <= n; i++) {
            if (!vis[i]) dfs1(i);
        }
        reverse(topsort.begin(), topsort.end());
        for (int u : topsort) {
            if (!who[u]) {
                ++comp;
                dfs2(u);
            }
        }
        scc.assign(comp + 1, {});
        for (int i = 1; i <= n; i++) {
            scc[who[i]].push_back(i);
        }
        condensed.assign(comp + 1, {});
        for (int u = 1; u <= n; u++) {
            for (int v : g[u]) {
                if (who[u] != who[v]) {
                    condensed[who[u]].push_back(who[v]);
                }
            }
        }
    }
} scc;

void solve() {
    int n, m; cin >> n >> m;
    scc.init(n);
    vector<int> coins(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> coins[i];
    }
    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        scc.addEdge(u, v);
    }
    scc.build();
    vector<ll> condensedCoin(scc.comp + 1);
    for (int i = 1; i <= scc.comp; i++) {
        for (auto j : scc.scc[i]) {
            condensedCoin[i] += coins[j];
        }
    }
    /// no need new topsort for condensed graph as
    // the algorithm outputs the components in topsorted order!
    vector<ll> dp(scc.comp + 1);
    for (int v = scc.comp; v >= 1; v--) {
        for (auto u : scc.condensed[v]) {
            dp[v] = max(dp[v], dp[u]);
        }
        dp[v] += condensedCoin[v];
    }
    cout << *max_element(begin(dp), end(dp)) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr); 

    solve();

    return 0;   
}