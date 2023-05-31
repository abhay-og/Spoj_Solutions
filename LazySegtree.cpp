struct segtree{
    vector<ll> t,lazy;
    ll sz=1;
    segtree(ll n){
        sz=1;
        while(sz<n)sz=sz*2;
        t.assign(2*sz,0);
        lazy.assign(2*sz,0);
    }
    void propogate(ll node_pos,ll lx,ll rx){
        if(rx==lx+1 || lazy[node_pos]==0)return;
        lazy[2*node_pos+1]+=lazy[node_pos];
        lazy[2*node_pos+2]+=lazy[node_pos];
        ll mid=(lx+rx)/2;
        t[2*node_pos+1]+=lazy[node_pos]*(mid-lx);
        t[2*node_pos+2]+=lazy[node_pos]*(rx-mid);
        lazy[node_pos]=0;
    }
    void update(ll pos,ll val){
        update(pos,val,0,0,sz);
    }
    void update(ll pos,ll val,ll node_pos,ll lx,ll rx){
        propogate(node_pos,lx,rx);
        if(rx==lx+1){
            t[node_pos]=val;
            return;
        }
        ll mid=(lx+rx)/2;
        if(pos<mid)update(pos,val,2*node_pos+1,lx,mid);
        else update(pos,val,2*node_pos+2,mid,rx);
        t[node_pos]=t[2*node_pos+1]+t[2*node_pos+2];
    }
    void set(ll l,ll r,ll val){
        set(l,r,val,0,0,sz);
    }
    void set(ll l,ll r,ll val,ll node_pos,ll lx,ll rx){
        propogate(node_pos,lx,rx);
        if(lx>=r || rx<=l)return;
        if(lx>=l && rx<=r){
            lazy[node_pos]+=val;
            t[node_pos]+=(val)*(rx-lx);
            return;
        }
        ll mid=(lx+rx)/2;
        set(l,r,val,2*node_pos+1,lx,mid);
        set(l,r,val,2*node_pos+2,mid,rx);
        t[node_pos]=t[2*node_pos+1]+t[2*node_pos+2];
    }
    ll get(ll l,ll r){
        return get(l,r,0,0,sz);
    }
    ll get(ll l,ll r,ll node_pos,ll lx,ll rx){
        propogate(node_pos,lx,rx);
        if(lx>=r || rx<=l)return 0;
        if(lx>=l && rx<=r)return t[node_pos];
        ll mid=(lx+rx)/2;
        return get(l,r,2*node_pos+1,lx,mid)+get(l,r,2*node_pos+2,mid,rx);
    }
};
