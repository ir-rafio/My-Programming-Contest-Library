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
	int res=LLONG_MAX, k;

	while(l<=r)
	{
		k=__lg(r-l+1);
		res=min(res, sparseTable[l][k]);
		l+=1<<k;
	}

	return res;
}