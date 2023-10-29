#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using llu = unsigned long long;

#define Ceil(x, y)      ((x) + (y) - 1) / (y); 
#define Print_Case(tc)  cout << "Case " << (tc) << ":\n"
#define All(con)        begin(con), end(con)
#define Size(con)       ((int)con.size())

#ifdef Pennyroyal
#include <debug.h>
#else
#define debug(...)
#endif

const int inf = 1e9 + 505;
const ll infll = 1e18 + 505;
const int MOD = 1000000007;

const int nmax = 1e5 + 5;

int n, m;

struct Edge {
    int u = -1, v = -1, w = inf;
    bool operator <(Edge const& other) const {
        return w > other.w;
    }
};

vector<Edge> adj[nmax];
vector<Edge> mst;

void prim(int root) {
    vector<bool> marked(n + 1, false); 

    priority_queue<Edge> pq;

    pq.push({-1, 1, 0});

    while (!pq.empty()) {
        int u = pq.top().u;
        int v = pq.top().v;
        int w = pq.top().w;

        pq.pop();

        if (marked[v]) continue;
        marked[v] = true;

        if (u != -1) mst.push_back({u, v, w});

        for (auto e : adj[v]) {
            int to = e.v;
            if (marked[to] == false)
                pq.push({v, e.v, e.w});
        }
    }
}

void solve(void) {
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({u, v, w});
        adj[v].push_back({v, u, w});
    }

    prim(1);

    if (Size(mst) != n - 1) {
        cout << "IMPOSSIBLE";
        return;
    }

    ll cost = 0;
    for (auto it : mst) {
        cost += it.w;
    }

    cout << cost;
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testcase = 1;
    // cin >> testcase;
    for (int tc = 1; tc <= testcase; tc++) {
        solve();
    }

    return 0;
}