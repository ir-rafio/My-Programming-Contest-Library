#include <bits/stdc++.h>

/*
@uthor: Nasrum Nur
---------------------------
code n drink Pennyroyal tea
*/

using namespace std;
using ll = long long;

const int nmax = 2e5 + 1;
bool mark[nmax];

vector<int> primes;
void sieve(int l, int r) {      // O(r - l)
    for (ll i = 2; i * i <= r; i++) {
        for (ll j = max(i * i, (l + (i - 1)) / i * i); j <= r; j += i)
            mark[j - l] = 1;
    }
    for (ll i = max(2, l); i <= r; i++) {
        if (!mark[i - l])
            primes.push_back(i);
    }
}

void solve(void) {
	for (auto i : primes) cerr << i << ' ';
	cerr << '\n';
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    sieve(1e9, 1e9 + 100);
    solve();

    return 0;
}