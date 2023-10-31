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
const int mmax = 2e5 + 5;

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

/*
5 5
1 2
3 1
3 4
4 5
5 3
*/

void solve(void) {
    cin >> n >> m;

    clear();

    for(int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back({v, i});
        
        in[v]++;
        out[u]++;
    }

    if(!canTour()) {
        cout << "no Eulerian Path exists\n";
    }
    else {
        DFS(findRoot());

        if(size(path) != m + 1) {
            cout << "no Eulerian Path exists\n";
        }
        else {
            reverse(path.begin(), path.end());
            for(auto node : path) {
                cout << node << ' ';
            }
            cout << '\n';
        }
    }
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}