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

struct LCA{
    vector<vector<ll>> dp;
    vector<vector<pair<ll,ll>>> g;
    vector<ll> dist,par,lvl;
    vector<vector<ll>> mx_dist,mn_dist;
    vector<bool> vis;
    bool f;
    ll n,LOG,a,b,mx; //(a,b) ->ends of the diameter, mx->diameter

    LCA(ll sz){
        n=sz;
        g.resize(n+1);
        dp.resize(n+1);
        dist.assign(n+1,0);
        par.assign(n+1,0);
        lvl.assign(n+1,0);
        LOG=log2l(n)+1;
        for(int i=0;i<=n;i++)dp[i].assign(LOG+2,0);
        mx_dist=dp;
        mn_dist.assign(n+1,vector<ll>(LOG+2,INF));
        f=1;
    }

    void dfs(ll v,ll p){
        par[v]=p;
        lvl[v]=lvl[p]+1;
        for(auto &z:g[v]){
            if(z.first==p)continue;
            mx_dist[z.first][0]=z.second;
            mn_dist[z.first][0]=z.second;
            dfs(z.first,v);
        }
    }

    void initialise(ll v,ll p){
        dp[v][0]=par[v];
        for(int j=1;j<=LOG;j++){
            if(lvl[v]<=(1ll<<j))break;
            dp[v][j]=dp[dp[v][j-1]][j-1];
            mx_dist[v][j]=max(mx_dist[v][j-1],mx_dist[dp[v][j-1]][j-1]);
            mn_dist[v][j]=min(mn_dist[v][j-1],mn_dist[dp[v][j-1]][j-1]);
        }
        for(auto &z:g[v]){
            if(z.first==p)continue;
            initialise(z.first,v);
        }
    }

    ll KthAncestor(ll v,ll k){
        for(int j=0;j<LOG;j++){
            if(k&(1ll<<j))v=dp[v][j];
        }
        return v;
    }

    ll Kth_mx_dist(ll v,ll k){
        ll ans=0;
        for(int j=0;j<LOG;j++){
            if(k&(1ll<<j)){
                ans=max(ans,mx_dist[v][j]);
                v=dp[v][j];
            }
        }
        return ans;
    }

    ll Kth_mn_dist(ll v,ll k){
        ll ans=INF;
        for(int j=0;j<LOG;j++){
            if(k&(1ll<<j)){
                ans=min(ans,mn_dist[v][j]);
                v=dp[v][j];
            }
        }
        return ans;
    }

    ll lca(ll v,ll u){
        if(lvl[u]<lvl[v])swap(u,v);
        ll dif=lvl[u]-lvl[v];
        u=KthAncestor(u,dif);
        if(u==v)return u;
        for(ll j=LOG-1;j>=0;j--){
            if(dp[u][j]!=dp[v][j]){
                u=dp[u][j];
                v=dp[v][j];
            }
        }
        return dp[u][0];
    }

    ll mx_d(ll v,ll u){
        if(lvl[u]<lvl[v])swap(u,v);
        ll dif=lvl[u]-lvl[v];
        ll ans=Kth_mx_dist(u,dif);
        u=KthAncestor(u,dif);
        if(u==v)return ans;
        for(ll j=LOG-1;j>=0;j--){
            if(dp[u][j]!=dp[v][j]){
                ans=max(ans,mx_dist[u][j]);
                ans=max(ans,mx_dist[v][j]);
                u=dp[u][j];
                v=dp[v][j];
            }
        }
        return max({ans,mx_dist[u][0],mx_dist[v][0]});
    }

    ll mn_d(ll v,ll u){
        if(lvl[u]<lvl[v])swap(u,v);
        ll dif=lvl[u]-lvl[v];
        ll ans=Kth_mn_dist(u,dif);
        u=KthAncestor(u,dif);
        if(u==v)return ans;
        for(ll j=LOG-1;j>=0;j--){
            if(dp[u][j]!=dp[v][j]){
                ans=min(ans,mn_dist[u][j]);
                ans=min(ans,mn_dist[v][j]);        
                u=dp[u][j];
                v=dp[v][j];
            }
        }
        return min({ans,mn_dist[u][0],mn_dist[v][0]});
    }

    ll distance(ll v,ll u){
        return dist[u]+dist[v]-2*dist[lca(u,v)];
    }

    ll lvldiff(ll v,ll u){
        return lvl[u]+lvl[v]-2*lvl[lca(u,v)];
    }

    void bfs(ll s){
        vis.assign(n+1,0);
        dist.assign(n+1,INF);
        mx=0;
        queue<ll> q;
        q.push(s);
        vis[s]=1;
        dist[s]=0;
        while(q.size()){
            ll v=q.front();
            q.pop();
            for(auto &z:g[v]){
                if(vis[z.first])continue;
                dist[z.first]=dist[v]+z.second;
                if(mx<dist[z.first]){
                    mx=dist[z.first];
                    if(f)a=z.first;
                    else b=z.first;
                }
                q.push(z.first);
                vis[z.first]=1;
            }
        }
    }

    void initialiseLCA(ll root=1){
        dfs(root,root);
        initialise(root,root);
        bfs(root);
        f=0;
        if(n==1)a=b=1;
        bfs(a);
        bfs(root);
    }
};

void solve(){
    ll n;
    cin>>n;
    LCA L(n);
    for(int i=0,u,v,w;i<n-1;i++){
        cin>>u>>v>>w;
        L.g[u].push_back({v,w});
        L.g[v].push_back({u,w});
    }
    L.initialiseLCA(1);
    ll q,u,v;
    cin>>q;
    while(q--){
        cin>>u>>v;
        cout<<L.mn_d(u,v)<<' '<<L.mx_d(u,v)<<'\n';
    }
    cout<<'\n';
} 

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    solve();
    return 0;
}
