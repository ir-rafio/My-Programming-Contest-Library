/*
Usage:
# Condensed Graph: It's a DAG where each node is an SCC of the
                the original Graph.
To get DAG: Topological sort isn't able to provide a DAG
            when the graph has cycles. In that case,
            for getting DAG, Condensed Graph is useful.
*/
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