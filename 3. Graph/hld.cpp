int sub[nmax], par[nmax], depth[nmax];
vector<int> adj[nmax];

void dfs_sz(int u, int p){
    sub[u] = 1, par[u] = p;
    depth[u] = (p == -1)? 0 : depth[p]+1;
    int mx = 0;     ///HLD
    for(auto &v: adj[u]){
        if(v == p) continue;
        dfs_sz(v, u);
        sub[u] += sub[v];
        if(sub[v] > mx) mx = sub[v], swap(v, adj[u][0]);  /// HLD
    }
}

int head[nmax];
int st[nmax], en[nmax], clk;
int dfsarr[nmax];       /// segtree will be built on this

void dfs_hld(int u, int p){
    st[u] = ++clk;
    /// put stuff in dfarr here
    dfsarr[clk] = val[u];       /// node specific value

    head[u] = (p != -1 && adj[p][0] == u)? head[p] : u; /// HLD
    for(auto &v : adj[u]){
        if(v == p) continue;
        dfs_hld(v, u);
    }
    en[u] = clk;
}

int lca(int a, int b){
    for(; head[a] != head[b]; b = par[head[b]])
        if(depth[head[a]] > depth[head[b]]) swap(a, b);
    if(depth[a] > depth[b]) swap(a, b);
    return a;
}

// process node u upto it's ancestor a
// if excl is true, a will not be processed
int chainProcess(int a, int u, bool excl = false){
    for(;head[u] != head[a];u = par[head[u]]){
        func(st[head[u]], st[u]);  // processing
        //query(1, 1, n, st[head[u]], st[u])
    }
    func(st[a]+excl, st[u]); // processing
}

// process path from node u to node v, if order matters will be tough
// if excl is true lca will not be processed
int pathProcess(int a, int b, bool excl){
    for(; head[a] != head[b]; b = par[head[b]]){
        if(depth[head[a]] > depth[head[b]]) swap(a, b);
        func(st[head[b]], st[b]);
    }
    if(depth[a] > depth[b]) swap(a, b);
    func(st[a] + excl, st[b]);
}