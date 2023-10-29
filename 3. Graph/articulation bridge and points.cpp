#include <bits/stdc++.h>

// code n drink Pennyroyal tea
#ifdef Pennyroyal
#include <debug.h>
#else
#define debug(...)
#define sdebug(...)
#endif

using namespace std;

/*
bridge: removing the ith edge increases the number of
        componenet in the graph
cutPoints: removing the ith vertex increases the number of
        componenet in the graph

tin[v] -> entry time for node v (lower the value is, the higher v is)
low[v] -> using one edge how high we can reach from node v

tin[u] < low[v] -> the descendants of node v can't go
                    higher than node u, thus a bridge
*/

/*
tested:
https://cses.fi/problemset/task/2177
https://vjudge.net/problem/UVA-315
*/

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

void solve(void) {
    int n, m; cin >> n >> m;
    Articulation b(n);
    for (int i = 1; i <= m; i++) {
        int u, v; cin >> u >> v;
        b.addEdge(u, v, i);
        b.addEdge(v, u, i);
    }
    b.find_bridge();
    b.find_cutPoints();
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}