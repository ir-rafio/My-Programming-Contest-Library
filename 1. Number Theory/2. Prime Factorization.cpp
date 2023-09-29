vector<pair<int,int>> factorize(int num)
{
	vector<pair<int,int>> v;

	while(num>1)
	{
		int p=divisor[num];
		v.push_back({p, 0});

		while(num%p==0)
		{
			v.back().second++;
			num/=p;
		}
	}

	return v;
}