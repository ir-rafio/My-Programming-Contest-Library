vector<int> moves, dp;

int mex(vector<int> &a) {
    set<int> b(a.begin(), a.end());
    for (int i = 0; ; ++i)
        if (!b.count(i))
            return i;
}

/*
there are k moves.
if XOR(grundy(input)) == 0: losing state
else winning state
*/
int grundy(int x) {
	if (dp[x] != -1) return dp[x];
	vector<int> reachable;
	for (auto m : moves) {
		if (x - m < 0) continue;
		int val = grundy(x - m);
		reachable.push_back(val);
	}
	return dp[x] = mex(reachable);
}