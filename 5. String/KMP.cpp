void buildLPS(string& pat, int nxt[])
{
    int i, m = pat.size();

    int l = 0;
    nxt[0] = 0;
    for(i = 1; i < m; i++)
    {
        char ch = pat[i];

        if(pat[l] == ch)
        {
            nxt[i] = l + 1;
            l++;
        }
        
        else if(l > 0)
        {
            l = nxt[l - 1];
            i--;
        }

        else
        {
            nxt[i] = 0;
            l = 0;
        }
    }
}

void runKMP(string& txt, string& pat, int nxt[], int res[])
{
    int i, m = pat.size(), n = txt.size();

    int l = 0;
    for(i = 0; i < n; i++)
    {
        char ch = txt[i];

        if(l < m && pat[l] == ch)
        {
            res[i] = l + 1;
            l++;
        }
        
        else if(l > 0)
        {
            l = nxt[l - 1];
            i--;
        }

        else
        {
            res[i] = 0;
            l = 0;
        }
    }
}
