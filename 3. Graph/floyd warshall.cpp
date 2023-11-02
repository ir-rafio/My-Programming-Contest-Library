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