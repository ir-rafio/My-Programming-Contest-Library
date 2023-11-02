template<typename node, typename change>
class SegmentTree
{
public:
    int n;

    node *tree, identity;
    node (*merge)(node, node);

    change *lazy, noUpdate;
    void (*applyUpdate)(int, int, node&, change);
    void (*mergeUpdate)(int, int, change&, change);

    void build(vector<node> &input, int lo, int hi, int root=0)
    {
        if(lo==hi)
        {
            tree[root]=input[lo];
            return;
        }

        int mid=lo+hi>>1, leftChild=2*root+1, rightChild=2*root+2;
        build(input, lo, mid, leftChild);
        build(input, mid+1, hi, rightChild);

        tree[root]=merge(tree[leftChild], tree[rightChild]);
    }

    void propagate(int lo, int hi, int root)
    {
        applyUpdate(lo, hi, tree[root], lazy[root]);

        if(lo<hi)
        {
            int mid=lo+hi>>1, leftChild=2*root+1, rightChild=2*root+2;

            mergeUpdate(lo, mid, lazy[leftChild], lazy[root]);
            mergeUpdate(mid+1, hi, lazy[rightChild], lazy[root]);
        }

        lazy[root]=noUpdate;
    }

    void update(int from, int to, int lo, int hi, int root, change delta)
    {
        if(lo>hi) return;
        
        propagate(lo, hi, root);
        if(from>hi || to<lo) return;

        if(from<=lo && to>=hi)
        {
            mergeUpdate(lo, hi, lazy[root], delta);
            propagate(lo, hi, root);
            return;
        }

        int mid=lo+hi>>1, leftChild=2*root+1, rightChild=2*root+2;
        update(from, to, lo, mid, leftChild, delta);
        update(from, to, mid+1, hi, rightChild, delta);

        tree[root]=merge(tree[leftChild], tree[rightChild]);
    }

    node query(int from, int to, int lo, int hi, int root)
    {
        if(lo>hi) return identity;
        
        propagate(lo, hi, root);
        if(from>hi || to<lo) return identity;

        if(from<=lo && to>=hi) return tree[root];
        
        int mid=lo+hi>>1, leftChild=2*root+1, rightChild=2*root+2;
        node q1=query(from, to, lo, mid, leftChild), q2=query(from, to, mid+1, hi, rightChild);
        return merge(q1, q2);
    }

    int lowerbound(int lo, int hi, int root, node val)
    {
        if(lo>hi) return -1;
        propagate(lo, hi, root);
        
        if(tree[root]<val) return -1;
        if(lo==hi)
        {
            if(tree[root]==val) return hi;
            return -1;
        }

        int mid=lo+hi>>1, leftChild=2*root+1, rightChild=2*root+2;
        int leftSum=query(lo, mid, lo, mid, leftChild);

        if(leftSum>=val) return lowerbound(lo, mid, leftChild, val);
        else return lowerbound(mid+1, hi, rightChild, val-leftSum);
        // val-leftsum works when merge function is sum
    }

    // leftmost position of a minsegtree
    // that has value <= val
    int walk(int lo, int hi, int root, int from, node val)
    {
        if(lo>hi) return -1;

        propagate(lo, hi, root);
        if(from>hi) return -1;
        if(tree[root]>val) return hi;

        if(lo==hi)
        {
            return hi;
        }

        int mid=lo+hi>>1, leftChild=2*root+1, rightChild=2*root+2;
        if(from>mid) return walk(mid+1, hi, rightChild, from, val);
        node q1=query(max(from, lo), mid, lo, mid, leftChild);

        if(q1<=val) return walk(lo, mid, leftChild, from, val);
        return walk(mid+1, hi, rightChild, from, val);
    }

public:
    SegmentTree(SegmentTree& st):
        tree(st.tree), lazy(st.lazy), n(st.n),
        merge(st.merge), identity(st.identity),
        applyUpdate(st.applyUpdate), mergeUpdate(st.mergeUpdate), noUpdate(st.noUpdate)
    {}

    SegmentTree(
        vector<node> &input,
        node (*merge)(node, node),
        node identity,
        void (*applyUpdate)(int, int, node&, change),
        void (*mergeUpdate)(int, int, change&, change),
        change noUpdate
        ):
        n(input.size()),
        merge(merge), identity(identity),
        applyUpdate(applyUpdate), mergeUpdate(mergeUpdate), noUpdate(noUpdate)
    {
        tree=new node[n<<2];
        build(input, 0, n-1);

        lazy=new change[n<<2];
        fill(lazy, lazy+(n<<2), noUpdate);
    }

    node query(int from, int to)
    {
        if(from>to || to>n) return identity;
        return query(from, to, 0, n-1, 0);
    }

    void update(int from, int to, change delta)
    {
        update(from, to, 0, n-1, 0, delta);
    }

    int lowerbound(int val)
    // Only works for non-decreasing function
    {
        return lowerbound(0, n-1, 0, val);
    }

    ~SegmentTree()
    {
        delete[] tree;
        delete[] lazy;
    }
};

int merge(int a, int b)
{
    return a+b;
}

void applyUpdate(int lo, int hi, int& val, int delta)
{
    val+=delta*(hi-lo+1);
}

void mergeUpdate(int lo, int hi, int& val, int delta)
{
    val+=delta;
}