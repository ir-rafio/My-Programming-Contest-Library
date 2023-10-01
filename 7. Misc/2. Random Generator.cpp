mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int n=1+rng()%100; // Random number between 1 and 100
