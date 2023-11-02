class Articulation {
public:
    Articulation(int n) {
        reset(n);
    }

    void reset(int n) {
        this->n = n;
        g.clear();
        g.resize(n + 1);
        visited.assign(n + 1, false);
        timer = 1;
        tin.assign(n + 1, -1);
        low.assign(n + 1, -1);
        deltaComp.assign(n + 1, 0);
        bridges.clear();
        cutPoints.clear();
    }

    void addEdge(int u, int v, int edgeIndex) {
        g[u].push_back({v, edgeIndex});
    }

    vector<int> find_bridge() {
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                dfs(i, -1);
            }
        }
        return bridges;
    }

    vector<int> find_cutPoints() {
        for (int i = 1; i <= n; i++) {
            if (!visited[i]) {
                dfs(i, -1);
            }
        }
        for (int i = 1; i <= n; i++) {
            if (deltaComp[i] > 0) {
                cutPoints.push_back(i);
            }
        }
        return cutPoints;
    }

private:
    vector<vector<pair<int, int>>> g;
    vector<bool> visited;
    vector<int> tin, low;
    vector<int> bridges, cutPoints;
    vector<int> deltaComp; // the change in number of component if vertex i is removed
    int n, timer = 1;

    void dfs(int at, int p = 0, int parEdge = -1) {
        visited[at] = true;
        tin[at] = low[at] = timer++;
        int children = 0;
        for (auto [to, ei] : g[at]) {
            if (ei == parEdge) continue;
            if (visited[to]) {
                low[at] = min(low[at], tin[to]);
            }
            else {
                dfs(to, at, ei);
                low[at] = min(low[at], low[to]);
                if (tin[at] < low[to]) {
                    bridges.push_back(ei);
                }
                if (p != -1 and tin[at] <= low[to]) {
                    deltaComp[at]++;
                }
                children++;
            }
        }
        if (p == -1 and children > 1) {
            deltaComp[at] = children - 1;
        }
    }
};