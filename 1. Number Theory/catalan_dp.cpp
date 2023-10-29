#include <bits/stdc++.h>

/*
@uthor: Nasrum Nur
---------------------------
code n drink Pennyroyal tea
*/

#ifdef Pennyroyal
#include <debug.h>
#else
#define debug(...)
#define sdebug(...)
#endif

using namespace std;

const int nmax = 1e4 + 1;
const int mod = 1000000007;
int catalan[nmax + 1];

void genCatalan(int n) {
    catalan[0] = catalan[1] = 1;
    for (int i = 2; i <= n; i++) {
    	catalan[i] = 0;
        for (int j = 0; j < i; j++) {
            catalan[i] += (catalan[j] * catalan[i - j - 1]) % mod;
            if (catalan[i] >= mod) {
                catalan[i] -= mod;
            }
        }
    }
}

void solve(void) {
    for (int i = 0; i <= 10; i++)
        cerr << catalan[i] << ' ';

    cerr << '\n';
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    genCatalan(nmax);
    solve();

    return 0;
}