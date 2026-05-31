const int N = 1e6 + 5;
int tree[4 * N];
BI lazy[4 * N];
 
template<typename node, typename change>
struct SegmentTree
{
    int n;

    node *tree, identity;
    node (*merge)(node, node);
 
    change *lazy, noChange;
    void (*applyUpdate)(int, int, node&, change);
    void (*mergeUpdate)(int, int, change&, change);
 
    void build(vector<node> &input, int lo, int hi, int root = 0)
    {
        if(lo == hi)
        {
            tree[root] = input[lo];
            return;
        }
 
        int mid = (lo + hi) / 2, leftChild = 2 * root + 1, rightChild = 2 * root + 2;
        
        build(input, lo, mid, leftChild);
        build(input, mid + 1, hi, rightChild);
        tree[root] = merge(tree[leftChild], tree[rightChild]);
    }
 
    void propagate(int lo, int hi, int root)
    {
        applyUpdate(lo, hi, tree[root], lazy[root]);
 
        if(lo < hi)
        {
            int mid = (lo + hi) / 2, leftChild = 2 * root + 1, rightChild = 2 * root + 2;
 
            mergeUpdate(lo, mid, lazy[leftChild], lazy[root]);
            mergeUpdate(mid + 1, hi, lazy[rightChild], lazy[root]);
        }
 
        lazy[root] = noChange;
    }
 
    void update(int from, int to, int lo, int hi, int root, change delta)
    {
        if(lo > hi) return;
        if(from > hi || to < lo) return;
        
        propagate(lo, hi, root);
 
        if(from <= lo && to >= hi)
        {
            mergeUpdate(lo, hi, lazy[root], delta);
            propagate(lo, hi, root);
            return;
        }
 
        int mid = (lo + hi) / 2, leftChild = 2 * root + 1, rightChild = 2 * root + 2;
        
        update(from, to, lo, mid, leftChild, delta);
        update(from, to, mid + 1, hi, rightChild, delta);
        tree[root] = merge(tree[leftChild], tree[rightChild]);
    }
 
    node query(int from, int to, int lo, int hi, int root)
    {
        if(lo > hi) return identity;
        if(from > hi || to < lo) return identity;
        
        propagate(lo, hi, root);
 
        if(from <= lo && to >= hi) return tree[root];
        
        int mid = (lo + hi) / 2, leftChild = 2 * root + 1, rightChild = 2 * root + 2;
        
        node q1 = query(from, to, lo, mid, leftChild);
        node q2 = query(from, to, mid + 1, hi, rightChild);
        return merge(q1, q2);
    }
 

    SegmentTree(const SegmentTree&) = default;
 
    SegmentTree(
        vector<node> &input,
        node (*merge)(node, node),
        node identity,
        void (*applyUpdate)(int, int, node&, change),
        void (*mergeUpdate)(int, int, change&, change),
        change noChange,
        node* treeArray,
        change* lazyArray
        ):
    
        tree(treeArray), lazy(lazyArray), n(input.size()),
        merge(merge), identity(identity),
        applyUpdate(applyUpdate), mergeUpdate(mergeUpdate), noChange(noChange)
    {
        if(n == 0) return;
        build(input, 0, n - 1);
        fill(lazy, lazy + 4 * n, noChange);
    }
 
    node query(int from, int to)
    {
        if(from > to || to >= n) return identity;
        return query(from, to, 0, n - 1, 0);
    }
 
    void update(int from, int to, change delta)
    {
        update(from, to, 0, n - 1, 0, delta);
    }
};
 
int minVal(int a, int b)
{
    return min(a, b);
}
 
void applyReplace(int lo, int hi, int& val, BI delta)
{
    auto [flag, newVal] = delta;
    if(flag == 1) val = newVal;
}
 
void mergeReplace(int lo, int hi, BI& delta1, BI delta2)
{
    auto [flag, newVal] = delta2;
    if(flag == 1) delta1 = delta2;
}

int MAX = 1e9 + 5;
BI UPD = {0, 0};

SegmentTree<int,BI> segtree(
    v,
    minVal,
    MAX,
    applyReplace,
    mergeReplace,
    UPD,
    tree,
    lazy
);
