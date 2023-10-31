#include <bits/stdc++.h>

// code n drink Pennyroyal tea
#ifdef Pennyroyal
#include <debug.h>
#else
#define debug(...)
#define sdebug(...)
#endif

using namespace std;

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

void solve() {
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int>> edges(m);
    for (auto &[w, u, v] : edges) {
        cin >> u >> v >> w;
    }

    sort(edges.begin(), edges.end());

    int cost = 0;
    vector<tuple<int, int, int>> mst;
    
    DSU d(n + 1);
    for(int i = 1; i <= n; i++) {
        d.make_set(i);
    }

    for (auto [w, u, v] : edges) {
        if (d.find_set(u) != d.find_set(v)) {
            cost += w;
            mst.push_back({w, u, v});
            d.union_sets(u, v);
        }
    }

    if (size(mst) != n - 1) {
        cout << "The graph isn't connected\n";
        return;
    }

    cout << "Minimum cost:\n" << cost << "\n\n";
    cout << "Minimum Spanning Tree (u, v, w):\n";
    for (auto [w, u, v] : mst) {
        cout << u << ' ' << v << ' ' << w << '\n';
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

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}