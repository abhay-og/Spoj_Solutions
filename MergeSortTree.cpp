class SegTree{
public:
    struct Node{//change the struct here
        ll val;
        vector<ll> v;
        Node(ll x=0){
            val=x;
        }
    };
    ll sz;
    vector<Node> t;
    Node Nil;
    //define the Nil element here
    void DefineNil(){
        Nil.val=0;
        Nil.v.clear();
    }
    Node Merge(const Node &a,const Node &b){
        Node res=Nil;
        res.val=a.val+b.val;
        int i=0,j=0;
        for(;i<a.v.size()&&j<b.v.size();){
            if(a.v[i]<b.v[j]){
                res.v.push_back(a.v[i]);
                i++;
            }
            else{
                res.v.push_back(b.v[j]);
                j++;
            }
        }
        while(i<a.v.size()){
            res.v.push_back(a.v[i]);
            i++;
        }
        while(j<b.v.size()){
            res.v.push_back(b.v[j]);
            j++;
        }
        return res;
    }
    //define single element operation here
    Node SingleElement(ll z){
        Node res;
        res.val=1;
        res.v.push_back(z);
        return res;
    }
    //define the constructor here
    SegTree(vector<ll>&a){
        sz=1;
        while(sz<a.size())sz*=2;
        DefineNil();
        t.assign(2*sz,Nil);
        Build(a,0,0,sz);
    }
    void Build(vector<ll>&a,ll node_pos,ll lx,ll rx){
        if(rx-lx==1){
            if(lx>=a.size())return;
            t[node_pos]=SingleElement(a[lx]);
            return;
        }
        ll mid=(lx+rx)/2;
        Build(a,2*node_pos+1,lx,mid);
        Build(a,2*node_pos+2,mid,rx);
        t[node_pos]=Merge(t[2*node_pos+1],t[2*node_pos+2]);
    }
    //function to update the value of a particular position
    void Set(ll pos,ll new_val){
        Set(pos,new_val,0,0,sz);
    }
    void Set(ll pos,ll new_val,ll node_pos,ll lx,ll rx){
        if(rx-lx==1){
            t[node_pos]=SingleElement(new_val);
            return;
        }
        ll mid=(lx+rx)/2;
        if(pos<mid)Set(pos,new_val,2*node_pos+1,lx,mid);
        else Set(pos,new_val,2*node_pos+2,mid,rx);
        t[node_pos]=Merge(t[2*node_pos+1],t[2*node_pos+2]);
    }
    //function to get queries answered
    ll QueryLessThan(ll l,ll r,ll val){
        return QueryLessThan(l,r,val,0,0,sz);
    }
    ll QueryLessThan(ll l,ll r,ll val,ll node_pos,ll lx,ll rx){//given value is less than how many elements in the given range
        if(lx>=r || rx<=l)return 0;
        if(lx>=l && rx<=r){
            ll it=upper_bound(t[node_pos].v.begin(),t[node_pos].v.end(),val)-t[node_pos].v.begin();
            return t[node_pos].val-it;
        }
        ll mid=(lx+rx)/2;
        ll res=0;
        ll res1=QueryLessThan(l,r,val,2*node_pos+1,lx,mid);
        ll res2=QueryLessThan(l,r,val,2*node_pos+2,mid,rx);
        res=res1+res2;
        return res;
    }
    ll QueryGreaterThan(ll l,ll r,ll val){
        return QueryGreaterThan(l,r,val,0,0,sz);
    }
    ll QueryGreaterThan(ll l,ll r,ll val,ll node_pos,ll lx,ll rx){//given value is greater than how many elements in the given range
        if(lx>=r || rx<=l)return 0;
        if(lx>=l && rx<=r){
            ll it=lower_bound(t[node_pos].v.begin(),t[node_pos].v.end(),val)-t[node_pos].v.begin();
            return it;
        }
        ll mid=(lx+rx)/2;
        ll res=0;
        ll res1=QueryGreaterThan(l,r,val,2*node_pos+1,lx,mid);
        ll res2=QueryGreaterThan(l,r,val,2*node_pos+2,mid,rx);
        res=res1+res2;
        return res;
    }
};
