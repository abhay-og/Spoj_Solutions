struct SegmentTree{   // 0 indexed [l,r] queries
    vector<ll> tree;
    vector<ll> arr;
    ll n;
    SegmentTree(const vector<ll>& input){
        arr=input;
        n=arr.size();
        tree.resize(4*n); 
        buildTree(1,0,n-1);
    }
    void buildTree(ll node,ll start,ll end){
        if (start == end){
            tree[node]=start;
        } else{
            ll mid=(start+end)/2;
            buildTree(2*node,start,mid);
            buildTree(2*node+1,mid+1,end);
            ll leftIdx=tree[2*node];
            ll rightIdx=tree[2*node+1];
            tree[node]=(arr[leftIdx]<arr[rightIdx])?leftIdx:rightIdx;
        }
    }
    ll query(ll node,ll start,ll end,ll left,ll right){
        if(start>right||end<left)return -1; 
        if(start>=left&&end<=right)return tree[node]; 
        ll mid=(start+end)/2;
        ll leftIdx=query(2*node,start,mid,left,right);
        ll rightIdx=query(2*node+1,mid+1,end,left,right);
        if(leftIdx==-1)return rightIdx;
        if(rightIdx==-1)return leftIdx;
        return (arr[leftIdx]<arr[rightIdx])?leftIdx:rightIdx;
    }
    int findMinIndex(int left,int right){
        return query(1,0,n-1,left,right);
    }
};
