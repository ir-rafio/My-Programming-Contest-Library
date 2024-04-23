vector<vector<int>> sparseTableBuild(vector<int>& v)
{
    int i, j, k, n=v.size();
    vector<vector<int>> sparseTable(n);
 
    for(i=0; i<n; i++) sparseTable[i].push_back(v[i]);
    for(j=0; ; j++)
    {
        k=1<<j;
        if(k>=n) break;
 
        for(i=0; i+2*k<=n; i++)
            sparseTable[i].push_back(min(sparseTable[i][j], sparseTable[i+k][j]));
    }
 
    return sparseTable;
}
 
int sparseTableQuery(vector<vector<int>>& sparseTable, int l, int r)
{
    int k=__lg(r-l+1);
    return min(sparseTable[l][k], sparseTable[r-(1<<k)+1][k]);
}
