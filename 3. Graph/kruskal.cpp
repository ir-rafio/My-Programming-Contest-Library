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

struct DSU {
    vector<int> parent, size;
    DSU(int n) {
        parent.assign(n, -1);
        size.assign(n, 0);
    }
    void make_set(int v) {
        parent[v] = v;
        size[v] = 1;
    }
    int find_set(int v) {
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    }
    void union_sets(int a, int b) {
        a = find_set(a);
        b = find_set(b);
        if (a != b) {
            if (size[a] < size[b]) swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

struct Edge {
    int u, v, w;
    bool operator <(Edge const& other) {
        return w < other.w;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].w;
    }

    sort(All(edges));

    int cost = 0;
    vector<Edge> mst;
    
    DSU d(n + 1);
    for(int i = 1; i <= n; i++) {
        d.make_set(i);
    }

    for (Edge e : edges) {
        if (d.find_set(e.u) != d.find_set(e.v)) {
            cost += e.w;
            mst.push_back(e);
            d.union_sets(e.u, e.v);
        }
    }

    if (Size(mst) != n - 1) {
        cout << "The graph isn't connected\n";
        return;
    }

    cout << "Minimum cost:\n" << cost << "\n\n";
    cout << "Minimum Spanning Tree (u, v, w):\n";
    for (Edge e : mst) {
        cout << e.u << ' ' << e.v << ' ' << e.w << '\n';
    }
    cout << '\n';
}

/*
6 9
5 4 9
5 1 4
4 2 3
1 2 2
4 1 1
4 3 5
6 2 7
6 3 8
3 2 3
*/

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}