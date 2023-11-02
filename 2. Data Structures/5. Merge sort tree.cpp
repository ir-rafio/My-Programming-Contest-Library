#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int nmax = 1e5 + 1;
int arr[nmax];

class MergeSortTree {
	#define lc ((n) << 1)
    #define rc (((n) << 1) | 1)
    const int identity = 0;
	
	ordered_set<pair<int, int>> tree[4 * nmax];

	inline int merge(int a, int b) {
        return a + b;
    }

public:
	MergeSortTree() {}
	void reset(int n) {
		for (int i = 0; i <= 4 * n; i++) {
			tree[i].clear();
		}
	}
	void build(int n, int b, int e) {
		if (b == e) {
			tree[n].insert({arr[b], b});
			return;
		}
		int mid = (b + e) / 2;
		build(lc, b, mid);
		build(rc, mid + 1, e);
		for (int i = b; i <= e; i++) {
			tree[n].insert({arr[i], i});
		}
	}
	int query(int n, int b, int e, int l, int r, int v, int k) {
        if (b > r || e < l) return identity;
        if (b >= l and e <= r) {
        	int q = tree[n].order_of_key({v, k});
        	return q;
        }
        int mid = (b + e) >> 1;
        int left = query(lc, b, mid, l, r, v, k);
        int right = query(rc, mid + 1, e, l, r, v, k);
        return merge(left, right);
	}
	void update(int n, int b, int e, int i, int v, int nv) {
        if (b > i || e < i) return;
		if (b == i && e == i) {
			tree[n].erase(tree[n].find({v, i}));
	        tree[n].insert({nv, i});
	        return;
        }
        int mid = (b + e) >> 1;
        update(lc, b, mid, i, v, nv);
        update(rc, mid + 1, e, i, v, nv);
        tree[n].erase(tree[n].find({v, i}));
        tree[n].insert({nv, i});
	}
} mergeSortTree;