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
pair<int, int> diophantine(int a, int b, int c, int k) {
	int x, y, g = egcd(abs(a), abs(b), x, y);
	x += k * (b / g), x *= c / g;
	y -= k * (a / g), y *= c / g;
	if (a < 0) x *= -1;
	if (b < 0) y *= -1;
	return {x, y};
}