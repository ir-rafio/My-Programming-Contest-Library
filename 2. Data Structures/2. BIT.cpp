void BITadd(vector<int>& BIT, int i, int delta)
{
    int n=BIT.size()-1;

    while(i<=n)
    {
        BIT[i]+=delta;
        i+=i&-i;
    }
}

int BITsum(vector<int>& BIT, int i)
{
    int ans=0;

    while(i)
    {
        ans+=BIT[i];
        i-=i&-i;
    }

    return ans;
}

int BITsum(vector<int>& BIT, int i, int j)
{
    if(i>j) return 0;

    int p=BITsum(BIT, j+1);
    p-=BITsum(BIT, i);

    return p;
}

vector<int> BITbuild(vector<int>& ara)
{
    int i, n=ara.size();
    vector<int> BIT(n+1, 0);

    for(i=1; i<=n; i++) BITadd(BIT, i, ara[i-1]);
    return BIT;
}

void BITreplace(vector<int>& BIT, int i, int p)
{
    int q=BITsum(BIT, i, i);
    BITadd(BIT, i+1, p-q);
}