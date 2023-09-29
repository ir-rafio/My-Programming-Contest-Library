vector<int> divisor(1e7+5);
vector<int> Primes;

void Sieve()
{
    int i, j, n=divisor.size();
    for(i=0; i<n; i++) divisor[i]=i;

    for(i=2; i<n; i++) if(divisor[i]==i)
    {
        Primes.push_back(i);
        for(j=i*i; j<n; j+=i) if(divisor[j]==j) divisor[j]=i;
    }
}