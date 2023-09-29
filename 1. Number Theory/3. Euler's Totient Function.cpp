int totient(int num)
{
	vector<pair<int,int>> v=factorize(num);
	
	int ans=num;
	for(auto it: v) ans-=ans/it.first;

	return ans;
}

int totient(int num)
{
	int p=divisor[num];
	
	if(p==num) return p-1;
	return totient(p)*totient(num/p);
}

int boundedTotient(int num, int cap)
{
	vector<pair<int,int>> v=factorize(num);

	int i, j, k=v.size(), temp, ans=cap;
	int n=1<<k;

	for(i=1; i<n; i++)
	{
		temp=1;
		for(j=0; j<k; j++) if(i&(1<<j)) temp*=v[j].first;

		__builtin_popcount(i)&1? ans-=cap/temp: ans+=cap/temp;
	}

	return ans;
}