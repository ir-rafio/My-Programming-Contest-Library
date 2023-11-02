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