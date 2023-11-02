int n, m;
vector<pair<int, int>> g[nmax];

int in[nmax], out[nmax];
int done[nmax], visited[mmax];
vector<int> path;

void clear() {
    for(int i = 0; i <= n; i++) {
        in[i] = out[i] = 0;
        g[i].clear();
    }
    path.clear();
}

bool canTour() {
    int startNode = 0, endNode = 0;
    for(int i = 1; i <= n; i++) {
        if(abs(out[i] - in[i]) > 1) return false;
        else if(out[i] - in[i] == 1)
            startNode++;
        else if(in[i] - out[i] == 1)
            endNode++;
    }
    return (startNode == 0 && endNode == 0) || (startNode == 1 && endNode == 1);
}

int findRoot() {
    int root = -1;
    for(int i = 1; i <= n; i++) {
        if(out[i] - in[i] == 1) return i;
        if(out[i] > 0) root = i;
    }
    return root;
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