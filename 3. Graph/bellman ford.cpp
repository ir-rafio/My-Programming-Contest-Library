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

const int nmax = 1e4 + 3, mmax = 1e4 + 3;
const ll inf = 1e18 + 505;

int n, m;
ll d[nmax];
pair<int, int> e[mmax];
ll cost[mmax];
int parent[nmax];

void refresh(int n) {
    for(int i = 0; i <= n; i++) {
        d[i] = inf;
    }
}

bool bellmanFord(int source) {
    bool negCycle;
    d[source] = 0;
    for (int i = 1; i <= n; i++) {
        bool done = true;
        negCycle = false;
        for (int j = 0; j < m; j++) {
            auto [u, v] = e[j]; int w = cost[j];
            if (d[u] < inf) {
                if (d[u] + w < d[v]) {
                    d[v] = d[u] + w;
                    done = false;
                    negCycle = true;
                }
            }
        }
        if (done) break;
    }
    return negCycle;
}

void solve() {
    cin >> n >> m;
    refresh(n);
    for(int i = 0; i < m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        e[i] = {u, v};
        cost[i] = c;
    }

    bellmanFord(1);

    for(int i = 1; i <= n; i++) cout << d[i] << ' ';
    cout << '\n';
}

int32_t main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}