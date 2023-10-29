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
using ll = long long;

/**
 *** From Benq's template
 * Description: Modular arithmetic. Assumes $MOD$ is prime.
 * Source: KACTL
 * Verification: https://open.kattis.com/problems/modulararithmetic
 * Usage: mi a = MOD+5; inv(a); // 400000003
 */
template<int MOD> struct mint {
	static const int mod = MOD; int v; 
 	explicit operator int() const { return v; } 
	mint() : v(0) {}
	mint(ll _v) : v(int(_v % MOD)) { v += (v < 0) * MOD; }
	mint& operator+=(mint o) { 
		if ((v += o.v) >= MOD) v -= MOD; return *this; }
	mint& operator-=(mint o) { 
		if ((v -= o.v) < 0) v += MOD; return *this; }
	mint& operator*=(mint o) { 
		v = int((ll)v * o.v % MOD); return *this; }
	friend mint pow(mint a, ll p) {
		assert(p >= 0);
		return p == 0 ? 1 : pow(a * a, p / 2) * (p & 1 ? a : 1);
	}
	friend mint inv(mint a) { assert(a.v != 0); return pow(a, MOD - 2); }
	friend mint operator+(mint a, mint b) { return a += b; }
	friend mint operator-(mint a, mint b) { return a -= b; }
	friend mint operator*(mint a, mint b) { return a *= b; }
};

using mi = mint<(int)1e9+7>;

int getDrng(int n) {
	mi c = 1;
	for (int i = 1; i <= n; i++) {
		c = (c * i) + (i & 1 ? -1 : 1);
		// cerr << c.v << '\n';
	}
	return c.v;
}

void solve(void) {
	cerr << getDrng(2) << '\n';
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}