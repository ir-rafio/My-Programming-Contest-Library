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

const ll inf = 1e18 + 505;
const int nmax = 505;

int n, m;

ll d[nmax][nmax];
int link[nmax][nmax];

void floydWarshall() {
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                    link[i][j] = link[i][k];
                }
            }
        }
    }
}

void negativeCycle() {
    for(int k = 1; k <= n; k++) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                if(d[i][k] < inf && d[k][j] < inf && d[k][k] < 0) {
                    d[i][j] = -inf;
                }
            }
        }
    }
}

void clear(int n) {
    for(int u = 1; u <= n; u++) {
        for(int v = 1; v <= n; v++) {
            if(u == v) {
                d[u][v] = 0;
                d[v][u] = 0;
            }
            else {
                d[u][v] = inf;
                d[v][u] = inf;
            }
        }
    }
}

void solve() {
    int q;
    cin >> n >> m >> q;
    
    clear(n);    

    for(int i = 0; i < m; i++) {
        int u, v;
        ll c;
        cin >> u >> v >> c;
        d[u][v] = min(d[u][v], c);
        d[v][u] = min(d[v][u], c);
        link[u][v] = v;
        link[v][u] = u;
    }

    floydWarshall();
    negativeCycle();

    while(q--) {
        int a, b;
        cin >> a >> b;
        if(d[a][b] == inf) {
            cout << "Not connected\n\n";
        }
        else if(d[a][b] == -inf) {
            cout << "Negative Cycle\n\n";
        }
        else {
            cout << d[a][b] << '\n';
            int u = a, v = b;
            cout << u << ' ';
            while(u != v) {
                u = link[u][v];
                cout << u << ' ';
            }
            cout << '\n';
            cout << '\n';
        }
    }
}

int32_t main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}