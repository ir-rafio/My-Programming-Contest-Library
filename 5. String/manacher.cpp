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

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for (int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (s[i - p[i]] == s[i + p[i]]) p[i]++;
        if (i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
        p[i]--;
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for(auto c : s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res), end(res));
}

/*
p[oddIndex] - 1 -> the length of the odd length palindrome
p[evenIndex] - 1 -> the length of the even length palindrome
*/

void solve(void) {
    string s = "babba";
    auto p = manacher(s);
    int index = 0;
    int len = 1;
    for (int i = 1; i < size(p); i++) {
        if (p[i] > len) {
            len = p[i];
            index = i / 2 - len / 2;
        }
    }
    for (int i = index; i < index + len; i++) {
        cout << s[i];
    }
}

signed main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}