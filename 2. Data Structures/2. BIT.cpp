void BITadd(vector<int>& BIT, int i, int delta)
{
    int n=BIT.size()-1;

    while(i<=n)
    {
        BIT[i]+=delta;
        int mask=i&-i;
        i+=mask;
    }
}

int BITsum(vector<int>& BIT, int i)
{
    int ans=0;

    while(i)
    {
        ans+=BIT[i];
        int mask=i&-i;
        i-=mask;
    }

    return ans;
}

vector<int> BITbuild(vector<int>& ara) // ara is 0-indexed
{
    int i, n=ara.size();
    vector<int> BIT(n+1, 0);

    for(i=1; i<=n; i++) BITadd(BIT, i, ara[i-1]);
    return BIT;
}

void BITreplace(vector<int>& BIT, int i, int val) // i is 0-indexed
{
    int s=BITsum(BIT, i, i);
    BITadd(BIT, i+1, val-s);
}

int BITsum(vector<int>& BIT, int l, int r) // l and r are 0-indexed
{
    int p=BITsum(BIT, r+1);
    p-=BITsum(BIT, l);

    return p;
}
