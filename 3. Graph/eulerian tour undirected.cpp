int n, m;
vector<pair<int, int>> g[nmax];

int done[nmax], visited[mmax];
vector<int> path;

void clear() {
    for(int i = 0; i < nmax; i++) {
        done[i] = 0;
        g[i].clear();
    }
    for(int i = 0; i < mmax; i++) visited[i] = 0;
    path.clear();
}

void DFS(int u) {
    while(done[u] < size(g[u])) {
        auto e = g[u][done[u]++];
        if(visited[e.second]) continue;
        visited[e.second] = 1;
        DFS(e.first);
    }
    path.emplace_back(u);
}

bool canTour(int n) {
    int edges = 0;
    vector<int> deg(n + 1);
    for(int u = 1; u <= n; u++) {
        for(auto e : g[u]) {
            deg[e.first]++;
            deg[u]++;
            edges++;
        }
    }

    int odd = 0, root = 0;
    for(int i = 1; i <= n; i++) {
        if(odd > 2) return false;
        if(deg[i] & 1)
            odd++, root = i;
    }

    if(root == 0) {
        for(int i = 1; i <= n; i++)
            if(deg[i]) root = i;
    }

    if(!root) return true;

    DFS(root);

    if(size(path) != edges / 2 + 1) return false;
    
    reverse(path.begin(), path.end());
    return true;
}