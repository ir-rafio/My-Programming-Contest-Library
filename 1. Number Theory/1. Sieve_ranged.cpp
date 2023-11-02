const int nmax = 2e5 + 1;
bool mark[nmax];

vector<int> primes;
void sieve(int l, int r) {      // O(r - l)
    for (int i = 2; i * i <= r; i++) {
        for (int j = max(i * i, (l + (i - 1)) / i * i); j <= r; j += i)
            mark[j - l] = 1;
    }
    for (int i = max(2, l); i <= r; i++) {
        if (!mark[i - l])
            primes.push_back(i);
    }
}