#include <bits/stdc++.h>

// code n drink Pennyroyal tea
#ifdef Pennyroyal
#include <debug.h>
#else
#define debug(...)
#define sdebug(...)
#endif

using namespace std;

const int nmax = 1e5 + 5;
vector<int> g[nmax];

// 0: used cross edge
// 1: used back edge
// -1: that vertice has no more edge
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

// https://cses.fi/problemset/task/1678/

void solve(void) {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].emplace_back(v);
    }

    for (int i = 1; i <= n; i++) {
        if (!mark[i] && DFS(i)) {
            break;
        }
    }

    if (cycleStart == -1) {
        cout << -1 << '\n';
    }
    else {
        vector<int> cycle;

        cycle.emplace_back(cycleStart);
        for (int i = cycleEnd; i != cycleStart; i = parent[i]) {
            cycle.emplace_back(i);
        }

        cycle.emplace_back(cycleStart);
        reverse(cycle.begin(), cycle.end());

        for(auto it : cycle) cout << it << ' ';
    }
}

/*
4 5
1 3
2 1
2 4
3 2
3 4
*/

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}