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

int egcd(int a, int b, int& x, int& y) {
	if (b == 0) {
    	x = 1, y = 0;
		return a;
	}
	int x1, y1, d;
	d = egcd(b, a % b, x1, y1);
	x = y1, y = x1 - y1 * (a / b);
	return d;
}

// returns the kth solution of ax+by=c
/*
12x+98y=c
0th solution, (x, y) = (-240, 30)
1st solution, (x, y) = (1230, -150)
2nd solution, (x, y) = (2700, -330)
3rd solution, (x, y) = (4170, -510)
*/
pair<int, int> diophantine(int a, int b, int c, int k) {
	int x, y, g = egcd(abs(a), abs(b), x, y);
	x += k * (b / g), x *= c / g;
	y -= k * (a / g), y *= c / g;
	if (a < 0) x *= -1;
	if (b < 0) y *= -1;
	return {x, y};
}

void solve(void) {
	int a = 12, b = 98, c = 60;
	auto sol = diophantine(a, b, c, 3);
	cerr << sol.first << ' ' << sol.second << '\n';
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}