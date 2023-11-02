int n, m;

vector<tuple<int, int, int>> adj[nmax];
vector<tuple<int, int, int>> mst;

void prim(int root) {
    vector<bool> marked(n + 1, false); 
    priority_queue<tuple<int, int, int>> pq;
    pq.push({0, -1, 1});
    while (!pq.empty()) {
        auto [w, u, v] = pq.top();
        w *= -1;
        pq.pop();
        if (marked[v]) continue;
        marked[v] = true;
        if (u != -1) mst.push_back({w, u, v});
        for (auto [ew, eu, ev] : adj[v]) {
            if (marked[ev] == false)
                pq.push({-ew, v, ev});
        }
    }
}