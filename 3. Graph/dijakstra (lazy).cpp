ll d[nmax];
int parent[nmax];
vector<pair<int, int>> g[nmax];
vector<int> path;

priority_queue<pair<ll, int>> pq;

void dijkstra(int src) {
    d[src] = 0;
    pq.push({0, src});
    while (!pq.empty()) {
        auto [wu, u] = pq.top(); wu *= -1;
        pq.pop();
        if (d[u] < wu) continue;
        for (auto [v, wv] : g[u]) {
            if (d[u] + wv < d[v]) {
                d[v] = d[u] + wv;
                parent[v] = u;
                pq.push({-(d[u] + wv), v});
            }
        }
    }
}