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

vector<int> z(string const& s) {
    int n = size(s);
    vector<int> z(n);
    int x = 0, y = 0;
    for (int i = 1; i < n; i++) {
    	z[i] = max(0, min(z[i - x], y - i + 1));
    	while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
    		x = i, y = i + z[i], z[i]++;
    	}
    }
    return z;
}

vector<int> match(string const& p, string const& t) {
    string s = p + "$" + t;
    int m = size(t), n = size(p);
    vector<int> pi = z(s), res;
    for (int i = n + 1; i < n + m + 1; i++) {
        if (pi[i] == n) {
            res.emplace_back(i - (n + 1));
        }
    }
    return res;
}

void solve(void) {
	string p = "aba", t = "abcababa"; cin >> p >> t;
	auto ans = match(p, t);
	for (auto i : ans) cout << i << ' ';
	cout << '\n';
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}