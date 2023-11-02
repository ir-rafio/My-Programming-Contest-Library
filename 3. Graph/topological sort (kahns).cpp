vector<int> g[nmax];
int indeg[nmax];
vector<int> topsort;

void bfs(int n) {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!indeg[i]) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topsort.push_back(u);
        for (auto v : g[u]) {
            indeg[v]--;
            if (!indeg[v]) {
                q.push(v);
            }
        }
    }
}