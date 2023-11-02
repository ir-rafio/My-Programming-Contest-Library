const int nmax = 1e8 + 1;
int mark[(nmax >> 6) + 1];

vector<int> primes;

#define isSet(n, pos) (bool)((n) & (1 << (pos)))
#define Set(n, pos) ((n) | (1 << (pos)))

void sieve(int n) {
    for (int i = 3; i * i <= n; i += 2) {
        if (isSet(mark[i >> 6], (i >> 1) & 31) == 0) {
            for (int j = i * i; j <= n; j += (i << 1)) 
                mark[j >> 6] = Set(mark[j >> 6], (j >> 1) & 31);
        }
    }

    primes.emplace_back(2);
    for (int i = 3; i <= n; i += 2) {
        if (isSet(mark[i >> 6], (i >> 1) & 31) == 0)
            primes.emplace_back(i);
    }
}