vector<vector<int>> ancestorTableBuild(vector<int>& parent)
{
    int i, n=parent.size();
    vector<vector<int>> ancestorTable(n);

    for(i=0; i<n; i++) if(parent[i]>=0) ancestorTable[i].push_back(parent[i]);
    
    bool flag=1;
    int ancestor, k=1;
    while(flag)
    {
        flag=0;

        for(i=0; i<n; i++) if(ancestorTable[i].size()==k)
        {
            ancestor=ancestorTable[i][k-1];
            if(ancestorTable[ancestor].size()<k) continue;

            flag=1;
            ancestorTable[i].push_back(ancestorTable[ancestor][k-1]);
        }

        k++;
    }

    return ancestorTable;
}
 
int kthAncestor(vector<vector<int>>& ancestorTable, int x, int k)
{
    int temp;

    while(k)
    {
        temp=__lg(k);
        if(ancestorTable[x].size()<=temp) return -1;
        x=ancestorTable[x][temp];
        k-=1<<temp;
    }

    return x;
}

void getTreeDepth(vector<vector<int>>& children, int src, vector<int>& depth, int srcDepth)
{
    depth[src]=srcDepth;
    for(auto it: children[src]) getTreeDepth(children, it, depth, srcDepth+1);
}

int lca(vector<vector<int>>& ancestorTable, vector<int>& depth, int x, int y)
{
    if(depth[x]>depth[y]) swap(x, y);
    y=kthAncestor(ancestorTable, y, depth[y]-depth[x]);

    int ax, ay, lo=0, hi=depth[x], mid, ans=-1;
    while(lo<=hi)
    {
        mid=lo+hi>>1;

        ax=kthAncestor(ancestorTable, x, mid);
        ay=kthAncestor(ancestorTable, y, mid);

        if(ax==ay) ans=ax, hi=mid-1;
        else lo=mid+1;
    }

    return ans;
}