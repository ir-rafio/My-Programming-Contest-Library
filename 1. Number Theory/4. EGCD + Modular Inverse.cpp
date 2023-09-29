int absMod(int a, int mod)
{
    return (mod+a%mod)%mod;
}

pair<int,int> egcd(int a, int b)
{
    if(b==0) return {1, 0};
    else
    {
        auto [x, y]=egcd(b, a%b);
        return {y, x-(a/b)*y};
    }
}

int modInverse(int a, int mod)
{
    if(mod<2) return -1;

    auto [x, y]=egcd(a, mod);
    int gcd=a*x+mod*y;
    if(gcd!=1) return -1;

    return absMod(x, mod);
}

const int N=1e7+5, MOD=1e9+7;
int inv[N];

void preCalcModInverse()
{
    inv[1]=1;

    int i, temp;
    for(i=2; i<N; i++)
    {
        temp=(MOD/i)*inv[MOD%i];
        inv[i]=MOD-temp%MOD;
    }
}