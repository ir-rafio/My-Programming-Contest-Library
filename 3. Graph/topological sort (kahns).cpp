#include <bits/stdc++.h>

// code n drink Pennyroyal tea
#ifdef Pennyroyal
#include <dbg.h>
#else
#define dbg(...)
#endif

using namespace std;

const int nmax = 2e5 + 1;

vector<int> g[nmax];
int indeg[nmax];
vector<int> topsort;

void bfs(int n) {
    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (!indeg[i]) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        topsort.push_back(u);
        for (auto v : g[u]) {
            indeg[v]--;
            if (!indeg[v]) {
                q.push(v);
            }
        }
    }
}

void refresh(int n) {
    topsort.clear();
    for (int i = 0; i <= n; i++) {
        g[i].clear();
        indeg[i] = 0;
    }
}

void solve() {
    int n, m; cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        indeg[v]++;
    }
    
    bfs(n);
    
    if (size(topsort) != n) cout << "IMPOSSIBLE";
    else {
        for (auto i : topsort) cout << i << ' ';
    }
    
}

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(nullptr); 

    solve();

    return 0;   
}