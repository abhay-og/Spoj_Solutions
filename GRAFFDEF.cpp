#include<bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set=tree<T,null_type, less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T>
using ordered_multiset=tree<T,null_type,less_equal<T>,rb_tree_tag, tree_order_statistics_node_update>;
using ll=long long;
using ld=long double;
const int MOD=1e9+7;
const ll INF=1e18;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll rand_ll(ll l=0, ll r=1e18){uniform_int_distribution<ll> uid(l,r);return uid(rng);}
ll n,m,timer;
vector<set<ll>> graph;
vector<bool> vis;
vector<ll> tin,low;
vector<pair<ll,ll>> ans;

void dfs(ll v,ll p){
    vis[v]=1;
    tin[v]=low[v]=timer++;
    for(auto &z:graph[v]){
        if(z==p)continue;
        if(vis[z]){
            low[v]=min(low[v],tin[z]);
        }
        else{
            dfs(z,v);
            low[v]=min(low[v],low[z]);
            if(low[z]>tin[v]){
                ans.push_back({min(v,z),max(v,z)});
            }
        }
    }
}

struct DSU{
    vector<ll>dsp,si;
    void make(ll v){
        dsp[v]=v;
        si[v]=1;
    }
    DSU(ll n){
        dsp.resize(n+1);
        si.resize(n+1);
        for(ll i=1;i<=n;i++)make(i);
    }
    ll find(ll v){
        if(v==dsp[v]) return v;
        return dsp[v]=find(dsp[v]);
    }
    void unio(ll a,ll b){
        a=find(a);
        b=find(b);
        if(a!=b){
            if(si[a]<si[b]) swap(a,b);
            dsp[b]=a;
            si[a]+=si[b];
        }
    }
};

void solve(){
    cout<<setprecision(30);
    cin>>n>>m;
    graph.resize(n+1);
    vis.assign(n+1,0);
    tin.assign(n+1,0);
    low=tin;
    timer=0;
    ans.clear();
    for(ll i=0,u,v;i<m;i++){
        cin>>u>>v;
        graph[u].insert(v);
        graph[v].insert(u);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i])dfs(i,0);
    }
    for(auto &z:ans){
        graph[z.first].erase(z.second);
        graph[z.second].erase(z.first);
    }
    DSU d(n);
    for(int i=1;i<=n;i++){
        for(auto &z:graph[i])d.unio(i,z);
    }
    ll den=(n*(n-1))/2;
    set<ll> par;
    for(int i=1;i<=n;i++)par.insert(d.find(i));
    vector<ll> sz;
    for(auto &z:par)sz.push_back(d.si[z]);
    ll num=0;
    for(auto &z:sz)num+=(n-z)*z;
    num/=2;
    ld ans=(ld)num/(ld)den;
    cout<<ans<<'\n';
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t=1;
    // cin>>t;
    for (int i=1;i<=t;i++){
        // cout<<"Caso #"<<i<<'\n';
        solve();
    }
    return 0;
}


//related to bridges again :)
