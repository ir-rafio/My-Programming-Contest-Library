void factorize(int num, vector<pair<int,int>>& v)
{
    if(v.size()) v.clear();
 
    for(auto p: Primes)
    {
        if(num<N) break;
 
        if(p*p>num)
        {
            v.push_back({num, 1});
            num=1;
        }
 
        else if(num%p==0)
        {
            v.push_back({p, 0});
 
            while(num%p==0)
            {
                v.back().second++;
                num/=p;
            }
        }
    }
 
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
}