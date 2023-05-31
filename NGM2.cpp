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

void solve(){
    ll n,k,l,num=0,cnt;
    cin>>n>>k;
    vector<ll> p(k);
    for(auto &z:p)cin>>z;
    for(int mask=0;mask<(1ll<<k);mask++){
        l=1;
        int set_bits=__builtin_popcount(mask);
        for(int i=0;i<k;i++){
            if(mask&(1ll<<i)){
                l=(l*p[i])/__gcd(l,p[i]);
            }
        }
        cnt=n/l;
        if(set_bits&1)num-=cnt;
        else num+=cnt;
    }
    cout<<num<<'\n';
}

int main() {
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t=1;
    // cin>>t;
    for (int i=1;i<=t;i++){
        // cout<<"Case #"<<i<<' ';
        solve();
    }
    return 0;
}
