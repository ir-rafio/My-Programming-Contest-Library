#include <bits/stdc++.h>

// code n drink Pennyroyal tea
#ifdef Pennyroyal
#include <debug.h>
#else
#define debug(...)
#define sdebug(...)
#endif

using namespace std;

struct KMP {
    vector<int> prefix(string const& s) {
        int n = size(s);
        vector<int> pi(n);
        for (int i = 1; i < n; i++) {
            int j = pi[i - 1];
            while (j > 0 and s[i] != s[j]) {
                j = pi[j - 1];
            }
            if (s[i] == s[j]) j++;
            pi[i] = j;
        }
        return pi;
    }

    vector<int> match(string const& p, string const& t) {
        string s = p + "$" + t;
        int m = size(t), n = size(p);
        vector<int> pi = prefix(s), res;
        for (int i = n + 1; i < n + m + 1; i++) {
            if (pi[i] == n) {
                res.emplace_back(i - 2 * n); // i - (n + 1) - n + 1
            }
        }
        return res;
    }
    
    vector<vector<int>> g;             // prefix tree
    vector<int> pref_cnt;
    int limit = 0;
    void build_prefix_tree(string const &s) {
        auto pi = prefix(s);
        int n = size(s);
        g.resize(n + 1);
        pref_cnt.assign(n + 1, -1);
        for (int i = n - 1; i >= 0; i--) {
            g[pi[i]].emplace_back(i + 1);
        }
    }
    void build_prefix_tree(string &s, string const &t) {
        string ss = s + "$" + t;
        auto pi = prefix(ss);
        int n = size(ss); limit = size(s) + 1;
        g.resize(n + 1);
        pref_cnt.assign(n + 1, -1);
        for (int i = n - 1; i >= 0; i--) {
            g[pi[i]].emplace_back(i + 1);
        }
    }

    int dfs_prefix(int u) {
        int res = 1;
        for (auto v : g[u]) {
            res += dfs_prefix(v);
        }
        if (u < limit) res--;
        return pref_cnt[u] = res;
    }
    
    int countUniqueSubstrings(string const& s) {
        int res = 0;
        string ss = "";
        for (auto c : s) {
            ss += c;
            auto rs = ss;
            reverse(begin(rs), end(rs));
            vector<int> pi = prefix(rs);
            res += size(ss) - *max_element(begin(pi), end(pi));
        }
        return res;
    }
    
    string period(string const& s) {
        auto pi = prefix(s);
        int n = size(s);
        int k = n - pi[n - 1];
        return n % k == 0 ? s.substr(0, k) : s;
    }
    
} matcher;

/*
             p     t
in:         aba abcababa 
indc:       3 5
pref_cnt:   9 4 3

s = p$t
i:  0 1 2 3 4 5 6 7 8 9 0 1
s:  a b a $ a b c a b a b a
pi: 0 0 1 0 1 2 0 1 2 3 2 3
*/

void solve(void) {
    string p, t; cin >> p >> t;
    
    vector<int> indc = matcher.match(p, t);
    for (auto i : indc) cout << i << ' ';
    cout << '\n';
    
    matcher.build_prefix_tree(p, t);
    matcher.dfs_prefix(0);
    for (int i = 0; i <= size(p); i++) {
        cout << matcher.pref_cnt[i] << ' ';
    }
    cout << '\n';

    cout << matcher.countUniqueSubstrings("baba") << '\n';
    
    cout << matcher.period("abacab") << '\n';
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}