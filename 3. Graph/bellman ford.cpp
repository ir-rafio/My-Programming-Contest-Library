int n, m;
ll d[nmax];
pair<int, int> e[mmax];
ll cost[mmax];
int parent[nmax];

void refresh(int n) {
    for(int i = 0; i <= n; i++) {
        d[i] = inf;
    }
}

bool bellmanFord(int source) {
    bool negCycle;
    d[source] = 0;
    for (int i = 1; i <= n; i++) {
        bool done = true;
        negCycle = false;
        for (int j = 0; j < m; j++) {
            auto [u, v] = e[j]; int w = cost[j];
            if (d[u] < inf) {
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    done = false;
                    negCycle = true;
                }
            }
        }
        if (done) break;
    }
    return negCycle;
}