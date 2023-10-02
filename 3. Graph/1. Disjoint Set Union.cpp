const int N=1e7+5;
vector<int> parent(N, -1);
vector<int> depth(N);
 
void make_set(int v)
{
    if(parent[v]>=0) return;

    parent[v]=v;
    depth[v]=0;
}
 
int find_root(int v)
{
    int pr=parent[v];
    if(pr==v || pr<0) return pr;
 
    int root=find_root(pr);
    return parent[v]=root;
}

void union_sets(int a, int b)
{
    a=find_root(a);
    b=find_root(b);

    if(a==b || a<0 || b<0) return;
    if(depth[a]<depth[b]) swap(a, b);

    parent[b]=a;
    if(depth[a]==depth[b]) depth[a]++;
}