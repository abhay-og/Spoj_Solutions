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
vector<vector<ll>> graph;
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

void solve(){
    cin>>n>>m;
    graph.clear();
    graph.resize(n+1);
    vis.assign(n+1,0);
    tin.assign(n+1,0);
    low=tin;
    timer=0;
    ans.clear();
    for(ll i=0,u,v;i<m;i++){
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i])dfs(i,0);
    }
    if(ans.size()==0){
        cout<<"Sin bloqueos\n";
        return;
    }
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<'\n';
    for(auto &z:ans)cout<<z.first<<' '<<z.second<<'\n';
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t=1;
    cin>>t;
    for (int i=1;i<=t;i++){
        cout<<"Caso #"<<i<<'\n';
        solve();
    }
    return 0;
}





// code to find bridges ;)
