vector<int> g[nmax];
int mark[nmax];

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