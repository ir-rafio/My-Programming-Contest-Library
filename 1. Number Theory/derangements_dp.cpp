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

const int mod = 1000000007;

const int nmax = 2e5 + 1;
int drng[nmax + 1];

void gen_drng(int n) {
	drng[2] = 1;
	for (int i = 3; i <= n; i++) {
		drng[i] = ((i - 1ll) * ((drng[i - 2] + drng[i - 1]) % mod)) % mod;
	}
}

void solve(void) {
	cout << drng[3] << '\n';
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    gen_drng(nmax);
    solve();

    return 0;
}