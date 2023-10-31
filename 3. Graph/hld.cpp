#include <bits/stdc++.h>

using namespace std;
using ll = long long;

/// https://judge.yosupo.jp/problem/vertex_add_path_sum

const int nmax = 5e5+10;
int val[nmax];
int sub[nmax], par[nmax], depth[nmax];
vector<int> adj[nmax];

void dfs_sz(int u, int p){
    sub[u] = 1;
    par[u] = p;
    depth[u] = (p == -1)? 0 : depth[p] + 1;
    int mx = 0;
    for (auto &v : adj[u]) {
        if (v == p) continue;
        dfs_sz(v, u);
        sub[u] += sub[v];
        if (sub[v] > mx) mx = sub[v], swap(v, adj[u][0]);
    }
}

int head[nmax];
int st[nmax], en[nmax], clk;
int dfsarr[nmax];

void dfs_hld(int u, int p){
    st[u] = ++clk;
    dfsarr[clk] = val[u];
    head[u] = (p != -1 && adj[p][0] == u) ? head[p] : u;
    for (auto &v : adj[u]){
        if (v == p) continue;
        dfs_hld(v, u);
    }
    en[u] = clk;
}

typedef ll node;
struct seg_tree {
    #define lc (n << 1)
    #define rc ((n << 1) | 1)
    const node neutral = 0;
    node t[4 * nmax];

    void reset(int n) {
        memset(t, 0, sizeof t);
    }

    inline node merge(node a, node b) {
        return a + b;
    }

    inline void pull(int n) {
        t[n] = t[lc] + t[rc];
    }

    void build(int n, int b, int e) {
        if (b == e) {
            t[n] = dfsarr[b];
            return;
        }
        int mid = (b + e) >> 1;
        build(lc, b, mid);
        build(rc, mid + 1, e);
        pull(n);
    }

    void update(int n, int b, int e, int i, int x) {
        if (b > i || e < i) return;
        if (b == e && b == i) {
            t[n] += x;
            return;
        }
        int mid = (b + e) >> 1;
        update(lc, b, mid, i, x);
        update(rc, mid + 1, e, i, x);
        pull(n);
    }

    node query(int n, int b, int e, int i, int j) {
        if (b > j || e < i) return neutral;
        if (b >= i && e <= j) return t[n];
        int mid = (b + e) >> 1;
        return merge(query(lc, b, mid, i, j), query(rc, mid + 1, e, i, j));
    }
} segTree;

int n;
ll pathProcess(int a, int b, bool excl = false) {
    ll ret = 0;
    for(; head[a] != head[b]; b = par[head[b]]) {
        if (depth[head[a]] > depth[head[b]]) swap(a, b);
        ret += segTree.query(1, 1, n, st[head[b]], st[b]);
    }
    if (depth[a] > depth[b]) swap(a, b);
    ret += segTree.query(1, 1, n, st[a] + excl, st[b]);
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int q;
    cin >> n >> q;

    for (int i = 0; i < n; i++) cin >> val[i];

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs_sz(0, -1);
    dfs_hld(0, -1);

    segTree.reset(n);
    segTree.build(1, 1, n);

    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int u, x; cin >> u >> x;
            segTree.update(1, 1, n, st[u], x);
        }
        else {
            int u, v; cin >> u >> v;
            cout << pathProcess(u, v, false) << "\n";
        }
    }

    return 0;
}
