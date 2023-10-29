#include <bits/stdc++.h>

// Pennyroyal -> herbal for all the bugs
#ifdef Pennyroyal
#include <debug.h>
#else
#define debug(...)
#define sdebug(...)
#endif

using namespace std;
using ll = long long;

const int nmax = 2e5 + 1;
const ll inf = 1e18 + 505;

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

void genPath(int source, int destination) {
    if(parent[destination] == -1 && d[destination] == inf) {
        path.push_back(-1);
        return;
    }
    for(int i = destination; parent[i] != -1; i = parent[i]) { 
        path.push_back(i);
    }
    path.push_back(source);
    reverse(path.begin(), path.end());
}

void refresh(int n) {
    path.clear();
    for (int i = 0; i <= n; i++) {
        g[i].clear();
        d[i] = inf;
        parent[i] = -1;
    }
}

void solve() {
    int n, m; cin >> n >> m;
    refresh(n);
    for(int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        g[u].push_back({v, c});
        g[v].push_back({u, c});
    }

    dijkstra(1);
    for (int i = 1; i <= n; i++) {
        cout << d[i] << ' ';
    }
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr); 

    solve();

    return 0;   
}