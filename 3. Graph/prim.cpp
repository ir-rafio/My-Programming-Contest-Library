#include <bits/stdc++.h>

// code n drink Pennyroyal tea
#ifdef Pennyroyal
#include <debug.h>
#else
#define debug(...)
#define sdebug(...)
#endif

using namespace std;
using ll = long long;

const int nmax = 1e5 + 5;

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

void solve(void) {
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({w, u, v});
        adj[v].push_back({w, v, u});
    }

    prim(1);

    if (size(mst) != n - 1) {
        cout << "IMPOSSIBLE";
        return;
    }

    ll cost = 0;
    for (auto [w, u, v] : mst) {
        cost += w;
    }

    cout << cost;
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}